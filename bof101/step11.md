# Buffer overflow of the network

So far, We have explored how to exploit a buffer-overflow:
- via program argument (strcopy function)
- via command prompt (gets function) 

Did you know that it works "almost" the same for a service exposed over the Network? Well there is a slight difference, though:
- you don't have access to the file system (no access to core dump, if any)
- you don't always have a remote shell to use:
  - No command-prompt to read events with `dmesg`
  - No static analysis of the remote binary: `file`, `objdump`, `readelf` ...

## Remote exploitation brings additional challenges

When trying to Fuzz with large payload a network service which is vulnerable to buffer-overflow, different scenarios may occure:
- There is no signal handler and the service crashes:
  - If there is failover in place, depending on how fast the service is restarted, we may or not notice some degradation of service
  - If no failover or if the service is slow to restart, it can be considered a DoS attack (Denial Of Service)
- A signal handler capture the SIGSEGV event: We don't know the binary and symbols, but we can blindly bruteforce the service until it behaves different. 

Blind exploitation utilizes time-measurement and is very hard, resource and time consuming: odds for succes are very uncertain. However, if you are able to put your hands on the remote binary or get a copy, then it suddenly becomes much easier. Alternatively, hacker may try to make educated guess what is the service name, version number or source code to recompile their own. With good guesses and knowlegde of the operating system, there is a high chance of success as well.

## Expose your vulnerable programme over the Network

To simulate a Network Buffer Overflow on localhost, we will use a small utility called `socat`. Without digging into details, the below command  will redirect all inputs and outputs of the executed programme to a socket exposed on port 1337:

`socat TCP-LISTEN:1337,nodelay,reuseaddr,fork EXEC:"stdbuf -i0 -o0 -e0 ./vuln"`{{execute}}

The above will execute our binary every time a network connection is established on port 1337. All inputs and outputs are unbuffered and redirected to the socket which makes all the terminal interaction happens through the network socket.

## Exercise: Exploit over the Network with netcat

To communicate with port 1337 on the same machine, we will use the netcat utility. The usage is very simple: `nc <IP> <PORT>`

1. Execute the previous socat command in the Terminal
2. Now open a new Terminal by clicking the `+` sign near the Terminal tab, then select `Open New Terminal`
3. A new terminal tab called "Terminal 2" appears
3. Wait few seconds until the prompt (the `$` sign) appears
3. On the second terminal, type `echo $(python -c "print('A'*44 + '\xf6\x91\x04\x08')") | nc localhost 1337`{{execute}}

Et Voila! You have executed your first remote exploit over the Network
