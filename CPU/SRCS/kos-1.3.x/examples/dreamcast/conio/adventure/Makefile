# KallistiOS ##version##
#
# conio/adventure/Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.3 2002/06/11 06:55:17 bardtx Exp $

all: rm-elf adventure.elf

include $(KOS_BASE)/Makefile.rules

OBJS = porthelper.o crc.o done.o init.o io.o main.o save.o subr.o vocab.o wizard.o data.o

data.c:
	gcc -o setup setup.c -DSETUP
	./setup glorkz > data.c

clean:
	-rm -f adventure.elf $(OBJS) data.c setup

rm-elf:
	-rm -f adventure.elf

adventure.elf: $(OBJS) 
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o adventure.elf $(KOS_START) $(OBJS) $(DATAOBJS) $(OBJEXTRA) -lconio $(KOS_LIBS)

run: adventure.elf
	$(KOS_LOADER) adventure.elf

dist:
	-rm -f $(OBJS) data.c setup
	$(KOS_STRIP) adventure.elf
