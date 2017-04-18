!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
makeflag = "nodebug=1"
!else
OBJ_DIR = Debug

!endif

proj=foxbear

mycflag=/I "..\misc" /I "..\fastfile"

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\gameproc.obj \
           $(OBJ_DIR)\tile.obj $(OBJ_DIR)\plane.obj $(OBJ_DIR)\sprite.obj \
           $(OBJ_DIR)\gfx.obj $(OBJ_DIR)\bmp.obj $(OBJ_DIR)\ddraw.obj \
           $(OBJ_DIR)\fbsound.obj ..\misc\$(OBJ_DIR)\dsutil.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).c

$(OBJ_DIR)\gameproc.obj:  gameproc.c gameproc.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\gameproc.obj $(mycflag) \
    $(cvars) gameproc.c

$(OBJ_DIR)\tile.obj:  tile.c tile.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\tile.obj $(mycflag) \
    $(cvars) tile.c

$(OBJ_DIR)\plane.obj:  plane.c plane.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\plane.obj $(mycflag) \
    $(cvars) plane.c

$(OBJ_DIR)\sprite.obj:  sprite.c sprite.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\sprite.obj $(mycflag) \
    $(cvars) sprite.c

$(OBJ_DIR)\gfx.obj:  gfx.c gfx.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\gfx.obj $(mycflag) \
    $(cvars) gfx.c

$(OBJ_DIR)\bmp.obj:  bmp.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\bmp.obj $(mycflag) \
    $(cvars) bmp.c

$(OBJ_DIR)\ddraw.obj:  ddraw.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\ddraw.obj $(mycflag) \
    $(cvars) ddraw.c

$(OBJ_DIR)\fbsound.obj:  fbsound.c fbsound.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\fbsound.obj $(mycflag) \
    $(cvars) fbsound.c

..\misc\$(OBJ_DIR)\dsutil.obj:  ..\misc\dsutil.c ..\misc\dsutil.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\dsutil.obj $(mycflag) \
    $(cvars) ..\misc\dsutil.c

$(OBJ_DIR)\$(proj).res: $(proj).rc
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res $(proj).def  
     -cd ..\fastfile
     -nmake -i $(makeflag)
     -cd ..\foxbear
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib  dsound.lib winmm.lib dxguid.lib \
           ..\fastfile\$(OBJ_DIR)\fastfile.lib

mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    if not exist ..\misc\$(OBJ_DIR)\NUL md ..\misc\$(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -echo y | del ..\misc\Retail
    -echo y | del ..\misc\Debug
    -rd Retail
    -rd Debug
    -rd ..\misc\Retail
    -rd ..\misc\Debug
    -cd ..\fastfile
    -nmake -i clean
    -cd ..\foxbear
