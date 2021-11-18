# How to build your compiling environment

We can see that our current architecture is 64 bits by running the below command:

`uname -a`{{execute}}

For the sake of simplicity, we will focus on 32 bits architecture, so we need a compilation toolchain that supports i386 architecture:

`dpkg --add-architecture i386`{{execute}}

It is good practice to update your environment before installing new packages. Also worth to notice that the command-line manual is not available by default on ubuntu, so we want to `unminimize` before installing anything:

`apt update -y && yes | unminimize apt upgrade -y`{{execute}}

Now, it is a good time to build a fresh compilation toolchain for both 64 and 32 bits architecture:

`apt install -y --fix-missing man man-db sudo build-essential gdb gdb-multiarch libc6-dbg libc6-dbg:i386 make gcc-multilib g++-multilib nasm ltrace strace`{{execute}}

Now let's move on to the next step to "Build your first C program"
