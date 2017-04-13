# Microsoft Developer Studio Generated NMAKE File, Based on sampclnt.dsp
!IF "$(CFG)" == ""
CFG=sampclnt - Win32 x86 Debug
!MESSAGE No configuration specified. Defaulting to sampclnt - Win32 x86 Debug.
!ENDIF 

!IF "$(CFG)" != "sampclnt - Win32 x86 Debug" && "$(CFG)" !=\
 "sampclnt - Win32 x86 Release" && "$(CFG)" !=\
 "sampclnt - Win32 (ALPHA) axp Debug" && "$(CFG)" !=\
 "sampclnt - Win32 (ALPHA) axp Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sampclnt.mak" CFG="sampclnt - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sampclnt - Win32 x86 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "sampclnt - Win32 x86 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "sampclnt - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE "sampclnt - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

OUTDIR=.\x86_debu
INTDIR=.\x86_debu
# Begin Custom Macros
OutDir=.\.\x86_debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampclnt.exe"

!ELSE 

ALL : "$(OUTDIR)\sampclnt.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dump.obj"
	-@erase "$(INTDIR)\sampclnt.obj"
	-@erase "$(INTDIR)\sampclnt.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\sampclnt.exe"
	-@erase "$(OUTDIR)\sampclnt.ilk"
	-@erase "$(OUTDIR)\sampclnt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG"\
 /D "_CONSOLE" /Fp"$(INTDIR)\sampclnt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\x86_debu/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampclnt.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampclnt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\sampclnt.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\sampclnt.exe"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\dump.obj" \
	"$(INTDIR)\sampclnt.obj" \
	"$(INTDIR)\sampclnt.res"

"$(OUTDIR)\sampclnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

OUTDIR=.\x86_Rele
INTDIR=.\x86_Rele
# Begin Custom Macros
OutDir=.\.\x86_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampclnt.exe"

!ELSE 

ALL : "$(OUTDIR)\sampclnt.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dump.obj"
	-@erase "$(INTDIR)\sampclnt.obj"
	-@erase "$(INTDIR)\sampclnt.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\sampclnt.exe"
	-@erase "$(OUTDIR)\sampclnt.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gi /O2 /I "..\..\include" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)\sampclnt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampclnt.res" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampclnt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\sampclnt.pdb" /machine:I386\
 /out:"$(OUTDIR)\sampclnt.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\dump.obj" \
	"$(INTDIR)\sampclnt.obj" \
	"$(INTDIR)\sampclnt.res"

"$(OUTDIR)\sampclnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

OUTDIR=.\axp_Debu
INTDIR=.\axp_Debu
# Begin Custom Macros
OutDir=.\.\axp_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampclnt.exe"

!ELSE 

ALL : "$(OUTDIR)\sampclnt.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dump.obj"
	-@erase "$(INTDIR)\sampclnt.obj"
	-@erase "$(INTDIR)\sampclnt.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\sampclnt.exe"
	-@erase "$(OUTDIR)\sampclnt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)\sampclnt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampclnt.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampclnt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:console /pdb:"$(OUTDIR)\sampclnt.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)\sampclnt.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\dump.obj" \
	"$(INTDIR)\sampclnt.obj" \
	"$(INTDIR)\sampclnt.res"

"$(OUTDIR)\sampclnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

OUTDIR=.\axp_Rele
INTDIR=.\axp_Rele
# Begin Custom Macros
OutDir=.\.\axp_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\sampclnt.exe"

!ELSE 

ALL : "$(OUTDIR)\sampclnt.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dump.obj"
	-@erase "$(INTDIR)\sampclnt.obj"
	-@erase "$(INTDIR)\sampclnt.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\sampclnt.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "_CONSOLE"\
 /Fp"$(INTDIR)\sampclnt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\sampclnt.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sampclnt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=odbc32.lib odbccp32.lib oledb.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib /nologo /subsystem:console /pdb:"$(OUTDIR)\sampclnt.pdb"\
 /machine:ALPHA /out:"$(OUTDIR)\sampclnt.exe"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\dump.obj" \
	"$(INTDIR)\sampclnt.obj" \
	"$(INTDIR)\sampclnt.res"

"$(OUTDIR)\sampclnt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "sampclnt - Win32 x86 Debug" || "$(CFG)" ==\
 "sampclnt - Win32 x86 Release" || "$(CFG)" ==\
 "sampclnt - Win32 (ALPHA) axp Debug" || "$(CFG)" ==\
 "sampclnt - Win32 (ALPHA) axp Release"
SOURCE=.\dump.cpp

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

DEP_CPP_DUMP_=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dump.obj" : $(SOURCE) $(DEP_CPP_DUMP_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

DEP_CPP_DUMP_=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dump.obj" : $(SOURCE) $(DEP_CPP_DUMP_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

DEP_CPP_DUMP_=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dump.obj" : $(SOURCE) $(DEP_CPP_DUMP_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

DEP_CPP_DUMP_=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\dump.obj" : $(SOURCE) $(DEP_CPP_DUMP_) "$(INTDIR)"


!ENDIF 

SOURCE=.\sampclnt.cpp

!IF  "$(CFG)" == "sampclnt - Win32 x86 Debug"

DEP_CPP_SAMPC=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\sampclnt.obj" : $(SOURCE) $(DEP_CPP_SAMPC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 x86 Release"

DEP_CPP_SAMPC=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\sampclnt.obj" : $(SOURCE) $(DEP_CPP_SAMPC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Debug"

DEP_CPP_SAMPC=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\sampclnt.obj" : $(SOURCE) $(DEP_CPP_SAMPC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "sampclnt - Win32 (ALPHA) axp Release"

DEP_CPP_SAMPC=\
	".\sampclnt.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\sampclnt.obj" : $(SOURCE) $(DEP_CPP_SAMPC) "$(INTDIR)"


!ENDIF 

SOURCE=.\sampclnt.rc
DEP_RSC_SAMPCL=\
	".\sampclnt.rc2"\
	".\sampver.h"\
	

"$(INTDIR)\sampclnt.res" : $(SOURCE) $(DEP_RSC_SAMPCL) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

