# KallistiOS ##version##
#
# drivers/dreamcast/net_la/Makefile
# Copyright (C)2003 Dan Potter
#
# $Id: Makefile,v 1.2 2003/07/15 07:55:01 bardtx Exp $

TARGET := net_la.elf

OBJS := lan_adapter.o

SUBDIRS =

include $(KOS_BASE)/loadable/programs/Makefile.prefab

exports.o: exports.c

exports.c: exports.txt
	$(KOS_BASE)/utils/genexports/genexports.sh exports.txt exports.c maple_symtab

local_clean:
	rm -f exports.c
