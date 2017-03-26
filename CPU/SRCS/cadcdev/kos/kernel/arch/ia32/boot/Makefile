# KallistiOS ##version##
#
# arch/ia32/loader/Makefile
#
# $Id: Makefile,v 1.2 2003/08/02 09:14:11 bardtx Exp $

all:
	nasm loader.asm -o loader.bin

install: all
	$(KOS_OBJCOPY) -O binary ../../../../lib/kernel.elf kernel.bin
	cat kernel.bin >> loader.bin
	dd if=loader.bin of=/home/bard/.bochs/hd0 seek=4032 bs=512 conv=notrunc

# Use this if you want a kosher binary for disassembly, for checking exactly
# what nasm did.
testbin:
	nasm -g -felf loader.asm -o loader.o

clean:
	rm -f loader.bin kernel.bin
