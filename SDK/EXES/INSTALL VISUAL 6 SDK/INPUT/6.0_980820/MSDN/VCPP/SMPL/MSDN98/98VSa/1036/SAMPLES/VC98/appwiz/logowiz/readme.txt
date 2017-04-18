========================================================================
					CUSTOM APPWIZARD: LOGOWIZ
========================================================================


This AppWizard is an example of how to write a custom AppWizard that is
a variant on the standard MFC AppWizard.  The techniques that this
custom AppWizard is designed to demonstrate are:

	1. removing a page from an otherwise standard AppWizard
	2. modifying defaults on standard AppWizard pages
	3. adding a custom page to an otherwise standard AppWizard
	4. conditional manipulation of project templates
	   - adding controls to the main window of a dialog-based application
	   - adding files to the new project
	   - adding code to otherwise standard templates

This file also contains a summary of what you will find in each of the
files that make up your LOGOWIZ DLL.

/////////////////////////////////////////////////////////////////////////////
REMOVING STANDARD APPWIZARD PAGES

You can remove any AppWizard pages from the standard list that you like.
While it is also possible to rearrange the sequence as well, that is not
recommended. This is done in the constructor for CDialogChooser in
chooser.cpp.

In this custom AppWizard, the ODBC page has been removed if this is an
MDI/SDI based app. You can find further details about how this was done in
comments near the code itself (see CDialogChooser::CDialogChooser() in
chooser.cpp).  If you want, you can set the defaults as desired for a page
that you remove.  This will have the effect of making the defaults mandatory
rather than optional.

/////////////////////////////////////////////////////////////////////////////
CHANGING DEFAULT SETTINGS

You can change default settings for standard AppWizard pages.  This is done
in your main custom AppWizard class (in this case, CLogoWizAppWiz in
logowaw.cpp) InitCustomAppWiz function. The list of settings you can change
are found in the online help.

In this custom AppWizard, the application type has been defaulted to dialog-
based and context sensitive help has been turned on.

/////////////////////////////////////////////////////////////////////////////
ADDING CUSTOM PAGES

You can insert custom pages at any point in the standard AppWizard sequence
that you like.  This is done in the same place that you would remove standard
AppWizard pages from the sequence (CDialogChooser::CDialogChooser()).

In this custom AppWizard, the user is given two choices for a dialog-based
application:

	1) where to put a company logo on the main window
	2) whether to include a "Press me" button on the main window

The first option is very simple to implement and required minimal changes to
the template files.  The second option involves adding several files to
handle a new dialog (popped up by pressing the "Press me" button) and adding
code to the main dialog class to handle pressing the button.

The following template files were modified to make that code work:

- confirm.inf   provide text in the AppWizard confirmation dialog about both
				the logo and the "Press me" dialog/button

- dialog.cpp,   handle the user clicking on the "Press me" button and pop up
  dialog.h      the "Press me" dialog when needed

- dlgall.rc     include the bitmaps for the "Press me" dialog's owner-draw
				buttons in the resources for the new project

- dlgres.h      define the IDs needed for handling all aspects of the
				"Press me" dialog

- dlgloc.rc     localized (English) versions of the dialogs needed for this
				project.  This includes the main dialog for the new dialog-
				based application as well as the "Press me" dialog.  The
				main dialog has been conditionally modified to include both
				the company logo (as an icon) and the "Press me" button
				used to bring up the "Press me" dialog.  The main window was
				also unconditionally made about twice the normal default
				size.

- dlgroot.clw   added ClassWizard information for the "Press me" dialog.

- frownu.bmp,   bitmaps needed to handle the owner-draw characteristics of
  frownd.bmp,   the Cancel button on the "Press me" dialog.
  frownf.bmp

- newproj.inf   copy the "Press me" bitmaps and files into the new project

- pressdlg.cpp, implement the "Press me" dialog behavior
  pressdlg.h

- readme.txt    tell the user about the addition of the logo and the
				"Press me" dialog in the standard 'readme'

- root.mak      added the "Press me" dialog classes and bitmaps to the
				appropriate dependency lists.

- smileu.bmp,   bitmaps needed to handle the owner-draw characteristics of
  smiled.bmp,   the OK button in the "Press me" dialog.
  smilef.bmp


Search for LOGO_ and PRESS_ME_DIALOG in the text files in the template
directory to see where these changes were made.  All but one of these changes
was done conditionally.  The change in size of the dialog-based application's
main window was the only unconditional change made.  In other words, if the user
chose to have no company logo and no "Press me" dialog, there would be no real
difference between a dialog-based application created using this custom
AppWizard and one created using the standard MFC AppWizard (all else being
equal).


========================================================================
							PROJECT FILES
========================================================================

LOGOWIZ.MAK
	This project file is compatible with the Visual C++ development
	environment.  It is also compatible with the NMAKE program provided with
	Visual C++.

	To build a debug version of the program from the MS-DOS prompt, type
	nmake /f LOGOWIZ.MAK CFG="Win32 Debug".

	To build a release version of the program, type
	nmake /f LOGOWIZ.MAK CFG="Win32 Release".

LOGOWIZ.CPP
	This file is the main DLL source file that contains the definition of
	DllMain().  It also exports the function GetCustomAppWizClass(), which
	returns a pointer to the one instance of this custom AppWizard's
	CCustomAppWiz-derived class.

LOGOWIZ.H
	This file is the main header file for the DLL.  It includes your
	RESOURCE.H file.

LOGOWIZ.RC
	This file is a listing of all of the Microsoft Windows resources that the
	program uses.  It includes all of your custom AppWizard's templates as
	custom resources of type "TEMPLATE".  These resources are pointers to the
	files in your project's TEMPLATE directory.  This file can be directly
	edited in the Visual C++ development environment.  However, you will
	probably want to edit your templates by opening the template files directly
	in the source editor rather than by editing the "TEMPLATE" resources from
	the Visual C++ resource editor.

LOGOWIZ.CLW
	This file contains information used by ClassWizard to edit existing
	classes or add new classes.  ClassWizard also uses this file to store
	information needed to create and edit message maps and dialog data
	maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////
Custom AppWizard Interface:

LOGOWAW.H, LOGOWAW.CPP - the CCustomAppWiz class
	These files contain your CCustomAppWiz-derived class,
	CLogowizAppWiz.  This class contains virtual member functions which
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

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
