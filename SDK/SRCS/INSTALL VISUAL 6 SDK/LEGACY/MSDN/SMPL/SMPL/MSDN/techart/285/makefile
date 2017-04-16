# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: debug.exe

# Update the object files if necessary

dbdlg.obj : dbdlg.c debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) dbdlg.c

dbfile.obj : dbfile.c debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) dbfile.c

debug.obj : debug.c debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) debug.c

main.obj : main.c debug.h
    $(cc) $(cflags) $(cvars) $(cdebug) main.c

# Update the resources if necessary

debug.res: debug.rc debug.h debug.ico debug.dlg
    rc -r debug.rc

debug.rbj: debug.res
    cvtres -$(CPU) debug.res -o debug.rbj

debug.exp: debug.obj dbfile.obj dbdlg.obj main.obj debug.def
    $(cvtobj) $(cvtdebug) debug.obj
    $(cvtobj) $(cvtdebug) dbdlg.obj
    $(cvtobj) $(cvtdebug) dbfile.obj
    $(cvtobj) $(cvtdebug) main.obj
    lib32 -machine:$(CPU)	       \
    -def:debug.def		     \
    debug.obj dbdlg.obj dbfile.obj main.obj    \
    -out:debug.lib

# Update the executable file if necessary.
# If so, add the resource back in.

debug.exe: debug.obj debug.rbj debug.def dbdlg.obj dbfile.obj main.obj debug.exp
    $(cvtobj) $(cvtdebug) *.obj
    $(link) $(linkdebug) $(guiflags) -out:debug.exe debug.obj debug.rbj dbdlg.obj dbfile.obj main.obj debug.exp $(guilibs)
