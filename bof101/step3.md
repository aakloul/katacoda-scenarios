# Static Binary Analysis

In binary exploitation or reverse engineering, a standard practice is to starts with static exploration of binaries. The `file` command is an excellent start:

`file ./say`{{execute}}

In a nutshell we learn:

- the binary is `ELF` format (linux binary)
- architecture is 32 bits
- it is dynamically linked (which means it can leverage OS shared functions)
- it is not stripped (which means debugging data is embedded in the executable)

How about we do the same for the 64 bit version? Can you spot the difference?

`file ./say64`{{execute}}

You can collect much more information with additional tools such as `objdump` or `readelf`, try it and don't get overwhelmed by output, we will explain in details in another course.

To get the list of symbols, try the below. Don't worry if you don't know yet what are symbols. Will come to that soon:

`objdump -t ./say`{{execute}}
or
`readelf -s ./say`{{execute}}

Remember when I said that the Gnu compiler (gcc) comes with tons of configurable options? Well, by default many security features are activated by default and make the exploitation of buffer overflow more difficult (not impossible). We don't necessarily need to run a binary to figure out which protection is enabled (or disabled). We can install and use `checksec`:

`apt install -y checksec`{{execute}}

Let's compare the security features compiled by default with nasm and gcc. 

`checksec --file=./say && checksec --file=./hello`{{execute}}

Note that as opposed to nasm with gcc, all security features are enabled by default:

| security feature | value | purpose |
| --- | --- | --- |
| RELRO | (No/Partial/Full) RELRO | Relocation Read-Only |
| STACK CANARY | (no) Canary found | detect smashed stack |
| NX | NX (en/dis)abled | prevent stack from being executable |
| PIE | No Pie | ASRL protection |

For the purpose of learning and to make exploitation easier, we will recompile to disable all security features. Don't worry, we will progressively enable them one-by-one to showcase their importance and limitations, as well as how it can be by-passed by hackers. To recompile without gcc security flags:

Disable other security mechanism: Canary, DEP (stack protection) and PIE

`gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o say say.c`{{execute}}

run again `checksec --file=./say`{{execute}} and what a surprise, no more security.

Note: if PIE is enabled, it is possible to disable ASLR at kernel level without a need to recompile by simply running.

`echo 0 | sudo tee /proc/sys/kernel/randomize_va_space` (No need to execute that one, as we have disabled PIE)

