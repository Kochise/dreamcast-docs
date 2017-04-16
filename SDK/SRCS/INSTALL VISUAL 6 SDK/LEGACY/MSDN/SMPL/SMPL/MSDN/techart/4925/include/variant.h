// Variant.H - Variant class

#ifndef VARIANT_H_
#define VARIANT_H_

#include "BString.H"
#include <iostream.h>

#define VCONSTRUCTBITS
#ifdef VCONSTRUCTBITS
const DWORD VT_CONSTRUCTED = 0x800;
#endif

// Variant class - wraps VARIANT type

typedef const VARIANT* LPCVARIANT;

//@B Variant1
class Variant : VARIANT
{
public:
	
	// Constructors
    Variant();
	Variant(const Variant& vSrc);   
	Variant(BYTE bSrc);	// VT_UI1
//@E Variant1
	Variant(short iSrc, VARTYPE vtSrc = VT_I2); 
	Variant(long lSrc, VARTYPE vtSrc = VT_I4); 
	Variant(float fltSrc); // VT_R4
	Variant(double dblSrc, VARTYPE vtSrc = VT_R8); 
	// VT_BOOL (see short)
	// VT_ERROR (see long)
	Variant(const CURRENCY& cySrc); // VT_CY
	Variant(LONGLONG i64Src); // Alternate VT_CY
	// VT_DATE (see double)
	Variant(BSTR bsSrc, VARTYPE vtSrc = VT_BSTR);
	Variant(String& sSrc);
	Variant(LPCSTR szSrc);
	Variant(LPCWSTR wszSrc);
	Variant(IDispatch * pdisp); // VT_DISPATCH
	Variant(IUnknown * punk); // VT_UNKNOWN
	Variant(const SAFEARRAY * psa, VARTYPE vt = VT_NULL); // VT_ARRAY | VT_TYPE

    // Destructor
	~Variant();

	// Copy constructors
	const Variant& operator=(const VARIANT& varSrc);
	const Variant& operator=(LPCVARIANT pvSrc);
	const Variant& operator=(const Variant& vSrc);

    // Assignment
	const Variant& operator=(BYTE bSrc);	
	const Variant& operator=(short iSrc);
	const Variant& operator=(long lSrc);
	const Variant& operator=(float fltSrc);
	const Variant& operator=(double dblSrc);
    const Variant& SetBoolean(Boolean f);
    const Variant& SetError(long err);
    const Variant& SetDate(DATE dt);

    // Boolean (see short)
    // Error (see long)
    const Variant& operator=(const CURRENCY& curSrc);
    const Variant& operator=(LONGLONG  curSrc);
    // Date (see double)
	const Variant& operator=(const String& sSrc);
	const Variant& operator=(const BSTR bsSrc);
	const Variant& operator=(LPCSTR szSrc);
    const Variant& operator=(LPCWSTR wszSrc);
	const Variant& operator=(IDispatch * pdisp); 
	const Variant& operator=(IUnknown * punk); 
	const Variant& operator=(const SAFEARRAY * psa); 

    // Operations
    void Destroy();
	void ChangeType(VARTYPE vartype, Variant * pSrc = NULL);
	BOOL IsMissing();
	VARTYPE Type();             // Return type
	void Type(VARTYPE vt);      // Change type

    // Make a copy of current with given type
    Variant CopyAs(VARTYPE vartype);
    // Make a copy of current with given or existing type, 
    // whichever has greater precision 
    Variant CopyPromote(VARTYPE vartype);
	
	// Type casts
	//operator Boolean();
	operator BYTE();
	operator BYTE() const;
	operator short();
	operator short() const; 
	operator long();
	operator long() const;
	operator float();
	operator float() const;
	operator double();
	operator double() const;
    operator LONGLONG();
    operator LONGLONG() const;
	operator CURRENCY();
	operator CURRENCY() const;
	operator BSTR();
	operator BSTR() const;
	operator String();
	operator String() const;

    operator Variant();
    operator Variant() const;

    friend ostream& operator<<(ostream& os, Variant& v);

	// Arithmetic operators
	// +
	friend Variant operator+(Variant& v1, Variant& v2);    
	const Variant& operator+=(Variant v);
	Variant & operator++(); // Prefix
	Variant operator++(int); // Postfix

	// -
	friend Variant operator-(Variant& v1, Variant& v2);
	const Variant& operator-=(Variant v);
	Variant & operator--(); // Prefix
	Variant operator--(int); // Postfix

	// *
	friend Variant operator*(Variant& v1, Variant& v2);
	const Variant& operator*=(Variant v);

    // /
	friend Variant operator/(Variant& v1, Variant& v2);
	const Variant& operator/=(Variant v);

	// %
	friend Variant operator%(Variant& v1, Variant& v2);
	const Variant& operator%=(Variant v);

	// Logical operators
	friend BOOL operator==(const Variant& v1, const Variant& v2);
	friend BOOL operator<(const Variant& v1, const Variant& v2);
	friend BOOL operator!=(const Variant& v1, const Variant& v2);
	friend BOOL operator<=(const Variant& v1, const Variant& v2);
	friend BOOL operator>=(const Variant& v1, const Variant& v2);
	friend BOOL operator>(const Variant& v1, const Variant& v2);
    static BOOL Preciser(VARTYPE vt1, VARTYPE vt2);

//@B Variant2
private: 
    // Constructor helper
    void VariantCreate(VARTYPE vt = VT_EMPTY);

    // Destructor helper
    void VariantDestroy();
    Boolean IsConstructed();
    void Constructed(Boolean f);
    
    // Look, Ma! No data.
};
//@E Variant2


// Implementation of inline members

inline void Variant::VariantCreate(VARTYPE vtA)
{
    vt = vtA;
    wReserved1 = 0;
    Constructed(True);
}

inline void Variant::VariantDestroy()
{
    Constructed(False);
	HRESULT hres = VariantClear(this);
    if (hres) throw hres;
}

inline Boolean Variant::IsConstructed()
{
#ifdef VCONSTRUCTBITS
    return (wReserved1 & VT_CONSTRUCTED) ? True : False;
#else
    return False;
#endif
}

inline void Variant::Constructed(Boolean f)
{
#ifdef VCONSTRUCTBITS
    if (f) {
        wReserved1 |= VT_CONSTRUCTED;
    } else {
        wReserved1 &= ~VT_CONSTRUCTED;
    }
#endif
}

//@B VariantCon
inline Variant::Variant()
{
    VariantCreate();
}

inline Variant::Variant(const Variant& v)
{
	VariantCreate();
	HRESULT hres = VariantCopy(this, (Variant *)&v);
    if (hres) throw hres;
}

inline Variant::Variant(BYTE nSrc)
{ 
    VariantCreate(VT_UI1); 
	bVal = nSrc; 
}
//@E VariantCon

inline Variant::Variant(float fltSrc)
{ 
    VariantCreate(VT_R4); 
	fltVal = fltSrc; 
}

inline Variant::Variant(const CURRENCY& curSrc)
{ 
    VariantCreate(VT_CY); 
    cyVal.int64 = curSrc.int64;
}

inline Variant::Variant(LONGLONG i64Src) // Alternate VT_CY
{ 
    VariantCreate(VT_CY); 
    cyVal.int64 = i64Src; 
}

inline Variant::Variant(String& sSrc)
{
    VariantCreate(VT_BSTR); 
	bstrVal = sSrc;
}

inline Variant::Variant(LPCSTR szSrc)
{
    VariantCreate(VT_BSTR); 
	bstrVal = SysAllocStringA(szSrc);
}

inline Variant::Variant(LPCWSTR wszSrc)
{
    VariantCreate(VT_BSTR); 
	bstrVal = SysAllocString(wszSrc);
}

inline Variant::Variant(IDispatch * pdispSrc)
{ 
    VariantCreate(VT_DISPATCH);
    pdispVal = pdispSrc;
}

inline Variant::Variant(IUnknown * punkSrc)
{
    VariantCreate(VT_UNKNOWN);
    punkVal = punkSrc;
}

//@B VariantDes
inline Variant::~Variant()
{
    if (IsConstructed()) {
        VariantDestroy();
    }
}
//@E VariantDes

// Copy constructors
inline const Variant& Variant::operator=(const VARIANT& varSrc)
{
	HRESULT hres = VariantCopy(this, (LPVARIANT)&varSrc);
    if (hres) throw hres;
	return *this;
}

inline const Variant& Variant::operator=(LPCVARIANT pSrc)
{
	HRESULT hres = VariantCopy(this, (LPVARIANT)pSrc);
    if (hres) throw hres;
	return *this;
}

inline const Variant& Variant::operator=(const Variant& vSrc)
{
	HRESULT hres = VariantCopy(this, (LPVARIANT)&vSrc);
    if (hres) throw hres;
	return *this;
}

inline BOOL Variant::IsMissing()
{
	return (vt == VT_ERROR) && (scode == DISP_E_PARAMNOTFOUND);
}

inline VARTYPE	Variant::Type()
{ 
    return vt; 
}

inline void Variant::Type(VARTYPE vartype)
{
    Boolean f = IsConstructed();
	HRESULT hres = VariantChangeType(this, this, 0, vartype);
    if (f) {
        Constructed(True);
    }
    if (hres) throw hres;
}

inline Variant::operator BYTE() 
{
    return CopyAs(VT_UI1).bVal;
}

inline Variant::operator short() 
{
    return CopyAs(VT_I2).iVal;
}

inline Variant::operator long()
{
    return CopyAs(VT_I4).lVal;
}

inline Variant::operator float()
{
    return CopyAs(VT_R4).fltVal;
}

inline Variant::operator double()
{
    return CopyAs(VT_R8).dblVal;
}

inline Variant::operator LONGLONG()
{
    return CopyAs(VT_CY).cyVal.int64;
}

inline Variant::operator CURRENCY()
{
    return CopyAs(VT_CY).cyVal;
}

inline Variant::operator Variant()
{
    // vt &= ~VT_CONSTRUCTED;
    return *this;
}

inline BOOL operator!=(const Variant& v1, const Variant& v2)
{ 
    return !(v1 == v2); 
}

inline BOOL operator<=(const Variant& v1, const Variant& v2)
{ 
    return !(v2 < v1); 
}

inline BOOL operator>=(const Variant& v1, const Variant& v2)
{ 
    return !(v1 < v2); 
}

inline BOOL operator>(const Variant& v1, const Variant& v2)
{ 
    return v2 < v1; 
}

#endif // VARIANT_H_


