# Microsoft Visual C++ generated build script - Do not modify

PROJ = ENUMDOC
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\APD\MSJ\SEP95.COL\ENUMDOC.NEW\
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /GA /Fd"ENUMDOC.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = ENUMDOC.DEF
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
		ENUMDOC.SBR \
		MAINFRM.SBR \
		DOC.SBR \
		VIEW.SBR \
		DOCENUM.SBR


ENUMDOC_RCDEP = c:\apd\msj\sep95.col\enumdoc.new\res\enumdoc.ico \
	c:\apd\msj\sep95.col\enumdoc.new\res\doca.ico \
	c:\apd\msj\sep95.col\enumdoc.new\res\docb.ico \
	c:\apd\msj\sep95.col\enumdoc.new\res\enumdoc.rc2


STDAFX_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h


ENUMDOC_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h \
	c:\apd\msj\sep95.col\enumdoc.new\enumdoc.h \
	c:\apd\msj\sep95.col\enumdoc.new\mainfrm.h \
	c:\apd\msj\sep95.col\enumdoc.new\doc.h \
	c:\apd\msj\sep95.col\enumdoc.new\view.h \
	c:\apd\msj\sep95.col\enumdoc.new\docenum.h


MAINFRM_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h \
	c:\apd\msj\sep95.col\enumdoc.new\enumdoc.h \
	c:\apd\msj\sep95.col\enumdoc.new\mainfrm.h


DOC_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h \
	c:\apd\msj\sep95.col\enumdoc.new\doc.h


VIEW_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h \
	c:\apd\msj\sep95.col\enumdoc.new\enumdoc.h \
	c:\apd\msj\sep95.col\enumdoc.new\doc.h \
	c:\apd\msj\sep95.col\enumdoc.new\view.h


DOCENUM_DEP = c:\apd\msj\sep95.col\enumdoc.new\stdafx.h \
	c:\apd\msj\sep95.col\enumdoc.new\docenum.h


all:	$(PROJ).EXE

ENUMDOC.RES:	ENUMDOC.RC $(ENUMDOC_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ENUMDOC.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

ENUMDOC.OBJ:	ENUMDOC.CPP $(ENUMDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ENUMDOC.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

DOC.OBJ:	DOC.CPP $(DOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOC.CPP

VIEW.OBJ:	VIEW.CPP $(VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEW.CPP

DOCENUM.OBJ:	DOCENUM.CPP $(DOCENUM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOCENUM.CPP


$(PROJ).EXE::	ENUMDOC.RES

$(PROJ).EXE::	STDAFX.OBJ ENUMDOC.OBJ MAINFRM.OBJ DOC.OBJ VIEW.OBJ DOCENUM.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
ENUMDOC.OBJ +
MAINFRM.OBJ +
DOC.OBJ +
VIEW.OBJ +
DOCENUM.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\mfx\+
d:\msvc15\mfc\lib\+
d:\msvc15\lib\+
d:\develop\vfwdk\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) ENUMDOC.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	ENUMDOC.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ENUMDOC.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
