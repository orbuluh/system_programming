/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter10
*/
#pragma once
#include <sys/signal.h> // MAC can't build with <signal.h> nor <csignal> ...
#include <stdio.h>
#include <iostream>

namespace signal_handling {

void usr1SigHandler(int signal) {
  std::cout << "catching user1(" << signal << ") signal... ignoring\n";
}

int demo() {
  std::cout << "Starting ..." << std::endl;
  signal(SIGTERM, SIG_IGN); // ignore sigterm
  signal(SIGKILL, SIG_IGN); // this won't do anything as SIGKILL can't be ignored
  signal(SIGUSR1, usr1SigHandler); // this won't do anything as SIGKILL can't be ignored
  while (true)
    ;
  std::cout << "Ending ..." << std::endl;
  return 0;
}

}  // namespace signal_handling