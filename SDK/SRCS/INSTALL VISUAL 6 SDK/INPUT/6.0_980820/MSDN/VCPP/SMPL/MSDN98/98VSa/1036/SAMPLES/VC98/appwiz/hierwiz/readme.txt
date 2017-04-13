========================================================================
					CUSTOM APPWIZARD: HIERWIZ
========================================================================
This AppWizard is an example of how to write a custom AppWizard that is
based solely on your custom steps.  The techniques that this
custom AppWizard is designed to demonstrate are:

	1. converting an existing project into a Custom AppWizard
	2. adding custom pages to a wizard which started out with no pages
	3. validating the user entries before going from one page to the next
	4. changing the state of the Next button depending on user options
	5. conditional manipulation of project templates
	   - adding a second view to an otherwise single view MDI application
	   - adding code to open a default document on startup

This file also contains a summary of what you will find in each of the
files that make up your HIERWIZ DLL.

/////////////////////////////////////////////////////////////////////////////
CONVERTING AN EXISTING PROJECT INTO A CUSTOM APPWIZARD

You can take any existing Appwizard generated project and convert it into
a Custom Appwizard by running Appwizard and selecting Custom Appwizard
from the project type. On the first page choose to base your Custom AppWizard
on an existing project.


/////////////////////////////////////////////////////////////////////////////
ADDING CUSTOM PAGES TO AN APPWIZARD WHICH DIDN'T HAVE ANY TO BEGIN WITH

A Custom Appwizard generated using the above options will not have any custom
pages. You will have to perform the following tasks to add custom pages to it.

i) Add a CDialogChooser derived class to your project.
	The easiest way of doing this is by creating a Custom Appwizard project
	based on your Custom steps, and copy the generated chooser.* files to your
	project. You can now modify these files to fit your Custom Appwizard.
	(For a complete description of the the different function and macros in the
	CDialogChooser class, please refer to the user documentation.)

/////////////////////////////////////////////////////////////////////////////
VALIDATING USER INPUT BEFORE CHANGING PAGES

	The CEdtDlg::OnDismiss() function in file "EDTDLG.CPP" performs data validation
	before the user moves on to the next/previous page.

/////////////////////////////////////////////////////////////////////////////
CHANGING THE STATE OF NEXT BUTTON DEPENDING ON USER OPTIONS.

	It may be necessary to disable or enable the "Next" button of your Custom Appwizard
	depending on the user choices on a given page.  Take a look at the CCustom1Dlg::OnNodata()
	function in file "CSTM1DLG.CPP" for an example.

/////////////////////////////////////////////////////////////////////////////
CONDITIONAL CHANGES TO THE CODE TEMPLATES

	Several changes were made to the HIERSVR sample to support multi-views of the same document.
	Additionally, code is conditionally generated depending on where the user's sample text comes from.
	The following template files were modified to accomplish this. Search for the dictionary symbols
	WANTS_TEXTVIEW, USER_INPUT_DATA, and OPEN_FILE in these files for the implementation.

- confirm.inf   provide text in the AppWizard confirmation dialog about both
				the text view and the sample input text.

- newproj.inf   to add the text view implementation files.

- root.cpp      code to register the new view, and open the default document.

- svrdoc.cpp    support for providing the text needed for the text view.

- svritem.cpp   support for exposing an item text.

- resource.h    define the IDs needed for handling all aspects of the new view commands.

- root.cpp      added ClassWizard information for the text view class

- root.rc       added a Text view to the main menu and popup menu.

- textview.*    declaration and implementation of the text view


- root.MAK      added the textview.cpp file.

========================================================================
							PROJECT FILES
========================================================================

HIERWIZ.MAK
	This project file is compatible with the Visual C++ development
	environment.  It is also compatible with the NMAKE program provided with
	Visual C++.

	To build a debug version of the program from the MS-DOS prompt, type
	nmake /f HIERWIZ.MAK CFG="Win32 Debug".

	To build a release version of the program, type
	nmake /f HIERWIZ.MAK CFG="Win32 Release".

HIERWIZ.CPP
	This file is the main DLL source file that contains the definition of
	DllMain().  It also exports the function GetCustomAppWizClass(), which
	returns a pointer to the one instance of this custom AppWizard's
	CCustomAppWiz-derived class.

HIERWIZ.H
	This file is the main header file for the DLL.  It includes your
	RESOURCE.H file.

HIERWIZ.RC
	This file is a listing of all of the Microsoft Windows resources that the
	program uses.  It includes all of your custom AppWizard's templates as
	custom resources of type "TEMPLATE".  These resources are pointers to the
	files in your project's TEMPLATE directory.  This file can be directly
	edited in the Visual C++ development environment.  However, you will
	probably want to edit your templates by opening the template files directly
	in the source editor rather than by editing the "TEMPLATE" resources from
	the Visual C++ resource editor.

HIERWIZ.CLW
	This file contains information used by ClassWizard to edit existing
	classes or add new classes.  ClassWizard also uses this file to store
	information needed to create and edit message maps and dialog data
	maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////
Custom AppWizard Interface:

HIERWAW.H, HIERWAW.CPP - the CCustomAppWiz class
	These files contain your CCustomAppWiz-derived class,
	CHierwizAppWiz.  This class contains virtual member functions which
	MFCAPWZ.DLL calls to initialize your custom AppWizard and to query which
	step to pop up at a given time.  This class also contains m_Dictionary,
	a CMapStringToString member variable, which maps template macro names
	to their values.

/////////////////////////////////////////////////////////////////////////////
Dialogs:

CHOOSER.H, CHOOSER.CPP - the dialog chooser
	These files contain your CDialogChooser class.  The class maintains
	pointers to each of your steps, keeps track of which step is currently
	up, and handles calls to your custom AppWizard class's member functions
	Next(...) and Back(...).

CSTM*DLG.H, CSTM*DLG.CPP - the dialog classes
	These files contain the dialog classes for all of your custom AppWizard's
	new steps.  They derive from CAppWizStepDlg and override
	CAppWizStepDlg::OnDismiss.

/////////////////////////////////////////////////////////////////////////////
Help Support:

MAKEHELP.BAT
	Use this batch file to create your custom AppWizard's Help file,
	LOGOWIZ.HLP.

LOGOWIZ.HPJ
	This file is the Help Project file used by the Help compiler to create
	your custom AppWizard's Help file.

HLP\LOGOWIZ.RTF
	This file contains an empty topic for each new step you generated.
	You may fill out the topics using any rich-text-format
	editor such as Microsoft Word.

/////////////////////////////////////////////////////////////////////////////
Template Files:

TEMPLATE\
	Put your template files in this directory.  Template files are stored
	in your custom AppWizard as custom resources of type "TEMPLATE", and are
	used by your custom AppWizard to determine the contents of the files it
	generates. When you add a new template file to this directory, you must
	import that file as a "TEMPLATE" custom resource into logowiz.rc.  Be
	sure to select the "External File" checkbox on the custom resource's
	property page.

TEMPLATE\CONFIRM.INF
	In this template you should put a description of the project your
	custom AppWizard generates.  The file uses template macros to customize the
	text to reflect which options were selected by the custom AppWizard user.
	When the custom AppWizard user clicks the "Finish" button, MFCAPWZ.DLL
	parses this template and sends the output to the New Project Information
	dialog.

TEMPLATE\NEWPROJ.INF
	This template lists all of the templates other than CONFIRM.INF and
	NEWPROJ.INF which your custom AppWizard will use to generate a project.
	After MFCAPWZ.DLL parses this template, the output lists the other
	templates to be parsed and what the output files should be called.  See
	the documentation on custom AppWizards for a more complete description
	of this template and the project generation process in general.

You have also been provided with copies of the templates used by AppWizard
to generate an executable.  You are free to modify any of these templates
to customize them any way you like.  For example, you may wish to change
the source code tabbing style, or to include your company's copyright
message at the top of each source code file.  If you delete any of these
templates, AppWizard's copy of the template will automatically be used
when your custom AppWizard generates projects.

/////////////////////////////////////////////////////////////////////////////
Other Standard Files:

STDAFX.H, STDAFX.CPP
	These files are used to build a precompiled header (PCH) file
	named LOGOWIZ.PCH and a precompiled types file named STDAFX.OBJ.

RESOURCE.H
	This is the standard header file, which defines new resource IDs.
	Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other Notes:

You will need to copy your custom AppWizard DLLs into the bin\appwiz subdirectory
under your Visual C++ installation (default: \msvc30\bin\appwiz) in order for them
to be available.  If you like, you can do this once in your project settings for
each custom AppWizard.  This is not done by default.

/////////////////////////////////////////////////////////////////////////////
