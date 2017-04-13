!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WINRUI.LIB and WINCSV.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINRUI.H and WINCSV.H"
!endif


INCLUDE = $(INCLUDE);$(ISVINCS);
LIB     = $(LIB);$(ISVLIBS);

all: wrui3270.exe

OPTS = -c -AS -G2sw -Zip -W2 -Od -DWINDOWS
CC = cl $(OPTS)

OBJS = wrui3270.obj

wrui3270.obj: wrui3270.c
    $(CC) $*.c

wrui3270.res: wrui3270.rc
    rc -r  wrui3270.rc

wrui3270.exe: $(OBJS) wrui3270.lnk wrui3270.res wrui3270.def wrui3270.rc
    link @wrui3270.lnk
    rc wrui3270.RES wrui3270.exe
