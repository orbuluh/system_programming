# Managing Signals
- from [C++ System Programming Cookbook](https://www.amazon.com/System-Programming-Cookbook-system-level-programming/dp/1838646558)

- For each signal sent to a process, Linux applies its default action.

|   Signal	|   Description	|  Default Action 	|
|---	      |---	          |---	              |
|  SIGABRT 	| Signal sent by abort() | Terminate (with a core dump, if possible)	|
|  SIGSEGV 	| Invalid memory reference | Terminate (with a core dump, if possible)	|
|  SIGSYS 	| Bad system call or process tried to execute an invalid system call. | Terminate (with a core dump, if possible) |
|  SIGQUIT 	| Quit generated from the keyboard (for example: Ctrl + /) | Terminate (with a core dump, if possible) |
|  SIGILL 	| A process tried to execute an illegal instruction | Terminate (with a core dump, if possible) |
|  SIGHUP 	| The Terminal controlling the process was closed (for example, the user logged out?) | Terminate	|
|  SIGINT 	| Interrupt generated from the keyboard (for example Ctrl + C) | Terminate |
|  SIGPIPE 	| A process tried to write to a pipe but with no reader | Terminate |
|  SIGALRM 	| Signal sent by alarm() | Terminate |
|  SIGIO 	| Async I/O event | Terminate |
|  SIGTRAP 	| Breakpoint trapped | Terminate |
|  SIGTERM 	| Termination signal (catchable) | Terminate |
|  SIGKILL 	| Process termination (un-catchable) | Terminate |
|  SIGSTOP 	| Stop a process | Stop the process |
---
- Signals are defined in the <signal.h> header file and are simply positive integers with a meaningful name always prefixed by the SIG word.
- when a signal (that is, a software interrupt) is raised ...
1. The signal is raised by a user of another process, or by Linux itself.
2. The signal is stored until Linux is able to deliver it.
3. Once delivered, Linux performs one of these specific actions:
   a. Ignore the signal: (there are signals that cannot be ignored, for example, SIGKILL)
   b. Perform the default action as listed above
   c. Handle the signal with the registered function (which the system developer implemented).
