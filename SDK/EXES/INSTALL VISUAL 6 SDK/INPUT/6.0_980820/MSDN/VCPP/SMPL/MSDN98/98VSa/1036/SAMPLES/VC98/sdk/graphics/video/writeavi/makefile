# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = writeavi.sym
!endif

all: writeavi.exe $(SYM)

OBJS= writeavi.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN    -I. -I..\include


# Update the resource if necessary

writeavi.res: writeavi.rc writeavi.h writeavi.rcv writeavi.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) writeavi.rc


# Update the object file if necessary

writeavi.obj: writeavi.c writeavi.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) writeavi.c


# Update the executable file if necessary, and if so, add the resource back in.

writeavi.exe writeavi.map:  $(OBJS) writeavi.res
    $(link) $(linkdebug) $(guilflags) -out:writeavi.exe $(OBJS) writeavi.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map
    
writeavi.sym:	$*.map
	mapsym $*.map

clean:
    @if exist writeavi.exe del writeavi.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
