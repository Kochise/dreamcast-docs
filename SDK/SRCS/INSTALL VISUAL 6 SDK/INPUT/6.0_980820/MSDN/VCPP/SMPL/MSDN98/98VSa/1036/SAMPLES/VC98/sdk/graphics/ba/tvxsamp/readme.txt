An MFC sample that connects to and controls TV Viewer.

Summary
=======
TVXSamp is a Microsoft(R) Foundation Classes (MFC) application that 
connects to and controls an instance of TV Viewer. The sample has a 
single dialog box with buttons you can click to test its functionality. 
On startup, TVXSamp gets a reference to a running instance of 
TV Viewer. It uses this reference to call methods of the TV Viewer 
dispatch interface, ITVViewer. 

For more information, see the TV Viewer and Creating TV Viewer 
Controls topics in the Broadcast Architecture Programmer's Reference.

More Information
================
The following information describes the TVXSamp sample.


Requirements
-----------------------------
TVXSamp.exe must be run on a computer running the 
Microsoft(R) Windows(R) 98 operating system with the TV Viewer 
components installed. You should start TV Viewer before running 
TVXSamp.exe.

TVXSamp.exe must be compiled using the 
Microsoft(R) Visual C++(R) development system version 5.0 
with MFC and Microsoft Active Template Library (ATL). 

You must configure your environment before 
compiling TVXSamp.exe. First, make sure that 
the environment variable INCLUDE points to the 
Visual C++ Include directory, the ATL include directory,
and the MFC Include directory. Similarly, make sure 
the environment variable LIB points to the 
Visual C++ Lib directory and the MFC Lib directory.

To Compile TVXSamp
------------------
From the command prompt, use the following command:

nmake

For make options, see the makefile header comments.


To Run TVXSamp
--------------
You must start TV Viewer before you run TVXSamp.exe. Otherwise, 
TVXSamp cannot connect to TV Viewer, and a run-time error occurs.

Start TVXSamp.exe either from the command line by typing 

TVXSamp

or by double-clicking the TVXSamp icon in Windows Explorer. 

A dialog box appears, containing the following buttons:

Toggle TV Mode
	Toggles TV Viewer between full screen and desktop mode.

Tune to TV Config
	Tunes TV Viewer to the TV Config channel, 1.

Tune Back to Previous Channel
	Tunes TV Viewer to the previous channel. This is the same 
	functionality as a Back button in a Web browser.


TVXSamp Files
=============

Tvdisp.h
	This is the header file for the TV Viewer dispatch interface. 
	It is created from Tvdisp.odl.

TVXSamp.h
    This is the main header file for the application. It includes 
    other project specific headers (including Resource.h) and 
    declares the CTVXSampApp application class.

TVXSamp.cpp
    This is the main application source file that contains the 
    application class CTVXSampApp.

TVXSamp.rc
    This is a listing of all of the Microsoft Windows resources that 
    the program uses. It includes the icons, bitmaps, and cursors that
    are stored in the Res subdirectory. This file can be directly 
    edited in Microsoft(R) Developer Studio.

Res\TVXSamp.ico
    This is an icon file that is used as the application's icon. This
    icon is included by the main resource file TVXSamp.rc.

Res\TVXSamp.rc2
    This file contains resources that are not edited by Microsoft 
    Developer Studio. You should place all resources that the 
    resource editor cannot edit in this file.

TVXSamp.reg
    This is an example .reg file that shows you the kind of 
    registration settings the framework sets for you. You can use 
    this as a .reg file to go along with your application.

TVXSamp.odl
    This file contains the Object Description Language source code for 
    the type library of your application.

TVXSamp.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes. ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.


/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog box class and Automation proxy class:

TVXSampDlg.h, TVXSampDlg.cpp -- the dialog
    These files contain your CTVXSampDlg class. This class defines
    the behavior of your application's main dialog box. The dialog 
    box's template is in the TVXSamp.rc file, which can be edited 
    in Microsoft Developer Studio.

DlgProxy.h, DlgProxy.cpp -- the Automation object
    These files contain your CTVXSampDlgAutoProxy class. This class
    is called the "Automation proxy" class for your dialog box, because 
    it takes care of exposing the Automation methods and properties 
    that Automation controllers can use to access your dialog box. 
    These methods and properties are not exposed from the dialog box
    class directly, because in the case of a modal-dialog-box-based MFC 
    application it is cleaner and easier to keep the Automation 
    object separate from the user interface.

/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named TVXSamp.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource 
    identifiers. Microsoft Developer Studio reads and updates this 
    file.
