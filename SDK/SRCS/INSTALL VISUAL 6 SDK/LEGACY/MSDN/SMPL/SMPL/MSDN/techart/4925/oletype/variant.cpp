// Variant class

#include "OleType.H"

// Constructors
// inline Variant::Variant()
// inline Variant::Variant(const VARIANT& var)
// inline Variant::Variant(LPCVARIANT pvar)
// inline Variant::Variant(const Variant& v)
// inline Variant::Variant(BYTE nSrc)

Variant::Variant(short iSrc, VARTYPE vtSrc)
{
	if (vtSrc != VT_I2 && vtSrc != VT_BOOL) throw ERROR_INVALID_PARAMETER;

	if (vtSrc == VT_BOOL) {
		VariantCreate(VT_BOOL);
		boolVal = iSrc ? True : False;
	} else {
		VariantCreate(VT_I2);
		iVal = iSrc;
	}
}

Variant::Variant(long lSrc, VARTYPE vtSrc)
{
	if (vtSrc != VT_I4 && vtSrc != VT_ERROR && vtSrc == VT_BOOL) {
        throw ERROR_INVALID_PARAMETER;
    }

	switch (vtSrc) {
	case VT_ERROR:
		VariantCreate(VT_ERROR);
		scode = lSrc;
		break;
	case VT_BOOL:
		VariantCreate(VT_BOOL);
		boolVal = lSrc ? True : False;
		break;
	default:
		VariantCreate(VT_I4);
		lVal = lSrc;
	}
}

// inline Variant::Variant(float fltSrc)

Variant::Variant(double dblSrc, VARTYPE vtSrc)
{ 
	if (vtSrc != VT_R8 && vtSrc != VT_DATE) throw ERROR_INVALID_PARAMETER;

	if (vtSrc == VT_DATE) {
		VariantCreate(VT_DATE);
		date = dblSrc;
	} else {
		VariantCreate(VT_R8);
		dblVal = dblSrc;
	}
}

// inline Variant::Variant(const CURRENCY& curSrc)
// inline Variant::Variant(LONGLONG i64Src) // Alternate VT_CY
// inline Variant::Variant(String& sSrc)

Variant::Variant(BSTR bsSrc, VARTYPE vtSrc)
{
	if (vtSrc != VT_BSTR && vtSrc != VT_LPWSTR) throw ERROR_INVALID_PARAMETER;
	if (vt == VT_BSTR) {
		bstrVal = bsSrc;
	} else {
        VariantCreate(VT_BSTR); 
		bstrVal = SysAllocString(bsSrc);
	}
}

// inline Variant::Variant(LPCSTR szSrc)
// inline Variant::Variant(LPCWSTR wszSrc)
// inline Variant::Variant(IDispatch * pdispSrc)
// inline Variant::Variant(IUnknown * punkSrc)
Variant::Variant(const SAFEARRAY * psaSrc, VARTYPE vt)
{
    if (vt == VT_NULL) {
        // Try to guess the array type 
        WORD af = psaSrc->fFeatures; 
        DWORD cb = psaSrc->cbElements;
        if (af & FADF_BSTR) {
            vt = VT_BSTR;
        } else if (af & FADF_VARIANT) {
            vt = VT_VARIANT;
        } else if (af & FADF_UNKNOWN) {
            vt = VT_UNKNOWN;
        } else if (af & FADF_DISPATCH) {
            vt = VT_DISPATCH;    
        } else if (cb == 1) {
            vt = VT_UI1;        
        } else if (cb == 2) {
            // Could be short or Boolean--we guess short, 
            // but user should tell us
            vt = VT_I2;        
        } else if (cb == 4) {
            // Could be long, float, or error--we guess long, 
            // but user should tell us
            vt = VT_I4;        
        } else if (cb == 8) {
            // Could be double, date, or currency--we guess double, 
            // but user should tell us
            vt = VT_R8;        
        } else {
            throw ERROR_INVALID_DATA;
        }
    } 
    VariantCreate(VT_ARRAY | vt);
    // Bad definition of SafeArrayCopy forces us to cast away constness
    HRESULT hres = SafeArrayCopy((SAFEARRAY*)psaSrc, &parray);
    if (hres) throw hres;
}


// Variant destructor
// inline Variant::~Variant()
// inline void Variant::Destroy()

// Copy constructors

// inline const Variant& Variant::operator=(const VARIANT& varSrc)
// inline const Variant& Variant::operator=(LPCVARIANT pSrc)
// inline const Variant& Variant::operator=(const Variant& vSrc)

const Variant& Variant::operator=(BYTE bSrc)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_UI1) {
        VariantDestroy();
		VariantCreate(VT_UI1);
	}
	bVal = bSrc;
	return *this;
}

const Variant& Variant::operator=(short iSrc)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_I4) {
        VariantDestroy();
		VariantCreate(VT_I4);
	}
	iVal = iSrc;
	return *this;
}

const Variant& Variant::operator=(long lSrc)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_I4) {
        VariantDestroy();
		VariantCreate(VT_I4);
	}
	lVal = lSrc;
	return *this;
}

const Variant& Variant::operator=(float flt)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_R4) {
        VariantDestroy();
		VariantCreate(VT_R4);
	}
	fltVal = flt;
	return *this;
}

const Variant& Variant::operator=(double dbl)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_R8) {
        VariantDestroy();
		VariantCreate(VT_R8);
	}
	dblVal = dbl;
	return *this;
}

const Variant& Variant::operator=(const CURRENCY& curSrc)
{
	// Free up previous VARIANT if necessary
    if (vt != VT_CY) {
        VariantDestroy();
		VariantCreate(VT_CY);
	}
    cyVal.int64 = curSrc.int64;
	return *this;
}

const Variant& Variant::operator=(LONGLONG curSrc)
{
	// Free up previous VARIANT if necessary
    if (vt != VT_CY) {
        VariantDestroy();
		VariantCreate(VT_CY);
	}
    cyVal.int64 = curSrc;
	return *this;
}

const Variant& Variant::operator=(const BSTR bsSrc)
{
    VariantDestroy();
	VariantCreate(VT_BSTR);
	bstrVal = SysAllocString(bsSrc);
	return *this;
}

const Variant& Variant::operator=(const String& sSrc)
{
    VariantDestroy();
	VariantCreate(VT_BSTR);
	bstrVal = sSrc;
	return *this;
}

const Variant& Variant::operator=(LPCSTR szSrc)
{
    VariantDestroy();
    VariantCreate(VT_BSTR); 
	bstrVal = SysAllocStringA(szSrc);
	return *this;
}

const Variant& Variant::operator=(LPCWSTR wszSrc)
{
    VariantDestroy();
    VariantCreate(VT_BSTR); 
    bstrVal = SysAllocString(wszSrc);
	return *this;
}


const Variant& Variant::operator=(IDispatch * pdispSrc)
{ 
    VariantDestroy();
    VariantCreate(VT_DISPATCH);
    pdispVal = pdispSrc;
	return *this;
}

const Variant& Variant::operator=(IUnknown * punkSrc)
{
    VariantDestroy();
    VariantCreate(VT_UNKNOWN);
    punkVal = punkSrc;
	return *this;
}

const Variant& Variant::operator=(const SAFEARRAY * psaSrc)
{
    VariantDestroy();
    // Try to guess the array type 
    WORD af = psaSrc->fFeatures; 
    DWORD cb = psaSrc->cbElements;
    if (af & FADF_BSTR) {
        vt = VT_BSTR;
    } else if (af & FADF_VARIANT) {
        vt = VT_VARIANT;
    } else if (af & FADF_UNKNOWN) {
        vt = VT_UNKNOWN;
    } else if (af & FADF_DISPATCH) {
        vt = VT_DISPATCH;    
    } else if (cb == 1) {
        vt = VT_UI1;        
    } else if (cb == 2) {
        // Could be short or Boolean--we guess short
        vt = VT_I2;        
    } else if (cb == 4) {
        // Could be long, float, or error--we guess long
        vt = VT_I4;        
    } else if (cb == 8) {
        // Could be double, date, or currency--we guess double
        vt = VT_R8;        
    } else {
        throw ERROR_INVALID_DATA;
    }
    VariantCreate(VT_ARRAY | vt);
    // Bad definition of SafeArrayCopy forces us to cast away constness
    HRESULT hres = SafeArrayCopy((SAFEARRAY*)psaSrc, &parray);
    if (hres) throw hres;
	return *this;
}

const Variant& Variant::SetBoolean(Boolean f)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_BOOL) {
        VariantDestroy();
		VariantCreate(VT_BOOL);
	}
	boolVal = f;
	return *this;
}

const Variant& Variant::SetError(long err)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_ERROR) {
        VariantDestroy();
		VariantCreate(VT_ERROR);
	}
	scode = err;
	return *this;
}

const Variant& Variant::SetDate(DATE dt)
{
	// Free up previous VARIANT if necessary
	if (vt != VT_DATE) {
        VariantDestroy();
		VariantCreate(VT_DATE);
	}
	date = dt;
	return *this;
}

// Operations

// inline BOOL Variant::IsMissing()
// inline VARTYPE	Variant::Type()
// inline void Variant::Type(VARTYPE vartype)

Variant Variant::CopyAs(VARTYPE vtDst)
{
    Variant v;
	HRESULT hres = VariantChangeType(&v, this, 0, vtDst);
    if (hres) throw hres;
    return v;
}

Variant Variant::CopyPromote(VARTYPE vtDst)
{
    Variant v;
    if (Variant::Preciser(vt, vtDst)) {
	    HRESULT hres = VariantChangeType(&v, this, 0, vtDst);
        if (hres) throw hres;
    } else {
        v = *this;
    }
    v.Constructed(True);
    return v;
}

// inline Variant::operator BYTE() 
// inline Variant::operator short() 
// inline Variant::operator long()
// inline Variant::operator float()
// inline Variant::operator double()
// inline Variant::operator LONGLONG()
// inline Variant::operator CURRENCY()
// inline Variant::operator BSTR()
// inline Variant::operator VARIANT()

Variant::operator BYTE() const
{
    Variant v = *this;
    v.Type(VT_UI1);
    return v.bVal;
}

Variant::operator short() const
{
    Variant v = *this;
    v.Type(VT_I2);
    return v.iVal;
}


Variant::operator long() const
{
    Variant v = *this;
    v.Type(VT_I4);
    return v.lVal;
}

Variant::operator float() const
{
    Variant v = *this;
    v.Type(VT_R4);
    return v.fltVal;
}

Variant::operator double() const
{
    Variant v = *this;
    v.Type(VT_R8);
    return v.dblVal;
}

Variant::operator LONGLONG() const
{
    Variant v = *this;
    v.Type(VT_CY);
    return v.cyVal.int64;
}

Variant::operator CURRENCY() const
{
    Variant v = *this;
    v.Type(VT_CY);
    return v.cyVal;
}

Variant::operator BSTR() const
{
    Variant v = *this;
    v.Type(VT_BSTR);
    return SysAllocString(v.bstrVal);
}

Variant::operator BSTR()
{
    if (Type() == VT_BSTR) {
        return bstrVal;
    } else {
        return String(*this);
    }
}

Variant::operator String() const
{
    Variant v = *this;
    v.Type(VT_BSTR);
    return String(v);
}


Variant::operator String()
{
    Variant v = CopyAs(VT_BSTR);
    String s = LPCWSTR(v.bstrVal); 
    return s;
}

Variant::operator Variant() const
{
    Variant v = *this;
    return v;
}

// Friend operator functions

// +
const Variant& Variant::operator+=(Variant v)
{
    if (Variant::Preciser(vt, v.vt)) {
        switch (vt) {
        case VT_UI1:
            bVal += (BYTE)v;
            break;
        case VT_I2:
            iVal += (short)v;
            break;
        case VT_I4:
            lVal += (long)v;
            break;
        case VT_R4:
            fltVal += (float)v;
            break;
        case VT_R8:
            dblVal += (double)v;
            break;
        case VT_CY:
            cyVal.int64 += (LONGLONG)v;
            break;
        case VT_BSTR:
            {
            String s = bstrVal;
            s += String(v);
            *this = s;
            }
            break;
        default:
            throw DISP_E_TYPEMISMATCH;
            break;
        }
    } else {
        Type(v.vt);
        switch (v.vt) {
        case VT_UI1:
            bVal += v.bVal;
            break;
        case VT_I2:
            iVal += v.iVal;
            break;
        case VT_I4:
            lVal += v.lVal;
            break;
        case VT_R4:
            fltVal += v.fltVal;
            break;
        case VT_R8:
            dblVal += v.dblVal;
            break;
        case VT_CY:
            cyVal.int64 += v.cyVal.int64;
            break;
        case VT_BSTR:
            {
            String s = bstrVal;
            s += v.bstrVal;
            v = s;
            }
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    }
    return *this; 
}

Variant operator+(Variant& v1, Variant& v2)
{
    if (Variant::Preciser(v1.vt, v2.vt)) {
	    switch (v1.vt) {
	    case VT_UI1:
            return short(v1.bVal + (BYTE)v2);
	    case VT_I2:
            return long(v1.iVal + (short)v2);
	    case VT_I4:
            return v1.lVal + (long)v2;
	    case VT_R4:
            return v1.fltVal + (float)v2;
	    case VT_R8:
            return v1.dblVal + (double)v2;
        case VT_CY:
            return v1.cyVal.int64 + (LONGLONG)v2;
	    case VT_BSTR:
            {
            String s = v1.bstrVal;
            s += (String)v2;
            return s;
            }
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    } else {
	    switch (v2.vt) {
	    case VT_UI1:
            return short((BYTE)v2 + v2.bVal);
	    case VT_I2:
            return long((short)v2 + v2.iVal);
	    case VT_I4:
            return (long)v1 + v2.lVal;
	    case VT_R4:
            return (float)v1 + v2.fltVal;
	    case VT_R8:
            return (double)v1 + v2.dblVal;
        case VT_CY:
            return (LONGLONG)v1 + v2.cyVal.int64;
	    case VT_BSTR:
            {
            String s = v1.bstrVal;
            s += (String)v2;
            return s;
            }
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    }
}

//@B PlusPlus
// Prefix
Variant & Variant::operator++()
{
	switch (vt) {
	case VT_UI1:
        ++bVal;
        break;
    case VT_I2:
        ++iVal;
        break;
	case VT_I4:
        ++lVal;
        break;
	case VT_R4:
        ++fltVal;
        break;
	case VT_R8:
        ++dblVal;
        break;
    case VT_CY:
        ++cyVal.int64;
        break;
	default:
		throw DISP_E_TYPEMISMATCH;
	}
    return *this;
}
//@E PlusPlus
// Postfix
Variant Variant::operator++(int)
{
    Variant v = *this;
	switch (vt) {
	case VT_UI1:
        bVal++;
		break;
	case VT_I2:
        iVal++;
		break;
	case VT_I4:
        lVal++;
		break;
	case VT_R4:
        fltVal++;
		break;
	case VT_R8:
        dblVal++;
		break;
    case VT_CY:
        cyVal.int64++;
		break;
	default:
        throw DISP_E_TYPEMISMATCH;	
	}
    return v;
}


// -
const Variant& Variant::operator-=(Variant v)
{
    if (Variant::Preciser(vt, v.vt)) {
	    switch (vt) {
	    case VT_UI1:
            bVal -= (BYTE)v;
            break;
	    case VT_I2:
            iVal -= (short)v;
            break;
	    case VT_I4:
            lVal -= (long)v;
            break;
	    case VT_R4:
            fltVal -= (float)v;
            break;
	    case VT_R8:
            dblVal -= (double)v;
            break;
        case VT_CY:
            cyVal.int64 -= (LONGLONG)v;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    } else {
        Type(v.vt);
	    switch (v.vt) {
	    case VT_UI1:
            bVal -= v.bVal;
            break;
	    case VT_I2:
            iVal -= v.iVal;
            break;
	    case VT_I4:
            lVal -= v.lVal;
            break;
	    case VT_R4:
            fltVal -= v.fltVal;
            break;
	    case VT_R8:
            dblVal -= v.dblVal;
            break;
        case VT_CY:
            cyVal.int64 -= v.cyVal.int64;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    }
    return *this; 
}

Variant operator-(Variant& v1, Variant& v2)
{
    if (Variant::Preciser(v1.vt, v2.vt)) {
	    switch (v1.vt) {
	    case VT_UI1:
            return short(v1.bVal - (BYTE)v2);
	    case VT_I2:
            return long(v1.iVal - (short)v2);
	    case VT_I4:
            return v1.lVal - (long)v2;
	    case VT_R4:
            return v1.fltVal - (float)v2;
	    case VT_R8:
            return v1.dblVal - (double)v2;
        case VT_CY:
            return v1.cyVal.int64 - (LONGLONG)v2;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    } else {
	    switch (v2.vt) {
	    case VT_UI1:
            return short((BYTE)v2 - v2.bVal);
	    case VT_I2:
            return long((short)v2 - v2.iVal);
	    case VT_I4:
            return (long)v1 - v2.lVal;
	    case VT_R4:
            return (float)v1 - v2.fltVal;
	    case VT_R8:
            return (double)v1 - v2.dblVal;
        case VT_CY:
            return (LONGLONG)v1 - v2.cyVal.int64;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    }
}

// Prefix
Variant & Variant::operator--()
{
	switch (vt) {
	case VT_UI1:
        --bVal;
        break;
	case VT_I2:
        --iVal;
        break;
	case VT_I4:
        --lVal;
        break;
	case VT_R4:
        --fltVal;
        break;
	case VT_R8:
        --dblVal;
        break;
    case VT_CY:
        --cyVal.int64;
        break;
	default:
		throw DISP_E_TYPEMISMATCH;
	}
    return *this;
}
// Postfix
Variant Variant::operator--(int)
{
    Variant v = *this;
	switch (vt) {
	case VT_UI1:
        bVal--;
		break;
	case VT_I2:
        iVal--;
		break;
	case VT_I4:
        lVal--;
		break;
	case VT_R4:
        fltVal--;
		break;
	case VT_R8:
        dblVal--;
		break;
    case VT_CY:
        cyVal.int64--;
		break;
	default:
        throw DISP_E_TYPEMISMATCH;	
	}
    return v;
}

// *
const Variant& Variant::operator*=(Variant v)
{
    if (Variant::Preciser(vt, v.vt)) {
	    switch (vt) {
	    case VT_UI1:
            bVal *= (BYTE)v;
            break;
	    case VT_I2:
            iVal *= (short)v;
            break;
	    case VT_I4:
            lVal *= (long)v;
            break;
	    case VT_R4:
            fltVal *= (float)v;
            break;
	    case VT_R8:
            dblVal *= (double)v;
            break;
	    case VT_CY:
            cyVal.int64 *= (LONGLONG)v;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    } else {
        Type(v.vt);
	    switch (v.vt) {
	    case VT_UI1:
            bVal *= v.bVal;
            break;
	    case VT_I2:
            iVal *= v.iVal;
            break;
	    case VT_I4:
            lVal *= v.lVal;
            break;
	    case VT_R4:
            fltVal *= v.fltVal;
            break;
	    case VT_R8:
            dblVal *= v.dblVal;
            break;
        case VT_CY:
            cyVal.int64 *= v.cyVal.int64;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    }
    return *this; 
}

Variant operator*(Variant& v1, Variant& v2)
{
    if (Variant::Preciser(v1.vt, v2.vt)) {
	    switch (v1.vt) {
	    case VT_UI1:
            return short(v1.bVal * (BYTE)v2);
	    case VT_I2:
            return long(v1.iVal * (short)v2);
	    case VT_I4:
            return v1.lVal * (long)v2;
	    case VT_R4:
            return v1.fltVal * (float)v2;
	    case VT_R8:
            return v1.dblVal * (double)v2;
        case VT_CY:
            return v1.cyVal.int64 * (LONGLONG)v2;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    } else {
	    switch (v2.vt) {
	    case VT_UI1:
            return short((BYTE)v2 * v2.bVal);
	    case VT_I2:
            return long((short)v2 * v2.iVal);
	    case VT_I4:
            return (long)v1 * v2.lVal;
	    case VT_R4:
            return (float)v1 * v2.fltVal;
	    case VT_R8:
            return (double)v1 * v2.dblVal;
        case VT_CY:
            return (LONGLONG)v1 * v2.cyVal.int64;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    }
}

// /
const Variant& Variant::operator/=(Variant v)
{
    if (long(v) == 0L) throw DISP_E_EXCEPTION;
    if (Variant::Preciser(vt, v.vt)) {
	    switch (vt) {
	    case VT_UI1:
            bVal /= (BYTE)v;
            break;
	    case VT_I2:
            iVal /= (short)v;
            break;
	    case VT_I4:
            lVal /= (long)v;
            break;
	    case VT_R4:
            fltVal /= (float)v;
            break;
	    case VT_R8:
            dblVal /= (double)v;
            break;
	    case VT_CY:
            cyVal.int64 /= (LONGLONG)v;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    } else {
        Type(v.vt);
	    switch (v.vt) {
	    case VT_UI1:
            bVal /= v.bVal;
            break;
	    case VT_I2:
            iVal /= v.iVal;
            break;
	    case VT_I4:
            lVal /= v.lVal;
            break;
	    case VT_R4:
            fltVal /= v.fltVal;
            break;
	    case VT_R8:
            dblVal /= v.dblVal;
            break;
        case VT_CY:
            cyVal.int64 /= v.cyVal.int64;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    }
    return *this; 
}

Variant operator/(Variant& v1, Variant& v2)
{
    if (long(v2) == 0L) throw DISP_E_EXCEPTION;
    if (Variant::Preciser(v1.vt, v2.vt)) {
	    switch (v1.vt) {
	    case VT_UI1:
            return short(v1.bVal / (BYTE)v2);
	    case VT_I2:
            return long(v1.iVal / (short)v2);
	    case VT_I4:
            return v1.lVal / (long)v2;
	    case VT_R4:
            return v1.fltVal / (float)v2;
	    case VT_R8:
            return v1.dblVal / (double)v2;
        case VT_CY:
            return v1.cyVal.int64 * (LONGLONG)v2;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    } else {
	    switch (v2.vt) {
	    case VT_UI1:
            return short((BYTE)v2 / v2.bVal);
	    case VT_I2:
            return long((short)v2 / v2.iVal);
	    case VT_I4:
            return (long)v1 / v2.lVal;
	    case VT_R4:
            return (float)v1 / v2.fltVal;
	    case VT_R8:
            return (double)v1 / v2.dblVal;
        case VT_CY:
            return (LONGLONG)v1 * v2.cyVal.int64;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    }
}

// %
const Variant& Variant::operator%=(Variant v)
{
    if (long(v) == 0L) throw DISP_E_EXCEPTION;
    if (Variant::Preciser(vt, v.vt)) {
	    switch (vt) {
	    case VT_UI1:
            bVal %= (BYTE)v;
            break;
	    case VT_I2:
            iVal %= (short)v;
            break;
	    case VT_I4:
            lVal %= (long)v;
            break;
	    case VT_CY:
            cyVal.int64 %= (LONGLONG)v;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    } else {
        Type(v.vt);
	    switch (v.vt) {
	    case VT_UI1:
            bVal %= v.bVal;
            break;
	    case VT_I2:
            iVal %= v.iVal;
            break;
	    case VT_I4:
            lVal %= v.lVal;
            break;
        case VT_CY:
            cyVal.int64 %= v.cyVal.int64;
            break;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            break;
	    }
    }
    return *this; 
}

Variant operator%(Variant& v1, Variant& v2)
{
    if (long(v2) == 0L) throw DISP_E_EXCEPTION;
    if (Variant::Preciser(v1.vt, v2.vt)) {
	    switch (v1.vt) {
	    case VT_UI1:
            return short(v1.bVal % (BYTE)v2);
	    case VT_I2:
            return long(v1.iVal % (short)v2);
	    case VT_I4:
            return v1.lVal % (long)v2;
        case VT_CY:
            return v1.cyVal.int64 * (LONGLONG)v2;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    } else {
	    switch (v2.vt) {
	    case VT_UI1:
            return short((BYTE)v2 % v2.bVal);
	    case VT_I2:
            return long((short)v2 % v2.iVal);
	    case VT_I4:
            return (long)v1 % v2.lVal;
        case VT_CY:
            return (LONGLONG)v1 * v2.cyVal.int64;
	    default:
		    throw DISP_E_TYPEMISMATCH;
            return 0L;
	    }
    }
}

// Logical operators

// Literal comparison. Types and values must match.
BOOL operator==(const Variant& v1, const Variant& v2)
{
  try {
	// Check type specific values
	switch (v1.vt)	{
	case VT_EMPTY:
		return v2.vt == VT_EMPTY;
	case VT_NULL:
		return v2.vt == VT_NULL;
	case VT_BOOL:
		return v1.boolVal == ((short)v2 != 0);
	case VT_UI1:
		return v1.bVal == (BYTE)v2;
	case VT_I2:
		return v1.iVal == (short)v2;
	case VT_I4:
		return v1.lVal == (long)v2;
	case VT_R4:
		return v1.fltVal == (float)v2;
	case VT_R8:
		return v1.dblVal == (double)v2;
	case VT_CY:
		return v1.cyVal == (LONGLONG)v2;
	case VT_DATE:
		return v1.date == (DATE)v2;
	case VT_BSTR:
		{
        String s = v2;
        return wcscmp(v1.bstrVal, (BSTR)s) == 0;
		}
	case VT_ERROR:
		return v2.vt == VT_ERROR && v1.scode == v2.scode;
	case VT_DISPATCH:
	case VT_UNKNOWN:
		return v1.punkVal == v2.punkVal;
	default:
		throw DISP_E_BADVARTYPE;
		// fall through
	}

	return FALSE;
  } catch(...) {
    // Type conversion errors always indicate not equal
    return FALSE;
  }
}

BOOL operator<(const Variant& v1, const Variant& v2)
{
  try {
	// Check type specific values
	switch (v1.vt)	{
	case VT_EMPTY:
		return v2.vt != VT_EMPTY;
	case VT_NULL:
		return v2.vt != VT_NULL;
	case VT_BOOL:
		return v1.boolVal < ((short)v2 != 0);
	case VT_UI1:
		return v1.bVal < (BYTE)v2;
	case VT_I2:
		return v1.iVal < (short)v2;
	case VT_I4:
		return v1.lVal < (long)v2;
	case VT_R4:
		return v1.fltVal < (float)v2;
	case VT_R8:
		return v1.dblVal < (double)v2;
	case VT_CY:
		return v1.cyVal.int64 < (LONGLONG)v2;
	case VT_DATE:
		return v1.date < (DATE)v2;
	case VT_BSTR:
		{
        String s = v2;
        return wcscmp(v1.bstrVal, (BSTR)s) < 0;
		}
	case VT_ERROR:
	case VT_DISPATCH:
	case VT_UNKNOWN:
	default:
        throw DISP_E_BADVARTYPE;
		// fall through
	}
  } catch(...) {
    // Type conversion errors always indicate less than
    return TRUE;
  }
}

// Only have to implement == and <.
// Others !=, <=, >=, and > implemented trivially with first two.
// inline BOOL operator!=(const Variant& v1, const Variant& v2)
// inline BOOL operator<=(const Variant& v1, const Variant& v2)
// inline BOOL operator>=(const Variant& v1, const Variant& v2)
// inline BOOL operator>(const Variant& v1, const Variant& v2)

ostream& operator<<(ostream& os, Variant& v)
{
  // Let OLE code translate to string
  try {
    String s = v;
    os << s;   // Automatic convertions to ANSI
  } catch(...) {
    // If VT_ERROR, we translate, otherwise insert blank
    if (v.vt == VT_ERROR) {
        os << "Facility:" << HRESULT_FACILITY(v.scode)
           << ", Severity:" << HRESULT_SEVERITY(v.scode) 
           << ", Code:" << HRESULT_CODE(v.scode);
    }
  }
    return os;   
}

// Check whether one type is more precise than another
BOOL Variant::Preciser(VARTYPE vt1, VARTYPE vt2)
{
    // Precision data table
    static int aiPrecise[] = {
        0, // VT_EMPTY	= 0,
	    0, // VT_NULL	= 1,
	    2, // VT_I2	= 2,
	    3, // VT_I4	= 3,
	    4, // VT_R4	= 4,
	    5, // VT_R8	= 5,
	    6, // VT_CY	= 6,
	    5, // VT_DATE	= 7,
	    7, // VT_BSTR	= 8,
	    0, // VT_DISPATCH	= 9,
	    0, // VT_ERROR	= 10,
	    0, // VT_BOOL	= 11,
	    0, // VT_VARIANT	= 12,
	    0, // VT_UNKNOWN	= 13,
	    0, // VT_I1	= 16,
	    1  // VT_UI1	= 17,
    };
    if (vt1 > VT_UI1 || vt2 > VT_UI1) throw E_INVALIDARG;
    return aiPrecise[vt1] > aiPrecise[vt2];
}

