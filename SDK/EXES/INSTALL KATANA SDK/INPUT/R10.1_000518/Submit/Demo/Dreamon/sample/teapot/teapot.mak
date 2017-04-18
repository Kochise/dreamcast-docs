#------------------------------------------------------------------------------
# Teapot.mak
# Assumes that you have SDK8 installed and environment variables setup
#------------------------------------------------------------------------------

PROJECT         = teapot

PROJECT_SRC    = \
        test.c\
        sbinit.c\
        model.c\
        t009.c\
        sndutls.c\
        global32.src

PROJECT_LIBS    = ..\..\lib\ginsu.lib,$(KATANA_ROOT)\lib\nindows.lib,$(KATANA_ROOT)\lib\sg_sd.lib

DEBUG           = TRUE
#LIST            = TRUE
BIN             = TRUE
GFXLIB		= NINJA

include ..\katana.inc
