#pragma once
/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter06/shm_chat_user1.c
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

namespace shared_mem_playground {

static constexpr auto STORAGE_ID1 = "/tmp/SHM_USER1";
static constexpr auto STORAGE_ID2 = "/tmp/SHM_USER2";
static constexpr auto STORAGE_SIZE = 32;

template <bool IsUser1>
void demo() {
  char message1[STORAGE_SIZE] = {};
  char message2[STORAGE_SIZE] = {};

  int fd1 = shm_open(STORAGE_ID1, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  int fd2 = shm_open(STORAGE_ID2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  if ((fd1 == -1) || (fd2 == -1)) {
    perror("failed to shm_open");
    return;
  }

  // extend shared memory object as by default it's initialized with size 0
  if constexpr (IsUser1) {
    int res1 = ftruncate(fd1, STORAGE_SIZE);
    if (res1 == -1) {
        perror("failed to ftruncate");
        return;
    }
  } else {
    int res2 = ftruncate(fd2, STORAGE_SIZE);
    if (res2 == -1) {
        perror("failed to ftruncate");
        return;
    }
  }

  // map shared memory to process address space
  // As shared memory is based on mmap (we essentially map a file to a portion
  // of memory), we need to expand the file pointed by fd1 to the size
  // STORAGE_SIZE that we need. Then, we need to map the two file descriptors to
  // a portion of memory in shared mode (MAP_SHARED)
  void *addr1 = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd1, 0);
  void *addr2 = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd2, 0);
  if ((addr1 == MAP_FAILED) || (addr2 == MAP_FAILED)) {
    perror("failed to  mmap");
    return;
  }

  // In write read below, there is none of the movement of data between user
  // space and kernel space that there was with FIFOs, pipes, and message queues
  // We just do memory copies between local buffers (allocated on the stack) and
  // the memory we mapped, and vice versa.

  // WRITE
  auto write = [&]() {
    fgets(message1, STORAGE_SIZE, stdin);
    int len = strlen(message1) + 1;
    memcpy(IsUser1? addr1: addr2, message1, len);
  };

  // READ
  auto read = [&]() {
    printf("press enter to get data from shared_mem");
    getchar(); // enter to get the data from addr2
    memcpy(message2, IsUser1? addr2: addr1, STORAGE_SIZE);
    printf("%s\n", message2);
  };

  if constexpr (IsUser1) {
    write();
    read();
  } else {
    read();
    write();
  }
}
}  // namespace shared_mem_playground