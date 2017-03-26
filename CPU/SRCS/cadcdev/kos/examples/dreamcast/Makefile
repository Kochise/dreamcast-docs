# KallistiOS ##version##
#
# examples/dreamcast/Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.17 2003/05/23 02:05:41 bardtx Exp $

DIRS = 2ndmix basic libdream kgl hello sound png network vmu conio pvr video lua parallax modem
ifdef KOS_CCPLUS
	DIRS += cpp tsunami
endif

all:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i || exit -1; done

clean:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i clean || exit -1; done
		
dist:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i dist || exit -1; done


