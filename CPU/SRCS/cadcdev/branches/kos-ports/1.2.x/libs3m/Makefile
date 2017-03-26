# KallistiOS ##version##
#
# kernel Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.1.1.1 2001/09/26 07:05:09 bardtx Exp $

OBJS = sfxmgr.o
SUBDIRS =

KOS_LOCAL_CFLAGS = -I$(KOS_BASE)/include/s3m

myall: $(OBJS)
	rm -f $(KOS_BASE)/lib/libs3m.a
	$(KOS_AR) rcs $(KOS_BASE)/lib/libs3m.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


