#
# KallistiOS Debug Host
# Copyright (C)2003 Dan Potter
#   

TARGET = debug.elf
OBJS = romdisk.o debug.o tty.o net.o proto.o fserv.o

LWIPDIR := $(KOS_BASE)/loadable/modules/net/net_lwip/lwip/src
ARCHDIR := $(LWIPDIR)/../../kos

KOS_LOCAL_CFLAGS := -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

LIBS := -ljpeg

include $(KOS_BASE)/loadable/programs/Makefile.prefab

