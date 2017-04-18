# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: fwatch.exe

fwatch.obj: fwatch.c
    $(cc) $(cflags) $(cdebug) $(cvars) fwatch.c -D_WIN32_WINNT=0x0400

fwatch.exe: fwatch.obj
    $(link) $(ldebug) $(conflags) -out:fwatch.exe fwatch.obj $(conlibs) user32.lib
