#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   hello Application                     **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : helloc hellos

# Make the client side application helloc
helloc : helloc.exe
helloc.exe : helloc.obj hello_c.obj
    $(link) $(linkdebug) $(conflags) -out:helloc.exe \
      helloc.obj hello_c.obj \
      rpcrt4.lib $(conlibsdll)

# helloc main program
helloc.obj : helloc.c hello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# helloc stub
hello_c.obj : hello_c.c hello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the server side application
hellos : hellos.exe
hellos.exe : hellos.obj hellop.obj hello_s.obj
    $(link) $(linkdebug) $(conflags) -out:hellos.exe \
      hellos.obj hello_s.obj hellop.obj \
      rpcrt4.lib $(conlibsdll)

# hello server main program
hellos.obj : hellos.c hello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
hellop.obj : hellop.c hello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# hellos stub file
hello_s.obj : hello_s.c hello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Stubs and header file from the IDL file
hello.h hello_c.c hello_s.c : hello.idl hello.acf
    midl -oldnames -cpp_cmd $(cc) -cpp_opt "-E" hello.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del hello_c.c
    -del hello_s.c
    -del hello.h
