#S3MPLAY Makefile (C) PH3NOM 2011

all: stream.drv

stream.drv: prog.elf
	$(DC_ARM_OBJCOPY) -O binary prog.elf stream.drv

prog.elf: crt0.o main.o aica.o s3mplay.o
	$(DC_ARM_CC) -Wl,-Ttext,0x00000000 -nostartfiles -nostdlib -e reset -o prog.elf crt0.o main.o aica.o s3mplay.o -lgcc

%.o: %.c
	$(DC_ARM_CC) $(DC_ARM_CFLAGS) $(DC_ARM_INCS) -c $< -o $@

%.o: %.s
	$(DC_ARM_AS) -mcpu=arm7di -march=armv4 $< -o $@

clean:
	-rm -f *.o *.srec *.elf prog.bin *.bck