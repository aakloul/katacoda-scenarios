# Buffer overflow of the network

So far, We have explored how to exploit a buffer-overflow:
- via program argument (strcopy function)
- via command prompt (gets function) 

Did you know that it works "almost" the same for a service exposed over the Network? Well there is a slight difference, though:
- you don't have access to the file system (no access to core dump, if any)
- you don't always have a remote shell to use:
  - to use the command-prompt to read events with `dmesg`
  - to perform static analysis of the remote binary: `file`, `objdump`, `readelf` ...

The Fuzzing technique consists in trying inputs of different sizes and different nature

you don't  
-  
