/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter06/fifo_chat_user1.c

Check CMakeLists where you set -DRW/-DWR and give executable with different name

*/
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

namespace fifo_playground {

static constexpr int MAX_LENGTH = 128;

int demo() {
  const char* fifoChat = "/tmp/chat";
  mkfifo(fifoChat, 0600); // 600 - write for user, prefix 0 for octave

  char msgReceived[MAX_LENGTH] = {};
  char msgToSend[MAX_LENGTH] = {};

  auto namedPipeWrite = [&]() {
    int fdUser1 = open(fifoChat, O_WRONLY);
    printf("User1: ");
    fgets(msgToSend, MAX_LENGTH, stdin);
    // Note: open is the same method used to open regular files
    write(fdUser1, msgToSend, strlen(msgToSend) + 1);
    close(fdUser1);
  };

  auto namedPipeRead = [&]() {
    int fdUser2 = open(fifoChat, O_RDONLY);
    read(fdUser2, msgReceived, sizeof(msgReceived));
    printf("User2: %s\n", msgReceived);
    close(fdUser2);
  };

  #if defined(RW)
  namedPipeRead();
  namedPipeWrite();
  #elif defined(WR)
  namedPipeWrite();
  namedPipeRead();
  #endif
  return 0;
}

}  // namespace fifo_playground