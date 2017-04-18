# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: dyndlg.exe dyndlg.hlp


# Update the resource if necessary

dyndlg.res: dyndlg.rc dyndlg.h
    $(rc) $(rcvars) -r -fo dyndlg.res dyndlg.rc


# Update the online help file if necessary.

dyndlg.hlp: dyndlg.hpj dyndlg.rtf
    @if exist dyndlg.PH del dyndlg.PH
    $(hc) dyndlg.hpj


# Update the object file if necessary

dyndlg.obj: dyndlg.c dyndlg.h
    $(cc) $(cdebug) $(cflags) $(cvars) dyndlg.c


# Update the executable file if necessary, and if so, add the resource back in.

dyndlg.exe: dyndlg.obj dyndlg.res
    $(link) $(linkdebug) $(guiflags) -out:dyndlg.exe dyndlg.obj dyndlg.res $(guilibs)
