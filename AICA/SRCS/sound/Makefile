
ARMCC = arm-elf-gcc
ARMAS = arm-elf-as -marm7
ARMLD = arm-elf-ld

ARMCFLAGS = -mcpu=arm7 -ffreestanding -fomit-frame-pointer -O4

AS = sh-elf-as -little
LD = sh-elf-ld -EL
CC = sh-elf-gcc -ml


music.srec : crt0.o dcmain.o
	$(CC) -o $@ -Wl,--oformat,srec,-Ttext,0x8c010000 \
		-nostartfiles crt0.o dcmain.o -lgcc

dcmain.o : dcmain.c music.h

crt0.o : crt0.s

music.h : music.bin
	./bintohex.pl < $< > $@

music.bin : music.elf
	arm-elf-objcopy -O binary $< $@

music.elf : base.o music.o aica.o
	$(ARMCC) $(ARMCFLAGS) -Wl,-Ttext=0 -nostartfiles -nostdlib -o $@ base.o music.o aica.o -lgcc

base.o : base.s
	$(ARMAS) -o $@ $<

music.o : music.c aica.h bwv784.h
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<

aica.o : aica.c aica.h
	$(ARMCC) $(ARMCFLAGS) -c -o $@ $<


clean :
	-rm -f *.o *.bin *.elf *.srec
	-rm -f music.h

