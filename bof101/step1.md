# How to build your compiling environment

We can see that our current architecture is 64 bits by running the below command:

`uname -a`{{execute}}

For the sake of simplicity, we will focus on 32 bits architecture, so we need a compilation toolchain that supports i386 architecture:

`dpkg --add-architecture i386`{{execute}}

It is good practice to update your environment before installing new packages. We will skip this step for the sake of time as it will take few precious minutes to install upgrades; however, should we meet any build issue during this scenario, then will have to rebuild with:

`apt update -y && apt upgrade -y`

Now, it is a good time to build a fresh compilation toolchain for both 64 and 32 bits architecture:

`apt install -y --fix-missing man man-db sudo build-essential gdb gdb-multiarch libc6-dbg libc6-dbg:i386 make gcc-multilib g++-multilib nasm ltrace strace`{{execute}}

Now let's move on to the next step to "Build your first C program"
