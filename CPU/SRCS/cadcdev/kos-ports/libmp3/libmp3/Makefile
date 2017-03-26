# KallistiOS ##version##
#
# libmp3/Makefile
# (c)2001 Dan Potter
#   
# $Id: Makefile,v 1.2 2002/02/10 06:36:38 bardtx Exp $

OBJS = main.o sndmp3.o

BUILD_TARGET = addons/libmp3
KOS_CFLAGS += -I../xingmp3 
# KOS_LOCAL_CFLAGS = -I../mpglib

all: $(OBJS)
	cp $(OBJS) ../build/

include $(KOS_BASE)/Makefile.prefab

