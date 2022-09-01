/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter06/mq_chat_user_1.c
*/
#include <mqueue.h> // "mqueue is part of the realtime extension to the POSIX
                    // standard. It is not supported on macOS because macOS is
                    // not a realtime operating system."
#include <stdio.h>

#include <string>

namespace msg_queue_playground {

static constexpr int MAX_MESSAGES = 10;
static constexpr int MAX_MSG_SIZE = 256;

template <bool IsUser1>
void demo() {
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = MAX_MESSAGES;
  attr.mq_msgsize = MAX_MSG_SIZE;
  attr.mq_curmsgs = 0;

  int user1Desc = 0;
  int user2Desc = 0;

  char message[MAX_MSG_SIZE] = {};
  char message2[MAX_MSG_SIZE] = {};

  using namespace std::string_literals;
  const auto actor1 = [&]() {
    if constexpr (IsUser1) {
      return "user1"s;
    } else {
      return "user2"s;
    }
  }();

  const auto actor2 = [&]() {
    if constexpr (IsUser1) {
      return "user2"s;
    } else {
      return "user1"s;
    }
  }();

  if ((user1Desc = mq_open("/tmp/"s + actor1, O_WRONLY | O_CREAT, "0660",
                           &attr)) == -1) {
    auto error = "mq_open error("s + actor1 + ")";
    perror(error.data());
    return;
  }
  if ((user2Desc = mq_open("/tmp/"s + actor2, O_RDONLY | O_CREAT, "0660",
                           &attr)) == -1) {
    auto error = "mq_open error("s + actor2 + ")";
    perror(error.data());
    return;
  }

  std::cout << actor1 << "...\n";
  if constexpr (IsUser1) {
    fgets(message, MAX_MSG_SIZE, stdin);
    if (mq_send(user1Desc, message, strlen(message) + 1, 0) == -1) {
      perror("Not able to send message to User 2");
      return;
    }

    if (mq_receive(user2Desc, message2, MAX_MSG_SIZE, nullptr) == -1) {
      perror("tried to receive a message from User 2 but I've failed!");
      return;
    }
    std::cout << actor2 << message2 << '\n';
  } else {
    std::cout << actor1 << "...\n";
    fgets(message, MAX_MSG_SIZE, stdin);
    if (mq_send(user2Desc, message, strlen(message) + 1, 0) == -1) {
      perror("Not able to send message to User 1");
      return;
    }

    if (mq_receive(user1Desc, message2, MAX_MSG_SIZE, NULL) == -1) {
      perror("tried to receive a message from User 1  but I've failed!");
      return;
    }
  }
  std::cout << actor2 << message2 << '\n';
}
}  // namespace msg_queue_playground