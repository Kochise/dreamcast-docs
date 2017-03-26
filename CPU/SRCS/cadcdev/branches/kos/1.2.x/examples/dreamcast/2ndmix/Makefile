# KallistiOS ##version##
#
# 2ndmix/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.4 2002/04/20 04:24:19 axlen Exp $

all: rm-elf 2ndmix.elf

include $(KOS_BASE)/Makefile.rules

OBJS = 2ndmix.o

clean:
	-rm -f 2ndmix.elf $(OBJS)
	-rm -f romdisk_boot.*

rm-elf:
	-rm -f 2ndmix.elf
	-rm -f romdisk_boot.img
	-rm -f romdisk_boot.o

DATAOBJS = romdisk_boot.o
2ndmix.elf: $(OBJS) romdisk_boot.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o 2ndmix.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) $(KOS_LIBS)

romdisk_boot.img:
	$(KOS_GENROMFS) -f romdisk_boot.img -d romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk_boot.img romdisk_boot romdisk_boot.o

run: 2ndmix.elf
	$(KOS_LOADER) 2ndmix.elf

dist:
	rm -f $(OBJS) romdisk_boot.*
	$(KOS_STRIP) 2ndmix.elf

