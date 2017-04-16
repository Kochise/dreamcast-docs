####
#makefile - makefile for client.exe
#
#Purpose:
#  Builds the VtblServer's client, client.exe.
#
#
#  Usage: NMAKE                 ; build with defaults
#     or: NMAKE option          ; build with the given option(s)
#     or: NMAKE clean           ; erase all compiled files
#
#     option:DEBUG=[0 | 1]            ; DEBUG=1 is the default
#             HOST=[ NT | WIN95]      ; HOST=NT (for win32 on NT)
#                                     ; HOST=WIN95 (for win32 on Win95, Win95 is the default)
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

TARGET  = WIN32

!if "$(HOST)" == ""
HOST  = WIN95
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
# WIN32 Settings
#
!if "$(TARGET)" == "WIN32"


WX = 

!ifndef MSTOOLS
!include <olesampl.mak>
!else
!include <$(MSTOOLS)\samples\ole\include\olesampl.mak>
!endif

CC = $(cc)
CFLAGS = $(cflags) $(cvarsmt) -DINC_OLE2 $(cdebug)

!if "$(HOST)" == "NT"
CFLAGS = $(CFLAGS) -DUNICODE
!endif

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

APPS = client

!if "$(TARGET)" == "WIN32"
LIBS = $(ole2libsmt)
!endif

OBJS = client.obj


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
    if exist *.log       del *.log
    if exist *.pdb       del *.pdb


##########################################################################
#
# Application Build (WIN32 Specific)
#
!if "$(TARGET)" == "WIN32"
$(APPS).exe : $(OBJS)
      $(LINK) @<< 
        $(LINKFLAGS) $(conlflags)
        -out:$@ 
        -map:$*.map
        $(OBJS)
        
        $(LIBS)
<<
!endif


##########################################################################
#
# Dependencies
# 
client.obj : client.cpp IVtblServer.h
     $(CC) client.cpp

