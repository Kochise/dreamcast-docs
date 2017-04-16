
// Basic wrappers for Win32

#ifndef _WIN32_H_
#define _WIN32_H_

BSTR DLLAPI GetFullPath(
    BSTR bsFileName,
	Variant * pvFilePart, 
	Variant * pvExtPart,
	Variant * pvDirPart
	);
	
BSTR DLLAPI SearchDirs(
    BSTR bsPath,
    Variant vExtension,
    Variant vPath,
    Variant * pvFilePart,
    Variant * pvExtPart,
    Variant * pvDirPart
    );

BSTR DLLAPI GetTempFile(
    BSTR bsPathName,
	BSTR bsPrefixString
	);

BSTR DLLAPI GetTempDir(
	void
	);

// Helper for Basic wrappers
void GetDirExt(
	LPWSTR pwchSpec, 
	Long * piDirPart,
	Long * piExtPart
	);

#endif // _WIN32_H_
