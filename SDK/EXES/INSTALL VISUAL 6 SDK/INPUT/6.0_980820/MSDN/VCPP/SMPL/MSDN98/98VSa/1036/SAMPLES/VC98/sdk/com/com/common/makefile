#+---------------------------------------------------------------------------
#
#  Microsoft Windows
#  Copyright (C) Microsoft Corporation, 1994-1997.
#
#  File:        makefile
#
#----------------------------------------------------------------------------

!include <olesampl.mak>

#
#       builds the sdkutil.LIB library
#

OLEFLAGS =

all: sdkutil.lib

clean:
    -del *.lib
    -del *.obj

stablize.obj: stablize.cxx
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) stablize.cxx

altassrt.obj: altassrt.cxx
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) altassrt.cxx

sdkutil.lib: altassrt.obj stablize.obj
    lib -out:sdkutil.lib altassrt.obj stablize.obj
    if not exist ..\lib mkdir ..\lib
    copy sdkutil.lib ..\lib
# Copy the file to the VC++ Lib directory
    copy sdkutil.lib $(MSVCDIR)\lib