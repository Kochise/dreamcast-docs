#ifndef _WINSAPP_
#define _WINSAPP_


class CWindowsList;

const long DEFAULTWIDTH = 200;

class CWinsApp : public CWinApp
{
public:
	CWinsApp() { 
		m_pWinMgr = NULL;
		m_fAutoDir  = FALSE;	
		m_fAutoSize  = FALSE;	
		m_fAutoVis  = FALSE;	
		m_iSortedCol = 0;
		m_lSize = DEFAULTWIDTH;	
	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinsApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWinsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetCommands(CWindowsList *pWindowsList) {m_pWinMgr = pWindowsList; };
	CWindowsList *GetCommands() {return(m_pWinMgr); };
	void SetAutoDir(BOOL fAutoDir) { m_fAutoDir = (DWORD)fAutoDir; }
	BOOL GetAutoDir() { return((BOOL)m_fAutoDir); };
	void SetAutoSize(BOOL fAutoSize) { m_fAutoSize = (DWORD)fAutoSize; }
	BOOL GetAutoSize() { return((BOOL)m_fAutoSize); };
	void SetAutoVis(BOOL fAutoVis) { m_fAutoVis = (DWORD)fAutoVis; }
	BOOL GetAutoVis() { return((BOOL)m_fAutoVis); };
	void SetSortedCol(long lSortedCol) { m_iSortedCol = lSortedCol; }
	long GetSortedCol() { return(m_iSortedCol); };
	long GetSize() { return(m_lSize); };
	void SetSize(long lSize) { m_lSize = lSize; };

protected:
	CWindowsList *m_pWinMgr;
	DWORD	m_fAutoDir;
	DWORD	m_fAutoSize;
	DWORD	m_fAutoVis;
	long	m_iSortedCol;
	long	m_lSize;
};


extern CWinsApp theApp;

#endif