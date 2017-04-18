# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: proclist.exe

USE_UNICODE=0

!if $(USE_UNICODE)
UNICODE_DEFINES=-DUNICODE -D_UNICODE
conflags = $(lflags) -subsystem:console,$(APPVER) -entry:wmainCRTStartup
!else
UNICODE_DEFINES=
!endif

proclist.obj: proclist.c
    $(cc) $(cdebug) $(cflags) $(UNICODE_DEFINES) $(cvars) proclist.c

proclist.res: proclist.rc
    $(rc) $(rcflags) $(rcvars) proclist.rc

proclist.exe: proclist.obj proclist.res
    $(link) $(conflags) -out:proclist.exe proclist.obj proclist.res $(conlibs) pdh.lib
