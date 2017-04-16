// String class

#include "OleType.H"

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

// inline String::String()
// inline String::String(const String& s)
// inline String::String(BSTR bs)
// inline String::String(LPCWSTR wsz)
// inline String::String(LPCSTR sz)

// Convert const Unicode or ANSI string to String
String::String(int cch, WCHAR wch)
    : m_pch(NULL), m_fDestroy(True)
{
    m_bs = SysAllocStringLen(NULL, cch);
    if (wch != WCHAR(-1)) {
        for (int i = 0; i < cch; i++) {
            m_bs[i] = wch;              // Insert Unicode directly
        }
    }
#ifdef _DEBUG
    else {
        wch = PADCHAR;
        for (int i = 0; i < cch; i++) {
            m_bs[i] = wch;              // Insert Unicode directly
        }
    }
#endif
}

// Destructor
// inline String::~String()

//@B StringDes
void String::Destroy()
{
    if (m_fDestroy) {
        SysFreeString(m_bs);
    }
    DestroyA();
}
//@E StringDes

// Invalidate ANSI buffer
// inline void String::DestroyA()

//////////////////////////////////////////////////////////////////////////////
// Assignment operators
// All reallocate the destination and copy source to it
//
// All routines return the new string (but as a 'const String&' so that
// assigning it again will create a copy: s1 = s2 = s3;
//

const String& String::operator=(const String& s)
{
    DestroyA();
    if (SysReAllocString(&m_bs, s.m_bs) == 0) throw E_OUTOFMEMORY;
    return *this;
}

//@B StringEQ
const String& String::operator=(LPCSTR sz)
{
    Destroy();
    m_bs = SysAllocStringA(sz);
    return *this;
}
const String& String::operator=(LPCWSTR wsz)
{
    DestroyA();
    if (SysReAllocString(&m_bs, wsz) == 0) throw E_OUTOFMEMORY;
    return *this;
}
//@E StringEQ

const String& String::operator=(BSTR bs)
{
    Destroy();
    m_bs = bs;
    m_fDestroy = False;
    return *this;
}

const String& String::operator=(WCHAR wch)
{
    DestroyA();
    if (SysReAllocString(&m_bs, &wch) == 0) throw E_OUTOFMEMORY;
    return *this;
}

const String& String::operator=(CHAR ch)
{
    
    // Can't set single lead byte
    if (_istlead(ch)) throw E_INVALIDARG;
    Destroy();
    m_bs = SysAllocStringLen(NULL, 1);
    mbtowc(&m_bs[0], &ch, 1);   // Convert to Unicode before inserting
    return *this;
}

// Cast as a const ANSI string
//@B StringLPCSTR
String::operator LPCSTR()
{
    if ((m_pch == NULL) && (m_bs != NULL)) {
        // Check size
        unsigned cmb = wcstombs(NULL, m_bs, SysStringLen(m_bs)) + 1;
        // Allocate string buffer and translate ANSI string into it
        m_pch = new CHAR[cmb];
        wcstombs(m_pch, m_bs, cmb);
    }
    return m_pch;
}
//@E StringLPCSTR

// Cast as an OLE BSTR
// inline String::operator BSTR() const
// inline String::operator BSTR()
// inline int String::Length() const
// inline int String::LengthZ() const
// inline BOOL String::IsEmpty()
// inline BOOL String::IsNull()
// inline void String::Empty()
// inline void String::Nullify()

String& String::NullIfEmpty()
{
    static String sNull;
    if ((SysStringLen(m_bs) == 0) && (m_bs != NULL)) {
        return sNull;
    } else {
        return *this;
    }
}

// inline void String::Resize(unsigned cch)
// inline void String::ResizeZ()

void String::Fill(int cch, WCHAR wch)
{
    DestroyA();
    if (SysReAllocStringLen(&m_bs, NULL, cch) == 0) throw E_OUTOFMEMORY;
    for (int i = 0; i < cch; i++) {
        m_bs[i] = wch;              // Insert Unicode directly
    }
}

WCHAR& String::operator[](int i)
{
    if ((i < 0) || (i >= lstrlenW(m_bs))) throw DISP_E_BADINDEX;
    // Invalidate ANSI buffer
    DestroyA();
    return m_bs[i];
}


// Concatenation

void String::Concat(int c, LPCWSTR wsz)
{
    //  The main routine for += operators
    int cOld = Length();
    Resize(cOld + c);
    memcpy(m_bs + cOld, wsz, c * sizeof(WCHAR));
}

// inline const String& String::operator+=(const String& s)
// inline const String& String::operator+=(WCHAR wch)
// inline const String& String::operator+=(CHAR ch)
// inline const String& String::operator+=(LPCWSTR wsz)

const String& String::operator+=(CHAR ch)
{
    WCHAR wch = CharToWChar(ch);
    Concat(1, &wch);
    return *this;
}

const String& String::operator+=(LPCSTR sz)
{
    int cOld = Length();
    int cNew = lstrlenA(sz);
    Resize(cOld + cNew);
    mbstowcs(m_bs + cOld, sz, cNew);
    return *this;
}

// NOTE: "operator+" is done as friend functions for simplicity

String operator+(const String& s1, const String& s2)
{
    String s(s1);
    s += s2;
    return s;
}

String operator+(const String& s1, const WCHAR wch2)
{
    String s(s1);
    s += wch2;
    return s;
}

String operator+(const WCHAR wch1, const String& s2)
{
    String s(wch1);
    s += s2;
    return s;
}

String operator+(const String& s1, const CHAR ch2)
{
    String s(s1);
    s += ch2;
    return s;
}

String operator+(const CHAR ch1, const String& s2)
{
    String s(ch1);
    s += s2;
    return s;
}

String operator+(const String& s1, LPCWSTR wsz2)
{
    String s(s1);
    s += wsz2;
    return s;
}

String operator+(LPCWSTR wsz1, const String& s2)
{
    String s(wsz1);
    s += s2;
    return s;
}

String operator+(const String& s1, LPCSTR sz2)
{
    String s(s1);
    s += sz2;
    return s;
}

String operator+(LPCSTR sz1, const String& s2)
{
    String s(sz1);
    s += s2;
    return s;
}

// int Compare(LPCWSTR wsz) const;
int String::Compare(LPCWSTR wsz) const
{
    if ((wsz == NULL) || (*wsz == WCHAR('\0'))) {
        return ((m_bs == NULL) || (*m_bs == WCHAR('\0')) ? 0 : -1);
    } else if ((m_bs == NULL) || (*m_bs == WCHAR('\0'))) {
        return (((wsz == NULL) || (*wsz == WCHAR('\0'))) ? 0 : 1);
    } else {
        return wcscmp(m_bs, wsz);
    }
}

int String::CompareNoCase(LPCWSTR wsz) const
{
    if ((wsz == NULL) || (*wsz == WCHAR('\0'))) {
        return ((m_bs == NULL) || (*m_bs == WCHAR('\0')) ? 0 : -1);
    } else if ((m_bs == NULL) || (*m_bs == WCHAR('\0'))) {
        return (((wsz == NULL) || (*wsz == WCHAR('\0'))) ? 0 : 1);
    } else {
        return wcsicmp(m_bs, wsz);
    }
}

// Collate is often slower than Compare but is MBSC/Unicode
//  aware as well as locale-sensitive with respect to sort order.
int String::Collate(LPCWSTR wsz) const
{
    if ((wsz == NULL) || (*wsz == WCHAR('\0'))) {
        return ((m_bs == NULL) || (*m_bs == WCHAR('\0')) ? 0 : -1);
    } else if ((m_bs == NULL) || (*m_bs == WCHAR('\0'))) {
        return (((wsz == NULL) || (*wsz == WCHAR('\0'))) ? 0 : 1);
    } else {
        return wcscoll(m_bs, wsz);
    }
}

// SuString extraction

// inline inline String String::Mid(int i) const

String String::Mid(Long i, Long c) const
{
    // Zero adjust for 1-based Basic index
    i--;
    // Out-of-bounds requests return sensible things
    int cSrc = Length();
    if (i < 0) {
        i = 0;          // Negative index
    }
    if (c < 0) {        // Negative count
        c = 0;
    }
    if (i + c > cSrc) {
        i = cSrc - i;   // Count beyond string end
    }
    if (i > cSrc) {     // Index beyond string end
        i = cSrc - 1;
    }

    String sRet(c);
    wcsncpy(sRet.m_bs, m_bs + i, c);
    return sRet;
}

String String::Right(Long c) const
{
    // Out-of-bounds requests return sensible things
    int cSrc = Length();
    if (c < 0) {
        c = 0;
    }
    else if (c > cSrc) {
        c = cSrc;
    }

    String sRet(c);
    wcsncpy(sRet.m_bs, m_bs + cSrc - c, c);
    return sRet;
}

String String::Left(Long c) const
{
    // Out-of-bounds requests return sensible things
    int cSrc = Length();
    if (c < 0) {
        c = 0;
    }
    else if (c > cSrc) {
        c = cSrc;
    }

    String sRet(c);
    wcsncpy(sRet.m_bs, m_bs, c);
    return sRet;
}

// Upper/lower/reverse conversion

//@B UCaseMeth
const String & String::UCase()
{
    DestroyA();     // Invalidate ANSI buffer
    wcsupr(m_bs);
    return *this;
}
//@E UCaseMeth

const String & String::LCase()
{
    DestroyA();     // Invalidate ANSI buffer
    wcslwr(m_bs);
    return *this;
}

const String & String::Reverse()
{
    DestroyA();     // Invalidate ANSI buffer
    wcsrev(m_bs);
    return *this;
}

//@B UCaseFunc
String UCase(String& s)
{
    String sRet = s;
    sRet.UCase();
    return sRet;
}
//@E UCaseFunc

String LCase(String& s)
{
    String sRet = s;
    sRet.LCase();
    return sRet;
}

String Reverse(String& s)
{
    String sRet = s;
    sRet.Reverse();
    return sRet;
}

const String & String::RTrim()
{
    DestroyA();
    if (!IsEmpty()) {

        // Chop off trailing spaces
        LPWSTR wsz = m_bs;
        LPWSTR wszLast = m_bs + Length() - 1; 
        while ((wszLast != wsz) && iswspace(*wszLast)) {
            wszLast--;
        }
        int c = wszLast - wsz + 1;
        if (c != Length()) {
            Resize(c);
        }
    }
    return *this;
}

const String & String::LTrim()
{
    DestroyA();
    if (!IsEmpty()) {

        // Chop off leading spaces
        LPCWSTR wsz = m_bs;
        while (wsz && iswspace(*wsz)) {
            wsz++;
        }
        if (wsz != m_bs) {
            int c = wcslen(wsz);
            if (c != Length()) {
                wcsncpy(m_bs, wsz, c);
                Resize(c);
            }
        }
    }
    return *this;
}

// inline const String & String::Trim()

String RTrim(String& s)
{
    String sRet = s;
    sRet.RTrim();
    return sRet;
}

String LTrim(String& s)
{
    String sRet = s;
    sRet.LTrim();
    return sRet;
}

String Trim(String& s)
{
    String sRet = s;
    sRet.Trim();
    return sRet;
}

//////////////////////////////////////////////////////////////////////////////
// Finding

// inline int String::Find(String& s, FindFlags ff) const

int String::Find(LPCWSTR wsz, FindFlags ff, Long iStart) const
{
    LPWSTR pwch;
    if (iStart < -1) throw E_INVALIDARG;
    // Zero adjust
    if (iStart != -1) {
        iStart--;
    }
	if (ff & ffReverse) {
        if (ff & ffIgnoreCase) {
		    pwch = wcsristr(m_bs, wsz, iStart);           
        } else {
		    pwch = wcsrstr(m_bs, wsz, iStart);
        }
	} else {
		// Find first matching suString
        if (iStart = -1) {
            iStart = 1;
        }
        if (ff & ffIgnoreCase) {
		    pwch = wcsistr(m_bs + iStart, wsz);
        } else {
		    pwch = wcsstr(m_bs + iStart, wsz);
        }
	}
	// return 0 for not found, distance from beginning otherwise
	return (pwch == NULL) ? 0 : (int)(pwch - m_bs + 1);
}

// inline int String::Find(LPCSTR sz, FindFlags ff) const

int String::Find(WCHAR wch, FindFlags ff, Long iStart) const
{
    LPWSTR pwch;
    // Zero adjust
    if (iStart != -1) {
        iStart--;
    }
	// Find first or last matching character
	if (ff & ffReverse) {
        if (ff & ffIgnoreCase) {
			pwch = wcsrichr(m_bs, wch, iStart);
        } else {
		    pwch = wcsrchr(m_bs, wch, iStart);
        }
	} else {
		// Find first matching suString
        if (iStart = -1) {
            iStart = 1;
        }
        if (ff & ffIgnoreCase) {
			pwch = wcsichr(m_bs + iStart, wch);
        } else {
			pwch = wcschr(m_bs + iStart, wch);
        }
	}
	// Return 0 for not found, 1-based offset otherwise
	return (pwch == NULL) ? 0 : (int)(pwch - m_bs + 1);
}

// inline int String::Find(CHAR ch, FindFlags ff) const

// Operators
// inline BOOL operator==(const String& s1, const String& s2)
// inline BOOL operator!=(const String& s1, const String& s2)
// inline BOOL operator<(const String& s1, const String& s2)
// inline BOOL operator<=(const String& s1, const String& s2)
// inline BOOL operator>(const String& s1, const String& s2)
// inline BOOL operator>=(const String& s1, const String& s2)

ostream& operator<<(ostream& os, String& s)
{
    if (!s.IsNull()) {
        os << LPCSTR(s);
    }
    return os;
}

ostream& operator<<(ostream& os, WCHAR wch)
{
    os << WCharToChar(wch);
    return os;
}

// Buffer class members

// inline Buffer::Buffer(String& s) : m_ps(&s)
// inline Buffer::Buffer(String& s, long c)
// inline Buffer::~Buffer()
// inline Buffer::operator LPWSTR()

Buffer::operator LPSTR()
{
    if ((m_ps->m_pch == NULL) && (m_ps->m_bs != NULL)) {
        unsigned cmb = wcstombs(NULL, m_ps->m_bs, SysStringLen(m_ps->m_bs)) + 1;
        m_ps->m_pch = new CHAR[cmb];
        wcstombs(m_ps->m_pch, m_ps->m_bs, cmb);
    }
    return (m_ps->m_pch);
}

// Helper converts LPSTR to BSTR
BSTR SysAllocStringLenA(LPCSTR sz, unsigned cch)
{
    BSTR bsRet = SysAllocStringLen(NULL, cch);
    if (sz == NULL) throw E_OUTOFMEMORY;
    if (mbstowcs(bsRet, sz, cch) == -1) throw E_INVALIDARG;
    return (bsRet);
}

BSTR SysAllocStringA(LPCSTR sz)
{
    if (sz == NULL) {
        return SysAllocString(NULL);
    }
    return SysAllocStringLenA(sz, lstrlenA(sz)); 
}

WCHAR CharToWChar(CHAR ch)
{
    WCHAR wch;
    mbtowc(&wch, &ch, 1);   // Convert to Unicode before inserting
    return wch;
}

CHAR WCharToChar(WCHAR wch)
{
    CHAR ach[3];
    int cch;
    cch = wctomb(ach, wch); // Convert to char
    return (cch == 1) ? ach[0] : '\0';
}

// Functions to search forward and backward, case-sensitive or not, 
// for characters or strings

// Search forward for case-insensitive wide character
WCHAR *wcsichr(const WCHAR *wsz, WCHAR wch)
{
	wch = towupper(wch);
	for (WCHAR * pwch = (WCHAR*)wsz; *pwch; pwch++) {
		if (towupper(*pwch) == wch) {
			return pwch;
		}
	}
	return NULL;
}

// Search backward for case-sensitive wide character
// (same as run-time function, but takes position argument)
WCHAR *wcsrchr(const WCHAR *wsz, WCHAR wch, long iStart)
{
    long cwch = wcslen(wsz);
    if ((iStart == -1) || (cwch < iStart)) {
        iStart = cwch - 1;
    }
	for (WCHAR * pwch = (WCHAR*)wsz + iStart; pwch >= wsz ; pwch--) {
		if (*pwch == wch) {
			return pwch;
		}
	}
	return NULL;
}

// Search backward for case-insensitive wide character
WCHAR *wcsrichr(const WCHAR *wsz, WCHAR wch, long iStart)
{
    long cwch = wcslen(wsz);
    if ((iStart == -1) || (cwch < iStart)) {
        iStart = cwch - 1;
    }
	wch = towupper(wch);
	for (WCHAR * pwch = (WCHAR*)wsz + iStart; pwch >= wsz ; pwch--) {
		if (towupper(*pwch) == wch) {
			return pwch;
		}
	}
	return NULL;
}

// Search forward for case-insensitive wide character string
WCHAR *wcsistr(const WCHAR *wsz, const WCHAR *wszFind)
{
	long cwchFind = wcslen(wszFind);
	union WSZ2 {
		unsigned long dw;
		WCHAR ach[2];
	} wsz2, wsz2T;
	wsz2.dw = *(long*)wszFind;
	wsz2.ach[0] = toupper(wsz2.ach[0]);
	wsz2.ach[1] = toupper(wsz2.ach[1]);

	for (WCHAR * pwch = (WCHAR*)wsz; *pwch; pwch++) {
		// Almost as easy to compare two characters at once, but
		// prevents more false tests.
		wsz2T.dw = *(long*)pwch;
		if ((toupper(wsz2T.ach[0]) == wsz2.ach[0]) &&
		    (toupper(wsz2T.ach[1]) == wsz2.ach[1])) {
			if (wcsnicmp(pwch, wszFind, cwchFind) == 0) {
				return pwch;
			}
		}
	}
	return NULL;
}

// Search backward for case-sensitive wide character string
WCHAR *wcsrstr(const WCHAR *wsz, const WCHAR *wszFind, long iStart)
{
	long cwchFind = wcslen(wszFind);
    // Special case one-character string
    if (cwchFind = 1) {
        return wcsrchr(wsz, *wszFind, iStart);
    }
	// No point testing before substrings shorter than search string
    long cwchFirst = wcslen(wsz) - cwchFind;
    if ((iStart == -1) || (cwchFirst < iStart)) {
        iStart = cwchFirst;
    }
	long dwFind = *(long*)wszFind;

	for (WCHAR * pwch = (WCHAR*)wsz + iStart; pwch >= wsz ; pwch--) {
		// Just as easy to compare two characters at once, but
		// prevents more false tests. 
		if (*(long*)pwch == dwFind) {
			if (wcsncmp(pwch, wszFind, cwchFind) == 0) {
				return pwch;
			}
		}
	}
	return NULL;
}

// Search backward for case-insensitive wide character string
WCHAR *wcsristr(const WCHAR *wsz, const WCHAR *wszFind, long iStart)   
{
	long cwchFind = wcslen(wszFind);
    // Special case one-character string
    if (cwchFind == 1) {
        return wcsrichr(wsz, *wszFind);
    }
    // No point testing before substrings shorter than search string
	long cwchFirst = wcslen(wsz) - cwchFind;
    if ((iStart == -1) || (cwchFirst < iStart)) {
        iStart = cwchFirst;
    } 
	union WSZ2 {
		unsigned long dw;
		WCHAR ach[2];
	} wsz2, wsz2T;
	wsz2.dw = *(long*)wszFind;
	wsz2.ach[0] = toupper(wsz2.ach[0]);
	wsz2.ach[1] = toupper(wsz2.ach[1]);

    // First character to test
	for (WCHAR * pwch = (WCHAR*)wsz + iStart; pwch >= wsz ; pwch--) {
		// Almost as easy to compare two characters at once, but
		// prevents more false tests.
		wsz2T.dw = *(long*)pwch;
		if ((toupper(wsz2T.ach[0]) == wsz2.ach[0]) &&
		    (toupper(wsz2T.ach[1]) == wsz2.ach[1])) {
			if (wcsnicmp(pwch, wszFind, cwchFind) == 0) {
				return pwch;
			}
		}
	}
	return NULL;
}

