# Set these paths to match your compiler setup
TARGET=arm-elf
DCBASE=/usr/local/dc/arm-elf
CC=$(DCBASE)/bin/$(TARGET)-gcc -mcpu=arm7 -Wall
LD=$(DCBASE)/bin/$(TARGET)-ld
AS=$(DCBASE)/bin/$(TARGET)-as -marm7
AR=$(DCBASE)/bin/$(TARGET)-ar
OBJCOPY=$(DCBASE)/bin/$(TARGET)-objcopy

all: aica_fw.h

aica_fw.h: prog.bin
	../../utils/bin2c prog.bin aica_fw.h.tmp
	echo 'unsigned char s3mplay[] = {' > aica_fw.h
	cat aica_fw.h.tmp >> aica_fw.h
	echo '};' >> aica_fw.h
	-rm aica_fw.h.tmp

prog.bin: prog.elf
	$(OBJCOPY) -O binary prog.elf prog.bin

prog.elf: crt0.o main.o aica.o s3mplay.o
	$(CC) -Wl,-Ttext,0x00000000 -nostartfiles -nostdlib -e reset -o prog.elf crt0.o main.o aica.o s3mplay.o -lgcc

%.o: %.c
	$(CC) -O2 $(INCS) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

clean:
	-rm -f *.o *.srec *.elf 1ST_READ.BIN prog.bin *.bck


