========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : DRAWING
========================================================================


AppWizard has created this DRAWING DLL for you.  This DLL not only
demonstrates the basics of using the Microsoft Foundation classes but
is also a starting point for writing your DLL.

This file contains a summary of what you will find in each of the files that
make up your DRAWING DLL.


DRAWING.MAK
    This project file is compatible with the Visual C++ development
	environment. 

    It is also compatible with the NMAKE program provided with Visual C++. 

    To build a debug version of the program from the MS-DOS prompt, type
nmake /f DRAWING.MAK CFG="Win32 Debug"
    or to build a release version of the program, type
nmake /f DRAWING.MAK CFG="Win32 Release"

DRAWING.H
	This is the main header file for the DLL.  It declares the
	CDrawingApp class.

DRAWING.CPP
	This is the main DLL source file.  It contains the class CDrawingApp.
	It also contains the OLE entry points required of inproc servers.

DRAWING.ODL
    This file contains the Object Description Language source code for the
    type library of your DLL.

DRAWING.RC
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in the
    Visual C++ development environment.

RES\DRAWING.RC2
    This file contains resources that are not edited by the Visual C++
	development environment.  You should place all resources not
	editable by the resource editor in this file.

DRAWING.DEF
    This file contains information about the DLL that must be
    provided to run with Microsoft Windows.  It defines parameters
    such as the name and description of the DLL.  It also exports
	functions from the DLL.

DRAWING.CLW
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

STDAFX.H, STDAFX.CPP
    These files are used to build a precompiled header (PCH) file
    named DRAWING.PCH and a precompiled types file named STDAFX.OBJ.

RESOURCE.H
    This is the standard header file, which defines new resource IDs.
    Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
