# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

all: infinst.exe

# Update the resource if necessary

instwiz.res: instwiz.rc infinst.h resource.h instwiz.h 
    $(rc) $(rcflags) $(rcvars) instwiz.rc

# Update the object file if necessary

instwiz.obj: instwiz.c infinst.h infdesc.h instwiz.h 
    $(cc) $(cflags) $(cvars) $(cdebug) instwiz.c

doinst.obj: doinst.c instwiz.h infinst.h infdesc.h
    $(cc) $(cflags) $(cvars) $(cdebug) doinst.c

infinst.obj: infinst.c infinst.h infdesc.h instwiz.h
    $(cc) $(cflags) $(cvars) $(cdebug) infinst.c

# Update the executable file if necessary, and if so, add the resource back in.

infinst.exe: infinst.obj instwiz.res doinst.obj instwiz.obj 
    $(link) $(linkdebug) $(guiflags) -out:infinst.exe \
     infinst.obj instwiz.res doinst.obj instwiz.obj \
     $(guilibs) comctl32.lib shell32.lib setupapi.lib

clean:
   del *.obj
   del *.res
   del *.exe