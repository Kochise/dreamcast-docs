# ============================================================================
# File: M A K E F I L E
# 
# NMAKE description file for the DFVIEW Docfile viewer sample
#
# Copyright (C) Microsoft Corporation, 1992-1993.  All Rights Reserved.
# ============================================================================
#
# Usage:    NMAKE DEBUG = 1 (build DEBUG exe)
#           NMAKE           (build RELEASE exe)
#
# ============================================================================


!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

APP       = MC

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug)
LINKFLAGS    = $(linkdebug) $(conflags)
APP_OBJS     = mc.obj mcparse.obj mclex.obj mcutil.obj mcout.obj

# ----------------------------------------------------------------------------
#                          O V E R A L L    G O A L
# ----------------------------------------------------------------------------
            
goal: $(APP).exe


                     
# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

$(APP).exe: $(APP_OBJS)
    @echo Linking ...
     $(link) $(LINKFLAGS) $(APP_OBJS) $(conlibs) user32.lib -out:$@

# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

{$(SRC_DIR)}.c{}.obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c $<


# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

mc.obj: mc.c mc.h

mcparse.obj: mcparse.c mc.h

mcout.obj: mcout.c mc.h

mclex.obj: mclex.c mc.h

mcutil.obj: mcutil.c
