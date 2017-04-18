#
# MAKEFILE
# Inside OLE Utilities Library, including various user interface
# devices and many helper functions used by a variety of samples.
#
# Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for "noisy" operation
!CMDSWITCHES +s

TARGET  = inole
OUTFILE = inole.dll

NOPRECOMP  = 1
DLL        = 1
NODOC      = 1
NOUILIB    = 1
NOCLASSLIB = 1
NOBOOKLIB  = 1
NOOCLIB    = 1

INCLS    = inoledll.h bttncuri.h gizmoint.h statint.h

OBJS1    = $(TARGET).obj
OBJS2    = uieffect.obj xform.obj helpers.obj ansi.obj
OBJS3    = bttncur.obj cursors.obj
OBJS4    = gizmobar.obj gizmoapi.obj gizmo.obj
OBJS5    = stastrip.obj
OBJS6    = ""
OBJS     = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)


RCFILES1 = $(TARGET).rc res\harrows.cur res\help.cur res\larrows.cur
RCFILES2 = res\magnify.cur res\neswarrs.cur res\nodrop.cur res\nwsearrs.cur
RCFILES3 = res\rarrow.cur res\sarrows.cur res\sizebarh.cur res\sizebarv.cur
RCFILES4 = res\splith.cur res\splitv.cur res\tabletop.cur res\varrows.cur
RCFILES5 = res\stdim72.bmp res\stdim96.bmp res\stdim120.bmp
RCFILES  = $(RCFILES1) $(RCFILES2) $(RCFILES3) $(RCFILES4) $(RCFILES5)

!include "..\\inole-a.mak"

#Override some of the things from inole-a.mak
#such as other library dependencies that we don't want

!ifndef WIN16
CL32    = -G3
!else
CL32    = -G2sd -Alfu
!endif

!ifdef CLEAN
goal:   clean
!else
goal:   inole.lib
!endif #CLEAN


!include "..\\inole-b.mak"

#This step does nothing for Win32
$(TARGET).lib: $(TARGET).dll
!ifdef WIN16
    implib $(TARGET).lib win16.def
!endif


##### Dependencies #####

$(TARGET).obj  : $(TARGET).cpp  $(INCLS)

uieffect.obj   : uieffect.cpp   $(INCLS)
xform.obj      : xform.cpp      $(INCLS)
helpers.obj    : helpers.cpp    $(INCLS)
ansi.obj       : ansi.cpp       $(INCLS)

bttncur.obj    : bttncur.c      $(INCLS)
cursors.obj    : cursors.c      $(INCLS)

gizmobar.obj   : gizmobar.c     $(INCLS)
gizmoapi.obj   : gizmoapi.c     $(INCLS)
gizmo.obj      : gizmo.c        $(INCLS)


stastrip.obj   : stastrip.c     $(INCLS)

$(TARGET).res  : $(TARGET).rc   $(INCLS) $(RCFILES)
