#
# MAKEFILE
# C and C++ Enumerators Chapter 2
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = enumrect
OUTFILE = enumrect.exe

NODOC      = 1
NOPRECOMP  = 1
NOUILIB    = 1
NOOCLIB    = 1
NOCLASSLIB = 1

INCLS    = $(TARGET).h ienum.h

OBJS1    = $(TARGET).obj
OBJS2    = enumcpp.obj enumc.obj
OBJS3    = ""
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2)

RCFILES  = $(TARGET).ico

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
enumcpp.obj   : enumcpp.cpp   $(INCLS)
enumc.obj     : enumc.c       $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
