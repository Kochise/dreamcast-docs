#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                Object Hello Application                 **#
#**            Copyright(c) Microsoft Corp. 1992-1996       **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = /Oi /ms_ext /c_ext /cpp_cmd $(CC)


.cxx.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /c $<

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /c $<

all:  ohello.dll client.exe server.exe

# Clean up everything
cleanall: clean
        @-del *.exe

# Clean up everything but the .EXEs
clean:
        @-del *.obj
        @-del ohello.dll
        @-del ohello.h
        @-del ohello.lib
        @-del ohello.exp
        @-del dlldata.c
        @-del ohello_?.c

#Run MIDL compiler to generate the header file and the proxy DLL files.
ohello.h dlldata.c ohello_p.c ohello_i.c : ohello.idl
    $(MIDL) $(MIDLFLAGS) ohello.idl

#Build the files for the proxy DLL.
dlldata.obj : dlldata.c
    $(CC) $(cdebug) $(cflags) -DREGISTER_PROXY_DLL $(cvarsdll) /c dlldata.c

ohello_i.obj : ohello_i.c

ohello_p.obj : ohello_p.c ohello.h

#Link the proxy DLL.
ohello.dll: ohello_p.obj ohello_i.obj dlldata.obj ohello.def
    $(link) $(linkdebug) -DLL -OUT:ohello.dll -DEF:ohello.def \
    ohello_p.obj ohello_i.obj dlldata.obj rpcrt4.lib uuid.lib kernel32.lib

#Build the files for the server application.
chello.obj: chello.cxx ohello.h

error.obj: error.cxx

server.obj: server.cxx ohello.h

#Link the server application.
server.exe: chello.obj error.obj ohello_i.obj server.obj
        $(link) $(linkdebug) $(conlflags) -OUT:server.exe \
        chello.obj error.obj ohello_i.obj server.obj  rpcrt4.lib $(ole2libsdll)

#Build the files for the client application.
client.obj: client.cxx ohello.h

#Link the client application.
client.exe: client.obj error.obj ohello_i.obj
        $(link) $(linkdebug) $(conlflags) -OUT:client.exe \
        client.obj error.obj ohello_i.obj rpcrt4.lib $(ole2libsdll)
