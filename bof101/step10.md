# Endianess and struct python module

The [struct python module](https://docs.python.org/3/library/struct.html#format-characters) is a formidable library to convert python values into C-structs. One of the main usage for it, is to__ interpret bytes as packed binary data__:

## Littler-Endian (LE) vs. Big-Endian (BE)

> In computing, endianness is the order or sequence of bytes of a word of digital data in computer memory. Endianness is primarily expressed as big-endian or little-endian. A big-endian system stores the most significant byte of a word at the smallest memory address and the least significant byte at the largest
> [Wikipedia](https://en.wikipedia.org/wiki/Endianness)

To illustrate, let's compare Arabic vs. English books: The first is written or read from right-to-left while the other is from left-to-right! Luckily, we don't have anything from top-to-bottom and the only alphabet we got are `0s` and `1s` ... what a relief!

Let's say that we want to write the number 134517454 (base10) in computer language. A computer only understand base2 (0s and 1s) but can easily represents bytes in base16 which will translates into 0x80492ce (base 16).

| -- | -- | -- |
| LE | \xce\x92\x04\x08 | least significant bytes written first |
| BE | \x08\x04\x92\xce | most significant bytes written first |





