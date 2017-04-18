# Microsoft Visual C++ generated build script - Do not modify

PROJ = SPELLER
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\APPS\SPELLIT\SPELLER\ 
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
CFLAGS_D_WEXE32 = /nologo /D_X86_ /W3 /FR /D_DEBUG /Zi /D_WINDOWS /Fd"SPELLER.PDB" /Fp"SPELLER.PCH"
CFLAGS_R_WEXE32 = /nologo /D_X86_ /W3 /FR /Ox /DNDEBUG /D_WINDOWS /Fp"SPELLER.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows nafxcwd.lib ..\..\animate\lib\animated.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib winmm.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows nafxcw.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib winmm.lib ..\..\animate\lib\animater.lib
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
		SPELLER.SBR \
		MAINFRM.SBR \
		SPELLDOC.SBR \
		WORDVIEW.SBR \
		WORDMAP.SBR


SPELLER_RCDEP =  \
	c:\apps\spellit\speller\res\speller.ico \
	c:\apps\spellit\speller\res\speller.rc2


STDAFX_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h


SPELLER_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speller\speller.h \
	c:\apps\spellit\speller\mainfrm.h \
	c:\apps\spellit\speller\spelldoc.h \
	c:\apps\spellit\speller\wordmap.h \
	c:\apps\spellit\speller\wordview.h


MAINFRM_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speller\speller.h \
	c:\apps\spellit\speller\mainfrm.h


SPELLDOC_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speller\speller.h \
	c:\apps\spellit\speller\spelldoc.h \
	c:\apps\spellit\speller\wordmap.h


WORDVIEW_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speller\speller.h \
	c:\apps\spellit\speller\spelldoc.h \
	c:\apps\spellit\speller\wordmap.h \
	c:\apps\spellit\speller\wordview.h


WORDMAP_DEP =  \
	c:\apps\spellit\speller\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speller\wordmap.h


all:	$(PROJ).EXE $(PROJ).BSC

SPELLER.RES:	SPELLER.RC $(SPELLER_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r SPELLER.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

SPELLER.OBJ:	SPELLER.CPP $(SPELLER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPELLER.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

SPELLDOC.OBJ:	SPELLDOC.CPP $(SPELLDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPELLDOC.CPP

WORDVIEW.OBJ:	WORDVIEW.CPP $(WORDVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORDVIEW.CPP

WORDMAP.OBJ:	WORDMAP.CPP $(WORDMAP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORDMAP.CPP


$(PROJ).EXE:	SPELLER.RES

$(PROJ).EXE:	STDAFX.OBJ SPELLER.OBJ MAINFRM.OBJ SPELLDOC.OBJ WORDVIEW.OBJ WORDMAP.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
SPELLER.OBJ 
MAINFRM.OBJ 
SPELLDOC.OBJ 
WORDVIEW.OBJ 
WORDMAP.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
SPELLER.RES
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
