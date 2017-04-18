// SafeArrah.H
 
#ifndef _SAFEARRAY_H_
#define _SAFEARRAY_H_

// Dim class encapsulates an array dimension
//@B Dim
class Dim : public SAFEARRAYBOUND
{
public:
	Dim(const long iLo, const long iHi)
	{ cElements = abs(iHi - iLo) + 1; lLbound = iLo; }
	Dim(const long c)
	{ cElements = c; lLbound = 0; }
	const Dim & operator=(const Dim & dim) 
	{ cElements = dim.cElements; lLbound = dim.lLbound; return *this; }
	const Dim & operator=(const long c) 
	{ cElements = c; lLbound = 0; return *this; }
	~Dim() {}
	long Elements() { return cElements; }
	long LBound() { return lLbound; }
	long UBound() { return lLbound + cElements - 1; }
};
//@E Dim

// Warning: Unused bit from fFeatures field could be used someday
const WORD VTA_CONSTRUCTED = 0x80;

// SafeArray container class for OLE types

//@B SafeArray1
template<class T, VARTYPE vt> 
class SafeArray 
{
public:
	// Constructors
	SafeArray();
	SafeArray(SAFEARRAY * psaSrc);
	SafeArray(Dim & dim);
    // Copy constructor
	SafeArray(const SafeArray & saSrc);

	// Destructor
	~SafeArray(); 

	// Operator equal
	const SafeArray & operator=(const SafeArray & saSrc);

	// Indexing
	T & Get(long i);
	T & Set(T & t, long i);
	T & operator[](const long i);    // C++ style (0-indexed)
	T & operator()(const long i);    // Basic style (LBound-indexed)
//@E SafeArray1

	// Type casts
	operator SAFEARRAY(); 
	operator SAFEARRAY() const; 
	operator Variant(); 
	operator Variant() const; 

	// Operations
	Boolean ReDim(Dim & dim);
	long LBound();
	long UBound();
	long Elements();
	long Dimensions();
    Boolean IsSizable();
	void Lock();
	void Unlock();

//@B SafeArray2
private:
	SAFEARRAY * psa;
    void Destroy();
    Boolean IsConstructed();
    void Constructed(Boolean f);
};
//@E SafeArray2

// Private helpers

template<class T, VARTYPE vt> 
inline void SafeArray<T,vt>::Destroy()
{
    Constructed(False);
	HRESULT hres = SafeArrayDestroy(psa);
    if (hres) throw hres;
}

template<class T, VARTYPE vt> 
inline Boolean SafeArray<T,vt>::IsConstructed()
{
    return (psa->fFeatures & VTA_CONSTRUCTED) ? True : False;
}

template<class T, VARTYPE vt> 
inline void SafeArray<T,vt>::Constructed(Boolean f)
{
    if (f) {
        psa->fFeatures |= VTA_CONSTRUCTED;
    } else {
        psa->fFeatures &= ~VTA_CONSTRUCTED;
    }
}

// Constructors
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray() 
{ 
    Dim dim(0);
	psa = SafeArrayCreate(vt, 1, &dim); 
    Constructed(True);
    if (psa == NULL) throw E_OUTOFMEMORY;
}


template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray(SAFEARRAY * psaSrc) 
{ 
    if (SafeArrayGetDim(psaSrc) != 1) throw E_INVALIDARG;
    Constructed(False);
    psa = psaSrc; 
}

template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray(const SafeArray & saSrc) 
{
    HRESULT hres = SafeArrayCopy(saSrc.psa, &psa);
    Constructed(True);
    if (hres) throw hres;
}


template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray(Dim & dim) 
{
	psa = SafeArrayCreate(vt, 1, &dim); 
    Constructed(True);
    if (psa == NULL) throw E_OUTOFMEMORY;
} 

// Destructor
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::~SafeArray()
{
	if (IsConstructed()) {
        Destroy();
    }
} 
	
// Operator = 
template<class T, VARTYPE vt> 
const SafeArray<T,vt> & SafeArray<T,vt>::operator=(const SafeArray & saSrc)
{
    if (psa) {
        
        SafeArrayDestroy(psa);
    }
    HRESULT hres = SafeArrayCopy(saSrc.psa, &psa);
    Constructed(True);
    if (hres) throw hres;
    return *this;
}

// Type casts
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::operator SAFEARRAY()
{
    return *psa; 
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator SAFEARRAY() const
{
    static SAFEARRAY * psaT;
    SafeArrayCopy(psa, &psaT);
    psaT->fFeatures &= ~VTA_CONSTRUCTED;
    return *psaT;
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator Variant() 
{
    return Variant(psa);
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator Variant() const
{
    static Variant v(psa);
    return v;
}

// Indexing
template<class T, VARTYPE vt> 
T & SafeArray<T,vt>::Get(long i)
{
	static T tRes;
	HRESULT hres = SafeArrayGetElement(psa, &i, &tRes);
	if (hres) throw hres;
	return tRes;
}

//@B Indexing
template<class T, VARTYPE vt> 
inline T & SafeArray<T,vt>::Set(T & t, long i)
{
	HRESULT hres = SafeArrayPutElement(psa, &i, (T *)&t);
	if (hres) throw hres;
    return t;
}

template<class T, VARTYPE vt> 
inline T & SafeArray<T,vt>::operator[](const long i)
{
    if (i < 0 || i > Elements() - 1) throw DISP_E_BADINDEX;
	return ((T*)psa->pvData)[i];
}

template<class T, VARTYPE vt> 
T & SafeArray<T,vt>::operator()(const long i)
{
    if (i < LBound() || i > UBound()) throw DISP_E_BADINDEX;
	return ((T*)psa->pvData)[i - LBound()];
}
//@E Indexing

// Operations
template<class T, VARTYPE vt> 
Boolean SafeArray<T,vt>::ReDim(Dim &dim)
{
    if (!IsSizable()) {
        return False;
    }
	HRESULT hres = SafeArrayRedim(psa, &dim);
	if (hres) throw hres;
    return True;
}

template<class T, VARTYPE vt> 
long SafeArray<T,vt>::LBound()
{
	long iRes;
	HRESULT hres = SafeArrayGetLBound(psa, 1, &iRes);
	if (hres) throw hres;
	return iRes;
}

template<class T, VARTYPE vt> 
inline long SafeArray<T,vt>::Elements()
{
	return psa->rgsabound[0].cElements;
}

template<class T, VARTYPE vt> 
long SafeArray<T,vt>::UBound()
{
	long iRes;
	HRESULT hres = SafeArrayGetUBound(psa, 1, &iRes);
	if (hres) throw hres;
	return iRes;
}

template<class T, VARTYPE vt> 
inline long SafeArray<T,vt>::Dimensions()
{
	return 1;
}

template<class T, VARTYPE vt> 
inline Boolean SafeArray<T,vt>::IsSizable()
{
    return (psa->fFeatures & FADF_FIXEDSIZE) ? False : True;
}

template<class T, VARTYPE vt>
inline void SafeArray<T,vt>::Lock()
{
	HRESULT hres = SafeArrayLock(psa);
	if (hres) throw hres;
}

template<class T, VARTYPE vt>
inline void SafeArray<T,vt>::Unlock()
{
	HRESULT hres = SafeArrayUnlock(psa);
	if (hres) throw hres;
}


#endif // _SAFEARRAY_H_
