# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=streams - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to streams - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "streams - Win32 Release" && "$(CFG)" !=\
 "streams - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "streams.mak" CFG="streams - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "streams - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "streams - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "streams - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "streams - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\streams.exe"

CLEAN : 
	-@erase ".\Release\streams.exe"
	-@erase ".\Release\WaveFile.obj"
	-@erase ".\Release\streams.obj"
	-@erase ".\Release\debug.obj"
	-@erase ".\Release\AudioStream.obj"
	-@erase ".\Release\assert.obj"
	-@erase ".\Release\Timer.obj"
	-@erase ".\Release\streams.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/streams.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/streams.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib dsound.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=winmm.lib dsound.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/streams.pdb" /machine:I386 /out:"$(OUTDIR)/streams.exe" 
LINK32_OBJS= \
	"$(INTDIR)/WaveFile.obj" \
	"$(INTDIR)/streams.obj" \
	"$(INTDIR)/debug.obj" \
	"$(INTDIR)/AudioStream.obj" \
	"$(INTDIR)/assert.obj" \
	"$(INTDIR)/Timer.obj" \
	"$(INTDIR)/streams.res"

"$(OUTDIR)\streams.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\streams.exe" "$(OUTDIR)\streams.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\streams.bsc"
	-@erase ".\Debug\AudioStream.sbr"
	-@erase ".\Debug\streams.sbr"
	-@erase ".\Debug\Timer.sbr"
	-@erase ".\Debug\WaveFile.sbr"
	-@erase ".\Debug\debug.sbr"
	-@erase ".\Debug\assert.sbr"
	-@erase ".\Debug\streams.exe"
	-@erase ".\Debug\AudioStream.obj"
	-@erase ".\Debug\streams.obj"
	-@erase ".\Debug\Timer.obj"
	-@erase ".\Debug\WaveFile.obj"
	-@erase ".\Debug\debug.obj"
	-@erase ".\Debug\assert.obj"
	-@erase ".\Debug\streams.res"
	-@erase ".\Debug\streams.ilk"
	-@erase ".\Debug\streams.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/streams.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/streams.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/AudioStream.sbr" \
	"$(INTDIR)/streams.sbr" \
	"$(INTDIR)/Timer.sbr" \
	"$(INTDIR)/WaveFile.sbr" \
	"$(INTDIR)/debug.sbr" \
	"$(INTDIR)/assert.sbr"

"$(OUTDIR)\streams.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib dsound.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib dsound.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/streams.pdb" /debug /machine:I386 /out:"$(OUTDIR)/streams.exe" 
LINK32_OBJS= \
	"$(INTDIR)/AudioStream.obj" \
	"$(INTDIR)/streams.obj" \
	"$(INTDIR)/Timer.obj" \
	"$(INTDIR)/WaveFile.obj" \
	"$(INTDIR)/debug.obj" \
	"$(INTDIR)/assert.obj" \
	"$(INTDIR)/streams.res"

"$(OUTDIR)\streams.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "streams - Win32 Release"
# Name "streams - Win32 Debug"

!IF  "$(CFG)" == "streams - Win32 Release"

!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\streams.rc
DEP_RSC_STREA=\
	".\streams.ico"\
	

"$(INTDIR)\streams.res" : $(SOURCE) $(DEP_RSC_STREA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\streams.cpp
DEP_CPP_STREAM=\
	".\AudioStream.h"\
	".\streams.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\Timer.h"\
	".\WaveFile.h"\
	

!IF  "$(CFG)" == "streams - Win32 Release"

# SUBTRACT CPP /YX

"$(INTDIR)\streams.obj" : $(SOURCE) $(DEP_CPP_STREAM) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# SUBTRACT CPP /YX

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\streams.obj" : $(SOURCE) $(DEP_CPP_STREAM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\streams.sbr" : $(SOURCE) $(DEP_CPP_STREAM) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WaveFile.cpp
DEP_CPP_WAVEF=\
	".\assert.h"\
	".\Debug.h"\
	".\WaveFile.h"\
	

!IF  "$(CFG)" == "streams - Win32 Release"

# ADD CPP /YX"MMSYSTEM.H"

"$(INTDIR)\WaveFile.obj" : $(SOURCE) $(DEP_CPP_WAVEF) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/streams.pch" /YX"MMSYSTEM.H" /Fo"$(INTDIR)/"\
 /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# ADD CPP /YX"MMSYSTEM.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/streams.pch"\
 /YX"MMSYSTEM.H" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\WaveFile.obj" : $(SOURCE) $(DEP_CPP_WAVEF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WaveFile.sbr" : $(SOURCE) $(DEP_CPP_WAVEF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AudioStream.cpp
DEP_CPP_AUDIO=\
	".\assert.h"\
	".\Debug.h"\
	".\AudioStream.h"\
	{$(INCLUDE)}"\dsound.h"\
	".\Timer.h"\
	".\WaveFile.h"\
	

!IF  "$(CFG)" == "streams - Win32 Release"

# ADD CPP /YX"MMSYSTEM.H"

"$(INTDIR)\AudioStream.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/streams.pch" /YX"MMSYSTEM.H" /Fo"$(INTDIR)/"\
 /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# ADD CPP /YX"MMSYSTEM.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/streams.pch"\
 /YX"MMSYSTEM.H" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\AudioStream.obj" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AudioStream.sbr" : $(SOURCE) $(DEP_CPP_AUDIO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\debug.c

!IF  "$(CFG)" == "streams - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\debug.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Timer.cpp
DEP_CPP_TIMER=\
	".\assert.h"\
	".\Debug.h"\
	".\Timer.h"\
	

!IF  "$(CFG)" == "streams - Win32 Release"

# ADD CPP /YX"MMSYSTEM.H"

"$(INTDIR)\Timer.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/streams.pch" /YX"MMSYSTEM.H" /Fo"$(INTDIR)/"\
 /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# ADD CPP /YX"MMSYSTEM.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/streams.pch"\
 /YX"MMSYSTEM.H" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Timer.obj" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Timer.sbr" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\assert.c
DEP_CPP_ASSER=\
	".\assert.h"\
	

!IF  "$(CFG)" == "streams - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

"$(INTDIR)\assert.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "streams - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\assert.obj" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\assert.sbr" : $(SOURCE) $(DEP_CPP_ASSER) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
