#=------------------------------------------------------------------------=
# vb5ctls.inc
#=------------------------------------------------------------------------=
# builds a control for the vb5 product.  adds a few pieces of functionality
# to the generic makectl.inc


#=------------------------------------------------------------------------=
# NOTE:
#
# variable definitions before the !include line, and new targets, etc,
# afterwards.
#
#=------------------------------------------------------------------------=


#=------------------------------------------------------------------------=
# variable definitions
#
!if "$(_SERVERFILENAME)"==""
_SERVERFILENAME=$(CONTROLNAME).Ocx
!endif

# Relative path to the INTL, satellite DLL build, directory
#
INTLPATH=.\.
VBLICPATH=..\..\VBLIC



IDHEADER=..\..\tools\idheader.bat

!if "$(INTLBLD)"==""
ALLTARGETS=Helpstrs.H $(_SERVERFILENAME)  \
!if "$(ASDEBUG)"=="" && "$(ASICECAP)"==""
           Lego
!endif
!else
ALLTARGETS=$(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL \
!endif

TLBTARGETS=HelpStrs.H ..\$(CONTROLNAME).ODL

# licensing support
#
!if "$(ASDEBUG)"!=""
_LIBS=$(_LIBS) $(VBLICPATH)\debug\vblic.lib 
!elseif "$(ASICECAP)"!=""
_LIBS=$(_LIBS) $(VBLICPATH)\icecap\vblic.lib 
!else
_LIBS=$(_LIBS) $(VBLICPATH)\release\vblic.lib 
!endif

#=------------------------------------------------------------------------=
# extra compiler flags, etc.
#
!if "$(ASDEBUG)"!=""
#
# debug
#
_LFLAGS=$(_LFLAGS) -map:$(_SERVERBASENAME).map

!else if "$(ASICECAP)"!=""
#
# icecap
#
_LFLAGS=$(_LFLAGS) -map:$(_SERVERBASENAME).map

!else
#
# release
#
_LFLAGS=$(_LFLAGS) -debugtype:fixup,cv -debug:notmapped,full -pdb:none -map:$(_SERVERBASENAME).map
!endif

#=------------------------------------------------------------------------=
# put all variable definitions before this, and new targets afterwards
#
!include "..\..\Include\MakeCtl.Inc"


#=------------------------------------------------------------------------=
# new targets
#

VBDep: HelpStrs.H dep

# helpstr/id support
#
HelpStrs.H : ..\$(CONTROLNAME).ID
    @echo Generating HelpIDs.H, HelpStrs.H and HelpStrs.RC
    @$(IDHEADER) ..\$(CONTROLNAME).id helpids.h helpstrs.h helpstrs.rc > nul

!if "$(_SERVERBASENAME)"==""
!message _SERVERBASENAME not set
!endif
!if "$(_SERVEREXTENSION)"==""
!message _SERVEREXTENSION not set
!endif
!if "$(_LOCALEBASENAME)"==""
!message _LOCALEBASENAME not set
!endif

# Localized DLL build
#
$(INTLPATH)\HelpStrs.RC : ..\$(CONTROLNAME).ID
		@echo Generating HelpStrs.RC
		@$(IDHEADER) ..\$(CONTROLNAME).id $(INTLPATH)\helpids.h $(INTLPATH)\helpstrs.h $(INTLPATH)\helpstrs.rc > nul

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

$(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL : $(INTLPATH)\helpstrs.rc $(INTLPATH)\intl.obj $(INTLPATH)\intl.rbj 
        @echo Linking satellite DLL ...
        @link -nologo -out:$(INTLPATH)\$(_LOCALEBASENAME)xxx.DLL -DLL -subsystem:windows,4.00 -nodefaultlib -machine:$(PROCESSOR_ARCHITECTURE) -entry:DllMain $(INTLPATH)\intl.obj $(INTLPATH)\intl.rbj

Lego:
!if "$(CTLS_LEGO)"=="YES"
  nmake -f $(THUNDER)\$(TOOLS)\$(LEGO)\instr.mak FILE_BASE=$(_SERVERBASENAME) FILE_EXTENSION=$(_SERVEREXTENSION) CMD_SCRIPT= BOOT_SYM=
!endif
