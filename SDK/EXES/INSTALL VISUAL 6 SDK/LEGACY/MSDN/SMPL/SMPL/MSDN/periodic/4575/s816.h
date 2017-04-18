//////////////////////////////////////////////////////
// 
// S816.h - Copyright 1995, Don Box 
//
// Shim classes that transform Unicode to ANSI and back
//
// Code that uses the earlier String816 class should be 
// migrated to String8 or String16, as String816 will 
// probably not be supported any longer.
//

#ifndef _S816_H
#define _S816_H

// String16 ////////////////////////////////////////////////////////

// Shim class that converts both 8-bit (foreign) and
// 16-bit (native) strings to 16-bit wideness

class String16 {
public:
// native and foreign constructors
	String16(const char *p8);
	String16(const wchar_t *p16);

// non-virtual destructor (this class is concrete)
  ~String16(void);

// native conversion operator
  operator const wchar_t * (void) const;

private:
// native wideness string
	wchar_t *m_sz;
// is foreign??
	BOOL m_bIsForeign;

// protect against assignment!
  String16(const String16&);
	String16& operator=(const String16&);
};

// native constructor is a pass-through
inline String16::String16(const wchar_t *p16) 
: m_sz((wchar_t *)p16), m_bIsForeign(FALSE) 
{ 
}

// simply give out the native wideness string 
inline String16::operator const wchar_t * (void) const 
{
  return m_sz;
}

// foreign constructor requires allocation of a native
// string and conversion
inline String16::String16(const char *p8)
: m_bIsForeign(TRUE) 
{
// calculate string length
  size_t len = strlen(p8);

// calculate required buffer size (some characters may
// already occupy 16-bits under DBCS)
  size_t size = mbstowcs(0, p8, len) + 1;

// alloc native string and convert
  if (m_sz = new wchar_t[size])
    mbstowcs(m_sz, p8, size);
}

// delete native string only if synthesized in foreign constructor
inline String16::~String16(void) {
  if (m_bIsForeign) 
    delete[] m_sz;
}


// String8 /////////////////////////////////////////////////////////

// Shim class that converts both 8-bit (native) and
// 16-bit (foreign) strings to 8-bit wideness

class String8 {
public:
// native and foreign constructors
	String8(const char *p8);
	String8(const wchar_t *p16);

// non-virtual destructor (this class is concrete)
  ~String8(void);

// native conversion operator
  operator const char * (void) const;

private:
// native wideness string
	char *m_sz;
// is foreign??
	BOOL m_bIsForeign;

// protect against assignment!
  String8(const String8&);
	String8& operator=(const String8&);
};

// native constructor is a pass-through
inline String8::String8(const char *p8) 
: m_sz((char *)p8), // casting away constness ONLY FOR CONVENIENCE!
  m_bIsForeign(FALSE) 
{ 
}

// simply give out the native wideness string 
inline String8::operator const char * (void) const 
{
  return m_sz;
}

// foreign constructor requires allocation of a native
// string and conversion
inline String8::String8(const wchar_t *p16)
: m_bIsForeign(TRUE) 
{
// calculate string length
  size_t len = wcslen(p16);

// calculate required buffer size (some characters may
// require more than one byte under DBCS)
  size_t size = wcstombs(0, p16, len) + 1;

// alloc native string and convert
  if (m_sz = new char[size])
    wcstombs(m_sz, p16, size);
}

// delete native string only if synthesized in foreign constructor
inline String8::~String8(void) {
  if (m_bIsForeign) 
    delete[] m_sz;
}

// Conditional Typedefs for Win32 and OLE Text Data Types ////////////////////

// typedef OLESTRCVAR to emulate the OLESTR 
// macro (converts any string at runtime instead 
// of simply changing layout of string literal at
// compile-time).

#ifdef OLE2ANSI
typedef String8 OLESTRCVAR;
#else
typedef String16 OLESTRCVAR;
#endif


// typedef __TEXTCVAR to emulate the __TEXT
// macro (converts any string at runtime instead 
// of simply changing layout of string literal at
// compile-time).


#ifdef UNICODE
typedef String16 __TEXTCVAR;
#else
typedef String8 __TEXTCVAR;
#endif

#endif
