// PINBALL.CPP - Implementation file for your Internet Server
//    Pinball Extension
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "Pinball.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object

CWinApp theApp;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CPinballExtension, CHttpServer)
	// TODO: insert your ON_PARSE_COMMAND() and
	// ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
	// For example:

	ON_PARSE_COMMAND(Default, CPinballExtension, ITS_EMPTY)
	DEFAULT_PARSE_COMMAND(Default, CPinballExtension)
	ON_PARSE_COMMAND(GetImage, CPinballExtension, ITS_I4)
	ON_PARSE_COMMAND_PARAMS("Favorite")
END_PARSE_MAP(CPinballExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CPinballExtension object

CPinballExtension theExtension;


///////////////////////////////////////////////////////////////////////
// CPinballExtension implementation

CPinballExtension::CPinballExtension()
{
}

CPinballExtension::~CPinballExtension()
{
}

BOOL CPinballExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

BOOL CPinballExtension::TerminateExtension(DWORD dwFlags)
{
	// extension is being terminated
	//TODO: Clean up any per-instance resources
	return TRUE;
}

BOOL CPinballExtension::LoadLongResource(CString& str, UINT nID)
{
	HRSRC hRes;
	HINSTANCE hInst = AfxGetResourceHandle();
	BOOL bResult = FALSE;

	hRes = FindResource(hInst, MAKEINTRESOURCE(nID), RT_HTML);
	if (hRes == NULL)
		ISAPITRACE1("Error: Resource %d could not be found\r\n", nID);
	else
	{
		DWORD dwSize = SizeofResource(hInst, hRes);
		if (dwSize == 0)
		{
			str.Empty();
			bResult = TRUE;
		}
		else
		{
			LPTSTR pszStorage = str.GetBufferSetLength(dwSize);

			HGLOBAL hGlob = LoadResource(hInst, hRes);
			if (hGlob != NULL)
			{
				LPVOID lpData = LockResource(hGlob);

				if (lpData != NULL)
				{
					memcpy(pszStorage, lpData, dwSize);
					bResult = TRUE;
				}

				FreeResource(hGlob);
			}
		}
	}

#ifdef _DEBUG
	if (!bResult)
		str.Format(_T("<b>Could not find string %d</b>"), nID);
#endif

	return bResult;
}



///////////////////////////////////////////////////////////////////////
// CPinballExtension command handlers

void CPinballExtension::Default(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	// show the user our regular HTML

	CString str;
	if (LoadLongResource(str, IDR_DEFAULT_HTML))
		*pCtxt << str;
	else
		*pCtxt << _T("Could not load default page from HTML resource.");

	EndContent(pCtxt);
}

BOOL CPinballExtension::SendAFile(CHttpServerContext* pCtxt,
	LPCTSTR pstrFullPath, LPCTSTR pstrContentType)
{
	BOOL bResult = FALSE;

	// open the file using SEQUENTIAL_SCAN and OVERLAPPED so we can
	// pass the resulting handle to IIS

	HANDLE hFile = ::CreateFile(pstrFullPath,
					GENERIC_READ, 0, NULL, OPEN_EXISTING,
					FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_OVERLAPPED, NULL);

	// If the file open failed, write an error message to the user.
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		*pCtxt << _T("File open failed on ");
		*pCtxt << pstrFullPath << _T("!  Error was ");
		*pCtxt << long(dwError);
		*pCtxt << _T("<br>");

		*pCtxt << _T("Did you correctly copy all the graphics files, too?<br>");
	}
	else
	{
		// try to transmit the file we've opened

		DWORD dwLength = GetFileSize(hFile, NULL);

		// formulate a proper header
		CString strHeader;
		strHeader.Format(
			_T("HTTP/1.0 200 OK\r\n%s\r\nContent-length: %d\r\n\r\n"),
			pstrContentType, dwLength);

		// double-cast is necessary because TransmitFile()
		// params are not const

		bResult = pCtxt->TransmitFile(hFile, HSE_IO_ASYNC,
			(LPVOID)(LPCTSTR) strHeader);

		// if it failed, explain it to the user
		if (!bResult)
		{
			StartContent(pCtxt);
			WriteTitle(pCtxt);

			DWORD dwError = GetLastError();
			*pCtxt << _T("TransmitFile called failed!  Error was ");
			*pCtxt << long(dwError) << _T("<br>");

			EndContent(pCtxt);
			CloseHandle(hFile);
		}

		// If the call to TransmitFile() was successful, we don't
		// need to do anything else.
	}

	return bResult;
}

BOOL CPinballExtension::SendJPGFile(CHttpServerContext* pCtxt,
	LPCTSTR pstrFile,   LPCTSTR pstrPath)
{
	// specify content type
	static const TCHAR szJPGContent[] = _T("Content-Type: image/jpeg");

	// build the local file name
	CString str(pstrPath);
	str += pstrFile;

	// send it off
	return SendAFile(pCtxt, str, szJPGContent);
}

BOOL CPinballExtension::SendGIFFile(CHttpServerContext* pCtxt,
	LPCTSTR pstrFile,   LPCTSTR pstrPath)
{
	// specify content type
	static const TCHAR szGIFContent[] = _T("Content-Type: image/gif");

	// build the local file name
	CString str(pstrPath);
	str += pstrFile;

	// send it off
	return SendAFile(pCtxt, str, szGIFContent);
}

void CPinballExtension::GetImage(CHttpServerContext* pCtxt, long dwChoice)
{
	// find the local directory where we live, as we'll assume all
	// the graphics files are nearby

	TCHAR szBuffer[_MAX_PATH];
	DWORD dwSize = _MAX_PATH;
	pCtxt->GetServerVariable("URL", szBuffer, &dwSize);

	LPTSTR pstrWhack = _tcsrchr(szBuffer, '/');
	if (pstrWhack == NULL)
	{
		StartContent(pCtxt);
		WriteTitle(pCtxt);
		*pCtxt << _T("Wierd response from GetServerVariable: ");
		*pCtxt << szBuffer << _T("<br>");
		EndContent(pCtxt);
	}
	else
	{
		// convert the URL into a useable local path
		dwSize = _MAX_PATH;
		*pstrWhack = NULL;
		pCtxt->ServerSupportFunction(HSE_REQ_MAP_URL_TO_PATH, szBuffer, &dwSize, 0);
		_tcscat(szBuffer, _T("/"));

		// depending on what the user asked for, send them something
		switch (dwChoice)
		{
		case 0:
			{
			StartContent(pCtxt);
			WriteTitle(pCtxt);
			CString str;
			if (LoadLongResource(str, IDR_REDIR_HTML))
				*pCtxt << str;
			else
				*pCtxt << _T("Could not load redir page from HTML resource.");
			}
			EndContent(pCtxt);
			break;

		case 1:
			SendJPGFile(pCtxt, _T("mars.jpg"), szBuffer);
			break;

		case 2:
			SendGIFFile(pCtxt, _T("tz.gif"), szBuffer);
			break;

		case 3:
			SendGIFFile(pCtxt, _T("taf.gif"), szBuffer);
			break;

		case 4:
			SendGIFFile(pCtxt, _T("cv.gif"), szBuffer);
			break;

		default:
			StartContent(pCtxt);
			WriteTitle(pCtxt);
			// how could this happen?
			*pCtxt << _T("Choice # ");
			*pCtxt << dwChoice;
			*pCtxt << _T(" is invlaid!<br>");
			EndContent(pCtxt);
			break;
		}
	}
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CPinballExtension, CHttpServer)
	//{{AFX_MSG_MAP(CPinballExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif  // 0
