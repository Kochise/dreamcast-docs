#
# MAKEFILE
# Cosmo Handler Chapter 19
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = hcosmo
OUTFILE = hcosmo19.dll
DLL     = 1
NODOC   = 1

INCLS   = $(TARGET).h

OBJS1   = $(TARGET).obj figure.obj iperstor.obj precomp.obj
OBJS2   = ioleobj.obj iviewobj.obj iadvsink.obj
OBJS3   = ""
OBJS4   = ""
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2)

RCFILES =

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).obj : $(TARGET).cpp   $(INCLS)
    echo +++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $*.cpp

figure.obj    : figure.cpp    $(INCLS)
iperstor.obj  : iperstor.cpp  $(INCLS)
ioleobj.obj   : ioleobj.cpp   $(INCLS)
iviewobj.obj  : iviewobj.cpp  $(INCLS)
iadvsink.obj  : iadvsink.cpp  $(INCLS)
$(TARGET).res : $(TARGET).rc  $(RCFILES)
