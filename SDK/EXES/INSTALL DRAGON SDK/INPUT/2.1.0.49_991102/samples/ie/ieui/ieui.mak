# Microsoft Developer Studio Generated NMAKE File, Based on ieui.dsp
!IF "$(CFG)" == ""
CFG=ieui - Win32 (WCE SH4) Debug
!MESSAGE No configuration specified. Defaulting to ieui - Win32 (WCE SH4) Debug.
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

!IF "$(CFG)" != "ieui - Win32 (WCE SH4) Release" && "$(CFG)" != "ieui - Win32 (WCE SH4) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ieui.mak" CFG="ieui - Win32 (WCE SH4) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ieui - Win32 (WCE SH4) Release" (based on "Win32 (WCE SH4) Dynamic-Link Library")
!MESSAGE "ieui - Win32 (WCE SH4) Debug" (based on "Win32 (WCE SH4) Dynamic-Link Library")
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
DEF_FILE=ieui.def

!IF  "$(CFG)" == "ieui - Win32 (WCE SH4) Release"

OUTDIR=.\retail
INTDIR=.\retail

ALL : "..\..\..\release\retail\samples\ieui.dll"


CLEAN :
	-@erase "$(OUTDIR)\ieui.exp"
	-@erase "$(OUTDIR)\ieui.lib"
	-@erase "..\..\..\release\retail\samples\ieui.dll"
	-@erase "$(INTDIR)\ieui.res"
	-@erase "$(INTDIR)\ieui.obj"
	-@erase "$(INTDIR)\dllmain.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Qsh4 /MC /W3 /GX- /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "IEUI_EXPORTS" /Fp"$(INTDIR)\ieui.pch" /YX /Fo"$(INTDIR)\\" /c /I "..\..\..\inc"
RSC_PROJ=/l 0x409 /r /fo"retail/ieui.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG"  /I "..\..\..\inc"
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ieui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:no /pdb:"..\..\..\release\retail\Samples/ieui.pdb" /machine:SH4 /nodefaultlib /out:"..\..\..\release\retail\Samples/ieui.dll" /libpath:"..\..\lib\retail" /libpath:"..\..\..\lib\retail" /subsystem:$(CESubsystem) /def:ieui.def
LINK32_OBJS= \
	"$(INTDIR)\ieui.res" \
	"$(INTDIR)\ieui.obj" \
	"$(INTDIR)\dllmain.obj"

"..\..\..\release\retail\samples\ieui.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ieui - Win32 (WCE SH4) Debug"

OUTDIR=.\debug
INTDIR=.\debug

ALL : "..\..\..\release\debug\samples\ieui.dll"


CLEAN :
	-@erase "$(OUTDIR)\ieui.exp"
	-@erase "$(OUTDIR)\ieui.lib"
	-@erase "$(OUTDIR)\ieui.pdb"
	-@erase "..\..\..\release\debug\samples\ieui.dll"
	-@erase "..\..\..\release\debug\samples\ieui.ilk"
	-@erase "$(INTDIR)\ieui.res"
	-@erase "$(INTDIR)\ieui.obj"
	-@erase "$(INTDIR)\dllmain.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Qsh4 /MC /W3 /GX- /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH4" /D "_SH4_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_MBCS" /D "_USRDLL" /D "IEUI_EXPORTS" /Fp"$(INTDIR)\ieui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /c /I "..\..\..\inc"
RSC_PROJ=/l 0x409 /r /fo"debug/ieui.res" /d "SHx" /d "SH4" /d "_SH4_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" /I "..\..\..\inc"
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ieui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=coredll.lib corelibc.lib ole32.lib oleaut32.lib uuid.lib /nologo /entry:"_DllMainCRTStartup" /base:"0x10000000" /align:"4096" /dll /incremental:no /pdb:"..\..\..\release\debug\Samples/ieui.pdb" /debug /machine:SH4 /nodefaultlib /out:"..\..\..\release\debug\Samples/ieui.dll" /libpath:"..\..\lib\debug" /libpath:"..\..\..\lib\debug" /subsystem:$(CESubsystem) /def:ieui.def
LINK32_OBJS= \
	"$(INTDIR)\ieui.res"  \
	"$(INTDIR)\ieui.obj"  \
	"$(INTDIR)\dllmain.obj"

"..\..\..\release\debug\samples\ieui.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

!IF "$(CFG)" == "ieui - Win32 (WCE SH4) Release" || "$(CFG)" == "ieui - Win32 (WCE SH4) Debug"
SOURCE=.\ieui.rc

!IF  "$(CFG)" == "ieui - Win32 (WCE SH4) Release"


"$(INTDIR)\ieui.res" : ieui.rc
	$(RSC) $(RSC_PROJ) ieui.rc

"$(INTDIR)\ieui.obj" : ieui.cpp "$(INTDIR)"

"$(INTDIR)\dllmain.obj" : dllmain.cpp "$(INTDIR)"

!ELSEIF  "$(CFG)" == "ieui - Win32 (WCE SH4) Debug"


"$(INTDIR)\ieui.res" : ieui.rc
	$(RSC) $(RSC_PROJ) ieui.rc

"$(INTDIR)\ieui.obj" : ieui.cpp "$(INTDIR)"

"$(INTDIR)\dllmain.obj" : dllmain.cpp "$(INTDIR)"

!ENDIF 


!ENDIF 

