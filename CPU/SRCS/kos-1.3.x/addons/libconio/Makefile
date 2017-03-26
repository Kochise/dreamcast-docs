# KallistiOS ##version##
#
# addons/libconio Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.3 2003/07/31 00:35:24 bardtx Exp $

OBJS =  conio.o input.o # draw.o
SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libconio.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libconio.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


