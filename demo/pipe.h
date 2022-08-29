/*
modified from
https://github.com/PacktPublishing/C-System-Programming-Cookbook/blob/master/Chapter06/pipe.c
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static constexpr auto msg1 = "Message sent from Child to Parent";
static constexpr auto msg2 = "Message sent from Parent to Child";

static constexpr auto MSGSIZE = 34;
static constexpr auto IN = 0;
static constexpr auto OUT = 1;

namespace pipe_playground {

int demo() {
  char inbufToParent[MSGSIZE] = {};
  char inbufToChild[MSGSIZE] = {};

  // each file descriptor is a pipe. Crete 2 pipes to achieve duplex
  // idx 0 read pipe(IN)
  // id1x 1 write pipe (OUT)
  int childToParentFds[2] = {};
  int parentToChildFds[2] = {};
  int nbytes = 0;

  inbufToParent[0] = 0;
  inbufToChild[0] = 0;
  if (pipe(childToParentFds) < 0) return 1;

  if (pipe(parentToChildFds) < 0) return 1;

  /*
  - The `read` and `write` system call causes the **process to step in kernel
    mode and save the input data temporarily in kernel space until the second
    process reads it.
  - One rule to follow is that **the unused end of the pipes has to be closed
  */

  auto childPid = fork();
  if (childPid > 0) {
    printf("Created child with PID = %d\n", childPid);

    // NOTE: The rule is the unused end of the pipes has to be closed.

    // child write to parent, close child's read(IN) first
    close(childToParentFds[IN]);
    write(childToParentFds[OUT], msg1, strlen(msg1));

    // we are going to write something from parent to child,
    // after parent read the message above. So we close child's
    // write(OUT) first as a preparation
    close(childToParentFds[OUT]);

    // parent going to read, close parent's write(OUT)
    close(parentToChildFds[OUT]);
    read(parentToChildFds[IN], inbufToChild, strlen(msg2));
    printf("%s\n", inbufToChild);
    // then we close parent's read(IN)
    close(parentToChildFds[IN]);
    wait(NULL);
  } else {
    // the original process (parent) run this code

    // parent going to read from child first, close parent's write(OUT)
    close(childToParentFds[OUT]);
    read(childToParentFds[IN], inbufToParent, strlen(msg1));
    printf("%s\n", inbufToParent);

    // after parent read, we close child's write(IN)
    close(childToParentFds[IN]);

    // going to write something back to child, we close parent's read(IN)
    close(parentToChildFds[IN]);
    write(parentToChildFds[OUT], msg2, strlen(msg2));
    close(parentToChildFds[OUT]);
  }
  return 0;
}

}  // namespace pipe_playground