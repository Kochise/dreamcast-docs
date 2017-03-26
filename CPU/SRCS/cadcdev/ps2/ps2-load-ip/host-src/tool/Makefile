#
# Makefile for ps2-load-ip/host-src
#
# Copyright (c)2001 Andrew Kieschnick
# License: GPL
#

include ../../Makefile.cfg

CC	= $(HOSTCC)
CFLAGS	= -g $(HOSTCFLAGS) -DPS2_IP=\"$(PS2_IP)\" -DHAVE_GETOPT
INCLUDE	= -I$(BFDINCLUDE)

OBJECTS	= ps2-tool.o syscalls.o

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: ps2-tool

ps2-tool: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(BFDLIB)

.PHONY : install
install: ps2-tool
	cp ps2-tool$(EXECUTABLEEXTENSION) $(TOOLINSTALLDIR)

.PHONY : clean
clean:
	rm -f $(OBJECTS)

.PHONY : distclean
distclean: clean 
	rm -f ps2-tool
