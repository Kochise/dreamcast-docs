
!if "$(ISVLIBS)"==""
!error "Set ISVLIBS to the directory containing WINSLI.LIB and WINCSV.LIB
!endif
!if "$(ISVINCS)"==""
!error "Set ISVINCS to the directory containing WINSLI.H and WINCSV.H"
!endif


INCLUDE = $(INCLUDE);$(ISVINCS);
LIB     = $(LIB);$(ISVLIBS);

all: wsli3270.exe

OPTS = -c -AS -G2sw -Zip -W2 -Od -DWINDOWS
CC = cl $(OPTS)

OBJS = wsli3270.obj

wsli3270.obj: wsli3270.c
    $(CC) $*.c

wsli3270.res: wsli3270.rc
    rc -r  wsli3270.rc

wsli3270.exe: $(OBJS) wsli3270.lnk wsli3270.res wsli3270.def wsli3270.rc
    link @wsli3270.lnk
    rc wsli3270.RES wsli3270.exe
