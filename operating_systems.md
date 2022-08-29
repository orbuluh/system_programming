# Sources
- [Operating Systems Internals and Design Principles, 9th Edition](https://www.amazon.com/Operating-Systems-Internals-Design-Principles/dp/0134670957)

# The objectives of operating systems
- **convenience, efficiency, and ability to evolve**.
- objective itself is hard, and it's even harder because these objectives in some cases competing with each other.

# Why the abstraction of "process"?
Three major lines of computer system development created problems in timing and synchronization that contributed to the development of the concept of the process:

<details><summary markdown="span">multiprogramming</summary>

```markdown
- **Goal**: keep the processor and I/O devices, including storage devices,
  simultaneously busy to achieve maximum efficiency.
- **Mechanics**: In response to signals indicating the completion of I/O
   transactions, the processor is switched among the various programs residing
   in main memory.
```
</details>

<details><summary markdown="span">general-purpose time sharing</summary>

```markdown
- **Goal**: be responsive to the needs of the individual user and yet, for cost
  reasons, be able to support many users simultaneously.
- These goals are compatible because of the relatively slow reaction time of the user.
```
</details>

<details><summary markdown="span">real-time transaction</summary>

```markdown
- **Goal**: a number of users are entering queries or updates against a database.
```
</details>

- The principal tool available to system programmers in developing the early multiprogramming and multiuser interactive systems was the **interrupt**.
- The processor would save some sort of context (e.g., program counter and other registers) and branch to an interrupt-handling routine which would determine the nature of the interrupt, process the interrupt, then resume user processing with the interrupted job or some other job.
- The design of the system software to coordinate these various activities turned out to be remarkably difficult. Four main causes of such errors

<details><summary markdown="span">Improper synchronization:</summary>

```markdown
- It is often the case that a routine must be suspended awaiting an event
  elsewhere in the system.
- Improper design of the signaling mechanism can result in signals being lost
  or duplicate signals being received.
```
</details>

<details><summary markdown="span">Failed mutual exclusion</summary>

```markdown
- It is often the case that more than one user or program will attempt to make
  use of a shared resource at the same time.
- There must be some sort of mutual exclusion mechanism that permits only one
  routine at a time to perform an update against the shared resources.
- The implementation of such mutual exclusion is difficult to verify as being
  correct under all possible sequences of events.
```
</details>

<details><summary markdown="span">Nondeterminate program operation</summary>

```markdown
- when programs share memory, and their execution is interleaved by the
  processor, they may interfere with each other by overwriting common memory
  areas in unpredictable ways.
```
</details>

<details><summary markdown="span">Deadlocks</summary>

```markdown
- two or more programs to be hung up waiting for each other.
```
</details>

What is needed to tackle these problems is a systematic way to monitor and control the various programs executing on the processor.  The concept of the **process** provides the foundation.

# So, what is "process"?
- A program in execution.
- An instance of a program running on a computer.
- The entity that can be assigned to and executed on a processor.
- A unit of activity characterized by a single sequential thread of execution, a current state, and an associated set of system resources.

# 3 components of a process
1. An executable program
2. The associated data needed by the program (variables, work space, buffers, etc.)
<details><summary markdown="span">3. The execution context of the program</summary>

```markdown
- The execution context , or process state , is the internal data by which the
  OS is able to supervise and control the process.
- This internal information is separated from the process, because the OS has
  information not permitted to the process.
- The context includes all of the information the OS needs to manage the process,
  and the processor needs to execute the process properly.
```
</details>

The process is realized as a data structure.
- This process structure is employed to solve the problems raised by multiprogramming and resource sharing.
- New features can be designed and incorporated into the OS (e.g., priority) by expanding the context to include any new information needed to support the feature.

# How about thread?
- In essence, a single process, which is assigned certain resources, can be broken up into **multiple, concurrent threads** that execute cooperatively to **perform the work of the process**.
- This introduces a new level of parallel activity to be managed by the hardware and software.


# Process and memory management
- The OS must prevent independent processes from interfering with each other’s memory, both data and instructions.
- In the same time, sometimes sharing of memory is desirable.
- So OS must allow portions of memory to be accessible in various ways by various users.

# Virtual memory and Pages
- Typically, operating systems meet these requirements with virtual memory.
- Because processes vary in size, if the processor switches among a number of processes, it is difficult to pack them compactly into main memory.
- Paging systems were introduced, which **allow processes to be comprised of a number of fixed-size blocks**, called **pages**.
- A program references a word by means of a virtual address consisting of **a page number and an offset within the page**.
- Each page of a process may be located anywhere in main memory.
- The paging system provides for a dynamic mapping between the **virtual address used in the program and a real address , or physical address, in main memory.**

## Not all pages of a process need to simultaneously reside in main memory
- All the pages of a process are maintained on disk. (Pages of all programs plus the OS are on disk, so as files.)
- When a process is executing, some (or all) of its pages are in main memory.
- If reference is made to a page that is not in main memory, the memory management hardware detects this and, in coordination with the OS, arranges for the missing page to be loaded.

## From user's perspective, a process is handled by a "virtual processor"
- The virtual processor has access to a virtual memory.
- Programming language instructions can reference program and data locations in the virtual memory area.
- Process isolation can be achieved by giving each process a unique, non-overlapping virtual memory.
- Memory sharing can be achieved by overlapping portions of two virtual memory spaces.
- Files are maintained in a long-term store. Files and portions of files may be copied into the virtual memory for manipulation by programs.


# TODO:
- and concurrency issues.
- locks and mutexes and semaphores and monitors and how they work.
- deadlock and livelock and how to avoid them.
- Know what resources a processes needs, and a thread needs,
- how context switching works,
- how it's initiated by the operating system and underlying hardware.
- scheduling. the fundamentals of "modern" concurrency constructs.