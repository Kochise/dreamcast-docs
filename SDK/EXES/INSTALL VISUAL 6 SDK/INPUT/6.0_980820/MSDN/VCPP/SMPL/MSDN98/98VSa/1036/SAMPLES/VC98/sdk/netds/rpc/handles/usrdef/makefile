#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   usrdef Application                    **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : usrdefc usrdefs

# Make the usrdefc
usrdefc : usrdefc.exe
usrdefc.exe : usrdefc.obj usrdef_c.obj
    $(link) $(linkdebug) $(conflags) -out:usrdefc.exe \
      usrdefc.obj usrdef_c.obj \
      rpcrt4.lib $(conlibsdll)

# usrdefc main program
usrdefc.obj : usrdefc.c usrdef.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# usrdefc stub
usrdef_c.obj : usrdef_c.c usrdef.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Make the usrdefs
usrdefs : usrdefs.exe
usrdefs.exe : usrdefs.obj usrdefp.obj usrdef_s.obj
    $(link) $(linkdebug) $(conflags) -out:usrdefs.exe \
      usrdefs.obj usrdef_s.obj usrdefp.obj \
      rpcrt4.lib $(conlibsdll)

# usrdefs main loop
usrdefs.obj : usrdefs.c usrdef.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
usrdefp.obj : usrdefp.c usrdef.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# usrdefs stub file
usrdef_s.obj : usrdef_s.c usrdef.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Stubs and header file from the IDL file
usrdef.h usrdef_c.c usrdef_s.c : usrdef.idl usrdef.acf
    midl -oldnames -cpp_cmd $(cc) -cpp_opt "-E" usrdef.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del usrdef_c.c
    -del usrdef_s.c
    -del usrdef.h
