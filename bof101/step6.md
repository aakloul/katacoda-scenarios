# Signal Handlers and symbols

Let's change directory and look at `vuln.c` which is a sligthly modified version of our previous C programme:

`cd ../buffer-overflow-0 && cat vuln.c`{{execute}}

Our objective is to exploit the buffer overflow vulnerability to print a secret password stored in a secret function which is never called, and therefore in appearance unreachable.

## Signal Handler

The differences with the previous programme are:
- usage of the `signal.h` header
- new function sigsegv_handler
- new function secretHiddenFunction, which is never called, so not accessible
- call of the signal function from main to intercept SIGSEGV interruption and execute  sigsegv_handler);  

Upon a Segmentation Fault, the sigsegv_handler will be executed:

Compile and execute:

`gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o vuln vuln.c`{{execute}}

`./vuln AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`{{execute}}

Because of the signal interruption being intercepted, we don't have a core dump and we don't have a dmesg log. As we have the source code, it is easy to momentarily disable the signal interception to visualize the instruction pointer (EIP cpu register) at the time of the segmentation fault. We will use a command-line editor called vim (Feel free to use `nano` if you are not comfortable with `vim`). If you are stuck in vim, you can quit at any time by typing `<ESC>qa!`.

1. open the source file in vim: `vim ./vuln.c`{{execute}}
2. show the line numbers by typing `<ESC>:set nu<ENTER>`
3. go to line 27 by typing `27gg`
4. change to INSERT mode with `I`
5. comment the line by typing `//` at the beginning of the line
6. save and quit with: `<ESC>ZZ`

Recompile and execute, but this time, instead of a large sequence of 'A' I am using a slightly modified version of the payload, to help me identify which region of the payload is overwriting the instruction pointer:
- 16 subsequent characters 'A'
- followed with several group of 4 character 'B', then 'C', then ..., then 'I'

`gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o vuln vuln.c`{{execute}}

`./vuln AAAAAAAAAAAAAAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIII`{{execute}}

Why all multiple of 4 characters? (Try to answer before looking at the response at the very bottom of this page)

The output of `dmesg | tail -2`{{execute}} shows that the ip is overwritten with 45454545, `45` being the hexadecimal representation of the character 'E', we know exactly which portion of our payload need to be modified.

## Symbols

We want to execute the `secretHiddenFunction`, so what we need is to have the instruction pointer points to the beginning of this function. That's where comes the symbols table which tie objects addresses with labels. Can you guess what is the default label for our secretHiddenFunction?

We can use `readelf -s ./vuln | grep secretHiddenFunction`{{execute}} or `objdump -t ./vuln | grep secretHiddenFunction`{{execute}} to identify the corresponding address 080492d7 (hexadecimal number). I will explain later what is the endianess, so for now just consider that because of endianess, we have to represent address bytes in reverse order and therefore the 32 bits address representing the secretHiddenFunction should be written in C or in python: `\xd7\x92\x04\x08`.

Our shell prompt does not permit to type non alphanumeric characters such as \xd7, \x92, \x04 and \x08

That's the moment to introduce python (or perl or ruby)

ANSWERS:

We are using multiple of 4 characters Because we are in 32 bits architecture and one character is one Byte which is exactly 8 bits size. Therefore I need four of them to make it a 32 bits address.
