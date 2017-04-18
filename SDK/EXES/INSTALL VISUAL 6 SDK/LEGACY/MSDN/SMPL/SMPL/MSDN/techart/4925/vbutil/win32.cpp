/* WIN32.CPP - Basic-friendly wrappers for Win32 API functions:

        Win32 Routine           Basic-Friendly Version
        -------------           ----------------------
        GetFullPathName         GetFullPath
        GetTempFileName         GetTempFile
        GetTempPath             GetTempDir
        SearchPath              SearchDirs

 */

#include "VBUtil.H"
#include "OleType.H"
#include "Win32.H"

const Long ctchTempMax = 256;

// Win32 functions with Basic interface

/* GetFullPath - Basic version of Win32 API emulation routine. It returns a
 * BSTR, and indexes to the file name, directory, and extension parts of the
 * full name.
 *
 * Input:  sFileName - file to be qualified in one of these formats:
 *
 *              [relpath\]file.ext
 *              \[path\]file.ext
 *              .\[path\]file.ext
 *              d:\[path\]file.ext
 *              ..\[path\]file.ext
 *              \\server\machine\[path\]file.ext
 *          iName - variable to receive file name position
 *          iDir - variable to receive directory position
 *          iExt - variable to receive extension position
 *
 * Return: Full path name, or an empty string on failure
 *
 * Errors: Any of the following:
 *              ERROR_BUFFER_OVERFLOW      = 111
 *              ERROR_INVALID_DRIVE        = 15
 *              ERROR_CALL_NOT_IMPLEMENTED = 120
 *              ERROR_BAD_PATHNAME         = 161
 */

//@B GetFullPath
BSTR DLLAPI GetFullPath(
    BSTR bsFileName,
    Variant * pvFilePart,
    Variant * pvExtPart,
    Variant * pvDirPart
    )
{
  try {
    String sFileName = bsFileName;
    LPTSTR ptchFilePart;
    Long ctch;
    TCHAR atch[3];

    // Get the path size, then create BString of that size
    ctch = GetFullPathName(sFileName, 1, atch, &ptchFilePart);
    Long err = (Long)GetLastError();
    if (ctch == 0) throw (err ? err : ERROR_INVALID_PARAMETER);
    String sRet(ctch - 1);
    ctch = GetFullPathName(sFileName, ctch, Buffer(sRet), &ptchFilePart);
    if (ctch == 0) throw (Long)GetLastError();
    ASSERT(cch <= ctchTempMax);

    // Get the directory, file, and extension positions
    Long iDirPart = 0, iFilePart = 0, iExtPart = 0;
    if (!sRet.IsEmpty() && ctch) {
        iFilePart = ptchFilePart - (LPCTSTR)sRet + 1;
        GetDirExt(sRet, &iDirPart, &iExtPart);
    }
    // Cram into variants regardless of missing optional arguments
    *pvDirPart = iDirPart;
    *pvFilePart = iFilePart;
    *pvExtPart = iExtPart;
    return sRet;
  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  }
}
//@E GetFullPath

//@B GetTempFile
BSTR DLLAPI GetTempFile(
    BSTR bsPathName,
    BSTR bsPrefix
    )
{
  try {
    String sPathName = bsPathName;
    String sPrefix = bsPrefix;
    String sRet(ctchTempMax); 
    if (GetTempFileName(sPathName, sPrefix, 0, Buffer(sRet)) == 0) {
        throw (Long)GetLastError();
    }
    sRet.ResizeZ();
    return sRet;
  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  }
}
//@E GetTempFile

BSTR DLLAPI GetTempDir()
{
  try {
    Long ctch;
    TCHAR atch[3];
    ctch = GetTempPath(1, atch);
    if (ctch == 0) throw (Long)GetLastError();
    String sRet(ctch - 1);
    if (GetTempPath(ctch, Buffer(sRet)) == 0) throw (Long)GetLastError();
    return sRet;
  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  }
}

//@B SearchDirs
BSTR DLLAPI SearchDirs(
    BSTR bsFileName,
    Variant vExt,
    Variant vPath,
    Variant * pvFilePart,
    Variant * pvExtPart,
    Variant * pvDirPart
    )
{
  try {
    LPTSTR ptchFilePart;
    Long ctch;
    String sFileName = bsFileName;
    if (sFileName.IsEmpty()) throw ERROR_INVALID_PARAMETER;

    // Handle missing or invalid extension or path
    String sExt;        // Default initialize to empty
    if (!vExt.IsMissing() && vExt.Type() != VT_EMPTY) {
        if (vExt.Type() != VT_BSTR) throw ERROR_INVALID_PARAMETER;
        sExt = vExt;
    }
    String sPath;       // Default initialize to empty
    if (!vPath.IsMissing() && vPath.Type() != VT_EMPTY) {
        if (vPath.Type() != VT_BSTR) throw ERROR_INVALID_PARAMETER;
        sPath = vPath;
    }
    
    // Get the file (treating empty strings as NULL pointers)
    String sRet(ctchTempMax);
    ctch = SearchPath(sPath.NullIfEmpty(), sFileName, 
                      sExt.NullIfEmpty(), ctchTempMax, 
                      Buffer(sRet), &ptchFilePart);
    ASSERT(ctch <= ctchTempMax);
    Long iDirPart = 0, iFilePart = 0, iExtPart = 0;
    if (ctch == 0) {
        sRet.Nullify();
        // Not finding a file returns zero, but isn't an error
        Long err = (Long)GetLastError();
        if (err) throw err;
    } else {
        // Calculate the file part offsets
        iFilePart = ptchFilePart - (LPCTSTR)sRet + 1;
        GetDirExt(sRet, &iDirPart, &iExtPart);
        // Resize must be after calculation because it may move ANSI buffer
        sRet.Resize(ctch);
    }
    // Cram into variants regardless of missing optional arguments
    *pvDirPart = iDirPart;
    *pvFilePart = iFilePart;
    *pvExtPart = iExtPart;
    return sRet;
  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  }
}
//@E SearchDirs

void GetDirExt(
    LPWSTR pwchSpec,
    Long * piDirPart,
    Long * piExtPart
    )
{
    LPWSTR pwch;
    WCHAR wch = towupper(*pwchSpec);

    // If in format d:\path\name.ext, return 3
    if ((wch >= L'A') &&
        (wch <= L'Z') &&
        (*(pwchSpec + 1) == L':') &&
        (*(pwchSpec + 2) == L'\\')) {
        *piDirPart = 3;
    // If in format \\machine\share\path\name.ext, return position of \path
    } else {
        ASSERT(wch == L'\\');
        ASSERT(*(pwchSpec + 1) == L'\\');
        for (pwch = pwchSpec + 2; *pwch && (*pwch != '\\'); pwch++)
            ;
        for (; *pwch && (*pwch != L'\\'); pwch++)
            ;
        *piDirPart = pwch - pwchSpec;
    }
    // Find extension
    *piExtPart = wcslen(pwchSpec); // Assume no extension
    for (pwch = pwchSpec + wcslen(pwchSpec);pwch > pwchSpec; pwch--) {
        if (*pwch == '.') {
            *piExtPart = pwch - pwchSpec + 1;
            break;
        }
        if ((*pwch == '\\') || (*pwch == ':')) {
            break;
        }
    }
}

