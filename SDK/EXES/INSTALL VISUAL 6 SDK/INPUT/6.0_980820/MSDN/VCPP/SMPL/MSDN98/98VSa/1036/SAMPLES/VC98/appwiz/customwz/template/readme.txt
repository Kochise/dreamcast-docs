========================================================================
					CUSTOM APPWIZARD: $$root$$
========================================================================


AppWizard has created a $$root$$ DLL for you.  This DLL is the starting point
for writing your custom AppWizard.  It demonstrates the basics of creating a
custom AppWizard.

Although your custom AppWizard is a DLL, it has the special suffix AWX.  When
you build $$root$$.awx, it will automatically be copied to your Template
directory.  Your custom AppWizard will then appear as a choice in the Project
Type drop-list in the New Workspace and Insert Project dialogs.  To run your
custom AppWizard, simply create a new workspace (or insert a project into the
current workspace), and select your custom AppWizard from the Project Type
drop-list.

This file contains a summary of what you will find in each of the files that
make up your $$root$$ DLL.

$$root$$.dsw
	This file (the project workspace file) contains information on the contents
	and organization of the project workspace. Other users can share the project
	workspace (.dsw) file, but they should export the makefiles locally.

	Files associated with the project workspace file are a project file (.dsp)
	for each project in the workspace and a workspace options file (.opt).

$$root$$.dsp
	This file (the project file) contains information at the project level and
	is used to build a single project or subproject. Other users can share the
	project (.dsp) file, but they should export the makefiles locally.

$$root$$.opt
	This file (the workspace options file) contains the workspace settings that
	you specify in the Project Settings dialog. These settings specify the
	appearance of the project workspace using your hardware and configuration.

	This binary file is automatically generated when you open the .dsw or .dsp
	file in the IDE. You should not share the .opt file, because it contains
	information specific to your computer.

$$root$$.ncb
	This file provides information on the NCB (No Compile Browse) parser, the
	mechanism that updates ClassView and WizardBar.

	This is a binary file that is generated automatically and should not be
	shared.

$$root$$.cpp
	This file is the main DLL source file that contains the definition of
	DllMain().  It also exports the function GetCustomAppWizClass(), which
	returns a pointer to the one instance of this custom AppWizard's
	CCustomAppWiz-derived class.

$$root$$.h
	This file is the main header file for the DLL.  It includes your
	RESOURCE.H file.

$$root$$.rc
	This file is a listing of all of the Microsoft Windows resources that the
	program uses.  It includes all of your custom AppWizard's templates as
	custom resources of type "TEMPLATE".  These resources are pointers to the
	files in your project's TEMPLATE directory.  This file can be directly
	edited in the Visual C++ development environment.  However, you will
	probably want to edit your templates by opening the template files directly
	in the source editor rather than by editing the "TEMPLATE" resources from
	the Visual C++ resource editor.

$$root$$.clw
	This file contains information used by ClassWizard to edit existing
	classes or add new classes.  ClassWizard also uses this file to store
	information needed to create and edit message maps and dialog data
	maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////
Custom AppWizard Interface:

$$filebase$$Aw.h, $$filebase$$Aw.cpp - the CCustomAppWiz class
	These files contain your CCustomAppWiz-derived class,
	C$$Safe_root$$AppWiz.  This class contains virtual member functions which
	MFCAPWZ.DLL calls to initialize your custom AppWizard and to query which
	step to pop up at a given time.  This class also contains m_Dictionary,
	a CMapStringToString member variable, which maps template macro names
	to their values.
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)

/////////////////////////////////////////////////////////////////////////////
Dialogs:

Chooser.h, Chooser.cpp - the dialog chooser
	These files contain your CDialogChooser class.  The class maintains
	pointers to each of your steps, keeps track of which step is currently
	up, and handles calls to your custom AppWizard class's member functions
	Next(...) and Back(...).
$$IF(HAS_NEW_STEPS)

Cstm*Dlg.h, Cstm*Dlg.cpp - the dialog classes
	These files contain the dialog classes for all of your custom AppWizard's
	new steps.  They derive from CAppWizStepDlg and override
	CAppWizStepDlg::OnDismiss.
$$ENDIF //HAS_NEW_STEPS
$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE
$$IF(HAS_NEW_STEPS)

/////////////////////////////////////////////////////////////////////////////
Help Support:

MakeHelp.bat
	Use this batch file to create your custom AppWizard's Help file,
	$$root$$.hlp.

$$root$$.hpj
	This file is the Help Project file used by the Help compiler to create
	your custom AppWizard's Help file.

HLP\$$root$$.rtf
	This file contains an empty topic for each new step you generated.
	You may fill out the topics using any rich-text-format
	editor such as Microsoft Word.
$$ENDIF //HAS_NEW_STEPS

/////////////////////////////////////////////////////////////////////////////
Template Files:

Template\
	Put your template files in this directory.  Template files are stored
	in your custom AppWizard as custom resources of type "TEMPLATE", and are
	used by your custom AppWizard to determine the contents of the files it
	generates. When you add a new template file to this directory, you must
	import that file as a "TEMPLATE" custom resource into $$root$$.rc.  Be
	sure to select the "External File" checkbox on the custom resource's
	property page.

Template\Confirm.inf
	In this template you should put a description of the project your
	custom AppWizard generates.  The file uses template macros to customize the
	text to reflect which options were selected by the custom AppWizard user.
	When the custom AppWizard user clicks the "Finish" button, MFCAPWZ.DLL
	parses this template and sends the output to the New Project Information
	dialog.
$$IF(CUSTOMTYPE_SEQUENCE)
		Initially, this file is identical to the Confirm.inf template used
	by AppWizard.  If you add your own custom steps to the standard AppWizard
	steps, you’ll need to add text, macros, and directives to this template
	that reflect each feature a user can choose in each custom step.
$$ENDIF //CUSTOMTYPE_SEQUENCE

Template\NewProj.inf
	This template lists all of the templates other than Confirm.inf and
	NewProj.inf which your custom AppWizard will use to generate a project.
	After MFCAPWZ.DLL parses this template, the output lists the other
	templates to be parsed and what the output files should be called.
$$IF(CUSTOMTYPE_SEQUENCE)
		Initially, this file is identical to the NewProj.inf template used
	by AppWizard.  If you add your own custom steps to the standard AppWizard
	steps which require that additional files be generated, you will need to
	add statements, macros, and directives to this template that can build a
	project for any combination of features a user can select from the custom
	steps.
$$ELIF(CUSTOMTYPE_ZAP)
$$IF(ZAP_FULL_PATH)
		Initially, this file contains the names of the templates that were
	generated from the project "$$ZAP_FULL_PATH$$".
	You will not need to edit this template unless you add functionality to
	the project generated by your custom AppWizard.
$$ENDIF //ZAP_FULL_PATH
$$ENDIF //CUSTOMTYPE_SEQUENCE,_ZAP
		See the documentation on custom AppWizards for a more complete
	description of this template and the project generation process in general.
$$IF(CUSTOMTYPE_SEQUENCE)

You have also been provided with copies of the templates used by AppWizard
$$IF(APWZSEQ_EXE)
to generate an executable.  You are free to modify any of these templates
$$ELSE //APWZSEQ_DLL
to generate a DLL.  You are free to modify any of these templates
$$ENDIF //APWZSEQ_EXE,DLL
to customize them any way you like.  For example, you may wish to change
the source code tabbing style, or to include your company's copyright
message at the top of each source code file.  If you delete any of these
templates, AppWizard's copy of the template will automatically be used
when your custom AppWizard generates projects.
$$ELIF(CUSTOMTYPE_ZAP)
$$IF(ZAP_FULL_PATH)

You have also been provided with template files in this directory based
off of the project "$$ZAP_FULL_PATH$$".
$$ENDIF //ZAP_FULL_PATH
$$ENDIF //CUSTOMTYPE_SEQUENCE,ZAP

/////////////////////////////////////////////////////////////////////////////
Other Standard Files:

StdAfx.h, StdAfx.cpp
	These files are used to build a precompiled header (PCH) file
	named $$root$$.pch and a precompiled types file named StdAfx.obj.

Resource.h
	This is the standard header file, which defines new resource IDs.
	Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other Notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.
