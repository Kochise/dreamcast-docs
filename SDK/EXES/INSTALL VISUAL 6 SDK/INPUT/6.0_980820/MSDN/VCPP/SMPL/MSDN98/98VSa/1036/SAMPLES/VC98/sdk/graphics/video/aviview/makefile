# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = aviview.sym
!endif

all: aviview.exe $(SYM)

OBJS=aviview.obj audplay.obj aviball.obj cdib.obj guid.obj regobjs.obj

LIBS=vfw32.lib winmm.lib msacm32.lib uuid.lib

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I..\include


# Update the resource if necessary

aviview.res: aviview.rc aviview.h aviview.rcv aviview.ico
    $(rc) -r -DWIN32 $(OTHERRCOPTS) aviview.rc


# Update the object file if necessary

audplay.obj: audplay.c audplay.h muldiv32.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) audplay.c

aviball.obj: aviball.c aviball.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) aviball.c

guid.obj: guid.c
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) guid.c

regobjs.obj: regobjs.cpp
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) regobjs.cpp

cdib.obj: cdib.c
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) cdib.c

aviview.obj: aviview.c aviview.h muldiv32.h audplay.h aviball.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) aviview.c

# Update the executable file if necessary, and if so, add the resource back in.

aviview.exe aviview.map:  $(OBJS) aviview.res
    $(link) $(linkdebug) $(guiflags) -out:aviview.exe $(OBJS) aviview.res $(guilibs) \
	$(LIBS) -map:$*.map
    
aviview.sym:	$*.map
	mapsym $*.map

clean:
    @if exist aviview.exe del aviview.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
