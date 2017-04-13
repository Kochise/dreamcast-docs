# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = langplay.sym
!endif

all: langplay.exe $(SYM)

OBJS= langplay.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

langplay.res: langplay.rc langplay.h langplay.rcv langplay.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) langplay.rc


# Update the object file if necessary

langplay.obj: langplay.c langplay.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) langplay.c


# Update the executable file if necessary, and if so, add the resource back in.

langplay.exe langplay.map:  $(OBJS) langplay.res
    $(link) $(linkdebug) $(guilflags) -out:langplay.exe $(OBJS) langplay.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map
    
langplay.sym:	$*.map
	mapsym $*.map

clean:
    @if exist langplay.exe del langplay.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib

