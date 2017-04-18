# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = aviedi32.sym
!endif

all: aviedi32.exe $(SYM)

OBJS=aviedit.obj audio.obj

LIBS=msacm32.lib vfw32.lib winmm.lib shell32.lib

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

aviedit.res: aviedit.rc aviedit.h aviedit.rcv aviedit.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) aviedit.rc


# Update the object file if necessary

audio.obj: audio.c audio.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) audio.c

aviedit.obj: aviedit.c aviedit.h muldiv32.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) aviedit.c

# Update the executable file if necessary, and if so, add the resource back in.

aviedi32.exe aviedi32.map:  $(OBJS) aviedit.res
    $(link) $(linkdebug) $(guiflags) -out:aviedi32.exe $(OBJS) aviedit.res $(guilibs) \
       $(LIBS) -map:$*.map
    
aviedi32.sym:	$*.map
	mapsym $*.map

clean:
    @if exist aviedi32.exe del aviedi32.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
