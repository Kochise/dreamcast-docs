#
# MAKEFILE
# CLASSLIB Skeleton
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = skel
OUTFILE = skel.exe

NOPRECOMP = 1
NOUILIB   = 1
NOOCLIB   = 1

INCLS    =

OBJS1    = $(TARGET).obj
OBJS2    = ""
OBJS3    = ""
OBJS4    = ""
OBJS5    = ""
OBJS6    = ""
OBJS     = $(OBJS1)

RCFILES1 = app.ico document.ico about.dlg
RCFILES2 = stdgz72.bmp stdgz96.bmp stdgz120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2)

!include "..\\..\\inole-a.mak"
!include "..\\..\\inole-b.mak"

##### Dependencies #####

$(TARGET).res : $(TARGET).rc     $(INCLS) $(RCFILES)

#Application level things
$(TARGET).obj : $(TARGET).cpp    $(INCLS)
