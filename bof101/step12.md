# Writing your first exploit

To make it easier, we need a local copy of the binary, so that we can perform our static and dynamic analysis. 
Then, we can create a local exploit.
To make it a remote exploit, we  simply modify our local exploit to have it work over the Network instead

## Let's 'write a local exploit first

Look at this local exploit code: `cat local-exploit.py`{{execute}}

- Two modules are imported: struct and os
- You are already familiar with struct module, so will cover only the os module
- The CRAFT A PAYLOAD section should not cause you any trouble if you have followed previous steps with attention
- Which leaves us with PAYLOAD DELIVERY on a local environment:
  - the `os.system()` will ask the operating system to execute whatever is in the parenthesis
  - `"echo %s | ./vuln" % payload`: the python interpreter will replace the `%s` sign with the value of the crafted payload

To execute the exploit, run `python local-exploit.py`{{execute}}

Once you are successful with the local exploit, you can adapt it to make a network exploit on localhost

## Utilize netcat to pipe your payload over the network

The first things that comes in mind, is to keep the payload and simply change the PAYLOAD DELIVERY

| | |
| --- | --- |
| local  | `"echo %s | ./vuln" % payload` |
| remote | `"echo %s | nc localhost 1337" % payload` |

Look at this netcat exploit code: `cat netcat-exploit.py`{{execute}}

To execute our exploit, we simply execute `python netcat-exploit.py`{{execute}}

Congratulations! You have written your first remote python exploit that automates the buffer-overflow exploitation in a reproducible manner

## Utilize python socket to replace netcat utility

Have a look at the remote exploit source code:

`cat socket-exploit.py`{{execute}}

- Two modules are imported: struct and socket. 
- The CRAFT A PAYLOAD section is almost the same as the local exploit
- The only difference is the '\n' added at the end of the payload (we did not need it on the previous exploits because it was implicitly added by the `echo` command)
- Which leaves us to walk-through the last section PAYLOAD DELIVERY: read the comments carefully, there is nothing else to add

To execute our exploit, we simply execute `python socket-exploit.py`{{execute}}

Congratulations! You have written a 100% python remote exploit 


