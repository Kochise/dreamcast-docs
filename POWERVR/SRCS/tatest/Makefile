AS = sh-elf-as -little
LD = sh-elf-ld -EL
CC = sh-elf-gcc -ml -m4-single-only -mhitachi

OBJS = startup.o main.o matrix.o ta.o video.o


tatest.srec : $(OBJS)
	$(CC) -o $@ -Wl,--oformat,srec,-Ttext=0x8c010000 -nostartfiles -nostdlib $(OBJS) -lgcc -lc -lgcc

startup.o : startup.s

main.o : main.c video.h ta.h matrix.h

matrix.o : matrix.s

ta.o : ta.c ta.h

video.o : video.c video.h


