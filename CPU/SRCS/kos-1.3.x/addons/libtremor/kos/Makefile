# KallistiOS ##version##
#
# addons/libtremor/kos Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.1 2002/09/04 03:28:40 bardtx Exp $

KOS_LOCAL_CFLAGS = -DPACKAGE=\"libvorbisidec\" -DVERSION=\"1.0.2\" \
	-DHAVE_DLFCN_H=1 -DHAVE_ALLOCA=1  -I. -I../xiph \
	-O2 -fsigned-char  -D_REENTRANT

OBJS    = sndoggvorbis.o main.o
SUBDIRS =

all: $(OBJS)
	cp $(OBJS) ../build/

clean:
	-rm -f $(OBJS)

include $(KOS_BASE)/Makefile.rules

