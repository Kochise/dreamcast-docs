# Microsoft Visual C++ generated build script - Do not modify

PROJ = NATIVEVB
DEBUG = 1
PROGTYPE = 1
CALLER = D:\VB3\VB.exe Perf0.MAK
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\INBOX\VBTNOTE1\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = MSDNVB01.C  
FIRSTCPP = SUMINFO.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /GD /ALw /Fd"MSDNVB01.PDB"
CFLAGS_R_WDLL = /nologo /W3 /FR /O1 /DNDEBUG /GD /ALw
LFLAGS_D_WDLL = /NOLOGO /NOD /PACKC:61440 /ALIGN:32 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew vbapi moleuicd moleuidd storage ole2 commdlg.lib olecli.lib olesvr.lib shell.lib toolhelp.lib ver.lib 
LIBS_R_WDLL = oldnames libw ldllcew vbapi moleuic moleuid storage ole2 commdlg.lib olecli.lib olesvr.lib shell.lib toolhelp.lib ver.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = NATIVEVB.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = INI_FUNC.SBR \
		VERSTAMP.SBR \
		DIRPATHS.SBR \
		NETWORK.SBR \
		HLSTR.SBR \
		SUMINFO.SBR \
		NATIVEVB.SBR


INI_FUNC_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


VERSTAMP_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h \
	d:\inbox\vbtnote1\verstamp.h


DIRPATHS_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


NETWORK_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


HLSTR_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


SUMINFO_DEP = c:\msvc\ole2\include\suminfo.h \
	c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


NATIVEVB_DEP = c:\vb\cdk\vbapi.h \
	d:\inbox\vbtnote1\nativevb.h


NATIVEVB_RCDEP = d:\inbox\vbtnote1\nativevb.rcv


all:	$(PROJ).DLL $(PROJ).BSC

INI_FUNC.OBJ:	INI_FUNC.C $(INI_FUNC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c INI_FUNC.C

VERSTAMP.OBJ:	VERSTAMP.C $(VERSTAMP_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c VERSTAMP.C

DIRPATHS.OBJ:	DIRPATHS.C $(DIRPATHS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c DIRPATHS.C

NETWORK.OBJ:	NETWORK.C $(NETWORK_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c NETWORK.C

HLSTR.OBJ:	HLSTR.C $(HLSTR_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c HLSTR.C

SUMINFO.OBJ:	SUMINFO.CPP $(SUMINFO_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c SUMINFO.CPP

NATIVEVB.OBJ:	NATIVEVB.C $(NATIVEVB_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c NATIVEVB.C

NATIVEVB.RES:	NATIVEVB.RC $(NATIVEVB_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r NATIVEVB.RC


$(PROJ).DLL::	NATIVEVB.RES

$(PROJ).DLL::	INI_FUNC.OBJ VERSTAMP.OBJ DIRPATHS.OBJ NETWORK.OBJ HLSTR.OBJ SUMINFO.OBJ \
	NATIVEVB.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
INI_FUNC.OBJ +
VERSTAMP.OBJ +
DIRPATHS.OBJ +
NETWORK.OBJ +
HLSTR.OBJ +
SUMINFO.OBJ +
NATIVEVB.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
c:\msvc\ole2\lib\+
c:\wing\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) NATIVEVB.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	NATIVEVB.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) NATIVEVB.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
