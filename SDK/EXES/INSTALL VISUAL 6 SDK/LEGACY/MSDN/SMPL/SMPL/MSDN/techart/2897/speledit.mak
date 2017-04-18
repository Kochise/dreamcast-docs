# Microsoft Visual C++ generated build script - Do not modify

PROJ = SPELEDIT
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\APPS\SPELLIT\SPELEDIT\ 
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
CFLAGS_D_WEXE32 = /nologo /D_X86_ /W3 /FR /D_DEBUG /Zi /D_WINDOWS /Fd"SPELEDIT.PDB" /Fp"SPELEDIT.PCH"
CFLAGS_R_WEXE32 = /nologo /D_X86_ /W3 /FR /Ox /DNDEBUG /D_WINDOWS /Fp"SPELEDIT.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows nafxcwd.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib winmm.lib ..\..\animate\lib\animated.lib
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
		SPELEDIT.SBR \
		MAINFRM.SBR \
		SPELLDOC.SBR \
		SPELLVW.SBR \
		ADDWDLG.SBR \
		WORDMAP.SBR \
		RECORDDL.SBR


SPELEDIT_RCDEP =  \
	c:\apps\spellit\speledit\res\speledit.ico \
	c:\apps\spellit\speledit\res\speledit.rc2


STDAFX_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h


SPELEDIT_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\speledit.h \
	c:\apps\spellit\speledit\mainfrm.h \
	c:\apps\spellit\speledit\spelldoc.h \
	c:\apps\spellit\speledit\wordmap.h \
	c:\apps\spellit\speledit\spellvw.h


MAINFRM_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\speledit.h \
	c:\apps\spellit\speledit\mainfrm.h


SPELLDOC_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\speledit.h \
	c:\apps\spellit\speledit\spelldoc.h \
	c:\apps\spellit\speledit\wordmap.h


SPELLVW_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\speledit.h \
	c:\apps\spellit\speledit\spelldoc.h \
	c:\apps\spellit\speledit\wordmap.h \
	c:\apps\spellit\speledit\spellvw.h \
	c:\apps\spellit\speledit\addwdlg.h


ADDWDLG_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\speledit.h \
	c:\apps\spellit\speledit\addwdlg.h \
	c:\apps\spellit\speledit\recorddl.h


WORDMAP_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\wordmap.h


RECORDDL_DEP =  \
	c:\apps\spellit\speledit\stdafx.h \
	c:\apps\animate\include\animate.h \
	c:\apps\spellit\speledit\recorddl.h


all:	$(PROJ).EXE $(PROJ).BSC

SPELEDIT.RES:	SPELEDIT.RC $(SPELEDIT_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r SPELEDIT.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

SPELEDIT.OBJ:	SPELEDIT.CPP $(SPELEDIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPELEDIT.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

SPELLDOC.OBJ:	SPELLDOC.CPP $(SPELLDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPELLDOC.CPP

SPELLVW.OBJ:	SPELLVW.CPP $(SPELLVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPELLVW.CPP

ADDWDLG.OBJ:	ADDWDLG.CPP $(ADDWDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ADDWDLG.CPP

WORDMAP.OBJ:	WORDMAP.CPP $(WORDMAP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORDMAP.CPP

RECORDDL.OBJ:	RECORDDL.CPP $(RECORDDL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RECORDDL.CPP


$(PROJ).EXE:	SPELEDIT.RES

$(PROJ).EXE:	STDAFX.OBJ SPELEDIT.OBJ MAINFRM.OBJ SPELLDOC.OBJ SPELLVW.OBJ ADDWDLG.OBJ \
	WORDMAP.OBJ RECORDDL.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
SPELEDIT.OBJ 
MAINFRM.OBJ 
SPELLDOC.OBJ 
SPELLVW.OBJ 
ADDWDLG.OBJ 
WORDMAP.OBJ 
RECORDDL.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
SPELEDIT.RES
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
