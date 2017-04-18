# Microsoft Developer Studio Generated NMAKE File, Format Version 41001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=Autoduck - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Autoduck - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Autoduck - Win32 Release" && "$(CFG)" !=\
 "Autoduck - Win32 Debug" && "$(CFG)" != "Autoduck - Win32 Duck"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Autoduck.mak" CFG="Autoduck - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Autoduck - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Autoduck - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "Autoduck - Win32 Duck" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Autoduck - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Autoduck - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Autoduck.exe"

CLEAN : 
	-@erase "$(INTDIR)\Adoutput.obj"
	-@erase "$(INTDIR)\Cmdargs.obj"
	-@erase "$(INTDIR)\Docexpr.obj"
	-@erase "$(INTDIR)\errmsg.obj"
	-@erase "$(INTDIR)\extract.obj"
	-@erase "$(INTDIR)\Fmt.obj"
	-@erase "$(INTDIR)\Fmtconst.obj"
	-@erase "$(INTDIR)\Fmtdiag.obj"
	-@erase "$(INTDIR)\Fmtext.obj"
	-@erase "$(INTDIR)\Fmtfile.obj"
	-@erase "$(INTDIR)\Fmtif.obj"
	-@erase "$(INTDIR)\Fmtindex.obj"
	-@erase "$(INTDIR)\Fmtpara.obj"
	-@erase "$(INTDIR)\fmtspec.obj"
	-@erase "$(INTDIR)\Fmttag.obj"
	-@erase "$(INTDIR)\Fmttext.obj"
	-@erase "$(INTDIR)\Fmttoken.obj"
	-@erase "$(INTDIR)\Fmttopic.obj"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\output.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\parsetag.obj"
	-@erase "$(INTDIR)\topiclog.obj"
	-@erase "$(OUTDIR)\Autoduck.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /Fp"$(INTDIR)/Autoduck.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Autoduck.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Autoduck.pdb" /machine:I386 /out:"$(OUTDIR)/Autoduck.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Adoutput.obj" \
	"$(INTDIR)\Cmdargs.obj" \
	"$(INTDIR)\Docexpr.obj" \
	"$(INTDIR)\errmsg.obj" \
	"$(INTDIR)\extract.obj" \
	"$(INTDIR)\Fmt.obj" \
	"$(INTDIR)\Fmtconst.obj" \
	"$(INTDIR)\Fmtdiag.obj" \
	"$(INTDIR)\Fmtext.obj" \
	"$(INTDIR)\Fmtfile.obj" \
	"$(INTDIR)\Fmtif.obj" \
	"$(INTDIR)\Fmtindex.obj" \
	"$(INTDIR)\Fmtpara.obj" \
	"$(INTDIR)\fmtspec.obj" \
	"$(INTDIR)\Fmttag.obj" \
	"$(INTDIR)\Fmttext.obj" \
	"$(INTDIR)\Fmttoken.obj" \
	"$(INTDIR)\Fmttopic.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\output.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\parsetag.obj" \
	"$(INTDIR)\topiclog.obj"

"$(OUTDIR)\Autoduck.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Autoduck_"
# PROP BASE Intermediate_Dir "Autoduck_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Autoduck.exe" "$(OUTDIR)\Autoduck.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Adoutput.obj"
	-@erase "$(INTDIR)\Adoutput.sbr"
	-@erase "$(INTDIR)\Cmdargs.obj"
	-@erase "$(INTDIR)\Cmdargs.sbr"
	-@erase "$(INTDIR)\Docexpr.obj"
	-@erase "$(INTDIR)\Docexpr.sbr"
	-@erase "$(INTDIR)\errmsg.obj"
	-@erase "$(INTDIR)\errmsg.sbr"
	-@erase "$(INTDIR)\extract.obj"
	-@erase "$(INTDIR)\extract.sbr"
	-@erase "$(INTDIR)\Fmt.obj"
	-@erase "$(INTDIR)\Fmt.sbr"
	-@erase "$(INTDIR)\Fmtconst.obj"
	-@erase "$(INTDIR)\Fmtconst.sbr"
	-@erase "$(INTDIR)\Fmtdiag.obj"
	-@erase "$(INTDIR)\Fmtdiag.sbr"
	-@erase "$(INTDIR)\Fmtext.obj"
	-@erase "$(INTDIR)\Fmtext.sbr"
	-@erase "$(INTDIR)\Fmtfile.obj"
	-@erase "$(INTDIR)\Fmtfile.sbr"
	-@erase "$(INTDIR)\Fmtif.obj"
	-@erase "$(INTDIR)\Fmtif.sbr"
	-@erase "$(INTDIR)\Fmtindex.obj"
	-@erase "$(INTDIR)\Fmtindex.sbr"
	-@erase "$(INTDIR)\Fmtpara.obj"
	-@erase "$(INTDIR)\Fmtpara.sbr"
	-@erase "$(INTDIR)\fmtspec.obj"
	-@erase "$(INTDIR)\fmtspec.sbr"
	-@erase "$(INTDIR)\Fmttag.obj"
	-@erase "$(INTDIR)\Fmttag.sbr"
	-@erase "$(INTDIR)\Fmttext.obj"
	-@erase "$(INTDIR)\Fmttext.sbr"
	-@erase "$(INTDIR)\Fmttoken.obj"
	-@erase "$(INTDIR)\Fmttoken.sbr"
	-@erase "$(INTDIR)\Fmttopic.obj"
	-@erase "$(INTDIR)\Fmttopic.sbr"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\Input.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\output.obj"
	-@erase "$(INTDIR)\output.sbr"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\Parse.sbr"
	-@erase "$(INTDIR)\parsetag.obj"
	-@erase "$(INTDIR)\parsetag.sbr"
	-@erase "$(INTDIR)\topiclog.obj"
	-@erase "$(INTDIR)\topiclog.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Autoduck.bsc"
	-@erase "$(OUTDIR)\Autoduck.exe"
	-@erase "$(OUTDIR)\Autoduck.ilk"
	-@erase "$(OUTDIR)\Autoduck.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Autoduck.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Autoduck.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Adoutput.sbr" \
	"$(INTDIR)\Cmdargs.sbr" \
	"$(INTDIR)\Docexpr.sbr" \
	"$(INTDIR)\errmsg.sbr" \
	"$(INTDIR)\extract.sbr" \
	"$(INTDIR)\Fmt.sbr" \
	"$(INTDIR)\Fmtconst.sbr" \
	"$(INTDIR)\Fmtdiag.sbr" \
	"$(INTDIR)\Fmtext.sbr" \
	"$(INTDIR)\Fmtfile.sbr" \
	"$(INTDIR)\Fmtif.sbr" \
	"$(INTDIR)\Fmtindex.sbr" \
	"$(INTDIR)\Fmtpara.sbr" \
	"$(INTDIR)\fmtspec.sbr" \
	"$(INTDIR)\Fmttag.sbr" \
	"$(INTDIR)\Fmttext.sbr" \
	"$(INTDIR)\Fmttoken.sbr" \
	"$(INTDIR)\Fmttopic.sbr" \
	"$(INTDIR)\Input.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\output.sbr" \
	"$(INTDIR)\Parse.sbr" \
	"$(INTDIR)\parsetag.sbr" \
	"$(INTDIR)\topiclog.sbr"

"$(OUTDIR)\Autoduck.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/Autoduck.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Autoduck.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Adoutput.obj" \
	"$(INTDIR)\Cmdargs.obj" \
	"$(INTDIR)\Docexpr.obj" \
	"$(INTDIR)\errmsg.obj" \
	"$(INTDIR)\extract.obj" \
	"$(INTDIR)\Fmt.obj" \
	"$(INTDIR)\Fmtconst.obj" \
	"$(INTDIR)\Fmtdiag.obj" \
	"$(INTDIR)\Fmtext.obj" \
	"$(INTDIR)\Fmtfile.obj" \
	"$(INTDIR)\Fmtif.obj" \
	"$(INTDIR)\Fmtindex.obj" \
	"$(INTDIR)\Fmtpara.obj" \
	"$(INTDIR)\fmtspec.obj" \
	"$(INTDIR)\Fmttag.obj" \
	"$(INTDIR)\Fmttext.obj" \
	"$(INTDIR)\Fmttoken.obj" \
	"$(INTDIR)\Fmttopic.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\output.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\parsetag.obj" \
	"$(INTDIR)\topiclog.obj"

"$(OUTDIR)\Autoduck.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Autoduck_"
# PROP BASE Intermediate_Dir "Autoduck_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Duckrel"
# PROP Intermediate_Dir "Duckrel"
# PROP Target_Dir ""
OUTDIR=.\Duckrel
INTDIR=.\Duckrel

ALL : "$(OUTDIR)\Autoduck.exe"

CLEAN : 
	-@erase "$(INTDIR)\Adoutput.obj"
	-@erase "$(INTDIR)\Cmdargs.obj"
	-@erase "$(INTDIR)\Docexpr.obj"
	-@erase "$(INTDIR)\errmsg.obj"
	-@erase "$(INTDIR)\extract.obj"
	-@erase "$(INTDIR)\Fmt.obj"
	-@erase "$(INTDIR)\Fmtconst.obj"
	-@erase "$(INTDIR)\Fmtdiag.obj"
	-@erase "$(INTDIR)\Fmtext.obj"
	-@erase "$(INTDIR)\Fmtfile.obj"
	-@erase "$(INTDIR)\Fmtif.obj"
	-@erase "$(INTDIR)\Fmtindex.obj"
	-@erase "$(INTDIR)\Fmtpara.obj"
	-@erase "$(INTDIR)\fmtspec.obj"
	-@erase "$(INTDIR)\Fmttag.obj"
	-@erase "$(INTDIR)\Fmttext.obj"
	-@erase "$(INTDIR)\Fmttoken.obj"
	-@erase "$(INTDIR)\Fmttopic.obj"
	-@erase "$(INTDIR)\Input.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\output.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\parsetag.obj"
	-@erase "$(INTDIR)\topiclog.obj"
	-@erase "$(OUTDIR)\Autoduck.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "DUCK" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /D "DUCK" /Fp"$(INTDIR)/Autoduck.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Duckrel/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Autoduck.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"Duckrel/Autoduck.exe"
LINK32_FLAGS=/nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/Autoduck.pdb" /machine:I386 /out:"$(OUTDIR)/Autoduck.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Adoutput.obj" \
	"$(INTDIR)\Cmdargs.obj" \
	"$(INTDIR)\Docexpr.obj" \
	"$(INTDIR)\errmsg.obj" \
	"$(INTDIR)\extract.obj" \
	"$(INTDIR)\Fmt.obj" \
	"$(INTDIR)\Fmtconst.obj" \
	"$(INTDIR)\Fmtdiag.obj" \
	"$(INTDIR)\Fmtext.obj" \
	"$(INTDIR)\Fmtfile.obj" \
	"$(INTDIR)\Fmtif.obj" \
	"$(INTDIR)\Fmtindex.obj" \
	"$(INTDIR)\Fmtpara.obj" \
	"$(INTDIR)\fmtspec.obj" \
	"$(INTDIR)\Fmttag.obj" \
	"$(INTDIR)\Fmttext.obj" \
	"$(INTDIR)\Fmttoken.obj" \
	"$(INTDIR)\Fmttopic.obj" \
	"$(INTDIR)\Input.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\output.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\parsetag.obj" \
	"$(INTDIR)\topiclog.obj"

"$(OUTDIR)\Autoduck.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Autoduck - Win32 Release"
# Name "Autoduck - Win32 Debug"
# Name "Autoduck - Win32 Duck"

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TOPICLOG.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Adoutput.h

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cmdargs.cpp

!IF  "$(CFG)" == "Autoduck - Win32 Release"

DEP_CPP_CMDAR=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\Cmdargs.obj" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

DEP_CPP_CMDAR=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\Cmdargs.obj" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"

"$(INTDIR)\Cmdargs.sbr" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

DEP_CPP_CMDAR=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\FMTSPEC.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\Cmdargs.obj" : $(SOURCE) $(DEP_CPP_CMDAR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMDARGS.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Docexpr.cpp
DEP_CPP_DOCEX=\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Docexpr.obj" : $(SOURCE) $(DEP_CPP_DOCEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Docexpr.obj" : $(SOURCE) $(DEP_CPP_DOCEX) "$(INTDIR)"

"$(INTDIR)\Docexpr.sbr" : $(SOURCE) $(DEP_CPP_DOCEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Docexpr.obj" : $(SOURCE) $(DEP_CPP_DOCEX) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOCEXPR.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\errmsg.cpp
DEP_CPP_ERRMS=\
	".\ERRMSG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\errmsg.obj" : $(SOURCE) $(DEP_CPP_ERRMS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\errmsg.obj" : $(SOURCE) $(DEP_CPP_ERRMS) "$(INTDIR)"

"$(INTDIR)\errmsg.sbr" : $(SOURCE) $(DEP_CPP_ERRMS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\errmsg.obj" : $(SOURCE) $(DEP_CPP_ERRMS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ERRMSG.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\extract.cpp

!IF  "$(CFG)" == "Autoduck - Win32 Release"

DEP_CPP_EXTRA=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\EXTRACT.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\PARSETAG.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\extract.obj" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

DEP_CPP_EXTRA=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\EXTRACT.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\PARSETAG.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\extract.obj" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"

"$(INTDIR)\extract.sbr" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

DEP_CPP_EXTRA=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\EXTRACT.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\PARSETAG.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\extract.obj" : $(SOURCE) $(DEP_CPP_EXTRA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXTRACT.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmt.cpp
DEP_CPP_FMT_C=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmt.obj" : $(SOURCE) $(DEP_CPP_FMT_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmt.obj" : $(SOURCE) $(DEP_CPP_FMT_C) "$(INTDIR)"

"$(INTDIR)\Fmt.sbr" : $(SOURCE) $(DEP_CPP_FMT_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmt.obj" : $(SOURCE) $(DEP_CPP_FMT_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMT.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtconst.cpp
DEP_CPP_FMTCO=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtconst.obj" : $(SOURCE) $(DEP_CPP_FMTCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtconst.obj" : $(SOURCE) $(DEP_CPP_FMTCO) "$(INTDIR)"

"$(INTDIR)\Fmtconst.sbr" : $(SOURCE) $(DEP_CPP_FMTCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtconst.obj" : $(SOURCE) $(DEP_CPP_FMTCO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTCONST.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtdiag.cpp
DEP_CPP_FMTDI=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTDIAG.H"\
	".\FMTIF.H"\
	".\FMTTAG.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtdiag.obj" : $(SOURCE) $(DEP_CPP_FMTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtdiag.obj" : $(SOURCE) $(DEP_CPP_FMTDI) "$(INTDIR)"

"$(INTDIR)\Fmtdiag.sbr" : $(SOURCE) $(DEP_CPP_FMTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtdiag.obj" : $(SOURCE) $(DEP_CPP_FMTDI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTDIAG.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtext.cpp
DEP_CPP_FMTEX=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTEXT.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtext.obj" : $(SOURCE) $(DEP_CPP_FMTEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtext.obj" : $(SOURCE) $(DEP_CPP_FMTEX) "$(INTDIR)"

"$(INTDIR)\Fmtext.sbr" : $(SOURCE) $(DEP_CPP_FMTEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtext.obj" : $(SOURCE) $(DEP_CPP_FMTEX) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTEXT.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtfile.cpp
DEP_CPP_FMTFI=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTFILE.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtfile.obj" : $(SOURCE) $(DEP_CPP_FMTFI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtfile.obj" : $(SOURCE) $(DEP_CPP_FMTFI) "$(INTDIR)"

"$(INTDIR)\Fmtfile.sbr" : $(SOURCE) $(DEP_CPP_FMTFI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtfile.obj" : $(SOURCE) $(DEP_CPP_FMTFI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTFILE.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtif.cpp
DEP_CPP_FMTIF=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTIF.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtif.obj" : $(SOURCE) $(DEP_CPP_FMTIF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtif.obj" : $(SOURCE) $(DEP_CPP_FMTIF) "$(INTDIR)"

"$(INTDIR)\Fmtif.sbr" : $(SOURCE) $(DEP_CPP_FMTIF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtif.obj" : $(SOURCE) $(DEP_CPP_FMTIF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTIF.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtindex.cpp
DEP_CPP_FMTIN=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTINDEX.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtindex.obj" : $(SOURCE) $(DEP_CPP_FMTIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtindex.obj" : $(SOURCE) $(DEP_CPP_FMTIN) "$(INTDIR)"

"$(INTDIR)\Fmtindex.sbr" : $(SOURCE) $(DEP_CPP_FMTIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtindex.obj" : $(SOURCE) $(DEP_CPP_FMTIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTINDEX.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmtpara.cpp
DEP_CPP_FMTPA=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTIF.H"\
	".\FMTPARA.H"\
	".\FMTTAG.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmtpara.obj" : $(SOURCE) $(DEP_CPP_FMTPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmtpara.obj" : $(SOURCE) $(DEP_CPP_FMTPA) "$(INTDIR)"

"$(INTDIR)\Fmtpara.sbr" : $(SOURCE) $(DEP_CPP_FMTPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmtpara.obj" : $(SOURCE) $(DEP_CPP_FMTPA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTPARA.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fmtspec.cpp

!IF  "$(CFG)" == "Autoduck - Win32 Release"

DEP_CPP_FMTSP=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\fmtspec.obj" : $(SOURCE) $(DEP_CPP_FMTSP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

DEP_CPP_FMTSP=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\fmtspec.obj" : $(SOURCE) $(DEP_CPP_FMTSP) "$(INTDIR)"

"$(INTDIR)\fmtspec.sbr" : $(SOURCE) $(DEP_CPP_FMTSP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

DEP_CPP_FMTSP=\
	".\ERRMSG.H"\
	".\FMTSPEC.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

"$(INTDIR)\fmtspec.obj" : $(SOURCE) $(DEP_CPP_FMTSP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTSPEC.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmttag.cpp
DEP_CPP_FMTTA=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTIF.H"\
	".\FMTTAG.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmttag.obj" : $(SOURCE) $(DEP_CPP_FMTTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmttag.obj" : $(SOURCE) $(DEP_CPP_FMTTA) "$(INTDIR)"

"$(INTDIR)\Fmttag.sbr" : $(SOURCE) $(DEP_CPP_FMTTA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmttag.obj" : $(SOURCE) $(DEP_CPP_FMTTA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTTAG.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmttext.cpp
DEP_CPP_FMTTE=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTIF.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmttext.obj" : $(SOURCE) $(DEP_CPP_FMTTE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmttext.obj" : $(SOURCE) $(DEP_CPP_FMTTE) "$(INTDIR)"

"$(INTDIR)\Fmttext.sbr" : $(SOURCE) $(DEP_CPP_FMTTE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmttext.obj" : $(SOURCE) $(DEP_CPP_FMTTE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTTEXT.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmttoken.cpp
DEP_CPP_FMTTO=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTTOKEN.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmttoken.obj" : $(SOURCE) $(DEP_CPP_FMTTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmttoken.obj" : $(SOURCE) $(DEP_CPP_FMTTO) "$(INTDIR)"

"$(INTDIR)\Fmttoken.sbr" : $(SOURCE) $(DEP_CPP_FMTTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmttoken.obj" : $(SOURCE) $(DEP_CPP_FMTTO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTTOKEN.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fmttopic.cpp
DEP_CPP_FMTTOP=\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTIF.H"\
	".\FMTTAG.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Fmttopic.obj" : $(SOURCE) $(DEP_CPP_FMTTOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Fmttopic.obj" : $(SOURCE) $(DEP_CPP_FMTTOP) "$(INTDIR)"

"$(INTDIR)\Fmttopic.sbr" : $(SOURCE) $(DEP_CPP_FMTTOP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Fmttopic.obj" : $(SOURCE) $(DEP_CPP_FMTTOP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FMTTOPIC.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Input.cpp
DEP_CPP_INPUT=\
	".\ERRMSG.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"

"$(INTDIR)\Input.sbr" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INPUT.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	".\Adoutput.h"\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\EXTRACT.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\output.h"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"

"$(INTDIR)\main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\output.cpp
DEP_CPP_OUTPU=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\output.h"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\output.obj" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\output.obj" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"

"$(INTDIR)\output.sbr" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\output.obj" : $(SOURCE) $(DEP_CPP_OUTPU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\output.h

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Parse.cpp
DEP_CPP_PARSE=\
	".\PARSE.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"

"$(INTDIR)\Parse.sbr" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PARSE.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\parsetag.cpp
DEP_CPP_PARSET=\
	".\CMDARGS.H"\
	".\DOCEXPR.H"\
	".\ERRMSG.H"\
	".\EXTRACT.H"\
	".\FMT.H"\
	".\FMTCONST.H"\
	".\FMTDIAG.H"\
	".\FMTEXT.H"\
	".\FMTFILE.H"\
	".\FMTIF.H"\
	".\FMTINDEX.H"\
	".\FMTPARA.H"\
	".\FMTSPEC.H"\
	".\FMTTAG.H"\
	".\FMTTEXT.H"\
	".\FMTTOKEN.H"\
	".\FMTTOPIC.H"\
	".\INPUT.H"\
	".\PARSE.H"\
	".\PARSETAG.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\parsetag.obj" : $(SOURCE) $(DEP_CPP_PARSET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\parsetag.obj" : $(SOURCE) $(DEP_CPP_PARSET) "$(INTDIR)"

"$(INTDIR)\parsetag.sbr" : $(SOURCE) $(DEP_CPP_PARSET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\parsetag.obj" : $(SOURCE) $(DEP_CPP_PARSET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PARSETAG.H

!IF  "$(CFG)" == "Autoduck - Win32 Release"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"

!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\topiclog.cpp
DEP_CPP_TOPIC=\
	".\ERRMSG.H"\
	".\PARSE.H"\
	".\TOPICLOG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\topiclog.obj" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\topiclog.obj" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"

"$(INTDIR)\topiclog.sbr" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\topiclog.obj" : $(SOURCE) $(DEP_CPP_TOPIC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Adoutput.cpp
DEP_CPP_ADOUT=\
	".\Adoutput.h"\
	".\ERRMSG.H"\
	

!IF  "$(CFG)" == "Autoduck - Win32 Release"


"$(INTDIR)\Adoutput.obj" : $(SOURCE) $(DEP_CPP_ADOUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Debug"


"$(INTDIR)\Adoutput.obj" : $(SOURCE) $(DEP_CPP_ADOUT) "$(INTDIR)"

"$(INTDIR)\Adoutput.sbr" : $(SOURCE) $(DEP_CPP_ADOUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Autoduck - Win32 Duck"


"$(INTDIR)\Adoutput.obj" : $(SOURCE) $(DEP_CPP_ADOUT) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
