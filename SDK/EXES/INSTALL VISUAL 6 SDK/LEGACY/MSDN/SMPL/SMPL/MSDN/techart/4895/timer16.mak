# Microsoft Visual C++ generated build script - Do not modify

PROJ = TIMER16
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MSDEV\PROJECTS\LATENCY\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = TIMER16.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /Gs /G2 /W3 /Zi /AMw /Od /D "_DEBUG" /Gw /Fd"TIMER16.PDB"
CFLAGS_R_WDLL = /nologo /Gs /G2 /W3 /AMw /O1 /D "NDEBUG" /Gw 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /CO  
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE  
LIBS_D_WDLL = libw mdllcew oldnames mmsystem.lib 
LIBS_R_WDLL = libw mdllcew oldnames mmsystem.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = TIMER16.DEF
OBJS_EXT = THK16.OBJ 
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
SBRS = TIMER16.SBR


THK16_DEP = 

TIMER16_DEP = c:\msdev\projects\latency\timer.h \
	c:\msdev\projects\latency\timer16.h


all:	$(PROJ).DLL

TIMER16.OBJ:	TIMER16.C $(TIMER16_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c TIMER16.C


$(PROJ).DLL::	TIMER16.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
TIMER16.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc15\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
