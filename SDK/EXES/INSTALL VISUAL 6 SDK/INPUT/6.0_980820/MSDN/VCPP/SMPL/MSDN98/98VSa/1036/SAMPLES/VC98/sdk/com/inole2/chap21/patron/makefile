#
# MAKEFILE
# Patron Chapter 21
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
OUTFILE = patron21.exe

INCLS    = $(TARGET).h pages.h resource.h tenant.h

OBJS1    = $(TARGET).obj client.obj document.obj precomp.obj
OBJS2    = print.obj pages.obj pagewin.obj page.obj
OBJS3    = pagemous.obj tenant.obj dragdrop.obj
OBJS4    = droptgt.obj dropsrc.obj iclisite.obj iadvsink.obj
OBJS5    = iuilink.obj iolecont.obj iperfile.obj iclassf.obj
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)

RCFILES1 = $(TARGET).ico document.ico about.dlg print.dlg
RCFILES2 = gizmo72.bmp gizmo96.bmp gizmo120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc $(INCLS) $(RCFILES)

#Application level things
#The file that does #define INITGUIDS should not use precompiled headers.
$(TARGET).obj : $(TARGET).cpp $(INCLS)
    echo ++++++++++
    echo Compiling $*.cpp
    cl $(CFLAGS) $(DEFS) $(DOC) $*.cpp

client.obj    : client.cpp    $(INCLS)
iclassf.obj   : iclassf.cpp   $(INCLS)

#Document level things
document.obj  : document.cpp  $(INCLS)
print.obj     : print.cpp     $(INCLS)
iuilink.obj   : iuilink.cpp   $(INCLS)
iperfile.obj  : iperfile.cpp  $(INCLS)
iolecont.obj  : iolecont.cpp  $(INCLS)

#Editor level things
pages.obj     : pages.cpp     $(INCLS)
pagewin.obj   : pagewin.cpp   $(INCLS)
page.obj      : page.cpp      $(INCLS)
pagemous.obj  : pagemous.cpp  $(INCLS)

dragdrop.obj  : dragdrop.cpp  $(INCLS)
droptgt.obj   : droptgt.cpp   $(INCLS)
dropsrc.obj   : dropsrc.cpp   $(INCLS)

tenant.obj    : tenant.cpp    $(INCLS)
iclisite.obj  : iclisite.cpp  $(INCLS)
iadvsink.obj  : iadvsink.cpp  $(INCLS)
