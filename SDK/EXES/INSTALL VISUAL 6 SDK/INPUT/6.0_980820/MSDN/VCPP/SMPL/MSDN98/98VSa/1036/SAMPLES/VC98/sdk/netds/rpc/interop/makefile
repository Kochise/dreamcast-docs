
#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                 OSF DCE Interop Application             **#
#**           Copyright(c) Microsoft Corp. 1993-1995        **#
#**                                                         **#
#*************************************************************#

SEHMAP=TRUE
!include <win32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags:G3=Gz)
cflags = $(cflags:Zi=Z7)
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

all : client.exe server.exe

# Make the client
client : client.exe
client.exe : client.obj msg_c.obj midluser.obj
    $(link) $(linkdebug) $(conflags) -out:client.exe -map:client.map \
      client.obj msg_c.obj midluser.obj \
      rpcrt4.lib $(conlibsdll)

# client main program
client.obj : client.c msg.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# client stub
msg_c.obj : msg_c.c msg.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Make the server executable
server : server.exe
server.exe : server.obj manager.obj msg_s.obj midluser.obj
    $(link) $(linkdebug) $(conflags) -out:server.exe -map:server.map \
      server.obj manager.obj msg_s.obj midluser.obj \
      rpcrt4.lib $(conlibsdll)

# server main program
server.obj : msg.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
manager.obj : msg.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# server stub
msg_s.obj : msg_s.c msg.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# midl_user* routines
midluser.obj : midluser.c
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Stubs and header file from the IDL file
msg.h msg_s.c msg_c.c : msg.idl msg.acf
    midl -cpp_cmd $(cc) -cpp_opt "-E" msg.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del msg_?.c
    -del msg.h
