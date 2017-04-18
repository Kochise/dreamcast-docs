#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   auto Application                      **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif


all : autoc autos

# Make the autoc
autoc : autoc.exe
autoc.exe : autoc.obj auto_c.obj
    $(link) $(linkdebug) $(conflags) -out:autoc.exe \
      autoc.obj auto_c.obj \
      rpcrt4.lib rpcns4.lib $(conlibsdll)

# autoc main program
autoc.obj : autoc.c auto.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# autoc stub
auto_c.obj : auto_c.c auto.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the autos
autos : autos.exe
autos.exe : autos.obj autop.obj auto_s.obj
    $(link) $(linkdebug) $(conflags) -out:autos.exe \
      autos.obj auto_s.obj autop.obj \
      rpcrt4.lib rpcns4.lib $(conlibsdll)

# autos main loop
autos.obj : autos.c auto.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
autop.obj  : autop.c auto.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# autos stub file
auto_s.obj : auto_s.c auto.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
auto.h auto_c.c auto_s.c : auto.idl auto.acf
    midl -oldnames -no_cpp auto.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del auto_c.c
    -del auto_s.c
    -del auto.h
