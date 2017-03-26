# libkosh for KallistiOS 1.2.0
#
# Makefile
# (c)2002 Dan Potter
#
# $Id: Makefile,v 1.2 2003/02/27 04:25:40 bardtx Exp $

OBJS = builtin.o chdir.o kosh.o input.o

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libkosh.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libkosh.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


