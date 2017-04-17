# Microsoft Developer Studio Generated NMAKE File, Based on vibectrl.dsp
!IF "$(CFG)" == ""
CFG=vibectrl - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to vibectrl - Win32 (WCE SH4) Debug.
!ENDIF 

!IF "$(CESubsystem)" == ""
CESubsystem=windowsce,2.0
!MESSAGE Variable CESubsystem not specified. Defaulting to windowsce,2.0
!ENDIF 

!IF "$(CEVersion)" == ""
CEVersion=200
!MESSAGE Variable CEVersion not specified. Defaulting to 200
!ENDIF 

!IF "$(CEConfigName)" == ""
CEConfigName=H/PC Ver. 2.00
!MESSAGE Variable CEConfigName not specified.  Defaulting to H/PC Ver. 2.00
!ENDIF 

!IF $(CEVersion) < 201
CECrt=L
CECrtDebug=Ld
CECrtMT=T
CECrtMTDebug=Td
CENoDefaultLib=corelibc.lib
CEx86Corelibc= 
!ELSE 
CECrt=C
CECrtDebug=C
CECrtMT=C
CECrtMTDebug=C
CENoDefaultLib=libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib
CEx86Corelibc=corelibc.lib
!ENDIF 

!IF "$(CFG)" != "vibectrl - Win32 (WCE SH4) Release" && "$(CFG)" != "vibectrl - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vibectrl.mak" CFG="vibectrl - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vibectrl - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE "vibectrl - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=shcl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vibectrl - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "$(INTDIR)\vibectrl.tlb" "..\..\..\release\retail\samples\vibectrl.dll"

CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vibectrl.h"
	-@erase "$(INTDIR)\vibectrl.obj"
	-@erase "$(INTDIR)\vibectrl.res"
	-@erase "$(INTDIR)\vibectrl.tlb"
	-@erase "$(OUTDIR)\vibectrl.exp"
	-@erase "..\..\..\release\retail\samples\vibectrl.dll"
	-@erase "..\..\..\release\retail\samples\vibectrl.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MC /W3 /Zi /Ox /I "..\atl" /I $(WCEDREAMCASTROOT)\inc /I "retail" /D "GAL_VERSION" /D "_ATL_NO_SECURITY" /D "ATL_USE_URLMON" /D "NO_DIALOGS" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\vibectrl.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /Qgvp /c 
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\vibectrl.res" /I $(WCEDREAMCASTROOT)\inc /i "retail" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vibectrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib dinput.lib dxguid.lib mapledev.lib /libpath:"..\..\..\lib\retail" /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:no /pdb:"..\..\..\release\retail\samples\vibectrl.pdb" /map:"..\..\..\release\retail\samples\vibectrl.map" /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /def:".\vibectrl.def" /out:"..\..\..\release\retail\samples\vibectrl.dll" /subsystem:$(CESubsystem) /STACK:65536,4096 
DEF_FILE= \
	".\vibectrl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\vibectrl.obj" \
	"$(INTDIR)\vibectrl.res"

"..\..\..\release\retail\samples\vibectrl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vibectrl - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "$(INTDIR)\vibectrl.tlb" "..\..\..\release\debug\samples\vibectrl.dll" 


CLEAN :
	-@erase "$(INTDIR)\atl.obj"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\pack.obj"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vibectrl.h"
	-@erase "$(INTDIR)\vibectrl.obj"
	-@erase "$(INTDIR)\vibectrl.res"
	-@erase "$(INTDIR)\vibectrl.tlb"
	-@erase "$(OUTDIR)\vibectrl.exp"
	-@erase "..\..\..\release\debug\samples\vibectrl.dll"
	-@erase "..\..\..\release\debug\samples\vibectrl.ilk"
	-@erase "..\..\..\release\debug\samples\vibectrl.map"
	-@erase "..\..\..\release\debug\samples\vibectrl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MC /W3 /Zi /Od /I "..\atl" /I $(WCEDREAMCASTROOT)\inc /I "debug" /D "GAL_VERSION" /D "_ATL_NO_SECURITY" /D "ATL_USE_URLMON" /D "NO_DIALOGS" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\vibectrl.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /Qsh4r7 /Qs /c 
RSC_PROJ=/l 0x409 /r /fo"$(INTDIR)\vibectrl.res" /I $(WCEDREAMCASTROOT)\inc /i "debug" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vibectrl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib dinput.lib dxguid.lib mapledev.lib /libpath:"..\..\..\lib\retail" /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:yes /pdb:"..\..\..\release\debug\samples\vibectrl.pdb" /map:"..\..\..\release\debug\samples\vibectrl.map" /debug /machine:SH4 /nodefaultlib:"$(CENoDefaultLib)" /def:".\vibectrl.def" /out:"..\..\..\release\debug\samples\vibectrl.dll" /subsystem:$(CESubsystem) /STACK:65536,4096 
DEF_FILE= \
	".\vibectrl.def"
LINK32_OBJS= \
	"$(INTDIR)\atl.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\pack.obj" \
	"$(INTDIR)\vibectrl.obj" \
	"$(INTDIR)\vibectrl.res"

"..\..\..\release\debug\samples\vibectrl.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

!IF "$(CFG)" == "vibectrl - Win32 (WCE SH4) Release" || "$(CFG)" == "vibectrl - Win32 (WCE SH4) Debug"
SOURCE=.\atl.cpp

"$(INTDIR)\atl.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\control.cpp

"$(INTDIR)\control.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vibectrl.h"


SOURCE=.\pack.cpp

"$(INTDIR)\pack.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vibectrl.cpp

"$(INTDIR)\vibectrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vibectrl.h"


SOURCE=.\vibectrl.idl

!IF  "$(CFG)" == "vibectrl - Win32 (WCE SH4) Release"

MTL_SWITCHES=/nologo /I "..\atl" /I $(WCEDREAMCASTROOT)\inc /D "NDEBUG" /tlb "$(OUTDIR)\vibectrl.tlb" /h "$(INTDIR)\vibectrl.h" /mktyplib203 /o "NUL" /win32 

"$(INTDIR)\vibectrl.tlb"	"$(INTDIR)\vibectrl.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vibectrl - Win32 (WCE SH4) Debug"

MTL_SWITCHES=/nologo /I "..\atl" /I $(WCEDREAMCASTROOT)\inc /D "_DEBUG" /tlb "$(OUTDIR)\vibectrl.tlb" /h "debug\vibectrl.h" /mktyplib203 /o "NUL" /win32 

"$(INTDIR)\vibectrl.tlb"	"$(INTDIR)\vibectrl.h" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vibectrl.rc

"$(INTDIR)\vibectrl.res" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vibectrl.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

