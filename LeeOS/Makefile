ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

ASMFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -nostdlib -fno-pie -fno-stack-protector
LDFLAGS = -m elf_i386 -T linker.ld

all: OS.img
builddir:
	mkdir -p build
build/stage1.bin:	boot/stage1.asm | builddir
	$(ASM) -f bin $< -o $@		
build/stage2.bin:	boot/stage2.asm	| builddir
	$(ASM) -f bin $< -o $@
build/kernel_entry.o: boot/entry.asm	| builddir
	$(ASM) $(ASMFLAGS) $< -o $@
build/kernel.o: kernel/kernel.c	| builddir
	$(CC) $(CFLAGS) $< -o $@
build/kernel.bin: build/kernel_entry.o build/kernel.o
	$(LD) $(LDFLAGS) -o $@ $^ --oformat binary
OS.img:	build/stage1.bin build/stage2.bin build/kernel.bin 
	cat $^ > $@
run:
	qemu-system-i386 -fda OS.img -boot d
clean:
	rm -rf build/*.bin build/*.o OS.img

#all:jrehgis
#	@nasm -f bin boot/stage1.asm -o build/stage1.bin
#	@nasm -f bin boot/stage2.asm -o build/stage2.bin
#	@sleep 0.1
#@i686-elf-gcc -ffreestanding -m32 -c kernel/kernel.c -o build/kernel.o
#@i686-elf-ld -m elf_i386 -T linker.ld build/stage2.o build/kernel.o -o build/stage2.elf
#@i686-elf-objcopy -O binary -R .note -R .comment -S build/stage2.elf build/stage2.bin
#	@cat build/stage1.bin build/stage2.bin > LeeOS.img
#run:
#	@qemu-system-x86_64 -drive format=raw,file=LeeOS.img


#clean:
#	@rm build/stage1.bin build/stage2.o LeeOS.img build/stage2.elf build/stage2.bin disk.img build/kernel.o 
