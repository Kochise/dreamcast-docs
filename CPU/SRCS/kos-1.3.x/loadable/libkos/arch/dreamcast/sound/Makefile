# KallistiOS ##version##
#
# arch/dreamcast/sound/Makefile
# Copyright (C)2001,2003 Dan Potter
#   
# $Id: Makefile,v 1.1 2003/06/19 04:20:59 bardtx Exp $

BUILD_TARGET=loadable/libkos

OBJS = snd_iface.o snd_sfxmgr.o snd_stream.o snd_stream_drv.o snd_mem.o

# Only compile this if we have an ARM compiler handy
ifdef DC_ARM7CC
	SUBDIRS = arm
endif

include $(KOS_BASE)/Makefile.prefab

snd_stream_drv.o: arm/stream.drv
	$(KOS_BASE)/utils/bin2o/bin2o $< snd_stream_drv snd_stream_drv.o

