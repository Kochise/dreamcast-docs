# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = movplay1.sym movplay2.sym
!endif

all: movplay1.exe movplay2.exe $(SYM)

OBJ1= movplay1.obj
OBJ2= movplay2.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

movplay.res: movplay.rc movplay.h movplay.rcv movplay.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) movplay.rc


# Update the object file if necessary

movplay1.obj: movplay1.c movplay.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) movplay1.c

movplay2.obj: movplay2.c movplay.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) movplay2.c


# Update the executable file if necessary, and if so, add the resource back in.

movplay1.exe movplay1.map:  $(OBJ1) movplay.res
    $(link) $(linkdebug) $(guillflags) -out:movplay1.exe $(OBJ1) movplay.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map

movplay2.exe movplay2.map:	$(OBJ2) movplay.res
    $(link) $(linkdebug) $(guilflags) -out:movplay2.exe $(OBJ2) movplay.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map
    
movplay1.sym:	$*.map
	mapsym $*.map

movplay2.sym:	$*.map
	mapsym $*.map

clean:
    @if exist movplay1.exe del movplay1.exe
    @if exist movplay2.exe del movplay2.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib

