# KallistiOS Ogg/Vorbis Decoder Library
#
# Library Makefile
# (c)2001 Thorsten Titze
# Based on KOS Makefiles by Dan Potter

TARGET = liboggvorbisplay.a
OBJS =
SUBDIRS = liboggvorbis liboggvorbisplay

all: subdirs copylibs

# Copy libs from target oggvorbis and oggvorbisplay to root
copylibs:
	cp ./liboggvorbisplay/lib/liboggvorbisplay.a $(KOS_ADDONS_BASE)/lib/$(KOS_ARCH)/

include ../Makefile.prefab
