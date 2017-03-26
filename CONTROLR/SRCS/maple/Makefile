AS = sh-elf-as -little
LD = sh-elf-ld -EL
CC = sh-elf-gcc -ml

OBJS = crt0.o test.o maple.o video.o

test : mapletest.srec
	../gdfs/upload.pike < mapletest.srec

mapletest.srec : $(OBJS)
	$(CC) -o $@ -Wl,--oformat,srec,-Ttext,0x8c010000 \
		-nostartfiles -nostdlib $(OBJS) -lgcc

crt0.o : crt0.s

test.o : test.c

maple.o : maple.c

video.o : video.s

