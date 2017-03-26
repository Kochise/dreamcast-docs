#
# Makefile for ps2-load-ip/target-src
#
# Copyright (c)2002 Dan Potter
# License: BSD
#   

# Target / source info
TARGET = ps2lip.elf

MINIKOS = minikos/startup.o minikos/sprintf.o minikos/vsprintf.o minikos/memcpy.o \
	minikos/strlen.o minikos/memchr.o minikos/memset.o minikos/printf.o minikos/irq.o \
	minikos/memcmp.o
ECOSDRV = ecosdrv/fb_support.o ecosdrv/smap.o
DCLOADIP = dcloadip/packet.o dcloadip/net.o dcloadip/commands.o dcloadip/go.o \
	dcloadip/syscalls.o

OBJS = $(MINIKOS) $(ECOSDRV) $(DCLOADIP) main.o

include ../Makefile.cfg

# KOS build shims
KOS_CC=$(TARGETCC)
KOS_AS=$(KOS_CC)
KOS_INCS=-I. -Iminikos -Iecosdrv -Idcloadip
KOS_ARCH=ps2
KOS_AFLAGS=-Wa,-EL -Wa,-mips3 -Wa,-mcpu=r5900 $(KOS_INCS) -c
KOS_CFLAGS=-D_arch_sub_rte -Wall -g -D_arch_$(KOS_ARCH) $(KOS_INCS) -O1 \
	-fomit-frame-pointer -DPS2_IP=\"$(PS2_IP)\"
KOS_LIBS=-lgcc
KOS_LDFLAGS=-nostartfiles -Wl,-Tminikos/link-rte.ld

all: rm-banner $(TARGET)

%.o: %.c
	$(KOS_CC) $(KOS_CFLAGS) -c $< -o $@

%.o: %.S
	$(KOS_AS) $(KOS_AFLAGS) $< -o $@

rm-banner:
	-rm -f minikos/banner.h
	-rm -f $(TARGET)

main.c: minikos/banner.h

minikos/banner.h: minikos/make_banner.sh
	minikos/make_banner.sh

clean:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(OBJS) $(KOS_LIBS)

