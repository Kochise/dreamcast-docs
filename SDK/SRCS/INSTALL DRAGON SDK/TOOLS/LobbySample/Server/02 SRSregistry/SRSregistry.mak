# Microsoft Developer Studio Generated NMAKE File, Based on SRSregistry.dsp
!IF "$(CFG)" == ""
CFG=SRSregistry - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの SRSregistry - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "SRSregistry - Win32 Release" && "$(CFG)" != "SRSregistry - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SRSregistry.mak" CFG="SRSregistry - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SRSregistry - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "SRSregistry - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
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

!IF  "$(CFG)" == "SRSregistry - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\module\SRSregistry.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSregistry.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SRSregistry.exp"
	-@erase "$(OUTDIR)\SRSregistry.lib"
	-@erase "..\module\SRSregistry.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSREGISTRY_EXPORTS" /Fp"$(INTDIR)\SRSregistry.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSregistry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\SRSdebug\Release\SRSdebug.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SRSregistry.pdb" /machine:I386 /def:".\SRSregistry.def" /out:"..\module/SRSregistry.dll" /implib:"$(OUTDIR)\SRSregistry.lib" 
DEF_FILE= \
	".\SRSregistry.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSregistry.obj"

"..\module\SRSregistry.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SRSregistry - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SRSregistry.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSregistry.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SRSregistry.dll"
	-@erase "$(OUTDIR)\SRSregistry.exp"
	-@erase "$(OUTDIR)\SRSregistry.ilk"
	-@erase "$(OUTDIR)\SRSregistry.lib"
	-@erase "$(OUTDIR)\SRSregistry.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSREGISTRY_EXPORTS" /Fp"$(INTDIR)\SRSregistry.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSregistry.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\SRSdebug\Release\SRSdebug.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SRSregistry.pdb" /debug /machine:I386 /def:".\SRSregistry.def" /out:"$(OUTDIR)\SRSregistry.dll" /implib:"$(OUTDIR)\SRSregistry.lib" /pdbtype:sept 
DEF_FILE= \
	".\SRSregistry.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSregistry.obj"

"$(OUTDIR)\SRSregistry.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SRSregistry.dep")
!INCLUDE "SRSregistry.dep"
!ELSE 
!MESSAGE Warning: cannot find "SRSregistry.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SRSregistry - Win32 Release" || "$(CFG)" == "SRSregistry - Win32 Debug"
SOURCE=.\SRSregistry.cpp

"$(INTDIR)\SRSregistry.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

