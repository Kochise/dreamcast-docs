// chooser.cpp : Implements the CDialogChooser class
//
// This class is where you set up the sequence of steps that will
// be followed in your custom AppWizard.  These steps can include
// both standard AppWizard steps and your own custom steps.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "logowiz.h"
#include "chooser.h"
#include "cstm1dlg.h"
#include "logowaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DOC_TRACK   0   // MDI/SDI based app track
#define DLG_TRACK   1   // dialog based app track

// define the steps, since these are array indices, their values matter
#define STEP_ZERO           0
#define STEP_APPTYPE        1
//#define STEP_DATABASE     2   // closed gap 'cause we dropped this one
#define STEP_OLE            2
#define STEP_DOCOPTIONS     3
#define STEP_PROJOPTIONS    4
#define STEP_CLASSES        5
#define STEP_DLGOPTIONS     6
#define STEP_CUSTOM         7

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[STEP_ZERO] = NULL;

	m_pDlgs[STEP_APPTYPE] = GetDialog(APWZDLG_APPTYPE);
	// m_pDlgs[STEP_DATABASE] = GetDialog(APWZDLG_DATABASE);
	m_pDlgs[STEP_OLE] = GetDialog(APWZDLG_OLE);
	m_pDlgs[STEP_DOCOPTIONS] = GetDialog(APWZDLG_DOCAPPOPTIONS);
	m_pDlgs[STEP_PROJOPTIONS] = GetDialog(APWZDLG_PROJOPTIONS);
	m_pDlgs[STEP_CLASSES] = GetDialog(APWZDLG_CLASSES);
	m_pDlgs[STEP_DLGOPTIONS] = GetDialog(APWZDLG_DLGAPPOPTIONS);

	m_pDlgs[STEP_CUSTOM] = new CCustom1Dlg;

	m_nCurrDlg = STEP_ZERO;
	m_nTrack = DOC_TRACK;
}
// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP 7
#define LAST_CUSTOM_STEP 7

// Set up arrays of indices to simulate behavior of AppWizard (i.e., to have
//  separate "tracks" for an MDI/SDI app and a dialog-based app).
// There are two things being illustrated here:
//  1.  there is a custom step added for the dialog-based app
//  2.  the ODBC step is left out for the MDI/SDI app
//static int nDocTrack[] = {STEP_ZERO, STEP_APPTYPE, STEP_DATABASE,
//  STEP_OLE, STEP_DOCOPTIONS, STEP_PROJOPTIONS, STEP_CLASSES, STEP_CUSTOM};
static int nDocTrack[] = {STEP_ZERO, STEP_APPTYPE, STEP_OLE,
	STEP_DOCOPTIONS, STEP_PROJOPTIONS, STEP_CLASSES};
//static int nDlgTrack[] = {STEP_ZERO, STEP_APPTYPE, STEP_DLGOPTIONS, STEP_PROJOPTIONS, STEP_CLASSES, STEP_CUSTOM};
static int nDlgTrack[] = {STEP_ZERO, STEP_APPTYPE, STEP_DLGOPTIONS, STEP_PROJOPTIONS, STEP_CUSTOM, STEP_CLASSES};
static int* pnTrack[] = {nDocTrack, nDlgTrack};
//static int nLast[] = {STEP_CUSTOM, STEP_CLASSES};
static int nLast[] = {STEP_CLASSES, STEP_CLASSES};

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
	// NOTE: Be sure to delete all of your custom steps here, but don't delete
	//  any standard AppWizard steps you got through the GetDialog API.
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(m_nTrack == DOC_TRACK || m_nTrack == DLG_TRACK);
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	// If the current step is the "project type" step, the AppWizard "track" may
	//  have changed.
	if (m_nCurrDlg == STEP_APPTYPE)
	{
		CString strTemp;
		m_nTrack = logowizaw.m_Dictionary.Lookup(_T("PROJTYPE_DLG"), strTemp) ? 1 : 0;
		SetNumberOfSteps(nLast[m_nTrack]);
	}

	m_nCurrDlg++;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == STEP_APPTYPE)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(m_nTrack == DOC_TRACK || m_nTrack == DLG_TRACK);
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	m_nCurrDlg--;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == STEP_APPTYPE)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
}
