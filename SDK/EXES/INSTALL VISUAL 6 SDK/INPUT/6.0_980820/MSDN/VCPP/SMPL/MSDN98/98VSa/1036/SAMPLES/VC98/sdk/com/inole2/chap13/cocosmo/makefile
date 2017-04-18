#
# MAKEFILE
# Component Cosmo Chapter 13
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = cocosmo
OUTFILE = cocos13.exe
NOOCLIB = 1
NOUILIB = 1

INCLS    = $(TARGET).h resource.h

OBJS1    = $(TARGET).obj precomp.obj
OBJS2    = client.obj document.obj
OBJS3    = iadvsink.obj dropsrc.obj droptgt.obj
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3)

RCFILES1 = $(TARGET).ico document.ico about.dlg
RCFILES2 = gizmo72.bmp gizmo96.bmp gizmo120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc $(INCLS) $(RCFILES)

#Application level things
#This rule is to exclude precompiled header use when INITGUIDS defined
$(TARGET).obj : $(TARGET).cpp $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $(DOC) $*.cpp

client.obj    : client.cpp    $(INCLS)

#Document level things
document.obj  : document.cpp  $(INCLS)
iadvsink.obj  : iadvsink.cpp  $(INCLS)
dropsrc.obj   : dropsrc.cpp   $(INCLS)
droptgt.obj   : droptgt.cpp   $(INCLS)
