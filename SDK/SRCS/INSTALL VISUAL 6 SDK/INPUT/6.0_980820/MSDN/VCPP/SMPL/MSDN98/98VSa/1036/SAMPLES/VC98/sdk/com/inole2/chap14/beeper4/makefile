#
# MAKEFILE
# Beeper Automation Object #4 Chapter 14
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
!MESSAGE WARNING:  This sample will only compile with OLE 2.02
!endif

TARGET  = dbeeper
OUTFILE = dbeeper4.dll
DLL     = 1
NODOC   = 1
NOPRECOMP = 1
NOUILIB = 1
NOCLASSLIB = 1

INCLS   = $(TARGET).h beeper.h ibeeper.h

OBJS1   = $(TARGET).obj beeper.obj
OBJS2   = ""
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1)

RCFILES =

TLBHEAD = /h ibeeper.h

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
beeper.obj    : beeper.cpp    $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
ibeeper.h     : beep0000.tlb
