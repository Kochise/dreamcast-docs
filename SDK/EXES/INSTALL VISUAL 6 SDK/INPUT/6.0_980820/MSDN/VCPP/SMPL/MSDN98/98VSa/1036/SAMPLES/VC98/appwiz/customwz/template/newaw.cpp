// $$filebase$$aw.cpp : implementation file
//

#include "stdafx.h"
#include "$$root$$.h"
#include "$$filebase$$aw.h"
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)
#include "chooser.h"
$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void C$$Safe_root$$AppWiz::InitCustomAppWiz()
{
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

$$ENDIF
$$IF(APWZSEQ_EXE)
	// At first, we don't know the total number of steps, since there are two
	//  possible "tracks" (MDI/SDI app and dialog-based app).
	SetNumberOfSteps(-1);

	// Inform AppWizard of the languages we support
	SetSupportedLanguages(_T("$$SUPPORTED_LANGS$$"));
$$ELIF(APWZSEQ_DLL)
	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

	// Inform AppWizard that we're making a DLL.
	m_Dictionary[_T("PROJTYPE_DLL")] = _T("1");
$$ELIF(CUSTOMTYPE_ZAP || !HAS_NEW_STEPS)
	// There are no steps in this custom AppWizard.
	SetNumberOfSteps(0);
$$IF(CUSTOMTYPE_ZAP)

	// Add build step to .hpj if there is one
	m_Dictionary[_T("HELP")] = _T("1");
$$IF(CREATE_DLL_PROJECT)

	// Inform AppWizard that we're making a DLL.
	m_Dictionary[_T("PROJTYPE_DLL")] = _T("1");
$$ENDIF //CREATE_DLL_PROJECT
$$ENDIF //CUSTOMTYPE_ZAP
$$ELSE
	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);
$$ENDIF

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void C$$Safe_root$$AppWiz::ExitCustomAppWiz()
{
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE
	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
$$IF(!CUSTOMTYPE_ZAP)
//  or "Next" on one of the custom AppWizard's steps.
$$ENDIF //!CUSTOMTYPE_ZAP
CAppWizStepDlg* C$$Safe_root$$AppWiz::Next(CAppWizStepDlg* pDlg)
{
$$IF(CUSTOMTYPE_ZAP)
	ASSERT(pDlg == NULL);   // By default, this custom AppWizard has no steps

	// Set template macros based on the project name entered by the user.

	// Get value of $$$$root$$$$ (already set by AppWizard)
	CString strRoot;
	m_Dictionary.Lookup(_T("root"), strRoot);

	// Set value of $$$$Doc$$$$, $$$$DOC$$$$
	CString strDoc = strRoot.Left(6);
	m_Dictionary[_T("Doc")] = strDoc;
	strDoc.MakeUpper();
	m_Dictionary[_T("DOC")] = strDoc;

	// Set value of $$$$MAC_TYPE$$$$
	strRoot = strRoot.Left(4);
	int nLen = strRoot.GetLength();
	if (strRoot.GetLength() < 4)
	{
		CString strPad(_T(' '), 4 - nLen);
		strRoot += strPad;
	}
	strRoot.MakeUpper();
	m_Dictionary[_T("MAC_TYPE")] = strRoot;

	// Return NULL to indicate there are no more steps.  (In this case, there are
	//  no steps at all.)
	return NULL;
$$ELIF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
$$ELSE
	return NULL;
$$ENDIF //CUSTOMTYPE_ZAP/HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE
}
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* C$$Safe_root$$AppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}
$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE

void C$$Safe_root$$AppWiz::CustomizeProject(IBuildProject* pProject)
{
	// TODO: Add code here to customize the project.  If you don't wish
	//  to customize project, you may remove this virtual override.

	// This is called immediately after the default Debug and Release
	//  configurations have been created for each platform.  You may customize
	//  existing configurations on this project by using the methods
	//  of IBuildProject and IConfiguration such as AddToolSettings,
	//  RemoveToolSettings, and AddCustomBuildStep. These are documented in
	//  the Developer Studio object model documentation.

	// WARNING!!  IBuildProject and all interfaces you can get from it are OLE
	//  COM interfaces.  You must be careful to release all new interfaces
	//  you acquire.  In accordance with the standard rules of COM, you must
	//  NOT release pProject, unless you explicitly AddRef it, since pProject
	//  is passed as an "in" parameter to this function.  See the documentation
	//  on CCustomAppWiz::CustomizeProject for more information.
}


// Here we define one instance of the C$$Safe_root$$AppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global $$safe_root$$aw.
C$$Safe_root$$AppWiz $$safe_root$$aw;
