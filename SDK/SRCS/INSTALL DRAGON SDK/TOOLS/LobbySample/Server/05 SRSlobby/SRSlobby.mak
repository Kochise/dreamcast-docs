# Microsoft Developer Studio Generated NMAKE File, Based on SRSlobby.dsp
!IF "$(CFG)" == ""
CFG=SRSlobby - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの SRSlobby - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "SRSlobby - Win32 Release" && "$(CFG)" != "SRSlobby - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "SRSlobby.mak" CFG="SRSlobby - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "SRSlobby - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "SRSlobby - Win32 Debug" ("Win32 (x86) Application" 用)
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

!IF  "$(CFG)" == "SRSlobby - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SRSlobby.exe"


CLEAN :
	-@erase "$(INTDIR)\SRSlobby.obj"
	-@erase "$(INTDIR)\SRSlobbyReq.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SRSlobby.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SRSlobby.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSlobby.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\lib\Release\SRSdebug.lib ..\lib\Release\SRSnetwork.lib ..\lib\Release\SRSmanage.lib ..\lib\Release\SRSregistry.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SRSlobby.pdb" /machine:I386 /out:"$(OUTDIR)\SRSlobby.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SRSlobby.obj" \
	"$(INTDIR)\SRSlobbyReq.obj"

"$(OUTDIR)\SRSlobby.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\SRSlobby.exe"
   copy  release\SRSlobby.exe  ..\bin\release
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "SRSlobby - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SRSlobby.exe"


CLEAN :
	-@erase "$(INTDIR)\SRSlobby.obj"
	-@erase "$(INTDIR)\SRSlobbyReq.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SRSlobby.exe"
	-@erase "$(OUTDIR)\SRSlobby.ilk"
	-@erase "$(OUTDIR)\SRSlobby.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\SRSlobby.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SRSlobby.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib ..\lib\debug\SRSdebug.lib ..\lib\debug\SRSnetwork.lib ..\lib\debug\SRSmanage.lib ..\lib\debug\SRSregistry.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SRSlobby.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SRSlobby.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SRSlobby.obj" \
	"$(INTDIR)\SRSlobbyReq.obj"

"$(OUTDIR)\SRSlobby.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\SRSlobby.exe"
   copy  debug\SRSlobby.exe  ..\bin\debug
	copy  debug\SRSlobby.pdb  ..\bin\debug
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("SRSlobby.dep")
!INCLUDE "SRSlobby.dep"
!ELSE 
!MESSAGE Warning: cannot find "SRSlobby.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SRSlobby - Win32 Release" || "$(CFG)" == "SRSlobby - Win32 Debug"
SOURCE=.\SRSlobby.cpp

"$(INTDIR)\SRSlobby.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SRSlobbyReq.cpp

"$(INTDIR)\SRSlobbyReq.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

