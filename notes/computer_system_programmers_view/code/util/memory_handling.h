#pragma once

/*
Modified from
https://www.cs.cmu.edu/afs/cs/academic/class/15213-f05/code/conc/csapp.h
*/

#include <cstddef>
#include <cstdlib>

#include <sys/types.h>

/* Memory mapping wrappers */
void* Mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset);
void Munmap(void* start, size_t length);

/* Dynamic storage allocation wrappers */
void* Malloc(size_t size);
void* Realloc(void* ptr, size_t size);
void* Calloc(size_t nmemb, size_t size);
void Free(void* ptr);