// threadlibtestView.cpp : implementation of the CThreadlibtestView class
//

#include <stdlib.h>  // for the rand stuff...
#include "stdafx.h"
#include <windows.h>

#include <winnls.h>



#include "easyview.h"
#include "threadlibtest.h"

#include "threadlibtestDoc.h"
#include "threadlibtestView.h"

#include "NoThreadDialog.h"

#include "xl5en32.h"


#define APP_CALLING
#include "thrdlib.h"
#undef APP_CALLING

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEXTFILELOC "c:\\temp\\results.fil"
#define SHEETFILELOC OLESTR("c:\\temp\\values.xls")

int iStartIndex, iEndIndex;
BOOL bCPUBound;

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestView

IMPLEMENT_DYNCREATE(CThreadlibtestView, CEasyOutputView)

BEGIN_MESSAGE_MAP(CThreadlibtestView, CEasyOutputView)
	//{{AFX_MSG_MAP(CThreadlibtestView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_CONCURRENT, OnConcurrent)
	ON_COMMAND(IDM_SERIAL, OnSerial)
	ON_COMMAND(ID_SETUPPARAMETERS_CONSTANTDELAYS, OnSetupparametersConstantdelays)
	ON_COMMAND(ID_SETUPPARAMETERS_RANDOMDELAYS, OnSetupparametersRandomdelays)
	ON_COMMAND(IDM_SETNOTHREADS, OnSetnothreads)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_WORSTCASE, OnWorstcase)
	ON_COMMAND(IDM_SINGLETEST, OnSingletest)
	ON_COMMAND(IDM_MULTIPLE, OnMultiple)
	ON_COMMAND(IDM_DOALL, OnDoall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestView construction/destruction

CThreadlibtestView::CThreadlibtestView()
{
 m_iDelay=500;
 m_iNumberOfThreads=10;
 m_iCompType=0;
}

CThreadlibtestView::~CThreadlibtestView()
{
}

BOOL CThreadlibtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CEasyOutputView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestView drawing

void CThreadlibtestView::OnDraw(CDC* pDC)
{
	CThreadlibtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestView diagnostics

#ifdef _DEBUG
void CThreadlibtestView::AssertValid() const
{
	CEasyOutputView::AssertValid();
}

void CThreadlibtestView::Dump(CDumpContext& dc) const
{
	CEasyOutputView::Dump(dc);
}

CThreadlibtestDoc* CThreadlibtestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadlibtestDoc)));
	return (CThreadlibtestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThreadlibtestView message handlers



extern "C"
{


long WINAPI pProcessor(long iArg)
{
 PTHREADBLOCKSTRUCT ptArg=(PTHREADBLOCKSTRUCT)iArg;
 BOOL bResult=TRUE;
 int iDelay=(ptArg->iDelay);
 if (bCPUBound) 
 {
  int iLoopCount;
  iLoopCount=(int)(((float)iDelay/1000.0)*ptArg->tbOutputTarget->m_iBiasFactor);
  QueryPerformanceCounter(&ptArg->liStart);
  for (int iCounter=0; iCounter<iLoopCount; iCounter++);
 }
 else
 { 
   QueryPerformanceCounter(&ptArg->liStart);
   Sleep(ptArg->iDelay);
 };
 return bResult;
}

long WINAPI pTerminator(long iArg, long iReturnCode)
{
 PTHREADBLOCKSTRUCT ptArg=(PTHREADBLOCKSTRUCT)iArg;
 QueryPerformanceCounter(&ptArg->liFinish);
 ptArg->iEndOrder=iEndIndex++;
 return(0);
}

}

int CThreadlibtestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEasyOutputView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!QueryPerformanceFrequency(&m_liOldVal))
    {
     AfxMessageBox("performance counting not supported...");
     return -1;
    };
 m_iCounterResolution=1000.0/(float)m_liOldVal.LowPart;
// now we have the resolution of the timer...
 AddStringandAdjust("please wait while the clock cycle performance is evaluated...");
 LARGE_INTEGER liStart,liEnd;
 m_iBiasFactor=0.0;
 UINT uiSampleIts=100000;
#define SAMPLELOOPS 100
 for (int i=0;i<SAMPLELOOPS;i++)
 {
  QueryPerformanceCounter(&liStart);
  for (int iLoop=0;iLoop<uiSampleIts;iLoop++);
  QueryPerformanceCounter(&liEnd);
  m_iBiasFactor+=(float)(liEnd.LowPart-liStart.LowPart);
 };
 m_iBiasFactor/=SAMPLELOOPS;
 float fBiasFactor=(float)m_liOldVal.LowPart*(float)uiSampleIts;
 m_iBiasFactor = fBiasFactor/m_iBiasFactor;
 sprintf(m_szBuf,"determined an iteration to be %6.8f",m_iBiasFactor);
 AddStringandAdjust(m_szBuf);
 return 0;
}

void CThreadlibtestView::OnConcurrent() 
{
    m_iThreadCounter = m_iNumberOfThreads;
    m_iCompType|=CT_CONCURRENT;

}

void CThreadlibtestView::OnSerial() 
{
    m_iThreadCounter = m_iNumberOfThreads;
    m_iCompType&=(0xffffffff&(~CT_CONCURRENT));
}


void CThreadlibtestView::OnSetupparametersConstantdelays() 
{
    if(!m_iNumberOfThreads) 
    {
     MessageBeep(-1);
     return;
    }; 

    for (int iLoop=0;iLoop<m_iNumberOfThreads;iLoop++)
	{
	 m_iNumbers[iLoop]=(int)&m_tbConc[iLoop];
	 m_tbConc[iLoop].iId=iLoop;
	 m_tbConc[iLoop].iDelay=m_iAverageDelay*m_iDelay;
	 m_tbConc[iLoop].tbOutputTarget=this;
     m_tbConc[iLoop].iStartOrder=0;
     m_tbConc[iLoop].iEndOrder=0;
     m_tbConc[iLoop].iTouchCount=0;
	};
	
}

void CThreadlibtestView::OnSetupparametersRandomdelays() 
{
    srand( (unsigned)time( NULL ) );
    if(!m_iNumberOfThreads) 
    {
     MessageBeep(-1);
     return;
    }; 
    int iDelaySum=0;
    unsigned int iCurrentDelay;

    for (int iLoop=0;iLoop<m_iNumberOfThreads;iLoop++)
	{
	 m_iNumbers[iLoop]=(int)&m_tbConc[iLoop];
	 m_tbConc[iLoop].iId=iLoop;
     iCurrentDelay=rand()%m_iDelay;
     iDelaySum+=iCurrentDelay;
	 m_tbConc[iLoop].iDelay=iCurrentDelay;
	 m_tbConc[iLoop].tbOutputTarget=this;
     m_tbConc[iLoop].iStartOrder=0;
     m_tbConc[iLoop].iEndOrder=0;
     m_tbConc[iLoop].iTouchCount=0;
	};
    m_iAverageDelay=iDelaySum/m_iNumberOfThreads;
}

void CThreadlibtestView::OnSetnothreads() 
{
 CNoThreadDialog cNoD;
 cNoD.m_NoThreads=m_iNumberOfThreads;
 cNoD.m_Delay=m_iDelay;
 cNoD.m_iCompType=(m_iCompType&(0xffffffff&(~CT_CPUBOUND)&(~CT_IOBOUND)));
 cNoD.DoModal();
 m_iNumberOfThreads = cNoD.m_NoThreads;
 m_iDelay = cNoD.m_Delay;
 m_iCompType|=((cNoD.m_iCompType==IDC_IOBOUND)?CT_IOBOUND:CT_CPUBOUND);
}

void CThreadlibtestView::OnDestroy() 
{
	CEasyOutputView::OnDestroy();
	
}

void CThreadlibtestView::OnWorstcase() 
{
    if(!m_iNumberOfThreads) 
    {
     MessageBeep(-1);
     return;
    }; 

    for (int iLoop=0;iLoop<m_iNumberOfThreads;iLoop++)
	{
	 m_iNumbers[iLoop]=(int)&m_tbConc[iLoop];
	 m_tbConc[iLoop].iId=iLoop;
	 m_tbConc[iLoop].iDelay=m_iDelay*(m_iNumberOfThreads-iLoop);  // bugbug...
	 m_tbConc[iLoop].tbOutputTarget=this;
     m_tbConc[iLoop].iStartOrder=0;
     m_tbConc[iLoop].iEndOrder=0;
     m_tbConc[iLoop].iTouchCount=0;
	};
	
}


void CThreadlibtestView::ExecuteTest()
{
    ConcurrentExecution *ce;
	bCPUBound=((m_iCompType&CT_IOBOUND)==0);
	ce = new ConcurrentExecution(25);
    if (!QueryPerformanceCounter(&m_liOldVal)) return;  // here's the current value...
    if (m_iCompType&CT_CONCURRENT)
    m_iThreadsUsed=ce->DoForAllObjects(m_iNumberOfThreads,(long *)m_iNumbers,(CONCURRENT_EXECUTION_ROUTINE)pProcessor,
		                                    (CONCURRENT_FINISHING_ROUTINE)pTerminator);
    else
    ce->DoSerial(m_iNumberOfThreads,(long *)m_iNumbers,(CONCURRENT_EXECUTION_ROUTINE)pProcessor,
		                                    (CONCURRENT_FINISHING_ROUTINE)pTerminator);
 	delete(ce);
// determine actual results
    for (int iLoop=0;iLoop<m_iNumberOfThreads;iLoop++)
    {
     LARGE_INTEGER liElapsed;
     LARGE_INTEGER liTurnaround;
//liElapsed is the absolute amount of time elapsed for each
//computation
     liElapsed.HighPart=m_tbConc[iLoop].liFinish.HighPart-m_tbConc[iLoop].liStart.HighPart;
     liElapsed.LowPart=m_tbConc[iLoop].liFinish.LowPart-m_tbConc[iLoop].liStart.LowPart;
//liTurnaround is the time elapsed from the beginning of all computations
// until the end of that computation
     liTurnaround.LowPart=m_tbConc[iLoop].liFinish.LowPart-m_liOldVal.LowPart;
     liTurnaround.HighPart=m_tbConc[iLoop].liFinish.HighPart-m_liOldVal.HighPart;
     if (m_tbConc[iLoop].iEndOrder==m_iNumberOfThreads-1)
     { // this is the last thread that ended...
      m_liElapsedSum.LowPart=liTurnaround.LowPart;
      m_liElapsedSum.HighPart=liTurnaround.HighPart;
     };
     m_fTurnAround+=((float)liTurnaround.LowPart*m_iCounterResolution)/(float)m_tbConc[iLoop].iDelay;
    }; // end of for loop
    m_fTurnAround/=m_iNumberOfThreads;
}
void CThreadlibtestView::OnSingletest() 
{   
    m_liElapsedSum.HighPart=0;
    m_liElapsedSum.LowPart=0;
    m_fTurnAround=0;
    m_iNumberOfTests=1;
    iStartIndex=0;
    iEndIndex=0;
    m_iThreadsUsed=0;
    ExecuteTest();

	
}

#define TESTRUNS 10

void CThreadlibtestView::OnMultiple() 
{
  m_liSum.HighPart=0; m_liSum.LowPart=0;m_fSum=0;
  for (int iLoop=0;iLoop<TESTRUNS;iLoop++)
  {
   OnSingletest();
   m_liSum.HighPart+=m_liElapsedSum.HighPart;
   m_liSum.LowPart+=m_liElapsedSum.LowPart;
   m_fSum+=m_fTurnAround;
  };
  m_liSum.HighPart/=TESTRUNS;
  m_liSum.LowPart/=TESTRUNS;
  m_fSum/=(float)TESTRUNS;
  sprintf(m_szBuf,"****************************************");
  AddStringandAdjust(m_szBuf);
  sprintf(m_szBuf,"total: %d %8lu, %6.6f",m_liSum.HighPart,m_liSum.LowPart,m_fSum);
  AddStringandAdjust(m_szBuf);
  sprintf(m_szBuf,"****************************************");
  AddStringandAdjust(m_szBuf);
	
}


#define DUMPIT  WriteFile(hFile,m_szBuf,strlen(m_szBuf),&bytesWritten,NULL)


void CThreadlibtestView::OnDoall() 
{
 // I know, I could use enums here... just
 // too lazy, I guess...
m_iCurrentIndex=0;
 // loop through numbers of threads
for (int iBiasCount=INITIALBIAS;iBiasCount<ENDBIAS;iBiasCount*=BIASOFFSET)
 {
   m_iDelay = iBiasCount;
  for (int iThreadCount=INITIALTHREADCT;iThreadCount<ENDTHREADCT;iThreadCount+=THREADOFFSET)
 // loop through delay biasses 
  {
   m_iNumberOfThreads = iThreadCount;
   OnWorstcase();
   OnSerial();  
   m_iCompType|=CT_IOBOUND;
   OnMultiple(); // first test
// this repetitive group of statements fills
// an array field with the respective values
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_NOTHREADS][AC_IOBOUND]=(float)iThreadCount;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_NODELAY][AC_IOBOUND]=(float)iBiasCount;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_ELAPSED][AC_IOBOUND]=(float)m_liSum.LowPart*m_iCounterResolution;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_RESPONSE][AC_IOBOUND]=(float)m_fSum;
// end of repetitive group   
   m_iCompType&=0xffff&~CT_IOBOUND;

   OnMultiple(); // second test
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_NOTHREADS][AC_CPUBOUND]=(float)iThreadCount;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_NODELAY][AC_CPUBOUND]=(float)iBiasCount;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_ELAPSED][AC_CPUBOUND]=(float)m_liSum.LowPart*m_iCounterResolution;
   m_iValues[m_iCurrentIndex][AC_SERIAL][AC_RESPONSE][AC_CPUBOUND]=(float)m_fSum;
   OnConcurrent(); 
   m_iCompType|=CT_IOBOUND;
   OnMultiple(); // third test
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_NOTHREADS][AC_IOBOUND]=(float)iThreadCount;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_NODELAY][AC_IOBOUND]=(float)iBiasCount;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_ELAPSED][AC_IOBOUND]=(float)m_liSum.LowPart*m_iCounterResolution;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_RESPONSE][AC_IOBOUND]=(float)m_fSum;
   m_iCompType&=0xffff&~CT_IOBOUND;
   OnMultiple(); // fourth test
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_NOTHREADS][AC_CPUBOUND]=(float)iThreadCount;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_NODELAY][AC_CPUBOUND]=(float)iBiasCount;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_ELAPSED][AC_CPUBOUND]=(float)m_liSum.LowPart*m_iCounterResolution;
   m_iValues[m_iCurrentIndex][AC_CONCURRENT][AC_RESPONSE][AC_CPUBOUND]=(float)m_fSum;
   m_iCurrentIndex++;
   };
  };
 // tests are done! Now dump the results into a file...
  DumpValues();
    StuffIntoExcel();
 };

 void CThreadlibtestView::DumpValues()
 {
 HANDLE hFile;
 DWORD bytesWritten;
 hFile=CreateFile(TEXTFILELOC,
                  GENERIC_READ|GENERIC_WRITE,
                  FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,
                  CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
 sprintf(m_szBuf,"Concurrent tests:\n\r");
 DUMPIT;
 sprintf(m_szBuf,"I/O bound results:\n\r");
 DUMPIT;
 for (int iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  sprintf(m_szBuf,"%d threads w/ bias %d: elapsed %6.1f, response %6.6f\n\r",
          (int)m_iValues[iLoop][AC_CONCURRENT][AC_NOTHREADS][AC_IOBOUND],
          (int)m_iValues[iLoop][AC_CONCURRENT][AC_NODELAY][AC_IOBOUND],
          m_iValues[iLoop][AC_CONCURRENT][AC_ELAPSED][AC_IOBOUND],
          m_iValues[iLoop][AC_CONCURRENT][AC_RESPONSE][AC_IOBOUND]);
  DUMPIT;
 };
 sprintf(m_szBuf,"CPU bound results:\n\r");
 DUMPIT;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  sprintf(m_szBuf,"%d threads w/ bias %d: elapsed %6.1f, response %6.6f\n\r",
          (int)m_iValues[iLoop][AC_CONCURRENT][AC_NOTHREADS][AC_CPUBOUND],
          (int)m_iValues[iLoop][AC_CONCURRENT][AC_NODELAY][AC_CPUBOUND],
          m_iValues[iLoop][AC_CONCURRENT][AC_ELAPSED][AC_CPUBOUND],
          m_iValues[iLoop][AC_CONCURRENT][AC_RESPONSE][AC_CPUBOUND]);
  DUMPIT;
 };
 sprintf(m_szBuf,"Serial tests:\n\r");
 DUMPIT;
 sprintf(m_szBuf,"I/O bound results:\n\r");
 DUMPIT;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  sprintf(m_szBuf,"%d threads w/ bias %d: elapsed %6.1f, response %6.6f\n\r",
          (int)m_iValues[iLoop][AC_SERIAL][AC_NOTHREADS][AC_IOBOUND],
          (int)m_iValues[iLoop][AC_SERIAL][AC_NODELAY][AC_IOBOUND],
          m_iValues[iLoop][AC_SERIAL][AC_ELAPSED][AC_IOBOUND],
          m_iValues[iLoop][AC_SERIAL][AC_RESPONSE][AC_IOBOUND]);
  DUMPIT;
 };
 sprintf(m_szBuf,"CPU bound results:\n\r");
 DUMPIT;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  sprintf(m_szBuf,"%d threads w/ bias %d: elapsed %6.1f, response %6.6f\n\r",
          (int)m_iValues[iLoop][AC_SERIAL][AC_NOTHREADS][AC_CPUBOUND],
          (int)m_iValues[iLoop][AC_SERIAL][AC_NODELAY][AC_CPUBOUND],
          m_iValues[iLoop][AC_SERIAL][AC_ELAPSED][AC_CPUBOUND],
          m_iValues[iLoop][AC_SERIAL][AC_RESPONSE][AC_CPUBOUND]);
  DUMPIT;
 };
		   
 CloseHandle(hFile);
// StuffIntoExcel();	
}

#define STRCONVERT_MAXLEN 500

#ifdef UNICODE
OLECHAR* ConvertToUnicode(char FAR* szA)
{
  return szA; 
}

#else
OLECHAR* ConvertToUnicode(char FAR* szA)
{
  static OLECHAR achW[STRCONVERT_MAXLEN]; 

  MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, STRCONVERT_MAXLEN);  
  return achW; 
}
#endif

OLECHAR * MakeCellIndex(char *letter, int iIndex)
{
 char szBuf[6];   // BUGBUG - don't hardcode
 wsprintf(szBuf,"%s%d",letter,iIndex);
 return ConvertToUnicode(szBuf);
};


// this code is adapted from the XLCLIENT code sample...

// this macro allocates a cell using the Range object

#define ALLOCRANGE(cell) \
    VariantClear(&v); \
   V_VT(&v) = VT_BSTR; \
   V_BSTR(&v) = SysAllocString(cell); \
   vRet = ws->Range(v,v); \
   SysFreeString(V_BSTR(&v));

// this macro stuffs a string into a cell
#define PUTSTR(cell,str) \
ALLOCRANGE(cell)  \
V_VT(&v) = VT_BSTR; \
V_BSTR(&v) = SysAllocString(OLESTR(str)); \
ptr = new Range(V_DISPATCH(&vRet)); \
ptr->SetValue(v); \
SysFreeString(V_BSTR(&v)); \
delete ptr; 
  

// this macro stuffs a float into a cell
#define PUTFLT(cell,flt) \
ALLOCRANGE(cell)  \
V_VT(&v) = VT_R8; \
V_R8(&v) = flt; \
ptr = new Range(V_DISPATCH(&vRet)); \
ptr->SetValue(v); \
delete ptr;


// this macro stuffs an integer into a cell
#define PUTINT(cell, ival)  \
ALLOCRANGE(cell)  \
V_VT(&v) = VT_I4; \
V_I4(&v) = (int)ival; \
ptr = new Range(V_DISPATCH(&vRet)); \
ptr->SetValue(v); \
delete ptr;


void CThreadlibtestView::StuffIntoExcel()
{   

	VARIANT v, vRet;
    Range *ptr;
// part 1: Create Excel sheet object to work with

Worksheet *ws = new Worksheet();
if (!ws->CreateDispatch("Excel.Sheet"))
{
 AfxMessageBox("couldn't create sheet object...");
 return;
};  

// part 2: Assign headings the array to cells

// I know that using arrays would be more efficient here...
// at this point, I'm looking for the minimal effort to
// stuff data into Excel, leave the finetuning to
// automation heads...
int iNextIndex=3;
int iLoop;

PUTSTR(OLESTR("A1"),"Threads");
PUTSTR(OLESTR("B1"),"Bias");
PUTSTR(OLESTR("C1"),"Elapsed time");
PUTSTR(OLESTR("D1"),"Response");
PUTSTR(OLESTR("A2"),"Concurrent");
PUTSTR(OLESTR("B2"),"I/O bound");
char szIndexValue[20];   // BUGBUG - don't hardcode
// we need to reserve m_iCurrentIndex lines here to
// stuff the values in
iNextIndex+=m_iCurrentIndex;
//iNextIndex+=1;
PUTSTR(MakeCellIndex("B",iNextIndex),"CPU bound");
iNextIndex+=m_iCurrentIndex;
iNextIndex+=1;
PUTSTR(MakeCellIndex("A",iNextIndex),"Serial");
PUTSTR(MakeCellIndex("B",iNextIndex),"I/O bound");
iNextIndex+=m_iCurrentIndex;
iNextIndex+=1;
PUTSTR(MakeCellIndex("B",iNextIndex),"CPU bound");


// part 3 - assign the values

// 3.1 - dump concurrent I/O bound
iNextIndex=3;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  PUTINT(MakeCellIndex("A",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_CONCURRENT][AC_NOTHREADS][AC_IOBOUND]);
  PUTINT(MakeCellIndex("B",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_CONCURRENT][AC_NODELAY][AC_IOBOUND]);
  PUTFLT(MakeCellIndex("C",iNextIndex+iLoop),m_iValues[iLoop][AC_CONCURRENT][AC_ELAPSED][AC_IOBOUND]);
  PUTFLT(MakeCellIndex("D",iNextIndex+iLoop),m_iValues[iLoop][AC_CONCURRENT][AC_RESPONSE][AC_IOBOUND]);
 };


// 3.2 - dump concurrent CPU bound
iNextIndex+=iLoop;
iNextIndex+=1;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  PUTINT(MakeCellIndex("A",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_CONCURRENT][AC_NOTHREADS][AC_CPUBOUND]);
  PUTINT(MakeCellIndex("B",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_CONCURRENT][AC_NODELAY][AC_CPUBOUND]);
  PUTFLT(MakeCellIndex("C",iNextIndex+iLoop),m_iValues[iLoop][AC_CONCURRENT][AC_ELAPSED][AC_CPUBOUND]);
  PUTFLT(MakeCellIndex("D",iNextIndex+iLoop),m_iValues[iLoop][AC_CONCURRENT][AC_RESPONSE][AC_CPUBOUND]);
 };


// 3.3 - dump serial I/O bound

iNextIndex+=iLoop;
iNextIndex+=1;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  PUTINT(MakeCellIndex("A",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_SERIAL][AC_NOTHREADS][AC_IOBOUND]);
  PUTINT(MakeCellIndex("B",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_SERIAL][AC_NODELAY][AC_IOBOUND]);
  PUTFLT(MakeCellIndex("C",iNextIndex+iLoop),m_iValues[iLoop][AC_SERIAL][AC_ELAPSED][AC_IOBOUND]);
  PUTFLT(MakeCellIndex("D",iNextIndex+iLoop),m_iValues[iLoop][AC_SERIAL][AC_RESPONSE][AC_IOBOUND]);
 };

// 3.4 - dump serial CPU bound

iNextIndex+=iLoop;
iNextIndex+=1;
 for (iLoop=0;iLoop<m_iCurrentIndex;iLoop++)
 {
  PUTINT(MakeCellIndex("A",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_SERIAL][AC_NOTHREADS][AC_CPUBOUND]);
  PUTINT(MakeCellIndex("B",iNextIndex+iLoop),(int)m_iValues[iLoop][AC_SERIAL][AC_NODELAY][AC_CPUBOUND]);
  PUTFLT(MakeCellIndex("C",iNextIndex+iLoop),m_iValues[iLoop][AC_SERIAL][AC_ELAPSED][AC_CPUBOUND]);
  PUTFLT(MakeCellIndex("D",iNextIndex+iLoop),m_iValues[iLoop][AC_SERIAL][AC_RESPONSE][AC_CPUBOUND]);
 };



// part 4 - save the sheet

    VARIANT v11,v12,v13,v14,v15,v16;
    V_VT(&v11) = VT_BSTR;
    V_BSTR(&v11)=SysAllocString(SHEETFILELOC);
    V_VT(&v12) = VT_I2;
    V_I2(&v12) = -4143;
    V_VT(&v13) = VT_BSTR;
    V_BSTR(&v13) = NULL;
    V_VT(&v14) = VT_BSTR;
    V_BSTR(&v14) = NULL;
    V_VT(&v15) = VT_BOOL;
    V_BOOL(&v15)=FALSE;
    V_VT(&v16) = VT_BOOL;
    V_BOOL(&v16) = FALSE;
     ws->SaveAs(v11,v12,v13,v14,v15,v16);
    SysFreeString(V_BSTR(&v11));
    delete ws;
	AddStringandAdjust("finished protocoling results...");  
    return; // Fail
}
