# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

TARGETNAME =    dseqf32

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = $(TARGETNAME).sym
!endif

all: $(TARGETNAME).dll $(SYM)

OBJS=           dseqf.obj factory.obj

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

handler.res: handler.rc handler.rcv
    $(rc) -r -DWIN32 $(OTHERRCOPTS) handler.rc


# Update the object file if necessary

factory.obj: factory.cpp handler.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) factory.cpp

dseqf.obj: dseqf.cpp handler.h handler.rc
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(OTHERCLOPTS) dseqf.cpp

# Update the dll file if necessary, and if so, add the resource back in.

$(TARGETNAME).dll $(TARGETNAME).map:  $(OBJS) handler.res
    lib -out:$(@B).lib -def:$(TARGETNAME).def $(OBJS)
     $(link) $(linkdebug) -out:$*.dll $(dllflags)  \
        $(@B).exp $(OBJS) handler.res $(olelibsdll) \
        vfw32.lib winmm.lib msacm32.lib -map:$*.map
    
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

