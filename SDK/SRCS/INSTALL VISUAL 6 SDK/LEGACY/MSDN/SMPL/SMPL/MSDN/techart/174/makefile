PROJ	= LISTTEST

!IF "$(CPU)" != ""

OS      = NT
ENV     = WIN32
EXENAME = LISTT32
DLLNAME = VLIST32

!ELSE

OS      = DOS
ENV     = WIN16
OUTDIR  = OBJ16
EXENAME = LISTTEST
DLLNAME = VLIST

!ENDIF

!IF "$(CPU)" == "i386"
OUTDIR = OBJi32
!ENDIF

!IF "$(CPU)" == "MIPS"
OUTDIR = OBJm32
!ENDIF

!IF "$(CPU)" == "ALPHA"
OUTDIR = OBJm32
!ENDIF

!IF "$(CPU)" == "Alpha"
OUTDIR = OBJm32
!ENDIF

!include <$(OS)$(ENV).MAK>

!IF "$(CPU)" != ""
cflagsdll = $(cflags)
!ENDIF

##### Main (default) Target #####
goal: $(OUTDIR) $(OUTDIR)\$(DLLNAME).dll $(OUTDIR)\$(DLLNAME).lib $(OUTDIR)\$(EXENAME).exe

$(OUTDIR):
   -mkdir $(OUTDIR)

#
# list test
#
$(OUTDIR)\listtest.obj: listtest.c listtest.h
   $(cc) $(cflags) $(cvars) $(cdebug) -Fo$(OUTDIR)\ listtest.c

# Update the resource if necessary
$(OUTDIR)\listtest.res : listtest.rc listtest.dlg
	rc -r -fo $(OUTDIR)\listtest.res $(cvars) listtest.rc

# Update the resource if necessary
$(OUTDIR)\listtest.rbj : listtest.rc listtest.dlg
	rc -r -fo $(OUTDIR)\listtest.res $(cvars) listtest.rc
	cvtres -$(CPU) $(OUTDIR)\listtest.res -o $(OUTDIR)\listtest.rbj


$(OUTDIR)\listt32.exe : $(OUTDIR)\listtest.rbj $(OUTDIR)\listtest.obj listtest.def $(OUTDIR)\vlist32.lib
	$(link) $(linkdebug) $(guiflags) $(OUTDIR)\listtest.obj $(guilibs) $(OUTDIR)\vlist32.lib \
	VERSION.LIB $(OUTDIR)\listtest.rbj -out:$(OUTDIR)\listtest.exe

$(OUTDIR)\listtest.exe : $(OUTDIR)\listtest.res $(OUTDIR)\listtest.obj \
	   listtest.def $(OUTDIR)\vlist.lib
   link $(linkflags) $(linkdebug) $(OUTDIR)\listtest,$(OUTDIR)\listtest,$(OUTDIR)\listtest,libw slibcew $(OUTDIR)\vlist,listtest.def
   rc $(DFLAGS) $(OUTDIR)\listtest.res

#
#  VLIST
#
# Update the resource if necessary
$(OUTDIR)\vlist.res : vlist.rc dlgvlist.dlg
	rc -r -fo $(OUTDIR)\vlist.res $(cvars) vlist.rc

$(OUTDIR)\vlist.obj: vlist.c vlistint.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ vlist.c

$(OUTDIR)\vlscroll.obj: vlscroll.c vlistint.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ vlscroll.c

$(OUTDIR)\vlrare.obj: vlrare.c vlistint.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ vlrare.c

$(OUTDIR)\vlsetcur.obj: vlsetcur.c vlistint.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ vlsetcur.c

$(OUTDIR)\dllstuff.obj: dllstuff.c vlistint.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ dllstuff.c

$(OUTDIR)\dlgvlist.obj: dlgvlist.c dlgvlist.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ dlgvlist.c

$(OUTDIR)\draw3d.obj:	draw3d.c draw3d.h
   $(cc) $(cflagsdll) $(cvarsdll) $(cdebug) -Fo$(OUTDIR)\ draw3d.c

# Update the dynamic link library
$(OUTDIR)\vlist32.dll: $(OUTDIR)\vlist.obj vlist.def $(OUTDIR)\vlist.res $(OUTDIR)\dllstuff.obj \
		   $(OUTDIR)\vlscroll.obj $(OUTDIR)\vlrare.obj \
		   $(OUTDIR)\vlsetcur.obj $(OUTDIR)\draw3d.obj
	$(link) $(linkdebug) -machine:$(CPU)  \
	-dll                            \
	-entry:DllEntryPoint$(DLLENTRY) \
	-out:$(OUTDIR)\vlist32.dll \
	$(guilibsdll) \
	$(OUTDIR)\vlist.obj $(OUTDIR)\vlrare.obj $(OUTDIR)\vlscroll.obj \
	$(OUTDIR)\vlsetcur.obj $(OUTDIR)\dllstuff.obj $(OUTDIR)\draw3d.obj

$(OUTDIR)\vlist.dll: $(OUTDIR)\vlist.obj vlist.def $(OUTDIR)\vlist.res \
		$(OUTDIR)\dllstuff.obj $(OUTDIR)\vlscroll.obj $(OUTDIR)\vlrare.obj \
		$(OUTDIR)\vlsetcur.obj $(OUTDIR)\dlgvlist.obj $(OUTDIR)\draw3d.obj
	link $(linkflags) $(linkdebug)	$(OUTDIR)\vlist $(OUTDIR)\vlrare $(OUTDIR)\vlscroll $(OUTDIR)\vlsetcur $(OUTDIR)\dllstuff $(OUTDIR)\dlgvlist $(OUTDIR)\draw3d libentry, $(OUTDIR)\vlist.dll,,libw sdllcew, vlist.def
	rc $(OUTDIR)\vlist.res $(OUTDIR)\vlist.dll

# Update the import library
$(OUTDIR)\vlist32.lib: $(OUTDIR)\vlist32.dll
	lib32 -machine:$(CPU) \
		 -def:vlist32.def	  \
		-out:$(OUTDIR)\vlist32.lib $(OUTDIR)\vlist.obj $(OUTDIR)\dllstuff.obj $(OUTDIR)\vlscroll.obj $(OUTDIR)\vlrare.obj $(OUTDIR)\vlsetcur.obj $(OUTDIR)\draw3d.obj

$(OUTDIR)\vlist.lib: $(OUTDIR)\vlist.dll
	implib $(OUTDIR)\vlist.lib vlist.def


# next to godliness
clean:
		-del $(OUTDIR)\*.dll
		-del $(OUTDIR)\*.obj
		-del $(OUTDIR)\*.res
		-del $(OUTDIR)\*.exe
		-del $(OUTDIR)\*.map
		-del $(OUTDIR)\*.sym
