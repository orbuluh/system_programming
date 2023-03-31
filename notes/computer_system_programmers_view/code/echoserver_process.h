#pragma once

/* Modified from
 * https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/echoserverp.c
 * A concurrent echo server based on processes
 */

#include <fmt/format.h>

#include <netinet/in.h>
#include <sys/wait.h>

#include <cstdlib>
#include <iostream>

#include "util/io_handling.h"
#include "util/network_handling.h"
#include "util/process_ctrl.h"
#include "util/signal_handling.h"

namespace echoserver_process {

void sigchld_handler(int sig) {
  // Since SIGCHLD signals are blocked while the `SIGCHLD` handler is executing,
  // and since Linux signals are not queued, the `SIGCHLD` handler must be
  // prepared to reap multiple zombie children.
  while (waitpid(-1, 0, WNOHANG) > 0)
    ;
  return;
}

int run(int port) {
  const auto listenfd = initListenFd(port);

  // servers typically run for long periods of time, so we must include a
  // `SIGCHLD` handler that **reaps zombie children**
  Signal(SIGCHLD, sigchld_handler);

  while (true) {
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    std::cout << "Server listening connection for port: " << port
              << "... (blocking)\n";
    int connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

    // The parent forks a child to handle each new connection req
    if (Fork() == 0) {
      // The parent and the child must close their respective copies of `connfd`
      // As we have mentioned, this is especially important for the parent,
      // which must close its copy of the connected descriptor to avoid a memory
      // leak.
      Close(listenfd); /* Child closes its listening socket */
      echo(connfd);    /* Child services client */
      Close(connfd);   /* Child closes connection with client */
      exit(0);         /* Child exits */
    }
    // because of the reference count in the socket’s file table entry, the
    // connection to the client will not be terminated until both the parent’s
    // and child’s copies of `connfd` are closed

    Close(connfd); /* Parent closes connected socket (important!) */
  }
}

}  // namespace echoserver_process