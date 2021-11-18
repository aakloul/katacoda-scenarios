# Build your first assembly program

We can verify our installation is operational by compiling and executing a helloworld assembly file.

`cd helloworld && cat helloworld.s`{{execute}}

To compile this assembly file you can simply execute the below:

- `-o helloworld` is the compiled executable
- `-m32` is to instruct the compiler we want a 32 bits executable, instead of default 64 bits

`gcc -m32 -o helloworld helloworld.s`{{execute}}

If the above command show no error output, you should have a newly created executable `./helloworld` that will output `Hello, World` upon execution.

`./helloworld`{{execute}}

It is very common to use `nasm` to assemble code. The `hello.asm` is a good example, and mostly differs from `helloworld.s` by its syntax:

- the `asm` file use Intel flavour syntax
- the `s` file use AT&T flavour

`cat hello.asm`{{execute}}

gcc may not be able to assemble, in this case we need to compile with `nasm` and link objects with `ld` commands:

Compile:

`nasm -f elf hello.asm -o hello.o`{{execute}}

Link:

`ld -m elf_i386 hello.o -o hello`{{execute}}

Run:

`./hello`{{execute}}

We just created a 32 bits executable from assembly code. What if we want 64 bits instead? Well you just repeat the "Compile,Link,Run" but change the compilation output format with `-f elf64` with:

`nasm -f elf64 hello.asm -o hello64.o`{{execute}}

`ld hello64.o -o hello64`{{execute}}

`./hello64`{{execute}}

# Build your first C program

Have a first look at this very simple C program. Have you spotted a vulnerability? if No, then no worries will come to that shortly:

`cat say.c`{{execute}}

Compile:

`gcc -m32 -o say say.c`{{execute}}

Run:

`./say "Hello friends!"`{{execute}}

The gcc compiler comes with a ton of configurable flags and options that may heavily change the built binaries. We have already seen the `-m32` flag, just try without it, and you'll have a much larger 64 bits binary.

`gcc -o say64 say.c`{{execute}}

