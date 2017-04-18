# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all: porttool.exe port.dll

# Update the object files if necessary

porttool.obj : porttool.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) porttool.c

ptbkport.obj : ptbkport.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) ptbkport.c

ptdlgs.obj : ptdlgs.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) ptdlgs.c

ptfile.obj : ptfile.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) ptfile.c

ptprint.obj : ptprint.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) ptprint.c

ptfind.obj : ptfind.c porttool.h
    $(cc) $(cflags) $(cvars) $(cdebug) ptfind.c

port.obj: port.c port.h
    $(cc) $(cflags) $(cvars) $(cdebug) port.c

# Update the resources if necessary

porttool.res: porttool.rc porttool.h porttool.dlg porttool.ico portstat.ico
    $(rc) $(rcflags) $(rcvars) porttool.rc

port.res: port.rc port.h portpriv.h portstat.ico
    $(rc) $(rcflags) $(rcvars) port.rc

# Update the import library

port.lib: port.obj port.def port.res
    $(implib) -machine:$(CPU)     \
    -def:port.def	    \
    port.obj    \
    -out:port.lib

porttool.exp: porttool.obj porttool.def 
    $(implib) -machine:$(CPU)     \
    -def:porttool.def	    \
    porttool.obj ptdlgs.obj ptprint.obj ptfind.obj ptbkport.obj  \
    -out:porttool.lib


# Update the dynamic link library

port.dll: port.obj port.def port.lib
    $(link) $(linkdebug) $(dlllflags)     \
    -base:0x1C000000  \
    -out:port.dll   \
    port.exp port.obj port.res $(guilibs)


# Update the executable file if necessary.
# If so, add the resource back in.

porttool.exe: porttool.obj port.dll port.lib porttool.res porttool.def ptbkport.obj ptdlgs.obj ptfile.obj ptfind.obj ptprint.obj porttool.exp
    $(link) $(linkdebug) $(guiflags) -out:porttool.exe porttool.obj port.lib porttool.res ptbkport.obj ptdlgs.obj ptfile.obj ptfind.obj ptprint.obj porttool.exp $(guilibs)
