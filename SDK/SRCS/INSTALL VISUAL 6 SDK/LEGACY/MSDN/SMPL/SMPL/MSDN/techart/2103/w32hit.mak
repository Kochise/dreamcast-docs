# Microsoft Visual C++ generated build script - Do not modify

PROJ = W32HIT
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\DENNISCR\SAMPLES\W32HIT\ 
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = BEZIER.C
FIRSTCPP = 
RC = rc
CFLAGS_D_WEXE32 = /nologo /W3 /Zi /YX /D "_X86_" /D "_DEBUG" /D "_WINDOWS" /ML /Fd"W32HIT.PDB" /Fp"W32HIT.PCH"
CFLAGS_R_WEXE32 = /nologo /W3 /YX /O2 /D "_X86_" /D "NDEBUG" /D "_WINDOWS" /FR /ML /Fp"W32HIT.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /STACK:16000 /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib vector2d.lib version.lib
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
SBRS = BEZIER.SBR \
		HITTEST.SBR \
		W32PEN.SBR \
		WNDPROC.SBR \
		PENSTUFF.SBR


BEZIER_DEP =  \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h


HITTEST_DEP =  \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h


W32PEN_DEP =  \
	d:\msvcnt\include\colordlg.h \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h


WNDPROC_DEP =  \
	d:\msvcnt\include\colordlg.h \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h


W32PEN_RCDEP =  \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h \
	c:\denniscr\samples\w32hit\w32pen.ico \
	c:\denniscr\samples\w32hit\pencur.cur \
	c:\denniscr\samples\w32hit\bitmap1.bmp \
	c:\denniscr\samples\w32hit\bitmap4.bmp


PENSTUFF_DEP =  \
	d:\msvcnt\include\colordlg.h \
	c:\denniscr\samples\w32hit\w32pen.h \
	c:\denniscr\samples\w32hit\vector2d.h \
	c:\denniscr\samples\w32hit\bezier.h


all:	$(PROJ).EXE

BEZIER.OBJ:	BEZIER.C $(BEZIER_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c BEZIER.C

HITTEST.OBJ:	HITTEST.C $(HITTEST_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c HITTEST.C

W32PEN.OBJ:	W32PEN.C $(W32PEN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c W32PEN.C

WNDPROC.OBJ:	WNDPROC.C $(WNDPROC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c WNDPROC.C

W32PEN.RES:	W32PEN.RC $(W32PEN_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r W32PEN.RC

PENSTUFF.OBJ:	PENSTUFF.C $(PENSTUFF_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c PENSTUFF.C


$(PROJ).EXE:	W32PEN.RES

$(PROJ).EXE:	BEZIER.OBJ HITTEST.OBJ W32PEN.OBJ WNDPROC.OBJ PENSTUFF.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
BEZIER.OBJ 
HITTEST.OBJ 
W32PEN.OBJ 
WNDPROC.OBJ 
PENSTUFF.OBJ 
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
