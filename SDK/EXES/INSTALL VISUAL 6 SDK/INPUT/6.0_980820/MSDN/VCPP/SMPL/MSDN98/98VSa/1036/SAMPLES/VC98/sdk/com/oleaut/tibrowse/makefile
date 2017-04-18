####
#makefile - makefile for tibrowse.exe
#
#       Copyright (C) 1992-1997, Microsoft Corporation
#
#Purpose:
#  Builds the OLE 2.0 sample IDispatch server, tibrowse.exe.
#
#
#  Usage: NMAKE                 ; build with defaults
#     or: NMAKE option          ; build with the given option(s)
#     or: NMAKE clean           ; erase all compiled files
#
#     option:
#         dev = [win16 | win32] ; dev=win32 is the default
#         DEBUG=[0|1]           ; DEBUG=1 is the default
#
#Notes:
#  This makefile assumes that the PATH, INCLUDE and LIB environment
#  variables are setup properly.
#
##############################################################################


##########################################################################
#
# Default Settings
#

!if "$(dev)" == ""
dev = win32
!endif

!if !("$(dev)" == "win16" || "$(dev)" == "win32")
!error Invalid dev option, choose from [win16 | win32]
!endif

!if "$(dev)" == "win16"
TARGET  = WIN16
!endif

!if "$(dev)" == "win32"
TARGET  = WIN32
!endif

!ifdef NODEBUG
DEBUG = 0
!endif

!if "$(DEBUG)" == "0"
NODEBUG = 1
!endif

!if "$(DEBUG)" == ""
DEBUG = 1
!endif


##########################################################################
#
# WIN16 Settings
#
!if "$(TARGET)" == "WIN16"

CC   = cl
LINK = link

RCFLAGS = -dWIN16
CFLAGS = -c -W3 -AM -GA -GEs -DWIN16
LINKFLAGS = /NOD /NOI /BATCH /ONERROR:NOEXE

LIBS = libw.lib mlibcew.lib

!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS) -Od -Zi -D_DEBUG $(CL)
LINKFLAGS = $(LINKFLAGS) /COD
!else
CFLAGS = $(CFLAGS) -Ox $(CL)
LINKFLAGS = $(LINKFLAGS) /FAR /PACKC
!endif
!endif


##########################################################################
#
# WIN32 Settings
#
!if "$(TARGET)" == "WIN32"

!include <olesampl.mak>

CC = $(cc)
CFLAGS = $(cflags) $(cvarsmt) -DINC_OLE2 $(cdebug)

!ifndef NODEBUG
CFLAGS = $(CFLAGS) -D_DEBUG
!endif

LINK = $(link)
LINKFLAGS = $(linkdebug) $(guilflags)
RCFLAGS = -DWIN32

!endif


##########################################################################
#
# Build rules
#

.cpp.obj:
    @echo Compiling $<...
    $(CC) $<

.c.obj:
    @echo Compiling $<...
    $(CC) $<


##########################################################################
#
# Application Settings
#

APPS = tibrowse


!if "$(TARGET)" == "WIN16"
LIBS = ole2.lib compobj.lib ole2disp.lib typelib.lib commdlg.lib $(LIBS)
!endif
!if "$(TARGET)" == "WIN32"
LIBS = $(olelibsmt)
!endif

OBJS = \
         tibrowse.obj


##########################################################################
#
# Default Goal
#

goal : setflags $(APPS).exe

setflags :
        set CL=$(CFLAGS)


##########################################################################
#
# Clean (erase) generated files
#
clean :
    if exist *.obj       del *.obj
    if exist $(APPS).exe del $(APPS).exe
    if exist $(APPS).map del $(APPS).map
    if exist $(APPS).res del $(APPS).res
    if exist *.pdb       del *.pdb


##########################################################################
#
# Application Build (WIN16 Specific)
#

!if "$(TARGET)" == "WIN16"
$(APPS).exe : $(OBJS) $(APPS).def $(APPS).res $(APPS).ico
        link $(LINKFLAGS) @<<
$(OBJS),
$@,,
$(LIBS),
$(APPS).def
<<
        rc -k -t $(APPS).res $@
!endif


##########################################################################
#
# Application Build (WIN32 Specific)
#
!if "$(TARGET)" == "WIN32"
$(APPS).exe : $(OBJS) $(APPS).def $(APPS).res $(APPS).ico
      $(LINK) @<<
        $(LINKFLAGS)
        -out:$@
        -map:$*.map
        $(OBJS)
        $(APPS).res
        $(LIBS)
<<
!endif


##########################################################################
#
# Application Build (Common)
#

$(APPS).res : $(APPS).rc
        rc $(RCFLAGS) -r -fo$@ $?


##########################################################################
#
# Dependencies
#


tibrowse.obj : tibrowse.cpp resource.h
    $(CC) tibrowse.cpp
