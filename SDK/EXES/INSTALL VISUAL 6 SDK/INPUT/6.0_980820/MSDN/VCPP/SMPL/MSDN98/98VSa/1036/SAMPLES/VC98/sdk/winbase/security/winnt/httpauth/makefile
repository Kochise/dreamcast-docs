# ============================================================================
# File: M A K E F I L E
# 
# NMAKE description file for the HTTPAUTH sample
#
# Copyright 1996-1997 Microsoft Corporation.  All Rights Reserved.
# ============================================================================
#
# Usage:    NMAKE DEBUG=1   (build DEBUG exe)
#           NMAKE NODEBUG=1 (build RELEASE exe)
#
# ============================================================================


!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

APP       = HTTPAUTH

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug) -I..\include
LINKFLAGS    = $(linkdebug) $(conflags) /subsystem:console 
APP_OBJS     = httpget.obj httpauth.obj get_sock.obj

# ----------------------------------------------------------------------------
#                          O V E R A L L    G O A L
# ----------------------------------------------------------------------------
            
goal: $(APP).exe


                     
# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

$(APP).exe: $(APP_OBJS)
    @echo Linking ...
     $(link) $(LINKFLAGS) $(APP_OBJS) $(conlibs) -out:$@

# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

{$(SRC_DIR)}.c{}.obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c $<


# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

httpget.obj: httpget.c proto.h

get_sock.obj: get_sock.c proto.h httpauth.h

httpauth.obj: httpauth.c httpauth.h
