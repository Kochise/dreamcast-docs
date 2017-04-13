# Copyright 1996  Microsoft Corporation
#
# Module Name:
#
#    makefile
#
# Abstract:
#
#    Active Directory Sample Code makefile
#
#

!include <win32.mak>

#
# general targets
#

all: adscmd.exe

cleansrc:
    del /q ADsCmd.Exe Main.Obj Util.Obj Enum.Obj Dump.Obj

clean: cleansrc all

#
# adscmd.exe
#

ADsCmd.Exe: main.Obj enum.Obj dump.Obj util.Obj
    $(link) $(ldebug) $(conlflags) -out:$@ $** $(olelibs) ActiveDs.lib ADsIID.lib

.cxx.Obj:
  $(cc) $(cdebug) $(cflags) $(cvars) -out:$@ $*.Cxx

Main.Obj: Main.Cxx Main.Hxx

Util.Obj: Util.Cxx Main.Hxx

Enum.Obj: Enum.Cxx Main.Hxx

Dump.Obj: Dump.Cxx Main.Hxx
