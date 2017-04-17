# Microsoft Developer Studio Generated NMAKE File, Based on SRSdebug.dsp
!IF "$(CFG)" == ""
CFG=SRSdebug - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの SRSdebug - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "SRSdebug - Win32 Release" && "$(CFG)" != "SRSdebug - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SRSdebug.mak" CFG="SRSdebug - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SRSdebug - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "SRSdebug - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
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

!IF  "$(CFG)" == "SRSdebug - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\module\SRSdebug.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSdebug.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SRSdebug.exp"
	-@erase "$(OUTDIR)\SRSdebug.lib"
	-@erase "..\module\SRSdebug.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSDEBUG_EXPORTS" /Fp"$(INTDIR)\SRSdebug.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSdebug.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SRSdebug.pdb" /machine:I386 /def:".\SRSdebug.def" /out:"..\module/SRSdebug.dll" /implib:"$(OUTDIR)\SRSdebug.lib" 
DEF_FILE= \
	".\SRSdebug.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSdebug.obj"

"..\module\SRSdebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SRSdebug - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SRSdebug.dll"


CLEAN :
	-@erase "$(INTDIR)\SRSdebug.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SRSdebug.dll"
	-@erase "$(OUTDIR)\SRSdebug.exp"
	-@erase "$(OUTDIR)\SRSdebug.ilk"
	-@erase "$(OUTDIR)\SRSdebug.lib"
	-@erase "$(OUTDIR)\SRSdebug.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SRSDEBUG_EXPORTS" /Fp"$(INTDIR)\SRSdebug.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSdebug.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SRSdebug.pdb" /debug /machine:I386 /def:".\SRSdebug.def" /out:"$(OUTDIR)\SRSdebug.dll" /implib:"$(OUTDIR)\SRSdebug.lib" /pdbtype:sept 
DEF_FILE= \
	".\SRSdebug.def"
LINK32_OBJS= \
	"$(INTDIR)\SRSdebug.obj"

"$(OUTDIR)\SRSdebug.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SRSdebug.dep")
!INCLUDE "SRSdebug.dep"
!ELSE 
!MESSAGE Warning: cannot find "SRSdebug.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SRSdebug - Win32 Release" || "$(CFG)" == "SRSdebug - Win32 Debug"
SOURCE=.\SRSdebug.cpp

"$(INTDIR)\SRSdebug.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

