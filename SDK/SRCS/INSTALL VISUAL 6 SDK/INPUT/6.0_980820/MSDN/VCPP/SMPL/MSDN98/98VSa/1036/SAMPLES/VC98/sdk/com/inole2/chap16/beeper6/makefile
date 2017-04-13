#
# MAKEFILE
# Beeper Object #6 with Property Pages Chapter 16
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = beeper
OUTFILE = dbeeper6.dll
DLL     = 1
NODOC   = 1
NOUILIB = 1
NOCLASSLIB = 1

INCLS   = $(TARGET).h beeper.h ibeeper.h

OBJS1   = dbeeper.obj precomp.obj
OBJS2   = $(TARGET).obj connpt.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES =

TLBHEAD = /h ibeeper.h

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

#Application level things
#The file that does #define INITGUIDS should not use precompiled headers.
dbeeper.obj : dbeeper.cpp   $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $(DOC) $*.cpp

$(TARGET).obj : $(TARGET).cpp $(INCLS)
beeper.obj    : beeper.cpp    $(INCLS)
connpt.obj    : connpt.cpp    $(INCLS)

beeper.res    : beeper.rc     $(INCLS) $(RCFILES)
ibeeper.h     : beep0000.tlb beep0007.tlb

#This rule builds other type libraries without generating ibeeper.h
beep0007.tlb  : beep0007.odl
    echo ++++++++++
    echo Compiling $*.odl
    $(WX) mktyplib /nologo /nocpp /o $*.log /tlb $*.tlb $*.odl
