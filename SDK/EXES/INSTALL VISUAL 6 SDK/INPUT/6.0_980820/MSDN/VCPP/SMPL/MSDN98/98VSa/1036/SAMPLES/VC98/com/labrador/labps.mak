# Microsoft Developer Studio Generated NMAKE File, Based on labps.dsp
!IF "$(CFG)" == ""
CFG=labps - Win32 Debug
!MESSAGE No configuration specified. Defaulting to labps - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "labps - Win32 Release" && "$(CFG)" != "labps - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "labps.mak" CFG="labps - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "labps - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "labps - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "labps - Win32 Release"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\labps.dll" ".\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\Lab_i.obj"
	-@erase "$(INTDIR)\Lab_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\labps.dll"
	-@erase "$(OUTDIR)\labps.exp"
	-@erase "$(OUTDIR)\labps.lib"
	-@erase ".\regsvr32.trg"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /Ox /D "NDEBUG" /D "REGISTER_PROXY_DLL" /D "WIN32" /D "_WINDOWS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\labps.pch" /YX /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\labps.pdb" /machine:I386 /def:".\labps.def" /out:"$(OUTDIR)\labps.dll" /implib:"$(OUTDIR)\labps.lib" 
DEF_FILE= \
	".\labps.def"
LINK32_OBJS= \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\Lab_i.obj" \
	"$(INTDIR)\Lab_p.obj"

"$(OUTDIR)\labps.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.
TargetPath=.\labps.dll
InputPath=.\labps.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "labps - Win32 Debug"

OUTDIR=.
INTDIR=.
# Begin Custom Macros
OutDir=.
# End Custom Macros

ALL : "$(OUTDIR)\labps.dll" ".\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\dlldata.obj"
	-@erase "$(INTDIR)\Lab_i.obj"
	-@erase "$(INTDIR)\Lab_p.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\labps.dll"
	-@erase "$(OUTDIR)\labps.exp"
	-@erase "$(OUTDIR)\labps.ilk"
	-@erase "$(OUTDIR)\labps.lib"
	-@erase "$(OUTDIR)\labps.pdb"
	-@erase ".\regsvr32.trg"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "REGISTER_PROXY_DLL" /D "_WIN32_DCOM" /Fp"$(INTDIR)\labps.pch" /YX /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\labps.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcndr.lib rpcns4.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\labps.pdb" /debug /machine:I386 /def:".\labps.def" /out:"$(OUTDIR)\labps.dll" /implib:"$(OUTDIR)\labps.lib" /pdbtype:sept 
DEF_FILE= \
	".\labps.def"
LINK32_OBJS= \
	"$(INTDIR)\dlldata.obj" \
	"$(INTDIR)\Lab_i.obj" \
	"$(INTDIR)\Lab_p.obj"

"$(OUTDIR)\labps.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.
TargetPath=.\labps.dll
InputPath=.\labps.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	echo on 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("labps.dep")
!INCLUDE "labps.dep"
!ELSE 
!MESSAGE Warning: cannot find "labps.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "labps - Win32 Release" || "$(CFG)" == "labps - Win32 Debug"
SOURCE=.\dlldata.c

"$(INTDIR)\dlldata.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Lab_i.c

"$(INTDIR)\Lab_i.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Lab_p.c

"$(INTDIR)\Lab_p.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

