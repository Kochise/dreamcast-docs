#+---------------------------------------------------------------------------
#
#  Microsoft Windows
#  Copyright (C) Microsoft Corporation, 1994-1995.
#
#  File:        makefile
#
#----------------------------------------------------------------------------

!include <olesampl.mak>

#
#       Makefile for OLE Sample DFView
#
#       builds DFView.EXE
#

OLEFLAGS = -I ..\idl -I ..\winhlprs
LINK = $(link)
LINKFLAGS = $(linkdebug) $(guilflags)
RCFLAGS = -DWIN32

OBJS = winmain.obj mwclass.obj strmvwr.obj about.obj bitmaps.obj message.obj
LIBS = $(olelibsmt) ..\..\com\winhlprs\winhlprs.lib

all: DFView.exe

clean:
    -del *.obj
    -del dfv.res
    -del DFView.map
    -del DFView.exe

winmain.obj: winmain.cxx        \
        dfv.h                   \
        mwclass.h               \
        message.h               \
        ..\..\com\winhlprs\cwindow.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

mwclass.obj: mwclass.cxx        \
        dfv.h                   \
        mwclass.h               \
        about.h                 \
        strmvwr.h               \
        bitmaps.h               \
        message.h               \
        ..\..\com\winhlprs\cdialog.h   \
        ..\..\com\winhlprs\cwindow.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

strmvwr.obj: strmvwr.cxx        \
        dfv.h                   \
        strmvwr.h               \
        message.h               \
        mwclass.h               \
        ..\..\com\winhlprs\cwindow.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

about.obj: about.cxx            \
        about.h                 \
        ..\..\com\winhlprs\cdialog.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

bitmaps.obj: bitmaps.cxx        \
        bitmaps.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

message.obj: message.cxx        \
        message.h
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $*.cxx

dfv.res: dfv.rc dfv.ico dfv.dlg document.bmp folder.bmp dfv.h
    rc $(RCFLAGS) -r -fo$@ $*.rc

DFView.exe: $(OBJS) dfv.res
    $(LINK) @<<
        $(LINKFLAGS)
        -out:$@
        -map:$*.map
        $(OBJS)
        dfv.res
        $(LIBS)
<<
