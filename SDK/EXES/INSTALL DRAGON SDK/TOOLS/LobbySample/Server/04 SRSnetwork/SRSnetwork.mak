# Microsoft Developer Studio Generated NMAKE File, Based on SRSnetwork.dsp
!IF "$(CFG)" == ""
CFG=SRSnetwork - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの SRSnetwork - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "SRSnetwork - Win32 Release" && "$(CFG)" != "SRSnetwork - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SRSnetwork.mak" CFG="SRSnetwork - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SRSnetwork - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "SRSnetwork - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 
!ERROR 無効な構成が指定されています。
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SRSnetwork - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\module\SRSnetwork.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSnetwork.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SRSnetwork.exp"
	-@erase "$(OUTDIR)\SRSnetwork.lib"
	-@erase "..\module\SRSnetwork.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSNETWORK_EXPORTS" /Fp"$(INTDIR)\SRSnetwork.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSnetwork.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\SRSdebug\release\SRSdebug.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SRSnetwork.pdb" /machine:I386 /def:".\SRSnetwork.def" /out:"..\module/SRSnetwork.dll" /implib:"$(OUTDIR)\SRSnetwork.lib" 
DEF_FILE= \
	".\SRSnetwork.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSnetwork.obj"

"..\module\SRSnetwork.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SRSnetwork - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SRSnetwork.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSnetwork.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SRSnetwork.dll"
	-@erase "$(OUTDIR)\SRSnetwork.exp"
	-@erase "$(OUTDIR)\SRSnetwork.ilk"
	-@erase "$(OUTDIR)\SRSnetwork.lib"
	-@erase "$(OUTDIR)\SRSnetwork.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSNETWORK_EXPORTS" /Fp"$(INTDIR)\SRSnetwork.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSnetwork.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\SRSdebug\release\SRSdebug.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SRSnetwork.pdb" /debug /machine:I386 /def:".\SRSnetwork.def" /out:"$(OUTDIR)\SRSnetwork.dll" /implib:"$(OUTDIR)\SRSnetwork.lib" /pdbtype:sept 
DEF_FILE= \
	".\SRSnetwork.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSnetwork.obj"

"$(OUTDIR)\SRSnetwork.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SRSnetwork.dep")
!INCLUDE "SRSnetwork.dep"
!ELSE 
!MESSAGE Warning: cannot find "SRSnetwork.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SRSnetwork - Win32 Release" || "$(CFG)" == "SRSnetwork - Win32 Debug"
SOURCE=.\SRSnetwork.cpp

"$(INTDIR)\SRSnetwork.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

