// (From modified TRACEWIN source, mainfrm.cpp)
//

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_MESSAGE(WM_COPYDATA, OnTraceMsg)
	.
	.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////
// Someone sent me a WM_COPYDATA message: display it.
//
LRESULT CMainFrame::OnTraceMsg(WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;
	if (m_nOutputWhere==ID_OUTPUT_OFF || pcds->dwData!=ID_COPYDATA_TRACEMSG)
		return 0;

	const char* lpText = (const char*)pcds->lpData;
	DWORD len = pcds->cbData;

	if (m_nOutputWhere==ID_OUTPUT_TO_WINDOW) {
		// Convert \n to \n\r for Windows brain-damaged edit control
		// It's 1995, and I'm still writing code like this!
		//
		const char* src = lpText;
		const char* endsrc = lpText + len;

		char buf[1024];
		char* dst = buf;
		char* endbuf = buf + sizeof(buf) - 1;

		while (src < endsrc && dst < endbuf) {
			if (*src == '\n')
				*dst++ = '\r';
			*dst++ = *src++;
		}
		*dst = 0;

		// Append string to contents of trace buffer
		m_wndBuffer.SetSel(-1, -1);		// end of edit text
		m_wndBuffer.ReplaceSel(buf);		// append string..
		m_wndBuffer.SendMessage(EM_SCROLLCARET);	// ..and show caret

	} else if (m_nOutputWhere==ID_OUTPUT_TO_FILE) {
		m_file.Write(lpText, len);

	}

	return 0;
}
