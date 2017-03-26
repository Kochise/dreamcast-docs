all: boot.bin

boot.bin: boot.o
	dc-objcopy -O binary boot.o boot.bin
	cp -f boot.bin ../bootstrap_load/romdisk/

boot.o: boot.s font.s
	dc-as -little boot.s -o boot.o

font.s: font.bin
	./makefonts.py > font.s
