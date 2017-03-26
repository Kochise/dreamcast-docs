# KallistiOS ##version##
#
# kernel Makefile
# Copyright (C)2001,2003 Dan Potter
#   
# $Id: Makefile,v 1.7 2003/06/23 05:25:29 bardtx Exp $

TARGET = $(KOS_BASE)/lib/kernel.elf

OBJS =
SUBDIRS = arch exports fs main mm thread net

all: subdirs rm-elf $(TARGET)

$(TARGET): build/romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		build/*.o -lc -lgcc

rm-elf:
	-rm -f $(TARGET) romdisk.img build/romdisk.o

romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk -v

build/romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk build/romdisk.o

include $(KOS_BASE)/Makefile.prefab

clean: clean_subdirs
	rm -f build/*.o romdisk.img

run:
	dc-tool -x $(TARGET)

copy:
	make -C ../loadable copy
