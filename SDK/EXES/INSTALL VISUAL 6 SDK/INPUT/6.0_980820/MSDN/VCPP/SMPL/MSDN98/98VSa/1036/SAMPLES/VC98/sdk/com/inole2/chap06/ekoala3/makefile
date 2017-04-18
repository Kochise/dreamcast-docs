#
# MAKEFILE
# Koala Object EXE Server Chapter 6
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = ekoala3
OUTFILE = ekoala3.exe

NODOC      = 1
NOUILIB    = 1
NOOCLIB    = 1
NOPRECOMP  = 1
NOCLASSLIB = 1

INCLS   = $(TARGET).h koala.h

OBJS1   = $(TARGET).obj koala.obj
OBJS2   = msgfilt.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES = koala.ico

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
koala.obj     : koala.cpp     $(INCLS)
msgfilt.obj   : msgfilt.cpp   $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
