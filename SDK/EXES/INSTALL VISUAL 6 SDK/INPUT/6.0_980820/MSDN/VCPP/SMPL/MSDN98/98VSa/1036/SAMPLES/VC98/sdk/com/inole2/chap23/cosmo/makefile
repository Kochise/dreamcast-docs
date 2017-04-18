#
# MAKEFILE
# Cosmo Chapter 23
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
OUTFILE = cosmo23.exe
NOOCLIB = 1
NOUILIB = 1

INCLS    = $(TARGET).h resource.h cosmole.h

OBJS1    = $(TARGET).obj client.obj precomp.obj
OBJS2    = document.obj polyline.obj polywin.obj
OBJS3    = dropsrc.obj droptgt.obj iclassf.obj
OBJS4    = figure.obj iperstor.obj idataobj.obj ioleobj.obj
OBJS5    = iperfile.obj
OBJS6    = iipobj.obj iipaobj.obj
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)

RCFILES1 = $(TARGET).ico document.ico about.dlg
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

dropsrc.obj   : dropsrc.cpp  $(INCLS)
droptgt.obj   : droptgt.cpp  $(INCLS)


#Editor level things
polyline.obj  : polyline.cpp $(INCLS) polyline.h
polywin.obj   : polywin.cpp  $(INCLS) polyline.h


#Compound Document Things
iclassf.obj   : iclassf.cpp  $(INCLS)

figure.obj    : figure.cpp   $(INCLS)
iperstor.obj  : iperstor.cpp $(INCLS)
idataobj.obj  : idataobj.cpp $(INCLS)
ioleobj.obj   : ioleobj.cpp  $(INCLS)
iperfile.obj  : iperfile.cpp $(INCLS)

iipobj.obj    : iipobj.cpp   $(INCLS)
iipaobj.obj   : iipaobj.cpp  $(INCLS)
