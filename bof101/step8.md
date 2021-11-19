# Using gdb or radare2 to get the offset

Rather then guessing where should be the return address, we can open the binary with a decompiler or debugger and look at the assembly source code.

## gdb

Open gdb:

`gdb ./vuln`{{execute}}

Disassemble the vulnerable `say` symbol:

`disas say`{{execute}}: We can see the assembly code with AT&T syntax

We can change to Intel syntax with:

`set disassembly-flavor intel`{{execute}} then `disas say`{{execute}} again 

The function starts with a prolog which aims to prepare a new stack frame:

```
   0x08049295 <+4>:     push   ebp
   0x08049296 <+5>:     mov    ebp,esp
```

Right after the prolog, we can see the buffer location:

```
   0x08049299 <+8>:     sub    esp,0x804
```

Let's print the offset size and we notice the compiler has assigned a slightly bigger size 2052 (4 more bytes) then expected.

`print 0x804`{{execute}}

The function ends with an epilog, which aims to restore the previous stack frame:

```
   0x080492d2 <+65>:    mov    ebx,DWORD PTR [ebp-0x4]
   0x080492d5 <+68>:    leave  
   0x080492d6 <+69>:    ret
```

epilog and prolog always starts and ends called functions:
- the prolog save the stack frame of the caller function and create a new stack frame for the callee
- the epilog restore the stack frame of the callee



