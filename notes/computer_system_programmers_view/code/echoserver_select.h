
#pragma once

/* Modified from
 * https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/echoservers.c
 * A concurrent echo server based on I/O multiplexing
 * `select` function to ask the kernel to suspend the process, returning
 * control to the application only after one or more I/O events have occurred
 */

#include <fmt/format.h>

#include <algorithm>
#include <array>

#include "util/error_handling.h"
#include "util/network_handling.h"
#include "util/robust_io.h"

namespace echoserver_select {

// FD_SETSIZE is a macro that defines the maximum number of file descriptors
// that can be used with the select() function on a given platform. It is
// typically defined in the system headers of the C library.

// The set of active clients is maintained in a Pool structure.
// The clientfd array represents a set of connected descriptors, with the
// integer −1 denoting an available slot.
struct Pool {       /* represents a pool of connected descriptors */
  int maxfd = -1;   /* largest descriptor in read_set */
  fd_set read_set;  /* set of all active descriptors */
  fd_set ready_set; /* subset of descriptors ready for reading  */
  int nready = 0;   /* number of ready descriptors from select */
  int maxi = 0;     /* highwater index into client array */
  std::array<int, FD_SETSIZE> clientfd;    /* set of active descriptors */
  std::array<rio_t, FD_SETSIZE> clientrio; /* set of active read buffers */
};

void init_pool(int listenfd, Pool& p);
void add_client(int connfd, Pool& p);
void check_clients(Pool& p);

int run(int port) {
  struct sockaddr_in clientaddr;
  static Pool pool;

  const auto listenfd = initListenFd(port);
  init_pool(listenfd, pool);

  while (1) {
    /* Wait for listening/connected descriptor(s) to become ready */
    pool.ready_set = pool.read_set;

    // During each iteration of the loop, the server calls the select function
    // to detect two different kinds of input events:
    // - (1) a connection request arriving from a new client (add_client)
    // - (2) a connected descriptor for an existing client being ready for
    //       reading (check_clients)

    pool.nready =
        Select(pool.maxfd + 1, &pool.ready_set, nullptr, nullptr, nullptr);

    /* If listening descriptor ready, add new client to pool */
    if (FD_ISSET(listenfd, &pool.ready_set)) {
      socklen_t clientlen = sizeof(struct sockaddr_in);
      int connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
      add_client(connfd, pool);
    }

    /* Echo a text line from each ready connected descriptor */
    check_clients(pool);
  }
}

void init_pool(int listenfd, Pool& p) {
  /* Initially, there are no connected descriptors */
  p.maxi = -1;
  std::fill(p.clientfd.begin(), p.clientfd.end(), -1);

  /* Initially, listenfd is the only member of select read set */
  p.maxfd = listenfd;
  FD_ZERO(&p.read_set);
  FD_SET(listenfd, &p.read_set);
}

void add_client(int connfd, Pool& p) {
  p.nready--;
  const auto availableSlot = [&]() {
    for (int i = 0; i < FD_SETSIZE; i++) { /* Find an available slot */
      if (p.clientfd[i] < 0) {
        /* Add connected descriptor to the pool */
        p.clientfd[i] = connfd;
        // initializes a corresponding Rio read buffer so that we can call
        // rio_readlineb on the descriptor
        Rio_readinitb(&p.clientrio[i], connfd);

        /* Add the descriptor to descriptor set */
        FD_SET(connfd, &p.read_set);

        // The maxfd variable keeps track of the largest file descriptor for
        // select.
        p.maxfd = std::max(connfd, p.maxfd);
        // The maxi variable keeps track of the largest index into the clientfd
        // array so that the check_clients function does not have to search the
        // entire array.
        p.maxi = std::max(i, p.maxi);
        return i;
      }
    }
    return FD_SETSIZE;
  }();

  if (availableSlot == FD_SETSIZE) { /* Couldn't find an empty slot */
    app_error("add_client error: Too many clients");
  }
}

void check_clients(Pool& p) {
  int bytesRead = 0;
  char buf[MAXLINE] = {};
  rio_t rio;

  for (int i = 0; (i <= p.maxi) && (p.nready > 0); i++) {
    int connfd = p.clientfd[i];
    rio = p.clientrio[i];

    /* If the descriptor is ready, echo a text line from it */
    if ((connfd > 0) && (FD_ISSET(connfd, &p.ready_set))) {
      p.nready--;
      if ((bytesRead = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        std::cout << fmt::format(
            "Server received {} bytes from fd {}. Content: \"{}\". Sending it "
            "back...\n",
            bytesRead, connfd, buf);
        // server echo what client sent back to client
        Rio_writen(connfd, buf, bytesRead);
      } else {
        // If we detect EOF because the client has closed its end of the
        // connection, then we close our end of the connection and remove the
        // descriptor from the pool (lines 24–25)
        std::cout << fmt::format("Server close fd {}\n", connfd);
        Close(connfd);
        FD_CLR(connfd, &p.read_set);
        p.clientfd[i] = -1;
      }
    }
  }
}

}  // namespace echoserver_select