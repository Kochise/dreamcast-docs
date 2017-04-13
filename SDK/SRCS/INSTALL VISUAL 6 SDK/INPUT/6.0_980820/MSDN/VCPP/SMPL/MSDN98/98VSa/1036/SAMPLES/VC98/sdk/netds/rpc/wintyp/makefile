#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Samples                   **#
#**                   WinTyp Application                    **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#** This is the makefile used to make the client and the    **#
#** server for the wintyp sample program where the client   **#
#** sends a bitmap to the server for either flipping or     **#
#** edge detection. The bitmap is thensent back to the      **#
#** client.                                                 **#
#** This file will compile for ANSI characters, to compile  **#
#** for UNICODE, type nmake /f makefile.uni at command line **#
#*************************************************************#
# FILE : MAKEFILE

!include <ntwin32.mak>

# Let the compiler know what version we are running
cflags=$(cflags) -D_WIN32_WINNT=0x400

all: client server

client : client.exe
client.exe : client.obj wintyp_c.obj client.rbj 
    $(link) $(linkdebug) $(guiflags) -out:client.exe -map:client.map \
	  client.obj client.rbj wintyp_c.obj rpcrt4.lib $(olelibsdll)

client.obj : client.c client.h wintyp.h
	$(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

wintyp_c.obj : wintyp_c.c wintyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

server : server.exe
server.exe : server.obj wintyp_s.obj remote.obj
    $(link) $(linkdebug) $(conflags) -out:server.exe -map:server.map\
      server.obj wintyp_s.obj remote.obj rpcrt4.lib  $(conlibsdll) \
      $(olelibsdll) 


server.obj : server.c common.h wintyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

remote.obj : remote.c common.h wintyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

wintyp_s.obj : wintyp_s.c wintyp.h
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
wintyp.h wintyp_c.c wintyp_s.c : wintyp.idl
	midl $(midlflags) -cpp_cmd $(cc) wintyp.idl


# Compile the resource file, and then convert it to an object file to include
client.rbj : client.rc clires.h
	$(RC) -r -DWIN32 -DWINVER=0x400  client.rc
	cvtres -$(CPU) client.res -o client.rbj


clean:
    -del client.exe
    -del server.exe

cleanall:  clean
    -del *.obj
    -del *.rbj 
    -del *.map
    -del *.res
    -del wintyp_*.c
    -del wintyp.h
