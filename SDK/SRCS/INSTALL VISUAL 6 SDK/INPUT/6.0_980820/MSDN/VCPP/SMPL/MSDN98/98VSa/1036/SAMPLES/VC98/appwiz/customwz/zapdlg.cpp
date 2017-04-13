// zapdlg.cpp : implementation file
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "zapdlg.h"
#include "sampleaw.h"
#include "zap.h"
#include "paint.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//static CTypedPtrMap<CMapStringToPtr, CString, int> g_TemplateNameCollisions;
static CMapStringToPtr g_TemplateNameCollisions;
CStringList g_TemplateNames;

static BOOL FindDuplicateFileNames(LPTSTR pstrPath, CMapStringToPtr &rmapFileNamesFound);

void MakeTemplateName(CString& strTemplateName, LPCTSTR szFileName)
{
	// Make template name upper-case
	strTemplateName = szFileName;
	strTemplateName.MakeUpper();

	// See if this template name collides with others we're using
	int nNextDigit;
	if (g_TemplateNameCollisions.Lookup(strTemplateName, (void *&)nNextDigit))
	{
		// There is a collision, so append a digit to the name & update
		//  collisions map
		CString strOldTemplateName = strTemplateName;
		strTemplateName.Format("%s%d", (LPCTSTR) strOldTemplateName, nNextDigit);
		g_TemplateNameCollisions[strOldTemplateName] = (void *) ++nNextDigit;

		// Call self recusively to make sure the new name doesn't collide
		MakeTemplateName(strTemplateName, strTemplateName);
	}
	else
	{
		// No collision, so update collision map for the future.
		g_TemplateNameCollisions[strTemplateName] = (void *)2;
	}
}

// This determines what type of project we're zapping.  The heuristic used:
// if no TARGTYPE line in the project makefile (or it doesn't fit criteria below), type is unknown
// TARGTYPE line has 1 as low byte of the value, type is projExe
// TARGTYPE line has 2 as low byte of the value, type is projDLL
// TARGTYPE line has 8 as high byte of the value, type is projJava
enProjType GetProjectType(LPCTSTR lpszProjName)
{
	#define SIZEBUF 256
	char szBuf[SIZEBUF];

	DWORD dwTargType = 0;
	CStdioFile file(lpszProjName, CFile::modeRead | CFile::typeText);

	// Read through makefile line by line
	while (file.ReadString(szBuf, SIZEBUF-1) != NULL)
	{
		// Is this line a "# TARGTYPE" line?  If so, grab the TARGTYPE value
		if (sscanf(szBuf, _T("# TARGTYPE \"%*[^\"]\" 0x%lx"), &dwTargType) == 1)
			break;
	}

	// Check the TARGTYPE value to see what it is
	if ((dwTargType & 0xFF00) == 0x800)
		return projJava;
	else if ((dwTargType & 0x00FF) == 1)
		return projExe;
	else if ((dwTargType & 0x00FF) == 2)
		return projDLL;
	else
		return projUnknown;
}


// This helper (used in TraverseDirectory) doubles occurrences of the backslash
//  character in szPath, so the path can be enclosed in double-quotes in the
//  resource file.
void DoubleSlashes(CString& strPathDblSlashes, LPCTSTR szPath)
{
	strPathDblSlashes.Empty();
	while (*szPath != '\0')
	{
		if (*szPath == '\\')
			strPathDblSlashes += "\\\\";
		else
			strPathDblSlashes += *szPath;
		szPath = _tcsinc(szPath);
	}
}

// This helper (used in TraverseDirectory) determines whether we should skip
//  zapping files in the given directory based on its name.
inline BOOL ShouldSkipDirectory(LPCTSTR szDir)
{
	return (!_tcscmp(szDir, _T(".")) || !_tcscmp(szDir, _T(".."))
		|| !_tcsicmp(szDir, _T("debug")) || !_tcsicmp(szDir, _T("release"))
		|| !_tcsicmp(szDir, _T("windebug")) || !_tcsicmp(szDir, _T("winrel"))
		|| !_tcsicmp(szDir, _T("pmcdebug")) || !_tcsicmp(szDir, _T("pmcrel"))
		|| !_tcsicmp(szDir, _T("macdebug")) || !_tcsicmp(szDir, _T("macrel")));
}

// This helper (used in TraverseDirectory) determines whether we should skip
//  zapping a file based on its extension.
inline BOOL ShouldSkipFile(LPCTSTR szExt)
{
	return (szExt != NULL &&
		(!_tcsicmp(szExt, _T(".mak")) || !_tcsicmp(szExt, _T(".vcp")) || !_tcsicmp(szExt, _T(".aps"))
			|| !_tcsicmp(szExt, _T(".sbr")) || !_tcsicmp(szExt, _T(".plg")) || !_tcsicmp(szExt, _T(".obj"))
			|| !_tcsicmp(szExt, _T(".pch")) || !_tcsicmp(szExt, _T(".res")) || !_tcsicmp(szExt, _T(".ilk"))
			|| !_tcsicmp(szExt, _T(".rsc")) || !_tcsicmp(szExt, _T(".bsc")) || !_tcsicmp(szExt, _T(".exe"))
			|| !_tcsicmp(szExt, _T(".bld")) || !_tcsicmp(szExt, _T(".opt")) || !_tcsicmp(szExt, _T(".pjx"))
			|| !_tcsicmp(szExt, _T(".dll")) || !_tcsicmp(szExt, _T(".pdb")) || !_tcsicmp(szExt, _T(".ncb"))
			|| !_tcsicmp(szExt, _T(".mdp")) || !_tcsicmp(szExt, _T(".dsw")) || !_tcsicmp(szExt, _T(".dsp"))));
}

// This recursive function is called from SetProjectFilesMacros with references
//  to CStrings that correspond to template macros we're setting.  It
//  traverses the given directory and updates these strings with names of
//  files it will zap into templates for the generated custom AppWizard.
void TraverseDirectory(const CString& strProjDir, const CString& strSubdir, CString& strProjFiles,
	CString& strTemplateSubdirs, CString& strTemplateRsc, CString& strGeneratedNewProjInfoDirs)
{
	WIN32_FIND_DATA ffd;
	HANDLE hSearch = ::FindFirstFile(strProjDir + strSubdir + _T("*.*"), &ffd);
	if (hSearch == INVALID_HANDLE_VALUE)    // Bad search handle
	{
		if (strSubdir.IsEmpty())
			// We've hit a bad search handle immediately after being called--
			//  the project directory is invalid.  Throw exception.
			ReportAndThrow(IDP_BAD_PROJDIR, strProjDir + strSubdir);
		else
			// We've hit a bad search handle in a recursive call--
			//  empty project subdirectory.  Just ignore it.
			return;
	}

	do
	{
		if (ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			// If it's a directory, recursively call self with the directory,
			//  and note the directory structure in the custom AppWizard's newproj.inf
			if (ShouldSkipDirectory(ffd.cFileName))
				continue;

			CString strNewSubdir = (strSubdir + ffd.cFileName) + _T('\n');
			strGeneratedNewProjInfoDirs += _T('/') + strNewSubdir;
			strTemplateSubdirs += _T('/') + (_T("template\\") + strNewSubdir);
			CString strNewDir = strSubdir;
			strNewDir += ffd.cFileName;
			strNewDir += _T('\\');
			TraverseDirectory(strProjDir, strNewDir, strProjFiles, strTemplateSubdirs,
				strTemplateRsc, strGeneratedNewProjInfoDirs);
			continue;
		}

		// Skip if it's a file we know we shouldn't copy (e.g., the makefile, .vcp file,
		//  .aps file, etc.).
		LPCTSTR lpch = _tcsrchr(ffd.cFileName, _T('.'));
		if (ShouldSkipFile(lpch))
			continue;

		// Skip if it has no length
		if (ffd.nFileSizeLow == 0 && ffd.nFileSizeHigh == 0)
			continue;

		// Zap the file's name
		CString strRootFile;
		sampleaw.m_Zap.ZapFileName(ffd.cFileName, strRootFile, 1);

		// Now that we have the info we need, update the strings we were passed

		// First, the string used in CUSTMWZ.DLL's newproj.inf:
						// The original project file...
		strProjFiles += (_T("#") + strProjDir + strSubdir + ffd.cFileName)
							// File to emit as custom AppWizard's template...
							+ (_T("\ttemplate\\") + strSubdir + strRootFile + _T('\n'));

		// Next, the string used in CUSTMWZ.DLL's root.rc (i.e., the
		//  generated custom AppWizard's resource file).
		CString strSubdirDblSlashes;
		DoubleSlashes(strSubdirDblSlashes, strSubdir);
		CString strTemplateName;
		MakeTemplateName(strTemplateName, strRootFile);
		strTemplateRsc += strTemplateName +
			_T("\tTEMPLATE DISCARDABLE\t\"template\\\\") + strSubdirDblSlashes + strRootFile +
			_T("\"\n");
		// Remember the template name for later, when we're generating lines in
		//  CUSTMWZ.DLL's newnwprj.inf (i.e., the generated custom AppWizard's
		//  newproj.inf).
		g_TemplateNames.AddTail(strTemplateName);

	}
	while (::FindNextFile(hSearch,  &ffd));
	::FindClose(hSearch);
}


// This function drives it all.  It's called just before the zap dialog is
//  dismissed, and coordinates setting the template macros that correspond
//  with the set of files to be zapped.
void SetProjectFilesMacros(LPCTSTR lpszSrcProjName)
{
	// In order to allow the user to click "Finish" from the first step,
	//  we should gracefully handle the case that no project was named to zap.
	if (lpszSrcProjName == NULL || *lpszSrcProjName == _T('\0'))
	{
		// If project name not specified, empty out the zapper macros
		DefineBoolMacro(_T("ZAP_FULL_PATH"), FALSE);
		DefineBoolMacro(_T("PROJECT_FILES"), FALSE);
		DefineBoolMacro(_T("GENERATED_NEWPROJ_INF_FILES"), FALSE);
		DefineBoolMacro(_T("GENERATED_NEWPROJ_INF_DIRS"), FALSE);
		DefineBoolMacro(_T("TEMPLATE_RSC"), FALSE);
		return;
	}

	// Here, we have a valid, non-NULL project name to zap.  First, get its
	//  full path name
	CString strFullPath;
	_tfullpath(strFullPath.GetBuffer(_MAX_PATH), lpszSrcProjName, _MAX_PATH);
	strFullPath.ReleaseBuffer();
	DefineStringMacro(_T("ZAP_FULL_PATH"), strFullPath);

	// Divide the path name into the various components.
	CString strDrive, strDir, strName, strExt;
	_tsplitpath(strFullPath, strDrive.GetBuffer(_MAX_DRIVE), strDir.GetBuffer(_MAX_DIR),
		strName.GetBuffer(_MAX_FNAME), strExt.GetBuffer(_MAX_EXT));
	strDrive.ReleaseBuffer();
	strDir.ReleaseBuffer();
	strName.ReleaseBuffer();
	strExt.ReleaseBuffer();
	sampleaw.m_Zap.SetRoot(strDir, strName);
	DefineStringMacro(_T("ZAP_SRC_PROJ"), strName + strExt);
	strDir = strDrive + strDir;

	// Now, declare the strings that will be passed to TraverseDirectory, and
	//  filled with lists of the files we'll zap.  These strings will later
	//  be used as template macros.
	CString strProjFiles;               // Will be $$PROJECT_FILES$$ in newproj.inf
	CString strTemplateSubdirs;             // Will be $$PROJECT_DIRS$$ in newproj.inf
	CString strGeneratedNewProjInfoDirs;// Will be $$GENERATED_NEWPROJ_INF_DIRS$$
	CString strTemplateRsc;             // Will be $$TEMPLATE_RSC$$ in root.rc

	// Set their values
	g_TemplateNameCollisions.RemoveAll();               // Initialize g_TemplateNameCollisions
	g_TemplateNameCollisions[_T("NEWPROJ.INF")] = (void *)2;    //  w/ the two canned template names
	g_TemplateNameCollisions[_T("CONFIRM.INF")] = (void *)2;
	g_TemplateNames.RemoveAll();
	TraverseDirectory(strDir, _T(""), strProjFiles, strTemplateSubdirs, strTemplateRsc, strGeneratedNewProjInfoDirs);

	// Set the template macros to their values
	DefineStringMacro(_T("PROJECT_FILES"), strProjFiles);
	DefineStringMacro(_T("TEMPLATE_SUBDIRS"), strTemplateSubdirs);
	DefineStringMacro(_T("GENERATED_NEWPROJ_INF_DIRS"), strGeneratedNewProjInfoDirs);
	DefineStringMacro(_T("TEMPLATE_RSC"), strTemplateRsc);
}


/////////////////////////////////////////////////////////////////////////////
// CZapDlg dialog


CZapDlg::CZapDlg()
	: CAppWizStepDlg(CZapDlg::IDD)
{
	//{{AFX_DATA_INIT(CZapDlg)
	m_strProjName = _T("");
	//}}AFX_DATA_INIT
}


void CZapDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZapDlg)
	DDX_Text(pDX, IDC_PROJ_NAME, m_strProjName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZapDlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CZapDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CZapDlg message handlers

// Validate the name of the project to zap, and set zap-related template
//  macros before dismissing
BOOL CZapDlg::OnDismiss()
{
	UpdateData(TRUE);

	// If the user specifies a nonempty, nonexistent path, balk
	if (!m_strProjName.IsEmpty()
		&& GetFileAttributes(m_strProjName) == 0xffffffff)
		return ReportError(IDP_ZAP_CANT_OPEN_FILE, m_strProjName);
	else if (m_strProjName.IsEmpty())   // no project name, no checking we can do
		return TRUE;

	// WARNING: continuing past this point with an empty project name could yield
	// unpredictable actions as _splitpath doesn't check for a non-NULL path
	// before trying to break it up into drive and directory.

	CHAR rgchPathBuffer[_MAX_PATH];
	CHAR rgchDrive[_MAX_DRIVE];
	CHAR rgchDirectory[_MAX_DIR];

	_splitpath(m_strProjName, rgchDrive, rgchDirectory, NULL, NULL);
	_makepath(rgchPathBuffer, rgchDrive, rgchDirectory, NULL, NULL);

	CMapStringToPtr map;

	BOOL fFoundDuplicate = FindDuplicateFileNames(rgchPathBuffer, map);

	if (fFoundDuplicate)
		return ReportError(IDP_ZAP_BAD_PROJECT, m_strProjName);

	if (m_strProjName.IsEmpty())
		return ReportError(IDP_ZAP_CANT_OPEN_FILE, m_strProjName);

	// Now set the macros corresponding to the files we zap into templates.
	//  This may throw an exception if it runs into an error.  In that
	//  case, we'll return FALSE.
	TRY
	{
		enProjType projType = GetProjectType(m_strProjName);
		if (projType != projExe && projType != projDLL)
			return ReportError(IDP_ZAP_NOT_CPP, m_strProjName);

		DefineBoolMacro(_T("CREATE_DLL_PROJECT"), projType == projDLL);
		SetProjectFilesMacros(m_strProjName);
	}
	CATCH(CFileException, e)
	{
		return ReportError(IDP_ZAP_CANT_OPEN_FILE, m_strProjName);
	}
	AND_CATCH(CException, e)
	{
		return FALSE;
	}
	END_CATCH

	// If we got this far, we've successfully built our list of files
	//  to zap.  We're ready to continue.
	return TRUE;
}

#define BROWSE_DLG_HELP_ID 17304

// Handle the "Browse..." button by popping up a file navigator.
void CZapDlg::OnBrowse()
{
	CString strBrowseTitle, strFilterString;
	strBrowseTitle.LoadString(IDS_BROWSE_TITLE);
	strFilterString.LoadString(IDS_BROWSE_FILTER);

	CFileDialog dlg(
		TRUE,                                       // Open File Dialog
		_T("dsp"),                                  // Default extension
		NULL,                                       // No default filename
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,     // OPENFILENAME flags
		strFilterString);   // Filter strings
	dlg.m_ofn.lpstrTitle = strBrowseTitle;
	dlg.SetHelpID(BROWSE_DLG_HELP_ID);
	if (dlg.DoModal() == IDOK)
		m_strProjName = dlg.GetPathName();

	UpdateData(FALSE);
}

#define STEP2_LEFT          8
#define STEP2_TOP           40
#define STEP2_WIDTH         179
#define STEP2_HEIGHT        224

// Override OnPaint to draw the one static picture on the left side
void CZapDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	PaintBackground(&dc, this);

	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(&dc))
		return;

	// Picture
	PaintBitmap(IDB_STEP2, STEP2_LEFT, STEP2_TOP, STEP2_WIDTH, STEP2_HEIGHT, &dc, &dcMem);
}

BOOL FindDuplicateFileNames(LPTSTR ptstrPath, CMapStringToPtr &rmap)
{
	WIN32_FIND_DATA wfd;

	BOOL fResult = FALSE; // Assume no duplicates

	size_t cchOldLength;

#if defined(_UNICODE)
	cchOldLength = wcslen(ptstrPath);
#else
	cchOldLength = strlen(ptstrPath);
#endif

	TCHAR *ptchOldNull = &ptstrPath[cchOldLength];

	_tcscpy(ptchOldNull, TEXT("*.*"));

	HANDLE hFind = ::FindFirstFile(ptstrPath, &wfd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		// We started a good search.  Let's handle each file now.
		for (;;)
		{
			if ((_tcscmp(wfd.cFileName, TEXT(".")) != 0) &&
				(_tcscmp(wfd.cFileName, TEXT("..")) != 0))
			{
				if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
				{
					// We've got a subdirectory.  Recurse.
					_tcscpy(ptchOldNull, wfd.cFileName);
					_tcscat(ptchOldNull, TEXT("\\"));

					if (FindDuplicateFileNames(ptstrPath, rmap))
					{
						fResult = TRUE;
						break;
					}
				}
				else
				{
					// First, canonicalize the case of the file...
					_tcsupr(wfd.cFileName);

					VOID *pvTemp;

					// If it's in the map, look out!
					if (rmap.Lookup(wfd.cFileName, pvTemp))
					{
						fResult = TRUE;
						break;
					}

					// It wasn't there and it isn't a generated file we don't care about; put a NULL in the list.
					CString strName = wfd.cFileName;
					CString strExt;
					int index = strName.ReverseFind('.');
					if( index != -1 ){
						strExt = strName.Right( strName.GetLength() - index );
					}
					if( strExt != ".EXE" && strExt != ".OBJ" && strExt != ".RES" && strExt != ".CNT" && strExt != ".HLP" ) {
						rmap.SetAt(wfd.cFileName, NULL);
					}
				}
			}

			// I hate to lose status if something more erroneous occurred
			// here, but it seems harmless.  -mgrier 6/12/96
			if (!::FindNextFile(hFind, &wfd))
				break;
		}

		::FindClose(hFind);
	}

	ptchOldNull = TEXT('\0');

	return fResult;
}
