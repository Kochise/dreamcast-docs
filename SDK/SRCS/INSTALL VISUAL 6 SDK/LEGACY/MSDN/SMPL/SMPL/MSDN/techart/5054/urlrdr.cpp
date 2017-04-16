// UrlRead.cpp : Implementation of CUrlReader
#include "stdafx.h"
#include "ReadUrl.h"
#include "UrlRdr.h"
#include <wininet.h>

/////////////////////////////////////////////////////////////////////////////
// CUrlReader

STDMETHODIMP CUrlReader::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUrlReader,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUrlReader::ReadUrl(BSTR sURL, BSTR sOutputSpec)
{
	// initialize variables
	m_hThread = NULL;
	m_dwThreadId = 0;

	// store incoming values
	m_URLSpec = sURL;
	m_OutputFilespec = sOutputSpec;

	// create URL reading thread
	m_hThread = ::CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)&CUrlReader::ProcessUrl,
		this,
		0,
		&m_dwThreadId);

	// return error code if thread could not be created
	if (m_hThread == NULL)
		return S_FALSE;

	// return success
	return S_OK;
}

DWORD WINAPI CUrlReader::ProcessUrl(void * pParam)
{
	CUrlReader * pCaller = (CUrlReader *)pParam;
	HINTERNET hSession;
	HINTERNET hURL;
	HANDLE hBuffer;
	HANDLE hFile;
	DWORD dwBytesRead;
	DWORD dwBufferSize;
	DWORD dwBytesWritten;
	LPVOID pBuffer;
	BOOL brc;

	// make connection to web, raise error event if error occurs
	hSession = ::InternetOpen(
				_T("Microsoft Internet Explorer"),
				INTERNET_OPEN_TYPE_PRECONFIG,
				NULL,
				NULL,
				0);
	if (hSession == NULL)
	{
		pCaller->Fire_ReadUrlError(GetLastError());
		return 0;
	}

	// make connection to URL, raise error event if error occurs
	hURL = ::InternetOpenUrl(
			hSession,
			pCaller->m_URLSpec,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);
	if (hURL == NULL)
	{
		pCaller->Fire_ReadUrlError(GetLastError());
		return 0;
	}

	// allocate storage buffer for URL contents
	dwBufferSize = 65535L;
	hBuffer = ::GlobalAlloc(GHND, dwBufferSize);
	pBuffer = ::GlobalLock(hBuffer);

	// read URL into buffer
	brc = ::InternetReadFile(
			hURL,
			pBuffer,
			dwBufferSize,
			&dwBytesRead);

	// write buffer out to data file
	hFile = ::CreateFile(
				pCaller->m_OutputFilespec,
				GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	brc = ::WriteFile(
			hFile,
			pBuffer,
			dwBytesRead,
			&dwBytesWritten,
			NULL);
	::CloseHandle(hFile);

	// release resources
	::GlobalUnlock(hBuffer);
	::GlobalFree(hBuffer);
	::InternetCloseHandle(hURL);
	::InternetCloseHandle(hSession);

	// raise event notification
	pCaller->Fire_ReadUrlFinished(0);
	return 0;
}

