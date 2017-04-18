========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : XRTFRAME
========================================================================


AppWizard has created this XRTFRAME application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your XRTFRAME application.


XRTFRAME.MAK
    This project file is compatible with the Visual C++ development
	environment. 

    It is also compatible with the NMAKE program provided with Visual C++. 

    To build a debug version of the program from the MS-DOS prompt, type
nmake /f XRTFRAME.MAK CFG="Win32 Debug"
    or to build a release version of the program, type
nmake /f XRTFRAME.MAK CFG="Win32 Release"

XRTFRAME.H
    This is the main header file for the application.  It includes other
    project specific headers (including RESOURCE.H) and declares the
    CXrtframeApp application class.

XRTFRAME.CPP
    This is the main application source file that contains the application
    class CXrtframeApp.

XRTFRAME.RC
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in the
    Visual C++ development environment.

RES\XRTFRAME.ICO
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file XRTFRAME.RC.

RES\XRTFRAME.RC2
    This file contains resources that are not edited by the Visual C++
	development environment.  You should place all resources not
	editable by the resource editor in this file.


XRTFRAME.CLW
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MAINFRM.H, MAINFRM.CPP
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

RES\TOOLBAR.BMP
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the
    CMainFrame class.  Edit this toolbar bitmap along with the
    array in MAINFRM.CPP to add more toolbar buttons.

RES\ITOOLBAR.BMP
	This bitmap file is used to create tiled images for the toolbar
	when your server application is in-place activated inside another
	container.  This toolbar is constructed in the CInPlaceFrame 
	class.  This bitmap is similar to the bitmap in RES\TOOLBAR.BMP
	except that it has many non-server commands removed.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

XRTFRDOC.H, XRTFRDOC.CPP - the document
    These files contain your CXrtframeDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CXrtframeDoc::Serialize).

XRTFRVW.H, XRTFRVW.CPP - the view of the document
    These files contain your CXrtframeView class.
    CXrtframeView objects are used to view CXrtframeDoc objects.
    
RES\XRTFRDOC.ICO
    This is an icon file, which is used as the icon for MDI child windows
    for the CXrtframeDoc class.  This icon is included by the main
    resource file XRTFRAME.RC.

XRTFRAME.REG
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.

XRTFRAME.ODL
    This file contains the Object Description Language source code for the
    type library of your application.

/////////////////////////////////////////////////////////////////////////////

AppWizard has also created classes specific to OLE Linking and Embedding

SRVRITEM.H, SRVRITEM.CPP - this class is used to 
	connect your CXrtframeDoc class to the OLE system, and optionally
	provide links to your document.
IPFRAME.H, IPFRAME.CPP - this class is derived
	from COleIPFrameWnd and controls all frame features during
	in-place activation.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

STDAFX.H, STDAFX.CPP
    These files are used to build a precompiled header (PCH) file
    named XRTFRAME.PCH and a precompiled types file named STDAFX.OBJ.

RESOURCE.H
    This is the standard header file, which defines new resource IDs.
    Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
