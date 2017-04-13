#
# MAKEFILE
# Patron Chapter 7
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = patron
OUTFILE = patron07.exe
NOOCLIB = 1

INCLS    = $(TARGET).h pages.h resource.h

OBJS1    = $(TARGET).obj client.obj precomp.obj
OBJS2    = document.obj print.obj
OBJS3    = pages.obj pagewin.obj page.obj
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3)

RCFILES1 = $(TARGET).ico document.ico about.dlg print.dlg
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

client.obj    : client.cpp    $(INCLS)

#Document level things
document.obj  : document.cpp  $(INCLS)
print.obj     : print.cpp     $(INCLS)

#Editor level things
pages.obj     : pages.cpp     $(INCLS)
pagewin.obj   : pagewin.cpp   $(INCLS)
page.obj      : page.cpp      $(INCLS)
