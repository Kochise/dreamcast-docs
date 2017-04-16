#=------------------------------------------------------------------------=
# MakeAuto.Inc
#=------------------------------------------------------------------------=
# Copyright  1995  Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=
#
# builds an automation server.  Assumes existence of $(SERVERNAME) and $(OBJS)
#

#
# targets
#
VERSIONHDR=dwinvers.h

!if "$(_SERVERFILENAME)"==""
_SERVERFILENAME=$(SERVERNAME).DLL
!endif

!if "$(_LOCALEBASENAME)"==""
!message _LOCALEBASENAME not set
!endif

# Special for msrdo20 build - allows output of ODL.H (or some other alternate)
!if "$(ALTERNATEODLHFILE)"==""
_ALTERNATEODLHFILE=-h $(SERVERNAME)Interfaces.H
!else
_ALTERNATEODLHFILE=$(ALTERNATEODLHFILE)
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
# Special for msrdo20 build - this is a non-mfc server NOT built in the framework
#
!if "$(NONFRAMEWRKMAKE)"==""
LIBS=$(FXDIR)\Debug\CtlFwD32.Lib
!endif
CFLAGS=-Zil -DDEBUG -Od -FI..\..\include\vc41warn.h
LFLAGS=-debugtype:fixup,cv -debug:notmapped,full -pdb:none
RCFLAGS=-dDEBUG

!else if "$(ASICECAP)"!=""
#
# ICECap
#
# Special for msrdo20 build - this is a non-mfc server NOT built in the framework
!if "$(NONFRAMEWRKMAKE)"==""
LIBS=$(FXDIR)\IceCap\CtlFwI32.Lib ICap.Lib msvcrt.lib
!endif
CFLAGS=-Gh -Zil -Owxsb1 -DICECAP -FI..\..\include\vc41warn.h
LFLAGS=-debug:mapped

!else
#
# Release
#
# Special for msrdo20 build - this is a non-mfc server NOT built in the framework
!if "$(NONFRAMEWRKMAKE)"==""
LIBS=$(FXDIR)\Release\CtlFwR32.Lib
!endif
CFLAGS=-Zil -Owxsb1 -FI..\..\include\vc41warn.h
LFLAGS=
!endif

#
# default flags
#
RCFLAGS=-r -i$(SRCDIR) $(RCFLAGS) $(_RCFLAGS) -I..\..\Include -i.
LIBS= $(LIBS) $(_LIBS) kernel32.lib user32.lib ole32.lib uuid.lib advapi32.lib oldnames.lib uuid2.lib oleaut32.lib comdlg32.lib gdi32.lib
!ifdef RISC_BLD
LFLAGS=$(LFLAGS) $(_LFLAGS) -nologo -out:$(_SERVERFILENAME) -DLL -subsystem:windows,4.00 -nodefaultlib -machine:$(PROCESSOR_ARCHITECTURE) -def:$(SRCDIR)\$(SERVERNAME).def
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -Gd -Gs -Gy -W3 -WX -Oi $(CFLAGS) $(_CFLAGS) -Tp
!else
LFLAGS=$(LFLAGS) $(_LFLAGS) -nologo -out:$(_SERVERFILENAME) -DLL -subsystem:windows,4.00 -nodefaultlib -machine:i386 -def:$(SRCDIR)\$(SERVERNAME).def
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -QIfdiv- -Gd -Gs -Gy -W3 -WX -Oi $(CFLAGS) $(_CFLAGS) -Tp
!endif


all: \
!if "$(INTLBLD)"==""
	$(MORETARGETS) $(SERVERNAME).Dll $(POSTTARGETS)
!else
	$(INTLPATH)\$(_LOCALEBASENAME)xxx.Dll
!endif

$(SERVERNAME).Dll: $(VERSIONHDR) $(SERVERNAME).TLB $(OBJS) $(SRCDIR)\Makefile
    $(LINK) $(OBJS) $(LIBS) $(LFLAGS)


{$(SRCDIR)}.cpp.obj:
    @$(CC) $(CFLAGS) $<

{$(SRCDIR)}.c.obj:
    @$(CC) $(CFLAGS) $<

# TODO: you should come up with some mechanism to generate this file
#       on your own.
#
$(VERSIONHDR) : ..\..\FrameWrk\dwinvers.h
    @echo Generating Version Information Header File (dwinvers.h)
    @copy ..\..\FrameWrk\dwinvers.h >nul

$(SERVERNAME).TLB : $(SRCDIR)\$(SERVERNAME).ODL
    @echo Generating $(SERVERNAME).TLB and $(_ALTERNATEODLHFILE)
    @$(MKTYPLIB) $(_MKTYPLIBFLAGS) -nologo -cpp_opt "/C /E /D__MKTYPLIB__ -nologo $(_MTLPREPROCFLAGS)" $(_ALTERNATEODLHFILE) -o Errors.LOG -tlb $(SERVERNAME).TLB $(SRCDIR)\$(SERVERNAME).ODL

$(SERVERNAME).Rbj : $(SERVERNAME).TLB $(SRCDIR)\$(SERVERNAME).RC
    @echo Compiling $(SERVERNAME).RC
    @$(RC) $(RCFLAGS) -fo $(SERVERNAME).Res $(SRCDIR)\$(SERVERNAME).Rc
!ifdef RISC_BLD
    @cvtres -machine:$(PROCESSOR_ARCHITECTURE) -nologo -out:$(SERVERNAME).Rbj $(SERVERNAME).Res
!else
    @cvtres -machine:ix86 -nologo -out:$(SERVERNAME).Rbj $(SERVERNAME).Res
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

Clean:
	del *.obj
	del *.dll
	del *.pdb
	del *.vcp

Dep: $(MORETARGETS) $(SERVERNAME).TLB
    @echo Generating Dependancies
    @$(MKDEP) -n -P ./ -I. -I$(SRCDIR) -I..\..\Include -s .obj $(SRCDIR)\*.c* > dep.mak

#=----------------------------=
# Include Dependency Makefile 
#
!IF EXIST(dep.mak)
!include dep.mak
!ENDIF
