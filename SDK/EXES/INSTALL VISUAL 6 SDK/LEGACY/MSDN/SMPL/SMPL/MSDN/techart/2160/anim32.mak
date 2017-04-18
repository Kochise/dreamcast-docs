# Microsoft Visual C++ generated build script - Do not modify

PROJ = ANIM32
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\APPS\ANIM32\ 
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
CFLAGS_D_WEXE32 = /nologo /G3 /W3 /Zi /D "_X86_" /D "_DEBUG" /D "_WINDOWS" /Fr /ML /Fd"ANIM32.PDB" /Fp"ANIM32.PCH"
CFLAGS_R_WEXE32 = /nologo /W3 /Ox /D "_X86_" /D "NDEBUG" /D "_WINDOWS" /FR /ML /Fp"ANIM32.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /MAP /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows nafxcwd.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib
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
		ANIM32.SBR \
		MAINFRM.SBR \
		ANIMDOC.SBR \
		ANIMVW.SBR \
		DIB.SBR \
		DIBPAL.SBR \
		SPRITE.SBR \
		SPRITELS.SBR \
		OSDIBVW.SBR \
		DBGWND.SBR \
		SPLSNO.SBR \
		RECTLS.SBR \
		SPRITEDL.SBR \
		ANIMSP.SBR \
		PHSPRITE.SBR


ANIM32_RCDEP =  \
	c:\apps\anim32\res\anim32.ico \
	c:\apps\anim32\res\debug.ico \
	c:\apps\anim32\res\anim32.rc2


STDAFX_DEP =  \
	c:\apps\anim32\stdafx.h


ANIM32_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\mainfrm.h \
	c:\apps\anim32\animdoc.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h \
	c:\apps\anim32\animvw.h \
	c:\apps\anim32\osdibvw.h \
	c:\apps\anim32\dibpal.h \
	c:\apps\anim32\rectls.h


MAINFRM_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\mainfrm.h \
	c:\apps\anim32\animdoc.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h


ANIMDOC_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\animdoc.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h


ANIMVW_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\animdoc.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h \
	c:\apps\anim32\animvw.h \
	c:\apps\anim32\osdibvw.h \
	c:\apps\anim32\dibpal.h \
	c:\apps\anim32\rectls.h \
	c:\apps\anim32\animsp.h \
	c:\apps\anim32\phsprite.h


DIB_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\dib.h


DIBPAL_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\dibpal.h \
	c:\apps\anim32\dib.h


SPRITE_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spriteno.h \
	c:\apps\anim32\spritedl.h


SPRITELS_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h


OSDIBVW_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\osdibvw.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\dibpal.h \
	c:\apps\anim32\animdoc.h


DBGWND_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\dbgwnd.h


SPLSNO_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\animdoc.h \
	c:\apps\anim32\dib.h \
	c:\apps\anim32\spritels.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\splsno.h \
	c:\apps\anim32\spriteno.h


RECTLS_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\rectls.h


SPRITEDL_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\spritedl.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\dib.h


ANIMSP_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\animsp.h \
	c:\apps\anim32\phsprite.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\dib.h


PHSPRITE_DEP =  \
	c:\apps\anim32\stdafx.h \
	c:\apps\anim32\anim32.h \
	c:\apps\anim32\dbgwnd.h \
	c:\apps\anim32\sprite.h \
	c:\apps\anim32\dib.h


all:	$(PROJ).EXE $(PROJ).BSC

ANIM32.RES:	ANIM32.RC $(ANIM32_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r ANIM32.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

ANIM32.OBJ:	ANIM32.CPP $(ANIM32_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIM32.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

ANIMDOC.OBJ:	ANIMDOC.CPP $(ANIMDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIMDOC.CPP

ANIMVW.OBJ:	ANIMVW.CPP $(ANIMVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIMVW.CPP

DIB.OBJ:	DIB.CPP $(DIB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIB.CPP

DIBPAL.OBJ:	DIBPAL.CPP $(DIBPAL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIBPAL.CPP

SPRITE.OBJ:	SPRITE.CPP $(SPRITE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITE.CPP

SPRITELS.OBJ:	SPRITELS.CPP $(SPRITELS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITELS.CPP

OSDIBVW.OBJ:	OSDIBVW.CPP $(OSDIBVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OSDIBVW.CPP

DBGWND.OBJ:	DBGWND.CPP $(DBGWND_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBGWND.CPP

SPLSNO.OBJ:	SPLSNO.CPP $(SPLSNO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPLSNO.CPP

RECTLS.OBJ:	RECTLS.CPP $(RECTLS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RECTLS.CPP

SPRITEDL.OBJ:	SPRITEDL.CPP $(SPRITEDL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITEDL.CPP

ANIMSP.OBJ:	ANIMSP.CPP $(ANIMSP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIMSP.CPP

PHSPRITE.OBJ:	PHSPRITE.CPP $(PHSPRITE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PHSPRITE.CPP


$(PROJ).EXE:	ANIM32.RES

$(PROJ).EXE:	STDAFX.OBJ ANIM32.OBJ MAINFRM.OBJ ANIMDOC.OBJ ANIMVW.OBJ DIB.OBJ DIBPAL.OBJ \
	SPRITE.OBJ SPRITELS.OBJ OSDIBVW.OBJ DBGWND.OBJ SPLSNO.OBJ RECTLS.OBJ SPRITEDL.OBJ \
	ANIMSP.OBJ PHSPRITE.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
ANIM32.OBJ 
MAINFRM.OBJ 
ANIMDOC.OBJ 
ANIMVW.OBJ 
DIB.OBJ 
DIBPAL.OBJ 
SPRITE.OBJ 
SPRITELS.OBJ 
OSDIBVW.OBJ 
DBGWND.OBJ 
SPLSNO.OBJ 
RECTLS.OBJ 
SPRITEDL.OBJ 
ANIMSP.OBJ 
PHSPRITE.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
ANIM32.RES
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
