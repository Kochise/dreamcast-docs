# Nmake macros for building Windows 32-Bit apps

TARGETOS=BOTH
!include <win32.mak>

all: ttfonts.exe ttfonts.hlp


# If we are building for Windows NT only, then use Unicode entry points.
!IF "$(TARGETOS)" == "WINNT"
cflags = $(cflags) -DUNICODE
!ENDIF


# Update the resource if necessary
ttfonts.res: ttfonts.rc ttfonts.h
    rc $(rcvars) $(rcflags) -r -fo ttfonts.res ttfonts.rc

# Update the online help file if necessary.
ttfonts.hlp: ttfonts.hpj ttfonts.rtf
    @if exist ttfonts.PH del ttfonts.PH
    $(hc) ttfonts.hpj

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Update the executable file if necessary, and if so, add the resource back in.
ttfonts.exe: ttfonts.obj allfont.obj dialogs.obj toolbar.obj display.obj ttfonts.res ttfonts.def
    $(link) $(linkdebug) $(guiflags) -out:ttfonts.exe \
          ttfonts.obj allfont.obj dialogs.obj toolbar.obj display.obj ttfonts.res $(guilibs)


# Clean up everything except .exe and .hlp files
clean:
    del *.obj *.res *.err *.ph
