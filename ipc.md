# Inter process communication
- from [C++ System Programming Cookbook](https://www.amazon.com/System-Programming-Cookbook-system-level-programming/dp/1838646558)

- Below four forms of IPC are the ones originally developed on the Unix System V and then reimplemented in the more modern POSIX standard, which Linux supports.
- There are cases where the processes are **not** on the same machine, and in those cases, we need to use other mechanisms such as **sockets**.
  - A socket has wider applicability as it puts in communication processes, regardless of the position on the network.
  - This generality comes at a cost: they are slower than the mechanisms

## Pipe
- The first IPC mechanism in the list is a pipe.
- A pipe **requires a relation between two processes (parent-child, for example) for it to work.**
  - This relation is needed in order to make the pipe visible by both the processes (as opposed to FIFO).
- The communication type is half-duplex:
  - the data flows from process A to process B, and for this reason, there is **no need for synchronization**.
  - In order to achieve a full-duplex communication type between two processes, two pipes must be used.
  - For the same reason that two processes must have a relationship in order to be able to use a pipe, a pipe **cannot** be used as a communication mechanism between **processes on two different machines**.
  - The **Linux kernel is involved** in the communication as the data is copied to the kernel, which is then further copied to the receiver process.
- For the vast majority of use cases, **pipes are intended to be used with small amounts of data**, but there might be scenarios where a larger amount is needed.
  - The standard POSIX says that a write of less than `pipe_BUF` bytes must be atomic.
  - It furthermore dictates that `pipe_BUF` must be at least 512 bytes (on Linux, it is 4 KB); otherwise, you have to take care of the synchronization at the user level by using mechanisms such as semaphores and mutexes.
- [code example](demo/pipe.h)

## FIFO
- The second IPC mechanism in the table is the FIFO (or named pipe).
  - It is a named pipe as it **requires a pathname to be created**, and indeed, it is **a special kind of a file**.
  - This makes the FIFO usable by **any processes even without a relationship between them.**
  - All they need is the path of the FIFO (likewise, a filename) that all the process will use.
- **Synchronization is not required** in this case either.
  - We have to be careful, though, as there are cases where synchronization is required, as the man page specifies.
  - The general rule is that, if you have any doubts about how much data exchange should happen between the processes, always provide a synchronization mechanism (for example, mutex, semaphores, and many others).
  - A FIFO (likewise, a pipe) provides a half-duplex communication mechanism **unless two FIFOs are provided for each process (one reader and one writer for each process);** in that case, it would make it a full-duplex communication.
  - FIFOs are **typically** used for IPC between **processes on the same machine** but, as it is based on files, if the file is visible by other machines, a FIFO could **potentially** be used for IPC between processes on different machines.
  - Even in this case, the kernel is involved in the IPC, with **data copied from kernel space to the user space of the processes.**

## message queue
- A message queue is a **linked list of messages stored in the kernel**.
- This definition already contains a piece of information; this is **a communication mechanism provided by the kernel**, and again, it means that the **data is copied back and forth from/to the kernel**.
- Message queues **do not require any relation between processes**; they have to **share a key to be able to access the same queue**.
- The Linux **kernel guarantees the atomicity of the operations on the queue** if the message is smaller than or equal to `pipe_BUF`.
- In that case, a synchronization mechanism is required.
- A message queue **cannot** be used outside the scope of **a machine**.

## shared memory
- This is the fastest form of IPC.
- This comes with a cost, in the sense that the processes using shared memory should use **a form of synchronization** (for example, mutexes or semaphores), as the man page suggests (man `shm_overview`).
- Processes must be running on the **same machine** to use the same shared memory, and it is identified with a key, likewise for message queues.
- As **the shared memory resides in the kernel space**, data is copied from the kernel space to the processes that read and delete it.

