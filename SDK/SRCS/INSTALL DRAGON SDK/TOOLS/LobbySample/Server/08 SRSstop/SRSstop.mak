# Microsoft Developer Studio Generated NMAKE File, Based on SRSstop.dsp
!IF "$(CFG)" == ""
CFG=SRSstop - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの SRSstop - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "SRSstop - Win32 Release" && "$(CFG)" != "SRSstop - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SRSstop.mak" CFG="SRSstop - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SRSstop - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "SRSstop - Win32 Debug" ("Win32 (x86) Application" 用)
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

!IF  "$(CFG)" == "SRSstop - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\module\SRSstop.exe"


CLEAN :
	-@erase "$(INTDIR)\SRSstop.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\module\SRSstop.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSstop.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\SRSdebug\Release\SRSdebug.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SRSstop.pdb" /machine:I386 /out:"..\module/SRSstop.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SRSstop.obj"

"..\module\SRSstop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SRSstop - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SRSstop.exe"


CLEAN :
	-@erase "$(INTDIR)\SRSstop.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SRSstop.exe"
	-@erase "$(OUTDIR)\SRSstop.ilk"
	-@erase "$(OUTDIR)\SRSstop.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSstop.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\SRSdebug\Release\SRSdebug.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SRSstop.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SRSstop.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SRSstop.obj"

"$(OUTDIR)\SRSstop.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SRSstop.dep")
!INCLUDE "SRSstop.dep"
!ELSE 
!MESSAGE Warning: cannot find "SRSstop.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SRSstop - Win32 Release" || "$(CFG)" == "SRSstop - Win32 Debug"
SOURCE=.\SRSstop.cpp

"$(INTDIR)\SRSstop.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

