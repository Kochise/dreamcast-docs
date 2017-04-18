#
# MAKEFILE
# Cosmo 1.0 (OLE 1.0) Chapter 18
#
# Copyright (c)1992-1995 Microsoft Corporation, All Rights Reserved
#
# Kraig Brockschmidt, Microsoft
# Internet  :  kraigb@microsoft.com
# Compuserve:  >INTERNET:kraigb@microsoft.com
#

#Add '#' to the next line for 'noisy' operation
!CMDSWITCHES +s

TARGET  = cosmo0
OUTFILE = cosmo0.exe

NODOC     = 1
NOPRECOMP = 1
NOUILIB   = 1
NOOCLIB   = 1
NOBOOKLIB = 1

INCLS   = cosmo.h oleinst.h oleglobl.h polyline.h

OBJS1   = cosmo.obj init.obj polyline.obj misc.obj commdlg.obj file.obj
OBJS2   = fileio.obj clip.obj exit.obj oleobj.obj oleclip.obj
OBJS3   = olemisc.obj olefile.obj oleglobl.obj oleinst.obj oleinit.obj
OBJS4	= oleexit.obj olevtbl.obj olesvr.obj oledoc.obj
OBJS5   = ""
OBJS6   = ""
OBJS    = $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)

RCFILES = cosmo.dlg cosmo.ico

!include "..\\..\\inole-a.mak"

#
# Since this is an OLE 1.0 app, we need to change some of the
# compiler and linker options.
#

!ifndef WIN16
DEFS32  = -DWIN32 -D_X86_=1 -DINC_OLE1 -DMAKEOLESERVER -DSERVERONLY -DMSC
LIBS32A = msvcrt.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib
LIBS32B = ..\..\lib\olesvr32.lib advapi32.lib
LIBS32  = $(LIBS32A) $(LIBS32B)
!else
CL32    = -G2sw -f -AS
DEFS32  = -DWIN16 -DMAKEOLESERVER -DSERVERONLY -DMSC
LIBS32A = libw slibcew commdlg shell
LIBS32B = olesvr
LIBS32  = $(LIBS32A) $(LIBS32B)
!endif


!include "..\\..\\inole-b.mak"


##### Dependencies #####

cosmo1.res   : cosmo1.rc  $(INCLS) $(RCFILES)

cosmo.obj    : cosmo.c    $(INCLS)
init.obj     : init.c     $(INCLS)
polyline.obj : polyline.c $(INCLS)
misc.obj     : misc.c     $(INCLS)
commdlg.obj  : commdlg.c  $(INCLS)
file.obj     : file.c     $(INCLS)
fileio.obj   : fileio.c   $(INCLS)
clip.obj     : clip.c     $(INCLS)
exit.obj     : exit.c     $(INCLS)
oleobj.obj   : oleobj.c   $(INCLS)
oleclip.obj  : oleclip.c  $(INCLS)
olemisc.obj  : olemisc.c  $(INCLS)
olefile.obj  : olefile.c  $(INCLS)
oleglobl.obj : oleglobl.c $(INCLS)
oleinst.obj  : oleinst.c  $(INCLS)
oleinit.obj  : oleinit.c  $(INCLS)
oleexit.obj  : oleexit.c  $(INCLS)
olevtbl.obj  : olevtbl.c  $(INCLS)
olesvr.obj   : olesvr.c   $(INCLS)
oledoc.obj   : oledoc.c   $(INCLS)
