# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: hooks32.exe hooksdll.dll

# Update the object files if necessary

hooks32.obj : hooks32.c hooks32.h
	$(cc) $(cflags) $(cvars) $(cdebug) hooks32.c

hooksdll.obj : hooksdll.c hooks32.h
	$(cc) $(cflags) $(cvars) $(cdebug) hooksdll.c

# Update the resources if necessary

hooks32.res: hooks32.rc hooks32.h
	$(rc) $(rcvars) -r hooks32.rc

hooks32.rbj: hooks32.res
	cvtres -$(CPU) hooks32.res -o hooks32.rbj

hooksdll.res: hooksdll.rc
	$(rc) $(rcvars) -r hooksdll.rc

hooksdll.rbj: hooksdll.res
	cvtres -$(CPU) hooksdll.res -o hooksdll.rbj

# Update the import library

hooksdll.lib: hooksdll.obj hooksdll.def hooksdll.rbj
    $(implib) -machine:$(CPU)     \
	-def:hooksdll.def		\
	hooksdll.obj	\
	-out:hooksdll.lib

hooks32.exp: hooks32.obj hooks32.def
    $(implib) -machine:$(CPU)     \
	-def:hooks32.def		\
	hooks32.obj ptdlgs.obj ptprint.obj ptfind.obj hooksdll.obj	\
	-out:hooks32.lib


# Update the dynamic link library

hooksdll.dll: hooksdll.obj hooksdll.def hooksdll.lib
    $(link) $(linkdebug)     \
    -base:0x1C000000  \
    -dll	      \
	-entry:LibMain$(DLLENTRY)	\
	-out:hooksdll.dll	\
	hooksdll.exp hooksdll.obj hooksdll.rbj \
	$(guilibsdll)


# Update the executable file if necessary.
# If so, add the resource back in.

hooks32.exe: hooks32.obj hooksdll.dll hooksdll.lib hooks32.rbj hooks32.def
	$(link) $(linkdebug) $(guiflags) \
	-out:hooks32.exe \
	hooks32.obj hooksdll.lib hooks32.rbj \
	$(guilibs)
