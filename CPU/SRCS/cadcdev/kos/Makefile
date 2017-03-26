# KallistiOS ##version##
#
# Root Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.5 2002/04/20 17:23:31 bardtx Exp $

# Add stuff to DIRS to auto-compile it with the big tree.
DIRS = utils
ifdef KOS_CCPLUS
	DIRS += libk++
endif
DIRS += kernel addons # examples

# Detect a non-working or missing environ.sh file.
ifndef KOS_BASE
error:
	@echo You don\'t seem to have a working  environ.sh file. Please take a look at
	@echo doc/README for more info.
	@exit 0
endif

all:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i || exit -1; done

clean:
	for i in $(DIRS); do $(KOS_MAKE) -C $$i clean || exit -1; done

distclean: clean
	-rm -f $(KOS_BASE)/lib/$(KOS_ARCH)/*
	-rm -f $(KOS_BASE)/addons/lib/$(KOS_ARCH)/*
