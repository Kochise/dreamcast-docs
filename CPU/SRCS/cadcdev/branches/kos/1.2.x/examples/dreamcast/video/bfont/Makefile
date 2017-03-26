# KallistiOS ##version##
#
# basic/bfont/Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.1 2002/06/27 23:23:09 bardtx Exp $

all: rm-elf bfont.elf

include $(KOS_BASE)/Makefile.rules

OBJS = bfont.o

clean:
	-rm -f bfont.elf $(OBJS)

rm-elf:
	-rm -f bfont.elf

bfont.elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o bfont.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) $(KOS_LIBS)

run: bfont.elf
	$(KOS_LOADER) bfont.elf

dist:
	-rm -f $(OBJS)
	$(KOS_STRIP) bfont.elf
