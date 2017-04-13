# Nmake macros for building Windows 32-Bit apps

!include <win32.mak>

all: textfx.exe


# Update the resource if necessary
textfx.res: textfx.rc textfx.h resource.h
    rc -r -fo textfx.res textfx.rc

# Inference rule for updating the object files
.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvars) $*.c

# Update the executable file if necessary, and if so, add the resource back in.
textfx.exe: textfx.obj fx.obj guide.obj textfx.res
    $(link) $(linkdebug) $(guiflags) -out:textfx.exe \
       textfx.obj fx.obj guide.obj textfx.res  $(guilibs)


# Clean up everything except .exe
clean:
    del *.obj *.res
