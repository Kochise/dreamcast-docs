# KOS libc ##version##
#
# libcrt Makefile
# Copyright (C)2003 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/07/15 07:35:21 bardtx Exp $

OBJS	:= crt0.o

all: $(OBJS)
	cp $(OBJS) $(KOS_BASE)/lib

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

clean:
	rm -f $(OBJS)
