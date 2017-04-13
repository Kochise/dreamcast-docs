# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: gina.dll

# Define the compiler flags conditional on NODEBUG
!IFDEF NODEBUG
ginaflags= $(cflags) -DUNICODE -D_UNICODE
!ELSE
ginaflags= $(cflags) -DUNICODE -D_UNICODE -DDBG
!ENDIF


# Update the resource if necessary
gina.res: res.rc
  rc -r -fo gina.res res.rc


# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cvarsdll) $(ginaflags) -I. $*.c


# Update the DLL
gina.DLL:              \
          gina.obj     \
          debug.obj    \
	  welcome.obj	\
          shutdown.obj \
          options.obj  \
          logon.obj    \
          util.obj     \
          gina.res
  $(link) $(dlllflags)		     \
	  -ignore:4078		     \
          -subsystem:native,4.0      \
          -def:gina.def              \
          -out:$*.dll                \
          $**                        \
          $(guilibsdll) comctl32.lib
