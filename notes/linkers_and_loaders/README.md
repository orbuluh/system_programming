
# [:book: Linkers and Loaders](https://a.co/d/0WnrSDZ)


Chapter summaries

[Chapter 1, Linking and Loading](ch1.linking_and_loading.md)

- provides a short historical overview of the linking process, and discusses the stages of the linking process. It ends with a short but complete example of a linker run, from input object files to a runnable 'Hello, world' program.

Chapter 2, Architectural Issues, reviews computer architecture from the point of view of linker design. It examines the SPARC, a representative reduced instruction set architecture, the IBM 360/370, an old but still very viable register-memory architecture, and the Intel x86, which is in a category of its own. Important architectural aspects include memory architecture, program addressing architecture, and the layout of address fields in individual instructions.

Chapter 3, Object Files, examines the internal structure of object and executable files. It starts with the very simplest files, MS-DOS .COM files, and goes on to examine progressively more complex files including DOS EXE, Windows COFF and PE (EXE and DLL), Unix a.out and ELF, and Intel/Microsoft OMF.

Chapter 4, Storage allocation, covers the first stage of linking, allocating storage to the segments of the linked program, with examples from real linkers.

Chapter 5, Symbol management, covers symbol binding and resolution, the process in which a symbolic reference in one file to a name in a second file is resolved to a machine address.

Chapter 6, Libraries, covers object code libraries, creation and use, with issues of library structure and performance.

Chapter 7, Relocation, covers address relocation, the process of adjusting the object code in a program to reflect the actual addresses at which it runs. It also covers position independent code (PIC), code created in a way that avoids the need for relocation, and the costs and benefits of doing so.

Chapter 8, Loading and overlays, covers the loading process, getting a program from a file into the computer's memory to run. It also covers tree-structured overlays, a venerable but still effective technique to conserve address space.

Chapter 9, Shared libraries, looks at what's required to share a single copy of a library's code among many different programs. This chapter concentrates on static linked shared libraries.

Chapter 10, Dynamic Linking and Loading, continues the discussion of Chapter 9 to dynamically linked shared libraries. It treats two examples in detail, Windows32 dynamic link libraries (DLLs), and Unix/Linux ELF shared libraries.

Chapter 11, Advanced techniques, looks at a variety of things that sophisticated modern linkers do. It covers new features that C++ requires, including 'name mangling', global constructors and destructors, template expansion, and duplicate code elimination. Other techniques include incremental linking, link-time garbage collection, link time code generation and optimization, load time code generation, and profiling and instrumentation. It concludes with an overview of the Java linking model, which is considerably more semantically complex than any of the other linkers covered.

Chapter 12, References, is an annotated bibliography



## []