# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = lowpass.sym
!endif

all: lowpass.exe $(SYM)

OBJS=		lowpass.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

lowpass.res: lowpass.rc lowpass.h strings.rc strings.h lowpass.rcv lowpass.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) lowpass.rc


# Update the object file if necessary

lowpass.obj: lowpass.c lowpass.h strings.h
    $(cc) $(cdebug)  $(cflags) $(cvars) $(OTHERCLOPTS) lowpass.c

# Update the executable file if necessary, and if so, add the resource back in.

lowpass.exe lowpass.map:  $(OBJS) lowpass.res
    $(link) $(linkdebug) $(guiflags) -out:lowpass.exe $(OBJS) lowpass.res $(guilibs) \
    winmm.lib -map:$*.map
    
lowpass.sym:	$*.map
	mapsym $*.map

clean:
    @if exist lowpass.exe del lowpass.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
