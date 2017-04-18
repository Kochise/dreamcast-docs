#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   repas Application                     **#
#**          Copyright(c) Microsoft Corp. 1992-1996         **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : repasc repass

# Make the client
repasc : repasc.exe
repasc.exe : repasc.obj repascu.obj repas_c.obj
    $(link) $(linkdebug) $(conflags) -out:repasc.exe -map:repasc.map \
      repasc.obj repascu.obj repas_c.obj \
      rpcrt4.lib $(conlibsdll)

# repas client main program
repasc.obj : repasc.c repasc.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

repascu.obj : repascu.c repasc.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# repas client stub
repas_c.obj : repas_c.c repasc.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs, auxiliary and header file from the IDL file for the client side
repasc.h repas_c.c : repas.idl repasc.acf
    midl -oldnames -ms_ext -no_cpp repas.idl -acf repasc.acf -header repasc.h -server none

# Make the server executable
repass : repass.exe
repass.exe : repass.obj repassu.obj repasp.obj repas_s.obj
    $(link) $(linkdebug) $(conflags) -out:repass.exe -map:repass.map \
      repass.obj repassu.obj repas_s.obj repasp.obj \
      rpcrt4.lib $(conlibsdll)

# repas server main
repass.obj : repass.c repass.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

repassu.obj : repassu.c repass.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
repasp.obj : repasp.c repass.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# repas server stub file
repas_s.obj : repas_s.c repass.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs, auxiliary and header file from the IDL file
repass.h repas_s.c : repas.idl repass.acf
    midl -oldnames -ms_ext -no_cpp repas.idl -acf repass.acf -header repass.h -client none

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del repas_c.c
    -del repas_s.c
    -del repasc.h
    -del repass.h
