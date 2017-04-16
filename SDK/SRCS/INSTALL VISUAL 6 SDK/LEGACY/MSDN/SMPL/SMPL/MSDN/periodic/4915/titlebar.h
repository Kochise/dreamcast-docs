struct TITLEPANE;				// fwd ref

//////////////////
// A titlebar is not really a window, just an object that manages title 
// bar "inidcators", which are like panes in the status bar.
//
class CTitleBar : public CCmdTarget {
	DECLARE_DYNAMIC(CTitleBar)
	TITLEPANE*	m_arPanes;		// array of "panes" (inidicators)
	UINT			m_nCount;		// #panes
	CString		m_sPrevTitle;	// previous title
	CString		m_sTitle;		// current title
public:
	CTitleBar();
	~CTitleBar();
	BOOL SetIndicators(const UINT* lpIDArray, int nIDCount);
	void OnIdleUpdate(CFrameWnd* pFrame, BOOL bDisableIfNoHndler);
};
