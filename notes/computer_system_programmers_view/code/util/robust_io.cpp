#include "robust_io.h"

#include <unistd.h>

#include <cerrno>
#include <cstring>

#include "error_handling.h"

/*********************************************************************
 * The Rio package - robust I/O functions
 **********************************************************************/
/*
 * rio_readn - robustly read n bytes (unbuffered)
 */
/* $begin rio_readn */
ssize_t rio_readn(int fd, void* userBuffer, size_t n) {
  size_t nleft = n;
  ssize_t nread;
  auto bufp = static_cast<char* >(userBuffer);

  while (nleft > 0) {
    if ((nread = read(fd, bufp, nleft)) < 0) {
      if (errno == EINTR) /* interrupted by sig handler return */
        nread = 0;        /* and call read() again */
      else
        return -1; /* errno set by read() */
    } else if (nread == 0)
      break; /* EOF */
    nleft -= nread;
    bufp += nread;
  }
  return (n - nleft); /* return >= 0 */
}
/* $end rio_readn */

/*
 * rio_writen - robustly write n bytes (unbuffered)
 */

ssize_t rio_writen(int fd, void* userBuffer, size_t n) {
  size_t nleft = n;
  ssize_t nwritten = 0;
  auto bufp = static_cast<char*>(userBuffer);

  while (nleft > 0) {
    if ((nwritten = write(fd, bufp, nleft)) <= 0) {
      if (errno == EINTR) /* interrupted by sig handler return */
        nwritten = 0;     /* and call write() again */
      else
        return -1; /* errorno set by write() */
    }
    nleft -= nwritten;
    bufp += nwritten;
  }
  return n;
}

/*
 * rio_read - This is a wrapper for the Unix read() function that
 *    transfers min(n, rio_cnt) bytes from an internal buffer to a user
 *    buffer, where n is the number of bytes requested by the user and
 *    rio_cnt is the number of unread bytes in the internal buffer. On
 *    entry, rio_read() refills the internal buffer via a call to
 *    read() if the internal buffer is empty.
 */
/* $begin rio_read */
static ssize_t rio_read(rio_t *rp, char* userBuffer, size_t n) {
  int cnt;

  while (rp->rio_cnt <= 0) { /* refill if buf is empty */
    rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
    if (rp->rio_cnt < 0) {
      if (errno != EINTR) /* interrupted by sig handler return */
        return -1;
    } else if (rp->rio_cnt == 0) /* EOF */
      return 0;
    else
      rp->rio_bufptr = rp->rio_buf; /* reset buffer ptr */
  }

  /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
  cnt = n;
  if (rp->rio_cnt < n) cnt = rp->rio_cnt;
  memcpy(userBuffer, rp->rio_bufptr, cnt);
  rp->rio_bufptr += cnt;
  rp->rio_cnt -= cnt;
  return cnt;
}
/* $end rio_read */

/*
 * rio_readinitb - Associate a descriptor with a read buffer and reset buffer
 */
/* $begin rio_readinitb */
void rio_readinitb(rio_t *rp, int fd) {
  rp->rio_fd = fd;
  rp->rio_cnt = 0;
  rp->rio_bufptr = rp->rio_buf;
}
/* $end rio_readinitb */

/*
 * rio_readnb - Robustly read n bytes (buffered)
 */
/* $begin rio_readnb */
ssize_t rio_readnb(rio_t *rp, void* userBuffer, size_t n) {
  size_t nleft = n;
  ssize_t nread;
  auto bufp = static_cast<char* >(userBuffer);

  while (nleft > 0) {
    if ((nread = rio_read(rp, bufp, nleft)) < 0) {
      if (errno == EINTR) /* interrupted by sig handler return */
        nread = 0;        /* call read() again */
      else
        return -1; /* errno set by read() */
    } else if (nread == 0)
      break; /* EOF */
    nleft -= nread;
    bufp += nread;
  }
  return (n - nleft); /* return >= 0 */
}
/* $end rio_readnb */

/*
 * rio_readlineb - robustly read a text line (buffered)
 */
/* $begin rio_readlineb */
ssize_t rio_readlineb(rio_t *rp, void* userBuffer, size_t maxlen) {
  int n, rc;
  char c;
  auto bufp = static_cast<char* >(userBuffer);

  for (n = 1; n < maxlen; n++) {
    if ((rc = rio_read(rp, &c, 1)) == 1) {
      *bufp++ = c;
      if (c == '\n') break;
    } else if (rc == 0) {
      if (n == 1)
        return 0; /* EOF, no data read */
      else
        break; /* EOF, some data was read */
    } else
      return -1; /* error */
  }
  *bufp = 0;
  return n;
}
/* $end rio_readlineb */

/**********************************
 * Wrappers for robust I/O routines
 **********************************/
ssize_t Rio_readn(int fd, void* ptr, size_t nbytes) {
  ssize_t n;

  if ((n = rio_readn(fd, ptr, nbytes)) < 0) {
    unix_error("Rio_readn error");
  }
  return n;
}

void Rio_writen(int fd, void* userBuffer, size_t n) {
  if (rio_writen(fd, userBuffer, n) != n) {
    unix_error("Rio_writen error");
  }
}

void Rio_readinitb(rio_t *rp, int fd) { rio_readinitb(rp, fd); }

ssize_t Rio_readnb(rio_t *rp, void* userBuffer, size_t n) {
  ssize_t rc;

  if ((rc = rio_readnb(rp, userBuffer, n)) < 0) {
    unix_error("Rio_readnb error");
  }
  return rc;
}

ssize_t Rio_readlineb(rio_t *rp, void* userBuffer, size_t maxlen) {
  ssize_t rc;

  if ((rc = rio_readlineb(rp, userBuffer, maxlen)) < 0) {
    unix_error("Rio_readlineb error");
  }
  return rc;
}