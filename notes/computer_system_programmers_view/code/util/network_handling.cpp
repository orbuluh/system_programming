#include "network_handling.h"
#include "robust_io.h"
#include "error_handling.h"
#include "shared_vars.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


/****************************
 * Sockets interface wrappers
 ****************************/

int Socket(int domain, int type, int protocol) {
  int rc;

  if ((rc = socket(domain, type, protocol)) < 0) unix_error("Socket error");
  return rc;
}

void Setsockopt(int s, int level, int optname, const void* optval, int optlen) {
  int rc;

  if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
    unix_error("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr* my_addr, int addrlen) {
  int rc;

  if ((rc = bind(sockfd, my_addr, addrlen)) < 0) unix_error("Bind error");
}

void Listen(int s, int backlog) {
  int rc;

  if ((rc = listen(s, backlog)) < 0) unix_error("Listen error");
}

int Accept(int s, struct sockaddr* addr, socklen_t *addrlen) {
  int rc;

  if ((rc = accept(s, addr, addrlen)) < 0) unix_error("Accept error");
  return rc;
}

void Connect(int sockfd, struct sockaddr* serv_addr, int addrlen) {
  int rc;

  if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
    unix_error("Connect error");
}

/************************
 * DNS interface wrappers
 ***********************/

/* $begin gethostbyname */
struct hostent *Gethostbyname(const char* name) {
  struct hostent *p;

  if ((p = gethostbyname(name)) == NULL) dns_error("Gethostbyname error");
  return p;
}
/* $end gethostbyname */

struct hostent *Gethostbyaddr(const char* addr, int len, int type) {
  struct hostent *p;

  if ((p = gethostbyaddr(addr, len, type)) == NULL)
    dns_error("Gethostbyaddr error");
  return p;
}

/********************************
 * Client/server helper functions
 ********************************/
/*
 * open_clientfd - open connection to server at <hostname, port>
 *   and return a socket descriptor ready for reading and writing.
 *   Returns -1 and sets errno on Unix error.
 *   Returns -2 and sets h_errno on DNS (gethostbyname) error.
 */
/* $begin open_clientfd */
int open_clientfd(char *hostname, int port) {
  int clientfd;
  struct hostent *hp;
  struct sockaddr_in serveraddr;

  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return -1; /* check errno for cause of error */

  /* Fill in the server's IP address and port */
  if ((hp = gethostbyname(hostname)) == NULL)
    return -2; /* check h_errno for cause of error */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)hp->h_addr, (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
  serveraddr.sin_port = htons(port);

  /* Establish a connection with the server */
  if (connect(clientfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0) return -1;
  return clientfd;
}
/* $end open_clientfd */

/*
 * open_listenfd - open and return a listening socket on port
 *     Returns -1 and sets errno on Unix error.
 */
/* $begin open_listenfd */
int open_listenfd(int port) {
  int listenfd, optval = 1;
  struct sockaddr_in serveraddr;

  /* Create a socket descriptor */
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  /* Eliminates "Address already in use" error from bind. */
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
                 sizeof(int)) < 0)
    return -1;

  /* Listenfd will be an endpoint for all requests to port
     on any IP address for this host */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);
  if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0) return -1;

  /* Make it a listening socket ready to accept connection requests */
  if (listen(listenfd, LISTENQ) < 0) return -1;
  return listenfd;
}
/* $end open_listenfd */

/******************************************
 * Wrappers for the client/server helper routines
 ******************************************/
int Open_clientfd(char *hostname, int port) {
  int rc;

  if ((rc = open_clientfd(hostname, port)) < 0) {
    if (rc == -1)
      unix_error("Open_clientfd Unix error");
    else
      dns_error("Open_clientfd DNS error");
  }
  return rc;
}

int Open_listenfd(int port) {
  int rc;

  if ((rc = open_listenfd(port)) < 0) unix_error("Open_listenfd error");
  return rc;
}

/******************************************
 * echo - read and echo text lines until client closes connection
 ******************************************/

void echo(int connfd) {
  int n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
    std::cout << "server received " << n << " bytes, ";
    Rio_writen(connfd, buf, n);
    std::cout << "content: \"" << buf << "\"\n";
  }
}

int initListenFd(int port) {
  return Open_listenfd(port);
}