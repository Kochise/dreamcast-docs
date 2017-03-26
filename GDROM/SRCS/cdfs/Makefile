AS = sh-elf-as -little
LD = sh-elf-ld -EL
CC = sh-elf-gcc -ml

OBJS = startup.o main.o cdfs.o syscall.o

cdfs.srec : $(OBJS)
	$(CC) -o $@ -Wl,--oformat,srec,-Ttext=0x8c010000 -nostartfiles -nostdlib $(OBJS) -lgcc

main.o : main.c

syscall.o : syscall.s

startup.o : startup.s

cdfs.o : cdfs.c


