# Ch 1. Introduction

## Linux Versus Other Unix-Like Kernels

- Linux is a member of the large family of Unix-like operating systems.
- One of the more appealing benefits to Linux is that it isn’t a commercial operating system
- Technically speaking, Linux is a true Unix kernel, although it is not a full Unix operating system because it does not include all the Unix applications, such as filesystem utilities, windowing systems and graphical desktops, system administrator commands, text editors, compilers, and so on.
  - However, because most of these programs are freely available under the GPL, they can be installed in every Linux-based system
- The current standards specify only an application programming interface (API)— that is, a well-defined environment in which user programs should run. Therefore, **the standards do not impose any restriction on internal design choices of a compliant kernel.**
- To define a common user interface, Unix-like kernels often share fundamental design ideas and features. In this respect, Linux is comparable with the other Unix-like operating systems.
- Linux doesn’t stick to any particular variant. Instead, it tries to adopt the best features and design choices of several different Unix kernels.
- The following list describes how Linux competes against some well-known commercial Unix kernels:

**Monolithic kernel**

- It is a large, complex do-it-yourself program, composed of several logically different components. In this, it is quite conventional; most commercial Unix variants are monolithic.
  - (Notable exceptions are the Apple Mac OS X)

**Compiled and statically linked traditional Unix kernels**

- Most modern kernels can **dynamically load and unload some portions of the kernel code** (typically, device drivers), which are usually called **modules**.
- Linux’s support for modules is very good, because it is able to automatically load and unload modules on demand.

**Kernel threading**

- Some Unix kernels, such as Solaris and SVR4.2/MP, are organized as **a set of kernel threads**.
  - A **kernel thread** is an **execution context** that can be independently scheduled;
  - it **may be associated with a user program, or it may run only some kernel functions.**
- **Context switches between kernel threads are usually much less expensive than context switches between ordinary processes**, because the former usually **operate on a common address space**.
- Linux uses kernel threads in a very limited way to **execute a few kernel functions periodically**; however, they do not represent the basic execution context abstraction. (That’s the topic of the next item.)

**Multithreaded application support**

- Most modern operating systems have some kind of support for multithreaded applications—that is, user programs that are designed in terms of **many relatively independent execution flows that share a large portion of the application data structures.**
- A multithreaded user application could be composed of many **lightweight processes (LWP)**, which are **processes that can operate on a common address space, common physical memory pages, common opened files, and so on**.
- Linux defines its own version of lightweight processes, which is different from the types used on other systems such as SVR4 and Solaris.
- While all the commercial Unix variants of LWPare based on kernel threads, **Linux regards lightweight processes as the basic execution context and handles them via the nonstandard `clone()` system call**

**Preemptive kernel**

- A preemptible kernel is a kernel configuration that allows for better responsiveness and lower latency **by enabling the kernel to be preempted or interrupted during its execution.**
  - This means that higher-priority tasks, such as user-space applications or time-sensitive tasks, can take over the CPU more quickly when needed, instead of waiting for the kernel to complete its current operation
- When compiled with the “Preemptible Kernel” option, Linux 2.6 can **arbitrarily interleave execution flows while they are in privileged mode.**

- Besides Linux 2.6, a few other conventional, general-purpose Unix systems, such as Solaris and Mach 3.0, are fully preemptive kernels.
- SVR4.2/MPintroduces some fixed preemption points as a method to get limited preemption capability.

**Multiprocessor support**

- Several Unix kernel variants take advantage of multiprocessor systems.
- Linux 2.6 supports **symmetric multiprocessing (SMP)** for different memory models, including **NUMA**: **the system can use multiple processors and each processor can handle any task**—there is no discrimination among them.
  - **NUMA (Non-Uniform Memory Access)** is a memory architecture used in multiprocessor systems to improve performance and scalability.
  - It divides memory into multiple nodes, each associated with a specific processor.
  - This allows faster access to local memory, reduces resource contention, and enhances the system's ability to scale with a larger number of processors.
- Although a few parts of the kernel code are still serialized by means of a single “big kernel lock,” it is fair to say that Linux 2.6 makes a near optimal use of SMP.

**Filesystem**

- Linux’s standard filesystems come in many flavors.
  - You can use the plain old Ext2 filesystem if you don’t have specific needs.
  - You might switch to Ext3 if you want to avoid lengthy filesystem checks after a system crash.
  - If you’ll have to deal with many small files, the ReiserFS filesystem is likely to be the best choice.
  - Besides Ext3 and ReiserFS, several other journaling filesystems can be used in Linux; they include IBM AIX’s Journaling File System (JFS) and Silicon Graphics IRIX’s XFS filesystem.
- Thanks to a powerful object-oriented **Virtual File System** technology (inspired by Solaris and SVR4), **porting a foreign filesystem to Linux is generally easier than porting to other kernels.**

**STREAMS**

- STREAMS I/O is a modular framework for implementing character-based I/O drivers, introduced in the UNIX System V Release 4 (SVR4).
- Linux, however, chose not to adopt STREAMS and instead developed its own networking and I/O subsystems, which focus on performance, efficiency, and modularity.


This assessment suggests that Linux is fully competitive nowadays with commercial operating systems. Moreover, Linux has several features that make it an exciting operating system.

- Commercial Unix kernels often introduce new features to gain a larger slice of the market, but these features are not necessarily useful, stable, or productive.
- By contrast, Linux—together with the other open source operating systems—doesn’t suffer from the restrictions and the conditioning imposed by the market, hence it can freely evolve according to the ideas of its designers (mainly Linus Torvalds).

Specifically, Linux offers the following advantages over its commercial competitors:


- Linux is cost-free. You can install a complete Unix system at no expense other than the hardware (of course).
- Linux is fully customizable in all its components. Thanks to the compilation options, you can customize the kernel by selecting only the features really needed.
- Moreover, thanks to the GPL, you are allowed to freely read and modify the source code of the kernel and of all system programs.
- Linux runs on low-end, inexpensive hardware platforms. You are able to build a network server using an old Intel 80386 system with 4 MB of RAM.
- Linux is powerful. Linux systems are very fast, because they fully exploit the features of the hardware components.
- **The main Linux goal is efficiency** and indeed many design choices of commercial variants, like the STREAMS I/O subsystem, have been rejected by Linus because of their implied performance penalty.
- Linux systems are very stable; they have a very low failure rate and system maintenance time.
- **The Linux kernel can be very small and compact**. It is possible to fit a kernel image, including a few system programs, on just one 1.44 MB floppy disk.
- Linux is highly compatible with many common operating systems.
  - Linux lets you directly mount filesystems for all versions of MS-DOS and Microsoft Windows, SVR4, OS/2, Mac OS X, Solaris, SunOS, NEXTSTEP, many BSD variants, and so on.
- Linux also is able to operate with many network layers, such as
  - Ethernet (as well as Fast Ethernet, Gigabit Ethernet, and 10 Gigabit Ethernet),
  - Fiber Distributed Data Interface (FDDI),
  - High Performance Parallel Interface (HIPPI),
  - IEEE 802.11 (Wireless LAN), and
  - IEEE 802.15 (Bluetooth).
- By using suitable libraries, Linux systems are even able to directly run programs written for other operating systems.
- Linux is well supported.
  - It may be a lot easier to get patches and updates for Linux than for any proprietary operating system.
  - The answer to a problem often comes back within a few hours after sending a message to some newsgroup or mailing list. Moreover, drivers for Linux are usually available a few weeks after new hardware products have been introduced on the market.
  - By contrast, hardware manufacturers release device drivers for only a few commercial operating systems—usually Microsoft’s.

## Hardware Dependency

- Linux tries to maintain a neat distinction between hardware-dependent and hardware-independent source code.
- To that end, both the `arch` and the `include` directories include 23 subdirectories that correspond to the different types of hardware platforms supported.
- For example:
  - `x86_64`: Workstations based on the AMD’s 64-bit microprocessors—such Athlon and Opteron—and Intel’s ia32e/EM64T 64-bit microprocessors
  - `i386`: IBM-compatible personal computers based on 80x86 microprocessors
  - `ia64`: Workstations based on the Intel 64-bit Itanium microprocessor

## Linux Versions

- For Linux kernel version >= 2.6, the second number no longer identifies stable or development versions.
- The new model of Linux development implies that two kernels having the same version but different release numbers—for instance, 2.6.10 and 2.6.11—can differ significantly even in core components and in fundamental algorithms.
- When a new kernel release appears, it is potentially unstable and buggy. To address this problem, the kernel developers may release patched versions of any kernel, which are identified by a fourth number in the version numbering scheme - like: `2.6.11.12`


## Basic Operating System Concepts

- Each computer system includes a basic set of programs called the **operating system**.
The most important program in the set is called the **kernel**. It is loaded into RAM when the system boots and contains many critical procedures that are needed for the system to operate.
  - The other programs are less crucial utilities; they can provide a wide variety of interactive experiences for the user—as well as doing all the jobs the user bought the computer for — but the essential shape and capabilities of the system are determined by the kernel. 
- The kernel provides key facilities to everything else on the system and determines many of the characteristics of higher software. Hence, **we often use the term “operating system” as a synonym for “kernel.”**
- The operating system must fulfill two main objectives:
  - :one: **Interact with the hardware components**, servicing all low-level programmable elements included in the hardware platform. 
  - :two: Provide an **execution environment** to the applications that run on the computer system (the so-called **user programs**).
- Some operating systems allow all user programs to directly play with the hardware components (a typical example is MS-DOS). In contrast, **a Unix-like operating system hides all low-level details concerning the physical organization of the computer from applications run by the user.**
- **When a program wants to use a hardware resource, it must issue a request to the operating system. The kernel evaluates the request and, if it chooses to grant the resource, interacts with the proper hardware components on behalf of the user program.**
  - To enforce this mechanism, modern operating systems rely on the availability of specific hardware features that forbid user programs to directly interact with low-level hardware components or to access arbitrary memory locations.
  - In particular, the hardware introduces at least two different execution modes for the CPU: a **non-privileged mode for user programs** and a **privileged mode for the kernel**.
  - Unix calls these **User Mode** and **Kernel Mode**, respectively.


### Multiuser Systems

- A multiuser system is **a computer that is able to concurrently and independently execute several applications belonging to two or more users.**
  - **Concurrently** means that applications can be active at the same time and contend for the various resources such as CPU, memory, hard disks, and so on.
  - **Independently** means that each application can perform its task with no concern for what the applications of the other users are doing.
- Switching from one application to another, of course, slows down each of them and affects the response time seen by the users.
- Many of the complexities of modern operating system kernels are present to minimize the delays enforced on each program and to provide the user with responses that are as fast as possible.
- Multiuser operating systems must include several features:
  - An authentication mechanism for verifying the user’s identity
  - A protection mechanism against buggy user programs that could block other applications running in the system
  - A protection mechanism against malicious user programs that could interfere with or spy on the activity of other users
  - An accounting mechanism that limits the amount of resource units assigned to each user
- To ensure safe protection mechanisms, operating systems must **use the hardware protection associated with the CPU privileged mode.** Otherwise, a user program would be able to directly access the system circuitry and overcome the imposed bounds.
- Unix is a multiuser system that enforces the hardware protection of system resources. 

### Users and Groups

- In a multiuser system, **each user has a private space on the machine**; typically, he owns some quota of the disk space to store files, receives private mail messages, and so on.
- The **operating system must ensure that the private portion of a user space is visible only to its owner.** In particular, it must ensure that no user can exploit a system application for the purpose of violating the private space of another user.
- All users are identified by a unique number called the User ID, or **UID**. Usually only a restricted number of persons are allowed to make use of a computer system.
- When one of these users starts a working session, the system asks for a login name and a password. If the user does not input a valid pair, the system denies access. Because the password is assumed to be secret, the user’s privacy is ensured.
- To selectively share material with other users, **each user is a member of one or more user groups**, which are identified by a unique number called a **user group ID**.
- **Each file is associated with exactly one group**.
  - For example, access can be set so the user owning the file has read and write privileges, the group has read-only privileges, and other users on the system are denied access to the file.
- Any Unix-like operating system has a special user called root or superuser.
  - The system administrator must log in as root to handle user accounts, perform maintenance tasks such as system backups and program upgrades, and so on.
  - The root user can do almost everything, because the operating system does not apply the usual protection mechanisms to her. In particular, the root user can access every file on the system and can manipulate every running user program.

### Processes

- All operating systems use one fundamental abstraction: the process. A process can be defined **either as “an instance of a program in execution”** or as **the “execution context” of a running program**.
- In traditional operating systems, a process executes a single sequence of instructions in an **address space**; the address space is the **set of memory addresses that the process is allowed to reference**.
- Modern operating systems **allow processes with multiple execution flows**—that is, **multiple sequences of instructions executed in the same address space**.
- Multiuser systems must enforce an execution environment in which **several processes can be active concurrently and contend for system resources, mainly the CPU**.
- Systems that allow **concurrent active processes are said to be multiprogramming or multiprocessing**.
- It is important to distinguish **programs** from **processes**;
  - several processes can execute the same program concurrently, while
  - the same process can execute several programs sequentially.
  - On uniprocessor systems, just one process can hold the CPU, and hence just one execution flow can progress at a time.
  - In general, the number of CPUs is always restricted, and therefore only a few processes can progress at once.
- An operating system component called the **scheduler** chooses the process that can progress.
  - Some operating systems allow only 拗音, which means that the **scheduler is invoked only when a process voluntarily relinquishes the CPU**.
  - But **processes of a multiuser system must be preemptable; the operating system tracks how long each process holds the CPU and periodically activates the scheduler.** Unix is a multiprocessing operating system with preemptable processes.
- Even when no user is logged in and no application is running, several system processes monitor the peripheral devices. In particular, **several processes listen at the system terminals waiting for user logins**.
  - When a user inputs a login name, the listening process runs a program that validates the user password.
  - If the user identity is acknowledged, the process creates another process that runs a shell into which commands are entered.
  - When a graphical display is activated, one process runs the window manager, and each window on the display is usually run by a separate process.
  - When a user creates a graphics shell, one process runs the graphics windows and a second process runs the shell into which the user can enter the commands.
  - For each user command, the shell process creates another process that executes the corresponding program. 
- Unix-like operating systems adopt a process/kernel model.
  - Each process **has the illusion that it’s the only process on the machine, and it has exclusive access to the operating system services.**
  - **Whenever a process makes a system call (i.e., a request to the kernel), the hardware changes the privilege mode from User Mode to Kernel Mode, and the process starts the execution of a kernel procedure with a strictly limited purpose.**
  - In this way, the operating system acts within the execution context of the process in order to satisfy its request. **Whenever the request is fully satisfied, the kernel procedure forces the hardware to return to User Mode and the process continues its execution from the instruction following the system call.**

### Kernel Architecture

- As stated before, most Unix kernels are monolithic: each kernel layer is integrated into the whole kernel program and runs in Kernel Mode on behalf of the current process. In contrast, microkernel operating systems demand a very small set of functions from the kernel, generally including a few synchronization primitives, a simple scheduler, and an interprocess communication mechanism. Several system processes that run on top of the microkernel implement other operating system–layer functions, like memory allocators, device drivers, and system call handlers. Although academic research on operating systems is oriented toward microkernels, such operating systems are generally slower than monolithic ones, because the explicit message passing between the different layers of the operating system has a cost. However, microkernel operating systems might have some theoretical advantages over monolithic ones. Microkernels force the system programmers to adopt a modularized approach, because each operating system layer is a relatively independent program that must interact with the other layers through well-defined and clean software interfaces. Moreover, an existing microkernel operating system can be easily ported to other architectures fairly easily, because all hardware-dependent components are generally encapsulated in the microkernel code. Finally, microkernel operating systems tend to make better use of random access memory (RAM) than monolithic ones, because system processes that aren’t implementing needed functionalities might be swapped out or destroyed. To achieve many of the theoretical advantages of microkernels without introducing performance penalties, the Linux kernel offers modules. A module is an object file whose code can be linked to (and unlinked from) the kernel at runtime. The object code usually consists of a set of functions that implements a filesystem, a device driver, or other features at the kernel’s upper layer. The module, unlike the external layers of microkernel operating systems, does not run as a specific process. Instead, it is executed in Kernel Mode on behalf of the current process, like any other statically linked kernel function. The main advantages of using modules include: A modularized approach Because any module can be linked and unlinked at runtime, system programmers must introduce well-defined software interfaces to access the data structures handled by modules. This makes it easy to develop new modules. Platform independence Even if it may rely on some specific hardware features, a module doesn’t depend on a fixed hardware platform. For example, a disk driver module that relies on the SCSI standard works as well on an IBM-compatible PC as it does on Hewlett-Packard’s Alpha. Frugal main memory usage A module can be linked to the running kernel when its functionality is required and unlinked when it is no longer useful; this is quite useful for small embedded systems. No performance penalty Once linked in, the object code of a module is equivalent to the object code of the statically linked kernel. Therefore, no explicit message passing is required when the functions of the module are invoked


## An Overview of the Unix Filesystem

The Unix operating system design is centered on its filesystem, which has several
interesting characteristics. We’ll review the most significant ones, since they will be
mentioned quite often in forthcoming chapters.
Files
A Unix file is an information container structured as a sequence of bytes; the kernel
does not interpret the contents of a file. Many programming libraries implement
higher-level abstractions, such as records structured into fields and record addressing based on keys. However, the programs in these libraries must rely on system calls
offered by the kernel. From the user’s point of view, files are organized in a treestructured namespace, as shown in Figure 1-1
