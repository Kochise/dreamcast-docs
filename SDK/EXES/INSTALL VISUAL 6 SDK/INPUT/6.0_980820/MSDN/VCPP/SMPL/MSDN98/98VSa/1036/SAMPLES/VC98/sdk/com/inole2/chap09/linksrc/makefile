#
# MAKEFILE
# Link Source Server Chapter 9
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

!ifdef WIN16
!ERROR This sample only compiles and runs under Win32
!endif

TARGET  = linksrc
OUTFILE = linksrc.exe
NODOC      = 1
NOUILIB    = 1
NOOCLIB    = 1
NOCLASSLIB = 1

INCLS   = $(TARGET).h objects.h

OBJS1   = $(TARGET).obj precomp.obj fileobj.obj
OBJS2   = contitem.obj simpitem.obj
OBJS3   = iolecont.obj idescrip.obj
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2) $(OBJS3)

RCFILES =

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
    echo +++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $*.cpp


fileobj.obj   : fileobj.cpp   $(INCLS)
contitem.obj  : contitem.cpp  $(INCLS)
simpitem.obj  : simpitem.cpp  $(INCLS)
iolecont.obj  : iolecont.cpp  $(INCLS)
idescrip.obj  : idescrip.cpp  $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
