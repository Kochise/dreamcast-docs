# KallistiOS ##version##
#
# libtga Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/02/27 04:25:42 bardtx Exp $

OBJS = tga.o

# Compat with older KOS functions for DC usage
ifeq ($(KOS_ARCH), dreamcast)
	OBJS += tga_texture.o
endif

SUBDIRS =

myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libtga.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libtga.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


