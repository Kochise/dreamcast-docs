!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=quat

OBJ_LIST = $(OBJ_DIR)\$(proj).obj  ..\misc\$(OBJ_DIR)\rmmain.obj \
           ..\misc\$(OBJ_DIR)\rmerror.obj

mycflag=/I "..\misc" -DD3DRMDEMO

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\$(proj).obj $(mycflag) \
    $(cvars) $(proj).c

..\misc\$(OBJ_DIR)\rmmain.obj:  ..\misc\rmmain.cpp
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\rmmain.obj $(mycflag) \
    $(cvars) ..\misc\rmmain.cpp
	
..\misc\$(OBJ_DIR)\rmerror.obj:  ..\misc\rmerror.c
    $(cc) $(cdebug) $(cflags) -Fo..\misc\$(OBJ_DIR)\rmerror.obj $(mycflag) \
    $(cvars) ..\misc\rmerror.c

..\misc\$(OBJ_DIR)\rmmain.res: ..\misc\rmmain.rc
   rc -i..\misc -r -fo  ..\misc\$(OBJ_DIR)\rmmain.res ..\misc\rmmain.rc
	

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) ..\misc\$(OBJ_DIR)\rmmain.res $(proj).def  
     $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) ..\misc\$(OBJ_DIR)\rmmain.res \
           $(guilibs) ddraw.lib d3drm.lib

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
