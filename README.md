# LeeOS
My own x86_64 opersting system!

Includes:
- Stage 1 and Stage 2 Bootloader in x86 assembly
- Kernel written in C compiled for i386 architexture
- Small kernel library

Requirements:
- qemu
- i686-elf-gcc/ld/objcopy on mac
- i686-linux-gnu-gcc/ld/objcopy binutils-i686-likux-gnu gcc-i686-linux-gnu on linux
- build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev 

Running It:
- Run "make && make run" in your terminal within the project directory and done!