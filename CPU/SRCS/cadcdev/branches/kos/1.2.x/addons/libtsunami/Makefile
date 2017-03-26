# Tsunami for KallistiOS ##version##
#
# Makefile
# (c)2002 Dan Potter
#   
# $Id: Makefile,v 1.2 2003/02/27 04:25:42 bardtx Exp $

TARGET := libtsunami.a

# Main sources
OBJS_MAIN := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

# Drawables
OBJS_DRW := $(patsubst %.cpp,%.o,$(wildcard src/drawables/*.cpp))

# Animations
OBJS_ANIMS := $(patsubst %.cpp,%.o,$(wildcard src/anims/*.cpp))

# Triggers
OBJS_TRIGS := $(patsubst %.cpp,%.o,$(wildcard src/triggers/*.cpp))

OBJS := $(OBJS_MAIN) $(OBJS_DRW) $(OBJS_ANIMS) $(OBJS_TRIGS)

# Grab the shared Makefile pieces
include ../Makefile.prefab
