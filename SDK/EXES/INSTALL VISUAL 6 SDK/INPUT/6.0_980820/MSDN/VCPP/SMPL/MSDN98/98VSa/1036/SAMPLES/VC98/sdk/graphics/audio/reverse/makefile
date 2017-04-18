# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = reverse.sym
!endif

all: reverse.exe $(SYM)

OBJS=		reverse.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

reverse.res: reverse.rc reverse.rcv strings.h strings.rc reverse.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) reverse.rc


# Update the object file if necessary

reverse.obj: reverse.c reverse.h strings.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) reverse.c


# Update the executable file if necessary, and if so, add the resource back in.

reverse.exe reverse.map:  $(OBJS) reverse.res
    $(link) $(linkdebug) $(guiflags) -out:reverse.exe $(OBJS) reverse.res $(guilibs) \
    winmm.lib -map:$*.map
    
reverse.sym:	$*.map
	mapsym $*.map

clean:
    @if exist reverse.exe del reverse.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
