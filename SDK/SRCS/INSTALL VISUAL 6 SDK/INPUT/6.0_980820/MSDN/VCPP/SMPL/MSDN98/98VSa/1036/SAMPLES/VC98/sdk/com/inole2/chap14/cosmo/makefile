#
# MAKEFILE
# Cosmo Chapter 14
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = cosmo
OUTFILE = cosmo14.exe
NOOCLIB = 1
NOUILIB = 1

TLBHEAD = /h icosmo.h
INCLS   = $(TARGET).h resource.h icosmo.h

OBJS1    = $(TARGET).obj client.obj precomp.obj
OBJS2    = iclassf.obj document.obj
OBJS3    = polyline.obj polywin.obj
OBJS4    = autobase.obj autoapp.obj
OBJS5    = autofigs.obj autofig.obj
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)

RCFILES1 = $(TARGET).ico document.ico about.dlg cosmo000.tlb
RCFILES2 = gizmo72.bmp gizmo96.bmp gizmo120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc $(INCLS) $(RCFILES)

#Application level things
#The file that does #define INITGUIDS should not use precompiled headers.
$(TARGET).obj : $(TARGET).cpp   $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $(DOC) $*.cpp

client.obj    : client.cpp   $(INCLS)

#Document level things
document.obj  : document.cpp $(INCLS) polyline.h

#Editor level things
polyline.obj  : polyline.cpp $(INCLS) polyline.h
polywin.obj   : polywin.cpp  $(INCLS) polyline.h

#Automation things
iclassf.obj   : iclassf.cpp  $(INCLS)
autobase.obj  : autobase.cpp $(INCLS)
autoapp.obj   : autoapp.cpp  $(INCLS)
autofigs.obj  : autofigs.cpp $(INCLS)
autofig.obj   : autofig.cpp  $(INCLS)

#Type information
icosmo.h      : cosmo000.tlb
