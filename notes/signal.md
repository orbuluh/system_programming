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

# What does happen to signals when a process forks (or executes) another one?
| Signal Behavior	  | `fork`ed child	| `exec`ed child 	|
|---	              |---	            |---	            |
|Default            |Inherited        |Inherited        |
|Ignored            |Inherited        |Inherited        |
|Customized handler |Inherited        |NOT Inherited    |

- when a process forks another process, the child essentially inherits all the behaviors of the parent.
- When a process executes another task (with `exec`), it **inherits the default behavior and the ignored behavior,but it does not inherit the handled method that is implemented.**

# send a signal to another process

- In order to send a signal to another process (or processes), the sending process must have appropriate privileges. (A process can send signals to another process if the current user owns it.)
- There might be cases where a process has to send a signal to itself. In this case, the system call, `raise()`, does the job
- Note: The handler code that manages the signal raised must be **reentrant**.
  - A function is **reentrant** if the data manipulated is** allocated on the stack or passed in the input.**
  - The rationale behind that is that the process might be in the middle of any processing, so the **handler must be very careful in modifying any static or global data.**