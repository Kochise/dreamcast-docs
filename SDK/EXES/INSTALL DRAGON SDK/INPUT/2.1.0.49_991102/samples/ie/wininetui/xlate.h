/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * xlate.h
 *
 * Description
 *   String conversion macros. 
 ********************************************************************/

#ifndef _DEBUG
#define USES_CONVERSION int _convert; _convert
#else
#define USES_CONVERSION int _convert = 0
#endif

inline LPWSTR WINAPI AtlA2WHelper(LPWSTR lpw, LPCSTR lpa, int nChars)
{
	// verify that no illegal character present
	// since lpw was allocated based on the size of lpa
	// don't worry about the number of chars
	lpw[0] = '\0';
	MultiByteToWideChar(CP_ACP, 0, lpa, -1, lpw, nChars);
	return lpw;
}

inline LPSTR WINAPI AtlW2AHelper(LPSTR lpa, LPCWSTR lpw, int nChars)
{
	// These sesolve to nothing on CE
	//
	// vladimi : bail out if lpa or lpw is NULL, 
	// if lpa is produced by a macro such as W2A, there is a chance
	// that _alloca failed and lpa is NULL. Without this check
	// lpa[0] = '\0'; line below will crash us
	//
	if (!lpa || !lpw)
	{
		return NULL;
	}
	// verify that no illegal character present
	// since lpa was allocated based on the size of lpw
	// don't worry about the number of chars
	lpa[0] = '\0';
	WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, nChars, NULL, NULL);
	return lpa;
}

// Copy a Unicode string into an ANSI buffer
inline void strcpyAW(LPSTR lpszDst,  LPCWSTR lpwszSrc)
{
    // Need +1 to get NUL terminator copied
    AtlW2AHelper(lpszDst,  lpwszSrc, 2*lstrlenW(lpwszSrc) + 1);
}

// Copy an ANSI string into an Unicode buffer
inline void strcpyWA(LPWSTR lpwszDst, LPCSTR lpszSrc)
{
    // Need +1 to get NUL terminator copied
    AtlA2WHelper(lpwszDst, lpszSrc,  strlen(lpszSrc) + 1);
}

#define A2W(lpa) (\
	((LPCSTR)lpa == NULL) ? NULL : (\
		_convert = (strlen(lpa)+1),\
		AtlA2WHelper((LPWSTR) alloca(_convert*2), lpa, _convert)))

#define W2A(lpw) (\
	((LPCWSTR)lpw == NULL) ? NULL : (\
		_convert = (lstrlenW(lpw)+1)*2,\
		AtlW2AHelper((LPSTR) alloca(_convert), lpw, _convert)))

#define A2CW(lpa) ((LPCWSTR)A2W(lpa))
#define W2CA(lpw) ((LPCSTR)W2A(lpw))

#if defined(_UNICODE)
// in these cases the default (TCHAR) is the same as OLECHAR
	inline size_t ocslen(LPCOLESTR x) { return lstrlenW(x); }
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src) { return lstrcpyW(dest, src); }
	inline LPCOLESTR T2COLE(LPCTSTR lp) { return lp; }
	inline LPCTSTR OLE2CT(LPCOLESTR lp) { return lp; }
	inline LPOLESTR T2OLE(LPTSTR lp) { return lp; }
	inline LPTSTR OLE2T(LPOLESTR lp) { return lp; }
#elif defined(OLE2ANSI)
// in these cases the default (TCHAR) is the same as OLECHAR
	inline size_t ocslen(LPCOLESTR x) { return lstrlen(x); }
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src) { return lstrcpy(dest, src); }
	inline LPCOLESTR T2COLE(LPCTSTR lp) { return lp; }
	inline LPCTSTR OLE2CT(LPCOLESTR lp) { return lp; }
	inline LPOLESTR T2OLE(LPTSTR lp) { return lp; }
	inline LPTSTR OLE2T(LPOLESTR lp) { return lp; }
#else
	inline size_t ocslen(LPCOLESTR x) { return lstrlenW(x); }
	//lstrcpyW doesn't work on Win95, so we do this
	inline OLECHAR* ocscpy(LPOLESTR dest, LPCOLESTR src)
	{return (LPOLESTR) memcpy(dest, src, (lstrlenW(src)+1)*sizeof(WCHAR));}
	//CharNextW doesn't work on Win95 so we use this
	#define T2COLE(lpa) A2CW(lpa)
	#define T2OLE(lpa) A2W(lpa)
	#define OLE2CT(lpo) W2CA(lpo)
	#define OLE2T(lpo) W2A(lpo)
#endif

#ifdef OLE2ANSI
	inline LPOLESTR A2OLE(LPSTR lp) { return lp;}
	inline LPSTR OLE2A(LPOLESTR lp) { return lp;}
	#define W2OLE W2A
	#define OLE2W A2W
	inline LPCOLESTR A2COLE(LPCSTR lp) { return lp;}
	inline LPCSTR OLE2CA(LPCOLESTR lp) { return lp;}
	#define W2COLE W2CA
	#define OLE2CW A2CW
#else
	inline LPOLESTR W2OLE(LPWSTR lp) { return lp; }
	inline LPWSTR OLE2W(LPOLESTR lp) { return lp; }
	#define A2OLE A2W
	#define OLE2A W2A
	inline LPCOLESTR W2COLE(LPCWSTR lp) { return lp; }
	inline LPCWSTR OLE2CW(LPCOLESTR lp) { return lp; }
	#define A2COLE A2CW
	#define OLE2CA W2CA
#endif

#ifdef _UNICODE
	#define T2A W2A
	#define A2T A2W
	inline LPWSTR T2W(LPTSTR lp) { return lp; }
	inline LPTSTR W2T(LPWSTR lp) { return lp; }
	#define T2CA W2CA
	#define A2CT A2CW
	inline LPCWSTR T2CW(LPCTSTR lp) { return lp; }
	inline LPCTSTR W2CT(LPCWSTR lp) { return lp; }
#else
	#define T2W A2W
	#define W2T W2A
	inline LPSTR T2A(LPTSTR lp) { return lp; }
	inline LPTSTR A2T(LPSTR lp) { return lp; }
	#define T2CW A2CW
	#define W2CT W2CA
	inline LPCSTR T2CA(LPCTSTR lp) { return lp; }
	inline LPCTSTR A2CT(LPCSTR lp) { return lp; }
#endif

inline BSTR OLE2BSTR(LPCOLESTR lp) {return ::SysAllocString(lp);}
#if defined(_UNICODE)
// in these cases the default (TCHAR) is the same as OLECHAR
	inline BSTR T2BSTR(LPCTSTR lp) {return ::SysAllocString(lp);}
	inline BSTR A2BSTR(LPCSTR lp) {USES_CONVERSION; return ::SysAllocString(A2COLE(lp));}
	inline BSTR W2BSTR(LPCWSTR lp) {return ::SysAllocString(lp);}
#elif defined(OLE2ANSI)
// in these cases the default (TCHAR) is the same as OLECHAR
	inline BSTR T2BSTR(LPCTSTR lp) {return ::SysAllocString(lp);}
	inline BSTR A2BSTR(LPCSTR lp) {return ::SysAllocString(lp);}
	inline BSTR W2BSTR(LPCWSTR lp) {USES_CONVERSION; return ::SysAllocString(W2COLE(lp));}
#else
	inline BSTR T2BSTR(LPCTSTR lp) {USES_CONVERSION; return ::SysAllocString(T2COLE(lp));}
	inline BSTR A2BSTR(LPCSTR lp) {USES_CONVERSION; return ::SysAllocString(A2COLE(lp));}
	inline BSTR W2BSTR(LPCWSTR lp) {return ::SysAllocString(lp);}
#endif

