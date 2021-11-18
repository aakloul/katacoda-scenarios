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

`objdump ./say`{{execute}}

`readelf ./say`{{execute}}
