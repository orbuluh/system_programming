#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <sys/socket.h>

/* Simplifies calls to bind(), connect(), and accept() */
using SA = struct sockaddr;

/* max text line length used for echo server/client*/
static constexpr auto MAXLINE = 8192;

/* Sockets interface wrappers */
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void* optval, int optlen);
void Bind(int sockfd, struct sockaddr* my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr* addr, socklen_t* addrlen);
void Connect(int sockfd, struct sockaddr* serv_addr, int addrlen);

/* DNS wrappers */
struct hostent* Gethostbyname(const char* name);
struct hostent* Gethostbyaddr(const char* addr, int len, int type);

/* Client/server helper functions */
int open_clientfd(char* hostname, int portno);
int open_listenfd(int portno);

/* Wrappers for client/server helper functions */
int Open_clientfd(char* hostname, int port);
int Open_listenfd(int port);

/* read and echo text lines until client closes connection */
void echo(int connfd);

int initListenFd(int port);