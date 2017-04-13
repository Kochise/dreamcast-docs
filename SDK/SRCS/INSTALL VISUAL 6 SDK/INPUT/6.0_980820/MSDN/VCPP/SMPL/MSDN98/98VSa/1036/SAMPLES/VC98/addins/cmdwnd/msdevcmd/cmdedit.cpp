// CmdEdit.cpp : implementation file
//

#include "stdafx.h"
#include "msdevcmd.h"
#include "CmdEdit.h"
#include "io.h"
#include <objmodel\dbgdefs.h>
#include "CommandWindow.h"
#include "msdevcmddlg.h"

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning( disable : 4310 )  // Disable warning message: warning C4310: cast truncates constant value

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit

CCmdEdit::CCmdEdit()
{
	CString strCurr;
	UINT nID;

	// Command initialization
	m_rgCmds.SetAt(_T("?"), CmdHelp);
	m_rgCmds.SetAt(_T("Open"), CmdOpen);
	m_rgCmds.SetAt(_T("Close"), CmdClose);
	m_rgCmds.SetAt(_T("q"), CmdQuit);
	m_rgCmds.SetAt(_T("G"), CmdGo);
	m_rgCmds.SetAt(_T("s"), CmdStep);
	m_rgCmds.SetAt(_T("t"), CmdStepInto);
	m_rgCmds.SetAt(_T("bld"), CmdBuild);
	m_rgCmds.SetAt(_T("rb"), CmdRebuild);
	m_rgCmds.SetAt(_T("cd"), CmdCD);
	m_rgCmds.SetAt(_T("cls"), CmdCls);
	m_rgCmds.SetAt(_T("!"),  CmdDos);
	m_rgCmds.SetAt(_T("bl"), CmdBL );
	m_rgCmds.SetAt(_T("bc"), CmdBC );
	m_rgCmds.SetAt(_T("bp"), CmdBP );
	m_rgCmds.SetAt(_T("bd"), CmdBD );
	m_rgCmds.SetAt(_T("be"), CmdBE );

	for (nID = IDS_START; strCurr.LoadString(nID); nID++)
	{
		m_rgStrings.AddTail(strCurr);
	}

	// other initialization
	m_pDlgParent = NULL;

	// determine if we are running on Win95/98 or WinNT
    DWORD dwVersion = ::GetVersion();

    m_fWin4 = LOBYTE(dwVersion) > 3;
    m_fWin95 = m_fWin4 && (dwVersion & 0x80000000) != 0;

}

CCmdEdit::~CCmdEdit()
{
}


void CCmdEdit::SetParent(CMsdevcmdDlg *pParent)
{
	m_pDlgParent = pParent;
}


BOOL CCmdEdit::FHaveApp()
{
	CCommandWindow *pCmdWnd;
	
	pCmdWnd = theApp.GetCmd();
	if (pCmdWnd)
	{
		m_spApplication = pCmdWnd->GetApp();
	}
	return(m_spApplication != NULL);
}



void CCmdEdit::Append(LPCTSTR szText)
{
	CString strOut;

	strOut = _T("\r\n");
	strOut += szText;
	SetSel(-1, -1, TRUE);
	ReplaceSel(strOut);
}



BEGIN_MESSAGE_MAP(CCmdEdit, CEdit)
	//{{AFX_MSG_MAP(CCmdEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit message handlers

void CCmdEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CmdOp pCmd;

	if (nChar == _T('\n') || nChar == _T('\r'))
	{
		//process command.
		int iLine, cb;
		TCHAR *pch;
		
		pch = m_strCmd.GetBuffer(_MAX_PATH);
		iLine = LineFromChar(-1);
		cb = GetLine(iLine, pch, _MAX_PATH);
		pch[cb] = _T('\0');
		m_strCmd.ReleaseBuffer();
		if (!FParseCommand(m_strCmd, pCmd))
		{
			if (pCmd == CmdDos || !FSendCommandToMSDEV(m_strCmd))
			{
				SendCmdToDos(m_strCmd);
			}
		}
		 // don't need this if system call is changed to CreateProcess or _pipe.
		if (m_pDlgParent)
			m_pDlgParent->SetForegroundWindow();
	}
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


void CCmdEdit::SendCmdToDos(CString& rstrCmd)
{
	CString strTmp;
	CStdioFile fileTmp;
	CString strTmpFileName;
	CString strRes;

	strTmpFileName = _T("finXXXX");
	_tmktemp(strTmpFileName.GetBuffer(0));
	strTmpFileName.ReleaseBuffer();
	strTmpFileName += _T(".tmp");

	strTmp = rstrCmd;
	strTmp += _T(" > ");
	strTmp += strTmpFileName;
	if (!m_fWin95) // nt supports error redirection; win95/8 do not
	{
		strTmp += _T("  2>&1 ");
	}
	try
	{
		::system(strTmp); // consider changing this to either CreateProcess or _pipe.
		if (fileTmp.Open(strTmpFileName, CFile::modeRead))
		{
			
			while (fileTmp.ReadString(strRes))
			{
				Append(strRes);
			}
			Append(_T("\0"));
			
			fileTmp.Close();
			_tremove(strTmpFileName);
		}
	}
	catch(...)
	{
	}


}


BOOL CCmdEdit::FSendCommandToMSDEV(CString& rstrCmd)
{
	BOOL fOK = FALSE;
	HRESULT hr;

	if (FHaveApp())
	{
		CComBSTR bstrCmd = rstrCmd;

		hr = m_spApplication->ExecuteCommand(bstrCmd);
		fOK = SUCCEEDED(hr);
	}
	return(fOK);
}


BOOL CCmdEdit::FParseCommand(CString& rstrCmd, CmdOp& rpCmd)
{
	BOOL fParsed = FALSE;
	POSITION p;
	CString strCmd = rstrCmd;
	CString strCurr;
	CString strMatch;
	int i, j, iMatch;
	LPVOID pCmd;

	rpCmd = NULL;
	strCmd.TrimLeft();
	p = m_rgStrings.GetHeadPosition();
	while (p && !fParsed)
	{
		strCurr = m_rgStrings.GetNext(p);
		i = strCurr.Find(_T(';'));
		_ASSERTE(i>0);
		if (i > 0)
		{
			strMatch = strCurr.Left(i);
			iMatch = strCmd.Find(strMatch, 0);
			if (iMatch == 0)
			{
				// found command.
				j = strCurr.Find(_T(';'), i+1);
				strMatch = strCurr.Mid(i+1, j - i - 1);
				pCmd = NULL;
				m_rgCmds.Lookup(strMatch, pCmd);
				if (pCmd)
				{
					fParsed = ((CmdOp)pCmd)(this, strMatch, strCmd);
					rpCmd = (CmdOp)pCmd;
				}
			}
		}
	}

	return(fParsed);
}

int CCmdEdit::GetBrkPntList(CStringArray &rgStrBrks)
{
	long cBrks = 0;
	long cBrkPnts = 0;
	HRESULT hr;

	if (FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			CComQIPtr<IBreakpoints, &IID_IBreakpoints> pBrkPnts;
			CComPtr<IDispatch> pDispBrkPnts;

			pDebugger->get_Breakpoints(&pDispBrkPnts);
			pBrkPnts = pDispBrkPnts;
			if (pBrkPnts)
			{
				hr = pBrkPnts->get_Count(&cBrks);
				rgStrBrks.RemoveAll();
				rgStrBrks.Add(_T("# : [*=enabled] File(line) Function, Executable, Type"));
				while (cBrkPnts < cBrks)
				{
					CComPtr<IDispatch> pDispBrkPnt;
					CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
					CComBSTR bstrLocation;
					CComBSTR bstrFile;
					CComBSTR bstrFunction;
					//long lElements;
					short sEnabled;
					//DsWindowsMessage dsWndMsg;
					//long lPassCount;
					CComBSTR bstrExecutable;
					DsBreakpointType lType;
					CComBSTR bstrWndProc;
					CComVariant varItem = cBrkPnts;
					/* Type:
					dsChangedExpression
					dsLocation
					dsLocationWithTrueExpression
					dsLocationWithChangedExpression
					dsMessage
					dsTrueExpression  
					*/

					hr = pBrkPnts->Item(varItem, &pDispBrkPnt);
					pBrkPnt = pDispBrkPnt;

					hr = pBrkPnt->get_Enabled(&sEnabled);
					CString strOut, strLocation, strType;
					TCHAR chEnabled = _T(' ');
					CComBSTR bstrT ;
					hr = pBrkPnt->get_Type((long *)&lType);
					hr = pBrkPnt->get_File(&bstrFile);
					hr = pBrkPnt->get_Function(&bstrFunction);
					hr = pBrkPnt->get_Executable(&bstrExecutable);
					hr = pBrkPnt->get_Location(&bstrLocation);

					strLocation = bstrLocation;
					if (strLocation.GetAt(0) == _T('.'))
						strLocation.Delete(0); // remove leading "."
					if (sEnabled)
					{
						chEnabled = _T('*');
					}
					switch(lType)
					{
					case dsChangedExpression:
						strType.LoadString(IDS_CHANGED_EXPRESSION);
						break;
					case dsLocation:
						strType.LoadString(IDS_LOCATION);
						break;
					case dsLocationWithTrueExpression:
						strType.LoadString(IDS_LOCATIONWITHTRUEEXPRESSION);
						break;
					case dsLocationWithChangedExpression:
						strType.LoadString(IDS_LOCATIONWITHCHANGEDEXPRESSION);
						break;
					case dsMessage:
						strType.LoadString(IDS_MESSAGE);
						break;
					case dsTrueExpression:
						strType.LoadString(IDS_TRUEEXPRESSION);
						break;
					}
					strOut.Format(_T("%2d : %c %ls(%s): %ls, %ls, %s:"),cBrkPnts, chEnabled, bstrFile, strLocation, bstrFunction, bstrExecutable, strType);

					rgStrBrks.Add(strOut);
					
					cBrkPnts++;
				}
			}
		}
	}
	return(cBrkPnts);
}


HRESULT CCmdEdit::FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen /*= TRUE*/)
{
	HRESULT hr = E_FAIL;
	CComPtr<IDispatch> pDispDocuments;
    CComQIPtr<IDocuments, &IID_IDocuments> pDocuments;
	CComBSTR bstrFile;
    m_spApplication->get_Documents(&pDispDocuments);
    pDocuments = pDispDocuments;
    pDispDocuments = NULL;
	BOOL fFound = FALSE;

	if (pDocuments)
	{	// ENSURE DOC IS OPEN -- WE KEEP FILES AROUND THAT MAY HAVE BEEN CLOSED
		CComVariant vtDocType = _T("Auto");
		CComVariant vtBoolReadOnly = FALSE;
		CComPtr<IDispatch> pDispDoc;
		bstrFile = szFile;
		CComQIPtr<IGenericDocument, &IID_IGenericDocument> pDocument;
		if (fOkToOpen)
		{
			hr = pDocuments->Open(bstrFile, vtDocType, vtBoolReadOnly, &pDispDoc);
			pDocument = pDispDoc;
			if (SUCCEEDED(hr) && pDocument)
			{
				fFound = TRUE;
				pDoc = pDocument;
			}
		}
		if (!fFound)
		{
			CComPtr<IUnknown> pUnk;
			CComQIPtr<IEnumVARIANT, &IID_IEnumVARIANT> pNewEnum;
			if (SUCCEEDED(pDocuments->get__NewEnum(&pUnk)) && pUnk != NULL)
			{
				pNewEnum = pUnk;
				VARIANT varGenericDocument;

				while (!fFound && pNewEnum->Next(1, &varGenericDocument, NULL) == S_OK)
				{
					CComQIPtr<IGenericDocument, &IID_IGenericDocument> pGenericDocument;
					ASSERT (varGenericDocument.vt == VT_DISPATCH);
					pGenericDocument = varGenericDocument.pdispVal;
					VariantClear(&varGenericDocument);
					CComBSTR bstrFullName;
					pGenericDocument->get_FullName(&bstrFullName);
					if (bstrFullName == szFile)
					{
						fFound = TRUE;
						pDoc = pGenericDocument;
					}
				}
			}


		}
	}

	return(hr);
}


//================================================================================
// COMMANDS
// Use the following as a template:

//BOOL CCmdEdit::CmdGo(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
//{
//	BOOL fOK = FALSE;
//
//	return(fOK);
//}


BOOL CCmdEdit::CmdCD(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;

	CString strDir;
	int i;

	strDir = rstrCmd;
	i = strDir.Find(_T(' '));
	if (i > 0)
	{
		strDir = strDir.Mid(i+1);
		::_tchdir(strDir);
	}
	::_tgetcwd(strDir.GetBuffer(_MAX_PATH), _MAX_PATH);
	strDir.ReleaseBuffer();
	strDir = _T(" --> ") + strDir;
	pThis->Append(strDir);
	if (pThis->FHaveApp())
	{
		CComBSTR bstrDir = strDir;
		pThis->m_spApplication->put_CurrentDirectory(bstrDir);
	}
	return(fOK);
}


BOOL CCmdEdit::CmdCls(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;

	CString strOut;

	strOut = _T("\0");
	pThis->SetSel(0, -1, TRUE);
	pThis->ReplaceSel(strOut);
	return(fOK);
}


BOOL CCmdEdit::CmdHelp(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;
	POSITION p;
	CString strCmd;
	CString strCurr;
	CString strMatch;
	CString strKey;
	LPVOID pCmd;
	int i, j;
	BOOL fShowOnlyEnabled = TRUE;
	BOOL fShow;

	strCmd.TrimRight();
	if (strCmd.Find(_T('*')) > 0)
	{
		fShowOnlyEnabled = FALSE;
	}
	p = pThis->m_rgStrings.GetHeadPosition();
	while (p)
	{
		strCmd.Empty();
		fShow = TRUE;
		strCurr = pThis->m_rgStrings.GetNext(p);
		i = strCurr.Find(_T(';'));
		_ASSERTE(i>0);
		if (i > 0)
		{
			strMatch = strCurr.Left(i);
			j = strCurr.Find(_T(';'), i+1);
			strKey = strCurr.Mid(i+1, j - i - 1);
			pCmd = NULL;
			pThis->m_rgCmds.Lookup(strKey, pCmd);
			if (!fShowOnlyEnabled)
			{
				if (pCmd)
				{
					strCmd += _T('*'); // command has handler
				}
				else
				{
					strCmd += _T(' '); // not enabled/found
					fShow = !fShowOnlyEnabled;
				}
			}
			if (fShow)
			{
				strCmd += strMatch;
				strCmd += _T(" - ");
				strCmd += strCurr.Mid(j+1);
				pThis->Append(strCmd);
			}
		}
	}

	int nId = IDS_DEFAULT;
	while (strCmd.LoadString(nId))
	{
		pThis->Append(strCmd);
		nId++;

	}
	return(fOK);
}

BOOL CCmdEdit::CmdGo(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;
	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		pThis->m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			hr = pDebugger->Go();
			fOK = TRUE;
		}
	}
	return(fOK);
}


BOOL CCmdEdit::CmdOpen(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;
	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CString strFile;
		int i;

		strFile = rstrCmd;
		i = strFile.Find(_T(' '));
		if (i > 0)
		{
			strFile = strFile.Mid(i);
			strFile.TrimLeft();
			strFile.TrimRight();
			CComQIPtr<IDocuments, &IID_IDocuments> pDocs;
			CComPtr<IDispatch> pDispDocs;
			pThis->m_spApplication->get_Documents(&pDispDocs);
			pDocs = pDispDocs;

			if (pDocs)
			{
				CComVariant vtDocType = _T("Auto");
				CComVariant vtBoolReadOnly = FALSE;
				CComBSTR bstrFile = strFile;
				CComPtr<IDispatch> pDispDoc;

				hr = pDocs->Open(bstrFile, vtDocType, vtBoolReadOnly, &pDispDoc);
				fOK = TRUE; // assume we succeeded
			}
		}
	}
	return(fOK);
}


BOOL CCmdEdit::CmdClose(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWindow;
		CComPtr<IDispatch> pDispWindow;
		pThis->m_spApplication->get_ActiveWindow(&pDispWindow);
		pWindow = pDispWindow;
		if (pWindow)
		{
			CComVariant varSaveChanges = dsSaveChangesPrompt;
			DsSaveStatus iSaved;
			hr = pWindow->Close(varSaveChanges, &iSaved);
			fOK = TRUE; // assume we succeeded
		}
	}
	return(fOK);
}

BOOL CCmdEdit::CmdBuild(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComVariant varConfig;
		CComPtr<IDispatch> pDispConfig;

		hr = pThis->m_spApplication->get_ActiveConfiguration(&pDispConfig);
		varConfig = pDispConfig;
		hr = pThis->m_spApplication->Build(varConfig);
	}
	return(fOK);
}

BOOL CCmdEdit::CmdRebuild(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComVariant varConfig;
		CComPtr<IDispatch> pDispConfig;

		hr = pThis->m_spApplication->get_ActiveConfiguration(&pDispConfig);
		varConfig = pDispConfig;
		hr = pThis->m_spApplication->RebuildAll(varConfig);
	}
	return(fOK);
}




BOOL CCmdEdit::CmdStep(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		pThis->m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			hr = pDebugger->StepOver();
			fOK = TRUE;
		}
	}
	return(fOK);
}


BOOL CCmdEdit::CmdStepInto(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		pThis->m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			hr = pDebugger->StepInto();
			fOK = TRUE;
		}
	}
	return(fOK);
}


BOOL CCmdEdit::CmdQuit(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;
	HWND hwnd;
	CWnd *pwndParent;

	pwndParent = pThis->GetParent();
	if (pwndParent)
	{
		hwnd = pwndParent->GetSafeHwnd();
		::SendMessage(hwnd, WM_CLOSE, 0, 0L);
	}
	return(fOK);
}


BOOL CCmdEdit::CmdExit(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;

	HRESULT hr;
	if (pThis->FHaveApp())
	{
		hr = pThis->m_spApplication->Quit();
		fOK = TRUE;
	}
	return(fOK);
}


 
 

BOOL CCmdEdit::CmdDos(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = FALSE;
	rstrCmd;

	// don't do anything but return false. We will check for this one later, and bypass calling msdev.
	return(fOK);
}

BOOL CCmdEdit::CmdBL(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;
	CStringArray rgStrBrks;
	int i, iMax;

	if (pThis->FHaveApp())
	{
		if (pThis->GetBrkPntList(rgStrBrks) > 0)
		{
			iMax = rgStrBrks.GetUpperBound();
			for (i = 0; i < iMax; i++)
			{
				pThis->Append(rgStrBrks.GetAt(i));
			}
		}
	}
	return(fOK);
}



BOOL CCmdEdit::CmdBC(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	BOOL fOK = TRUE;
	HRESULT hr;
	long cBrks = 0;
	CString strCmd = rstrCmd;
	CString strT;
	int i;
	long lBrkPnt;

	if (pThis->FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		pThis->m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			CComQIPtr<IBreakpoints, &IID_IBreakpoints> pBrkPnts;
			CComPtr<IDispatch> pDispBrkPnts;

			pDebugger->get_Breakpoints(&pDispBrkPnts);
			pBrkPnts = pDispBrkPnts;
			if (pBrkPnts)
			{
				hr = pBrkPnts->get_Count(&cBrks);
				strCmd.TrimLeft();
				i = strCmd.Find(rstrCmdName);
				_ASSERTE(i >= 0);
				strCmd = strCmd.Mid(i + rstrCmdName.GetLength());
				strCmd.TrimLeft();
				if (strCmd.IsEmpty() || strCmd.Find(_T('*')))
				{ // clear all
					CComBSTR bstrCommand;

					bstrCommand = _T("DebugRemoveAllBreakpoints");
					hr = pThis->m_spApplication->ExecuteCommand(bstrCommand);
				}
				else
				{
					while (!strCmd.IsEmpty())
					{
						i = strCmd.Find(_T(','));
						if (i < 0) // end of line?
						{
							lBrkPnt = _ttol(strCmd);
							strCmd.Empty();
						}
						else
						{
							strT = strCmd.Left(i);
							lBrkPnt = _ttol(strT);
							strCmd = strCmd.Mid(i+1);
						}
						
						CComPtr<IDispatch> pDispBreakpoint;
						CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBreakpoint;
						CComVariant varBrkPnt;
						CComBSTR bstrLine;
						
						varBrkPnt = lBrkPnt;
						hr = pBrkPnts->Item(varBrkPnt, &pDispBreakpoint);
						pBreakpoint = pDispBreakpoint;
						if(pBreakpoint)
						{
							pBreakpoint->Remove();
						}
					}
				}

			}
		}
	}
	return(fOK);
}

BOOL CCmdEdit::CmdBP(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{ //;Set Breakpoint. Arguments are [File,]"." (current line), line number, ".+n" 
	// where n is an integer offset to line to set breakpoint on. Eg., "bp foo.cpp, 32" or "bp ." or "bp  .+3".
	BOOL fOK = TRUE;
	HRESULT hr;
	if (pThis->FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		CComQIPtr<IBreakpoints, &IID_IBreakpoints> pBrkPnts;
		CComPtr<IDispatch> pDispBrkPnts;
		hr = pThis->m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			CString strFile, strCmd, strLine;
			int i, cb;
			long lLine = 0;
			CComPtr<IGenericDocument> pGenericDoc;

			strCmd = rstrCmd;
			i = strCmd.Find(rstrCmdName);
			_ASSERTE(i >= 0); // how did we get here if this is false?
			if (i >= 0)
			{
				strCmd = strCmd.Mid(i + rstrCmdName.GetLength());
				i = strCmd.Find(_T(','));
				if (i >= 0)
				{ // have a file, we surmise
					strFile = strCmd.Left(i);
					strCmd = strCmd.Mid(i+1);
					pThis->FindDoc(strFile, pGenericDoc, TRUE);
					pGenericDoc->put_Active(VARIANT_TRUE);;
				}
				else
				{
					CComPtr<IDispatch> pDispDoc;
					pThis->m_spApplication->get_ActiveDocument(&pDispDoc);
					if (pDispDoc)
					{
						pDispDoc.QueryInterface(&pGenericDoc);
					}
				}
				strLine = strCmd.SpanIncluding(_T(" 0123456789."));
				cb = strLine.GetLength();
				if (cb > 0)
				{
					i = strCmd.Find(strLine);
					strLine.TrimLeft();
					if (strLine.GetAt(0) == _T('.'))
						strLine.Delete(0); // remove leading "."
					_ASSERTE(i >= 0);
					strCmd = strCmd.Mid(i + cb);
					strCmd.TrimLeft();
					lLine = _ttol(strLine);
					if (!strCmd.IsEmpty())
					{
						CString strT;
						BOOL fAdd = strCmd.GetAt(0) == _T('+');
						if (strCmd.GetAt(0) == _T('-') || fAdd)
						{
							strCmd = strCmd.Mid(1);
							strT = strCmd.SpanIncluding(_T(" 0123456789"));
							strT.TrimLeft();
							if (fAdd)
							{
								lLine += _ttol(strT);
							}
							else
							{
								lLine -= _ttol(strT);
							}
							if (lLine < 0)
								lLine = 0;
						}
					}
				}
				pDebugger->get_Breakpoints(&pDispBrkPnts);
				pBrkPnts = pDispBrkPnts;
				if (pBrkPnts && pGenericDoc)
				{
					CComQIPtr<ITextDocument, &IID_ITextDocument> pTextDoc;
					CComPtr<IDispatch> pDispBrkPnt;
					CComPtr<IDispatch> pDispSel;
					CComQIPtr<ITextSelection, &IID_ITextSelection> pSel;
					hr = pGenericDoc->put_Active(VARIANT_TRUE);
					pTextDoc = pGenericDoc;
					if (pTextDoc)
					{
						hr = pTextDoc->get_Selection(&pDispSel);
						if (SUCCEEDED(hr) && pDispSel)
						{
							CComVariant varSelMode = dsMove;
							CComVariant varSel;
							pSel = pDispSel;
							hr = pSel->GoToLine(lLine, varSelMode);

							varSel = lLine;
							hr = pBrkPnts->AddBreakpointAtLine(varSel, &pDispBrkPnt);
						}
					}
				}
			}
		}
	}
	return(fOK);
}


BOOL CCmdEdit::CmdBD(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	pThis->DoEnableDisableCmds(rstrCmdName, rstrCmd, FALSE);
	return(TRUE);
}

BOOL CCmdEdit::CmdBE(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd)
{
	pThis->DoEnableDisableCmds(rstrCmdName, rstrCmd, TRUE);
	return(TRUE);
}

BOOL CCmdEdit::DoEnableDisableCmds(CString& rstrCmdName, CString& rstrCmd, BOOL fEnable)
{ // enable/disable breakpoints
	BOOL fOK = TRUE;
	HRESULT hr;
	long cBrkPnts = 0;
	long cBrks = 0;
	CString strCmd = rstrCmd;
	int i;
	long lBrkPnt;
	short sEnabled = fEnable ? VARIANT_TRUE : VARIANT_FALSE;
	CString strT;

	if (FHaveApp())
	{
		CComQIPtr<IDebugger, &IID_IDebugger> pDebugger;
		CComPtr<IDispatch> pDispDebugger;
		m_spApplication->get_Debugger(&pDispDebugger);
		pDebugger = pDispDebugger;
		if (pDebugger)
		{
			CComQIPtr<IBreakpoints, &IID_IBreakpoints> pBrkPnts;
			CComPtr<IDispatch> pDispBrkPnts;

			pDebugger->get_Breakpoints(&pDispBrkPnts);
			pBrkPnts = pDispBrkPnts;
			if (pBrkPnts)
			{
				hr = pBrkPnts->get_Count(&cBrks);
				strCmd.TrimLeft();
				i = strCmd.Find(rstrCmdName);
				_ASSERTE(i >= 0);
				strCmd = strCmd.Mid(i + rstrCmdName.GetLength());
				strCmd.TrimLeft();
				if (strCmd.IsEmpty() || strCmd.Find(_T('*')) >= 0 )
				{ // enable/disable all
					for (lBrkPnt = 0; lBrkPnt < cBrks; lBrkPnt++)
					{
						CComPtr<IDispatch> pDispBreakpoint;
						CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
						CComVariant varBrkPnt;
						CComBSTR bstrLine;
						
						varBrkPnt = lBrkPnt;
						hr = pBrkPnts->Item(varBrkPnt, &pDispBreakpoint);
						pBrkPnt = pDispBreakpoint;
						if (SUCCEEDED(hr) && pBrkPnt)
						{
							hr = pBrkPnt->put_Enabled(sEnabled);
						}
					}
				}
				else
				{
					while (!strCmd.IsEmpty())
					{
						i = strCmd.Find(_T(','));
						if (i < 0) // end of line?
						{
							lBrkPnt = _ttol(strCmd);
							strCmd.Empty();
						}
						else
						{
							strT = strCmd.Left(i);
							lBrkPnt = _ttol(strT);
							strCmd = strCmd.Mid(i+1);
						}
						
						CComPtr<IDispatch> pDispBreakpoint;
						CComQIPtr<IBreakpoint, &IID_IBreakpoint> pBrkPnt;
						CComVariant varBrkPnt;
						CComBSTR bstrLine;
						
						varBrkPnt = lBrkPnt;
						hr = pBrkPnts->Item(varBrkPnt, &pDispBreakpoint);
						pBrkPnt = pDispBreakpoint;
						if (SUCCEEDED(hr) && pBrkPnt)
						{
							hr = pBrkPnt->put_Enabled(sEnabled);
						}

					}
				}

			}
		}
	}
	return(fOK);
}

