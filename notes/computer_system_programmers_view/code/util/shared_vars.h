#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <sys/stat.h>
#include <unistd.h>



/* Misc constants */
static constexpr auto MAXBUF = 8192;  /* max I/O buffer size */
static constexpr auto LISTENQ = 1024; /* second argument to listen() */

/* Default file permissions are DEF_MODE & ~DEF_UMASK */

static constexpr auto DEF_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
static constexpr auto DEF_UMASK = S_IWGRP | S_IWOTH;

/* External variables */
extern char* *environ; /* defined by libc */
