# Microsoft Developer Studio Generated NMAKE File, Based on Dlltrace.dsp
!IF "$(CFG)" == ""
CFG=DllTrace - Win32 Release
!MESSAGE No configuration specified. Defaulting to DllTrace - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DllTrace - Win32 Release" && "$(CFG)" != "DllTrace - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dlltrace.mak" CFG="DllTrace - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DllTrace - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DllTrace - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "DllTrace - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Dlltrace.exe"

!ELSE 

ALL : "Trace - Win32 Release" "$(OUTDIR)\Dlltrace.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Trace - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlltrace.obj"
	-@erase "$(INTDIR)\dlltrace.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Dlltrace.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dlltrace.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dlltrace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Release/Trace.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Dlltrace.pdb" /machine:I386 /out:"$(OUTDIR)\Dlltrace.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlltrace.obj" \
	"$(INTDIR)\dlltrace.res" \
	"$(OUTDIR)\Trace.lib"

"$(OUTDIR)\Dlltrace.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DllTrace - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Dlltrace.exe"

!ELSE 

ALL : "Trace - Win32 Debug" "$(OUTDIR)\Dlltrace.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Trace - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dlltrace.obj"
	-@erase "$(INTDIR)\dlltrace.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Dlltrace.exe"
	-@erase "$(OUTDIR)\Dlltrace.ilk"
	-@erase "$(OUTDIR)\Dlltrace.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dlltrace.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Dlltrace.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Debug/Trace.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Dlltrace.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Dlltrace.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlltrace.obj" \
	"$(INTDIR)\dlltrace.res" \
	"$(OUTDIR)\Trace.lib"

"$(OUTDIR)\Dlltrace.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Dlltrace.dep")
!INCLUDE "Dlltrace.dep"
!ELSE 
!MESSAGE Warning: cannot find "Dlltrace.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DllTrace - Win32 Release" || "$(CFG)" == "DllTrace - Win32 Debug"
SOURCE=.\dlltrace.cpp

"$(INTDIR)\dlltrace.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\dlltrace.rc

"$(INTDIR)\dlltrace.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "DllTrace - Win32 Release"

"Trace - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Trace.mak CFG="Trace - Win32 Release" 
   cd "."

"Trace - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Trace.mak CFG="Trace - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "DllTrace - Win32 Debug"

"Trace - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Trace.mak CFG="Trace - Win32 Debug" 
   cd "."

"Trace - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\Trace.mak CFG="Trace - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

