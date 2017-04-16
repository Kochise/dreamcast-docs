@echo off

rem Create the log file from the headers and source files
AUTODOC /LANIMATE.LOG /ONUL /FAUTODOC.FMT *.CPP ..\include\*.H

rem Create the output file
AUTODOC /RH /CANIMATE.LOG /OANIMATE.RTF /FAUTODOC.FMT /t4 *.CPP ..\include\*.H
HC31 ANIMATE

rem Delete the intermediate files
del animate.hpj
del animate.log
del animate.rtf


