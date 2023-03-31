#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <cstdio>

#include <sys/types.h>
#include <sys/stat.h>

/* Unix I/O wrappers */
int Open(const char* pathname, int flags, mode_t mode);
ssize_t Read(int fd, void* buf, size_t count);
ssize_t Write(int fd, const void* buf, size_t count);
off_t Lseek(int fildes, off_t offset, int whence);
void Close(int fd);
int Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout);
int Dup2(int fd1, int fd2);
void Stat(const char* filename, struct stat *buf);
void Fstat(int fd, struct stat *buf);



/* Standard I/O wrappers */
void Fclose(FILE *fp);
FILE *Fdopen(int fd, const char* type);
char* Fgets(char* ptr, int n, FILE *stream);
FILE *Fopen(const char* filename, const char* mode);
void Fputs(const char* ptr, FILE *stream);
size_t Fread(void* ptr, size_t size, size_t nmemb, FILE *stream);
void Fwrite(const void* ptr, size_t size, size_t nmemb, FILE *stream);