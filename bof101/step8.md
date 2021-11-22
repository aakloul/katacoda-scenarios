# Using a disassembler to get the offset

Rather then guessing where the return address should be, we can open the binary with a decompiler or debugger and look at the assembly source code. 

## Definitions

Those are my personal definitions, and that's all you need to know to starts with. When you get more advanced, I will certainly elaborate further on the definitions:

- `disassembling` : the process of translating machine opcode (binaries: 0s and 1s) into assembly instructions
- `caller`: a function that call another function
- `callee`: a function which is called by another function
- `stack frame`: a region in the stack aimed to store and retrieve data for a specific function 

In our vulnerable code, we had the main function calling the say function, and therefore:
- main is the caller
- say is the callee

## gdb can disassenble a binary

Open gdb:

`gdb ./vuln`{{execute}}

Disassemble the vulnerable `say` symbol:

`disas say`{{execute}}: We can see some assembly code. It is written in AT&T syntax (refer to assembly101 course)

We can change it to Intel syntax which is a little bit more friendly: `set disassembly-flavor intel`{{execute}} then disassemble the say function again: `disas say`{{execute}}

We can see the assembly code looks different. This is out of scope of the learning objectives so we won't be covering this, but you can trust me those are just two different manners to represent the exact same machine code.

## Quick code overview

The say function starts with a `prolog` which aims to:
1. save the location of the caller (main function) base pointer: I call it personnally old-ebp or caller-ebp
2. prepare a new stack frame for the callee (say function)

```asm
push   ebp	; save caller-ebp (4 bytes) in the stack
mov    ebp,esp  ; a new stackframe is created, ebp becomes the callee-ebp
```

Right after the prolog, we can see two interesting instructions:

a CPU register is pushed in the stack (it's size is 32 bits or 4 bytes)

```asm
push   ebx
```

Then our buffer is allocated:

```asm
sub    esp,0x804
```

Let's print how much space is allocated for our buffer: 

`print 0x804`{{execute}}

We notice the compiler has assigned a slightly bigger size 2052 (4 more bytes) then expected.

Let's skip everything and jump to the three last instructions, it is called an `epilog`. The purpose of the epilog is to evict the callee stackframe and restore the caller stackframe:

```asm
mov    ebx,DWORD PTR [ebp-0x4]	; Restore the caller-ebp
leave  
ret				; Restore the Instruction pointer to resume with caller next instruction
```

## How does a stack frame looks like?

Few rules you need to keep in mind (bear with me, we won't explain now - this is more the topic for an assembly101 class):
- every callee function starts with a prolog (except the main function)
- every callee function ends with an epilog  (except the main function)

The creation of a new stack frame occurs everytime a callee is called, and obey a certain sequence:
1. arguments are pushed first in the new stack
2. the value of  the instruction pointer + 4 bytes (EIP+4) is stored as the `return address` (RIP)
  - it will be used to resume to the caller next instructions after the callee returns with the `ret` instruction
3. the prolog save the caller stackframe base pointer: I call it caller-ebp or old-ebp 
4. the prolog initiate a new stack frame for the callee (by assigning to ebp the address of the top of the stack)
5. Last but not least, local variables are pushed in the stack

## Exercise

1. Take a pencil, and try to draw the say function stackframe right after the prolog is being executed (not including above step 5.)

Once you have finished, look at the solution and compare whether this is what you were expecting. Have a second reading of the stakframe creation rules if needed.

The solution is: `clear && cat solution1.md`{{execute}}

Have you noticed that our stack is groing "going down"? First bytes pushed in the stack are higher in the memory then bytes pushed last ...

Are you able to tell which number of bytes should replace every `?` from the solution? Try to figure out before moving to the next exercise instruction.

2. How about you complete your drawing  to represent the stack frame just after the local variable is allocated? 

The solution is: `clear && cat solution2.md`{{execute}}

The stack keeps growing down ... 

3. Try to replace the question marks `?` in the solution?

4. Can you see the size of the Offset?

The solution is: `clear && cat solution3.md`{{execute}}
