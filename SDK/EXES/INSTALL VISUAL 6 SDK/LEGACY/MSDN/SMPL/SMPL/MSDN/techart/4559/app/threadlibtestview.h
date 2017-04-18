// threadlibtestView.h : interface of the CThreadlibtestView class
//
/////////////////////////////////////////////////////////////////////////////

class CThreadlibtestView;

#define NUMBEROFTHREADS 100

// these constants define the array positions
// of the respective results.
#define AC_NOTHREADS 0
#define AC_NODELAY 1
#define AC_ELAPSED 2
#define AC_RESPONSE 3
#define NUMBERITEMS AC_RESPONSE+1
#define AC_IOBOUND 0
#define AC_CPUBOUND 1
#define BOUNDTYPES AC_CPUBOUND+1
#define AC_SERIAL 0
#define AC_CONCURRENT 1
#define COMPTYPES AC_CONCURRENT+1

#define INITIALTHREADCT 2
#define ENDTHREADCT 20
#define THREADOFFSET 3

#define INITIALBIAS 10
#define ENDBIAS 5000
#define BIASOFFSET 3

#define NUMBERLOOPS (ENDTHREADCT/THREADOFFSET)*(ENDBIAS/BIASOFFSET)


typedef struct
{
 int iId;
 int iDelay;
 CThreadlibtestView *tbOutputTarget;
 LARGE_INTEGER liStart;
 LARGE_INTEGER liFinish;
 int iStartOrder, iEndOrder, iTouchCount;
} THREADBLOCKSTRUCT, *PTHREADBLOCKSTRUCT;

#define CT_SERIAL 0
#define CT_CONCURRENT 1
#define CT_CPUBOUND 0
#define CT_IOBOUND 2

class CThreadlibtestView : public CEasyOutputView
{
private:
    THREADBLOCKSTRUCT m_tbConc[NUMBEROFTHREADS];
    int m_iNumbers[NUMBEROFTHREADS];
    int m_iAverageDelay;
	int m_iCompType;
    int m_iNumberOfTests;
    int m_iThreadsUsed;
	int m_iCurrentIndex;
    float m_iCounterResolution;
	LARGE_INTEGER m_liSum;
    float m_fSum;
	float m_iValues[NUMBERLOOPS][COMPTYPES][NUMBERITEMS][BOUNDTYPES];


public:
    float m_iBiasFactor;
	LARGE_INTEGER m_liOldVal,m_liNewVal,m_liElapsedSum;
    float m_fTurnAround;
    int m_iNumberOfThreads;
    int m_iThreadCounter;
    int m_iDelay;
protected: // create from serialization only
    CThreadlibtestView();
	DECLARE_DYNCREATE(CThreadlibtestView)

// Attributes
public:
	CThreadlibtestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadlibtestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThreadlibtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    void ExecuteTest();
	void DumpValues();
	void StuffIntoExcel();
// Generated message map functions
protected:
	//{{AFX_MSG(CThreadlibtestView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnConcurrent();
	afx_msg void OnSerial();
	afx_msg void OnSetupparametersConstantdelays();
	afx_msg void OnSetupparametersRandomdelays();
	afx_msg void OnSetnothreads();
	afx_msg void OnDestroy();
	afx_msg void OnWorstcase();
	afx_msg void OnSingletest();
	afx_msg void OnMultiple();
	afx_msg void OnDoall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in threadlibtestView.cpp
inline CThreadlibtestDoc* CThreadlibtestView::GetDocument()
   { return (CThreadlibtestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
