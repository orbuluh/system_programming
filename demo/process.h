#pragma once
/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter03/process_01.cpp
*/
#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

namespace process_fork {

int demo() {
  int status;
  std::cout << "pid=" << getpid() << " (parent): ppid=" << getppid()
            << " status addr=" << &status << " ready to fork..." << '\n';
  pid_t child = fork();
  if (child == -1) {
    // fork() returns -1 on failure
    std::cout << "pid=" << getpid() << " (parent): fork() failed." << '\n';
    return -1;
  } else if (child == 0) {
    // fork() returns 0 to the child process
    // After calling fork, there are two processes that run independently from
    // each other. The processor switches between them like it does with other
    // separate processes, so you don't know who is going to be scheduled first
    // Both cases can happen. The parent is normally free to run after the
    // system call has checked all possible errors, while the child still has to
    // build a complete environment to run. So it is very possible for the
    // parent to run first.
    std::cout << "pid=" << getpid() << " (child): ppid=" << getppid()
              << " <--(should equal to parent's pid), "
              << "status addr=" << &status << '\n';
  } else {
    // fork() returns the PID of the child to the parent
    std::cout << "pid=" << getpid()
              << " (parent): execute else block and wait ..."
              << " status addr=" << &status << '\n';
    wait(&status);  // wait for the child process to finish...
    // If there is no wait - the parent will finish, and the child, if it's
    // still running, will become a zombie.
    std::cout << "pid=" << getpid() << " (parent): done wait for child\n";
  }
  return 0;
}

}  // namespace process_fork

extern "C" int kill(pid_t pid, int sig);

namespace process_kill {
int demo() {
  int status;
  std::cout << "pid=" << getpid() << "(parent) - before fork\n";
  auto child = fork();
  if (child == -1) {
    std::cout << "fork() failed." << std::endl;
    return 1;
  } else if (child == 0) {
    std::cout << "pid=" << getpid() << "(child) - about to sleep ... (likely"
              << " no chance to run but killed by parent already\n";
    if (execl("/bin/sleep", "sleep", "10", NULL) < 0) {
      std::cout << "pid=" << getpid()
                << "(child) - error in executing child process for sleep cmd\n";
      return 2;
    }
  } else {
    std::cout << "pid=" << getpid()
              << "(parent) - killing the childPid=" << child << '\n';
    int status = kill(child, 9);
    if (status == 0) {
      std::cout << "pid=" << getpid()
                << "(parent) - child process childPid=" << child
                << " killed ...\n";
    } else {
      std::cout << "pid=" << getpid()
                << "(parent) - failed to kill childPid=" << child << '\n';
    }
  }
  return 0;
}
}  // namespace process_kill

namespace process_deamon {
int demo() {
  // When a parent creates a child process, the file mode creation mask is
  // inherited (that is, the child process will inherit the initial access
  // permission of the parent). We want to make sure we reset them.
  umask(0);

  std::cout << "pid=" << getpid() << "(parent) - before fork\n";
  auto child = fork();
  if (child == -1) {
    std::cout << "pid=" << getpid() << "(parent) - fork failed\n";
    return -1;
  } else if (child == 0) {
    std::cout << "pid=" << getpid() << "(child) - before becoming deamon\n";
    // setsid does three things:
    // - The child process becomes the leader of a newly created session.
    // - It becomes the leader of a new process group.
    // - It gets disassociated from its controlling Terminal
    // e.g. setsid is mandatory to make a process to be deamon
    setsid();
    // chdir() changes the current working directory of the calling
    // process to the directory specified in path.
    // why doing this? The parent process might run in a temporary (or mounted)
    // folder that might not exist for long. It's a good practice to set the
    // current folder to meet the long-term expectations of the daemon process.
    if (chdir("/") < 0) std::cout << "Couldn't change directory" << std::endl;
    // Attach here the daemon specific long running tasks ...  like sleep
    sleep(10);
  }

  // after the parent has created the child process, it returns.
  return 0;
}
}  // namespace process_deamon