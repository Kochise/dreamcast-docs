# Microsoft Developer Studio Generated NMAKE File, Based on wininetui.dsp
!IF "$(CFG)" == ""
CFG=wininetui - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to wininetui - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "wininetui - Win32 (WCE SH4) Release" && "$(CFG)" != "wininetui - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wininetui.mak" CFG="wininetui - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wininetui - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE "wininetui - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Dynamic-Link Library")
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
DEF_FILE=wininetui.def

!IF  "$(CFG)" == "wininetui - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\samples\wininetui.dll"


CLEAN :
	-@erase "$(OUTDIR)\wininetui.exp"
	-@erase "$(OUTDIR)\wininetui.lib"
	-@erase "..\..\..\release\retail\samples\wininetui.dll"
	-@erase "$(INTDIR)\wininetui.res"
	-@erase "$(INTDIR)\wininetui.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Qsh4 /MC /W3 /GX- /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "WININETUI_EXPORTS" /Fp"$(INTDIR)\wininetui.pch" /YX /Fo"$(INTDIR)\\" /c /I "..\..\..\inc"
RSC_PROJ=/l 0x409 /r /fo"retail/wininetui.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "NDEBUG"  /I "..\..\..\inc"
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wininetui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:no /pdb:"..\..\..\release\retail\Samples/wininetui.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/wininetui.dll" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) /def:wininetui.def
LINK32_OBJS= \
	"$(INTDIR)\wininetui.res" \
	"$(INTDIR)\wininetui.obj"

"..\..\..\release\retail\samples\wininetui.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "wininetui - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\samples\wininetui.dll"


CLEAN :
	-@erase "$(OUTDIR)\wininetui.exp"
	-@erase "$(OUTDIR)\wininetui.lib"
	-@erase "$(OUTDIR)\wininetui.pdb"
	-@erase "..\..\..\release\debug\samples\wininetui.dll"
	-@erase "..\..\..\release\debug\samples\wininetui.ilk"
	-@erase "$(INTDIR)\wininetui.res"
	-@erase "$(INTDIR)\wininetui.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Qsh4 /MC /W3 /GX- /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "_MBCS" /D "_USRDLL" /D "WININETUI_EXPORTS" /Fp"$(INTDIR)\wininetui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c /I "..\..\..\inc"
RSC_PROJ=/l 0x409 /r /fo"debug/wininetui.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /D "_UNICODE" /d "DEBUG" /I "..\..\..\inc"
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wininetui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:no /pdb:"..\..\..\release\debug\Samples/wininetui.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/wininetui.dll" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) /def:wininetui.def
LINK32_OBJS= \
	"$(INTDIR)\wininetui.res"  \
	"$(INTDIR)\wininetui.obj"

"..\..\..\release\debug\samples\wininetui.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

!IF "$(CFG)" == "wininetui - Win32 (WCE SH4) Release" || "$(CFG)" == "wininetui - Win32 (WCE SH4) Debug"
SOURCE=.\wininetui.rc

!IF  "$(CFG)" == "wininetui - Win32 (WCE SH4) Release"


"$(INTDIR)\wininetui.res" : wininetui.rc
	$(RSC) $(RSC_PROJ) wininetui.rc

"$(INTDIR)\wininetui.obj" : wininetui.cpp "$(INTDIR)"

!ELSEIF  "$(CFG)" == "wininetui - Win32 (WCE SH4) Debug"


"$(INTDIR)\wininetui.res" : wininetui.rc
	$(RSC) $(RSC_PROJ) wininetui.rc

"$(INTDIR)\wininetui.obj" : wininetui.cpp "$(INTDIR)"

!ENDIF 


!ENDIF 

