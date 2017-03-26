OBJS =  layer1.o layer2.o common.o dct64_i386.o decode_i386.o
OBJS += layer3.o tabinit.o interface.o
CC=gcc
CFLAGS=-O2 -Wall -DLAYER1 -DLAYER2 -DLAYER3

all: libmpg.a

libmpg.a: $(OBJS)
#	$(KOS_AR) rcs libmpg.a $(OBJS)
	cp $(OBJS) ../build

*.o: mpg123.h mpglib.h

clean:
	rm -f $(OBJS)

include $(KOS_BASE)/Makefile.rules

