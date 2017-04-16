// CXAppWizStepDlg -- defines a derived class from CAppWizStepDlg

class CXAppWizStepDlg : public CAppWizStepDlg
{
 public:
 CXAppWizStepDlg(UINT nIDTemplate) : CAppWizStepDlg(nIDTemplate)
 {
 };
 ~CXAppWizStepDlg()
 {
 };
 virtual BOOL SetDefaults()
 {
  OnInitDialog();
  OnDismiss();
  return TRUE;
 };
};