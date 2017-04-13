# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = captest.sym
!endif

all: captest.exe $(SYM)

OBJS=		captest.obj dialogs.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

captest.res: captest.rc captest.h captest.dlg captest.rcv captest.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) captest.rc


# Update the object file if necessary

dialogs.obj: dialogs.c captest.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) dialogs.c

captest.obj: captest.c captest.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) captest.c

# Update the executable file if necessary, and if so, add the resource back in.

captest.exe captest.map:  $(OBJS) captest.res
    $(link) $(linkdebug) $(guiflags) -out:captest.exe $(OBJS) captest.res $(guilibs) \
	vfw32.lib winmm.lib -map:$*.map
    
captest.sym:	$*.map
	mapsym $*.map

clean:
    @if exist captest.exe del captest.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
