CC ?= clang
NASM ?= nasm
LD ?= ld
STRIP ?= strip
MKBOOTIMG ?= mkbootimg
QEMU ?= qemu-system-x86_64

CFLAGS = -Wall -fpic -ffreestanding -fno-stack-protector -nostdinc -nostdlib

.PHONY: all clean run run-graphical

all: kernel.elf

clean:
	rm -f *.o *.img *.elf

run: kernel.img
	$(QEMU) -drive file=$^,format=raw -serial stdio -display none

run-graphical: kernel.img
	$(QEMU) -drive file=$^,format=raw -serial stdio

kernel.elf: kernel.c link.ld
	$(CC) $(CFLAGS) -mno-red-zone -c kernel.c -o kernel.o
	$(NASM) -f elf64 putc.asm -o putc.o
	$(LD) -nostdlib -nostartfiles -T link.ld kernel.o putc.o -o $@
	$(STRIP) -s -K mmio -K fb -K bootboot -K environment $@

kernel.img: mkbootimg.json kernel.elf
	$(MKBOOTIMG) $< $@
