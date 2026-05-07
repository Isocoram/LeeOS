ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

ASMFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector
LDFLAGS = -m elf_i386 -T linker.ld

all: OS.img
builddir:
	@mkdir -p build
build/stage1.bin:	boot/stage1.asm | builddir
	$(ASM) -f bin $< -o $@		
build/stage2.bin:	boot/stage2.asm	| builddir
	$(ASM) -f bin $< -o $@
build/kernel_entry.o: boot/entry.asm	| builddir
	$(ASM) $(ASMFLAGS) $< -o $@
build/kernel.o: kernel/kernel.c	| builddir
	$(CC) $(CFLAGS) $< -o $@
#build/kernel_library.o: src/kernel_library.c | builddir
#	$(CC) $(CFLAGS) -c $< -o $@
build/kernel.bin: build/kernel_entry.o build/kernel.o 
	$(LD) $(LDFLAGS) -o $@ $^ --oformat binary
OS.img:	build/stage1.bin build/stage2.bin build/kernel.bin
	cat $^ > $@
run:
	@qemu-system-i386 -drive format=raw,file=OS.img,if=floppy -boot a
clean:
	@rm -rf build/*.bin build/*.o OS.img
