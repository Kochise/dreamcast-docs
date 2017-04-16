# Microsoft Visual C++ generated build script - Do not modify

PROJ = DCLIKBAR
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MSJ\JAN96.COL\DCLIKBAR\
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /GA /Fd"DCLIKBAR.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DCLIKBAR.DEF
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
		DCLIKBAR.SBR \
		MAINFRM.SBR \
		DOC.SBR \
		VIEW.SBR


DCLIKBAR_RCDEP = c:\msj\jan96.col\dclikbar\res\app.ico \
	c:\msj\jan96.col\dclikbar\res\doc.ico \
	c:\msj\jan96.col\dclikbar\res\app.rc2


STDAFX_DEP = c:\msj\jan96.col\dclikbar\stdafx.h


DCLIKBAR_DEP = c:\msj\jan96.col\dclikbar\stdafx.h \
	c:\msj\jan96.col\dclikbar\dclikbar.h \
	c:\msj\jan96.col\dclikbar\mainfrm.h \
	c:\msj\jan96.col\dclikbar\doc.h \
	c:\msj\jan96.col\dclikbar\view.h


MAINFRM_DEP = c:\msj\jan96.col\dclikbar\stdafx.h \
	c:\msj\jan96.col\dclikbar\dclikbar.h \
	c:\msj\jan96.col\dclikbar\mainfrm.h


DOC_DEP = c:\msj\jan96.col\dclikbar\stdafx.h \
	c:\msj\jan96.col\dclikbar\dclikbar.h \
	c:\msj\jan96.col\dclikbar\doc.h


VIEW_DEP = c:\msj\jan96.col\dclikbar\stdafx.h \
	c:\msj\jan96.col\dclikbar\dclikbar.h \
	c:\msj\jan96.col\dclikbar\doc.h \
	c:\msj\jan96.col\dclikbar\view.h


all:	$(PROJ).EXE

DCLIKBAR.RES:	DCLIKBAR.RC $(DCLIKBAR_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DCLIKBAR.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DCLIKBAR.OBJ:	DCLIKBAR.CPP $(DCLIKBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DCLIKBAR.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

DOC.OBJ:	DOC.CPP $(DOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOC.CPP

VIEW.OBJ:	VIEW.CPP $(VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEW.CPP


$(PROJ).EXE::	DCLIKBAR.RES

$(PROJ).EXE::	STDAFX.OBJ DCLIKBAR.OBJ MAINFRM.OBJ DOC.OBJ VIEW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DCLIKBAR.OBJ +
MAINFRM.OBJ +
DOC.OBJ +
VIEW.OBJ +
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
	$(RC) $(RESFLAGS) DCLIKBAR.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DCLIKBAR.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DCLIKBAR.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
