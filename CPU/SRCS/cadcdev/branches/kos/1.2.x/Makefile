# KallistiOS ##version##
#
# Root Makefile
# (c)2000-2001 Dan Potter
#   
# $Id: Makefile,v 1.5 2002/04/20 17:23:31 bardtx Exp $

all: build-utils build-libc build-libm build-libk++ build-kernel build-addons # build-examples

clean:
	-rm -f lib/*
	$(KOS_MAKE) -C utils clean
	$(KOS_MAKE) -C libc clean
	$(KOS_MAKE) -C libm clean
	$(KOS_MAKE) -C libk++ clean
	$(KOS_MAKE) -C kernel clean
	$(KOS_MAKE) -C addons clean
#	$(KOS_MAKE) -C examples clean

build-utils:
	$(KOS_MAKE) -C utils

build-libc:
	$(KOS_MAKE) -C libc

build-libm:
	$(KOS_MAKE) -C libm

build-libk++:
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C libk++
endif

build-kernel:
	$(KOS_MAKE) -C kernel

build-addons:
	$(KOS_MAKE) -C addons

build-examples:
	$(KOS_MAKE) -C examples


