#
# MAKEFILE
# Koala Client #2 Chapter 6
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = objuser2
OUTFILE = objuser2.exe

NODOC      = 1
NOOCLIB    = 1
NOPRECOMP  = 1
NOCLASSLIB = 1

INCLS   = $(TARGET).h

OBJS1   = $(TARGET).obj msgfilt.obj
OBJS2   = ""
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1)

RCFILES = $(TARGET).ico

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"


##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
msgfilt.obj   : msgfilt.cpp   $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
