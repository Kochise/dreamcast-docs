#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   rpcssm Application                    **#
#**            Copyright(c) Microsoft Corp. 1992-1996       **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags:G3=Gz)
!endif

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : rpcssmc rpcssms

# Make the rpcssm client
rpcssmc : rpcssmc.exe
rpcssmc.exe : rpcssmc.obj rpcssm_c.obj
    $(link) $(linkdebug) $(conflags) -out:rpcssmc.exe \
      rpcssmc.obj rpcssm_c.obj \
      rpcrt4.lib $(conlibsdll)

# client main program
rpcssmc.obj : rpcssmc.c rpcssm.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# client stub
rpcssm_c.obj : rpcssm_c.c rpcssm.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the rpcssm server
rpcssms : rpcssms.exe
rpcssms.exe : rpcssms.obj rpcssmp.obj rpcssm_s.obj
    $(link) $(linkdebug) $(conflags) -out:rpcssms.exe \
      rpcssms.obj rpcssmp.obj rpcssm_s.obj \
      rpcrt4.lib $(conlibsdll)

# server main loop
rpcssms.obj : rpcssms.c rpcssm.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
rpcssmp.obj : rpcssmp.c rpcssm.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# server stub file
rpcssm_s.obj : rpcssm_s.c rpcssm.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
rpcssm.h rpcssm_c.c rpcssm_s.c : rpcssm.idl rpcssm.acf
    midl -oldnames -no_cpp rpcssm.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del rpcssm_c.c
    -del rpcssm_s.c
    -del rpcssm.h
