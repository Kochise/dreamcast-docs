#----------------------------------------------------------------------------
#
# Description:
#   Make File Header for BackOffice Software Development Kit
#
# Copyright:
#   Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
#
#----------------------------------------------------------------------------

!ifndef BASEMAKE_INCLUDED       # Prevent multiple inclusions
BASEMAKE_INCLUDED = 1


#*********************************************
#
# Parameter Checking and Defaults
#
#*********************************************
!ifndef Proj
!     ERROR Component name (Proj) has not been defined.
!endif

!ifndef INCLUDE
!   ERROR INCLUDE variable is empty; must include at least system include directory
!endif

!ifndef LIB
!   ERROR LIB variable is empty; must include at least system lib directory
!endif

!if defined(clean)
$(Proj): Clean
!else
$(Proj): All
!endif

!if defined(nodebug)
BLDTYPE=Retail
!endif

!if "$(BLDTYPE)" == "Retail" | "$(BLDTYPE)" == "RETAIL" | "$(BLDTYPE)" == "retail" | "$(BLDTYPE)" == "RTL" | "$(BLDTYPE)" == "rtl"
BLDTYPE1=Retail
!else if "$(BLDTYPE)" == "Profile" | "$(BLDTYPE)" == "PROFILE" | "$(BLDTYPE)" == "profile"
BLDTYPE1=Profile
!else if "$(BLDTYPE)" == "Debug" | "$(BLDTYPE)" == "DEBUG" | "$(BLDTYPE)" == "debug" | "$(BLDTYPE)" == "DBG" | "$(BLDTYPE)" == "dbg"
BLDTYPE1=Debug
!else ifndef BLDTYPE
BLDTYPE1=Debug
!else
!   ERROR BLDTYPE must be either Retail, Profile or Debug.
!endif   

!if "$(BLDTYPE1)" == "Retail"
nodebug=1
!endif

!ifndef PLATFORM
PLATFORM=Win32
!endif   

!ifndef CALL
CALL=C
!endif

!ifndef PACK
PACK=YES
!endif

!ifndef LOG
LOG=YES
!endif

!ifndef WARNING_LEVEL
WARNING_LEVEL=3
!endif

!ifndef CPU
!ifndef PROCESSOR_ARCHITECTURE
!ERROR CPU and PROCESSOR_ARCHITECTURE variables are empty; at least one must be defined
!endif
CPU=$(PROCESSOR_ARCHITECTURE)
!if "$(CPU)"=="x86" | "$(CPU)"=="X86"
CPU = i386
!endif
!endif

!ifndef APPVER
APPVER=4.0
!endif

!ifndef USE_EXCHANGE
!include <win32.mak>
!endif

# Save build args for any recursive nmakes 
BLDARGS= BLDTYPE=$(BLDTYPE) PLATFORM=$(PLATFORM) LOG=$(LOG) CPU=$(CPU) 

#*********************************************
#
# Paths
#
#*********************************************

!ifndef BKOFFICE
!ifdef PROJROOT
BKOFFICE=$(PROJROOT)\        # must add trailing backslash
!else
BKOFFICE=\BkOffice\          # assume a reasonable default
!endif
!endif

!ifdef MAKEDIRS
MkDest=
!include $(MAKEDIRS)
!else
ResDir=.
ObjDir=.\$(PLATFORM)\$(BLDTYPE1)
IncDir=$(BKOFFICE)Include
LibDir=$(BKOFFICE)Lib

INCLUDE=$(ObjDir);$(IncDir);$(INCLUDE);
LIB=$(LibDir);$(LIB);

# Win95 doesn't support "&" on command line
MkDest=@for %d in ($(PLATFORM) $(ObjDir)) do @$(COMSPEC) /c if not exist %d md %d

!endif

#*********************************************
#
# Tools
#
#*********************************************

MAKEEXE = nmake
IMPLIB  = lib
CC      = cl
LIBU    = lib
LINK    = link
RC      = rc
MC      = mc
HC      = start /wait hcrtf


#*********************************************
#
# Flags
#
#*********************************************

# CL is for all C and C++ files
#   -WX     Warnings as errors
#   -J      char becomes unsigned char
#   
CL=$(cflags) -c -W$(WARNING_LEVEL) -J -Fo$@ /nologo $(CL)

# LFLAGS is for all links
LFLAGS=-NOLOGO -NODEFAULTLIB -machine:$(CPU) -out:$@ -INCREMENTAL:NO -PDB:NONE $(LFLAGS)

# DLLFLAGS is for linking DLLs
DLLFLAGS=-DLL -map:$(ObjDir)\$(@B).map $(DLLFLAGS)

# LIBFLAGS is for making libraries
LIBFLAGS=-NOLOGO -MACHINE:$(CPU) -out:$@ $(LIBFLAGS) 

# RFLAGS is for Windows resources
RFLAGS= -I$(ResDir) -fo$@ -DWIN32 $(noansi) -r -D_WIN32 $(RFLAGS) 

# MFLAGS is for the message compiler
MFLAGS=-v -c -s -h $(ObjDir) -r $(ObjDir) -x $(ObjDir) $(MFLAGS)

# MRFLAGS is for the resource compiler when used after the message compiler
MRFLAGS=-l 409 -r -x -i$(ObjDir) $(MRFLAGS)

# HFLAGS is for the help compiler 
HFLAGS=-xn

#---------------------------------------------
# Calling convention Flag
#---------------------------------------------

!if "$(CALL)"=="PASCAL"
CL=-Gc $(CL)
!endif

#---------------------------------------------
# Function Packaging Flag
#---------------------------------------------

!if "$(PACK)" == "YES"
CL=-Gy $(CL)
cDefines=-Gy $(cDefines)
!endif

#---------------------------------------------
# Output Redirection
#---------------------------------------------
!if "$(LOG)" == "NO"
LogCmd=
!else
LogCmd= >> $(ObjDir)\$(Proj).Out
!endif 

#---------------------------------------------
# Optimization Flags
#---------------------------------------------
!if "$(BLDTYPE1)" == "Retail"
CL=-O2 $(CL)
!else if "$(BLDTYPE1)" == "Profile"
CL=-Od -Z7 -Gh $(CL)
!else
CL=-Od -Z7 $(CL)
!endif

#---------------------------------------------
# PLATFORM specific Flags
#---------------------------------------------
!if "$(CPU)" == "I386"
CL = $(CL) -D_X86_=1
scall  = -Gz
lflags   = $(lflags) -align:0x1000
!endif

!if "$(CPU)" == "MIPS"
CL = $(CL) -D_MIPS_=1
scall  =
!endif

!if "$(CPU)" == "PPC"
CL = $(CL) -D_PPC_=1
scall  =
lflags   = $(lflags) -ignore:4078
!endif

!if "$(CPU)" == "ALPHA"
CL = $(CL) -D_ALPHA_=1
scall  =
!endif

#---------------------------------------------
# Windows version
#---------------------------------------------
!if "$(APPVER)" == "4.0"
CL = $(CL) -DWINVER=0x0400
rflags=$(rflags) -DWINVER=0x0400
!endif

#---------------------------------------------
# Additional MFC Flags
#---------------------------------------------
# Note: we are only using MFC for Exchange Admin
# extension dlls, which must be statically linked to MFC.

!ifdef Use_MFC
CL= $(CL) /GX /DSTRICT /DWIN32 /D_WINDOWS /D_MBCS /D_WINDLL 
CL= $(CL) /D_USRDLL -D_AFX_NO_BSTR_SUPPORT /D_AFXDLL

!if "$(BLDTYPE1)"=="Debug"
CL= $(CL) /D_DEBUG
!endif

!ifdef crtdll                                 # Use DLL CRT? (which is multithreaded)
crtflags = -MD$(DbgLibFlag) $(crtflags)
!elseif defined(crtst) && !defined(crtflags)  # use Single Threaded CRT?
crtflags = -ML$(DbgLibFlag) $(crtflags)
!elseif defined(crtmt)                        # use Multithreaded CRT?
crtflags = -MT$(DbgLibFlag) $(crtflags)
!else                                         # default to crtdll
crtflags = -MD$(DbgLibFlag) $(crtflags)
!endif                                        # ifdef crtdll/else crtst/crtmt/else

!endif

#---------------------------------------------
# Build Type Flags  (Retail/Debug)
#---------------------------------------------

!if "$(BLDTYPE1)"=="Retail"
CL=-DSHIP $(CL)
LFLAGS = $(LFLAGS) -RELEASE
!else if "$(BLDTYPE1)"=="Profile"
CL=-DDEBUG -DTEST -DPROFILE $(CL)
LFLAGS = $(LFLAGS) -DEBUG:mapped,partial -DEBUGTYPE:coff -PROFILE
libs = $(libs) CAP.LIB
!else 
CL=-DDEBUG -DTEST $(CL) 
LFLAGS = $(LFLAGS) -debug:full -debugtype:cv
!endif


#---------------------------------------------
# Determine CRT Flags
#---------------------------------------------

!ifdef crtdll                                 # Use DLL CRT? (which is multithreaded)
crtflags = -DWIN32 $(noansi) -D_WIN32 -D_MT -D_DLL
!elseif defined(crtst) && !defined(crtflags)  # use Single Threaded CRT?
crtflags = -DWIN32 $(noansi) -D_WIN32
!elseif defined(crtmt)                        # use Multithreaded CRT?
crtflags = -DWIN32 $(noansi) -D_WIN32 -D_MT
!else                                         # default to crtdll
crtflags = -DWIN32 $(noansi) -D_WIN32 -D_MT -D_DLL
!endif                                        # ifdef crtdll/else crtst/crtmt/else

#---------------------------------------------
# Determine app type Flags (console, gui, or DLL)
#---------------------------------------------

!if defined(console)                          # console app
linkflags=$(linkflags) -subsystem:console -entry:mainCRTStartup
!elseif !defined(dll)                         # not a dll, default to gui app
linkflags=$(linkflags) -subsystem:windows -entry:WinMainCRTStartup
!endif                                        # ifdef console/else



#*********************************************
#
# Libraries
#
#*********************************************

!if "$(BLDTYPE1)"=="Retail"
DbgLibFlag =
!else
DbgLibFlag = d
!endif

#---------------------------------------------
# Back Office SDK specific
#---------------------------------------------
!ifdef USE_SNA
libs=$(libs) fmistr32.lib ihvLink.lib snacli.lib wappc32.lib wcpic32.lib
libs=$(libs) wincsv32.lib winrui32.lib winsli32.lib
!endif # USE_SNA

!ifdef USE_SQL
libs=$(libs) ntwdbLib.lib
!endif # USE_SQL

!ifdef USE_ODS
libs=$(libs) opends60.lib
!endif # USE_ODS

!if defined(USE_MSM) || defined(USE_SMS)
libs=$(libs) smsapi.lib objectty.lib
!endif # USE_MSM || USE_SMS

!ifdef USE_NETMON
libs=$(libs) atalk.lib bhmon.lib bhsupp.lib browser.lib filter.lib friendly.lib
libs=$(libs) hexedit.lib llc.lib nal.lib ncp.lib netlogon.lib nmapi.lib
libs=$(libs) parser.lib ppp.lib slbs.lib toolbar.lib
!endif # USE_NETMON

!ifdef USE_EXCHANGE
!  ifndef Building_ExchSDK
libs=ExchSDK$(DbgLibFlag).Lib $(libs)
!  endif # Building_ExchSDK

libs=$(libs) Mapi32.Lib Uuid.Lib

!if "$(WARNING_LEVEL)" != "4"
CL= $(CL) -WX
!endif

DLLFLAGS = $(DLLFLAGS) -def:$(@B).def
!endif # USE_EXCHANGE

#---------------------------------------------
# Determine CRT Libraries
#---------------------------------------------
libc = libc$(DbgLibFlag).lib oldnames.lib
libcmt = libcmt$(DbgLibFlag).lib oldnames.lib
libcdll = msvcrt$(DbgLibFlag).lib oldnames.lib

!ifdef crtdll                                 # Use DLL CRT?
libcrt=$(libcdll)
!elseif defined(crtst) && !defined(crtflags)  # use Single Threaded CRT?
libcrt=$(libc)
!elseif defined(crtmt)                        # use Multithreaded CRT?
libcrt=$(libcmt)
!else                                         # default to crtdll
libcrt=$(libcdll)
!endif                                        # endif crtdll/else crtst/crtmt/else

#---------------------------------------------
# Determine app type libraries (console, gui, or DLL)
#---------------------------------------------

!ifdef dll                                    # is this a DLL?
linklibs=$(libs) kernel32.lib advapi32.lib user32.lib gdi32.lib comctl32.lib comdlg32.lib ole32.lib winspool.lib version.lib
!elseif defined(console)                      # not a DLL, perhaps a console app
linklibs=$(libs) kernel32.lib advapi32.lib user32.lib ole32.lib version.lib
!else                                         # default to gui app
linklibs=$(libs) kernel32.lib $(optlibs) advapi32.lib user32.lib gdi32.lib comdlg32.lib ole32.lib winspool.lib version.lib
!endif                                        # ifdef dll/else console/else

LinkLibs = $(LibList) $(linklibs) $(libcrt)

!if "$(BLDTYPE1)" == "Profile"
LinkLibs = $(LinkLibs) cap.lib
!endif


#---------------------------------------------
# Additional MFC Libraries
#---------------------------------------------
# Note that linking order is important when using MFC!

!ifdef Use_MFC
linklibs = mfcs40$(DbgLibFlag).lib mfc40$(DbgLibFlag).lib $(linklibs)
!endif


#*********************************************
#
# Inference Rules
#
#*********************************************
.SUFFIXES:
.SUFFIXES: .c .cpp .obj .def .lib .dll .exe .mc .rc .res .exp .bin .hpj

# C Targets
.c{$(ObjDir)\}.obj:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)
!endif
    $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)

# C++ Targets
.cpp{$(ObjDir)\}.obj:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)
!endif
    $(CC) $(CL) $(crtflags) $(cDefines) $< $(LogCmd)

# Resource Targets from .RC files
{$(ResDir)\}.rc{$(ObjDir)\}.res:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo $(RC) $(RFLAGS) $(ResDir)\$(@B).rc $(LogCmd)
!endif
    $(RC) $(RFLAGS) $(ResDir)\$(@B).rc $(LogCmd)

# Resource Targets from .MC files
.mc{$(ObjDir)\}.res:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo $(MC) $(MFLAGS) $< $(LogCmd)
!endif
    $(MC) $(MFLAGS) $< $(LogCmd)
!if "$(LOG)"=="YES"
    @echo $(RC) $(MRFLAGS) -fo$@ $(ObjDir)\$(@B).rc $(LogCmd)
!endif
    $(RC) $(MRFLAGS) -fo$@ $(ObjDir)\$(@B).rc $(LogCmd)

# Import Libraries
.def{$(ObjDir)\}.lib:
!if "$(LOG)"=="YES"
    @echo $(IMPLIB) -NOLOGO -MACHINE:$(CPU) -DEF:$(@B).DEF -OUT:$@ $(LogCmd)
!endif
    $(IMPLIB) -NOLOGO -MACHINE:$(CPU) -DEF:$(@B).DEF -OUT:$@ $(LogCmd)
    xcopy $@ $(LibDir)\ $(LogCmd)

.def{$(ObjDir)\}.exp:
!if "$(LOG)"=="YES"
    @echo $(IMPLIB) -NOLOGO -MACHINE:$(CPU) -DEF:$(@B).DEF -OUT:$(@R).Lib $(LogCmd)
!endif
    $(IMPLIB) -NOLOGO -MACHINE:$(CPU) -DEF:$(@B).DEF -OUT:$(@R).Lib $(LogCmd)

# Static Libraries
{$(ObjDir)\}.obj{$(ObjDir)\}.lib:
!if "$(LOG)"=="YES"
    @echo $(LIBU) $(LIBFLAGS)  $** $(LogCmd)
!endif
    $(LIBU) $(LIBFLAGS) $** $(LogCmd)
!if "$(LOG)"=="YES"
    @echo xcopy $@ $(LibDir) $(LogCmd)
!endif
    xcopy $@ $(LibDir)\ $(LogCmd)

# DLLs
{$(ObjDir)\}.obj{$(ObjDir)\}.dll:
    @echo $** > $(ObjDir)\objfiles.lst
    @echo $(LinkLibs) > $(ObjDir)\libfiles.lst
!if "$(LOG)"=="YES"
    @echo   $(LINK) $(LFLAGS) $(DLLFLAGS) $(linkflags) @$(ObjDir)\objfiles.lst @$(ObjDir)\libfiles.lst $(LogCmd)
!endif
    $(LINK) $(LFLAGS) $(DLLFLAGS) $(linkflags) @$(ObjDir)\objfiles.lst @$(ObjDir)\libfiles.lst $(LogCmd)
!if "$(LOG)"=="YES"
    @echo xcopy $(@R).lib $(LibDir) $(LogCmd)
!endif
    -xcopy $(@R).lib $(LibDir)\ $(LogCmd)

# BINs
{$(ObjDir)\}.obj{$(ObjDir)\}.bin:
    @echo $(LinkLibs) > $(ObjDir)\libfiles.lst
!if "$(LOG)"=="YES"
    @echo $(LINK) $(LFLAGS) $(linkflags) $** @$(ObjDir)\libfiles.lst $(LogCmd)
!endif
    $(LINK) $(LFLAGS) $(linkflags) $** @$(ObjDir)\libfiles.lst $(LogCmd)

# EXEs
{$(ObjDir)\}.obj{$(ObjDir)\}.exe:
    @echo $** > $(ObjDir)\objfiles.lst
    @echo $(LinkLibs) > $(ObjDir)\libfiles.lst
!if "$(LOG)"=="YES"
    @echo $(LINK) $(LFLAGS) $(linkflags) @$(ObjDir)\objfiles.lst @$(ObjDir)\libfiles.lst $(LogCmd)
!endif
    $(LINK) $(LFLAGS) $(linkflags) @$(ObjDir)\objfiles.lst @$(ObjDir)\libfiles.lst $(LogCmd)

# Helpfiles
.hpj{$(ObjDir)\}.hlp:
    $(MkDest)
!if "$(LOG)"=="YES"
    @echo  $(HC) $(HFLAGS) $(@B).Hpj
!endif
    $(HC) $(HFLAGS) $(@B).Hpj
!if "$(LOG)"=="YES"
    @echo   xcopy $(@F) $(ObjDir)
!endif
    -xcopy $(@F) $(ObjDir) $(LogCmd)

#*********************************************
#
# Make Targets
#
#*********************************************

#---------------------------------------------
# List Output Files
#---------------------------------------------
ListDir:
    dir $(ObjDir)

#---------------------------------------------
# Display Output Listing File
#---------------------------------------------
!ifndef ERRVIEW
ERRVIEW=start notepad.exe
!endif

ListOut:
    $(ERRVIEW) $(ObjDir)\$(Proj).out

#---------------------------------------------
# Delete Output Listing File
#---------------------------------------------
DelOut:
    del $(ObjDir)\$(Proj).out

#---------------------------------------------
# Clean Output Directories
#---------------------------------------------
clean:
 $(MkDest)
!if "$(OS)" == "Windows_NT"
 del /q $(ObjDir)\*.obj \
        $(ObjDir)\*.out \
        $(ObjDir)\*.h   \
        $(ObjDir)\*.dbg \
        $(ObjDir)\*.lib \
        $(ObjDir)\*.exe \
        $(ObjDir)\*.dll \
        $(ObjDir)\*.map \
        $(ObjDir)\*.res \
        $(ObjDir)\*.rc  \
        $(ObjDir)\*.bin \
        $(ObjDir)\*.lst \
        $(ObjDir)\*.blt \
        $(ObjDir)\*.hlp \
        $(ObjDir)\*.srl \
        $(ObjDir)\*.exp >NUL 2>NUL
!else  # Win95 doesn't support "2>" on command line, multiple files on a Del command, or /q
 erase  $(ObjDir)\*.obj >NUL
 erase  $(ObjDir)\*.out >NUL
 erase  $(ObjDir)\*.h   >NUL
 erase  $(ObjDir)\*.dbg >NUL
 erase  $(ObjDir)\*.lib >NUL
 erase  $(ObjDir)\*.exe >NUL
 erase  $(ObjDir)\*.dll >NUL
 erase  $(ObjDir)\*.map >NUL
 erase  $(ObjDir)\*.res >NUL
 erase  $(ObjDir)\*.rc  >NUL
 erase  $(ObjDir)\*.bin >NUL
 erase  $(ObjDir)\*.lst >NUL
 erase  $(ObjDir)\*.blt >NUL
 erase  $(ObjDir)\*.hlp >NUL
 erase  $(ObjDir)\*.srl >NUL
 erase  $(ObjDir)\*.exp >NUL
!endif  # OS == Windows_NT
!endif      # BASEMAKE_INCLUDED
