!include <win32.mak>

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

proj=dxview

OBJ_LIST = $(OBJ_DIR)\$(proj).obj $(OBJ_DIR)\dxprint.obj $(OBJ_DIR)\dinput.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\$(proj).obj:  $(proj).c $(proj).h
    $(cc) $(cdebug) $(cflags) -DDX_3D -DDX5 -Fo$(OBJ_DIR)\$(proj).obj $(cvars) $(proj).c
	
$(OBJ_DIR)\dxprint.obj: dxprint.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dxprint.obj $(cvars) dxprint.c

$(OBJ_DIR)\dinput.obj: dinput.c
    $(cc) $(cdebug) $(cflags) -Fo$(OBJ_DIR)\dinput.obj $(cvars) dinput.c

$(OBJ_DIR)\$(proj).res: $(proj).rc 
   rc -r -fo $(OBJ_DIR)\$(proj).res $(proj).rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(guiflags) -out:$(OBJ_DIR)\$(proj).exe \
           $(OBJ_LIST) $(OBJ_DIR)\$(proj).res \
           $(guilibs) ddraw.lib comctl32.lib dplayx.lib \
           ole32.lib dinput.lib dxguid.lib winmm.lib 
                                                              
mkdir:
    if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -echo y | del Retail
    -echo y | del Debug
    -rd Retail
    -rd Debug
