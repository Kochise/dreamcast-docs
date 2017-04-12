# KallistiOS 1.1.6
#
# Root Makefile
# (c)2000-2001 Dan Potter
#   
# $Id: Makefile,v 1.2 2002/01/05 07:03:11 bardtx Exp $

all: build-utils build-kernel build-addons build-examples

clean:
	-rm -f lib/*
	$(KOS_MAKE) -C utils clean
	$(KOS_MAKE) -C kernel clean
	$(KOS_MAKE) -C addons clean
	$(KOS_MAKE) -C examples clean

build-utils:
	$(KOS_MAKE) -C utils

build-kernel:
	$(KOS_MAKE) -C kernel

build-addons:
	$(KOS_MAKE) -C addons
	cp lib-release/libm.a lib/

build-examples:
	$(KOS_MAKE) -C examples


