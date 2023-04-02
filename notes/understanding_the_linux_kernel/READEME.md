# [Understanding the Linux Kernel](https://www.amazon.com/Understanding-Linux-Kernel-Third-Daniel/dp/0596005652)

## Overview of the Book

- [Chapter 1, Introduction](ch1.introduction.md), presents a general picture of what is inside a Unix kernel and how Linux competes against other well-known Unix systems.
- The heart of any Unix kernel is memory management. [Chapter 2, Memory Addressing](), explains how 80×86 processors include special circuits to address data in memory and how Linux exploits them.
- Processes are a fundamental abstraction offered by Linux and are introduced in [Chapter 3, Processes](). Here we also explain how each process runs either in an unprivileged User Mode or in a privileged Kernel Mode.
- Transitions between User Mode and Kernel Mode happen only through well-established hardware mechanisms called interrupts and exceptions. These are introduced in [Chapter 4, Interrupts and Exceptions]().
- In many occasions, the kernel has to deal with bursts of interrupt signals coming from different devices and processors. Synchronization mechanisms are needed so that all these requests can be serviced in an interleaved way by the kernel: they are discussed in [Chapter 5, Kernel Synchronization](), for both uniprocessor and multiprocessor systems.
- One type of interrupt is crucial for allowing Linux to take care of elapsed time; further details can be found in [Chapter 6, Timing Measurements]().
- [Chapter 7, Process Scheduling](), explains how Linux executes, in turn, every active process in the system so that all of them can progress toward their completions.
- Next we focus again on memory. [Chapter 8, Memory Management](), describes the sophisticated techniques required to handle the most precious resource in the system (besides the processors, of course): available memory. This resource must be granted both to the Linux kernel and to the user applications.
- [Chapter 9, Process Address Space](), shows how the kernel copes with the requests for memory issued by greedy application programs.
- [Chapter 10, System Calls](), explains how a process running in User Mode makes requests to the kernel, while
- [Chapter 11, Signals](), describes how a process may send synchronization signals to other processes.
- Now we are ready to move on to another essential topic, how Linux implements the filesystem. A series of chapters cover this topic.
- [Chapter 12, The Virtual Filesystem](), introduces a general layer that supports many different filesystems.
- Some Linux files are special because they provide trapdoors to reach hardware devices; [Chapter 13, I/O Architecture and Device Drivers](), and
- [Chapter 14, Block Device Drivers](), offer insights on these special files and on the corresponding hardware device drivers.
- Another issue to consider is disk access time; [Chapter 15, The Page Cache](), shows how a clever use of RAM reduces disk accesses, therefore improving system performance significantly.
- Building on the material covered in these last chapters, we can now explain in [Chapter 16, Accessing Files](), how user applications access normal files.
- [Chapter 17, Page Frame Reclaiming](), completes our discussion of Linux memory management and explains the techniques used by Linux to ensure that enough memory is always available.
- The last chapter dealing with files is [Chapter 18, The Ext2 and Ext3 Filesystems](), which illustrates the most frequently used Linux filesystem, namely Ext2 and its recent evolution, Ext3.
- The last two chapters end our detailed tour of the Linux kernel: [Chapter 19, Process Communication](), introduces communication mechanisms other than signals available to User Mode processes;
- [Chapter 20, Program Execution](), explains how user applications are started.
- Last, but not least, are the appendixes: [Appendix A, System Startup](), sketches out how Linux is booted, while
- [Appendix B, Modules](), describes how to dynamically reconfigure the running kernel, adding and removing functionalities as needed.