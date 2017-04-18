class CMacroDialogBar :
   public CDialogBar
{
   DECLARE_DYNAMIC( CMacroDialogBar )

public:
   BOOL Create( CWnd* pParent, UINT nStyle, UINT nID );

protected:
   CSize CalcFixedLayout( BOOL tStretch, BOOL tHorz );

protected:
   CMacroComboBox m_cboxMacroName;

protected:
	DECLARE_MESSAGE_MAP()
};
