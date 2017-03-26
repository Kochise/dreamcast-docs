# KallistiOS Ogg/Vorbis Decoder Library
#
# Library Makefile
# (c)2001 Thorsten Titze
# Based on KOS Makefiles by Dan Potter

OBJS =
SUBDIRS = liboggvorbis liboggvorbisplay

all: subdirs copylibs

# Copy libs from target oggvorbis and oggvorbisplay to root
copylibs:
	# -cp ./liboggvorbis/lib/liboggvorbis.a $(KOS_BASE)/lib/
	-cp ./liboggvorbisplay/lib/liboggvorbisplay.a $(KOS_ADDONS_BASE)/lib/

include $(KOS_BASE)/Makefile.rules

clean: clean_subdirs

run:


