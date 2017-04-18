#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**               Mandelbrot RPC Application                **#
#**            Copyright(c) Microsoft Corp. 1991-1995       **#
#**                                                         **#
#*************************************************************#
# The same source code is used to build either a standalone
# or an RPC version of the Microsoft Windows (R) Mandelbrot
# sample application.  The flag RPC determines which version
# is built.  To build a standalone version, use the commands:
#     >nmake cleanall
#     >set NOTRPC=1
#     >nmake
# To build the RPC version, use the commands:
#     >nmake cleanall
#     >set NOTRPC=
#     >nmake
!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

!ifdef NOTRPC
RPCFLAG =
!else
RPCFLAG = -DRPC
!endif

.c.obj:
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(RPCFLAG) $<

# Targets
# The RPC version produces client and server executables.
# The standalone version produces a single exe file, "mandel".

!ifndef NOTRPC
all: client.exe server.exe
!else
all: mandel.exe
!endif

mandel.exe: mandel.obj remote.obj mandel.def mandel.rbj calc.obj
    $(link) $(linkdebug) $(guiflags) -out:mandel.exe -map:mandel.map \
      mandel.obj remote.obj calc.obj mandel.rbj $(guilibsdll)

client.exe: mandel.obj remote.obj mandel.def mandel.rbj mdlrpc_c.obj
    $(link) $(linkdebug) $(guiflags) -out:client.exe -map:client.map \
      mandel.obj remote.obj mdlrpc_c.obj \
      mandel.rbj rpcrt4.lib $(guilibsdll)

server.exe: server.obj calc.obj mdlrpc_s.obj
    $(link) $(linkdebug) $(conflags) -out:server.exe -map:server.map \
      server.obj calc.obj mdlrpc_s.obj \
      rpcrt4.lib $(conlibsdll)

# Update the resource if necessary
mandel.rbj: mandel.rc mandel.h
    rc -r mandel.rc
    cvtres -$(CPU) mandel.res -o mandel.rbj

# Object file dependencies

# server only built for RPC version; always needs mdlrpc.h
server.obj: server.c mandel.h mdlrpc.h

# Compile differently for RPC, standalone versions
!ifndef NOTRPC
mandel.obj: mandel.c mandel.h mdlrpc.h
remote.obj: remote.c mandel.h mdlrpc.h
calc.obj  : calc.c mandel.h mdlrpc.h
!else
mandel.obj: mandel.c mandel.h
remote.obj: remote.c mandel.h
calc.obj  : calc.c mandel.h
!endif

# client stub
mdlrpc_c.obj : mdlrpc_c.c mdlrpc.h

# server stub file
mdlrpc_s.obj : mdlrpc_s.c mdlrpc.h

# Stubs and header file from the IDL file
mdlrpc.h mdlrpc_c.c mdlrpc_s.c: mdlrpc.idl mdlrpc.acf
    midl -oldnames -cpp_cmd $(cc) -cpp_opt "-E" mdlrpc.idl

clean:
    -del client.exe
    -del server.exe
    -del mandel.exe

cleanall:  clean
    -del *.obj
    -del *.map
    -del *.res
    -del *.rbj
    -del mdlrpc_*.c
    -del mdlrpc.h
