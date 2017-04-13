!include <win32.mak>

#NODEBUG=1

TARGETNAME=SmbSmpEx
OBJS=$(TARGETNAME).res StdAfx.obj $(TARGETNAME).obj BasePage.obj DDxDDv.obj ExtObj.obj PropList.obj RegExt.obj ResProp.obj

EXTRACFLAGS=/D _WINDOWS /D _WINDLL /D _AFXDLL /D _USRDLL /GX
EXTRALINKFLAGS=-dll
EXTRALIBS=clusapi.lib resutils.lib cluadmex.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib

!IFNDEF NODEBUG
EXTRACFLAGS=$(EXTRACFLAGS) $(cdebug) /D _DEBUG
EXTRALINKFLAGS=$(EXTRALINKFLAGS) $(ldebug)
EXTRALIBS=$(EXTRALIBS) mfcs42ud.lib mfc42ud.lib mfco42ud.lib msvcrtd.lib
!ELSE
EXTRACFLAGS=$(EXTRACFLAGS) /D NDEBUG
EXTRALIBS=$(EXTRALIBS) mfcs42u.lib mfc42u.lib
!ENDIF

!IF "$(CPU)" == "i386"
EXTRALINKFLAGS=$(EXTRALINKFLAGS) /MACHINE:ix86
!ELSEIF "$(CPU)" == "ALPHA"
EXTRALINKFLAGS=$(EXTRALINKFLAGS) /MACHINE:alpha
!ENDIF

.cpp.obj:
    $(cc) $(cflags) $(EXTRACFLAGS) $(cvarsdll) /Fp"$(TARGETNAME).pch" /Yu"stdafx.h" $*.cpp

.h.idl:
    midl . -DMIDL_PASS /header $(TARGETNAME).h /iid $(TARGETNAME)_i.c /tlb $(TARGETNAME).tlb

all: $(TARGETNAME).dll

$(TARGETNAME).res: $(TARGETNAME).rc
    $(rc) -r -fo $(TARGETNAME).res $(TARGETNAME).rc

ExtObjID.h: ExtObjID.idl
    midl $*.idl -DMIDL_PASS /header $*.h /iid $*_i.c /tlb $*.tlb

StdAfx.obj: StdAfx.cpp
    $(cc) $(cflags) $(EXTRACFLAGS) $(cvarsdll) /Fp"$(TARGETNAME).pch" /Yc"stdafx.h" $*.cpp

$(TARGETNAME).obj: $(TARGETNAME).cpp stdafx.h $(TARGETNAME).h ExtObj.h BasePage.h RegExt.h resource.h ExtObjID.h PropList.h

BasePage.obj: BasePage.cpp stdafx.h $(TARGETNAME).h ExtObj.h BasePage.h BasePage.inl resource.h ExtObjID.h PropList.h

DDxDDv.obj: DDxDDv.cpp stdafx.h resource.h

ExtObj.obj: ExtObj.cpp stdafx.h $(TARGETNAME).h ExtObj.h ResProp.h resource.h ExtObjID.h

PropList.obj: PropList.cpp stdafx.h PropList.h

RegExt.obj: RegExt.cpp stdafx.h

ResProp.obj: ResProp.cpp stdafx.h $(TARGETNAME).h ResProp.h ExtObj.h DDxDDv.h resource.h BasePage.h PropList.h ExtObjID.h

$(TARGETNAME).dll: $(OBJS) $(TARGETNAME).def
    $(link) $(EXTRALINKFLAGS) $(dlllflags) -out:$(TARGETNAME).dll -def:$(TARGETNAME).def $(OBJS) $(EXTRALIBS) $(guilibsdll)

clean:
    erase $(OBJS) $(TARGETNAME).dll $(TARGETNAME).exp $(TARGETNAME).lib $(TARGETNAME).pch ExtObjID.h ExtObjID_i.c ExtObjID.tlb
