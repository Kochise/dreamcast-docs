// Modified Write function from TRACEWIN.H
//
void CMfxTrace::Write(const void* lpBuf, UINT nCount)
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
		pTraceWnd->SendMessage(WM_COPYDATA, 
			(WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(), 
			(LPARAM)&cds);

	} else {
		// No trace window: do normal debug thing
		//
		::OutputDebugString((LPCSTR)lpBuf);	
	}
}
