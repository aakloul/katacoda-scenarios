# Core Dump post-mortem analysis with gdb

When you type `ls -l`{{execute}} do you see a `core` file? 

If you can't see the `core dump`, no panic, it is certainly because of your user limits. Check user limits with `ulimit -a`{{execute}}. If the core file size is zero, no core dump can be generated, but you can change the value to unlimited size with `ulimit -c unlimited`{{execute}}; then check again `ulimit -a`{{execute}} and re-execute the programme with a large argument: `./say AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`{{execute}}.

Got a core dump file? Great ... I told you, not to panic :)

The core dump contains a lot of debugging information on what happened, with an instant photography snapshot of CPU registries, memory, heap and execution stack at the time of the crash. We are not gonna explore the `core dump` in detail today as it is the topic for another training. However we can quicky demonstrate its value to perform post-mortem analysis of a crash.

We will use gdb, the GNU Debugger, which is the standard, a real swiss army knife, to explore core dump and debug step-by-step a program in command-line. Command-line may look intimidating but we often don't have the choice, especially when there is no graphical interface on Unix server. My personal view is that such tools are extremly powerful and very straightforward when you used it often, some kind of brain gymnastic. But when you are new to it, it can be a pain, so I recommend to use a 'Cheat sheet' or take a separate gdb101 course. Graphical equivalent exists such as `IDA Pro` and `ghidra` that works on both Linux and Windows. Another powerful command-line alternative is `radare2`.

To load a program with its core dump, run 'gdb /path/to/binary /path/to/core`:

`gdb ./say core`{{execute}}

We immediately see the program was terminated because of a segmentation fault at 41414141 and we can print the instruction pointer or any other registry value:

`print $eip`{{execute}} : instruction pointer

`p $esp`{{execute}} : stack pointer

We can also print 20 words (80 bytes) before the stack pointer to see what the stack frame looked like at the time of the segfault. 

`x/-20x $esp`{{execute}}

We can see all the 'A' character represented by the sequence of __41__:

`quit`{{execute}}

We don't need core dump for the rest of this scenario, so we can disable with `ulimit -c 0`{{execute}}
