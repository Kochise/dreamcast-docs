#=------------------------------------------------------------------------=
# MakeCBC.Inc
#=------------------------------------------------------------------------=
# Copyright  1995  Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=
#
# builds a custom base class.  Assumes existence of $(DESIGNERNAME), and $(OBJS)
#

#
# targets
#
VERSIONHDR=dwinvers.h


#
# support for naming your DLL something other than DESIGNERNAME
#
!if "$(_SERVERFILENAME)"==""
_SERVERFILENAME=$(DESIGNERNAME).DLL
!endif
!if "$(_RUNMODESERVERNAME)"==""
_RUNMODESERVERNAME=$(RUNMODE).DLL
!endif

# Tools
#
!include "Tools.Inc"
SRCDIR=..
FXDIR=..\..\FrameWrk
INTLPATH=.\.

# build specific flags
#
!if "$(ASDEBUG)"!=""
#
# debug
#
LIBS=$(FXDIR)\Debug\CtlFwD32.Lib
CFLAGS=-Zil -DDEBUG -Od -FI..\..\include\vc41warn.h
LINKFLAGS=-debugtype:fixup,cv -debug:notmapped,full -pdb:none
RCFLAGS=-dDEBUG

!else if "$(ASICECAP)"!=""
#
# ICECap
#
LIBS=$(FXDIR)\IceCap\CtlFwI32.Lib ICap.Lib msvcrt.lib
CFLAGS=-Gh -Zil -Owxsb1 -DICECAP -FI..\..\include\vc41warn.h
LINKFLAGS=-debug:mapped

!else
#
# Release
#
LIBS=$(FXDIR)\Release\CtlFwR32.Lib
CFLAGS=-Zil -Owxsb1 -FI..\..\include\vc41warn.h
LINKFLAGS=-debugtype:fixup,cv -debug:notmapped,full -pdb:none
!endif

#
# default flags
#
MLFLAGS=-c -coff -I$(SRCDIR) -I..\..\Include -nologo
RCFLAGS=-r -i$(SRCDIR) $(RCFLAGS) $(_RCFLAGS) -I..\..\Include -i.

# UNDONE: marcwan,  1.96 -- find a better way to integrate ocx96.lib
#
LIBS= $(LIBS) $(_LIBS) olepro32.lib kernel32.lib user32.lib ole32.lib uuid.lib advapi32.lib oldnames.lib uuid2.lib oleaut32.lib comdlg32.lib gdi32.lib ..\..\lib\$(PROCESSOR_ARCHITECTURE)\ocx96.lib
!ifdef RISC_BLD
LFLAGS=$(LINKFLAGS) $(_LFLAGS) -nologo -DLL -subsystem:windows,4.00 -nodefaultlib -machine:$(PROCESSOR_ARCHITECTURE)
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -Gd -Gs -Gy -W3 -WX -Oi $(CFLAGS) $(_CFLAGS) -Tp
!else
LFLAGS=$(LINKFLAGS) $(_LFLAGS) -nologo -DLL -subsystem:windows,4.00 -nodefaultlib -machine:i386
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -QIfdiv- -Gd -Gs -Gy -W3 -WX -Oi $(CFLAGS) $(_CFLAGS) -Tp
!endif

DSGNLFLAGS=-out:$(_SERVERFILENAME) $(LFLAGS) -def:$(SRCDIR)\$(DESIGNERNAME).def
DSGNLIBS=$(LIBS) $(_DSGNLIBS)
RUNLFLAGS=-out:$(_RUNMODESERVERNAME) $(LFLAGS) -def:$(SRCDIR)\$(RUNMODE).DEF
RUNLIBS=$(LIBS) $(_RUNLIBS)

#=--------------------------------------------------------------------------=
# build the designer, and, if appropriate, the run-mode DLL
#
all: \
!if "$(INTLBLD)"==""
!if "$(RUNMODEDLL)"=="YES"
     $(_RUNMODESERVERNAME) \
!endif
     $(_SERVERFILENAME) \
!if "$(ASDEBUG)"=="" && "$(ASICECAP)"==""
	   Lego
!endif
!else
    $(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL
!endif


$(_SERVERFILENAME): $(VERSIONHDR) $(DESIGNERNAME).TLB $(OBJS) $(SRCDIR)\Makefile
    $(LINK) $(OBJS) $(DSGNLIBS) $(DSGNLFLAGS)

$(_RUNMODESERVERNAME): $(VERSIONHDR) \
!if "$(RUNMODETLB)"=="YES"
		$(RUNMODE).TLB \
!endif
		$(RUNOBJS)
    $(LINK) $(RUNOBJS) $(RUNLFLAGS) $(RUNLIBS)

{$(SRCDIR)}.cpp.obj:
    @$(CC) $(CFLAGS) $<

{$(SRCDIR)}.c.obj:
    @$(CC) $(CFLAGS) $<

{$(SRCDIR)}.asm.Obj:
    @$(ML) $(MLFLAGS) $<

# TODO: you should come up with some mechanism to generate this file
#       on your own.
#
$(VERSIONHDR) : ..\..\FrameWrk\dwinvers.h
    @echo Generating Version Information Header File (dwinvers.h)
    @copy ..\..\FrameWrk\dwinvers.h >nul

$(DESIGNERNAME).TLB : $(SRCDIR)\$(DESIGNERNAME).ODL
    @echo Generating $(DESIGNERNAME).TLB and $(DESIGNERNAME)Interfaces.H
    @$(MKTYPLIB) $(_MKTYPLIBFLAGS) -nologo -cpp_opt "/C /E /D__MKTYPLIB__ -nologo" -h $(DESIGNERNAME)Interfaces.H -o Errors.LOG -tlb $(DESIGNERNAME).TLB $(SRCDIR)\$(DESIGNERNAME).ODL

$(RUNMODE).TLB : $(SRCDIR)\$(RUNMODE).ODL
    @echo Generating $(RUNMODE).TLB and $(RUNMODE)Interfaces.H
    @$(MKTYPLIB) $(_MKTYPLIBFLAGS) -nologo -cpp_opt "/C /E /D__MKTYPLIB__ -nologo" -h $(RUNMODE)Interfaces.H -o Errors.LOG -tlb $(RUNMODE).TLB $(SRCDIR)\$(RUNMODE).ODL

$(DESIGNERNAME).Rbj : $(DESIGNERNAME).TLB $(SRCDIR)\$(DESIGNERNAME).RC
    @echo Compiling $(DESIGNERNAME).RC
    @$(RC) $(RCFLAGS) -fo $(DESIGNERNAME).Res $(SRCDIR)\$(DESIGNERNAME).Rc
!ifdef RISC_BLD
    @cvtres -machine:$(PROCESSOR_ARCHITECTURE) -nologo -out:$(DESIGNERNAME).Rbj $(DESIGNERNAME).Res
!else
    @cvtres -machine:ix86 -nologo -out:$(DESIGNERNAME).Rbj $(DESIGNERNAME).Res
!endif

$(RUNMODE).Rbj : \
!if "$(RUNMODETLB)"=="YES"
		$(RUNMODE).TLB \
!endif
		$(SRCDIR)\$(RUNMODE).RC
    @echo Compiling $(RUNMODE).RC
    @$(RC) $(RCFLAGS) -fo $(RUNMODE).Res $(SRCDIR)\$(RUNMODE).Rc
!ifdef RISC_BLD
    @cvtres -machine:$(PROCESSOR_ARCHITECTURE) -nologo -out:$(RUNMODE).Rbj $(RUNMODE).Res
!else
    @cvtres -machine:ix86 -nologo -out:$(RUNMODE).Rbj $(RUNMODE).Res
!endif

# Localized DLL build
#
$(INTLPATH)\intl.obj : $(INTLPATH)\intl.cpp
	@echo Compiling satellite DLL  ...
	@cl -nologo /c /Zl /DINTLBUILD $(INTLPATH)\intl.cpp /Fo$(INTLPATH)\intl.obj

$(INTLPATH)\intl.res : $(INTLPATH)\intl.rc
	@echo Compiling satellite DLL resources ...
	@rc -dINTLBUILD -i..\. -i\. -i..\..\framewrk\. -i..\..\include\. $(_RCFLAGS) -fo $(INTLPATH)\intl.res $(INTLPATH)\intl.rc

$(INTLPATH)\intl.rbj : $(INTLPATH)\intl.res
!ifdef RISC_BLD 
	@cvtres -machine:$(PROCESSOR_ARCHITECTURE) -nologo -out:$(INTLPATH)\intl.rbj $(INTLPATH)\intl.res
!else
	@cvtres -machine:ix86 -nologo -out:$(INTLPATH)\intl.rbj $(INTLPATH)\intl.res
!endif

$(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL : $(INTLPATH)\intl.obj $(INTLPATH)\intl.rbj
	@echo Linking satellite DLL ...
	@link -nologo -out:$(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL -DLL -subsystem:windows,4.00 -nodefaultlib -machine:$(PROCESSOR_ARCHITECTURE) -entry:DllMain $(INTLPATH)\intl.obj $(INTLPATH)\intl.rbj


!if "$(_SERVERBASENAME)"==""
!message _SERVERBASENAME not set
!endif
!if "$(_SERVEREXTENSION)"==""
!message _SERVEREXTENSION not set
!endif
!if "$(_RUNMODEBASENAME)"==""
!message _RUNMODEBASENAME not set
!endif
!if "$(_RUNMODEEXTENSION)"==""
!message _RUNMODEEXTENSION not set
!endif

!if "$(INTLBLD)"!=""
!if "$(_LOCALEBASENAME)"==""
!message _LOCALEBASENAME not set
!endif
!endif

Lego:
!if "$(CTLS_LEGO)"=="YES"
  nmake -f $(THUNDER)\$(TOOLS)\$(LEGO)\instr.mak FILE_BASE=$(_SERVERBASENAME) FILE_EXTENSION=$(_SERVEREXTENSION) CMD_SCRIPT= BOOT_SYM=
  nmake -f $(THUNDER)\$(TOOLS)\$(LEGO)\instr.mak FILE_BASE=$(_RUNMODEBASENAME) FILE_EXTENSION=$(_RUNMODEEXTENSION) CMD_SCRIPT= BOOT_SYM=
!endif

Clean:
	del *.obj
	del *.dll
	del *.pdb
	del *.vcp

Dep: \
!if "$(RUNMODETLB)"=="YES"
     $(RUNMODE).TLB \
!endif     
     $(DESIGNERNAME).TLB
    @echo Generating Dependancies
    @$(MKDEP) -n -P ./ -I. -I$(SRCDIR) -I..\..\Include -s .obj $(SRCDIR)\*.c* > dep.mak

#=----------------------------=
# Include Dependency Makefile 
#
!IF EXIST(dep.mak)
!include dep.mak
!ENDIF
