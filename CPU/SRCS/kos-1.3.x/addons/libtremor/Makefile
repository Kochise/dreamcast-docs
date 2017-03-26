# KallistiOS ##version##
#
# addons/libtremor Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/02/27 04:25:42 bardtx Exp $

OBJS  = 
SUBDIRS = xiph kos

myall: subdirs
	rm -f $(KOS_ADDONS_BASE)/lib/libtremor.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libtremor.a build/*.o

include $(KOS_BASE)/Makefile.prefab

clean: clean_subdirs
	rm -f build/*.o build/*.a

