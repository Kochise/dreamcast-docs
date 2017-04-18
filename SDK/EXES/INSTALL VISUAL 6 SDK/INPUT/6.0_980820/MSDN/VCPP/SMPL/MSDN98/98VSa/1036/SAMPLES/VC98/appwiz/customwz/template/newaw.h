#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

// $$filebase$$aw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see $$root$$.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class C$$Safe_root$$AppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE

	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);
$$IF(HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE)

protected:
	CDialogChooser* m_pChooser;
$$ENDIF //HAS_NEW_STEPS || CUSTOMTYPE_SEQUENCE
};

// This declares the one instance of the C$$Safe_root$$AppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global $$Safe_root$$aw.  (Its definition is in $$filebase$$aw.cpp.)
extern C$$Safe_root$$AppWiz $$safe_root$$aw;

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
