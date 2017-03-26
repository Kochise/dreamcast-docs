# KallistiOS ##version##
#
# $Id: Makefile,v 1.1 2003/07/31 00:48:09 bardtx Exp $

BUILD_TARGET=loadable/libkos

OBJS = lwip_socket.o lwip_bind.o lwip_listen.o lwip_select.o lwip_accept.o \
	lwip_write.o lwip_close.o lwip_read.o lwip_ioctl.o lwip_connect.o

LWIPDIR := $(KOS_BASE)/loadable/modules/net/net_lwip/lwip/src
ARCHDIR := $(LWIPDIR)/../../kos

KOS_LOCAL_CFLAGS := -DIPv4 \
	-I$(LWIPDIR)/include -I$(ARCHDIR)/include \
	-I$(LWIPDIR)/include/ipv4

include $(KOS_BASE)/Makefile.prefab



