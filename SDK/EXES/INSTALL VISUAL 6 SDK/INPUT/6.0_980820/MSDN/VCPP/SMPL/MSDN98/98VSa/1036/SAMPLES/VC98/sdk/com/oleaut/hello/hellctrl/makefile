####
#makefile - makefile for hellctrl.exe
#
#       Copyright 1994 - 1997 Microsoft Corporation
#
#Purpose:
#  Builds the Automation controller, hellctrl.exe.
#  By default a 32 bit ANSI application that can run on Win95
#  and NT 3.51 is built.
#
#  Usage: NMAKE                 ; build with default (32 bit ANSI for NT & Win95)
#     or: NMAKE option          ; build with the given option(s)
#     or: NMAKE clean           ; erase all compiled files
#  Use NMAKE clean before re-building with options.
#
#     option: dev = [win16 | win32]    ; dev=win32 is the default
#             DEBUG=[0 | 1]          ; DEBUG=1 is the default
#             HOST=[DOS | NT | WIN95]  ; HOST=DOS 
#                                      ; HOST=NT (for Unicode win32 on NT)
#                                      ; HOST=WIN95 (for ANSI win32 on Win95 & NT)
#                                      ; HOST=WIN95 is the default
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
!ifndef CPU
CPU=i386
!endif


# Change the following dev & HOST settings to compile hellctrl for 16 bit, 
# 32 bit Unicode on NT or 32 bit ANSI on NT & Win95

!if "$(dev)" == ""
dev = win32 
HOST = WIN95
!endif

!if !("$(dev)" == "win16" || "$(dev)" == "win32")
!error Invalid dev option, choose from [win16 | win32]
!endif

!if "$(dev)" == "win16"
TARGET  = WIN16
!if "$(HOST)" == ""
HOST  = DOS
!endif
!endif

!if "$(dev)" == "win32"
TARGET  = WIN32
!if "$(HOST)" == ""
HOST  = WIN95
!endif
!endif

!undef NODEBUG

!if "$(DEBUG)" == "0"
NODEBUG = 1
!endif


##########################################################################
#
# WIN16 Settings
#
!if "$(TARGET)" == "WIN16"

CC   = cl
LINK = link
!if "$(HOST)" == "DOS"
WX   = wx /w 
!else
WX   =
!endif

RCFLAGS = -dWIN16
CFLAGS = -c -W3 -AM -GA -GEs -DWIN16
LINKFLAGS = /NOD /NOI /BATCH /ONERROR:NOEXE

LIBS = libw.lib mlibcew.lib

!ifdef NODEBUG
CFLAGS = $(CFLAGS) -Ox $(CL)
LINKFLAGS = $(LINKFLAGS) /FAR /PACKC
!else
CFLAGS = $(CFLAGS) -Od -Zi -D_DEBUG $(CL)
LINKFLAGS = $(LINKFLAGS) /COD
!endif
!endif


##########################################################################
#
# WIN32 Settings
#
!if "$(TARGET)" == "WIN32"


WX = 

!include <olesampl.mak>

CC = $(cc)
CFLAGS = $(cflags) $(cvarsmt) -DINC_OLE2 $(cdebug)

!if "$(HOST)" == "NT"
CFLAGS = $(CFLAGS) -DUNICODE
!endif

!ifdef NODEBUG
!else
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
APPS = hellctrl

!if "$(TARGET)" == "WIN16"
LIBS = ole2.lib compobj.lib ole2disp.lib typelib.lib commdlg.lib $(LIBS)
!endif
!if "$(TARGET)" == "WIN32"
LIBS = $(ole2libsmt)
!endif

OBJS = hellctrl.obj 


##########################################################################
#
# Default Goal
#

goal : setflags $(APPS).exe

setflags :
    set CL=$(CFLAGS)


##########################################################################
#
# Application Build (WIN16 Specific)
#

!if "$(TARGET)" == "WIN16"
$(APPS).exe : $(OBJS) $(APPS).def $(APPS).res 
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
$(APPS).exe : $(OBJS) $(APPS).def $(APPS).res 
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

hellctrl.obj : hellctrl.cpp hellctrl.h tlb.h
     $(CC) hellctrl.cpp

##########################################################################
#
# Clean (erase) generated files
#
clean :
    if exist *.obj       del *.obj
    if exist $(APPS).map del $(APPS).map
    if exist $(APPS).res del $(APPS).res
    if exist *.pdb       del *.pdb
