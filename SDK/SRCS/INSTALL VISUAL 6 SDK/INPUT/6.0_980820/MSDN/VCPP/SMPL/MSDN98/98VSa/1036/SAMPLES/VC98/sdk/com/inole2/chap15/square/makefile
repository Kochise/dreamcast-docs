#
# MAKEFILE
# Sphere Square Automation Object Chapter 15
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s


TARGET  = square
OUTFILE = square.exe
NODOC   = 1
NOPRECOMP = 1
NOCLASSLIB = 1
NOUILIB = 1

INCLS   = $(TARGET).h isquare.h

OBJS1   = $(TARGET).obj
OBJS2   = ""
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1)

RCFILES = square.tlb
TLBHEAD = /h isquare.h

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
square.tlb    : square.odl
isquare.h     : square.tlb
