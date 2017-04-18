# Microsoft Developer Studio Generated NMAKE File, Based on qurydemo.dsp
!IF "$(CFG)" == ""
CFG=qurydemo - Win32 x86 Debug
!MESSAGE No configuration specified. Defaulting to qurydemo - Win32 x86 Debug.
!ENDIF 

!IF "$(CFG)" != "qurydemo - Win32 x86 Debug" && "$(CFG)" !=\
 "qurydemo - Win32 x86 Release" && "$(CFG)" !=\
 "qurydemo - Win32 (ALPHA) axp Release" && "$(CFG)" !=\
 "qurydemo - Win32 (ALPHA) axp Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qurydemo.mak" CFG="qurydemo - Win32 x86 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qurydemo - Win32 x86 Debug" (based on "Win32 (x86) Application")
!MESSAGE "qurydemo - Win32 x86 Release" (based on "Win32 (x86) Application")
!MESSAGE "qurydemo - Win32 (ALPHA) axp Release" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE "qurydemo - Win32 (ALPHA) axp Debug" (based on\
 "Win32 (ALPHA) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

OUTDIR=.\X86_Debu
INTDIR=.\X86_Debu
# Begin Custom Macros
OutDir=.\.\X86_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\qurydemo.exe"

!ELSE 

ALL : "$(OUTDIR)\qurydemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\query.obj"
	-@erase "$(INTDIR)\qurydemo.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\qurydemo.exe"
	-@erase "$(OUTDIR)\qurydemo.ilk"
	-@erase "$(OUTDIR)\qurydemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)\qurydemo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\X86_Debu/
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\qurydemo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qurydemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qurydemo.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)\qurydemo.exe"\
 /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\query.obj" \
	"$(INTDIR)\qurydemo.res"

"$(OUTDIR)\qurydemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

OUTDIR=.\X86_Rele
INTDIR=.\X86_Rele
# Begin Custom Macros
OutDir=.\.\X86_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\qurydemo.exe"

!ELSE 

ALL : "$(OUTDIR)\qurydemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\query.obj"
	-@erase "$(INTDIR)\qurydemo.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\qurydemo.exe"
	-@erase "$(OUTDIR)\qurydemo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /Zi /Od /Ob1 /I "..\..\include" /D "WIN32" /D\
 "_NDEBUG" /D "_WINDOWS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\X86_Rele/
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
MTL_PROJ=/nologo /D "_NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\qurydemo.res" /d "_NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qurydemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qurydemo.pdb" /machine:I386\
 /out:"$(OUTDIR)\qurydemo.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\query.obj" \
	"$(INTDIR)\qurydemo.res"

"$(OUTDIR)\qurydemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

OUTDIR=.\axp_Rele
INTDIR=.\axp_Rele
# Begin Custom Macros
OutDir=.\.\axp_Rele
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\qurydemo.exe"

!ELSE 

ALL : "$(OUTDIR)\qurydemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\query.obj"
	-@erase "$(INTDIR)\qurydemo.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\qurydemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /MD /Gt0 /W3 /O2 /I "..\..\include" /D "WIN32" /D "_WINDOWS"\
 /Fp"$(INTDIR)\qurydemo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\qurydemo.res" /d "_NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qurydemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /pdb:"$(OUTDIR)\qurydemo.pdb" /machine:ALPHA\
 /out:"$(OUTDIR)\qurydemo.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\query.obj" \
	"$(INTDIR)\qurydemo.res"

"$(OUTDIR)\qurydemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

OUTDIR=.\axp_Debu
INTDIR=.\axp_Debu
# Begin Custom Macros
OutDir=.\.\axp_Debu
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\qurydemo.exe"

!ELSE 

ALL : "$(OUTDIR)\qurydemo.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\query.obj"
	-@erase "$(INTDIR)\qurydemo.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\qurydemo.exe"
	-@erase "$(OUTDIR)\qurydemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /alpha 
CPP=cl.exe
CPP_PROJ=/nologo /Gt0 /W3 /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\qurydemo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /MDd /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\qurydemo.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qurydemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=oledb.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /pdb:"$(OUTDIR)\qurydemo.pdb" /debug /machine:ALPHA\
 /out:"$(OUTDIR)\qurydemo.exe" /libpath:"..\..\LIB\$(PROCESSOR_ARCHITECTURE)" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\query.obj" \
	"$(INTDIR)\qurydemo.res"

"$(OUTDIR)\qurydemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "qurydemo - Win32 x86 Debug" || "$(CFG)" ==\
 "qurydemo - Win32 x86 Release" || "$(CFG)" ==\
 "qurydemo - Win32 (ALPHA) axp Release" || "$(CFG)" ==\
 "qurydemo - Win32 (ALPHA) axp Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

DEP_CPP_MAIN_=\
	".\qurydemo.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

DEP_CPP_MAIN_=\
	".\qurydemo.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

DEP_CPP_MAIN_=\
	".\qurydemo.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

DEP_CPP_MAIN_=\
	".\qurydemo.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

SOURCE=.\query.cpp

!IF  "$(CFG)" == "qurydemo - Win32 x86 Debug"

DEP_CPP_QUERY=\
	".\qurydemo.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\query.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 x86 Release"

DEP_CPP_QUERY=\
	".\qurydemo.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\query.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Release"

DEP_CPP_QUERY=\
	".\qurydemo.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\query.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qurydemo - Win32 (ALPHA) axp Debug"

DEP_CPP_QUERY=\
	".\qurydemo.h"\
	{$(INCLUDE)}"msdaguid.h"\
	{$(INCLUDE)}"oledb.h"\
	{$(INCLUDE)}"oledberr.h"\
	{$(INCLUDE)}"transact.h"\
	

"$(INTDIR)\query.obj" : $(SOURCE) $(DEP_CPP_QUERY) "$(INTDIR)"


!ENDIF 

SOURCE=.\qurydemo.rc
DEP_RSC_QURYD=\
	".\newquery.bmp"\
	".\querywdw.ico"\
	".\qurydemo.h"\
	".\qurydemo.ico"\
	".\qurydemo.rc2"\
	".\quryver.h"\
	".\runquery.bmp"\
	

"$(INTDIR)\qurydemo.res" : $(SOURCE) $(DEP_RSC_QURYD) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

