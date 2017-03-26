# KallistiOS ##version##
#
# arch/ps2/kernel/Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.3 2002/11/03 03:40:55 bardtx Exp $

# Generic kernel abstraction layer: this provides a set of routines
# that the portable part of the kernel expects to find on every
# target processor. Other routines may be present as well, but
# that minimum set must be present.

COPYOBJS = banner.o dbgio.o main.o irq.o panic.o entry.o
COPYOBJS += init_flags_default.o init_romdisk_default.o
COPYOBJS += crtbegin.o crtend.o atexit.o mm.o startup.o
COPYOBJS += cache.o syscall.o timer.o
OBJS = $(COPYOBJS)
SUBDIRS = 

myall: $(OBJS)
	-cp $(COPYOBJS) $(KOS_BASE)/kernel/build/
	-rm banner.c banner.o

include $(KOS_BASE)/Makefile.prefab

banner.o: banner.c

banner.c: make_banner.sh
	./make_banner.sh


