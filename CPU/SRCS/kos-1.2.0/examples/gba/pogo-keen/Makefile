# KallistiOS 1.1.6
#
# pogo-keen/Makefile
# (c)2002 Gil Megidish
#   
# $Id: Makefile,v 1.1 2002/09/23 19:30:27 gilm Exp $

all: pogo-keen.gba

include $(KOS_BASE)/Makefile.rules

OBJS = pogo.o

clean:
	-rm -f $(OBJS)
	-rm -f pogo-keen.gba
	-rm -f pogo-keen.elf
	-rm -f romdisk_boot.o
	-rm -f romdisk_boot.img

pogo-keen.gba: pogo-keen.elf
	$(KOS_BASE)/utils/gba-elf2bin/gba-elf2bin pogo-keen.elf pogo-keen.gba
	-rm -f pogo-keen.elf

DATAOBJS = romdisk_boot.o
pogo-keen.elf: $(OBJS) $(DATAOBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o pogo-keen.elf \
		$(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -L$(KOS_BASE)/lib -lkallisti -lgcc

romdisk_boot.o:
	$(KOS_GENROMFS) -f romdisk_boot.img -d romdisk_boot -v
	$(KOS_BASE)/utils/bin2o/bin2o romdisk_boot.img romdisk_boot romdisk_boot.o

