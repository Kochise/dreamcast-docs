#*************************************************************#
#**                                                         **#
#**                 Microsoft RPC Examples                  **#
#**                   doctor Application                    **#
#**         Copyright(c) Microsoft Corp. 1992-1996          **#
#**                                                         **#
#*************************************************************#

!include <ntwin32.mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

all : doctorc doctors

# Make the doctor client executable
doctorc : doctorc.exe
doctorc.exe : doctorc.obj doctor_c.obj
    $(link) $(linkdebug) $(conflags) -out:doctorc.exe \
      doctorc.obj doctor_c.obj \
      rpcrt4.lib $(conlibsdll)

# client main program
doctorc.obj : doctorc.c doctor.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(DEBUG) $*.c

# client stub
doctor_c.obj : doctor_c.c doctor.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(DEBUG) $*.c


# Make the doctor server executable
doctors : doctors.exe
doctors.exe : doctors.obj doctorp.obj doctor_s.obj
    $(link) $(linkdebug) $(conflags) -out:doctors.exe \
      doctors.obj doctor_s.obj doctorp.obj \
      rpcrt4.lib $(conlibsdll)

# server main loop
doctors.obj : doctors.c doctor.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(DEBUG) $*.c

# remote procedures
doctorp.obj  : doctorp.c doctor.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(DEBUG) $*.c

# server stub file
doctor_s.obj : doctor_s.c doctor.h
   $(cc) $(cdebug) $(cflags) $(cvarsdll) $(DEBUG) $*.c

# Stubs and header file from the IDL file
doctor.h doctor_c.c doctor_s.c : doctor.idl doctor.acf
    midl -oldnames -no_cpp -ms_ext doctor.idl

# Clean up everything
cleanall : clean
    -del *.exe

# Clean up everything but the .EXEs
clean :
    -del *.obj
    -del *.map
    -del doctor_c.c
    -del doctor_s.c
    -del doctor.h
