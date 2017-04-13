!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=duel

OBJ_LIST = $(OBJ_DIR)\$(proj).obj ..\misc\$(OBJ_DIR)\ddutil.obj \
           $(OBJ_DIR)\util.obj $(OBJ_DIR)\wizard.obj \
           $(OBJ_DIR)\gameproc.obj $(OBJ_DIR)\gfx.obj $(OBJ_DIR)\comm.obj \
           $(OBJ_DIR)\input.obj $(OBJ_DIR)\lobby.obj \
           $(OBJ_DIR)\ds3dutil.obj $(OBJ_DIR)\sfx.obj

mycflag=/I "..\misc"

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c resource.h ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).c
	
..\misc\$(OBJ_DIR)\ddutil.obj:  ..\misc\ddutil.cpp ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\ddutil.obj $(mycflag) \
    $(cvars) ..\misc\ddutil.cpp

$(OBJ_DIR)\util.obj:  util.c util.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\util.obj $(mycflag) \
    $(cvars) util.c

$(OBJ_DIR)\wizard.obj:  wizard.c wizard.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\wizard.obj $(mycflag) \
    $(cvars) wizard.c

$(OBJ_DIR)\gameproc.obj:  gameproc.c gameproc.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\gameproc.obj $(mycflag) \
    $(cvars) gameproc.c

$(OBJ_DIR)\gfx.obj:  gfx.c gfx.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\gfx.obj $(mycflag) \
    $(cvars) gfx.c

$(OBJ_DIR)\comm.obj:  comm.c comm.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\comm.obj $(mycflag) \
    $(cvars) comm.c

$(OBJ_DIR)\input.obj:  input.c input.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\input.obj $(mycflag) \
    $(cvars) input.c

$(OBJ_DIR)\lobby.obj:  lobby.c lobby.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\lobby.obj $(mycflag) \
    $(cvars) lobby.c

$(OBJ_DIR)\ds3dutil.obj:  ds3dutil.c ds3dutil.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\ds3dutil.obj $(mycflag) \
    $(cvars) ds3dutil.c

$(OBJ_DIR)\sfx.obj:  sfx.c sfx.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\sfx.obj $(mycflag) \
    $(cvars) sfx.c


$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib dplayx.lib winmm.lib dinput.lib dsound.lib \
           comctl32.lib ole32.lib

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    @if not exist ..\misc\$(OBJ_DIR)\NUL md ..\misc\$(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@echo y | del ..\misc\Retail
    -@echo y | del ..\misc\Debug
    -@rd Retail
    -@rd Debug
    -@rd ..\misc\Retail
    -@rd ..\misc\Debug
