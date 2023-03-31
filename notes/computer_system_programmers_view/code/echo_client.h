#pragma once
/*
 * echoclient.c - An echo client
 */

#include <fmt/format.h>

#include <string_view>

#include "util/network_handling.h"
#include "util/robust_io.h"

namespace echoclient {

int run(std::string& host, int port) {
  int clientfd = Open_clientfd(host.data(), port);
  rio_t rio;
  Rio_readinitb(&rio, clientfd);

  char buf[MAXLINE] = {};
  while (Fgets(buf, MAXLINE, stdin) != NULL) {
    std::cout << fmt::format("client sending content\"{}\" to server\n", buf);
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, MAXLINE);
    std::cout << fmt::format("client received content\"{}\" from server\n", buf);
  }
  Close(clientfd);
  exit(0);
}

}  // namespace echoclient