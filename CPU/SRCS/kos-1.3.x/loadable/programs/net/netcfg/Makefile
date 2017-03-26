#
# KallistiOS Network Configurator
# Copyright (C)2003 Dan Potter
#   

TARGET = netcfg.elf
OBJS = romdisk.o netcfg.o menu.o starfield.o subwelcome.o textdisplay.o \
	subexit.o popup.o menubox.o hsv.o widget.o subnetdrv.o ipeditor.o \
	subip.o messagebox.o subsave.o

LIBS := -ltsunami -lpng -ljpeg -lkmg -lz -lparallax -lk++ -lm

include $(KOS_BASE)/loadable/programs/Makefile.prefab

