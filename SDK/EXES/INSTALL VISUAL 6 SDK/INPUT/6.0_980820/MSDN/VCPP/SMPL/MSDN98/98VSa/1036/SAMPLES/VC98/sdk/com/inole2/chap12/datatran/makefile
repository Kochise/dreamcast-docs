#
# MAKEFILE
# Data Transfer Object DLL Chapter 12
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = datatran
OUTFILE = datatran.dll
DLL     = 1
NODOC   = 1
PCHINC  = dataobj.h
NOCLASSLIB = 1
NOUILIB = 1

INCLS   = $(TARGET).h dataobj.h

OBJS1   = $(TARGET).obj dataobj.obj precomp.obj
OBJS2   = idataobj.obj ienumfe.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES =

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp $(INCLS)
    echo +++++++++
    echo Compiling $*.cpp
    cl -nologo $(CFLAGS) $(DEFS) $*.cpp

dataobj.obj   : dataobj.cpp   $(INCLS)
idataobj.obj  : idataobj.cpp  $(INCLS)
ienumfe.obj   : ienumfe.cpp   $(INCLS)
$(TARGET).res : $(TARGET).rc  $(INCLS) $(RCFILES)
