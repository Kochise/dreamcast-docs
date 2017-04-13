# Microsoft Developer Studio Generated NMAKE File, Based on TableCopy.dsp
!IF "$(CFG)" == ""
CFG=TableCopy - Win32 x86 Release
!MESSAGE No configuration specified. Defaulting to TableCopy - Win32 x86\
 Release.
!ENDIF 

!IF "$(CFG)" != "TableCopy - Win32 x86 Release" && "$(CFG)" !=\
 "TableCopy - Win32 x86 Debug" && "$(CFG)" !=\
 "TableCopy - Win32 (ALPHA) axp Debug" && "$(CFG)" !=\
 "TableCopy - Win32 (ALPHA) axp Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TableCopy.mak" CFG="TableCopy - Win32 x86 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TableCopy - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "TableCopy - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE "TableCopy - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "TableCopy - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

OUTDIR=.\x86_Rele
INTDIR=.\x86_Rele
# Begin Custom Macros
OutDir=.\.\x86_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TableCopy.exe"

!ELSE 

ALL : "$(OUTDIR)\TableCopy.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\DataSource.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\PROGRESS.OBJ"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(INTDIR)\STEP1.OBJ"
	-@erase "$(INTDIR)\STEP2.OBJ"
	-@erase "$(INTDIR)\STEP3.OBJ"
	-@erase "$(INTDIR)\STEP4.OBJ"
	-@erase "$(INTDIR)\Table.obj"
	-@erase "$(INTDIR)\TableCopy.obj"
	-@erase "$(INTDIR)\TableCopy.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(OUTDIR)\TableCopy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /O1 /I "..\..\INCLUDE" /D "NDEBUG" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\x86_Rele/
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TableCopy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TableCopy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib\
 user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TableCopy.pdb" /machine:I386 /nodefaultlib\
 /out:"$(OUTDIR)\TableCopy.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\DataSource.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\PROGRESS.OBJ" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\Spy.obj" \
	"$(INTDIR)\STEP1.OBJ" \
	"$(INTDIR)\STEP2.OBJ" \
	"$(INTDIR)\STEP3.OBJ" \
	"$(INTDIR)\STEP4.OBJ" \
	"$(INTDIR)\Table.obj" \
	"$(INTDIR)\TableCopy.obj" \
	"$(INTDIR)\TableCopy.res" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\Wizard.obj"

"$(OUTDIR)\TableCopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

OUTDIR=.\x86_Debu
INTDIR=.\x86_Debu
# Begin Custom Macros
OutDir=.\.\x86_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TableCopy.exe"

!ELSE 

ALL : "$(OUTDIR)\TableCopy.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\DataSource.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\PROGRESS.OBJ"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(INTDIR)\STEP1.OBJ"
	-@erase "$(INTDIR)\STEP2.OBJ"
	-@erase "$(INTDIR)\STEP3.OBJ"
	-@erase "$(INTDIR)\STEP4.OBJ"
	-@erase "$(INTDIR)\Table.obj"
	-@erase "$(INTDIR)\TableCopy.obj"
	-@erase "$(INTDIR)\TableCopy.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(OUTDIR)\TableCopy.exe"
	-@erase "$(OUTDIR)\TableCopy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /Gi /Zi /Od /I "..\..\INCLUDE" /D "_DEBUG" /D\
 "FINDLEAKS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\x86_Debu/
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TableCopy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TableCopy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib\
 user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TableCopy.pdb" /debug /machine:I386 /nodefaultlib\
 /out:"$(OUTDIR)\TableCopy.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\DataSource.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\PROGRESS.OBJ" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\Spy.obj" \
	"$(INTDIR)\STEP1.OBJ" \
	"$(INTDIR)\STEP2.OBJ" \
	"$(INTDIR)\STEP3.OBJ" \
	"$(INTDIR)\STEP4.OBJ" \
	"$(INTDIR)\Table.obj" \
	"$(INTDIR)\TableCopy.obj" \
	"$(INTDIR)\TableCopy.res" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\Wizard.obj"

"$(OUTDIR)\TableCopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

OUTDIR=.\axp_Debu
INTDIR=.\axp_Debu
# Begin Custom Macros
OutDir=.\.\axp_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TableCopy.exe"

!ELSE 

ALL : "$(OUTDIR)\TableCopy.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\DataSource.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\PROGRESS.OBJ"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(INTDIR)\STEP1.OBJ"
	-@erase "$(INTDIR)\STEP2.OBJ"
	-@erase "$(INTDIR)\STEP3.OBJ"
	-@erase "$(INTDIR)\STEP4.OBJ"
	-@erase "$(INTDIR)\Table.obj"
	-@erase "$(INTDIR)\TableCopy.obj"
	-@erase "$(INTDIR)\TableCopy.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(OUTDIR)\TableCopy.exe"
	-@erase "$(OUTDIR)\TableCopy.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /Zi /Od /I "..\..\INCLUDE" /D "_DEBUG" /D "FINDLEAKS"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\axp_Debu/
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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TableCopy.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TableCopy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib\
 user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\TableCopy.pdb" /debug /machine:ALPHA /nodefaultlib\
 /out:"$(OUTDIR)\TableCopy.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\DataSource.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\PROGRESS.OBJ" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\Spy.obj" \
	"$(INTDIR)\STEP1.OBJ" \
	"$(INTDIR)\STEP2.OBJ" \
	"$(INTDIR)\STEP3.OBJ" \
	"$(INTDIR)\STEP4.OBJ" \
	"$(INTDIR)\Table.obj" \
	"$(INTDIR)\TableCopy.obj" \
	"$(INTDIR)\TableCopy.res" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\Wizard.obj"

"$(OUTDIR)\TableCopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

OUTDIR=.\axp_Rele
INTDIR=.\axp_Rele
# Begin Custom Macros
OutDir=.\.\axp_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TableCopy.exe"

!ELSE 

ALL : "$(OUTDIR)\TableCopy.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\COMMON.OBJ"
	-@erase "$(INTDIR)\DataSource.obj"
	-@erase "$(INTDIR)\Error.obj"
	-@erase "$(INTDIR)\PROGRESS.OBJ"
	-@erase "$(INTDIR)\Property.obj"
	-@erase "$(INTDIR)\Spy.obj"
	-@erase "$(INTDIR)\STEP1.OBJ"
	-@erase "$(INTDIR)\STEP2.OBJ"
	-@erase "$(INTDIR)\STEP3.OBJ"
	-@erase "$(INTDIR)\STEP4.OBJ"
	-@erase "$(INTDIR)\Table.obj"
	-@erase "$(INTDIR)\TableCopy.obj"
	-@erase "$(INTDIR)\TableCopy.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\Wizard.obj"
	-@erase "$(OUTDIR)\TableCopy.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /O1 /I "..\..\INCLUDE" /D "NDEBUG" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\axp_Rele/
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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TableCopy.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TableCopy.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib msvcrt.lib kernel32.lib ole32.lib oleaut32.lib\
 user32.lib uuid.lib comctl32.lib /nologo /subsystem:windows\
 /pdb:"$(OUTDIR)\TableCopy.pdb" /machine:ALPHA /nodefaultlib\
 /out:"$(OUTDIR)\TableCopy.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\COMMON.OBJ" \
	"$(INTDIR)\DataSource.obj" \
	"$(INTDIR)\Error.obj" \
	"$(INTDIR)\PROGRESS.OBJ" \
	"$(INTDIR)\Property.obj" \
	"$(INTDIR)\Spy.obj" \
	"$(INTDIR)\STEP1.OBJ" \
	"$(INTDIR)\STEP2.OBJ" \
	"$(INTDIR)\STEP3.OBJ" \
	"$(INTDIR)\STEP4.OBJ" \
	"$(INTDIR)\Table.obj" \
	"$(INTDIR)\TableCopy.obj" \
	"$(INTDIR)\TableCopy.res" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\Wizard.obj"

"$(OUTDIR)\TableCopy.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "TableCopy - Win32 x86 Release" || "$(CFG)" ==\
 "TableCopy - Win32 x86 Debug" || "$(CFG)" ==\
 "TableCopy - Win32 (ALPHA) axp Debug" || "$(CFG)" ==\
 "TableCopy - Win32 (ALPHA) axp Release"
SOURCE=.\COMMON.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_COMMO=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_COMMO=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_COMMO=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_COMMO=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\COMMON.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"


!ENDIF 

SOURCE=.\DataSource.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_DATAS=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DataSource.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_DATAS=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DataSource.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_DATAS=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DataSource.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_DATAS=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\DataSource.obj" : $(SOURCE) $(DEP_CPP_DATAS) "$(INTDIR)"


!ENDIF 

SOURCE=.\Error.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_ERROR=\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_ERROR=\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_ERROR=\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_ERROR=\
	".\COMMON.H"\
	".\Error.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Error.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ENDIF 

SOURCE=.\PROGRESS.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_PROGR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\PROGRESS.OBJ" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_PROGR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\PROGRESS.OBJ" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_PROGR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\PROGRESS.OBJ" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_PROGR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\PROGRESS.OBJ" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"


!ENDIF 

SOURCE=.\Property.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_PROPE=\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_PROPE=\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_PROPE=\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_PROPE=\
	".\COMMON.H"\
	".\Error.h"\
	".\Property.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Property.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Spy.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_SPY_C=\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_SPY_C=\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_SPY_C=\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_SPY_C=\
	".\COMMON.H"\
	".\Error.h"\
	".\List.h"\
	".\Spy.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Spy.obj" : $(SOURCE) $(DEP_CPP_SPY_C) "$(INTDIR)"


!ENDIF 

SOURCE=.\STEP1.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_STEP1=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP1.OBJ" : $(SOURCE) $(DEP_CPP_STEP1) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_STEP1=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP1.OBJ" : $(SOURCE) $(DEP_CPP_STEP1) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP1=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP1.OBJ" : $(SOURCE) $(DEP_CPP_STEP1) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP1=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP1.OBJ" : $(SOURCE) $(DEP_CPP_STEP1) "$(INTDIR)"


!ENDIF 

SOURCE=.\STEP2.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_STEP2=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP2.OBJ" : $(SOURCE) $(DEP_CPP_STEP2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_STEP2=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP2.OBJ" : $(SOURCE) $(DEP_CPP_STEP2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP2=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP2.OBJ" : $(SOURCE) $(DEP_CPP_STEP2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP2=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP2.OBJ" : $(SOURCE) $(DEP_CPP_STEP2) "$(INTDIR)"


!ENDIF 

SOURCE=.\STEP3.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_STEP3=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP3.OBJ" : $(SOURCE) $(DEP_CPP_STEP3) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_STEP3=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP3.OBJ" : $(SOURCE) $(DEP_CPP_STEP3) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP3=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP3.OBJ" : $(SOURCE) $(DEP_CPP_STEP3) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP3=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP3.OBJ" : $(SOURCE) $(DEP_CPP_STEP3) "$(INTDIR)"


!ENDIF 

SOURCE=.\STEP4.CPP

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_STEP4=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP4.OBJ" : $(SOURCE) $(DEP_CPP_STEP4) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_STEP4=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP4.OBJ" : $(SOURCE) $(DEP_CPP_STEP4) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_STEP4=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP4.OBJ" : $(SOURCE) $(DEP_CPP_STEP4) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_STEP4=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\STEP4.OBJ" : $(SOURCE) $(DEP_CPP_STEP4) "$(INTDIR)"


!ENDIF 

SOURCE=.\Table.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_TABLE=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_TABLE=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_TABLE=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_TABLE=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Table.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TableCopy.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_TABLEC=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\TableCopy.obj" : $(SOURCE) $(DEP_CPP_TABLEC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_TABLEC=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\TableCopy.obj" : $(SOURCE) $(DEP_CPP_TABLEC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_TABLEC=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\TableCopy.obj" : $(SOURCE) $(DEP_CPP_TABLEC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_TABLEC=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\TableCopy.obj" : $(SOURCE) $(DEP_CPP_TABLEC) "$(INTDIR)"


!ENDIF 

SOURCE=.\TableCopy.rc
DEP_RSC_TABLECO=\
	".\Catalog.ico"\
	".\Column.ico"\
	".\columnlong.ico"\
	".\columnread.ico"\
	".\Index.ico"\
	".\PrimaryKey.ico"\
	".\Schema.ico"\
	".\Synonym.ico"\
	".\SysTable.ico"\
	".\Table.ico"\
	".\TABLE_CO.ICO"\
	".\TableCopy.rc2"\
	".\Type.ico"\
	".\version.h"\
	".\View.ico"\
	

"$(INTDIR)\TableCopy.res" : $(SOURCE) $(DEP_RSC_TABLECO) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\WinMain.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_WINMA=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\WinMain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_WINMA=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\WinMain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_WINMA=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\WinMain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_WINMA=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\List.h"\
	".\Property.h"\
	".\Spy.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\WinMain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


!ENDIF 

SOURCE=.\Wizard.cpp

!IF  "$(CFG)" == "TableCopy - Win32 x86 Release"

DEP_CPP_WIZAR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Wizard.obj" : $(SOURCE) $(DEP_CPP_WIZAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 x86 Debug"

DEP_CPP_WIZAR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Wizard.obj" : $(SOURCE) $(DEP_CPP_WIZAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Debug"

DEP_CPP_WIZAR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Wizard.obj" : $(SOURCE) $(DEP_CPP_WIZAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TableCopy - Win32 (ALPHA) axp Release"

DEP_CPP_WIZAR=\
	".\COMMON.H"\
	".\DataSource.h"\
	".\Error.h"\
	".\PROGRESS.H"\
	".\Property.h"\
	".\Table.h"\
	".\TableCopy.h"\
	".\WinMain.h"\
	".\Wizard.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\Wizard.obj" : $(SOURCE) $(DEP_CPP_WIZAR) "$(INTDIR)"


!ENDIF 


!ENDIF 

