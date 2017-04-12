# Makefile for use with MSI to build custom actions, tests or tools.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
# EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
#
# Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.
#
# Must define the following (unless optional or default is indicated) using one of:
#   1. command line to nmake.exe (syntax: MACRO=value) (highest precedence)
#   2. in outer makefile that !include this (typically a header section in .CPP file)
#   3. environment variable
#
#  MODULENAME=   base name of .cpp file to build .exe or .dll with same base name
#  SUBSYSTEM=    "console" or "windows" for EXE, do not define if DLL unless "RESOURCE"
#  UNICODE=1  to compile Unicode executables (default is ANSI)
#  ENTRY=     entrypoints (comma separated) for DLL or non-standard entry point for EXE
#  VERSION=  "SHIP" or "DEBUG" or "CVPACK" or "NOBSC"(no browser files, the default)

# Options to generate a version resource (recommended)
#
#  FILEVERSION=  specify MM.mm to generate version resource (=MSI to track MSI version)
#  PRODUCTVERSION=  product version for resource, defaults to FILEVERSION
#  DESCRIPTION=  description for use in version resource (if FILEVERSION defined)
#  COMPANYNAME=  company name to use in version resource (if FILEVERSION defined)

# Build options that will generally need to be set
#
#  INCLUDE=   include path for compiler, should include MSI.H, MSIQUERY.H (unless MSIPROJ set)
#  LIB=       lib path for use by linker, should include MSI.LIB (unless MSIPROJ set)

# Options that may be used in special cases, not needed for simple builds
#
#  ADDCPP=    optional comma-separated list of additional CPP files to compile
#  DEPEND=    optional list of additional make dependents, normally include files
#  LINKLIBS=  additional libraries to link, standard libraries are:
#             kernel32.lib user32.lib advapi32.lib libc.lib version.lib gdi32.lib
#  BUILDDIR=  to override default: SHIP|DEBUG|CVPACK under current dir (unless MSIPROJ set)
#  MSILIB=    full path to MSI import lib, defaults to MSI.LIB using lib path search rules
#  VCBIN=     directory of all MSVC executables, else uses MSDevDir & MSVCDir, else PATH
# Note: For VC5 use, if MSDevDir is defined, then MSVCDir must also be defined (VCVARS32.BAT)

#-----------------------------------------------------------------------------
# directory resolution
#-----------------------------------------------------------------------------

!ifndef MODULENAME
!error Must define MODULENAME to base name of .cpp file
!endif

!ifndef MODULESRC
MODULESRC = .
!endif

!ifndef VERSION
VERSION = NOBSC
!endif
!if "$(VERSION)"=="SHIP"
_subdir_ = SHIP
!else if "$(VERSION)"=="DEBUG" || "$(VERSION)"=="NOBSC"
_subdir_ = DEBUG
!else if "$(VERSION)"=="CVPACK"
_subdir_ = CVPACK
!else
!error Must define VERSION to SHIP or CVPACK, or DEBUG or NOBSC(default)
!endif

!ifdef MSIPROJ
BUILDDIR   = $(MSIPROJ)\build\$(_subdir_)
COMMONDIR  = $(MSIPROJ)\build\common
MSICPP     = -I$(COMMONDIR)
!else
!ifndef BUILDDIR
BUILDDIR   = $(MODULESRC)\$(_subdir_)
!endif
!endif

OBJDIR = $(BUILDDIR)\OBJECT

#-----------------------------------------------------------------------------
# build model processing
#-----------------------------------------------------------------------------

!ifdef PROCESSOR_ARCHITECTURE
PLATFORM = $(PROCESSOR_ARCHITECTURE)
!else
PLATFORM = x86
!endif
!if "$(PLATFORM)" == "x86" || "$(PLATFORM)" == "X86"
_machine_ = /MACHINE:IX86
!else if "$(PLATFORM)" == "alpha" || "$(PLATFORM)" == "ALPHA"
_machine_ = /MACHINE:ALPHA
!else
!error Must define PLATFORM to x86 or ALPHA
!endif

ALIGN = -align:0x1000

_objects_ = $(OBJDIR)\$(MODULENAME).obj
!ifdef SUBSYSTEM
!if defined(ENTRY)
ENTRY = /ENTRY:$(ENTRY)
!else if "$(SUBSYSTEM)" == "console" || "$(SUBSYSTEM)" == "CONSOLE"
!ifdef UNICODE
ENTRY = /ENTRY:wmainCRTStartup
!else
ENTRY = /ENTRY:mainCRTStartup
!endif
!endif
!if "$(SUBSYSTEM)" == "resource" || "$(SUBSYSTEM)" == "RESOURCE"
SUBSYSTEM = /DLL
TARGET = $(MODULENAME).dll
_objects_ =
ALIGN = -align:0x1000
ENTRY = /NOENTRY $(_machine_)
!else if "$(SUBSYSTEM)" == "windows" || "$(SUBSYSTEM)" == "WINDOWS"
SUBSYSTEM = /SUBSYSTEM:$(SUBSYSTEM),4.0
TARGET = $(MODULENAME).exe
EXCEPTIONS = -GX
!ifdef UNICODE
ENTRY = /ENTRY:wWinMainCRTStartup
!else
ENTRY = /ENTRY:WinMainCRTStartup
!endif
!else
SUBSYSTEM = /SUBSYSTEM:$(SUBSYSTEM),4.0
TARGET = $(MODULENAME).exe
EXCEPTIONS = -GX
!endif
!else # DLL
!if defined(AUTOMATION) && "$(AUTOMATION)" != "NOEXCEPTIONS"
EXCEPTIONS = -GX
!else
EXCEPTIONS = # exceptions not supported in DLL at this time
!endif
SUBSYSTEM = /DLL
TARGET = $(MODULENAME).dll
!if defined(ENTRY)
ENTRY = /EXPORT:$(ENTRY:,= /EXPORT:)
!endif
!if defined(AUTOMATION)
ENTRY = $(ENTRY) /EXPORT:DllGetClassObject /EXPORT:DllCanUnloadNow /EXPORT:DllRegisterServer /EXPORT:DllUnregisterServer
!endif
!endif # SUBSYTEM | DLL

!if !defined(MSILIB) && "$(_objects_)" != ""
!ifdef MSIPROJ
MSILIB     = $(BUILDDIR)\Msi.lib  # should be COMMONDIR?
!else
MSILIB     = Msi.lib
!endif
!endif

#-----------------------------------------------------------------------------
# default build target object dependencies
#-----------------------------------------------------------------------------

all: $(BUILDDIR)\$(TARGET)

!if defined(ADDCPP) && [echo _objects_=$(_objects_) $(OBJDIR)\$(ADDCPP:,=.obj $(OBJDIR^)\).obj > $(OBJDIR)\obj.tmp] == 0
!include $(OBJDIR)\obj.tmp
!endif

#-----------------------------------------------------------------------------
# tools
#-----------------------------------------------------------------------------

!ifdef VCBIN
_vcbin_ = $(VCBIN)\#
_msdevbin_ = $(VCBIN)\#
!else # VCBIN not defined
!ifdef MSVCDIR # VC5
_vcbin_ = $(MSVCDIR)\bin\#
!endif
!ifdef MSDEVDIR # VC vars set
_msdevbin_ = $(MSDEVDIR)\bin\#
!ifndef MSVCDIR # VC 4.x
_vcbin_ = $(MSDEVDIR)\bin\#
!endif
!endif
!endif

CC      = "$(_vcbin_)cl"
RC      = "$(_msdevbin_)rc"
LINK    = "$(_vcbin_)link"
BSCMAKE = "$(_vcbin_)bscmake"
MKTYPLIB= "$(_vcbin_)mktyplib" /cpp_cmd $(_vcbin_)cl

#-----------------------------------------------------------------------------
# flags
#-----------------------------------------------------------------------------

DFLAGS = -DWIN -D_WIN32 -DWIN32

cppflags = -c -W3 -WX -DSTRICT -nologo -J -Gf $(EXCEPTIONS) $(DFLAGS) 
linkcommon = /NODEFAULTLIB /MAP $(ALIGN)
linkexe = $(lflags)
linkdll = $(lflags) -entry:_DllMainCRTStartup@12 -dll
linkDEBUG = -debug:full -debugtype:cv
linkCVPACK = -debug:full -debugtype:both,fixup /opt:ref

!ifdef UNICODE
cppflags = $(cppflags) -DUNICODE -D_UNICODE
!endif

!if "$(VERSION)"=="DEBUG"
#cppflags= $(cppflags) /Fd$(@D)\msitool.pdb -Zi -DDEBUG /Fr$(@R).sbr -Ob1
#cppflags= $(cppflags) /Fd$(@D)\msitool.pdb -Zi -DDEBUG /Fr$(@R).sbr -Ox
cppflags = $(cppflags) /Fd$(@D)\msitool.pdb -Zi -DDEBUG /Fr$(@R).sbr
linkflags = $(linkcommon) $(linkDEBUG)
!else if "$(VERSION)"=="NOBSC"
cppflags = $(cppflags) /Fd$(@D)\msitool.pdb -Zi -DDEBUG
linkflags = $(linkcommon) $(linkDEBUG)
!else if "$(VERSION)"=="SHIP"
cppflags = $(cppflags) -Ox -Gy
linkflags = $(linkcommon)
!else
cppflags= $(cppflags) -DCVPACK
linkflags = $(linkcommon) $(linkCVPACK)
!endif
!ifdef LINKBASE
linkflags = $(linkflags) /BASE:$(LINKBASE)
!endif

rcflags  = -r -d_RC32 $(DFLAGS) -i $(OBJDIR)
!if "$(VERSION)"=="DEBUG" || "$(VERSION)"=="NOBSC" 
rcflags = $(rcflags) -DDEBUG
!endif

impflags = -nologo
bscflags = -nologo -n

#-----------------------------------------------------------------------------

!if "$(_objects_)" != ""
LIBS =  kernel32.lib user32.lib advapi32.lib libc.lib version.lib gdi32.lib
!endif
!ifdef AUTOMATION
_typelib_ = $(OBJDIR)\$(MODULENAME).tlb
!endif

#-----------------------------------------------------------------------------
# MSI header file dependencies
#-----------------------------------------------------------------------------

!if "$(FILEVERSION)"=="Msi" || "$(FILEVERSION)"=="msi"
FILEVERSION = MSI
!endif
!if "$(PRODUCTVERSION)"=="Msi" || "$(PRODUCTVERSION)"=="msi"
PRODUCTVERSION = MSI
!endif
!ifdef MSIPROJ
_depend_ = $(DEPEND:,= ) $(COMMONDIR)\msiquery.h
!if "$(FILEVERSION)"=="MSI" || "$(PRODUCTVERSION)"=="MSI"
_depend_ = $(_depend_) $(OBJDIR)\verdate.h
!endif
!else
_depend_ = $(DEPEND:,= )
!endif

#-----------------------------------------------------------------------------
# version resource generation
#-----------------------------------------------------------------------------

!if defined(FILEVERSION) && (defined(MSIPROJ) || !("$(FILEVERSION)"=="MSI" || "$(PRODUCTVERSION)"=="MSI"))
!ifndef PRODUCTVERSION
PRODUCTVERSION = $(FILEVERSION)
!endif
!ifndef COMPANYNAME
COMPANYNAME = Microsoft Corporation
!endif
$(OBJDIR)\$(MODULENAME).res : $(MODULESRC)\$(MODULENAME).cpp $(MAKEFILE) $(_typelib_)
	$(RC) $(rcflags) -Fo$(OBJDIR)\$(MODULENAME).res <<$(OBJDIR)\$(MODULENAME).rc
#include "$(MODULESRC)\$(MODULENAME).cpp"
!if "$(FILEVERSION)"=="MSI" || "$(PRODUCTVERSION)"=="MSI"
#include "$(OBJDIR)\verdate.h"
!endif
VS_VERSION_INFO VERSIONINFO
!if "$(FILEVERSION)"=="MSI"
FILEVERSION    nVersionMajor,nVersionMinor,0,nVersionBuild
!else
FILEVERSION    $(FILEVERSION:.=,)
!endif
!if "$(PRODUCTVERSION)"=="MSI"
PRODUCTVERSION    nVersionMajor,nVersionMinor,0,nVersionBuild
!else
PRODUCTVERSION $(PRODUCTVERSION:.=,)
!endif
FILEFLAGSMASK VS_FFI_FILEFLAGSMASK
!if "$(VERSION)"=="DEBUG" || "$(VERSION)"=="NOBSC"
FILEFLAGS VS_FF_DEBUG
!else
FILEFLAGS 0L
!endif
FILEOS VOS__WINDOWS32
!if "$(SUBSYSTEM)"=="/DLL"
FILETYPE VFT_DLL
!else
FILETYPE VFT_APP
!endif
FILESUBTYPE 0L
{
  BLOCK "StringFileInfo"
  {
    BLOCK "040904E4"
    {
      VALUE "CompanyName",     "$(COMPANYNAME)\0"
      VALUE "FileDescription", "$(DESCRIPTION)\0"
!if "$(FILEVERSION)"=="MSI"
      VALUE "FileVersion",     szVerNum
!else
      VALUE "FileVersion",     "$(FILEVERSION)\0"
!endif
      VALUE "InternalName",    "$(TARGET) $(VERSION)\0"
      VALUE "LegalCopyright",  "Copyright \251 $(COMPANYNAME) 1997\0"
      VALUE "ProductName",     "MSI\0"
!if "$(PRODUCTVERSION)"=="MSI"
      VALUE "ProductVersion",  szVerNum
!else
      VALUE "ProductVersion",  "$(PRODUCTVERSION)\0"
!endif
    }
  }
  BLOCK "VarFileInfo" { VALUE "Translation", 0x409, 0x4E4 }
}
<<KEEP
!else #!defined(FILEVERSION)
$(OBJDIR)\$(MODULENAME).res : $(MODULESRC)\$(MODULENAME).cpp $(_typelib_) $(OBJDIR)
	$(RC) $(rcflags) -Fo$@ $(MODULESRC)\$(MODULENAME).cpp
!endif #defined(FILEVERSON)

#-----------------------------------------------------------------------------
# build rules
#-----------------------------------------------------------------------------

.SUFFIXES : .exe .obj .cpp .res .rc

## can't find path! MAKEFILE = MsiTool.mak  # build targets are dependent upon makefile changes

$(BUILDDIR) : 
	if not exist $(BUILDDIR)\NUL md $(BUILDDIR)

$(OBJDIR) : $(BUILDDIR)
	if not exist $(BUILDDIR)\OBJECT\NUL md $(BUILDDIR)\OBJECT

{$(MODULESRC)}.cpp{$(OBJDIR)}.obj:
	$(CC) $(cppflags) -Fo$*.obj $(MSICPP) $< 

!if "$(_objects_)" != ""
$(_objects_) : $(_depend_) $(OBJDIR)
!endif

!ifdef AUTOMATION
$(OBJDIR)\$(MODULENAME).tlb : $(MODULESRC)\$(MODULENAME).cpp
	$(MKTYPLIB) /w0 $(MODULESRC)\$(MODULENAME).cpp /tlb $(OBJDIR)\$(MODULENAME).tlb
!endif

$(BUILDDIR)\$(TARGET): $(MAKEFILE) $(_objects_) $(OBJDIR)\$(MODULENAME).res
	$(LINK) -out:$@ $(linkflags) $(SUBSYSTEM) $(ENTRY) @<<$(OBJDIR)\$(MODULENAME).lrf
		$(_objects_)
		$(OBJDIR)\$(MODULENAME).res
		$(MSILIB) $(LINKLIBS) $(LIBS)
<<KEEP
!if "$(VERSION)"=="DEBUG" && "$(_objects_)" != ""
	$(BSCMAKE) $(bscflags) -o $(BUILDDIR)\$(*B) $(_objects_:.obj=.sbr)
!endif