# KallistiOS ##version##
#
# arch/dreamcast/hardware/Makefile
# (c)2000-2001 Dan Potter
#
# $Id: Makefile,v 1.12 2003/05/23 02:04:42 bardtx Exp $

# Init wrapper
OBJS = hardware.o

# BIOS services
OBJS += biosfont.o cdrom.o flashrom.o

# Sound
OBJS += spu.o spudma.o

# Bus support
OBJS += asic.o g2bus.o

# Video-related
OBJS += video.o vblank.o

# CPU-related
OBJS += sq.o

SUBDIRS = pvr network maple modem

include $(KOS_BASE)/Makefile.prefab



