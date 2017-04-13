# Nmake macros for building Windows 32-Bit apps

APPVER=4.0

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = idfedt32.sym
!endif

all: idfedt32.exe $(SYM)

LIBS=msacm32.lib vfw32.lib winmm.lib shell32.lib

OTHERCLOPTS=-nologo -I. -I..\include
OTHERRCOPTS=-I. -I..\include -I..\..\include


# Update the resource if necessary

idfedit.res: idfedit.rc idfedit.rcv
    $(rc) $(rcflags) $(rcvars) $(OTHERRCOPTS) idfedit.rc


# Update the object file if necessary

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) $<

# Update the executable file if necessary, and if so, add the resource back in.

idfedt32.exe idfedt32.map:   drawstr.obj \
                head.obj    \
                idf.obj \
                main.obj \
                tridee.obj \
                idfedit.res
    $(link) $(linkdebug) $(guiflags) -out:idfedt32.exe $** $(guilibs) \
        $(LIBS) -map:$*.map
    
idfedt32.sym:	$*.map
	mapsym $*.map

clean:
    @if exist idfedt32.exe del idfedt32.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
