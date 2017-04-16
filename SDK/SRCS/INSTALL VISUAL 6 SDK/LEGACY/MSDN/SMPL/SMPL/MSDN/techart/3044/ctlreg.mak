# Microsoft Visual C++ generated build script - Do not modify

PROJ = CTLREG
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\ARTICLES\SAMPLES\CTLREG\
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"CTLREG.PDB"
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /FR /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = lafxcwd ole2.lib ole2.lib oldnames libw llibcew commdlg.lib olecli.lib shell.lib ver.lib 
LIBS_R_WEXE = lafxcw ole2.lib oldnames libw llibcew commdlg.lib shell.lib ver.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = CTLREG.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		CTLREG.SBR \
		MAINFRM.SBR \
		CTLREDOC.SBR \
		CTLREVW.SBR \
		CCTLREG.SBR \
		UNREGDLG.SBR


CTLREG_RCDEP = c:\articles\samples\ctlreg\res\ctlreg.ico \
	c:\articles\samples\ctlreg\res\ctlreg.rc2


STDAFX_DEP = c:\articles\samples\ctlreg\stdafx.h


CTLREG_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\ctlreg.h \
	c:\articles\samples\ctlreg\mainfrm.h \
	c:\articles\samples\ctlreg\ctlredoc.h \
	c:\articles\samples\ctlreg\ctlrevw.h


MAINFRM_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\ctlreg.h \
	c:\articles\samples\ctlreg\mainfrm.h


CTLREDOC_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\ctlreg.h \
	c:\articles\samples\ctlreg\ctlredoc.h


CTLREVW_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\ctlreg.h \
	c:\articles\samples\ctlreg\ctlredoc.h \
	c:\articles\samples\ctlreg\ctlrevw.h


CCTLREG_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\cctlreg.h


UNREGDLG_DEP = c:\articles\samples\ctlreg\stdafx.h \
	c:\articles\samples\ctlreg\ctlreg.h \
	c:\articles\samples\ctlreg\unregdlg.h


all:	$(PROJ).EXE $(PROJ).BSC

CTLREG.RES:	CTLREG.RC $(CTLREG_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r CTLREG.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

CTLREG.OBJ:	CTLREG.CPP $(CTLREG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CTLREG.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CTLREDOC.OBJ:	CTLREDOC.CPP $(CTLREDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CTLREDOC.CPP

CTLREVW.OBJ:	CTLREVW.CPP $(CTLREVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CTLREVW.CPP

CCTLREG.OBJ:	CCTLREG.CPP $(CCTLREG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CCTLREG.CPP

UNREGDLG.OBJ:	UNREGDLG.CPP $(UNREGDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UNREGDLG.CPP


$(PROJ).EXE::	CTLREG.RES

$(PROJ).EXE::	STDAFX.OBJ CTLREG.OBJ MAINFRM.OBJ CTLREDOC.OBJ CTLREVW.OBJ CCTLREG.OBJ \
	UNREGDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
CTLREG.OBJ +
MAINFRM.OBJ +
CTLREDOC.OBJ +
CTLREVW.OBJ +
CCTLREG.OBJ +
UNREGDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
D:\MSVC\CDK16\LIB\+
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\msvc\ole2\samples\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) CTLREG.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	CTLREG.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) CTLREG.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
