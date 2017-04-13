!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=donuts
cflags = -DUSE_DSOUND $(cflags)

OBJ_LIST = $(OBJ_DIR)\$(proj).obj ..\misc\$(OBJ_DIR)\ddutil.obj \
           ..\misc\$(OBJ_DIR)\dsutil.obj $(OBJ_DIR)\input.obj

mycflag=/I "..\misc"

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c resource.h ..\misc\ddutil.h \
    ..\misc\dsutil.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).c

$(OBJ_DIR)\input.obj:  input.c input.h
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\input.obj $(mycflag) \
    $(cvars) input.c

..\misc\$(OBJ_DIR)\dsutil.obj:  ..\misc\dsutil.c ..\misc\dsutil.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\dsutil.obj $(mycflag) \
    $(cvars) ..\misc\dsutil.c

..\misc\$(OBJ_DIR)\ddutil.obj:  ..\misc\ddutil.cpp ..\misc\ddutil.h
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\ddutil.obj $(mycflag) \
    $(cvars) ..\misc\ddutil.cpp

$(OBJ_DIR)\$(proj).res: $(proj).rc resource.h
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res\
           $(guilibs) ddraw.lib dsound.lib winmm.lib dinput.lib dxguid.lib
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
