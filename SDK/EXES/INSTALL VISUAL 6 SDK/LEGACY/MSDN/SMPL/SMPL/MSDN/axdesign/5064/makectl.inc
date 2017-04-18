#=------------------------------------------------------------------------=
# MakeCtl.Inc
#=------------------------------------------------------------------------=
# Copyright  1995  Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=
#
# builds a control.  Assumes existence of $(CONTROLNAME), and $(OBJS)
#

#
# targets
#
VERSIONHDR=dwinvers.h

#
# support for naming your OCX something other than CONTROLNAME
#
!if "$(_SERVERFILENAME)"==""
_SERVERFILENAME=$(CONTROLNAME).Ocx
!endif

# Tools
#
!include "Tools.Inc"
SRCDIR=..
FXDIR=..\..\FrameWrk


# build specific flags
#
!if "$(ASDEBUG)"!=""
#
# debug
#
LIBS=$(FXDIR)\Debug\CtlFwD32.Lib
CFLAGS=-Zil -DDEBUG -Od -LDd -FI..\..\include\vc41warn.h
LFLAGS=-debugtype:fixup,cv -debug:notmapped,full -pdb:none
RCFLAGS=-dDEBUG
MLFLAGS=-Zi

!else if "$(ASICECAP)"!=""
#
# ICECap
#
LIBS=$(FXDIR)\IceCap\CtlFwI32.Lib ICap.Lib msvcrt.lib
CFLAGS=-Gh -Zil -Owxsb1 -DICECAP -FI..\..\include\vc41warn.h
LFLAGS=-debug:mapped
MLFLAGS=-Zi

!else
#
# Release
#
LIBS=$(FXDIR)\Release\CtlFwR32.Lib
CFLAGS=-Zil -Owxsb1 -FI..\..\include\vc41warn.h
LFLAGS=
MLFLAGS=-Zi
!endif

#
# default flags
#
!if "$(PROCESSOR_ARCHITECTURE)"=="ALPHA"
MLFLAGS=-I$(SRCDIR) -I..\..\Include -nologo $(MLFLAGS)
!elseif "$(PROCESSOR_ARCHITECTURE)"=="MIPS"
MLFLAGS=-c -I$(SRCDIR) -I..\..\Include -nologo $(MLFLAGS)
!elseif "$(PROCESSOR_ARCHITECTURE)"=="PPC"
MLFLAGS=-I$(SRCDIR) -I..\..\Include -nologo $(MLFLAGS)
!else
MLFLAGS=-c -coff -I$(SRCDIR) -I..\..\Include -nologo $(MLFLAGS)
!endif
RCFLAGS=-r -i$(SRCDIR) $(RCFLAGS) $(_RCFLAGS) -I..\..\Include -i.

# UNDONE: marcwan,  1.96 -- find a better way to integrate ocx96.lib
#
LIBS= $(LIBS) $(_LIBS) kernel32.lib user32.lib ole32.lib uuid.lib advapi32.lib oldnames.lib uuid2.lib oleaut32.lib comdlg32.lib gdi32.lib ..\..\lib\$(PROCESSOR_ARCHITECTURE)\ocx96.lib
!ifdef RISC_BLD
LFLAGS=$(LFLAGS) $(_LFLAGS) -nologo -out:$(_SERVERFILENAME) -DLL -subsystem:windows,4.00 -nodefaultlib -machine:$(PROCESSOR_ARCHITECTURE) -def:$(SRCDIR)\$(CONTROLNAME).def
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -Gd -Gs -W3 -WX -Oi -DRISC_BLD $(CFLAGS) $(_CFLAGS) -Tp
!else
LFLAGS=$(LFLAGS) $(_LFLAGS) -nologo -out:$(_SERVERFILENAME) -DLL -subsystem:windows,4.00 -nodefaultlib -machine:i386 -def:$(SRCDIR)\$(CONTROLNAME).def
CFLAGS=-nologo -c -I. -I$(SRCDIR) -I..\..\Include -QIfdiv- -Gd -Gs -Gy -W3 -WX -Oi $(CFLAGS) $(_CFLAGS) -Tp
!endif

# set up our default targets
#
!if "$(ALLTARGETS)"==""
ALLTARGETS=$(_SERVERFILENAME)
!endif

!if "$(TLBTARGETS)"==""
TLBTARGETS=$(SRCDIR)\$(CONTROLNAME).ODL
!endif

#=------------------------------------------------------------------------=
# the good stuff -- the real targets
#
all: $(ALLTARGETS)

$(_SERVERFILENAME): $(VERSIONHDR) $(CONTROLNAME).TLB $(OBJS) $(SRCDIR)\Makefile
    $(LINK) $(OBJS) $(LIBS) $(LFLAGS)

{$(SRCDIR)}.cpp.obj:
    @$(CC) $(CFLAGS) $<

{$(SRCDIR)}.c.obj:
    @$(CC) $(CFLAGS) $<

{$(SRCDIR)}.s.Obj:
!ifdef RISC_BLD
!  if "$(PROCESSOR_ARCHITECTURE)"=="PPC"
    @$(CC) /P /Tc $<
    @$(ML) $*.i
     del $*.i
!  else
    @$(ML) $(MLFLAGS) $< /Fo$@
!  endif
!else
{$(SRCDIR)}.asm.Obj:
    @$(ML) $(MLFLAGS) $<
!endif

# TODO: you should come up with some mechanism to generate this file
#       on your own.
#
$(VERSIONHDR) : ..\..\FrameWrk\dwinvers.h
    @echo Generating Version Information Header File (dwinvers.h)
    @copy ..\..\FrameWrk\dwinvers.h >nul

$(CONTROLNAME).TLB : $(TLBTARGETS)
    @echo Generating $(CONTROLNAME).TLB and $(CONTROLNAME)Interfaces.H
    @$(MKTYPLIB) $(_MKTYPLIBFLAGS) -nologo -cpp_opt "/C /E /D__MKTYPLIB__ -nologo $(_MTLPREPROCFLAGS)" -h $(CONTROLNAME)Interfaces.H -o Errors.LOG -tlb $(CONTROLNAME).TLB $(SRCDIR)\$(CONTROLNAME).ODL

$(CONTROLNAME).Rbj : $(CONTROLNAME).TLB $(SRCDIR)\$(CONTROLNAME).RC
    @echo Compiling $(CONTROLNAME).RC
    @$(RC) $(RCFLAGS) -fo $(CONTROLNAME).Res $(SRCDIR)\$(CONTROLNAME).Rc
!ifdef RISC_BLD
    @cvtres -machine:$(PROCESSOR_ARCHITECTURE) -nologo -out:$(CONTROLNAME).Rbj $(CONTROLNAME).Res
!else
    @cvtres -machine:ix86 -nologo -out:$(CONTROLNAME).Rbj $(CONTROLNAME).Res
!endif

Clean:
	del *.obj
	del *.dll
	del *.pdb
	del *.vcp

Dep: $(CONTROLNAME).TLB
    @echo Generating Dependancies
    @$(MKDEP) -n -P ./ -I. -I$(SRCDIR) -I..\..\Include -s .obj $(SRCDIR)\*.c* > dep.mak

#=----------------------------=
# Include Dependency Makefile 
#
!IF EXIST(dep.mak)
!include dep.mak
!ENDIF
