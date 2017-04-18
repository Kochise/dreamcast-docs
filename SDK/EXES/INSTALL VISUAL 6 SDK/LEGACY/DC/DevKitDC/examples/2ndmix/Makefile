# KallistiOS 1.1.6
#
# 2ndmix/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.1.1.1 2001/09/26 07:05:15 bardtx Exp $

all: rm-elf kallistios.elf

include $(KOS_BASE)/Makefile.rules

OBJS = 2ndmix.o

clean:
	-rm -f kallistios.elf $(OBJS)
	-rm -f romdisk_boot.*

rm-elf:
	-rm -f kallistios.elf
	-rm -f romdisk_boot.img
	-rm -f romdisk_boot.o

DATAOBJS = romdisk_boot.o
kallistios.elf: $(OBJS) romdisk_boot.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o kallistios.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -lkallisti -lgcc

romdisk_boot.img:
	$(KOS_GENROMFS) -f romdisk_boot.img -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk_boot.img romdisk_boot romdisk_boot.o

run: kallistios.elf
	$(KOS_LOADER) kallistios.elf

dist:
	rm -f $(OBJS) romdisk_boot.*
	mv kallistios.elf 2ndmix.elf
	$(KOS_CC_BASE)/bin/sh-elf-strip 2ndmix.elf

