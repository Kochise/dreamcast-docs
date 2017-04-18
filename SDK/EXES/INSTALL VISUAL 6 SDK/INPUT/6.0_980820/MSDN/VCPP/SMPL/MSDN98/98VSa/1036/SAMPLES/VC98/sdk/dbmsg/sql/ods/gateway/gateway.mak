# Microsoft Developer Studio Generated NMAKE File, Based on Gateway.dsp
!IF "$(CFG)" == ""
CFG=Gateway - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Gateway - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Gateway - Win32 Release" && "$(CFG)" != "Gateway - Win32 Debug" && "$(CFG)" != "Gateway - Win32 (ALPHA) Debug" && "$(CFG)" != "Gateway - Win32 (ALPHA) Release" && "$(CFG)" != "Gateway - Win32 (PPC) Debug" && "$(CFG)" != "Gateway - Win32 (PPC) Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gateway.mak" CFG="Gateway - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gateway - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Gateway - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Gateway - Win32 (ALPHA) Debug" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "Gateway - Win32 (ALPHA) Release" (based on "Win32 (ALPHA) Console Application")
!MESSAGE "Gateway - Win32 (PPC) Debug" (based on "Win32 (PPC) Console Application")
!MESSAGE "Gateway - Win32 (PPC) Release" (based on "Win32 (PPC) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Gateway - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Gateway.exe"


CLEAN :
	-@erase "$(INTDIR)\GATECBS.OBJ"
	-@erase "$(INTDIR)\GATEWAY.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Gateway.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /Fp"$(INTDIR)\Gateway.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gateway.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Gateway.pdb" /machine:I386 /out:"$(OUTDIR)\Gateway.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GATECBS.OBJ" \
	"$(INTDIR)\GATEWAY.OBJ"

"$(OUTDIR)\Gateway.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Gateway - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Gateway.exe"


CLEAN :
	-@erase "$(INTDIR)\GATECBS.OBJ"
	-@erase "$(INTDIR)\GATEWAY.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Gateway.exe"
	-@erase "$(OUTDIR)\Gateway.ilk"
	-@erase "$(OUTDIR)\Gateway.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "DBNTWIN32" /Fp"$(INTDIR)\Gateway.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gateway.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Gateway.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Gateway.exe" 
LINK32_OBJS= \
	"$(INTDIR)\GATECBS.OBJ" \
	"$(INTDIR)\GATEWAY.OBJ"

"$(OUTDIR)\Gateway.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Debug"

OUTDIR=.\Gateway_
INTDIR=.\Gateway_

ALL : 


CLEAN :
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gateway.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Gateway.pdb" /debug /machine:ALPHA /out:"$(OUTDIR)\Gateway.exe" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Release"

OUTDIR=.\Gateway0
INTDIR=.\Gateway0

ALL : 


CLEAN :
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Gateway.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opends60.lib ntwdblib.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Gateway.pdb" /machine:ALPHA /out:"$(OUTDIR)\Gateway.exe" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Debug"

OUTDIR=.\Gateway3
INTDIR=.\Gateway3

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
BSC32=bscmake.exe
LINK32=link.exe

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Release"

OUTDIR=.\Gateway4
INTDIR=.\Gateway4

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
RSC=rc.exe
BSC32=bscmake.exe
LINK32=link.exe

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Gateway.dep")
!INCLUDE "Gateway.dep"
!ELSE 
!MESSAGE Warning: cannot find "Gateway.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Gateway - Win32 Release" || "$(CFG)" == "Gateway - Win32 Debug" || "$(CFG)" == "Gateway - Win32 (ALPHA) Debug" || "$(CFG)" == "Gateway - Win32 (ALPHA) Release" || "$(CFG)" == "Gateway - Win32 (PPC) Debug" || "$(CFG)" == "Gateway - Win32 (PPC) Release"
SOURCE=.\GATECBS.C

!IF  "$(CFG)" == "Gateway - Win32 Release"


"$(INTDIR)\GATECBS.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Gateway - Win32 Debug"


"$(INTDIR)\GATECBS.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Release"

!ENDIF 

SOURCE=.\GATEWAY.C

!IF  "$(CFG)" == "Gateway - Win32 Release"


"$(INTDIR)\GATEWAY.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Gateway - Win32 Debug"


"$(INTDIR)\GATEWAY.OBJ" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Debug"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (ALPHA) Release"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Debug"

!ELSEIF  "$(CFG)" == "Gateway - Win32 (PPC) Release"

!ENDIF 


!ENDIF 

