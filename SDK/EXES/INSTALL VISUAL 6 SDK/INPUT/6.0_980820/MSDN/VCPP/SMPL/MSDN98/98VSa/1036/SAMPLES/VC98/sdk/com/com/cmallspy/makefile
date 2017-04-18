#+---------------------------------------------------------------------------
#
#  Microsoft Windows
#  Copyright (C) Microsoft Corporation, 1994 - 1996
#
#  File:        makefile
#
#       Makefile for sample implemention of IMallocSpy
#
#----------------------------------------------------------------------------

!include <olesampl.mak>

all : cmallspy.lib test.exe

clean:
        -del cmallspy.obj
        -del cmallspy.lib

cmallspy.obj : cmallspy.cxx cmallspy.hxx
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $(CFLAGS) cmallspy.cxx

test.obj : test.cxx cmallspy.hxx
    $(cc) $(cvars) $(cflags) $(UFLAGS) $(cdebug) $(OLEFLAGS) $(CFLAGS) test.cxx

cmallspy.lib : cmallspy.obj
    lib $(LFLAGS)            \
        -OUT:cmallspy.lib    \
        -DEBUGTYPE:both      \
        cmallspy.obj

test.exe:  test.obj cmallspy.lib
  $(link) $(linkdebug) $(conflags) -machine:$(CPU) -out:$*.exe $** $(olelibs) $(conlibsmt)

