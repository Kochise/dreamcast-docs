# Nmake macros for building Windows 32-Bit apps

APPVER=4.0

!include <win32.mak>

all: multiui.exe

LIBS=imm32.lib comctl32.lib


# Update the resource if necessary

multiui.res: multiui.rc
    $(rc) $(rcflags) $(rcvars) multiui.rc


# Update the object file if necessary

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $<

# Update the executable file if necessary, and if so, add the resource back in.

multiui.exe:    dlgs.obj    \
                data.obj    \
                multiui.obj \
                multiwnd.obj    \
                multiui.res
    $(link) $(linkdebug) $(guiflags) -out:multiui.exe $** $(guilibs) $(LIBS)
