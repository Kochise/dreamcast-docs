#
# MAKEFILE
# Cosmo Chapter 1
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
OUTFILE = cosmo01.exe
NOUILIB = 1
NOOCLIB = 1

INCLS    = $(TARGET).h resource.h

OBJS1    = $(TARGET).obj client.obj precomp.obj
OBJS2    = document.obj
OBJS3    = polyline.obj polywin.obj
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3)

RCFILES1 = $(TARGET).ico document.ico about.dlg
RCFILES2 = gizmo72.bmp gizmo96.bmp gizmo120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc $(INCLS) $(RCFILES)

#Application level things
$(TARGET).obj : $(TARGET).cpp $(INCLS)
client.obj    : client.cpp    $(INCLS)

#Document level things
document.obj  : document.cpp $(INCLS) polyline.h

#Editor level things
polyline.obj  : polyline.cpp $(INCLS) polyline.h
polywin.obj   : polywin.cpp  $(INCLS) polyline.h
