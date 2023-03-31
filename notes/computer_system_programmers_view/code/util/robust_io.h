#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <sys/types.h>

/* Persistent state for the robust I/O (Rio) package */
static constexpr auto RIO_BUFSIZE = 8192;

struct rio_t {
  int rio_fd;                /* descriptor for this internal buf */
  int rio_cnt;               /* unread bytes in internal buf */
  char* rio_bufptr;          /* next unread byte in internal buf */
  char rio_buf[RIO_BUFSIZE]; /* internal buffer */
};

/* Wrappers for Rio package */

ssize_t Rio_readn(int fd, void* userBuffer, size_t n);
void Rio_writen(int fd, void* userBuffer, size_t n);
void Rio_readinitb(rio_t* rp, int fd);
ssize_t Rio_readnb(rio_t* rp, void* userBuffer, size_t n);
ssize_t Rio_readlineb(rio_t* rp, void* userBuffer, size_t maxlen);