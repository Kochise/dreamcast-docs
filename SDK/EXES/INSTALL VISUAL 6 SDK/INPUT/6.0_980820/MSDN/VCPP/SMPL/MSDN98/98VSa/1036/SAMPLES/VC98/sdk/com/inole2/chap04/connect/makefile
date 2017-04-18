#
# MAKEFILE
# Connectable Object demonstration, Chapter 4
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = connect
OUTFILE = connect.exe

NODOC      = 1
NOUILIB    = 1
NOOCLIB    = 1
NOCLASSLIB = 1

INCLS    = $(TARGET).h interfac.h object.h

OBJS1    = $(TARGET).obj sink.obj
OBJS2    = object.obj connpt.obj
OBJS3    = precomp.obj
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3)

RCFILES  = $(TARGET).ico

!include "..\\..\\inole-a.mak"
!ifndef WIN16
LIBS     = winmm.lib
!endif
!include "..\\..\\inole-b.mak"

##### Dependencies #####

#This rule is to exclude precompiled header use when INITGUIDS defined
$(TARGET).obj : $(TARGET).cpp $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $*.cpp

sink.obj      : sink.cpp      $(INCLS)
object.obj    : object.cpp    $(INCLS)
connpt.obj    : connpt.cpp    $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
