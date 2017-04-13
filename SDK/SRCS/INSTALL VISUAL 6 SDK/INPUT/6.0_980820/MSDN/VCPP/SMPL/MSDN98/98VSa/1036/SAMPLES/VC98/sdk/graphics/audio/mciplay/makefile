# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = mciplay.sym
!endif

all: mciplay.exe $(SYM)

OBJS= mciplay.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

mciplay.res: mciplay.rc mciplay.h mciplay.rcv mciplay.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) mciplay.rc



# Update the object file if necessary

mciplay.obj: mciplay.c mciplay.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) mciplay.c

# Update the executable file if necessary, and if so, add the resource back in.

mciplay.exe mciplay.map:  $(OBJS) mciplay.res
    $(link) $(linkdebug) $(guilflags) -out:mciplay.exe $(OBJS) mciplay.res $(guilibs) \
	 winmm.lib vfw32.lib -map:$*.map
    
mciplay.sym:	$*.map
	mapsym $*.map

clean:
    @if exist mciplay.exe del mciplay.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib

