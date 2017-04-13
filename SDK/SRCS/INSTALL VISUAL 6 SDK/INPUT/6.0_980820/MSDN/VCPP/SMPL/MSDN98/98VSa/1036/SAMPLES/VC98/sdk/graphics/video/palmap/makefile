# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

guiflags=-DLL
TARGETNAME =    palmap32
OBJS=		palmap.obj dibmap.obj
LIBS=           $(guilibs) vfw32.lib ole32.lib


!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = $(TARGETNAME).sym
!endif

all: $(TARGETNAME).dll $(SYM)


OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I..\include


# Update the resource if necessary

$(TARGETNAME).res: palmap.rc palmap.rcv
    $(rc) -r -DWIN32 -fo $@ $(OTHERRCOPTS) palmap.rc


# Update the object file if necessary

palmap.obj: palmap.c palmap.h dibmap.h palmap.rc
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) palmap.c

dibmap.obj: dibmap.c dibmap.h
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) dibmap.c


# Update the executable file if necessary, and if so, add the resource back in.

$(TARGETNAME).dll $(TARGETNAME).map:  $(OBJS) $(@B).res $(@B).def
    $(implib) -out:$(@B).lib -def:$(@B).def $(OBJS)
    $(link) $(linkdebug) $(dlllflags) -out:$(@B).dll $(@B).exp $(OBJS) \
    $(@B).res $(LIBS) -map:$*.map
    
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

