# Dynamic Fuzzing

## Source code walk-through

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

## Dynamic Fuzzing

`./say "hello"`{{execute}}

`./say "hello how are you"`{{execute}}

`./say "hello how are you super duper friend"`{{execute}}

We have the message `segmentation fault`. This is because we have written more character then the buffer can contain. Do you remember the size of the buffer is 16 bytes? but look at how many characters we have copied in the buffer:

`echo "hello how are you my super duper friend" | wc -c`{{execute}}: This argument has 37 characters

When a segmentation fault occures, it has to be logged by the system. The simplest way to get valuable kernel logs is the output the two last rows of the `dmesg` command:

`dmesg | tail -2`{{execute}}

It says `segfault at 72662072` and instruction pointer: `ip 0000000072662072`, will explain later what is the instruction pointer. 

What happened? Remember the size of the buffer is 16 bytes, but we have copied in the buffer 37 bytes! It is much more then what the buffer can contain, and therefore the excedent bytes are being written outside of the buffer. We call it an overflow ... and because it's a buffer overflowing, we call it buffer overflow.

## Exercise

1. Let's execute again our buffer overflow with a long sequence of 'A' characters (at least 32)
2. What is the value of the instruction pointer?

## ASCII tables

`apt install -y ascii`{{execute}}: ascii is a very useful table that shows ASCII characters and their decimal or hexadecimal representation

On the previous exercise, you should have identified that the instruction pointer is a sequence of 41 ... what's that 41 and where does it comes from?

Look at the `ascii`{{execute}} table for the value 41 in the hex column, or just type `ascii 41`{{execute}}: What you learn is that 41 is the hexadecimal representation of the ASCII character 'A'. We normally represent it `0x41` which means `41 in base 16`. In C or python language, we write it `\x41`.

Remember the value of the `ip` when we have executed: `./say "hello how are you super duper friend"` ? The value of the ip was 72662072 which represents i4 hexadecimal number: \x72, \x66, \x20 and \x72. The 4 corresponding ASCII characters are:

| | | |
| --- | --- | --- |
| 72 | 66 | 20 | 72 |
| r | f | space | r | 

If we reverse the order of those four ASCII characters, we find the sequence `r fr` which has a match in our argument: "hello how are you super dupe`r fr`iend:
- Let's count how many character before our sequence: `echo "hello how are you super dupe" | wc -c`{{execute}}, will call this number OFFSET
- The 4 next characters location ("r fr"), will call it RIP
- Anything after (iend) can be discarded and ignore

## Exercise

1. Modify the argument with a text of your choice (at least 32 characters)
2. Execute the buffer overflow
3. Identify the new value of the instruction pointer
4. Use the ascii table to identify the 4 characters in RIP
5. Has the OFFSET changed?
