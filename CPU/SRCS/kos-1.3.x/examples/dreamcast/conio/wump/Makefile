# KallistiOS ##version##
#
# conio/wump/Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.1 2002/04/20 19:49:40 bardtx Exp $

all: rm-elf wump.elf

include $(KOS_BASE)/Makefile.rules

OBJS = wump.o

clean:
	-rm -f wump.elf $(OBJS)

rm-elf:
	-rm -f wump.elf

wump.elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o wump.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -lconio $(KOS_LIBS)

run: wump.elf
	$(KOS_LOADER) wump.elf

dist:
	-rm -f $(OBJS)
	$(KOS_STRIP) wump.elf
