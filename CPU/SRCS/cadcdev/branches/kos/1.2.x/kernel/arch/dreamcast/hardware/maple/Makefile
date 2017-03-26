# KallistiOS ##version##
#
# arch/dreamcast/hardware/maple/Makefile
# (c)2000-2001 Dan Potter
#
# $Id: Makefile,v 1.2 2003/03/15 00:47:24 bardtx Exp $

# Core maple handling stuff
OBJS := maple_driver.o maple_enum.o maple_globals.o
OBJS := $(OBJS) maple_init_shutdown.o maple_irq.o
OBJS := $(OBJS) maple_queue.o maple_utils.o

# Various input devices
OBJS := $(OBJS) controller.o keyboard.o mouse.o purupuru.o

# Output devices
OBJS := $(OBJS) vmu.o

# Old maple compatibility
OBJS := $(OBJS) maple_compat.o

SUBDIRS =

include $(KOS_BASE)/Makefile.prefab



