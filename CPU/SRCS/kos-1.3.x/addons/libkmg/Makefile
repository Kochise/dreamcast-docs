# KallistiOS ##version##
#
# libkmg Makefile
# Copyright (c)2003 Dan Potter
#   
# $Id: Makefile,v 1.1 2003/03/14 05:50:36 bardtx Exp $

OBJS = kmg.o

SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libkmg.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libkmg.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


