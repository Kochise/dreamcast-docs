# Microsoft Visual C++ generated build script - Do not modify

PROJ = SCHOOLUI
DEBUG = 1
PROGTYPE = 1
CALLER =
ARGS =
DLLS =
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\PLUGPLAY\SAMPLE\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG =
CPPCREATEPCHFLAG =
CUSEPCHFLAG =
CPPUSEPCHFLAG =
FIRSTC = SCHOOLUI.C
FIRSTCPP =
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ASw /YX"configmg.h" /Od /D "_DEBUG" /D "STRICT" /I "c:\ddk\inc32" /FR /GD /Fd"SCHOOLUI.PDB"     /Fp"SCHOOLUI.PCH"
CFLAGS_R_WDLL = /nologo /G3 /W3 /ASw /YX"configmg.h" /O1 /D "NDEBUG" /D "STRICT" /I "c:\ddk\inc32" /FR /GD /Fp"SCHOOLUI.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = sdllcew oldnames libw c:\ddk\lib\commctrl.lib
LIBS_R_WDLL = sdllcew oldnames libw c:\ddk\lib\commctrl.lib
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS =
DEFFILE = SCHOOLUI.DEF
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
SBRS = SCHOOLUI.SBR


SCHOOLUI_DEP = c:\ddk\inc16\commctrl.h \
	c:\mstools\include\pshpack1.h \
	c:\mstools\include\poppack.h \
	c:\ddk\inc16\setupx.h \
	c:\ddk\inc16\prsht.h


all:	$(PROJ).DLL $(PROJ).BSC

SCHOOLUI.OBJ:	SCHOOLUI.C $(SCHOOLUI_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c SCHOOLUI.C

SCHOOLUI.RES:	SCHOOLUI.RC $(SCHOOLUI_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SCHOOLUI.RC


$(PROJ).DLL::	SCHOOLUI.RES

$(PROJ).DLL::	SCHOOLUI.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
SCHOOLUI.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\ddk\lib\+
c:\msvc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) SCHOOLUI.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	SCHOOLUI.RES
	if not exist MSVC.BND	$(RC) $(RESFLAGS) SCHOOLUI.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<

clean:
   del schoolui.sbr
   del schoolui.bsc
   del schoolui.pch
   del schoolui.aps
   del schoolui.res
   del schoolui.map
   del schoolui.obj
   del schoolui.pdb
   del schoolui.lib
   del schoolui.vcw
   del schoolui.wsp
