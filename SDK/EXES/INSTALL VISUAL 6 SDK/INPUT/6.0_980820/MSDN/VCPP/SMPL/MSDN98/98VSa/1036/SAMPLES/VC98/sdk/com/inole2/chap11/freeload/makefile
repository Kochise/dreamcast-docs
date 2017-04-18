#
# MAKEFILE
# Freeloader Chapter 11
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = freeload
OUTFILE = freeload.exe

NOUILIB = 1
NOOCLIB = 1

INCLS    = $(TARGET).h resource.h

OBJS1    = $(TARGET).obj precomp.obj
OBJS2    = client.obj document.obj
OBJS3    = ""
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2)

RCFILES1 = app.ico document.ico about.dlg
RCFILES2 = stdgz72.bmp stdgz96.bmp stdgz120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc $(INCLS) $(RCFILES)

$(TARGET).obj : $(TARGET).cpp    $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $(DOC) $*.cpp


client.obj    : client.cpp    $(INCLS)
document.obj  : document.cpp  $(INCLS)
