# KallistiOS 1.1.6
#
# test/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.1.1.1 2001/09/26 07:05:15 bardtx Exp $

all: rm-elf kallistios.elf

include $(KOS_BASE)/Makefile.rules

OBJS = threading.o

clean:
	-rm -f kallistios.elf $(OBJS)
	-rm -f romdisk_boot.*

rm-elf:
	-rm -f kallistios.elf
	-rm -f romdisk_boot.o

kallistios.elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o kallistios.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -lkallisti -lgcc

run: kallistios.elf
	$(KOS_LOADER) kallistios.elf


dist:
	rm -f $(OBJS) romdisk_boot.*
	mv kallistios.elf threading.elf
	$(KOS_CC_BASE)/bin/sh-elf-strip threading.elf
