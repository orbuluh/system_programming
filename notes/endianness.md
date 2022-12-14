# Endianness

> Highlighted from [wiki](https://en.wikipedia.org/wiki/Endianness)

## (Fun fact) Naming source

The adjective endian comes from the 1726 novel  ... characters ... are divided into those breaking the shell of a boiled egg from the big end (Big-Endians) or from the little end (Little-Endians)

## Background

- Computers store information in various-sized **groups of binary bits**. Each group is assigned a number, called its **address**, that the computer uses to access that data.
- On most modern computers, the smallest data group with an address is eight bits long and is called a **byte**.
- Larger groups comprise two or more bytes, for example, a 32-bit word contains four bytes. There are two possible ways **a computer could number the individual bytes in a larger group, starting at either end.**
- Endianness is primarily expressed as big-endian (BE) or little-endian (LE).
  - A big-endian system stores the **most significant byte of a word at the smallest** memory address and the least significant byte at the largest.
  - A little-endian system, in contrast, stores the **least-significant byte at the smallest address.**


```txt
    32-bit integer: 0A0B0C0D  broken to 4 bytes:
    - 0x0A (most-significant byte)
    - 0x0B
    - 0x0C
    - 0x0D (least-significant byte)

    bytes are stored in four sequential byte locations in memory
    starting with the memory location with address a.
    The difference between big and little endian is the order of the four bytes
    of the integer being stored.

Memory  in ...   BE       SE
    a:         0x0A     0x0D
  a+1:         0x0B     0x0C
  a+2:         0x0C     0x0B
  a+3:         0x0D     0x0A
```

- When memory bytes are printed sequentially from left to right (e.g. in a **hex dump**),  when visualized, little-endian representation can be counter-intuitive.

```txt
   '   J  o  h  n  '
 hex  4A 6F 68 6E

Memory  in ...   BE         SE
    a:         0x4A (J)   0x6E (n)
  a+1:         0x6F (o)   0x68 (h)
  a+2:         0x68 (h)   0x6F (o)
  a+3:         0x6E (n)   0x4A (J)
```

## Context of usage

- Internally, any given computer will work equally well regardless of what endianness it uses since its hardware will consistently use the same endianness to both store and load its data. For this reason, programmers and computer users normally ignore the endianness of the computer they are working with.
- However, endianness can become an issue **when moving data external to the computer – as when transmitting data between different computers, or a programmer investigating internal computer bytes of data from a memory dump – and the endianness used differs from expectation.** In these cases, the endianness of the data must be understood and accounted for.

So the main 2 context of usage:

- Endianness is the order or sequence of bytes of a word of digital data in **computer memory.**
- Endianness may also be used to describe the order in which the **bits are transmitted over a communication channel**, e.g., big-endian in a communications channel transmits the most significant bits first

Both types of endianness are in widespread use in digital electronic engineering.

- **Big-endianness** is the dominant ordering in **networking protocols**, such as in the internet protocol suite, where it is referred to as network order, transmitting the most significant byte first.
- Conversely, **little-endianness** is the dominant ordering for **processor architectures** (x86, most ARM implementations, base RISC-V implementations) and their associated memory.
- File formats can use either ordering; some formats use a mixture of both or contain an indicator of which ordering is used throughout the file.
- The initial choice of endianness of a new design is often arbitrary, but later technology revisions and updates perpetuate the existing endianness to maintain backward compatibility.

## Side notes

- The styles of little- and big-endian may also be used more generally to **characterize the ordering of any representation**, e.g. the digits in a numeral system or the sections of a date
  - Numbers in positional notation are generally written with their digits in left-to-right big-endian order, even in right-to-left scripts.
  - Similarly, programming languages use big-endian digit ordering for numeric literals.
- Bi-endianness is a feature supported by numerous computer architectures that feature switchable endianness in data fetches and stores or for instruction fetches.