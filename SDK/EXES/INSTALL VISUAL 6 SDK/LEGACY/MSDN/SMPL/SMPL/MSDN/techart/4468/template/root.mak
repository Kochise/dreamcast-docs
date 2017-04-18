# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)
!MESSAGE No configuration specified.  Defaulting to $$SAFE_ROOT$$ - Win32 NT kernel\
 driver (debug).
!ENDIF 

!IF "$(CFG)" != "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)" && "$(CFG)" !=\
 "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "root.mak" CFG="$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\$$SAFE_ROOT$$.sys"

CLEAN : 
	-@erase "c:\ddk\lib\i386\free\$$SAFE_ROOT$$.sys"
	-@erase ".\WinRel\$$SAFE_ROOT$$.res"
	-@erase ".\WinRel\$$SAFE_ROOT$$dep.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /G4 /Gz /MT /W3 /Ox /Gf /Gy /I "c:\ddk\inc" /D "NDEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /U "NT_INST" /c
# SUBTRACT CPP /Ot /Oa /Ow /Og /Oi /Os /Fr /YX
CPP_PROJ=/nologo /G4 /Gz /MT /W3 /Ox /Gf /Gy /I "c:\ddk\inc" /D "NDEBUG" /D\
 "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D\
 "WIN32_LEAN_AND_MEAN" /D "NT_UP" /U "NT_INST" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/$$SAFE_ROOT$$.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/root.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 c:\ddk\lib\i386\free\ntoskrnl.lib c:\ddk\lib\i386\free\hal.lib kernel32.lib /nologo /base:0x10000 /entry:"DriverEntry@8" /pdb:"mousecl.pdb" /machine:I386 /nodefaultlib /out:"c:\ddk\lib\i386\free\$$SAFE_ROOT$$.sys" /SUBSYSTEM:native
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=c:\ddk\lib\i386\free\ntoskrnl.lib c:\ddk\lib\i386\free\hal.lib\
 kernel32.lib /nologo /base:0x10000 /entry:"DriverEntry@8" /incremental:no\
 /pdb:"mousecl.pdb" /machine:I386 /nodefaultlib\
 /out:"c:\ddk\lib\i386\free\$$SAFE_ROOT$$.sys" /SUBSYSTEM:native 
LINK32_OBJS= \
	"$(INTDIR)/$$SAFE_ROOT$$dep.obj" \
	"$(INTDIR)/$$SAFE_ROOT$$.res"

"$(OUTDIR)\$$SAFE_ROOT$$.sys" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\$$SAFE_ROOT$$.sys"

CLEAN : 
	-@erase "c:\ddk\lib\i386\checked\$$SAFE_ROOT$$.sys"
	-@erase ".\WinDebug\$$SAFE_ROOT$$.res"
	-@erase ".\WinDebug\$$SAFE_ROOT$$dep.obj"
	-@erase ".\WinDebug\$$SAFE_ROOT$$.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /G4 /Gz /MTd /W3 /Z7 /Oi /Gf /Gy /I "c:\ddk\inc" /D "_DEBUG" /D "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D "WIN32_LEAN_AND_MEAN" /D "NT_UP" /D "RDRDBG" /D "SRVDBG" /D "DBG" /D "_IDWBUILD" /U "NT_INST" /Zel /QI6 /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /G4 /Gz /MTd /W3 /Z7 /Oi /Gf /Gy /I "c:\ddk\inc" /D "_DEBUG"\
 /D "_X86_" /D "i386" /D "STD_CALL" /D "CONDITION_HANDLING" /D\
 "WIN32_LEAN_AND_MEAN" /D "NT_UP" /D "RDRDBG" /D "SRVDBG" /D "DBG" /D\
 "_IDWBUILD" /U "NT_INST" /Fo"$(INTDIR)/" /Zel /QI6 /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/$$SAFE_ROOT$$.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/root.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /base:0x10000 /entry:"DriverEntry@8" /incremental:no /debug /debugtype:both /machine:I386 /nodefaultlib /out:"c:\ddk\lib\i386\checked\$$SAFE_ROOT$$.sys" /SUBSYSTEM:native
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /base:0x10000 /entry:"DriverEntry@8" /incremental:no\
 /pdb:"$(OUTDIR)/$$SAFE_ROOT$$.pdb" /debug /debugtype:both /machine:I386 /nodefaultlib\
 /out:"c:\ddk\lib\i386\checked\$$SAFE_ROOT$$.sys" /SUBSYSTEM:native 
LINK32_OBJS= \
	"$(INTDIR)/$$SAFE_ROOT$$dep.obj" \
	"$(INTDIR)/$$SAFE_ROOT$$.res"

"$(OUTDIR)\$$SAFE_ROOT$$.sys" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)"
# Name "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"

!IF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)"

!ELSEIF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\$$SAFE_ROOT$$.rc
NODEP_RSC_$$SAFE_ROOT$$=\
	".\common.ver"\
	

!IF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (release)"


"$(INTDIR)\$$SAFE_ROOT$$.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "$$SAFE_ROOT$$ - Win32 NT kernel driver (debug)"


"$(INTDIR)\$$SAFE_ROOT$$.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\$$SAFE_ROOT$$dep.c

"$(INTDIR)\$$SAFE_ROOT$$dep.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
