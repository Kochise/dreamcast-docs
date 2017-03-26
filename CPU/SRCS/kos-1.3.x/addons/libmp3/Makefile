# KallistiOS ##version##
#
# kernel Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.3 2003/02/27 04:25:40 bardtx Exp $

OBJS =
SUBDIRS = xingmp3 libmp3
# SUBDIRS = mpglib libmp3

myall: subdirs
	rm -f $(KOS_ADDONS_BASE)/lib/libmp3.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libmp3.a build/*.o

include $(KOS_BASE)/Makefile.prefab

clean: clean_subdirs
	rm -f build/*.o build/*.a

run:

