#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Samples                   **#
#**                   pipes Application                     **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#** This is the makefile used to make the client and the    **#
#** server for the pipe sample program where the client     **#
#** sends a file to the server for "encoding", using pipes, **#
#** and then the file is sent back to the client.           **#
#** This file will compile for ANSI characters, to compile  **#
#** for UNICODE, type nmake /f makefile.uni at the command  **#
#** line                                                    **#
#*************************************************************#
# FILE : MAKEFILE

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

# Let the compiler know what version we are running
cflags=$(cflags) -D_WIN32_WINNT=0x400

# Need to use the __stdcall convention when using pipes
cvarsdll = $(cvarsdll) -Gz

all : client server

# Make the client side application 
client : client.exe
client.exe : pipec.obj pipe_c.obj
	$(link) $(linkdebug) $(conflags) -out:client.exe \
	  pipec.obj pipe_c.obj \
	  rpcrt4.lib rpcns4.lib $(conlibsdll)

# client main program
pipec.obj : pipec.c pipe.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# client stub
pipe_c.obj : pipe_c.c pipe.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the server side application
server : server.exe
server.exe : pipes.obj pipeproc.obj pipe_s.obj
	$(link) $(linkdebug) $(conflags) -out:server.exe \
	  pipes.obj pipe_s.obj pipeproc.obj \
	  rpcrt4.lib rpcns4.lib $(conlibsdll)

# server main program
pipes.obj : pipes.c pipe.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
pipeproc.obj : pipeproc.c pipe.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# server stub file
pipe_s.obj : pipe_s.c pipe.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c


# Stubs and header file from the IDL file
pipe.h pipe_c.c pipe_s.c : pipe.idl
	midl $(midlflags) -cpp_cmd $(cc) pipe.idl
	
# Clean up everything
cleanall : clean
	-del *.exe

# Clean up everything but the .EXEs
clean :
	-del *.obj
	-del pipe_c.c
	-del pipe_s.c
	-del pipe.h
	-del tempfile.oak
