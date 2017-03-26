# KallistiOS ##version##
#
# examples/dreamcast/kgl/basic/Makefile
# 
# (c)2002 Paul Boese
#
# $Id: Makefile,v 1.6 2002/12/09 04:52:17 bardtx Exp $
#
# This will make all the examples, leaving only the elf files.
# If you want to clean everything, use 'clean'.

SUBDIRS = gl scissor texenv texwrap vfzclip vq

all: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _dir_%, %, $@)

clean: $(patsubst %, _cleandir_%, $(SUBDIRS))

$(patsubst %, _cleandir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _cleandir_%, %, $@) clean

dist: $(patsubst %, _distdir_%, $(SUBDIRS))

$(patsubst %, _distdir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _distdir_%, %, $@) dist

