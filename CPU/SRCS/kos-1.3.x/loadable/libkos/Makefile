# KOS libc ##version##
#
# libkos Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.3 2003/08/02 09:16:56 bardtx Exp $

SUBDIRS = arch fs misc shims

all: subdirs
	rm -f $(KOS_BASE)/lib/libkos.a
	$(KOS_AR) rcs $(KOS_BASE)/lib/libkos.a build/*.o

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

clean: clean_subdirs
	rm -f build/*.o
