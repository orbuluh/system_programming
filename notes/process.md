# Process
- from [C++ System Programming Cookbook](https://www.amazon.com/System-Programming-Cookbook-system-level-programming/dp/1838646558)
- [code](demo/process.h)
- The program, by calling `fork`, creates **a copy of the calling process**.
- This means that the two processes have the same code and, although they are two completely different processes, the code base will be the same.
- The user has to hook the child code in the `else if (child == 0)` section.
- The parent, eventually, will have to wait for the child to finish its task with the `wait(&status);` call.
- Another alternative is the `waitpid (123, &status, WNOHANG)` call, which waits for a specific PID (or waits for all the child processes if the first parameter is -1).
  - `WNOHANG` makes `waitpid` immediately return, even if the status of a child is not immediately available.

- What happens if the parent process does not wait for the child to finish? That is, what happens if there is no `wait(&status);` call? 
  - Technically, the parent will finish, and the **child, still running, will become a zombie**.
  - This was a huge problem in the Linux kernel before version 2.6 as **the zombie processes stayed in the system until they were waited for.**
  - The child's processes are now adopted by the `init` process (which has a PID of 1), which, **periodically, waits for children who can die.**

- The most common way of creating processes is the fork/exec combination.
  - As we've seen, fork creates a completely new process with its own PID, but now, the `else if (child == 0)` section executes an external process, **which has a different code base.**

- Why a **process should be used instead of a thread** is an important aspect to consider. The answer depends, but in general, the following aspects should be considered:
  - A t**hread runs in the same memory space of the process that launched it.**
  - This aspect has both pros and cons. The main implication is that if a thread crashes, the whole application crashes.
  - Communication between threads is much faster than interprocess communications.
  - A process can be spawned with lower privileges (through `setrlimit`) to limit the resources available to untrusted code.
  - A program designed in processes is **more segregated** than one designed in threads.

- A process has a **PID** as its unique identifier. It also belongs to a group that has a process group ID (**PGID**).
  - A process group is a collection of one or more processes.
  - **All the processes in the same group can receive signals from the same Terminal**.
  - **Each group has a leader**, and the **PGID has the same value as the leader's PID**.
- A session is **a collection of one or more groups**.
  - A new session can be created by calling the `setsid` method.
  - A session can have a (single) controlling Terminal.
  - The `ps -efj` command shows all the processes running with the PID, PPID, and PGID, and the controlling Terminal (TTY) info for each process: