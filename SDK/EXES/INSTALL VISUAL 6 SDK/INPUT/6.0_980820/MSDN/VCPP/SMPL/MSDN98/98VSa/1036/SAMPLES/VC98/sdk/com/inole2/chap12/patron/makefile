#
# MAKEFILE
# Patron Chapter 12
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
OUTFILE = patron12.exe
NOOCLIB = 1

INCLS    = $(TARGET).h pages.h resource.h

OBJS1    = $(TARGET).obj client.obj precomp.obj
OBJS2    = document.obj print.obj pages.obj
OBJS3    = pagewin.obj page.obj pagemous.obj
OBJS4    = tenant.obj
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)

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
document.obj  : document.cpp  $(INCLS) pages.h
print.obj     : print.cpp     $(INCLS) pages.h

#Editor level things
pages.obj     : pages.cpp     $(INCLS) pages.h
pagewin.obj   : pagewin.cpp   $(INCLS) pages.h
page.obj      : page.cpp      $(INCLS) pages.h
pagemous.obj  : pagemous.cpp  $(INCLS) pages.h
tenant.obj    : tenant.cpp    $(INCLS) pages.h
