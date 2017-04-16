# Microsoft Visual C++ generated build script - Do not modify

PROJ = W32PEN
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = K:\A-JASONS\JPW32PEN.BAK\W32PEN\ 
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = PENSTUFF.C
FIRSTCPP = 
RC = rc
CFLAGS_D_WEXE32 = /nologo /W3 /Zi /YX /D "_X86_" /D "_DEBUG" /D "_WINDOWS" /ML /Fd"W32PEN.PDB" /Fp"W32PEN.PCH"
CFLAGS_R_WEXE32 = /nologo /W3 /YX /O2 /D "_X86_" /D "NDEBUG" /D "_WINDOWS" /FR /ML /Fp"W32PEN.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib version.lib winmm.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
LFLAGS_D_LIB32 = /NOLOGO
LFLAGS_R_LIB32 = /NOLOGO
LIBS_D_WEXE32 = 
LIBS_R_WEXE32 = 
RCFLAGS32 = 
D_RCDEFINES32 = -d_DEBUG
R_RCDEFINES32 = -dNDEBUG
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE32)
LFLAGS = $(LFLAGS_D_WEXE32)
LIBS = $(LIBS_D_WEXE32)
LFLAGS_LIB=$(LFLAGS_D_LIB32)
MAPFILE_OPTION = 
RCDEFINES = $(D_RCDEFINES32)
!else
CFLAGS = $(CFLAGS_R_WEXE32)
LFLAGS = $(LFLAGS_R_WEXE32)
LIBS = $(LIBS_R_WEXE32)
MAPFILE_OPTION = 
LFLAGS_LIB=$(LFLAGS_R_LIB32)
RCDEFINES = $(R_RCDEFINES32)
!endif
SBRS = PENSTUFF.SBR \
		W32PEN.SBR \
		WNDPROC.SBR


PENSTUFF_DEP =  \
	d:\msvcnt\include\colordlg.h \
	k:\a-jasons\jpw32pen.bak\w32pen\w32pen.h


W32PEN_DEP =  \
	d:\msvcnt\include\colordlg.h \
	k:\a-jasons\jpw32pen.bak\w32pen\w32pen.h


WNDPROC_DEP =  \
	d:\msvcnt\include\colordlg.h \
	k:\a-jasons\jpw32pen.bak\w32pen\w32pen.h


W32PEN_RCDEP =  \
	k:\a-jasons\jpw32pen.bak\w32pen\w32pen.h \
	k:\a-jasons\jpw32pen.bak\w32pen\w32pen.ico \
	k:\a-jasons\jpw32pen.bak\w32pen\pencur.cur \
	k:\a-jasons\jpw32pen.bak\w32pen\bitmap1.bmp \
	k:\a-jasons\jpw32pen.bak\w32pen\bitmap4.bmp


all:	$(PROJ).EXE

PENSTUFF.OBJ:	PENSTUFF.C $(PENSTUFF_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c PENSTUFF.C

W32PEN.OBJ:	W32PEN.C $(W32PEN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c W32PEN.C

WNDPROC.OBJ:	WNDPROC.C $(WNDPROC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c WNDPROC.C

W32PEN.RES:	W32PEN.RC $(W32PEN_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r W32PEN.RC


$(PROJ).EXE:	W32PEN.RES

$(PROJ).EXE:	PENSTUFF.OBJ W32PEN.OBJ WNDPROC.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
PENSTUFF.OBJ 
W32PEN.OBJ 
WNDPROC.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
W32PEN.RES
$(LIBS)
$(LIBS_EXT)
$(DEFFILE_OPTION) -implib:$(PROJ).lib
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
