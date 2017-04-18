#
# MAKEFILE
# QueryInterface and Multiple Interface Samples, Chapter 2
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = query
OUTFILE = query.exe

NODOC      = 1
NOPRECOMP  = 1
NOUILIB    = 1
NOOCLIB    = 1
NOCLASSLIB = 1

INCLS    = $(TARGET).h interfac.h object1.h object2.h object3.h

OBJS1    = $(TARGET).obj object1.obj
OBJS2    = object2.obj object3.obj
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
object1.obj   : object1.cpp   $(INCLS)
object2.obj   : object2.cpp   $(INCLS)
object3.obj   : object3.cpp   $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
