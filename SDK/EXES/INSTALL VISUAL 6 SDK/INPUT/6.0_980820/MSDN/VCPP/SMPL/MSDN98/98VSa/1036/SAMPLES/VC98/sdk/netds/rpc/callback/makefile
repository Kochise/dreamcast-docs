#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                  Callback Application                   **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : callc calls

# Make the client side application callc
callc : callc.exe
callc.exe : callc.obj call_c.obj
    $(link) $(linkdebug) $(conflags) -out:callc.exe \
      callc.obj call_c.obj \
      rpcrt4.lib $(conlibsdll)

# callc main program
callc.obj : callc.c call.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# callc stub
call_c.obj : call_c.c call.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the server side application
calls : calls.exe
calls.exe : calls.obj callp.obj call_s.obj
    $(link) $(linkdebug) $(conflags) -out:calls.exe \
      calls.obj call_s.obj callp.obj \
      rpcrt4.lib $(conlibsdll)

# call server main program
calls.obj : calls.c call.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
callp.obj : callp.c call.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# calls stub file
call_s.obj : call_s.c call.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
call.h call_c.c call_x.c call_s.c : call.idl call.acf
    midl -oldnames -ms_ext -no_cpp call.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del call_c.c
    -del call_s.c
    -del call.h
