# KallistiOS 1.2.0
#
# os/main/Makefile
# (c)2000-2001 Dan Potter
#   
# $Id: Makefile,v 1.1.1.1 2001/09/26 07:05:01 bardtx Exp $

# I've tried to make this architecture generic, but I admit I haven't really
# tried it for anything but Dreamcast. You'll have to remove disclaimer.c at
# the least.

all: rm-elf kallistios.elf

include $(KOS_BASE)/Makefile.rules

OBJS = main.o disclaimer.o

clean:
	-rm -f kallistios.elf $(OBJS)
	-rm -f romdisk_boot.*

rm-elf:
	-rm -f kallistios.elf
	-rm -f romdisk_boot.*

DATAOBJS = romdisk_boot.o
kallistios.elf: $(OBJS) romdisk_boot.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o kallistios.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -los -lkallisti -lgcc

romdisk_boot.img:
	$(KOS_GENROMFS) -f romdisk_boot.img -d ../romdisk_boot -v

romdisk_boot.o: romdisk_boot.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk_boot.img romdisk_boot romdisk_boot.o

run: kallistios.elf
	$(KOS_LOADER) kallistios.elf

