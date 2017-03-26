# Parallax for KallistiOS ##version##
#
# Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/02/27 04:25:41 bardtx Exp $

# C sources
OBJS_C := $(patsubst %.c,%.o,$(wildcard src/*.c))

SUBDIRS =

.PHONY: clib

all: clib

clib: $(OBJS_C)
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libparallax.a $(OBJS_C)

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

clean:
	-rm -f $(OBJS_C) $(OBJS_CPP)

