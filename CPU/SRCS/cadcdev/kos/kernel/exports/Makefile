# KallistiOS ##version##
#
# kernel/exports/Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.1 2003/06/19 04:29:00 bardtx Exp $

OBJS = nmmgr.o kernel_exports.o exports.o library.o
SUBDIRS = 

include $(KOS_BASE)/Makefile.prefab

kernel_exports.o: kernel_exports.c

kernel_exports.c: ../exports.txt
	$(KOS_BASE)/utils/genexports/genexports.sh ../exports.txt kernel_exports.c kernel_symtab

clean:
	-rm -f kernel_exports.c $(OBJS)
