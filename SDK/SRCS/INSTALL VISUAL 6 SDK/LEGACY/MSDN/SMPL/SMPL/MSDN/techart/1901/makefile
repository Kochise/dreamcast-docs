# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: sizebox.exe

# Update the resource if necessary

sizebox.res: sizebox.rc sizebox.h
    $(rc) -r -fo sizebox.tmp sizebox.rc
    $(cvtres) -$(CPU) sizebox.tmp -o sizebox.res
    del sizebox.tmp

# Update the object file if necessary

sizebox.obj: sizebox.c sizebox.h
    $(cc) $(cdebug) $(cflags) $(cvars) sizebox.c

# Update the executable file if necessary, and if so, add the resource back in.

sizebox.exe: sizebox.obj sizebox.res
    $(link) $(linkdebug) $(guiflags) -out:sizebox.exe sizebox.obj sizebox.res $(guilibs)
