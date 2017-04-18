#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   dunion Application                    **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : dunionc dunions

# Make the dunionc
dunionc : dunionc.exe
dunionc.exe : dunionc.obj dunion_c.obj
    $(link) $(linkdebug) $(conflags) -out:dunionc.exe \
      dunionc.obj dunion_c.obj \
      rpcrt4.lib $(conlibsdll)

# dunionc main program
dunionc.obj : dunionc.c dunion.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dunionc stub
dunion_c.obj : dunion_c.c dunion.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the dunions
dunions : dunions.exe
dunions.exe : dunions.obj dunionp.obj dunion_s.obj
    $(link) $(linkdebug) $(conflags) -out:dunions.exe \
      dunions.obj dunion_s.obj dunionp.obj \
      rpcrt4.lib $(conlibsdll)

# dunions main loop
dunions.obj : dunions.c dunion.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
dunionp.obj  : dunionp.c dunion.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dunions stub file
dunion_s.obj : dunion_s.c dunion.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
dunion.h dunion_c.c dunion_s.c : dunion.idl dunion.acf
    midl -oldnames -no_cpp dunion.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del dunion_c.c
    -del dunion_s.c
    -del dunion.h
