// chooser.cpp : Implements the CDialogChooser class
//

#include "stdafx.h"
#include "$$root$$.h"
#include "chooser.h"
$$BEGINLOOP(NUM_NEW_STEPS)
#include "cstm$$ITERATOR$$dlg.h"
$$ENDLOOP
$$IF(APWZSEQ_EXE)
#include "$$filebase$$aw.h"
$$ENDIF //APWZSEQ_EXE

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;
$$IF(APWZSEQ_EXE)

	m_pDlgs[1] = GetDialog(APWZDLG_APPTYPE);
	m_pDlgs[2] = GetDialog(APWZDLG_DATABASE);
	m_pDlgs[3] = GetDialog(APWZDLG_OLE);
	m_pDlgs[4] = GetDialog(APWZDLG_DOCAPPOPTIONS);
	m_pDlgs[5] = GetDialog(APWZDLG_PROJOPTIONS);
	m_pDlgs[6] = GetDialog(APWZDLG_CLASSES);
	m_pDlgs[7] = GetDialog(APWZDLG_DLGAPPOPTIONS);
$$ELIF(APWZSEQ_DLL)

	m_pDlgs[1] = GetDialog(APWZDLG_DLLPROJOPTIONS);
$$ENDIF //APWZSEQ_EXE,_DLL
$$IF(HAS_NEW_STEPS)

$$BEGINLOOP(NUM_NEW_STEPS)
	m_pDlgs[$$MPDLGS_INDEX$$] = new CCustom$$ITERATOR$$Dlg;
$$ENDLOOP
$$ENDIF //HAS_NEW_STEPS

	m_nCurrDlg = 0;
$$IF(APWZSEQ_EXE)
	m_nTrack = 0;
$$ENDIF
}
$$IF(HAS_NEW_STEPS)
// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP $$MPDLGS_INDEX_0$$
#define LAST_CUSTOM_STEP $$MPDLGS_INDEX_LAST$$
$$ENDIF //HAS_NEW_STEPS
$$IF(APWZSEQ_EXE)

// Set up arrays of indices to simulate behavior of AppWizard (i.e., to have
//  separate "tracks" for an MDI/SDI app and a dialog-based app).
static int nDocTrack[] = {0, 1, 2, 3, 4, 5, 6$$CUSTOM_INDICES$$};
static int nDlgTrack[] = {0, 1, 7, 5, 6$$CUSTOM_INDICES$$};
static int* pnTrack[] = {nDocTrack, nDlgTrack};
static int nLast[] = {$$LAST_DOCTRACK_INDEX$$, $$LAST_DLGTRACK_INDEX$$};
$$ENDIF //APWZSEQ_EXE
$$IF(HAS_NEW_STEPS)

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
$$IF(CUSTOMTYPE_SEQUENCE)
	// NOTE: Be sure to delete all of your custom steps here, but don't delete
	//  any standard AppWizard steps you got through the GetDialog API.
$$ENDIF //CUSTOMTYPE_SEQUENCE
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}
$$ENDIF //HAS_NEW_STEPS

// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
$$IF(APWZSEQ_EXE)
	ASSERT(m_nTrack == 0 || m_nTrack == 1);
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	// If the current step is the "project type" step, the AppWizard "track" may
	//  have changed.
	if (m_nCurrDlg == 1)
	{
		CString strTemp;
		m_nTrack = $$safe_root$$aw.m_Dictionary.Lookup(_T("PROJTYPE_DLG"), strTemp) ? 1 : 0;
		SetNumberOfSteps(nLast[m_nTrack]);
	}

	m_nCurrDlg++;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == 1)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
$$ELSE //!APWZSEQ_EXE
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

	m_nCurrDlg++;
	return m_pDlgs[m_nCurrDlg];
$$ENDIF //APWZSEQ_EXE
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
$$IF(APWZSEQ_EXE)
	ASSERT(m_nTrack == 0 || m_nTrack == 1);
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	m_nCurrDlg--;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == 1)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
$$ELSE //!APWZSEQ_EXE
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

	m_nCurrDlg--;
	return m_pDlgs[m_nCurrDlg];
$$ENDIF //APWZSEQ_EXE
}
