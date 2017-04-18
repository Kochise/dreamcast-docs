#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   nhello Application                    **#
#**            Copyright(c) Microsoft Corp. 1992-1996       **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : nhelloc nhellos nsserv

# Make the nhelloc
nhelloc : nhelloc.exe
nhelloc.exe : nhelloc.obj nhello_c.obj
    $(link) $(linkdebug) $(conflags) -out:nhelloc.exe \
      nhelloc.obj nhello_c.obj \
      rpcrt4.lib rpcns4.lib $(conlibsdll)

# nhelloc main program
nhelloc.obj : nhelloc.c nhello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# nhelloc stub
nhello_c.obj : nhello_c.c nhello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Make the nhellos
nhellos : nhellos.exe
nhellos.exe : nhellos.obj nhellop.obj nhello_s.obj
    $(link) $(linkdebug) $(conflags) -out:nhellos.exe \
      nhellos.obj nhello_s.obj nhellop.obj \
      rpcrt4.lib rpcns4.lib $(conlibsdll)

# nhellos main loop
nhellos.obj : nhellos.c nhello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
nhellop.obj  : nhellop.c nhello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# nhellos stub file
nhello_s.obj : nhello_s.c nhello.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the nhellos
nsserv : nsserv.exe
nsserv.exe : nsserv.obj nhellop.obj nhello_s.obj service.obj
    $(link) $(linkdebug) $(conflags) -out:nsserv.exe \
      nsserv.obj nhello_s.obj nhellop.obj service.obj \
      rpcrt4.lib rpcns4.lib $(conlibsdll) advapi32.lib shell32.lib

# nhellos main loop
nsserv.obj : nsserv.c nhello.h service.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# nsserv serivce manager interface
service.obj : service.c service.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Stubs and header file from the IDL file
nhello.h nhello_c.c nhello_s.c : nhello.idl
    midl -ms_ext -cpp_cmd $(cc) -cpp_opt "-E" nhello.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del nhello_c.c
    -del nhello_s.c
    -del nhello.h
