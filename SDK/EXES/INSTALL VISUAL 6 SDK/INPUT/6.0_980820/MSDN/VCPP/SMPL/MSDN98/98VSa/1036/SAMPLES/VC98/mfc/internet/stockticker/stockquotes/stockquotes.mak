# Microsoft Developer Studio Generated NMAKE File, Based on stockquotes.dsp
!IF "$(CFG)" == ""
CFG=stockquotes - Win32 Debug
!MESSAGE No configuration specified. Defaulting to stockquotes - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "stockquotes - Win32 Debug" && "$(CFG)" !=\
 "stockquotes - Win32 Unicode Debug" && "$(CFG)" !=\
 "stockquotes - Win32 Release MinSize" && "$(CFG)" !=\
 "stockquotes - Win32 Release MinDependency" && "$(CFG)" !=\
 "stockquotes - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "stockquotes - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "stockquotes.mak" CFG="stockquotes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stockquotes - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stockquotes - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stockquotes - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stockquotes - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stockquotes - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "stockquotes - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "stockquotes - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.ilk"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OUTDIR)\stockquotes.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fp"$(INTDIR)\stockquotes.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /debug /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\stockquotes.dll
InputPath=.\Debug\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.ilk"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OUTDIR)\stockquotes.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /debug /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib"\
 /pdbtype:sept 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\stockquotes.dll
InputPath=.\DebugU\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib" 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\stockquotes.dll
InputPath=.\ReleaseMinSize\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib" 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\stockquotes.dll
InputPath=.\ReleaseMinDependency\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib" 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\stockquotes.dll
InputPath=.\ReleaseUMinSize\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\stockquotes.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\EnumStocks.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stockquotes.obj"
	-@erase "$(INTDIR)\stockquotes.pch"
	-@erase "$(INTDIR)\stockquotes.res"
	-@erase "$(INTDIR)\StockQuotes_.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\stockquotes.dll"
	-@erase "$(OUTDIR)\stockquotes.exp"
	-@erase "$(OUTDIR)\stockquotes.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\stockquotes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\stockquotes.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\stockquotes.pdb" /machine:I386 /def:".\stockquotes.def"\
 /out:"$(OUTDIR)\stockquotes.dll" /implib:"$(OUTDIR)\stockquotes.lib" 
DEF_FILE= \
	".\stockquotes.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumStocks.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stockquotes.obj" \
	"$(INTDIR)\stockquotes.res" \
	"$(INTDIR)\StockQuotes_.obj"

"$(OUTDIR)\stockquotes.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\stockquotes.dll
InputPath=.\ReleaseUMinDependency\stockquotes.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 


!IF "$(CFG)" == "stockquotes - Win32 Debug" || "$(CFG)" ==\
 "stockquotes - Win32 Unicode Debug" || "$(CFG)" ==\
 "stockquotes - Win32 Release MinSize" || "$(CFG)" ==\
 "stockquotes - Win32 Release MinDependency" || "$(CFG)" ==\
 "stockquotes - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "stockquotes - Win32 Unicode Release MinDependency"
SOURCE=.\dlldatax.c
SOURCE=.\EnumStocks.cpp
DEP_CPP_ENUMS=\
	".\EnumStocks.h"\
	".\StdAfx.h"\
	".\stockquotes.h"\
	".\StockQuotes_.h"\
	

"$(INTDIR)\EnumStocks.obj" : $(SOURCE) $(DEP_CPP_ENUMS) "$(INTDIR)"\
 "$(INTDIR)\stockquotes.pch" ".\stockquotes.h"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "stockquotes - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)\stockquotes.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\stockquotes.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\stockquotes.cpp
DEP_CPP_STOCK=\
	".\dlldatax.h"\
	".\EnumStocks.h"\
	".\StdAfx.h"\
	".\stockquotes.h"\
	".\StockQuotes_.h"\
	".\stockquotes_i.c"\
	

"$(INTDIR)\stockquotes.obj" : $(SOURCE) $(DEP_CPP_STOCK) "$(INTDIR)"\
 "$(INTDIR)\stockquotes.pch" ".\stockquotes.h" ".\stockquotes_i.c"


SOURCE=.\stockquotes.idl

!IF  "$(CFG)" == "stockquotes - Win32 Debug"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Debug"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinSize"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Release MinDependency"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinSize"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ELSEIF  "$(CFG)" == "stockquotes - Win32 Unicode Release MinDependency"

InputPath=.\stockquotes.idl

".\stockquotes.tlb"	".\stockquotes.h"	".\stockquotes_i.c"	 : $(SOURCE)\
 "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "stockquotes.h" /iid "stockquotes_i.c" "stockquotes.idl"

!ENDIF 

SOURCE=.\stockquotes.rc
DEP_RSC_STOCKQ=\
	".\EnumStocks.rgs"\
	".\StockQuotes.rgs"\
	".\stockquotes.tlb"\
	

"$(INTDIR)\stockquotes.res" : $(SOURCE) $(DEP_RSC_STOCKQ) "$(INTDIR)"\
 ".\stockquotes.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StockQuotes_.cpp
DEP_CPP_STOCKQU=\
	".\EnumStocks.h"\
	".\StdAfx.h"\
	".\stockquotes.h"\
	".\StockQuotes_.h"\
	

"$(INTDIR)\StockQuotes_.obj" : $(SOURCE) $(DEP_CPP_STOCKQU) "$(INTDIR)"\
 "$(INTDIR)\stockquotes.pch" ".\stockquotes.h"



!ENDIF 

