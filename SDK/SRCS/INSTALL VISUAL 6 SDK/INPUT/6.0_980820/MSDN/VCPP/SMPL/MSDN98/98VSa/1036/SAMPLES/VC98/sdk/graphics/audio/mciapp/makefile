# Nmake macros for building Windows 32-Bit apps

APPVER=4.0

!include <win32.mak>

!if "$(CPU)" == "i386" # .syms are useful for Win95
SYM = mciapp32.sym
!endif

all: mciapp32.exe $(SYM)

LIBS=msacm32.lib vfw32.lib winmm.lib shell32.lib

OTHERCLOPTS=-DWIN32_LEAN_AND_MEAN -nologo -I. -I..\include
OTHERRCOPTS=-DWIN32_LEAN_AND_MEAN -I. -I..\include


# Update the resource if necessary

mciapp.res: mciapp.rc mciapp.rcv
    $(rc) $(rcflags) $(rcvars) $(OTHERRCOPTS) mciapp.rc


# Update the object file if necessary

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $(OTHERCLOPTS) $<

# Update the executable file if necessary, and if so, add the resource back in.

mciapp32.exe mciapp32.map:   mciapp.obj \
                app.obj     \
                appinit.obj \
                debug.obj   \
                mciapp.res
    $(link) $(linkdebug) $(guiflags) -out:mciapp32.exe $** $(guilibs) $(LIBS) \
         -map:$*.map
    
mciapp32.sym:	$*.map
	mapsym $*.map

clean:
    @if exist mciapp32.exe del mciapp32.exe
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.sym del *.sym
    @if exist *.res del *.res
    @if exist *.pdb del *.pdb
    @if exist *.exp del *.exp
    @if exist *.lib del *.lib
