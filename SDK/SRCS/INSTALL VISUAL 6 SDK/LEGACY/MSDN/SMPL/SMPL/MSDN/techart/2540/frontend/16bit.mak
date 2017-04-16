# Microsoft Visual C++ generated build script - Do not modify

PROJ = 16BIT
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\WIN95\DDK\BASE\SAMPLES\CALLBACK\FRONTEND\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = 16BIT.CPP   
RC = rc
CFLAGS_D_WEXE = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /AM /GA /Fd"16BIT.PDB"
CFLAGS_R_WEXE = /nologo /W3 /FR /O1 /DNDEBUG /AM /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew receiver commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = 16BIT.DEF
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
SBRS = 16BIT.SBR \
		16BITDOC.SBR \
		16BITVW.SBR \
		LINKSTR.SBR \
		MAINFRM.SBR \
		STDAFX.SBR


16BIT_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h \
	c:\win95\ddk\base\samples\callback\frontend\16bit.h \
	c:\win95\ddk\base\samples\callback\frontend\mainfrm.h \
	c:\win95\ddk\base\samples\callback\frontend\16bitdoc.h \
	c:\win95\ddk\base\samples\callback\frontend\16bitvw.h


16BITDOC_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h \
	c:\win95\ddk\base\samples\callback\frontend\16bit.h \
	c:\win95\ddk\base\samples\callback\frontend\16bitdoc.h


16BITVW_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h \
	c:\win95\ddk\base\samples\callback\frontend\16bit.h \
	c:\win95\ddk\base\samples\callback\frontend\linkstr.h \
	c:\win95\ddk\base\samples\callback\frontend\16bitdoc.h \
	c:\win95\ddk\base\samples\callback\frontend\16bitvw.h \
	c:\win95\ddk\base\samples\callback\frontend\receiver.h \
	c:\win95\ddk\base\samples\callback\frontend\helper.h


LINKSTR_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h \
	c:\win95\ddk\base\samples\callback\frontend\linkstr.h


MAINFRM_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h \
	c:\win95\ddk\base\samples\callback\frontend\16bit.h \
	c:\win95\ddk\base\samples\callback\frontend\mainfrm.h


STDAFX_DEP = c:\win95\ddk\base\samples\callback\frontend\stdafx.h


16BIT_RCDEP = c:\win95\ddk\base\samples\callback\frontend\res\16bit.ico \
	c:\win95\ddk\base\samples\callback\frontend\res\16bit.rc2


all:	$(PROJ).EXE $(PROJ).BSC

16BIT.OBJ:	16BIT.CPP $(16BIT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c 16BIT.CPP

16BITDOC.OBJ:	16BITDOC.CPP $(16BITDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 16BITDOC.CPP

16BITVW.OBJ:	16BITVW.CPP $(16BITVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 16BITVW.CPP

LINKSTR.OBJ:	LINKSTR.CPP $(LINKSTR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LINKSTR.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP

16BIT.RES:	16BIT.RC $(16BIT_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r 16BIT.RC


$(PROJ).EXE::	16BIT.RES

$(PROJ).EXE::	16BIT.OBJ 16BITDOC.OBJ 16BITVW.OBJ LINKSTR.OBJ MAINFRM.OBJ STDAFX.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
16BIT.OBJ +
16BITDOC.OBJ +
16BITVW.OBJ +
LINKSTR.OBJ +
MAINFRM.OBJ +
STDAFX.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
m:\msvc16\lib\+
m:\msvc16\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) 16BIT.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	16BIT.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) 16BIT.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
