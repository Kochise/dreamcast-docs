COM Sample Directory Tree

The COM directory contains several sample COM applications.

Directory   Description

COMMON      Common code used by all the OLE samples.
INCLUDE     Common include files used by all the OLE samples.
WINHLPRS    Library of Windows helper functions used by MFRACT and DFVIEW.

BROWSE      OLE Automation controller that controls the BROWSEH inproc server.
BROWSEH     OLE Automation server that browses a type library.
BTTNCUR     Genertates BTTNCUR.DLL and BTTNCUR.LIB.
CMALLSPY    Sample IMallocSpy implementation.
COM         OLE tutorial samples.
DEFO2V      Source code for the OLE2VIEW default object viewer DLL.
DFVIEW      Docfile viewer.
DISPCALC    OLE Automation sample program.
DISPDEMO    Sample OLE Automation controller.
DSPCALC2    OLE Automation sample program.
GIZMOBAR    Generates GIZMOBAR.DLL and GIZMOBAR.LIB.
HELLO       OLE automation server that implements a dual interface.
LINES       OLE Automation implementing collections and subobjects.
MFRACT      Custom interface sample.
OLEAPT      OLE Apartment model threading sample.
OLESTD      Generates OLESTD.LIB.
OUTLINE     Series illustrating converting a Windows application to OLE.
SIMPCNTR    Simple OLE container sample.
SIMPDND     Simple drag and drop sample.
SIMPSVR     Simple OLE server sample.
SPOLY       OLE Automation sample polygon drawing program.
SPOLY2      OLE Automation sample polygon drawing program.
TIBROWSE    OLE Automation sample type library browser.

Additional directories are created by these samples:

LIB         Will contain library files generated during the build.
BIN         Will contain many of the target .EXE and .DLL files.

More details on each of these samples can be found in the readme.txt
files found in these directories.

To build all of these samples, use the following command

    nmake -a