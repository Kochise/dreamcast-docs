# KallistiOS ##version##
#
# addons/libtremor/xiph Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.1 2002/09/04 03:28:40 bardtx Exp $

KOS_LOCAL_CFLAGS = -DPACKAGE=\"libvorbisidec\" -DVERSION=\"1.0.2\" \
	-DHAVE_DLFCN_H=1 -I. \
	-O2 -fsigned-char  -D_REENTRANT

OBJS  = bitwise.o block.o codebook.o floor0.o floor1.o framing.o info.o
OBJS += mapping0.o mdct.o registry.o res012.o sharedbook.o synthesis.o vorbisfile.o
OBJS += window.o
SUBDIRS =

all: $(OBJS)
	cp $(OBJS) ../build/

clean:
	-rm -f $(OBJS)

include $(KOS_BASE)/Makefile.rules

