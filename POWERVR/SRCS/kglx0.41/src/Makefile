# KallistiOS 1.1.8
#
# addons/libgl Makefile
# (c)2001 Dan Potter
#
# $Id: Makefile,v 1.4 2002/06/28 04:41:52 axlen Exp $

OBJS  = glapi.o gldlist.o
OBJS +=  gldepth.o gldraw.o glkos.o gllight.o glmisc.o
OBJS +=   gltex.o gltrans.o glvars.o glblend.o glfog.o
SUBDIRS =

KOS_CFLAGS+=-DINLINE="static __inline__"

myall: $(OBJS)
	rm -f ../lib/libkglx.a
	$(KOS_AR) rcs ../lib/libkglx.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


gldraw.o: gldraw.c gloparray.c