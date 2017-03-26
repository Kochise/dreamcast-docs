# KOS libm ##version##
#
# Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.1 2002/03/04 06:07:39 bardtx Exp $

# math
OBJS_MATH := $(patsubst %.c,%.o,$(wildcard math/*.c))
OBJS      := $(OBJS_MATH)

# common
OBJS_COMMON := $(patsubst %.c,%.o,$(wildcard common/*.c))
OBJS        += $(OBJS_COMMON)

SUBDIRS =

KOS_CFLAGS := $(KOS_CFLAGS) -I$(KOS_BASE)/libm -I$(KOS_BASE)/libm/common -I$(KOS_BASE)/include/newlib-libm-sh4

all: $(OBJS)
	$(KOS_AR) rcs $(KOS_BASE)/lib/$(KOS_ARCH)/libm.a $(OBJS)

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab


