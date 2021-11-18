# Dynamic Fuzzing

`cat say.c`{{execute}}

Let's look at the main function:
- this programme takes exactly one argument: `argc > 1`
- the first argument is passed to the say function: `say(argv[1])`
- if we have less then one argument then the prompt will show: "This program takes 1 argument."

Let's have a look on the say function:
- the function argument is a pointer named `input`; it points to a table of `char` that contains the first argument of the programme
- we initialise a buffer called `buf` with a size 16 char. One char is of size 8 bits (1 bytes).
- The strcpy command will copy our programme imput into the buffer
- Then we print the content of buffer in the console

`./say "hello"`{{execute}}

`./say "hello how are you"`{{execute}}

`./say "hello how are you my friends"`{{execute}}

We have the message `segmentation fault`. This is because we have written more character then the buffer can contain. Do you remember the size of the buffer is 16 bytes? but look at how many characters we have copied in the buffer:

`echo "hello how are you my friends" | wc`{{execute}}

When you type `ls -l`{{execute}} do you see a `core` file? if Yes, it contains a lot of debugging information on what happen, with an instant snapshot of CPU registries, memory, heap and execution stack at the time of the crash. We are not gonna explore the `core dump` today, but will keep it for later.

If you can't see the `core dump`, no panic, it is certainly because of your user limits. Check user limits with `ulimit -a`{{execute}}. If the core file size is zero, no core dump can be generated, but you can change the value to unlimited size with `ulimit -c unlimited`{{execute}}; then check again `ulimit -a`{{execute}} and re-execute the programme with a large argument: `./say AAAAAAAAAAAAAAAAAAAAAAAA`{{execute}}.

Got a core dump file? Great ...

When a segmentation fault occures, it has to be logged by the system. Extremely valuable information can be obtained without the need of a core dump to proceed further in exploitation. The simplest way is the output the two last rows of the `dmesg` command:

`dmesg | tail -2`{{execute}}

It says `segfault at 41414141` and instruction pointer: `ip 0000000041414141`, will explain later what is the instruction pointer. 

41 is the hexadecimal representation of the ASCII character 'A'. We normally represent it `0x41` which means `41 in base 16`. In C or python language, we write it `\x41`.

# Core Dump analysis with gdb

gdb is the GNU Debugger, swiss army knife to explore core dump and debug step-by-step a program in command-line. Command-line may look intimidating but it is actually quite straightforward and often there is no graphical interface on Unix server. Graphical equivalent are `IDA Pro` and `ghidra` that works on both Linux and Windows. Another command-line alternative is `radare2`.

To load a program with its core dump, run 'gdb /path/to/binary /path/to/core`:

`gdb ./say core`{{execute}}

We immediately see the program was terminated because of a segmentation fault at 41414141 and we can print the instruction pointer or any other registry value:

`print $eip`{{execute}}

We can also print 20 words (80 bytes) before the stack pointer to see what the stack frame looked like at the time of the seg fault. We can see all the 'A' character represented by the sequence of __41__:

`x/-20x $esp`{{execute}}





