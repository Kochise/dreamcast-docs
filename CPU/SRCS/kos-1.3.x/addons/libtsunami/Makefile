# Tsunami for KallistiOS ##version##
#
# Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/02/27 04:25:42 bardtx Exp $

# Main sources
OBJS_MAIN := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

# Drawables
OBJS_DRW := $(patsubst %.cpp,%.o,$(wildcard src/drawables/*.cpp))

# Animations
OBJS_ANIMS := $(patsubst %.cpp,%.o,$(wildcard src/anims/*.cpp))

# Triggers
OBJS_TRIGS := $(patsubst %.cpp,%.o,$(wildcard src/triggers/*.cpp))

OBJS := $(OBJS_MAIN) $(OBJS_DRW) $(OBJS_ANIMS) $(OBJS_TRIGS)

SUBDIRS =

.PHONY: cpplib

all: cpplib

cpplib: $(OBJS)
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libtsunami.a $(OBJS)

# Grab the shared Makefile pieces
include $(KOS_BASE)/Makefile.prefab

clean:
	-rm -f $(OBJS)

