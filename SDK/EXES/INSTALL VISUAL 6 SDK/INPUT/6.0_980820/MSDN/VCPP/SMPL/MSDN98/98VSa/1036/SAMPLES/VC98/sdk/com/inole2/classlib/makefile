#
# MAKEFILE
# Sample Code Class Libraries
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for "noisy" operation
!CMDSWITCHES +s

!ifdef SDI
TARGET  = classSDI
OUTFILE = classSDI.lib
!else
TARGET  = classMDI
OUTFILE = classMDI.lib
!endif

NOPRECOMP = 1

INCLS   = classlib.h classres.h

OBJS1   = cstrtabl.obj chourgls.obj
OBJS2   = cwindow.obj cframe.obj framewin.obj
OBJS3   = cclient.obj cdocumnt.obj docwin.obj
OBJS4   = chatch.obj ctoolbar.obj cstatlin.obj
OBJS5   =
OBJS6   =
OBJS    = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)

!include "..\\inole-a.mak"

#Create a library
$(TARGET).lib : $(OBJS)
    echo ++++++++++
    echo Creating $@
    if exist $(OUTFILE) del  $(OUTFILE)

!ifndef WIN16
    echo -out:$(OUTFILE)            > classlib.lrf
    echo *.obj                     >> classlib.lrf
!else
    echo $(OUTFILE)                 > classlib.lrf
    echo y                         >> classlib.lrf
    type files.lst                 >> classlib.lrf
    echo nul                       >> classlib.lrf
!endif

    lib  @classlib.lrf
    if exist classlib.lrf del classlib.lrf


##### Dependencies #####

cstrtabl.obj  : cstrtabl.cpp $(INCLS)
chourgls.obj  : chourgls.cpp $(INCLS)

cwindow.obj   : cwindow.cpp  $(INCLS)

cframe.obj    : cframe.cpp   $(INCLS)
framewin.obj  : framewin.cpp $(INCLS)

cclient.obj   : cclient.cpp  $(INCLS)

cdocumnt.obj  : cdocumnt.cpp $(INCLS)
docwin.obj    : docwin.cpp   $(INCLS)

chatch.obj    : chatch.cpp   $(INCLS)

ctoolbar.obj  : ctoolbar.cpp $(INCLS)
cstatlin.obj  : cstatlin.cpp $(INCLS)
