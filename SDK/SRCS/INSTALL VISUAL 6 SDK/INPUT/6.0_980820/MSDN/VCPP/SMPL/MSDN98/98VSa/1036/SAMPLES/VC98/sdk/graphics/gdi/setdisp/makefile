# Nmake macros for building Windows 32-Bit apps

TARGETOS=WIN95
APPVER=4.0

!include <win32.mak>

!ifndef nodebug
cflags = $(cflags) -DDBG
!endif

all: SetDisp.exe

# Update the resource if necessary

SetDisp.res: SetDisp.rc SetDisp.h resource.h
    $(rc) $(rcflags) $(rcvars) SetDisp.rc

# Update the object file if necessary

SetDisp.obj: SetDisp.c SetDisp.h
    $(cc) $(cflags) $(cvars) $(cdebug) SetDisp.c

# Update the executable file if necessary, and if so, add the resource back in.
SetDisp.exe: SetDisp.obj SetDisp.res
    $(link) $(linkdebug) $(guiflags) -out:SetDisp.exe SetDisp.obj SetDisp.res $(guilibs) shell32.lib

cleanall:
   del *.exe
   del *.obj
   del *.res

clean:
   del *.obj
   del *.res
