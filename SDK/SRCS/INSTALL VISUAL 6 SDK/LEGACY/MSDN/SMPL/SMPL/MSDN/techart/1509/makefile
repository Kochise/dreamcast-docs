# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: exeview.exe

# object files for exeview.exe
exeview.obj : exeview.c exeview.h
    $(cc) $(cflags) $(cvars) $(cdebug) exeview.c

viewmem.obj : viewmem.c exeview.h
    $(cc) $(cflags) $(cvars) $(cdebug) viewmem.c

viewio.obj : viewio.c exeview.h
    $(cc) $(cflags) $(cvars) $(cdebug) viewio.c


# object files for pefile.dll
pefile.obj : pefile.c pefile.h
    $(cc) $(cflags) $(cvars) $(cdebug) pefile.c



# resrouces for pefile.dll
pefile.res: pefile.rc pefile.h
    rc -r pefile.rc

pefile.rbj: pefile.res
    cvtres -$(CPU) pefile.res -o pefile.rbj


# resrouces for exeview.exe
exeview.res: exeview.rc exeview.h exeview.ico
    rc -r exeview.rc

exeview.rbj: exeview.res
    cvtres -$(CPU) exeview.res -o exeview.rbj



# export library for pefile.dll
pefile.lib: pefile.obj pefile.def pefile.rbj
    lib32 -machine:$(CPU)	 \
    -def:pefile.def		 \
    pefile.obj			 \
    -out:pefile.lib

# export/import library for exeview.exe
exeview.exp: exeview.obj exeview.def viewmem.obj viewio.obj pefile.lib
    lib32 -machine:$(CPU)	 \
    -def:exeview.def		 \
    -out:exeview.lib		 \
    exeview.obj viewmem.obj viewio.obj pefile.lib



# link pefile.dll
pefile.dll: pefile.obj pefile.def pefile.lib
    $(link) $(linkdebug)	 \
    -base:0x1C000000		 \
    -dll			 \
    -entry:DLLEntry$(DLLENTRY)	 \
    -out:pefile.dll		 \
    -ALIGN:0x1000		 \
    pefile.exp pefile.obj pefile.rbj $(guilibsdll)



# link exeview.exe
exeview.exe: exeview.rbj exeview.def exeview.exp exeview.obj viewmem.obj viewio.obj pefile.lib pefile.dll
    $(link) $(linkdebug)	 \
    $(guiflags) 		 \
    -out:exeview.exe		 \
    -ALIGN:0x1000		 \
    exeview.obj viewmem.obj viewio.obj exeview.rbj exeview.exp pefile.lib $(guilibs)
