# Microsoft Developer Studio Generated NMAKE File, Based on lobbytest.dsp
!IF "$(CFG)" == ""
CFG=lobbytest - Win32 Debug
!MESSAGE 構成が指定されていません。ﾃﾞﾌｫﾙﾄの lobbytest - Win32 Debug を設定します。
!ENDIF 

!IF "$(CFG)" != "lobbytest - Win32 Release" && "$(CFG)" != "lobbytest - Win32 Debug"
!MESSAGE 指定された ﾋﾞﾙﾄﾞ ﾓｰﾄﾞ "$(CFG)" は正しくありません。
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "lobbytest.mak" CFG="lobbytest - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "lobbytest - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "lobbytest - Win32 Debug" ("Win32 (x86) Application" 用)
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

!IF  "$(CFG)" == "lobbytest - Win32 Release"

OUTDIR=.\..\module
INTDIR=.\Release

ALL : "..\bin\release\lobbytest.exe"


CLEAN :
	-@erase "$(INTDIR)\SRLtestApl.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\bin\release\lobbytest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\lobbytest.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lobbytest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\lib\release\SRLdebug.lib ..\lib\release\SRLregistry.lib ..\lib\release\SRLmanage.lib ..\lib\release\SRLevent.lib ..\lib\release\SRLsend.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\lobbytest.pdb" /machine:I386 /out:"..\bin\release\lobbytest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SRLtestApl.obj"

"..\bin\release\lobbytest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lobbytest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\bin\Debug\lobbytest.exe"


CLEAN :
	-@erase "$(INTDIR)\SRLtestApl.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\lobbytest.pdb"
	-@erase "..\bin\Debug\lobbytest.exe"
	-@erase "..\bin\Debug\lobbytest.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\lobbytest.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lobbytest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\lib\debug\SRLdebug.lib ..\lib\\debug\SRLregistry.lib ..\lib\debug\SRLmanage.lib ..\lib\debug\SRLevent.lib ..\lib\debug\SRLsend.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\lobbytest.pdb" /debug /machine:I386 /out:"..\bin\Debug\lobbytest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SRLtestApl.obj"

"..\bin\Debug\lobbytest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("lobbytest.dep")
!INCLUDE "lobbytest.dep"
!ELSE 
!MESSAGE Warning: cannot find "lobbytest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "lobbytest - Win32 Release" || "$(CFG)" == "lobbytest - Win32 Debug"
SOURCE=.\SRLtestApl.cpp

"$(INTDIR)\SRLtestApl.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

