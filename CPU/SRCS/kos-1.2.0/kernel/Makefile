# KallistiOS 1.2.0
#
# kernel Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.5 2002/02/27 05:43:11 bardtx Exp $

OBJS =
SUBDIRS = arch fs misc mm thread net

all: subdirs
	rm -f $(KOS_BASE)/lib/libkallisti.a
	$(KOS_AR) rcs $(KOS_BASE)/lib/libkallisti.a build/*.o build/libc/*.o

include $(KOS_BASE)/Makefile.prefab

clean: clean_subdirs
	rm -f build/*.o
	rm -f build/libc/*.o

run:


