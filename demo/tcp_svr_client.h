/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter07
*/
#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

namespace tcp {

constexpr unsigned int SERVER_PORT = 50544;
constexpr unsigned int MAX_BUFFER = 128;
constexpr unsigned int MSG_REPLY_LENGTH = 18;
constexpr unsigned int MAX_INCOMING_CONN = 5;

namespace server {

int demo() {
  //Server: socket() -> bind() -> listen() -> accept() -> receive() -> send()

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "open socket error" << std::endl;
    return 1;
  }

  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
             sizeof(int));

  struct sockaddr_in serv_addr;
  struct sockaddr_in cli_addr;
  std::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(SERVER_PORT);

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "bind error" << std::endl;
    return 2;
  }

  listen(sockfd, MAX_INCOMING_CONN);
  socklen_t clilen = sizeof(cli_addr);
  int incomingSock = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (incomingSock < 0) {
    std::cerr << "accept error" << std::endl;
    return 3;
  }

  std::cout << "server: got connection from = " << inet_ntoa(cli_addr.sin_addr)
            << " and port = " << ntohs(cli_addr.sin_port) << std::endl;
  write(incomingSock, "You are connected!", MSG_REPLY_LENGTH);

  std::string buffer(MAX_BUFFER, 0);
  if (read(incomingSock, &buffer[0], MAX_BUFFER - 1) < 0) {
    std::cerr << "read from socket error" << std::endl;
    return 4;
  }
  std::cout << "Got the message:" << buffer << std::endl;

  close(incomingSock);
  close(sockfd);
  return 0;
}
}  // namespace server

namespace client {

int demo() {
  // client: socket() -> connect() -> send() -> receive()

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "socket error" << std::endl;
    return 1;
  }

  struct hostent *server = gethostbyname("localhost");
  if (server == nullptr) {
    std::cerr << "gethostbyname, no such host" << std::endl;
    return 2;
  }

  struct sockaddr_in serv_addr;
  std::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons(SERVER_PORT);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "connect error: the server does not look running" << std::endl;
    return 3;
  }

  std::string readBuffer(MAX_BUFFER, 0);
  if (read(sockfd, &readBuffer[0], MAX_BUFFER - 1) < 0) {
    std::cerr << "read from socket failed" << std::endl;
    return 5;
  }
  std::cout << readBuffer << std::endl;

  std::string writeBuffer(MAX_BUFFER, 0);
  std::cout << "What message for the server? : ";
  getline(std::cin, writeBuffer);
  if (write(sockfd, writeBuffer.c_str(), strlen(writeBuffer.c_str())) < 0) {
    std::cerr << "write to socket" << std::endl;
    return 4;
  }

  close(sockfd);
  return 0;
}
}  // namespace client
}  // namespace tcp
