#
# Makefile
#
# Copyright (C)2004 Dan Potter
# License: BSD
#   

# Target / source info
START = 0x8c004000
#START = 0x8c010000

MINIKOS = minikos/startup.o minikos/memchr.o minikos/memcmp.o \
	minikos/memcpy.o minikos/memmove.o minikos/sprintf.o \
	minikos/vsprintf.o minikos/strlen.o minikos/entry.o \
	minikos/strncmp.o minikos/memset.o minikos/dbg_printf.o \
	minikos/strcpy.o \
	minikos/scif.o minikos/g2bus.o minikos/timer.o \
	minikos/video.o minikos/biosfont.o minikos/irq.o

DRIVERS = drivers/broadband_adapter.o drivers/lan_adapter.o

NET = net/core.o net/icmp.o net/udp.o net/arp.o

MAIN = slinkie/main.o slinkie/syscalls.o slinkie/commands.o \
	slinkie/exec.o

OBJS = $(MINIKOS) $(DRIVERS) $(NET) $(UIP) $(MAIN)

OBJS1R = 1st_read/cache.o 1st_read/main.o 1st_read/payload.o

include ../Makefile.cfg

all: rm-banner 1st_read.bin

%.bin: %.elf
	$(TARGETOBJCOPY) -R .stack -O binary $< $@

%.o: %.c
	$(TARGETCC) $(TARGETCFLAGS) -I. -Iminikos -Idrivers -D_arch_dreamcast -Wall -fno-builtin -fno-strict-aliasing -c $< -o $@

%.o: %.s
	$(TARGETAS) -little $< -o $@

rm-banner:
	-rm -f minikos/banner.h
	-rm -f slinkie.elf slinkie.bin 1st_read.elf 1st_read.bin

slinkie/main.c: minikos/banner.h

minikos/banner.h: minikos/make_banner.sh
	minikos/make_banner.sh

clean:
	-rm -f slinkie.bin slinkie.elf 1st_read.bin 1st_read.elf $(OBJS) $(OBJS1R) minikos/banner.h

slinkie.elf: $(OBJS)
	$(TARGETCC) $(TARGETCFLAGS) -Wl,-Ttext=$(START) -nostartfiles -nostdlib -o slinkie.elf $(OBJS) -lgcc

1st_read/payload.o: slinkie.bin
	../host/scripts/bin2o slinkie.bin payload 1st_read/payload.o

1st_read.elf: $(OBJS1R)
	$(TARGETCC) $(TARGETCFLAGS) -Wl,-Ttext=0x8c010000 -nostartfiles -nostdlib -o 1st_read.elf $(OBJS1R) -lgcc
