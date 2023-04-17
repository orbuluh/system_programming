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


- In operating systems, the **kernel** is the core component that manages system resources and provides services to other programs.
- A monolithic kernel is a type of kernel architecture in which **all kernel services run in the same address space, sharing the same memory and hardware resources.**
  - This means that **all kernel code and device drivers are loaded and executed in a single, unified kernel space.**
- In contrast, a microkernel architecture separates kernel services into individual, standalone processes, **each with its own address space, and uses inter-process communication mechanisms to provide services to other processes.**
  - microkernel operating systems demand a very small set of functions from the kernel, generally including a few synchronization primitives, a simple scheduler, and an interprocess communication mechanism. Several system processes that run on top of the microkernel implement other operating system–layer functions, like memory allocators, device drivers, and system call handlers.
  - Although academic research on operating systems is oriented toward microkernels, such operating systems are **generally slower than monolithic ones**, because the explicit message passing between the different layers of the operating system has a cost.
  - However, microkernel operating systems might have some **theoretical advantages** over monolithic ones.
    - Microkernels **force the system programmers to adopt a modularized approach**, because each operating system layer is a relatively independent program that must interact with the other layers through well-defined and clean software interfaces.
    - Moreover, an existing microkernel operating system can be **easily ported to other architectures fairly easily, because all hardware-dependent components are generally encapsulated in the microkernel code.**
    - Finally, microkernel operating systems tend to make better use of random access memory (RAM) than monolithic ones, because **system processes that aren’t implementing needed functionalities might be swapped out or destroyed.**

- As stated before, most Unix kernels are monolithic:
  - **each kernel layer is integrated into the whole kernel program and runs in Kernel Mode on behalf of the current process.**

## Linux modules

- To achieve many of the theoretical advantages of microkernels without introducing performance penalties, **the Linux kernel offers modules.**
- A **module** is an object file whose code **can be linked to (and unlinked from) the kernel at runtime.**
- The object code usually consists of a set of functions that implements a filesystem, a device driver, or other features at **the kernel’s upper layer**.
- The module, unlike the external layers of microkernel operating systems, does not run as a specific process. Instead, **it is executed in Kernel Mode on behalf of the current process, like any other statically linked kernel function.**
- The main advantages of using modules include:
  - **A modularized approach**:
    - Because any module can be linked and unlinked at runtime, **system programmers must introduce well-defined software interfaces to access the data structures handled by modules.** This makes it easy to develop new modules.
  - **Platform independence**:
    - Even if it may rely on some specific hardware features, **a module doesn’t depend on a fixed hardware platform.**
    - For example, a disk driver module that relies on the SCSI standard works as well on an IBM-compatible PC as it does on Hewlett-Packard’s Alpha.
  - **Frugal main memory usage**
    - **A module can be linked to the running kernel when its functionality is required and unlinked when it is no longer useful; this is quite useful for small embedded systems.**
  - **No performance penalty**
    - **Once linked in, the object code of a module is equivalent to the object code of the statically linked kernel.** Therefore, no explicit message passing is required when the functions of the module are invoked


## An Overview of the Unix Filesystem

The Unix operating system design is centered on its filesystem.

### Files

- **A Unix file is an information container structured as a sequence of bytes**;
- the **kernel does not interpret the contents of a file**.
- Many **programming  libraries implement higher-level abstractions**, such as records structured into fields and record addressing based on keys.
- However, the **programs in these libraries must rely on system calls offered by the kernel.**


- From the user’s point of view, files are organized in a tree-structured namespace.
  - All the nodes of the tree, except the leaves, denote directory names.
- A directory node contains information about the files and directories just beneath it.
- A file or directory name consists of a sequence of arbitrary ASCII characters, with the exception of `/` and of the null character `\0`.
- Most filesystems place a limit on the length of a filename, typically no more than 255 characters.
- The directory corresponding to the root of the tree is called the root directory. By convention, its name is a slash (`/`).
- Names must be different within the same directory, but the same name may be used in different directories.
- **Unix associates a current working directory with each process**; it **belongs to the process execution context**, and **it identifies the directory currently used by the process.**
- To identify a specific file, the process uses a pathname, which consists of slashes alternating with a sequence of directory names that lead to the file.
- If the first item in the pathname is a slash, the pathname is said to be absolute, because its starting point is the root directory. Otherwise, if the first item is a directory name or filename, the pathname is said to be relative, because its starting point is the process’s current directory.
- While specifying filenames, the notations “.” and “..” are also used. They denote the current working directory and its parent directory, respectively.
- If the current working directory is the root directory, “.” and “..” coincide.

## Hard and Soft Links

- A filename included in a directory is called a **file hard link**, or more simply, a **link**.
- The same file may have several links included in the same directory or in different ones, so it may have several filenames.

- :man_technologist: The Unix command: `$ ln p1 p2` is used to create a new hard link that has the pathname `p2` for a file identified by the pathname `p1`.

- Hard links have two limitations:
  - **It is not possible to create hard links for directories.** Doing so might transform the directory tree into a graph with cycles, thus making it impossible to locate a file according to its name.
  - **Links can be created only among files included in the same filesystem.**
  - This is a serious limitation, because modern Unix systems may include several filesystems located on different disks and/or partitions, and users may be unaware of the physical divisions between them.
- To overcome these limitations, soft links (also called symbolic links) were introduced a long time ago.
- Symbolic links are short files that contain an arbitrary pathname of another file.
- The pathname may refer to **any file or directory located in any filesystem**; it may even refer to a nonexistent file.
- :man_technologist: The Unix command: `$ ln -s p1 p2` creates a new soft link with pathname p2 that refers to pathname p1.
  - When this command is executed, the filesystem **extracts the directory part of `p2` and creates a new entry in that directory of type symbolic link, with the name indicated by `p2`.**
  - This new file contains the name indicated by pathname `p1`.
  - This way, each reference to `p2` can be translated automatically into a reference to `p1`.

## File Types

- Unix files may have one of the following types:
  - Regular file
  - Directory
  - Symbolic link
  - Block-oriented device file
  - Character-oriented device file
  - Pipe and named pipe (also called FIFO)
  - Socket

- The first three file types are constituents of any Unix filesystem. Their implementation is described in detail in Chapter 18.
- Device files are related **both to I/O devices, and to device drivers integrated into the kernel.**
  - For example, when a program accesses a device file, it acts directly on the I/O device associated with that file (see Chapter 13).
- Pipes and sockets are special files used for interprocess communication (see the section “Synchronization and Critical Regions” later in this chapter; also see Chapter 19).
- **File Descriptor** and **Inode** Unix makes a clear distinction between the **contents of a file and the information about a file**.
- With the exception of device files and files of special filesystems, each file consists of a sequence of bytes.
- The file does not include any control information, such as its length or an end-of-file (EOF) delimiter. **All information needed by the filesystem to handle a file is included in a data structure** called an **inode**.
- **Each file has its own inode**, which the filesystem uses to identify the file.
- While filesystems and the kernel functions handling them can vary widely from one Unix system to another, they must always provide at least the following attributes, which are specified in the POSIX standard:
  - File type (see the previous section)
  - Number of hard links associated with the file
  - File length in bytes
  - Device ID (i.e., an identifier of the device containing the file)
  - Inode number that identifies the file within the filesystem
  - UID of the file owner
  - User group ID of the file
  - Several timestamps that specify the inode status change time, the last access time, and the last modify time
  - Access rights and file mode (see the next section)

## Access Rights and File Mode

- The potential users of a file fall into three classes:
  - The user who is the owner of the file
  - The users who belong to the same group as the file, not including the owner
  - All remaining users (others) There are three types of access rights—read, write, and execute—for each of these three classes.
- Thus, the set of access rights associated with a file consists of nine different binary flags. Three additional flags, called `suid` (**Set User ID**), **sgid** (**Set Group ID**), and sticky, define the file mode.
- These flags have the following meanings when applied to executable files:
  - `suid`: A process executing a file **normally keeps the User ID (UID) of the process owner.** However, if the executable file has the `suid` flag set, the process gets the UID of the file owner.
  - `sgid`: A process executing a file keeps the user group ID of the process group. However, if the executable file has the `sgid` flag set, the process gets the user group ID of the file.
  - `sticky`: An executable file with the sticky flag set corresponds to a request to the kernel to **keep the program in memory after its execution terminates.**
    - When a file is created by a process, its owner ID is the UID of the process.
    - Its owner user group ID can be either the process group ID of the creator process or the user group ID of the parent directory, depending on the value of the `sgid` flag of the parent directory.

## File-Handling System Calls

- When a user accesses the contents of either a regular file or a directory, he actually accesses some data stored in a hardware block device. In this sense, a filesystem is a user-level view of the physical organization of a hard disk partition.
- Because a process in User Mode cannot directly interact with the low-level hardware components, **each actual file operation must be performed in Kernel Mode**. Therefore, the Unix operating system defines several system calls related to file handling.
- All Unix kernels devote great attention to the efficient handling of hardware block devices to achieve good overall system performance. In the chapters that follow, we will describe topics related to file handling in Linux and specifically how the kernel reacts to file-related system calls. To understand those descriptions, you will need to know how the main file-handling system calls are used; these are described in the next section.

### Opening a file

- Processes can access only “opened” files. To open a file, the process invokes the system call: `fd = open(path, flag, mode)`
  - `path` Denotes the pathname (relative or absolute) of the file to be opened.
  - `flag` Specifies how the file must be opened (e.g., read, write, read/write, append). It also can specify whether a nonexisting file should be created.
  - `mode` Specifies the access rights of a newly created file.
  - This system call creates an “open file” object and returns an identifier called a **file descriptor**.
- An open file object contains:
  - Some file-handling data structures, such as a set of flags specifying how the file has been opened,
  - an offset field that denotes the current position in the file from which the next operation will take place (the so-called **file pointer**), and so on.
  - Some pointers to kernel functions that the process can invoke.
- The set of permitted functions depends on the value of the `flag` parameter.
- We discuss open file objects in detail in Chapter 12. Let’s limit ourselves here to describing some general properties specified by the POSIX semantics.
  - A **file descriptor** represents an **interaction between a process and an opened file**, while
  - an **open file object** contains data related to that interaction.
  - The **same open file object may be identified by several file descriptors in the same process**.
- **Several processes may concurrently open the same file.**
  - In this case, the filesystem assigns a separate file descriptor to each file, along with a separate open file object.
  - When this occurs, the Unix filesystem does not provide any kind of synchronization among the I/O operations issued by the processes on the same file. However, several system calls such as `flock()` are available to allow processes to synchronize themselves on the entire file or on portions of it (see Chapter 12).
- To create a new file, the process also may invoke the `creat()` system call, which is handled by the kernel exactly like `open( )`.

### Accessing an opened file

- Regular Unix files can be addressed either sequentially or randomly, while device files and named pipes are usually accessed sequentially. In both kinds of access, the kernel stores the file pointer in the open file object—that is, the **current position at which the next read or write operation will take place**.
- Sequential access is implicitly assumed: the `read()` and `write()` system calls always refer to the position of the current file pointer.
- To modify the value, a program must explicitly invoke the `lseek()` system call.
- When a file is opened, the kernel sets the file pointer to the position of the first byte in the file (offset 0) The `lseek()` system call requires the following parameters: `newoffset = lseek(fd, offset, whence);`
  - `fd` Indicates the file descriptor of the opened file
  - `offset` Specifies a signed integer value that will be used for computing the new position of the file pointer
  - `whence` Specifies whether the new position should be computed by adding the offset value to the number 0 (offset from the beginning of the file), the current file pointer, or the position of the last byte (offset from the end of the file)
- The `read()` system call requires the following parameters: `nread = read(fd, buf, count);`
  - `fd` Indicates the file descriptor of the opened file
  - `buf` Specifies the address of the buffer in the process’s address space to which the data will be transferred
  - `count` Denotes the number of bytes to read.
  - When handling such a system call, the kernel attempts to read `count` bytes from the file having the file descriptor `fd`, starting from the current value of the opened file’s `offset` field.
- In some cases—end-of-file, empty pipe, and so on—the kernel does not succeed in reading all `count` bytes.
  - The returned `nread` value specifies the number of bytes effectively read.
  - The file pointer also is updated by adding `nread` to its previous value.
- The `write()` parameters are similar.

### Closing a file

- When a process does not need to access the contents of a file anymore, it can invoke the system call: `res = close(fd);`
  - which releases the open file object corresponding to the file descriptor `fd`.
- When a process terminates, the kernel closes all its remaining opened files.

### Renaming and deleting a file

- To rename or delete a file, a process does not need to open it. Indeed, such operations do not act on the contents of the affected file, but rather on the contents of **one or more directories**.
- For example, the system call: `res = rename(oldpath, newpath);` changes the name of a file link, while the system call: `res = unlink(pathname);` decreases the file link count and removes the corresponding directory entry. The file is deleted only when the link count assumes the value 0.


## An Overview of Unix Kernels

- Unix **kernels provide an execution environment** in which applications may run. Therefore, the **kernel must implement a set of services and corresponding interfaces.**
- Applications use those interfaces and **do not usually interact directly with hardware resources.**

## The Process/Kernel Model

- As already mentioned, a CPU can run in either User Mode or Kernel Mode. Actually, some CPUs can have more than two execution states. For instance, the 80 × 86 microprocessors have four different execution states.
- But all **standard** Unix kernels use **only** Kernel Mode and User Mode.
- When a program is executed in User Mode, it cannot directly access the kernel data structures or the kernel programs.
- When an application executes in Kernel Mode, however, these restrictions no longer apply.
- Each **CPU model provides special instructions** to switch from User Mode to Kernel Mode and vice versa.
- A program usually executes in User Mode and switches to Kernel Mode only when requesting a service provided by the kernel. When the kernel has satisfied the program’s request, it puts the program back in User Mode.
- Processes are dynamic entities that usually have a limited life span within the system.
- The task of creating, eliminating, and synchronizing the existing processes is delegated to a group of routines in the kernel.
- **The kernel itself is not a process but a process manager.**
- The process/kernel model assumes that processes that require a kernel service use specific programming constructs called **system calls**.
  - Each system call sets up the group of parameters that identifies the process request and then **executes the hardware-dependent CPU instruction to switch from User Mode to Kernel Mode.**

- Besides user processes, Unix systems include a few privileged processes called **kernel threads** with the following characteristics:
  - They run in Kernel Mode in the kernel address space.
  - They do not interact with users, and thus do not require terminal devices.
  - They are usually created during system startup and remain alive until the system is shut down.
- On a uniprocessor system, only one process is running at a time, and it may run either in User or in Kernel Mode.
  - If it runs in Kernel Mode, the processor is executing some kernel routine.

![](imgs/fig1.2.JPG)

- Examples of transitions between User and Kernel Mode.
  - Process 1 in User Mode issues a system call, after which the process switches to Kernel Mode, and the system call is serviced.
  - Process 1 then resumes execution in User Mode until a timer interrupt occurs, and the scheduler is activated in Kernel Mode.
  - A process switch takes place, and Process 2 starts its execution in User Mode until a hardware device raises an interrupt.
  - As a consequence of the interrupt, Process 2 switches to Kernel Mode and services the interrupt.


- Unix kernels do much more than handle system calls; in fact, kernel routines can be activated in several ways:

- A process invokes a **system call**.
- The CPU executing the process **signals an exception**, which is an unusual condition such as an invalid instruction. The kernel handles the exception on behalf of the process that caused it.
- A **peripheral device** issues an interrupt signal to the CPU to notify it of an event such as a request for attention, a status change, or the completion of an I/O operation.
  - Each interrupt signal is dealt by a kernel program called an **interrupt handler**.
  - Because peripheral devices operate asynchronously with respect to the CPU, interrupts occur at unpredictable times.
- A kernel thread is executed.
  - Because it runs in Kernel Mode, the corresponding program must be considered part of the kernel.

## Process Implementation
