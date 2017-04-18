#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#define LAST_DLG $$MPDLGS_INDEX_LAST$$

class CDialogChooser
{
public:
	CDialogChooser();
$$IF(HAS_NEW_STEPS)
	~CDialogChooser();
$$ENDIF //HAS_NEW_STEPS

	// All calls by mfcapwz.dll to C$$Safe_root$$AppWiz::Next
	//  & C$$Safe_root$$AppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
$$IF(APWZSEQ_EXE)
	// Current step's index into the current track (defined in chooser.cpp).
$$ELSE //!APWZSEQ_EXE
	// Current step's index into the internal array m_pDlgs
$$ENDIF //APWZSEQ_EXE
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
$$IF(APWZSEQ_EXE)

	// Current track (MDI/SDI app or dialog-based app; see chooser.cpp).
	int m_nTrack;
$$ENDIF
};


//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
