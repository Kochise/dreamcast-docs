# Microsoft Visual C++ generated build script - Do not modify

PROJ = GRAVITY
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
ORIGIN_VER = 1.00
PROJPATH = C:\ARTICLES\SAMPLES\GRAVITY\ 
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
CFLAGS_D_WEXE32 = /nologo /D_X86_ /W3 /FR /D_DEBUG /Zi /D_WINDOWS /Fd"GRAVITY.PDB" /Fp"GRAVITY.PCH"
CFLAGS_R_WEXE32 = /nologo /D_X86_ /W3 /FR /Ox /DNDEBUG /D_WINDOWS /Fp"GRAVITY.PCH"
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
		GRAVITY.SBR \
		MAINFRM.SBR \
		ANIMDOC.SBR \
		ANIMVW.SBR \
		BODY.SBR \
		DIB.SBR \
		DIBPAL.SBR \
		OSDIBVW.SBR \
		PHSPRITE.SBR \
		RECTLS.SBR \
		SPLSNO.SBR \
		SPRITE.SBR \
		SPRITEDL.SBR \
		SPRITELS.SBR \
		TIMEDLG.SBR \
		UNI.SBR \
		UNIDLG.SBR


GRAVITY_RCDEP =  \
	c:\articles\samples\gravity\res\gravity.ico \
	c:\articles\samples\gravity\res\msdn.ico \
	c:\articles\samples\gravity\res\gravity.rc2


STDAFX_DEP =  \
	c:\articles\samples\gravity\stdafx.h


GRAVITY_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\mainfrm.h \
	c:\articles\samples\gravity\animdoc.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\body.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\uni.h \
	c:\articles\samples\gravity\animvw.h \
	c:\articles\samples\gravity\osdibvw.h \
	c:\articles\samples\gravity\dibpal.h \
	c:\articles\samples\gravity\rectls.h


MAINFRM_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\mainfrm.h


ANIMDOC_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\animdoc.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\body.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\uni.h


ANIMVW_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\animdoc.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\body.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\uni.h \
	c:\articles\samples\gravity\animvw.h \
	c:\articles\samples\gravity\osdibvw.h \
	c:\articles\samples\gravity\dibpal.h \
	c:\articles\samples\gravity\rectls.h


BODY_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\animdoc.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\body.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\uni.h \
	c:\articles\samples\gravity\spritedl.h


DIB_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\dib.h


DIBPAL_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\dibpal.h \
	c:\articles\samples\gravity\dib.h


OSDIBVW_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\osdibvw.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\dibpal.h \
	c:\articles\samples\gravity\animdoc.h


PHSPRITE_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\spriteno.h


RECTLS_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\rectls.h


SPLSNO_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\animdoc.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\body.h \
	c:\articles\samples\gravity\phsprite.h \
	c:\articles\samples\gravity\uni.h


SPRITE_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\spriteno.h \
	c:\articles\samples\gravity\spritedl.h


SPRITEDL_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\spritedl.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\dib.h


SPRITELS_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\spritels.h \
	c:\articles\samples\gravity\sprite.h \
	c:\articles\samples\gravity\dib.h \
	c:\articles\samples\gravity\splsno.h \
	c:\articles\samples\gravity\spriteno.h


TIMEDLG_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\timedlg.h \
	c:\articles\samples\gravity\uni.h


UNI_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\uni.h \
	c:\articles\samples\gravity\unidlg.h \
	c:\articles\samples\gravity\timedlg.h


UNIDLG_DEP =  \
	c:\articles\samples\gravity\stdafx.h \
	c:\articles\samples\gravity\gravity.h \
	c:\articles\samples\gravity\unidlg.h \
	c:\articles\samples\gravity\uni.h


all:	$(PROJ).EXE $(PROJ).BSC

GRAVITY.RES:	GRAVITY.RC $(GRAVITY_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r GRAVITY.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

GRAVITY.OBJ:	GRAVITY.CPP $(GRAVITY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GRAVITY.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

ANIMDOC.OBJ:	ANIMDOC.CPP $(ANIMDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIMDOC.CPP

ANIMVW.OBJ:	ANIMVW.CPP $(ANIMVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ANIMVW.CPP

BODY.OBJ:	BODY.CPP $(BODY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BODY.CPP

DIB.OBJ:	DIB.CPP $(DIB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIB.CPP

DIBPAL.OBJ:	DIBPAL.CPP $(DIBPAL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIBPAL.CPP

OSDIBVW.OBJ:	OSDIBVW.CPP $(OSDIBVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OSDIBVW.CPP

PHSPRITE.OBJ:	PHSPRITE.CPP $(PHSPRITE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PHSPRITE.CPP

RECTLS.OBJ:	RECTLS.CPP $(RECTLS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RECTLS.CPP

SPLSNO.OBJ:	SPLSNO.CPP $(SPLSNO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPLSNO.CPP

SPRITE.OBJ:	SPRITE.CPP $(SPRITE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITE.CPP

SPRITEDL.OBJ:	SPRITEDL.CPP $(SPRITEDL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITEDL.CPP

SPRITELS.OBJ:	SPRITELS.CPP $(SPRITELS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPRITELS.CPP

TIMEDLG.OBJ:	TIMEDLG.CPP $(TIMEDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TIMEDLG.CPP

UNI.OBJ:	UNI.CPP $(UNI_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UNI.CPP

UNIDLG.OBJ:	UNIDLG.CPP $(UNIDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UNIDLG.CPP


$(PROJ).EXE:	GRAVITY.RES

$(PROJ).EXE:	STDAFX.OBJ GRAVITY.OBJ MAINFRM.OBJ ANIMDOC.OBJ ANIMVW.OBJ BODY.OBJ DIB.OBJ \
	DIBPAL.OBJ OSDIBVW.OBJ PHSPRITE.OBJ RECTLS.OBJ SPLSNO.OBJ SPRITE.OBJ SPRITEDL.OBJ \
	SPRITELS.OBJ TIMEDLG.OBJ UNI.OBJ UNIDLG.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ 
GRAVITY.OBJ 
MAINFRM.OBJ 
ANIMDOC.OBJ 
ANIMVW.OBJ 
BODY.OBJ 
DIB.OBJ 
DIBPAL.OBJ 
OSDIBVW.OBJ 
PHSPRITE.OBJ 
RECTLS.OBJ 
SPLSNO.OBJ 
SPRITE.OBJ 
SPRITEDL.OBJ 
SPRITELS.OBJ 
TIMEDLG.OBJ 
UNI.OBJ 
UNIDLG.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
GRAVITY.RES
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
