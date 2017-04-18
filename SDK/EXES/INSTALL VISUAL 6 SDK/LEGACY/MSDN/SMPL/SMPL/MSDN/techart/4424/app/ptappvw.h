// ptappvw.h : interface of the CPtappView class
//
/////////////////////////////////////////////////////////////////////////////

typedef enum Libtypes {small_dll,large_dll,largefixup_dll};
typedef enum Basetypes {preferred_base=0,rebased_base=1};
typedef enum runtimesupport {no_runtime=0,static_runtime=1,dynamic_runtime=2};
typedef enum exports {no_exports, yes_exports};


class CPtappView : public CEasyOutputView
{
private:
    HINSTANCE m_hDLLInstance;
	HANDLE m_hFile, m_hFileMapping, m_hMutex;
	LPSTR m_lpImage;
	LARGE_INTEGER m_liOldVal,m_liNewVal,m_liDiffVal,m_liSum;
	unsigned long m_iReference;
	DWORD m_dwImageBase;
	DWORD m_dwImageSize;
	char m_pstrDLL[13];
	char m_pstrFullPathDLL[MAX_PATH];
	unsigned long m_dwMemSize;
	LPVOID m_lpMem;
	DWORD m_dwMinWorkSize, m_dwMaxWorkSize;
	int m_bTypeFlags[8];
	BOOL m_bObtainedMemoryThroughVirtualAlloc;
    LARGE_INTEGER m_liResults[3][2][3][2];

protected: // create from serialization only
	CPtappView();
	DECLARE_DYNCREATE(CPtappView)

// Attributes
public:
	CPtappDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtappView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPtappView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPtappView)
	afx_msg void OnLoaddll();
	afx_msg void OnLockrange();
	afx_msg void OnUnloaddll();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnUnlockrange();
	afx_msg void OnMultipletests();
	afx_msg void OnHogmemory();
	afx_msg void OnUnhogmem();
	afx_msg void OnSmalldll();
	afx_msg void OnLargefixed();
	afx_msg void OnLargenofixups();
	afx_msg void OnCrtsupport();
	afx_msg void OnFinishdll();
	afx_msg void OnUpdateCrtsupport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLargefixed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLargenofixups(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSmalldll(CCmdUI* pCmdUI);
	afx_msg void OnRunhogging();
	afx_msg void OnLockranegmultiple();
	afx_msg void OnLoaddllnofixups();
	afx_msg void OnDyncrtpre();
	afx_msg void OnUpdateDyncrtpre(CCmdUI* pCmdUI);
	afx_msg void OnHasexports();
	afx_msg void OnUpdateHasexports(CCmdUI* pCmdUI);
	afx_msg void OnBatch();
	afx_msg void OnCustomdll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
 public:
    BOOL MapFile(LPCTSTR);
	BOOL UnmapFile();
	friend int ThreadRoutine(CPtappView *);
	void OnLoadDllHelper(BOOL bDisplayResults);
	void DoMultipletests(Libtypes,runtimesupport,exports);
    void MapandSetupDllStuff();
};

#ifndef _DEBUG  // debug version in ptappvw.cpp
inline CPtappDoc* CPtappView::GetDocument()
   { return (CPtappDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
