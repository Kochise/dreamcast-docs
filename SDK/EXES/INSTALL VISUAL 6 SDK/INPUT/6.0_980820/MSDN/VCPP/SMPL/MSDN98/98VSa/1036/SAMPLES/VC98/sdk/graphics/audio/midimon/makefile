# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = midim32.sym
!endif

all: midim32.exe $(SYM)

OBJS=		midimon.obj prefer.obj instdata.obj filter.obj \
		display.obj  circbuf.obj about.obj callback.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I..\include


# Update the resource if necessary

midimon.res: midimon.rc midimon.h midimon.rcv midimon.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) midimon.rc


# Update the object file if necessary

prefer.obj: prefer.c midimon.h prefer.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) prefer.c

filter.obj: filter.c filter.h midimon.h display.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) filter.c

instdata.obj: instdata.c instdata.h midimon.h circbuf.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) instdata.c

display.obj: display.c display.h circbuf.h midimon.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) display.c

circbuf.obj: circbuf.c circbuf.h midimon.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) circbuf.c

about.obj: about.c about.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) about.c

callback.obj: callback.c callback.h circbuf.h instdata.h midimon.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) callback.c

midimon.obj: midimon.c midimon.h prefer.h about.h circbuf.h \
                instdata.h filter.h display.h callback.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) midimon.c


# Update the executable file if necessary, and if so, add the resource back in.

midim32.exe midim32.map:  $(OBJS) midimon.res
    $(link) $(linkdebug) $(guiflags) -out:midim32.exe $(OBJS) midimon.res $(guilibs) \
	vfw32.lib winmm.lib msacm32.lib uuid.lib -map:$*.map
    
midim32.sym:	$*.map
	mapsym $*.map

clean:
    @if exist midim32.exe del midim32.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib

