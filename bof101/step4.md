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

`echo "hello how are you my friends" | wc -c`{{execute}}

When a segmentation fault occures, it has to be logged by the system. The simplest way to get valuable kernel logs is the output the two last rows of the `dmesg` command:

`dmesg | tail -2`{{execute}}

It says `segfault at 41414141` and instruction pointer: `ip 0000000041414141`, will explain later what is the instruction pointer. 

41 is the hexadecimal representation of the ASCII character 'A'. We normally represent it `0x41` which means `41 in base 16`. In C or python language, we write it `\x41`.

