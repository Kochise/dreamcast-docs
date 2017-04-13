#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   cluuid Application                    **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : cluuidc cluuids

# Make the client side application cluuidc
cluuidc : cluuidc.exe
cluuidc.exe : cluuidc.obj cluuid_c.obj
    $(link) $(linkdebug) $(conflags) -out:cluuidc.exe \
      cluuidc.obj cluuid_c.obj \
      rpcrt4.lib $(conlibsdll)

# cluuidc main program
cluuidc.obj : cluuidc.c cluuid.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# cluuidc stub
cluuid_c.obj : cluuid_c.c cluuid.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the server side application
cluuids : cluuids.exe
cluuids.exe : cluuids.obj cluuidp.obj cluuid_s.obj
    $(link) $(linkdebug) $(conflags) -out:cluuids.exe \
      cluuids.obj cluuid_s.obj cluuidp.obj \
      rpcrt4.lib $(conlibsdll)

# cluuid server main program
cluuids.obj : cluuids.c cluuid.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
cluuidp.obj : cluuidp.c cluuid.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# cluuids stub file
cluuid_s.obj : cluuid_s.c cluuid.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
cluuid.h cluuid_c.c cluuid_s.c : cluuid.idl cluuid.acf
    midl -oldnames -use_epv -no_cpp cluuid.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del cluuid_c.c
    -del cluuid_s.c
    -del cluuid.h
