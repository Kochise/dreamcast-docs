# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993, 1994  Microsoft Corporation.  All Rights Reserved.


# There are two sets of tools options and build rules below: one for 32-bit
# builds and one for 16-bit builds. In addition there are rules for debug
# and non-debug builds.
#     To distinguish between 32-bit and 16-bit builds, define MAK16.
#     To distinguish between debug and non-debug builds, define _NODEBUG.
#
# To execute a build, refer to the following table:
#
#     Build Type                Command line
#     -----------------         ----------------------------
#     32-bit, debug             nmake
#     32-bit, non-debug         nmake "_NODEBUG=1"
#     16-bit, debug             nmake "MAK16=1"
#     16-bit, non-debug         nmake "_NODEBUG=1" "MAK16=1"
#



PROJ = Listview

all: $(PROJ).exe 


#--------------------------------------------------------------------------
# Files in project

# **TODO** Add any global dependencies to GLOBAL_DEP
# **TODO** Add any resource dependencies to RC_DEP

PROJ_OBJS  = Listview.obj
GLOBAL_DEP = Listview.h
RC_DEP     = Listview.h 

LIBS   =
LIBS32 = user32.lib gdi32.lib kernel32.lib version.lib libc.lib comctl32.lib


#--------------------------------------------------------------------------
# Dependencies

# **TODO** Add file dependences to build any new files listed above

Listview.obj:  Listview.c  $(GLOBAL_DEP) Listview.h

#--------------------------------------------------------------------------
# Note:  You should not need to change anthing below this line unless you
#        want to modify the compiler options, etc.  For normal project
#        maintenance, all changes are done above.

# Choose either a 32-bit build or a 16-bit build

!ifndef MAK16
# 32-bit specific build information

#--------------------------------------------------------------------------
# 32-bit Tools Options

!ifdef _NODEBUG
# Non-debugging options

!MESSAGE 32-bit Non-debugging build

CFLAGS    = /c /W3 /ML /Ox /nologo
CDEFINES  = /D"_X86_" /D"NDEBUG" /D"_WINDOWS" /D"WIN32"
LFLAGS    = /NOLOGO /SUBSYSTEM:windows
RCFLAGS   = /r
RCDEFINES = /dNDEBUG /d, /dWIN32
MAPFILE   =

!else
# Debugging options

!MESSAGE 32-bit Debugging build

CFLAGS    = /c /W3 /ML /Od /Zi /Fd$(PROJ).pdb /nologo
CDEFINES  = /D"_X86_" /D"_DEBUG" /D"_WINDOWS" /D"WIN32"
LFLAGS    = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows
RCFLAGS   = /r
RCDEFINES = /d_DEBUG /d, /dWIN32
MAPFILE   = /map:$(PROJ).map

!endif

#--------------------------------------------------------------------------
# 32-bit Build Rules

$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res
    link @<<
    $(LFLAGS)
    $(BASE_OBJS) $(PROJ_OBJS)
    /out:$(PROJ).exe
    $(MAPFILE)
    $(PROJ).res
    $(LIBS32) $(LIBS)
<<


!else
# 16-bit specific build information

#--------------------------------------------------------------------------
# 16-bit Tools Options

!ifdef _NODEBUG
# Non-debugging options

!MESSAGE 16-bit Non-debugging build

CFLAGS    = /c /AM /G2A /W3 /Zpe /O1 /nologo
CDEFINES  = /DNDEBUG /DWIN16
LFLAGS    = /NOLOGO /ONERROR:NOEXE /NOD /NOE /AL:16
RCFLAGS   = /r
RCDEFINES = /dNDEBUG /d,
MAPFILE   = nul

!else
# Debugging options

!MESSAGE 16-bit Debugging build

CFLAGS    = /c /f- /AM /G2A /W3 /Zipe /Od /Fd$(PROJ).pdb /nologo
CDEFINES  = /D_DEBUG /DWIN16
LFLAGS    = /NOLOGO /ONERROR:NOEXE /NOD /NOE /CO /AL:16
RCFLAGS   = /r
RCDEFINES = /d_DEBUG /d,
MAPFILE   = $(PROJ).map

!endif

#--------------------------------------------------------------------------
# 16-bit Build Rules

$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(PROJ).res $(PROJ).def
    link @<<
    $(LFLAGS) $(BASE_OBJS) $(PROJ_OBJS)
    $(PROJ).exe
    $(MAPFILE)
    $(LIBS16) $(LIBS)
    $(PROJ).def
<<
    rc $(PROJ).RES $(PROJ).exe

!endif


#--------------------------------------------------------------------------
# Inference rules common to both 16-bit and 32-bit builds

.c.obj:
    cl @<<
    $(CFLAGS) $(CDEFINES) $<
<<


#--------------------------------------------------------------------------
# Build rules common to both 16-bit and 32-bit builds

#$(PROJ).bsc: $(SBRS)
#    bscmake @<<
#    /o$(PROJ).bsc $(SBRS)
#<<

$(PROJ).res: $(PROJ).rc $(RC_DEP)
    rc $(RCFLAGS) $(RCDEFINES) /fo$(PROJ).res $(PROJ).rc


#--------------------------------------------------------------------------
# Rules for cleaning out those old files

clean:
    del *.bak
    del *.pdb
    del *.obj
    del *.res
    del *.exp
    del *.map
    del *.sbr
    del *.bsc

cleaner: clean
    del *.exe
    del *.lib
    del *.dll

# End of file -------------------------------------------------------------
