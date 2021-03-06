# What else can I fuzz to detect buffer overflow?

Well, it is up to the exploit developer to Fuzz everything that can receive data. It could be:
- any programme argument
- a command prompt where the programme ask the user for his input
- a data stream, such as a network socket exposed on a certain port
- an http API or a websocket
- a text field in a graphical interface or a web form
- an image (whichever the format) or any kind of media (audio, video format ...)
- an AI input (why not?)

## gets is the most vulnerable C-function to Buffer Overflow

Let's explore another vulnerable function with a command prompt input instead of an argument:

`cd ../buffer-overflow-1 && cat ./vuln.c`{{execute}}

At compilation time, you get a high chance to have a warning message because you are using a dangerous C-function `gets`. This function prompt the user for a keyboard input and will copy whatever the user type in a buffer without verifying the size of the buffer. The weakness of this function design is it cannot know in advance how many characters you will type in. You can have more details in the manual: `man gets`{{execute}} (lick on the terminal and press `q`{{execute}} to quit)

`gcc -m32 -O0 -fno-stack-protector -no-pie -z execstack  -o vuln vuln.c`{{execute}}

Then execute without argument: `./vuln`{{execute}}. Type anything below the Buffer size, and it will be echoed back to you.

It is possible to use the `echo` command to pass your input to this programme:

`echo "This is a test" | ./vuln`{{execute}}

Which make it easy to use python again:

`echo $(python -c "print('A'*64)") | ./vuln`{{execute}}

Now that we get our segmentation fault, how about you craft your own exploit?

## Exercise

Find a way to execute the `win` function:

1. What is the address of the `win` symbol
2. Identify the size of the offset to fill-in the buffer before overwriting the instruction pointer
3. Modify the payload to overwrite the instruction pointer with the `win` function address

