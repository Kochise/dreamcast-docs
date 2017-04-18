# Nmake macros for building Windows 32-Bit apps

APPVER=5.0

!include <win32.mak>
cflags     = -DUSEWAPI $(cflags)

all: imeappsw.exe

LIBS=imm32.lib comctl32.lib
LINKFILES=comp.obj data.obj imeapps.obj imemenu.obj mode.obj paint.obj setcomp.obj \
          status.obj subs.obj toolbar.obj wsubs.obj imeapps.res
# Update the resource if necessary

imeapps.res: ..\imeapps.rc ..\imeapps.rcv
    $(rc) $(rcflags) $(rcvars) /fo imeapps.res	 ..\imeapps.rc


comp.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
data.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
imeapps.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
imemenu.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
mode.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
paint.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
setcomp.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
status.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
subs.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
toolbar.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 
wsubs.obj: ..\$(@B).c
    $(cc) $(cdebug) $(cflags) $(cvars) ..\$(@B).c 

# Update the executable file if necessary, and if so, add the resource back in.

imeappsw.exe:    comp.obj    \
                data.obj    \
                imeapps.obj \
                imemenu.obj \
                mode.obj    \
                paint.obj   \
                setcomp.obj \
                status.obj  \
                subs.obj    \
                toolbar.obj \
                wsubs.obj   \
                imeapps.res
    $(link) $(linkdebug) $(guiflags) -out:imeappsw.exe $(LINKFILES) $(guilibs) $(LIBS)
