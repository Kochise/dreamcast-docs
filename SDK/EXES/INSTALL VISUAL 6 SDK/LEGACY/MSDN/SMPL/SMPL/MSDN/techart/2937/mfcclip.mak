# Microsoft Visual C++ generated build script - Do not modify

PROJ = MFCCLIP
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\APPS\MFCCLIP\ 
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC = 
FIRSTCPP = STDAFX.CPP
RC = rc
CFLAGS_D_WEXE32 = /nologo /D_X86_ /W3 /FR /D_DEBUG /Zi /D_WINDOWS /Fd"MFCCLIP.PDB" /Fp"MFCCLIP.PCH"
CFLAGS_R_WEXE32 = /nologo /D_X86_ /W3 /FR /Ox /DNDEBUG /D_WINDOWS /Fp"MFCCLIP.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows nafxcwd.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows nafxcw.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
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
		MFCCLIP.SBR \
		MAINFRM.SBR \
		CLIPDOC.SBR \
		CLIPVW.SBR \
		MYOBJ.SBR \
		MYOBLIST.SBR \
		MYOBJDLG.SBR \
		TRANSBMP.SBR


MFCCLIP_RCDEP =  \
	c:\apps\mfcclip\res\mfcclip.ico \
	c:\apps\mfcclip\res\smile.bmp \
	c:\apps\mfcclip\res\mfcclip.rc2


STDAFX_DEP =  \
	c:\apps\mfcclip\stdafx.h


MFCCLIP_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\transbmp.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\myobj.h \
	c:\apps\mfcclip\myoblist.h \
	c:\apps\mfcclip\mainfrm.h \
	c:\apps\mfcclip\clipdoc.h \
	c:\apps\mfcclip\clipvw.h


MAINFRM_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\mainfrm.h


CLIPDOC_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\myobj.h \
	c:\apps\mfcclip\myoblist.h \
	c:\apps\mfcclip\clipdoc.h


CLIPVW_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\transbmp.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\myobj.h \
	c:\apps\mfcclip\myoblist.h \
	c:\apps\mfcclip\clipdoc.h \
	c:\apps\mfcclip\clipvw.h


MYOBJ_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\myobjdlg.h \
	c:\apps\mfcclip\myobj.h


MYOBLIST_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\myobj.h \
	c:\apps\mfcclip\myoblist.h


MYOBJDLG_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\mfcclip.h \
	c:\apps\mfcclip\myobjdlg.h


TRANSBMP_DEP =  \
	c:\apps\mfcclip\stdafx.h \
	c:\apps\mfcclip\transbmp.h


all:	$(PROJ).EXE $(PROJ).BSC

MFCCLIP.RES:	MFCCLIP.RC $(MFCCLIP_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r MFCCLIP.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MFCCLIP.OBJ:	MFCCLIP.CPP $(MFCCLIP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MFCCLIP.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CLIPDOC.OBJ:	CLIPDOC.CPP $(CLIPDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLIPDOC.CPP

CLIPVW.OBJ:	CLIPVW.CPP $(CLIPVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLIPVW.CPP

MYOBJ.OBJ:	MYOBJ.CPP $(MYOBJ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MYOBJ.CPP

MYOBLIST.OBJ:	MYOBLIST.CPP $(MYOBLIST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MYOBLIST.CPP

MYOBJDLG.OBJ:	MYOBJDLG.CPP $(MYOBJDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MYOBJDLG.CPP

TRANSBMP.OBJ:	TRANSBMP.CPP $(TRANSBMP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TRANSBMP.CPP


$(PROJ).EXE:	MFCCLIP.RES

$(PROJ).EXE:	STDAFX.OBJ MFCCLIP.OBJ MAINFRM.OBJ CLIPDOC.OBJ CLIPVW.OBJ MYOBJ.OBJ \
	MYOBLIST.OBJ MYOBJDLG.OBJ TRANSBMP.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
MFCCLIP.OBJ 
MAINFRM.OBJ 
CLIPDOC.OBJ 
CLIPVW.OBJ 
MYOBJ.OBJ 
MYOBLIST.OBJ 
MYOBJDLG.OBJ 
TRANSBMP.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
MFCCLIP.RES
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
