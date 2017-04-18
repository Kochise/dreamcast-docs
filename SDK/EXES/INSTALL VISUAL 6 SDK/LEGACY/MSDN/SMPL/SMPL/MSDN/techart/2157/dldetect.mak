# Microsoft Visual C++ generated build script - Do not modify

PROJ = DLDETECT
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = D:\MSTOOLS\SAMPLES\DEADLOCK\FRONTEND\MFC\DLDMFC\DLDETECT\ 
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = 
FIRSTCPP = STDAFX.CPP
RC = rc
CFLAGS_D_WEXE32 = /nologo /W3 /Zi /YX /D "_X86_" /D "_DEBUG" /D "_WINDOWS" /FR /ML /Fd"DLDETECT.PDB" /Fp"DLDETECT.PCH"
CFLAGS_R_WEXE32 = /nologo /W3 /YX /Ox /D "_X86_" /D "NDEBUG" /D "_WINDOWS" /FR /ML /Fp"DLDETECT.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows nafxcwd.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib matrix.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows nafxcw.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib matrix.lib
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
SBRS = STDAFX.SBR \
		DLDETECT.SBR \
		MAINFRM.SBR \
		MATVIEW.SBR \
		CLASSES.SBR \
		TPPROPS.SBR \
		PNTDOC.SBR \
		NETVIEW.SBR \
		INVARIAN.SBR \
		GRIDSIZE.SBR


DLDETECT_RCDEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\res\dldetect.ico \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\res\dldetect.rc2


STDAFX_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h


DLDETECT_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h


MAINFRM_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h


MATVIEW_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h


CLASSES_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h


TPPROPS_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\tpprops.h


PNTDOC_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h


NETVIEW_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\tpprops.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\gridsize.h


INVARIAN_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h


GRIDSIZE_DEP =  \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\stdafx.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\dldetect.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matrix.hpp \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\classes.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\mainfrm.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\pntdoc.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\netview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\matview.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\invarian.h \
	d:\mstools\samples\deadlock\frontend\mfc\dldmfc\dldetect\gridsize.h


all:	$(PROJ).EXE $(PROJ).BSC

DLDETECT.RES:	DLDETECT.RC $(DLDETECT_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r DLDETECT.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DLDETECT.OBJ:	DLDETECT.CPP $(DLDETECT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLDETECT.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

MATVIEW.OBJ:	MATVIEW.CPP $(MATVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATVIEW.CPP

CLASSES.OBJ:	CLASSES.CPP $(CLASSES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLASSES.CPP

TPPROPS.OBJ:	TPPROPS.CPP $(TPPROPS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TPPROPS.CPP

PNTDOC.OBJ:	PNTDOC.CPP $(PNTDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PNTDOC.CPP

NETVIEW.OBJ:	NETVIEW.CPP $(NETVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c NETVIEW.CPP

INVARIAN.OBJ:	INVARIAN.CPP $(INVARIAN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c INVARIAN.CPP

GRIDSIZE.OBJ:	GRIDSIZE.CPP $(GRIDSIZE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GRIDSIZE.CPP


$(PROJ).EXE:	DLDETECT.RES

$(PROJ).EXE:	STDAFX.OBJ DLDETECT.OBJ MAINFRM.OBJ MATVIEW.OBJ CLASSES.OBJ TPPROPS.OBJ \
	PNTDOC.OBJ NETVIEW.OBJ INVARIAN.OBJ GRIDSIZE.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
DLDETECT.OBJ 
MAINFRM.OBJ 
MATVIEW.OBJ 
CLASSES.OBJ 
TPPROPS.OBJ 
PNTDOC.OBJ 
NETVIEW.OBJ 
INVARIAN.OBJ 
GRIDSIZE.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
DLDETECT.RES
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
