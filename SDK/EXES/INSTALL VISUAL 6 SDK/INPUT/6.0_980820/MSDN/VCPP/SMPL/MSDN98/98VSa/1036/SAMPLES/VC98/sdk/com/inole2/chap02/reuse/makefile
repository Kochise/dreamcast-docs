#
# MAKEFILE
# COM Reusability Samples, Chapter 2
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = reuse
OUTFILE = reuse.exe

NODOC      = 1
NOPRECOMP  = 1
NOUILIB    = 1
NOOCLIB    = 1
NOCLASSLIB = 1

INCLS    = $(TARGET).h interfac.h

OBJS1    = $(TARGET).obj animal.obj
OBJS2    = koalac.obj koalaa.obj
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
animal.obj    : animal.cpp    $(INCLS) animal.h
koalac.obj    : koalac.cpp    $(INCLS) koalac.h
koalaa.obj    : koalaa.cpp    $(INCLS) koalaa.h
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
