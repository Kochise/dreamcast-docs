# KallistiOS ##version##
#
# net/lwip/Makefile
# Copyright (C)2003 Dan Potter
#
# $Id: Makefile,v 1.4 2003/07/15 07:55:02 bardtx Exp $

TARGET := net_lwip.elf

OBJS := module.o exports.o

SUBDIRS := lwip
LIBS := -L. -llwip4
LWIPDIR := lwip/src
ARCHDIR := kos

myall: make-lwip rm-target $(TARGET)

rm-target:
	rm -f $(TARGET)

include $(KOS_BASE)/loadable/programs/Makefile.prefab

make-lwip:
	$(MAKE) -f Makefile.lwip

KOS_LOCAL_CFLAGS := -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

exports.o: exports.c

exports.c: exports.txt
	$(KOS_BASE)/utils/genexports/genexports.sh exports.txt exports.c lwip_symtab

clean:
	$(MAKE) -f Makefile.lwip clean
	rm -f $(OBJS) $(TARGET) exports.c
