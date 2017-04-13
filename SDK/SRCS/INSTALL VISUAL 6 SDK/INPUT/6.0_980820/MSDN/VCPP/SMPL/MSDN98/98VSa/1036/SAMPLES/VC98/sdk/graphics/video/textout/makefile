# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

TARGETNAME =    txtout32

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = $(TARGETNAME).sym
!endif

all: $(TARGETNAME).dll $(SYM)

OBJS=           txtout.obj drvproc.obj

OTHERCLOPTS=-nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

txtout.res: txtout.rc txtout.h txtout.rcv
    $(rc) -r -DWIN32 $(OTHERRCOPTS) txtout.rc


# Update the object files if necessary

drvproc.obj: drvproc.c txtout.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) drvproc.c

txtout.obj: txtout.c txtout.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) txtout.c


# Update the executable file if necessary, and if so, add the resource back in.

$(TARGETNAME).dll $(TARGETNAME).map:    $(OBJS) txtout.res
    $(implib) -out:$(@B).lib -def:$(TARGETNAME).def $(OBJS)
    $(link) $(linkdebug) $(dllflags) -out:$*.dll \
          $(@B).exp $(OBJS) txtout.res $(guilibsdll) winmm.lib -map:$*.map
    
$(TARGETNAME).sym:	$*.map
	mapsym $*.map

clean:
    @if exist $(TARGETNAME).dll del $(TARGETNAME).dll
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
