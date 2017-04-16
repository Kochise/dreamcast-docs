////////////////////////////////////////////////////////////////
// TRACEWIN Copyright 1995-1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// TRACEWIN is a development tool that displays MFC TRACE output in
// a window, even if you don't run under the debugger. To use tracewin,
// simply #include this file in your main .cpp file, the one that contains
// your CWinApp-derived app, and call 
//
//		MfxTraceInit();
//
// from your app's InitInstance function. You also need the TRACEWIN applet
// itself, which you can download from any MSJ bulletin board. NOTE: since 
// TraceWin.h contains code, you should only #include it in once place in
// your app. (Don't #include it in stdafx.h.)
//
// NOTE: I would have defined a static instance to initialize MfxTrace, so
// calling MfxTraceInit would be unecessary, but there's a problem with the
// order of intializations. CFileTrace requires that afxDump be initialized
// first, which can fail to happen if CFileTrace is initialized as a static
// object.
//
// Modification history
// 4-1-95:   Created
// 10-12-95: Use WM_COPYDATA instead of atoms. Also note the name of this 
//           file is changed to TRACEWIN.H.
// 11-10-95: Added "Keep WIndow on Top" feature and fixed a bug 
//           relating to saved window pos.
// 11-15-95: Save/Restore position with CWindowPlacement.
// 12-05-95: Implemented tracer object with "new" instead of static, so
//           it remains around for reporting memory leaks, if any.

#ifdef _WIN32	// TraceWin only used for WIN32

#define TRACEWND_CLASSNAME "MfxTraceWindow"

// This ID is sent as COPYDATASRUCT::dwData to identify the WM_COPYDATA
// message as coming from an app using TRACEWIN. 
//
#define ID_COPYDATA_TRACEMSG MAKELONG(MAKEWORD('t','w'),MAKEWORD('i','n'))

#ifdef _DEBUG

//////////////////
// CFileTrace looks like a CFile, but "writes" to the trace window
//
class CFileTrace : public CFile {
	CFileTrace()  { }			// private constructor
public:
	virtual void Write(const void* lpBuf, UINT nCount);
	static void Init();
};

/////////////////
// Initialize tracing. Replace global afxDump.m_pFile with me.
//
void CFileTrace::Init()
{
	// This initialization function creates the only instance ever
	// of a CFileTrace object, and it's never deleted. This gurantees
	// that when MFC gets around to reporting memory leaks, they will
	// show up in the TRACEWIN window. If I were to instantiate CFileTrace 
	// as a static object, it would be destructed before the CRT gets
	// around to reporting memory leaks, and the information would be lost.

	static CFileTrace* pTracer;
	if (afxDump.m_pFile == NULL) {
		// Since I don't want this allocation to be reported as a leak,
		// turn off memory tracking
		BOOL bEnable = AfxEnableMemoryTracking(FALSE);
		afxDump.m_pFile = pTracer = new CFileTrace; //&theTracer;
		AfxEnableMemoryTracking(bEnable);

	} else if (afxDump.m_pFile != pTracer)
		TRACE("afxDump is already using a file; TRACEWIN not installed.\n");
}

//////////////////
// Override to Write to TRACEWIN applet instead of file.
//
void CFileTrace::Write(const void* lpBuf, UINT nCount)
{
	if (!afxTraceEnabled)
		return;

	CWnd *pTraceWnd = CWnd::FindWindow(TRACEWND_CLASSNAME, NULL);
	if (pTraceWnd) {
		// Found Trace window: send string with WM_COPYDATA
		//
		COPYDATASTRUCT cds;
		cds.dwData = ID_COPYDATA_TRACEMSG;
		cds.cbData = nCount;
		cds.lpData = (void*)lpBuf;
		CWinApp* pApp = AfxGetApp();
		pTraceWnd->SendMessage(WM_COPYDATA, 
			pApp ? (WPARAM)pApp->m_pMainWnd->GetSafeHwnd() : 0,
			(LPARAM)&cds);

	} else {
		// No trace window: do normal debug thing
		::OutputDebugString((LPCSTR)lpBuf);	
	}
}

#define MfxTraceInit CFileTrace::Init

#else  // Not _DEBUG

#define MfxTraceInit()

#endif // _DEBUG

#else  // Not _WIN32

#define MfxTraceInit()

#endif // _WIN32
