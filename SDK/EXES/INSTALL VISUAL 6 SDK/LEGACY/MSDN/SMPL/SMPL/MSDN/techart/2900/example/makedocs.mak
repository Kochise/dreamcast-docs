# Autoduck MAKEFILE
#
# Eric Artzt, Program Manager
# Consumer Division, Kids Software Group
# Internet  :  erica@microsoft.com
#

OUTDIR  = $(ProjDir)\Autoduck
TARGET  = $(Project)
TITLE   = $(TARGET) Help
DOCHDR  = $(TARGET) API Reference
AD      = autoduck.exe
ADTOC   = $(AdDir)\Contents.D
ADHLP   = /RH /O$(OUTDIR)\$(TARGET).RTF /D "title=$(TITLE)"
ADDOC   = /RD /O$(OUTDIR)\$(TARGET).DOC /D "doc_header=$(DOCHDR)"
ADTAB   = 8
HC      = hcw /a /e /c
SOURCE  = *.cpp *.h *.bas *.d

# Help and Doc targets

target ::
!if !EXIST("$(OUTDIR)")
    md $(OUTDIR)
! endif

target :: $(TARGET).hlp $(TARGET).doc

clean:
    if exist $(OUTDIR)\*.rtf del $(OUTDIR)\*.rtf
    if exist $(OUTDIR)\$(TARGET).doc del $(OUTDIR)\$(TARGET).doc
    if exist $(OUTDIR)\$(TARGET).hlp del $(OUTDIR)\$(TARGET).hlp

# Generate a Help file

$(TARGET).rtf : $(SOURCE) $(ADTOC)
    $(AD) $(ADHLP) /t$(ADTAB) $(ADTOC) $(SOURCE)

$(TARGET).hlp : $(TARGET).rtf
    $(HC) $(OUTDIR)\$(TARGET).HPJ

# Generate a print documentation file

$(TARGET).doc :  $(SOURCE)
    $(AD) $(ADDOC) /t$(ADTAB) $(SOURCE)

