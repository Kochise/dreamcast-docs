// zap.cpp : implementation of the CZap class
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "sampleaw.h"
#include "zap.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This helper (used in CZap::LoadFile) determines whether we should zap
//  a file into a "binary" template-- that is, a template to be copied using
//  CopyTemplate, rather than parsed via ProcessTemplate.
inline BOOL ShouldCopyVerbatim(LPCTSTR szFullName, LPCTSTR szExt)
{
	return (szExt != NULL &&
		// Icons and bitmaps should be copied not parsed
		(!_tcsicmp(szExt, _T(".ico")) || !_tcsicmp(szExt, _T(".bmp"))
			// miscellaneous binary files not to be parsed
			|| !_tcsicmp(szExt, _T(".dat"))
			// .rtf files other than afxdlg.rtf should be copied not parsed
			|| (!_tcsicmp(szExt, _T(".rtf")) && _tcsicmp(szFullName, _T("afxdlg.rtf")))));
}

// Given a filename, map it to memory, store its size in dwSize, and return
//  the mapped view.
LPCTSTR CZap::LoadFile(LPCTSTR lpszResource, DWORD& dwSize)
{
	ASSERT(m_hFile == NULL);
	ASSERT(m_hMapping == NULL);
	ASSERT(m_strFile.IsEmpty());

	// First open the file
	m_hFile = CreateFile(
		lpszResource,           // File name
		GENERIC_READ,           // Read-only
		FILE_SHARE_READ
			| FILE_SHARE_WRITE, // Allow sharing-- we're only doing a quick scan
		NULL,                   // No security attributes
		OPEN_EXISTING,          // Only open an existing file
		0,                      // Ignore file attributes
		NULL);                  // Ignore hTemplateFile

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		m_hFile = NULL;
		ReportAndThrow(IDP_ZAP_CANT_OPEN_FILE, lpszResource);
	}

	// Get the file's size
	dwSize = GetFileSize(m_hFile, NULL);
	if (dwSize == 0xffffffff)
	{
		m_hFile = NULL;
		ReportAndThrow(IDP_ZAP_CANT_GET_SIZE, lpszResource);
	}

	// Create a mapping object from the file
	m_hMapping = CreateFileMapping(
		m_hFile,                // Handle we got from CreateFile
		NULL,                   // No security attributes
		PAGE_READONLY,          // read-only
		0, 0,                   // Max size = current size of file
		NULL);                  // Don't name the mapping object

	// Map the file to memory
	m_lpszFile = (LPCTSTR) MapViewOfFile(
		m_hMapping,             // Handle we got from CreateFileMapping
		FILE_MAP_READ,          // read-only (didn't I mention that before?)
		0, 0,                   // Offset into file = beginning of file
		0);                     // Map entire file

	_tsplitpath(lpszResource, NULL, m_strSubdir.GetBuffer(_MAX_DIR), m_strBaseFileName.GetBuffer(_MAX_FNAME),
		m_strFileExt.GetBuffer(_MAX_EXT));
	m_strSubdir.ReleaseBuffer();
	m_strSubdir.MakeLower();
	m_strBaseFileName.ReleaseBuffer();
	m_strFileExt.ReleaseBuffer();
	m_strBaseFileName += m_strFileExt;
	LPCTSTR szBeginRootDir = _tcsstr(m_strSubdir, m_strRootDir);
	ASSERT(szBeginRootDir != NULL);
	m_strSubdir = szBeginRootDir + m_strRootDir.GetLength();

	m_bBinary = ShouldCopyVerbatim(m_strBaseFileName, m_strFileExt);

	// Remember name of file for potential future error messages
	m_strFile = lpszResource;

	return m_lpszFile;
}

// Called after a file has been zapped to deallocate resources used for zapping.
void CZap::UnloadFile()
{
	ASSERT(m_hFile != NULL);
	ASSERT(m_hMapping != NULL);
	ASSERT(m_lpszFile != NULL);
	ASSERT(!m_strFile.IsEmpty());

	VERIFY(UnmapViewOfFile((LPVOID) m_lpszFile));
	VERIFY(CloseHandle(m_hMapping));
	VERIFY(CloseHandle(m_hFile));
	m_hFile = NULL;
	m_hMapping = NULL;
	m_strFile.Empty();
}

// This helper (used in CZap::AddToNewProjInf) determines whether to set the
//  "resource file" flag for this file in the generated newproj.inf

inline BOOL ShouldAddFileToResource (LPCTSTR szFullName, LPCTSTR szExt)
{
	return (szExt != NULL &&
		(!_tcsicmp (szExt, _T(".rc2")) || !_tcscmp (szExt, _T(".ico"))
		|| !_tcsicmp (szExt, _T(".bmp"))));
}

// This is defined in zapdlg.cpp.  We've stored the non-colliding names of the templates
//  we're generating in here.  This information is used in CZap::AddToNewProjInf() below.
extern CStringList g_TemplateNames;

// This is called after a file is zapped.  At that point, it has been determined
//  whether the resulting template should be considered a "binary" template, and
//  so we're prepared to add the entry to the generated custom AppWizard's
//  newproj.inf (which is what this does).
void CZap::AddToNewProjInf()
{
	ASSERT(m_posTplName != NULL);

	// Determine whether we should set the ':' flag.
	CString strFlag;
	if (ShouldAddFileToResource (m_strBaseFileName,  m_strFileExt))
		strFlag = _T(":");

	// Determine whether we should set the '=' flag
	CString strEquals;
	strEquals = m_bBinary ? _T("=") : _T("");

	CString strMacroizedFile;
	ZapFileName(m_strBaseFileName, strMacroizedFile);
	CString strTemplateName = g_TemplateNames.GetNext(m_posTplName);

	// Finally, the string used in this custom AppWizard's newnwprj.inf
	//  (i.e., the generated custom AppWizard's newproj.inf).
	m_strGeneratedNewProjInfo += strEquals + strFlag + strTemplateName // Template we just zapped
		+ _T('\t')
		+ m_strSubdir + strMacroizedFile + _T('\n');        // What that template generates
}


// This is the meat of our override of ProcessTemplate.  It zaps a file line
//  by line using ZapLine.
void CZap::ZapFile(LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput)
{
	ASSERT(m_hFile != NULL);
	ASSERT(m_hMapping != NULL);
	if (m_posTplName == NULL)
		m_posTplName = g_TemplateNames.GetHeadPosition();

	if (m_bBinary)
	{
		sampleaw.CopyTemplate(lpszInput, dwSize, pOutput);
		AddToNewProjInf();
		return;
	}

	if (dwSize == 0)
	{
		pOutput->WriteLine(_T(" "));
		AddToNewProjInf();
		return;
	}

	LPCTSTR lpszBeginLine = lpszInput;
	LPCTSTR lpszEndLine;

	// Loop line by line, until we go past the end
	while ((DWORD) (lpszBeginLine-lpszInput) < dwSize)
	{
		// Start from the beginning of a line, and find a carriage return
		lpszEndLine = _tcschr(lpszBeginLine, _T('\r'));

		// If there was no carriage return...
		if (lpszEndLine == NULL
			// ...or no newline after the carriage return
			|| *(lpszEndLine = _tcsinc(lpszEndLine)) != _T('\n'))
		{
			// Then this must be a binary file (or there was no trailing
			//  "\r\n" at the end of the file).  In either case, bail and
			//  write the rest of the file verbatim to the output; mark the
			//  file as binary.
			m_bBinary = TRUE;
			pOutput->WriteBlock(lpszBeginLine, dwSize - (DWORD)(lpszBeginLine-lpszInput));
			break;
		}

		// Here, we successfully found a "\r\n", and lpszEndLine is
		//  sitting at the '\n'.  So zap the line.
		CString strLine(lpszBeginLine, lpszEndLine-lpszBeginLine-1);
		ZapLine(strLine);
		pOutput->WriteLine(strLine);
		lpszBeginLine = _tcsinc(lpszEndLine);
	}
	AddToNewProjInf();
}

// Here are the brains of the operation.  zrdGeneral contains the strings we
//  search for, and what we replace them with.  ZapRawData is defined in
//  zap.h.
// The reason we have such a structure is that we can not simply "macroize"
//  every occurrence of the project name in its files.  For example, if the
//  project were named "View" or "while", and we blindly replaced all
//  occurrences of the project name with macros, the generated custom AppWizard
//  would be incapable of creating compilable projects.  Thus, we have to
//  search for the project name occurring in special contexts.
// In general, the format is:
//      { Pre, RootType, Post, {Replacement #0, Replacement #1}},
//  where Pre + RootType + Post is the string we search for, and Replacement #0
//  is what we usually replace it with-- the exception is when we're naming
//  one of the generated custom AppWizard's template files, in which case we use
//  Replacement #1.  (Replacement #1 can be NULL if we know that the particular
//  search string will never be replaced by the name of a template file in
//  the generated custom AppWizard.)
// See CZap::ZapLine and its references in CZap::ZapFile & CZap::ZapFileName,
//  to see how zrdGeneral is used.
static ZapRawData zrdGeneral[] =
{
	{_T(""), ZRD_ROOT, _T(".h"), {_T("$$root$$.h"), _T("root.h")}},
	{_T(""), ZRD_ROOT, _T(".cpp"), {_T("$$root$$.cpp"), _T("root.cpp")}},
	{_T(""), ZRD_ROOT, _T(".rc"), {_T("$$root$$.rc"), _T("root.rc")}},
	{_T(""), ZRD_ROOT_UPR, _T(".RC"), {_T("$$ROOT$$.RC"), NULL}},
	{_T(""), ZRD_ROOT, _T(".rc2"), {_T("$$root$$.rc2"), _T("root.rc2")}},
	{_T(""), ZRD_ROOT_UPR, _T(".RC2"), {_T("$$ROOT$$.RC2"), NULL}},
	{_T(""), ZRD_ROOT, _T(".ico"), {_T("$$root$$.ico"), _T("root.ico")}},
	{_T(""), ZRD_ROOT, _T(".dll"), {_T("$$root$$.dll"), NULL}},
	{_T(""), ZRD_ROOT_UPR, _T(".DLL"), {_T("$$ROOT$$.DLL"), NULL}},
	{_T(""), ZRD_ROOT, _T(".exe"), {_T("$$root$$.exe"), NULL}},
	{_T(""), ZRD_ROOT_UPR, _T(".EXE"), {_T("$$ROOT$$.EXE"), NULL}},
	{_T(""), ZRD_ROOT, _T(".mak"), {_T("$$root$$.mak"), _T("root.mak")}},
	{_T(""), ZRD_ROOT, _T(".hm"), {_T("$$root$$.hm"), _T("root.hm")}},
	{_T(""), ZRD_ROOT_UPR, _T(".HM"), {_T("$$ROOT$$.HM"), NULL}},
	{_T(""), ZRD_ROOT, _T(".hpj"), {_T("$$root$$.hpj"), _T("root.hpj")}},
	{_T(""), ZRD_ROOT_UPR, _T(".HPJ"), {_T("$$ROOT$$.HPJ"), NULL}},
	{_T(""), ZRD_ROOT, _T(".cnt"), {_T("$$root$$.cnt"), _T("root.cnt")}},
	{_T(""), ZRD_ROOT, _T(".clw"), {_T("$$root$$.clw"), _T("root.clw")}},
	{_T(""), ZRD_ROOT, _T(".reg"), {_T("$$root$$.reg"), _T("root.reg")}},
	{_T(""), ZRD_ROOT, _T(".def"), {_T("$$root$$.def"), _T("root.def")}},
	{_T(""), ZRD_ROOT, _T(".odl"), {_T("$$root$$.odl"), _T("root.odl")}},
	{_T(""), ZRD_ROOT, _T(".tlb"), {_T("$$root$$.tlb"), _T("root.tlb")}},
	{_T(""), ZRD_ROOT, _T(".HLP"), {_T("$$root$$.hlp"), _T("root.hlp")}},
	{_T(""), ZRD_ROOT, _T(".LOG"), {_T("$$root$$.log"), _T("root.log")}},
	{_T(""), ZRD_R_FILE, _T(".reg"), {_T("$$root$$Mac.reg"), _T("MacRoot.reg")}},
	{_T(""), ZRD_R_FILE, _T(".r"), {_T("$$root$$Mac.r"), _T("root.r")}},
	{_T(""), ZRD_ROOT, _T(".r"), {_T("$$root$$.r"), _T("root.r")}},
	{_T(""), ZRD_ROOT, _T(".pch"), {_T("$$root$$.pch"), NULL}},
	{_T(""), ZRD_ROOT, _T("DLL"), {_T("$$safe_root$$DLL"), NULL}},
	{_T("library "), ZRD_CLASS, _T(""), {_T("library $$root$$"), NULL}},// (root.odl)
	{_T("IID_I"), ZRD_DOC, _T(""), {_T("IID_I$$Doc$$"), NULL}},
	{_T("IDD_"), ZRD_SAFE_ROOT, _T("_"), {_T("IDD_$$SAFE_ROOT$$_"), NULL}},
	{_T("C"), ZRD_CLASS, _T("App"), {_T("C$$Safe_root$$App"), NULL}},
	{_T("C"), ZRD_CLASS, _T("Doc"), {_T("C$$Safe_root$$Doc"), NULL}},
	{_T("C"), ZRD_CLASS, _T("View"), {_T("C$$Safe_root$$View"), NULL}},
	{_T("C"), ZRD_CLASS, _T("Set"), {_T("C$$Safe_root$$Set"), NULL}},
	{_T("C"), ZRD_CLASS, _T("CntrItem"), {_T("C$$Safe_root$$CntrItem"), NULL}},
	{_T("C"), ZRD_CLASS, _T("SrvrItem"), {_T("C$$Safe_root$$SrvrItem"), NULL}},
	{_T("C"), ZRD_CLASS, _T("Dlg"), {_T("C$$Safe_root$$Dlg"), NULL}},
	{_T(""), ZRD_FILEBASE, _T("Doc."), {_T("$$root$$Doc."), _T("Doc.")}},
	{_T(""), ZRD_FILEBASE, _T("View."), {_T("$$root$$View."), _T("View.")}},
	{_T(""), ZRD_FILEBASE, _T("Set."), {_T("$$root$$Set."), _T("RecSet.")}},
	{_T(""), ZRD_FILEBASE, _T("Dlg."), {_T("$$root$$Dlg."), _T("Dialog.")}},
	{_T("m_"), ZRD_ROOT, _T("Set"), {_T("m_$$safe_root$$Set"), NULL}},
	{_T("IDR_"), ZRD_DOC_UPR, _T("TYPE"), {_T("IDR_$$DOC$$TYPE"), NULL}},
	{_T("dispinterface I"), ZRD_DOC, _T(""), {_T("dispinterface I$$Doc$$"), NULL}},
	{_T("\\n"), ZRD_DOC, _T("\\n"), {_T("\\n$$Doc$$\\n"), NULL}},
	{_T("\""), ZRD_ROOT, _T("\""), {_T("\"$$root$$\""), NULL}},
	{_T("\""), ZRD_CLASS, _T("\""), {_T("\"$$Root$$\""), NULL}},
	{_T("= "), ZRD_ROOT, _T(""), {_T("= $$Root$$"), NULL}},
	{_T("= "), ZRD_DOC, _T(""), {_T("= $$Doc$$"), NULL}},
	{_T("\""), ZRD_ROOT_UPR, _T(" MFC Extension DLL"), {_T("\"$$ROOT$$ MFC Extension DLL"), NULL}},
	{_T("\""), ZRD_ROOT_UPR, _T(" MFC Application"), {_T("\"$$ROOT$$ MFC Application"), NULL}},
	{_T("\""), ZRD_ROOT_UPR, _T("\\0\""), {_T("\"$$ROOT$$\\0\""), NULL}},
	{_T("\""), ZRD_ROOT_UPR, _T(" Dynamic Link Library"), {_T("\"$$ROOT$$ Dynamic Link Library"), NULL}},
	{_T(""), ZRD_ROOT, _T(" application"), {_T("$$root$$ application"), NULL}},
	{_T(""), ZRD_ROOT, _T(" Application"), {_T("$$root$$ Application"), NULL}},
	{_T(""), ZRD_CLASS, _T(".Application"), {_T("$$Safe_root$$.Application"), NULL}},
	{_T("coclass "), ZRD_CLASS, _T(""), {_T("coclass $$Safe_root$$"), NULL}},
	{_T(""), ZRD_ROOT_UPR, _T(" application"), {_T("$$ROOT$$ application"), NULL}},
	{_T(""), ZRD_ROOT_UPR, _T(" Application"), {_T("$$ROOT$$ Application"), NULL}},
	{_T(""), ZRD_ROOT_UPR, _T(" DLL"), {_T("$$ROOT$$ DLL"), NULL}},
	{_T("\""), ZRD_ROOT, _T(" Version 1.0"), {_T("\"$$Root$$ Version 1.0"), NULL}},
	{_T("\"&About "), ZRD_ROOT, _T("..."), {_T("\"&About $$Root$$..."), NULL}},
	{_T("\"About "), ZRD_ROOT, _T("\""), {_T("\"About $$Root$$\""), NULL}},
	{_T("Make help for Project "), ZRD_ROOT_UPR, _T(""), {_T("Make help for Project $$ROOT$$"), NULL}},
	{_T("// "), ZRD_ROOT, _T(" bundle resource ID"), {_T("// $$root$$ bundle resource ID"), NULL}},
	{_T("// "), ZRD_ROOT, _T(" document"), {_T("// $$root$$ document"), NULL}},
	{_T("// "), ZRD_ROOT, _T(" signature"), {_T("// $$root$$ signature"), NULL}},
	{_T(""), ZRD_DOC, _T(" Document"), {_T("$$Doc$$ Document"), NULL}},
	{_T("MICROSOFT FOUNDATION CLASS LIBRARY : "), ZRD_ROOT, _T(""),
		{_T("MICROSOFT FOUNDATION CLASS LIBRARY : $$root$$"), NULL}},
	{_T(""), ZRD_CLASS, _T(".Document"), {_T("$$Doc$$.Document"), NULL}},
	{_T("\\n"), ZRD_MAC_TYPE, _T(" Files\""), {_T("\\n $$MAC_TYPE$$ Files\""), NULL}},
	{_T("'"), ZRD_MAC_TYPE, _T("'"), {_T("'$$MAC_TYPE$$'"), NULL}},
	{_T("\\n"), ZRD_MAC_TYPE, _T("\\n"), {_T("\\n$$MAC_TYPE$$\\n"), NULL}},
};

// Called when the zap dialog is dismissed.  It initializes the matches
//  array (m_pStrMatches) for the particular project's root name.
void CZap::SetRoot(LPCTSTR lpszDir, LPCTSTR lpszRoot)
{
	m_strRoot = lpszRoot;

	m_strRootDir = lpszDir;
	m_strRootDir.MakeLower();

	m_strGeneratedNewProjInfo.Empty();
	m_posTplName = NULL;

	InitMatches();
}

// Changes each space in str to an underscore
void SpaceToUnderscore(CString& str)
{
	LPCTSTR pch = str;
	for (int i=0; *pch != _T('\0'); i += _tclen(pch), pch = _tcsinc(pch))
	{
		if (str[i] == _T(' '))
			str.SetAt(i, _T('_'));
	}
}

void MakeSafeRoot(CString& tag, LPCTSTR szRoot)
{
	tag.Empty();

	const TCHAR* pch = szRoot;
	for( ; *pch != '\0'; pch = _tcsinc(pch))
	{
		if(_istalnum(*pch)  // Strip characters that cannot be in class names
		   || *pch == '_')  // valid chars are 'A'-'Z', 'a'-'z', '0'-'9', '_'
		{
			tag += *pch;
		}
	}
	if(tag.IsEmpty())       // An empty tag would produce: CApp, CDoc, and CView
		tag = "My";         // CView would become CMyView, so just make tag="My"

	if (_istdigit(tag[0]))  // Can't begin with number
		tag = "My" + tag;

	tag.SetAt(0, (TCHAR)_totupper(tag[0]));     // make 1st character upper

	if (!tag.Compare(_T("Custom")))         // rare, probably tester only, case
		tag = "My" + tag;

	// Limit length of tag so generated class names don't exceed _MAX_SYMBOL
	#define MAX_ADDED_TO_TAG 10
	#define _MAX_SYMBOL 64
	if (tag.GetLength() + MAX_ADDED_TO_TAG > _MAX_SYMBOL)
		tag = tag.Left(_MAX_SYMBOL - MAX_ADDED_TO_TAG);
}

// This fills the array m_pStrMatches with an entry for each search string
//  from zrdGeneral.  Each entry is the concatenation of the three components
//  of the search string (i.e., Pre, RootType, and Post).
// Example (loosely expressed):
//  m_pStrMatches[0] = "" + ZRD_ROOT + ".h"
//  m_pStrMatches[1] = "" + ZRD_ROOT_UPR ".H"
//  etc.
void CZap::InitMatches()
{
	// First, translate ZRD_ROOT, ZRD_ROOT_UPR, etc. into strings based
	//  on the name of the "zappee" (i.e., project off of which we're
	//  basing the custom AppWizard).

	CString strRootTypes[NUM_ROOT_TYPES];
	strRootTypes[ZRD_ROOT] = m_strRoot;

	strRootTypes[ZRD_ROOT_UPR] = strRootTypes[ZRD_ROOT];
	strRootTypes[ZRD_ROOT_UPR].MakeUpper();

	CString strSafeRoot;
	MakeSafeRoot(strSafeRoot, m_strRoot);
	strRootTypes[ZRD_SAFE_ROOT] = strSafeRoot;
	strRootTypes[ZRD_SAFE_ROOT].MakeUpper();

	strRootTypes[ZRD_CLASS] = m_strRoot;
	strRootTypes[ZRD_CLASS].SetAt(0, (TCHAR)_totupper(strRootTypes[ZRD_CLASS][0]));

	strRootTypes[ZRD_FILEBASE] = m_strRoot;

	strRootTypes[ZRD_DOC] = m_strRoot.Left(6);
	strRootTypes[ZRD_DOC].SetAt(0, (TCHAR)_totupper(strRootTypes[ZRD_DOC][0]));

	strRootTypes[ZRD_DOC_UPR] = strRootTypes[ZRD_DOC];
	strRootTypes[ZRD_DOC_UPR].MakeUpper();

	strRootTypes[ZRD_MAC_TYPE] = m_strRoot.Left(4);
	int nLen = strRootTypes[ZRD_MAC_TYPE].GetLength();
	if (nLen < 4)
	{
		CString strPad(_T(' '), 4 - nLen);
		strRootTypes[ZRD_MAC_TYPE] += strPad;
	}
	strRootTypes[ZRD_MAC_TYPE].MakeUpper();

	strRootTypes[ZRD_R_FILE] = m_strRoot + _T("Mac");

	strRootTypes[ZRD_R_FILE_UPR] = strRootTypes[ZRD_R_FILE];
	strRootTypes[ZRD_R_FILE_UPR].MakeUpper();

	// Now, using these values, traverse zrdGeneral and concatenate the three
	//  components of each search string.  Store the value in the
	//  corresponding entry of the array m_pStrMatches.

	FreeMatches();
	int nSize = sizeof(zrdGeneral)/sizeof(ZapRawData);
	m_pStrMatches = new CString[nSize];

	for (int i=0; i < nSize; i++)
	{
		m_pStrMatches[i] =
			zrdGeneral[i].lpszPre +
			strRootTypes[zrdGeneral[i].nRootType] +
			zrdGeneral[i].lpszPost;
	}
}

void CZap::FreeMatches()
{
	if (m_pStrMatches != NULL)
		delete [sizeof(zrdGeneral)/sizeof(ZapRawData)] m_pStrMatches;
	m_pStrMatches = NULL;
}

CZap::~CZap()
{
	ASSERT(m_posTplName == NULL);
	FreeMatches();
}


void CZap::ZapLine(CString& strLine, int iReplace /* = 0 */)
{
	ASSERT(m_pStrMatches != NULL);
	ASSERT(0 <= iReplace && iReplace <= 1);

	for (int i=0; i < sizeof(zrdGeneral)/sizeof(ZapRawData); i++)
	{
		int nStart = strLine.Find(m_pStrMatches[i]);
		if (nStart != -1)
		{
			if (zrdGeneral[i].lpszReplace[iReplace] != NULL)
			{
				strLine = strLine.Left(nStart)              // Region to left of match
					+ zrdGeneral[i].lpszReplace[iReplace]   // String to replace match with
					+ (((LPCTSTR) strLine) + nStart + m_pStrMatches[i].GetLength());
						// String to right of match
				i--;                // In case there are more occurrences of this match
			}
		}
	}
}

void CZap::ZapFileName(LPCTSTR lpszFileName, CString& rStrZappedFile, int iReplace /* = 0 */)
{
	rStrZappedFile = lpszFileName;
	ZapLine(rStrZappedFile, iReplace);
}
