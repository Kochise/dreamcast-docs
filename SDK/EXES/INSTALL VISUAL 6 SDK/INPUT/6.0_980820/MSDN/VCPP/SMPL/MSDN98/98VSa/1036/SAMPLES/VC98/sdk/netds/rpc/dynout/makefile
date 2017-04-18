#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   dynout Application                    **#
#**         Copyright(c) Microsoft Corp. 1996               **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>


all : dynoutc dynouts

# Make the client side application dynoutc
dynoutc : dynoutc.exe
dynoutc.exe : dynoutc.obj dynout_c.obj
    $(link) $(linkdebug) $(conflags) -out:dynoutc.exe \
      dynoutc.obj dynout_c.obj \
      rpcrt4.lib $(conlibsdll)

# dynoutc main program
dynoutc.obj : dynoutc.c dynout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dynoutc stub
dynout_c.obj : dynout_c.c dynout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Make the server side application
dynouts : dynouts.exe
dynouts.exe : dynouts.obj dynoutp.obj dynout_s.obj
    $(link) $(linkdebug) $(conflags) -out:dynouts.exe \
      dynouts.obj dynout_s.obj dynoutp.obj \
      rpcrt4.lib  rpcns4.lib $(conlibsdll)

# dynout server main program
dynouts.obj : dynouts.c dynout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# remote procedures
dynoutp.obj : dynoutp.c dynout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# dynouts stub file
dynout_s.obj : dynout_s.c dynout.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

# Stubs and header file from the IDL file
# Add /ms_ext and /c_ext switches to midl command line 
# compiling with MIDL 2.0
dynout.h dynout_c.c dynout_s.c : dynout.idl dynout.acf
    midl /pack 1 -cpp_cmd cl -cpp_opt "-E" dynout.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del dynout_c.c
    -del dynout_s.c
    -del dynout.h
