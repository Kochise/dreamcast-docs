
#ifndef _TEST_H_
#define _TEST_H_

BSTR DLLAPI TestBStrArgs(
    BCSTR bsIn, 
	BSTR * pbsInOut,
	BSTR * pbsOut);

void DLLAPI TestBStr();

BSTR DLLAPI TestBString(
    BCSTR bsIn, 
	BSTR * pbsInOut,
	BSTR * pbsOut);

Variant DLLAPI TestVariant(
    Variant vIn, 
    Variant * pvInOut, 
    Variant * pvOut);

#if 0
//@B TestSafeArrayProto2
Variant DLLAPI TestSafeArray(SafeArray<short, VT_I2> & aiInOut, 
                             SafeArray<BSTR, VT_BSTR> & asOut);
//@E TestSafeArrayProto2
#else
//@B TestSafeArrayProto1
Variant DLLAPI TestSafeArray(ArrayInteger & aiInOut, ArrayString & asOut);
//@E TestSafeArrayProto1
#endif

//@B TestSA
Variant DLLAPI TestSA(SAFEARRAY ** ppsaiInOut, SAFEARRAY ** ppsasOut);
//@E TestSA

double DLLAPI AddEmUp(ParamArray & avParams);

#endif // _TEST_H_
