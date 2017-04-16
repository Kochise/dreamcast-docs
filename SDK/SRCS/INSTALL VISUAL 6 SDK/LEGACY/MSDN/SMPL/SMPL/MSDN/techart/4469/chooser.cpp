// chooser.cpp : Implements the CDialogChooser class
//

#include "stdafx.h"
#include "NtDDWzd.h"
#include "chooser.h"
#include "cstm1dlg.h"

#include "resource.h"  // for the constants used in cstmdlg2.h

#include "cstm2dlg.h"
#include "cstm3dlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;

	m_pDlgs[1] = new CCustom1Dlg;
	m_pDlgs[2] = new CCustom2Dlg;
	m_pDlgs[3] = new CCustom3Dlg(0);

	m_nCurrDlg = 0;
    m_iAddlSteps = 0;
}
// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP 1
#define LAST_CUSTOM_STEP 3

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
	NukeAddlStepArray();
}

// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	if (m_nCurrDlg <LAST_DLG)
//	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < LAST_DLG);
//	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
    {
	 m_nCurrDlg++;
	 return m_pDlgs[m_nCurrDlg];
	}
	else
	{
	 if (m_nCurrDlg>LAST_DLG+m_iAddlSteps) return (CAppWizStepDlg*)NULL;
	 m_nCurrDlg++;
	 return m_iNewStepArray[m_nCurrDlg-LAST_DLG-1];
	};
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
//	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= LAST_DLG);
//	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
    if (1>=m_nCurrDlg) return (CAppWizStepDlg*)NULL;
	if (m_nCurrDlg<=LAST_DLG)
	{
	 m_nCurrDlg--;
	 return m_pDlgs[m_nCurrDlg];
	}
	else
	{
	 m_nCurrDlg--;
	 if (m_nCurrDlg==LAST_DLG) return m_pDlgs[LAST_DLG];
	 else return m_iNewStepArray[m_nCurrDlg-LAST_DLG-1];
	};
}

BOOL CDialogChooser::RegisterNewSteps(int i)
{
 NukeAddlStepArray();
 m_iAddlSteps = i;
 // RAc -- check return value
 m_iNewStepArray=(CAppWizStepDlg **)malloc(m_iAddlSteps*sizeof(CAppWizStepDlg *));
 for (int iLoop=1;iLoop<=i;iLoop++)
  m_iNewStepArray[iLoop-1]= new CCustom3Dlg(iLoop);
 return TRUE;
}

void CDialogChooser::NukeAddlStepArray()
{
 if (m_iAddlSteps==0) return;
 for (int iLoop=0;iLoop<m_iAddlSteps;iLoop++)
  delete m_iNewStepArray[iLoop];
 m_iAddlSteps=0;
 free(m_iNewStepArray);
}