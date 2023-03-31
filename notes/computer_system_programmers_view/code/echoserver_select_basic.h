
#pragma once

/* Modified from
 * https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/select.c
 * A concurrent echo server based on I/O multiplexing
 * `select` function to ask the kernel to suspend the process, returning
 * control to the application only after one or more I/O events have occurred
 */

#include "util/network_handling.h"
#include "util/io_handling.h"

namespace echoserver_select_basic {

void command() {
  char buf[MAXLINE];
  if (!Fgets(buf, MAXLINE, stdin)) exit(0); /* EOF */
  printf("%s", buf);                        /* Process the input command */
}

int run(int port) {
  const auto listenfd = initListenFd(port);

  fd_set read_set, ready_set;
  FD_ZERO(&read_set);               // create an empty read set
  FD_SET(STDIN_FILENO, &read_set);  // add one file descriptor
  FD_SET(listenfd, &read_set);      // add another file descriptor

  while (true) { // typical server loop
    ready_set = read_set;
    Select(listenfd + 1, &ready_set, nullptr, nullptr, nullptr);
    // instead of waiting for a connection request by calling the `accept`
    // function, we call the `select` function, which blocks until either the
    // listening descriptor or standard input is ready for reading
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      command(); /* read command line from stdin */
    }
    if (FD_ISSET(listenfd, &ready_set)) {
      socklen_t clientlen = sizeof(struct sockaddr_in);
      struct sockaddr_in clientaddr;
      int connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
      echo(connfd); /* echo client input until EOF */
    }
  }
}

} // namespace echoserver_select_basic