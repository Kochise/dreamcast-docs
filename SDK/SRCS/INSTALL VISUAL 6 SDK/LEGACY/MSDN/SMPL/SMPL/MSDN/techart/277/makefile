# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

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
    $(cc) $(cflags) $(cvarsdll) $(cdebug) port.c

# Update the resources if necessary

porttool.res: porttool.rc porttool.h porttool.dlg porttool.ico portstat.ico
    $(rc) $(rcvars) -r porttool.rc

port.res: port.rc port.h portpriv.h portstat.ico
    $(rc) $(rcvars) -r port.rc

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
    port.exp port.obj port.res $(guilibsdll)


# Update the executable file if necessary.
# If so, add the resource back in.

porttool.exe: porttool.obj port.dll port.lib porttool.res porttool.def ptbkport.obj ptdlgs.obj ptfile.obj ptfind.obj ptprint.obj porttool.exp
    $(link) $(linkdebug) $(guiflags) -out:porttool.exe porttool.obj port.lib porttool.res ptbkport.obj ptdlgs.obj ptfile.obj ptfind.obj ptprint.obj porttool.exp $(guilibs)
