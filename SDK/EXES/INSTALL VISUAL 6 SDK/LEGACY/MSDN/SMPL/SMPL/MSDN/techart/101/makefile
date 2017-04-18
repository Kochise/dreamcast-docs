# Makefile : Builds the hello application
#
# Usage:     NMAKE option (build hello)
#    or:     NMAKE clean  (erase all compiled files)
#
# options:   DEBUG=[0|1]  (DEBUG not defined is equivalent to DEBUG=0)
#				 LARGE=[0|1] (Build Large model if 1. Default is Medium Model)
#				 MINST=[0|1] (Make multiple Instance - only valid with LARGE=1)
#
# examples: nmake DEBUG=1  // medium model debug
#				nmake DEBUG=1 LARGE=1 // large model debug
#				nmake LARGE=1 MINST=1 // multi-instnace large model non-debug
#


!if "$(LARGE)"=="1"
MODEL=L
!if "$(MINST)"=="1"
!MESSAGE !!!
!MESSAGE In order to use multi-instance Large Model MFC Apps
!MESSAGE The Large Model MFC libraries much be compiled with OPT="/Gt32767 /Gx"
!MESSAGE !!!
CPPSPECIAL=/Gt65500 /Gx
!endif
!else
MODEL=M
!endif

CPPFLAGS=  /DWINVER=0x0300 /A$(MODEL) /W3 /Zp /GA /GEs /G2 $(CPPSPECIAL)
LINKFLAGS=/NOD /ONERROR:NOEXE

!if "$(DEBUG)"=="1"
CPPFLAGS=/D_DEBUG $(CPPFLAGS) /Od /Zi /f
LINKFLAGS=/MAP $(LINKFLAGS) /COD
LIBS=$(MODEL)afxcwd libw $(MODEL)libcew
!else
CPPFLAGS=$(CPPFLAGS) /Oselg /Gs
LINKFLAGS=$(LINKFLAGS)  
LIBS=$(MODEL)afxcw libw $(MODEL)libcew
!endif

newopr.exe:     newopr.obj newopr.def newopr.res
	link $(LINKFLAGS) newopr, newopr, newopr, $(LIBS),newopr.def;
	rc -k -30 /t newopr.res


newopr.res:  resource.h newopr.ico newopr.dlg

newopr.obj:  newopr.h resource.h

clean:
	-erase newopr.exe
	-erase newopr.res
	-erase newopr.obj
