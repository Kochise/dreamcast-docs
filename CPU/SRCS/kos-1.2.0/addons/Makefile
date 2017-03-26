# KallistiOS 1.2.0
#
# addons/Makefile
# (c)2000-2001 Dan Potter
#   
# $Id: Makefile,v 1.21 2003/04/24 02:52:42 bardtx Exp $

all: build-jpeg build-mp3 build-oggvorbis build-gl \
	build-zlib build-png build-dcplib build-libbz2 build-libmodplug \
	build-lwip build-pcx build-tga build-conio build-imageload \
	build-lua build-tremor build-parallax build-tsunami build-kosh \
	build-sdl build-kmg
	# build-os

clean:
	$(KOS_MAKE) -C libbz2 clean
	$(KOS_MAKE) -C zlib clean
	$(KOS_MAKE) -C libpng clean
	$(KOS_MAKE) -C libpcx clean
	$(KOS_MAKE) -C libjpeg clean
	$(KOS_MAKE) -C libpcx clean
	$(KOS_MAKE) -C libtga clean
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C lwip clean
	$(KOS_MAKE) -C lua clean
	$(KOS_MAKE) -C libmp3 clean
	$(KOS_MAKE) -C liboggvorbis clean
	$(KOS_MAKE) -C libgl clean
	$(KOS_MAKE) -C libdcplib clean
	$(KOS_MAKE) -C libmodplug clean
	$(KOS_MAKE) -C libimageload clean
	$(KOS_MAKE) -C libconio clean
#	$(KOS_MAKE) -C libos clean
	$(KOS_MAKE) -C libtremor clean
	$(KOS_MAKE) -C libparallax clean
	$(KOS_MAKE) -C libtsunami clean
	$(KOS_MAKE) -C libkosh clean
	$(KOS_MAKE) -C SDL clean
	$(KOS_MAKE) -C libkmg clean
endif


build-imageload:
	$(KOS_MAKE) -C libimageload

build-jpeg:
	$(KOS_MAKE) -C libjpeg

build-zlib:
	$(KOS_MAKE) -C zlib

build-libbz2:
	$(KOS_MAKE) -C libbz2

build-png:
	$(KOS_MAKE) -C libpng

build-pcx:
	$(KOS_MAKE) -C libpcx

build-tga:
	$(KOS_MAKE) -C libtga

build-lwip:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C lwip
endif
	
build-lua:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C lua
endif

build-mp3:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libmp3
endif

build-oggvorbis:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C liboggvorbis
endif

build-gl:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libgl
endif

build-os:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libos
endif

build-dcplib:
ifeq ($(KOS_ARCH), dreamcast)
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C libdcplib
endif
endif

build-libmodplug:
ifeq ($(KOS_ARCH), dreamcast)
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C libmodplug
endif
endif

build-conio:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libconio
endif

build-kosh:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libkosh
endif

build-tremor:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libtremor
endif

build-parallax:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libparallax
endif

build-tsunami:
ifeq ($(KOS_ARCH), dreamcast)
ifdef KOS_CCPLUS
	$(KOS_MAKE) -C libtsunami
endif
endif

build-sdl:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C SDL
endif

build-kmg:
ifeq ($(KOS_ARCH), dreamcast)
	$(KOS_MAKE) -C libkmg
endif


