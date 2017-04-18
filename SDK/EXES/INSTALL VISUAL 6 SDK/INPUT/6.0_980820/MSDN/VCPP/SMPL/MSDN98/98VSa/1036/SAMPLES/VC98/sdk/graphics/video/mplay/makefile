# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = mplay.sym
!endif

all: mplay.exe $(SYM)

OBJS= mplay.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

mplay.res: mplay.rc mplay.h mplay.rcv mplay.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) mplay.rc


# Update the object file if necessary

mplay.obj: mplay.c mplay.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) mplay.c


# Update the executable file if necessary, and if so, add the resource back in.

mplay.exe mplay.map:  $(OBJS) mplay.res
    $(link) $(linkdebug) $(guilflags) -out:mplay.exe $(OBJS) mplay.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map
    
mplay.sym:	$*.map
	mapsym $*.map

clean:
    @if exist mplay.exe del mplay.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib

