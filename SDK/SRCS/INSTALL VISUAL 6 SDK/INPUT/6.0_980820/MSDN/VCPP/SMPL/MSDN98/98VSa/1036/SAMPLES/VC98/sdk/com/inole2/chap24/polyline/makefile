#
# MAKEFILE
# Polyline Component Chapter 24
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = polyline
OUTFILE = poly24.dll
DLL     = 1
NODOC   = 1
NOUILIB = 1

INCLS   = $(TARGET).h resource.h ipoly.h

OBJS1   = $(TARGET).obj dllpoly.obj precomp.obj
OBJS2   = ipolylin.obj polywin.obj iconnpt.obj
OBJS3   = iperstor.obj iperstmi.obj idataobj.obj
OBJS4   = ioleobj.obj iviewobj.obj irunobj.obj
OBJS5   = iextconn.obj iipobj.obj iipaobj.obj
OBJS6   = control.obj
OBJS    = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)

RCFILES =

TLBHEAD = /h ipoly.h

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

#This rule is defined separately to avoid precompiled headers where
#INITGUIDS is defined.

dllpoly.obj   : dllpoly.cpp   $(INCLS)
    echo +++++++++
    echo Compiling $*.cpp
    cl -nologo $(CFLAGS) $(DEFS) $*.cpp

$(TARGET).obj : $(TARGET).cpp $(INCLS)
ipolylin.obj  : ipolylin.cpp  $(INCLS)
polywin.obj   : polywin.cpp   $(INCLS)
iconnpt.obj   : iconnpt.cpp   $(INCLS)
iperstor.obj  : iperstor.cpp  $(INCLS)
idataobj.obj  : idataobj.cpp  $(INCLS)
iperstmi.obj  : iperstmi.cpp  $(INCLS)
ioleobj.obj   : ioleobj.cpp   $(INCLS)
iviewobj.obj  : iviewobj.cpp  $(INCLS)
irunobj.obj   : irunobj.cpp   $(INCLS)
iextconn.obj  : iextconn.cpp  $(INCLS)
iipobj.obj    : iipobj.cpp    $(INCLS)
iipaobj.obj   : iipaobj.cpp   $(INCLS)
control.obj   : control.cpp   $(INCLS)
$(TARGET).res : $(TARGET).rc  $(RCFILES) resource.h

ipoly.h       : polyline.tlb  polyline.tlb
polyline.tlb  : polyline.odl
