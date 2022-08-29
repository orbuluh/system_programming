/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter03/process_01.cpp
*/
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

namespace process_playground {

int demo() {
  int status;
  std::cout << "pid=" << getpid() << " (parent): ppid=" << getppid()
            << " status addr=" << &status << " ready to fork..." << std::endl;
  pid_t child = fork();
  if (child == -1) {
    // fork() returns -1 on failure
    std::cout << "pid=" << getpid() << " (parent): fork() failed." << std::endl;
    return -1;
  } else if (child == 0) {
    // fork() returns 0 to the child process
    std::cout << "pid=" << getpid() << " (child): ppid=" << getppid()
              << " <--(should equal to parent's pid), "
              << "status addr=" << &status << std::endl;
  } else {
    // fork() returns the PID of the child to the parent
    std::cout << "pid=" << getpid()
              << " (parent): execute else block and wait ..."
              << " status addr=" << &status << std::endl;
    wait(&status);  // wait for the child process to finish...
    std::cout << "pid=" << getpid() << " (parent): done wait for child"
              << std::endl;
  }
  return 0;
}

}  // namespace process_playground
