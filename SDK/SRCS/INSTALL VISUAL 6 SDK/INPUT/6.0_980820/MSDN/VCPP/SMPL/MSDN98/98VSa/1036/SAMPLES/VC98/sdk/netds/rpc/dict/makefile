
#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                 Dictionary Application                  **#
#**            Copyright(c) Microsoft Corp. 1991-1995       **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags:G3=Gz)
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : client.exe server.exe play.exe

# Make the client
client : client.exe
client.exe : client.obj util0.obj replay_c.obj
    $(link) $(linkdebug) $(conflags) -out:client.exe -map:client.map \
      client.obj util0.obj replay_c.obj \
      rpcrt4.lib $(conlibsdll)

# dict client main program
client.obj : client.c util0.h replay.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dict client stub
replay_c.obj : replay_c.c replay.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Make the server executable
server : server.exe
server.exe : server.obj util0.obj replay_s.obj replay.obj dict0.obj
    $(link) $(linkdebug) $(conflags) -out:server.exe -map:server.map \
      server.obj util0.obj replay_s.obj replay.obj dict0.obj \
      rpcrt4.lib $(conlibsdll)

# dict server main program
server.obj : server.c util0.h replay.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dict remote procedures
replay.obj : replay.c util0.h replay.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dict server auxiliary file
replay_s.obj : replay_s.c replay.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# make the local executable
play : play.exe
play.exe : play.obj lutil0.obj dict0.obj
    $(link) $(linkdebug) $(conflags) -out:play.exe -map:play.map \
      play.obj lutil0.obj dict0.obj \
      $(conlibsdll)

# dict local main program
play.obj : play.c util0.h dict0.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

dict0.obj : dict0.c dict0.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

util0.obj : util0.c util0.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

lutil0.obj : util0.c util0.h
   copy util0.c lutil0.c
   $(cc) $(cdebug) $(cflags) $(cvarsdll) -D_LOCAL lutil0.c
   del lutil0.c

# Stubs and header file from the IDL file
replay.h replay_s.c replay_c.c : replay.idl replay.acf
    midl -ms_ext -oldnames -no_cpp replay.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del replay_?.c
    -del replay.h
