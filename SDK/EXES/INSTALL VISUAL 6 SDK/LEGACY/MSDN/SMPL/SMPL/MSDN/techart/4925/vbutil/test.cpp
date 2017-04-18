/* TEST.CPP - Test functions for BSTR, String, and other types.
 */

#include "VBUtil.H"
#include "OleType.H"
#include "Test.h"

BSTR DLLAPI TestBStrArgs(
    BCSTR bsIn, 
	BSTR * pbsInOut,
	BSTR * pbsOut)
{
	BSTR bsRet;
	Boolean f = False;

#define COPYINMODIFY 1
#define MODIFYIN 0
#define RETURNIN 0
#define REALLOCATEIN 0
#if COPYINMODIFY
	// Copy an in string and modify copy
	bsRet = SysAllocString(bsIn);
	_wcsrev(bsRet);
#elif MODIFYIN
	// Modify an in string
	_wcsrev(bsIn);
	bsRet = SysAllocString(bsIn);
	// Illegal, but you can get away with it
#elif RETURNIN
	// Return an in string
	bsRet = bsIn;
	// Illegal and OLE fails
#elif REALLOCATEIN 
	// Reallocate in string
	f = SysReAllocString(&bsIn, L"In for good");
	// Illegal and C++ consts won't let you do it
#endif

#define MODIFYINOUT 1
#define COPYINREALLOCOUT 0
#define NULLIFYINOUT 0
#define COPYINFREEOUT 0
#if MODIFYINOUT 
	// Modify in/out 
	_wcsupr(*pbsInOut);
	// Legal and recommended
#elif COPYINREALLOCOUT
	// Use input
	f = SysReAllocString(&bsRet, *pbsInOut);
	// Replace with different output
	f = SysReAllocString(pbsInOut, L"Out and in");
	// Legal and recommended
#elif NULLIFYINOUT
	// Return NULL through string
	f = SysReAllocString(pbsInOut, NULL);
	// Legal and recommended
#elif COPYINFREEOUT
	// Use input
	f = SysReAllocString(&bsRet, *pbsInOut);
	// Free output
	SysFreeString(*pbsInOut);
	// Illegal and OLE fails
#endif
	
#define ALLOCOUT 1
#define MODIFYOUT 0
#define REALLOCOUT 0
#if ALLOCOUT  
	// Allocate a string for out parameter
	*pbsOut = SysAllocString(L"Out the hatch");
	// Legal and recommended
#elif MODIFYOUT 
	// Modify out parameter
	_wcslwr(*pbsOut);
	// Illegal, probable crash because there's nothing there
#elif REALLOCOUT 
	// Reallocate new string
	f = SysReAllocString(pbsOut, L"Time out");
	// Illegal, but you might get away with it
#endif

#define ALLOCRET 1
#define NULLRET 0
#define INRET 0
#if ALLOCRET
	// Return an allocated string
	return bsRet;
	// Legal
#elif NULLRET
	// Return null
	return NULL;
	// Legal
#elif INRET
	// Return an input string
	return bsIn;
	// Illegal and OLE fails
#endif
} 

void DLLAPI TestBStr()
{
    // Run in a debugger to see the results
	Boolean f;
	unsigned cch;

    // Allocate strings
	BSTR bs1 = SysAllocString(L"Test");
	BSTR bs2 = SysAllocString(L"");
	BSTR bs3 = SysAllocString(NULL);
    // Test their lengths
	cch = SysStringLen(bs1);
	cch = SysStringLen(bs2);
	cch = SysStringLen(bs3);
    // Reallocate them. 
	f = SysReAllocString(&bs2, L"Junk");
	f = SysReAllocString(&bs1, bs1);
	f = SysReAllocString(&bs2, L"Trash");
	f = SysReAllocString(&bs3, L"Funk");
    // Free them
	SysFreeString(bs1);
	SysFreeString(bs2);
	SysFreeString(bs3);

    // Allocate them by length
	bs1 = SysAllocStringLen(L"Test", 2);
	bs2 = SysAllocStringLen(L"Where is it?", 8);
	bs3 = SysAllocStringLen(NULL, 10);
    // Reallocate them by length
	f = SysReAllocStringLen(&bs1, L"Grime", 2);
	f = SysReAllocStringLen(&bs2, bs2, 3);
	f = SysReAllocStringLen(&bs3, NULL, 10);
    // Free them 
	SysFreeString(bs1);
	SysFreeString(bs2);
	SysFreeString(bs3);

    // Allocate byte strings
	bs1 = SysAllocStringByteLen("Test", 2);
	bs2 = SysAllocStringByteLen("Test", 8);
	bs3 = SysAllocStringByteLen(NULL, 10);
    // Test their lengths
	cch = SysStringByteLen(bs1);
	cch = SysStringByteLen(bs2);
	cch = SysStringByteLen(bs3);
    // Free them
	SysFreeString(bs1);
	SysFreeString(bs2);
	SysFreeString(bs3);

    // Allocate from ANSI strings
	bs1 = SysAllocStringA("Test");
	bs2 = SysAllocStringA("");
	bs3 = SysAllocStringA(NULL);
    // Test their lengths
	cch = SysStringLen(bs1);
	cch = SysStringLen(bs2);
	cch = SysStringLen(bs3);
    // Free them
	SysFreeString(bs1);
	SysFreeString(bs2);
	SysFreeString(bs3);

}

//@B TestString1
BSTR DLLAPI TestString(
    BCSTR bsIn, 
	BSTR * pbsInOut,
	BSTR * pbsOut)
{
//@E TestString1
  try {
    
//@B TestString2
	// Constructors
	String sTmp;                    // Uninitialized
	String sIn = bsIn;              // In argument from BSTR
	String sCopy = *pbsInOut;       // In/out argument from BSTR
	String sString = sIn;           // One String from another
	String sChar(1, WCHAR('A'));    // A single character
	String sChars(30, WCHAR('B'));  // A filled buffer 
	String sBuf(30);                // An unititialized buffer
	String sWide = _W("Wide");      // From Unicode string
	String sNarrow = "Narrow";      // From ANSI string
	String sNative = _T("Native");  // From native string
	String sRet;
//@E TestString2

//@B TestString3
	// Assignment
	WCHAR wsz[] = L"Wide";
	char sz[] = "Narrow";
	sTmp = sIn;                     // From another String variable
	sTmp = _W("Wide");              // From Unicode literal string
	sTmp = WCHAR('W');              // From Unicode character
    sTmp = LPCWSTR(wsz);            // From Unicode string variable
    sTmp = LPCSTR(sz);              // From ANSI string variable
//@E TestString3

//@B TestString4
    ostrstream ostr;

    ostr << endcl << "Test length and resize:" << endcl;
    sTmp = _W("Yo!");
    ostr << "sTmp = _W(\"Yo!\"); // sTmp==\"" << sTmp 
         << "\", " << "sTmp.Length()==" << sTmp.Length() << endcl;
//@E TestString4
    sTmp.Resize(20);
    ostr << "sTmp.Resize(20);  // sTmp==\"" << sTmp 
         << "\", " << "sTmp.Length()==" << sTmp.Length() 
         << ", " << "sTmp.LengthZ()==" << sTmp.LengthZ() << endcl;
    sTmp.ResizeZ();
    ostr << "sTmp.ResizeZ();   // sTmp==\"" << sTmp 
         << "\", " << "sTmp.Length()==" << sTmp.Length() << endcl;

    // Null and Empty
    ostr << endcl << "Test Empty, Nullify, IsEmpty, and IsNull:" << endcl;
    sTmp = "Empty";
    ostr << "sTmp = \"Empty\";   // sTmp==\"" << sTmp << "\"," 
         << "sTmp.IsEmpty==" << sTmp.IsEmpty() 
         << ", sTmp.IsNull==" << sTmp.IsNull() << endcl;
	sTmp.Empty();
    ostr << "sTmp.Empty();     // sTmp==\"" << sTmp << "\"," 
         << "sTmp.IsEmpty==" << sTmp.IsEmpty() 
         << ", sTmp.IsNull==" << sTmp.IsNull() << endcl;

    sTmp.Nullify();
    ostr << "sTmp.Nullify();   // sTmp==\"" << sTmp << "\"," 
         << "sTmp.IsEmpty==" << sTmp.IsEmpty() 
         << ", sTmp.IsNull==" << sTmp.IsNull() << endcl;

	// Logical operators
    ostr << endcl << "Test logical operators:" << endcl
         << "sTmp==\"" << sTmp << "\", sNarrow==\"" << sNarrow 
         << "\", sWide==\"" << sWide << "\"" << endcl;

    ostr << "(sTmp == BNULL)==" << (sTmp == BNULL) << endcl
	     << "(sTmp == _B(\"\"))==" << (sTmp == _B("")) << endcl
	     << "(sNarrow == sWide)==" << (sNarrow == sWide) << endcl
	     << "(sNarrow == _B(\"Narrow\"))==" << (sNarrow == _B("Narrow")) << endcl
	     << "(_B(\"Narrow\") == sNarrow)==" << (_B("Narrow") == sNarrow) << endcl
	     << "(sNarrow != sWide)==" << (sNarrow != sWide) << endcl
	     << "(sNarrow < sWide)==" << (sNarrow < sWide) << endcl
	     << "(sNarrow <= sWide)==" << (sNarrow <= sWide) << endcl
	     << "(sNarrow > sWide)==" << (sNarrow > sWide) << endcl
	     << "(sNarrow >= sWide)==" << (sNarrow >= sWide) << endcl;

	// Indexing
	int i = 2;
	WCHAR wch = WCHAR('n');

    ostr << endcl << "Test indexing:" << endcl
         << "sWide==\"" << sWide << "\", i==" << i 
         << ", wch=='" << CHAR(wch) << "'" << endcl;

	sWide[i] = wch;
    ostr << "sWide[i] = wch;     // sWide==\"" << sWide << "\"" << endcl;

	wch = sWide[i - 1];
    ostr << "wch = sWide[i - 1]; // wch=='" << CHAR(wch) << "'" << endcl;

    sWide[0] = 'F'; 
    ostr << "sWide[0] = 'F';     // sWide==\"" << sWide << "\"" << endcl;

	// Concatenation
    ostr << endcl << "Test concatenation:" << endcl
         << "sChar==\"" << sChar << "\", sIn==\"" << sIn << "\"" << endcl;
    
	sChar += sIn;
    ostr << "sChar += sIn;        // sChar==\"" << sChar << "\"" << endcl;
	sChar += WCHAR('F');
    ostr << "sChar += WCHAR('F'); // sChar==\"" << sChar << "\"" << endcl;
	sChar += 'G';
	ostr << "sChar += 'G';        // sChar==\"" << sChar << "\"" << endcl;
	sChar += _W("Wide");
	ostr << "sChar += _W(\"Wide\"); // sChar==\"" << sChar << "\"" << endcl;
	sChar += "Narrow";
	ostr << "sChar += \"Narrow\";   // sChar==\"" << sChar << "\"" << endcl;

	sTmp = sNarrow + sNative + _W("Slow") + "Fast" + WCHAR('C') + 'D';
	ostr << "sTmp = sNarrow + sNative + _W(\"Slow\") + "
            "\"Fast\" + WCHAR('C') + 'D'" << endcl
         << "// sTmp==\"" << sTmp << "\"" << endcl;

	// SuStrings
    ostr << endcl << "Test substrings:" << endcl;
	sChar = sTmp.Mid(7, 6);
    ostr << "sChar = sTmp.Mid(7, 6); // sChar==\"" << sChar << "\"" << endcl;
	sChar = sTmp.Mid(7);

    ostr << "sChar = sTmp.Mid(7);    // sChar==\"" << sChar << "\"" << endcl;
	sChar = sTmp.Left(6);
    ostr << "sChar = sTmp.Left(6);   // sChar==\"" << sChar << "\"" << endcl;
	sChar = sTmp.Right(6);
    ostr << "sChar = sTmp.Right(6);  // sChar==\"" << sChar << "\"" << endcl;

	// Transformations
    ostr << endcl << "Test transformations:" << endcl
         << "sWide==\"" << sWide << "\"" << endcl;
	sWide.UCase();
    ostr << "sWide.UCase();          // sWide==\"" << sWide << "\"" << endcl;
	sWide.LCase();
    ostr << "sWide.LCase();          // sWide==\"" << sWide << "\"" << endcl;
	sWide.Reverse();
    ostr << "sWide.Reverse();        // sWide==\"" << sWide << "\"" << endcl;
	sChar = UCase(sWide);
    ostr << "sChar = UCase(sWide);   // sChar==\"" << sChar 
         << "\", sWide==\"" << sWide << "\"" << endcl;
	sChar = LCase(sWide);
    ostr << "sChar = LCase(sWide);   // sChar==\"" << sChar 
         << "\", sWide==\"" << sWide << "\"" << endcl;
	sChar = Reverse(sWide);
    ostr << "sChar = Reverse(sWide); // sChar==\"" << sChar 
         << "\", sWide==\"" << sWide << "\"" << endcl;

	// Trimming
    sTmp = _W("   \t Stuff  \t ");
    ostr << endcl << "Test trimming:" << endcl;
    sChar = Trim(sTmp);
    ostr << "sChar = Trim(sTmp);     // sChar==\"" << sChar 
         << "\", sTmp==\"" << sTmp<< "\"" << endcl;
	sTmp.Trim();
    ostr << "sTmp.Trim();            // sTmp==\"" << sTmp << "\"" << endcl;
	
	// Find suString or character
	sTmp = _W("A string In a String in a String in a string.");
    ostr << endcl << "Test character and string find:" << endcl
         << "// sTmp=\"" << sTmp << "\"" << endcl
         << "//      \"12345678901234567890123456789012345678901234567890\"" << endcl;
	i = sTmp.Find('S');
    ostr << "i = sTmp.Find('S');                                // Found at position: " << i << endcl;
	i = sTmp.Find('S', ffReverse);
    ostr << "i = sTmp.Find('S', ffReverse);                     // Found at position: " << i << endcl;
	i = sTmp.Find('S', ffIgnoreCase);
    ostr << "i = sTmp.Find('S', ffIgnoreCase);                  // Found at position: " << i << endcl;
	i = sTmp.Find('S', ffReverse | ffIgnoreCase);
    ostr << "i = sTmp.Find('S', ffReverse | ffIgnoreCase);      // Found at position: " << i << endcl;
	i = sTmp.Find('Z');
    ostr << "i = sTmp.Find('Z');                                // Found at position: " << i << endcl; 
	i = sTmp.Find("String");
    ostr << "i = sTmp.Find(\"String\");                           // Found at position: " << i << endcl;
	i = sTmp.Find("String", ffReverse);
    ostr << "i = sTmp.Find(\"String\", ffReverse);                // Found at position: " << i << endcl;
	i = sTmp.Find("String", ffIgnoreCase);
    ostr << "i = sTmp.Find(\"String\", ffIgnoreCase);             // Found at position: " << i << endcl; 
	i = sTmp.Find("String", ffIgnoreCase | ffReverse);
    ostr << "i = sTmp.Find(\"String\", ffIgnoreCase | ffReverse); // Found at position: " << i << endcl; 
	i = sTmp.Find("Ztring");
    ostr << "i = sTmp.Find(\"Ztring\");                           // Found at position: " << i << endcl;

//@B TestString9
    ostr << ends;
    char * pch = ostr.str();
    sRet = pch;
    delete[] pch;
//@E TestString9

//@B TestString10
    // Return through out parameters
    sTmp = _W("...send me back");
    *pbsInOut = sTmp;
    *pbsOut = _B("Out of the fire");

    // Return value
	return sRet;

  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  } 
}
//@E TestString10

Variant DLLAPI TestVariant(Variant vIn, 
                           Variant * pvInOut, 
                           Variant * pvOut)
{
  try {

    ostrstream ostr;

    ostr << endcl << endcl << "Testing arguments:" << endcl;
    ostr << "vIn: " << vIn << endcl;
    ostr << "pvInOut: " << *pvInOut << endcl;

	Variant vRet, vTmp;
//@B VariantInit
	Variant vInteger = (Integer)6;
	Variant vLong = 9L;
    Variant vSingle = 7.87f;
	Variant vDouble = -89.2;
	Variant vBoolean(True, VT_BOOL);
	Variant vString = _W("String");  
	Variant vError((Long)DISP_E_EXCEPTION, VT_ERROR);
	Variant vCurrency = (Currency)78965;
	Variant vDate(2.5, VT_DATE);    // Noon, January 1, 1900
//@E VariantInit

    ostr << endcl << "Testing output of different objects:" << endcl
         << "vInteger==" << vInteger << endcl
         << "vLong==" << vLong << endcl
         << "vSingle==" << vSingle << endcl
         << "vDouble==" << vDouble << endcl
         << "vBoolean==" << vBoolean << endcl
         << "vString==\"" << vString << "\"" << endcl
         << "vError==" << vError << endcl
         << "vCurrency==" << vCurrency<< endcl
         << "vDate==" << vDate << endcl;

//@B TestVariant1
    // Assign to types that have no operator=
    vBoolean.SetBoolean(False);
    vError.SetError((Long)E_ACCESSDENIED);
    vDate.SetDate(3333.125);
//@E TestVariant1
    
//@B TestVariant2
    // Assign to nearest type and then change to desired type
    vDate = 3333.125;
    vDate.Type(VT_DATE);
//@E TestVariant2
    
//@B TestVariant3
    // Assign double to long (throwing away remainder)
    Long i = vDouble;
    // Assign a date to a string (comes out in date string format)
    String s = vDate;
    // Assign numeric string a numeric variable
    vString = _W("3.1416");
    vSingle = vString.CopyAs(VT_R4);
//@E TestVariant3
    
    ostr << endcl << "Testing arithmetic:" << endcl;
    vTmp = vInteger + vLong;
    ostr << "vTmp = vInteger + vLong; // " 
         << vInteger << " + " << vLong << " == " << vTmp << endcl;
    ostr << "vTmp += vDouble;         // " << vTmp;
    vTmp += vDouble;
    ostr << " += " << vDouble << " == " << vTmp << endcl;
    Single flt = 3.25f;
    ostr << "Single flt = 3.25;" << endcl
         << "flt += (Single)vTmp;      // " << flt;
    flt += (Single)vTmp;
    ostr << " += " << vTmp << " == " << flt << endcl;
    ostr << "vTmp += (Integer)77;       // " << vTmp;
    vTmp += Integer(77);
    ostr << " += " << (Integer)77 << " == " << vTmp << endcl;
    ostr << "vTmp += vInteger++;      // " << vTmp;
    vTmp += vInteger++;
    ostr << " += " << (Integer)vInteger - 1 << " == " << vTmp << endcl;
    ostr << "vTmp += ++vInteger;      // " << vTmp;
    vTmp += ++vInteger;    
    ostr << " += " << vInteger << " == " << vTmp << endcl;

    vString = _W("Stuff");
    vTmp = vString + vLong;
    ostr << "vTmp = vString + vLong;  // "
         << vString << " + " << vLong << " == " << vTmp << endcl;
    ostr << "vTmp += vDouble;         // " << vTmp << " += ";
    vTmp += vDouble;
    ostr << vDouble << " == " << vTmp << endcl;
    
    vTmp = vInteger - vLong;
    ostr << "vTmp = vInteger - vLong; // " 
         << vInteger << " - " << vLong << " == " << vTmp << endcl;
    ostr << "vTmp -= vDouble;         // " << vTmp;
    vTmp -= vDouble;
    ostr << " -= " << vDouble << " == " << vTmp << endcl;
    ostr << "flt -= (Single)vTmp;      // " << flt;
    flt -= (Single)vTmp;
    ostr << " -= " << vTmp << " == " << flt << endcl;
    ostr << "vTmp -= Integer(77);       // " << vTmp;
    vTmp -= (Integer)77;
    ostr << " -= " << (Integer)77 << " == " << vTmp << endcl;
    
    ostr << "vTmp -= vInteger--;      // " << vTmp;
    vTmp -= vInteger--;
    ostr << " -= " << (Integer)vInteger + 1 << " == " << vTmp << endcl;
    ostr << "vTmp -= --vInteger;      // " << vTmp;
    vTmp -= --vInteger;
    ostr << " -= " << vInteger << " == " << vTmp << endcl;
    
    vTmp = vInteger * vLong;
    ostr << "vTmp = vInteger * vLong; // " 
         << vInteger << " * " << vLong << " == " << vTmp << endcl;
    ostr << "vTmp *= vDouble;         // " << vTmp;
    vTmp *= vDouble;
    ostr << " *= " << vDouble << " == " << vTmp << endcl;
    ostr << "flt *= (Single)vTmp;      // " << flt;
    flt *= (Single)vTmp;
    ostr << " *= " << vTmp << " == " << flt << endcl;
    ostr << "vTmp *= Integer(7);        // " << vTmp;
    vTmp *= (Integer)7;
    ostr << " *= " << (Integer)7 << " == " << vTmp << endcl;
    
    vTmp = vLong / vInteger;
    ostr << "vTmp = vInteger / vLong; // " 
         << vLong << " / " << vInteger << " == " << vTmp << endcl;
    ostr << "vTmp /= vSingle;         // " << vTmp;
    vTmp /= vSingle;
    ostr << " /= " << vSingle<< " == " << vTmp << endcl;
    ostr << "flt /= (Single)vTmp;      // " << flt;
    flt /= (Single)vTmp;
    ostr << " /= " << vTmp << " == " << flt << endcl;
    ostr << "vTmp /= (Integer)7;        // " << vTmp;
    vTmp /= (Integer)7;
    ostr << " /= " << (Integer)7 << " == " << vTmp << endcl;
    
    vTmp = vLong % vInteger;
    ostr << "vTmp = vLong % vInteger; // " 
         << vLong << " % " << vInteger << " == " << vTmp << endcl;
    ostr << "vTmp %= vInteger;        // " << vTmp;
    vTmp %= vInteger;
    ostr << " %= " << vInteger << " == " << vTmp << endcl;
    
    ostr << endcl << "Testing logical operators:" << endcl;
    vDouble = vLong.CopyAs(VT_R8);

    Boolean f;
    f = (vDouble == vLong);
    ostr << "f = (vDouble == vLong);  // (" 
         << vDouble << " == " << vLong << ") == " << f << endcl;
    f = (vInteger == vLong);
    ostr << "f = (vInteger == vLong); // (" 
         << vInteger << " == " << vLong << ") == " << f << endcl;
    f = (vInteger != vLong);
    ostr << "f = (vInteger != vLong); // (" 
         << vInteger << " != " << vLong << ") == " << f << endcl;
    f = (vInteger <= vLong);
    ostr << "f = (vInteger <= vLong); // (" 
         << vInteger << " <= " << vLong << ") == " << f << endcl;
    f = (vInteger < vLong);
    ostr << "f = (vInteger < vLong);  // (" 
         << vInteger << " < " << vLong << ") == " << f << endcl;
    f = (vInteger > vLong);
    ostr << "f = (vInteger > vLong);  // (" 
         << vInteger << " > " << vLong << ") == " << f << endcl;
    f = (vInteger >= vLong);
    ostr << "f = (vInteger >= vLong); // (" 
         << vInteger << " >= " << vLong << ") == " << f << endcl;
    vTmp = vDate;
    vTmp.Type(VT_BSTR);
    f = (vTmp == vDate);
    ostr << "f = (vTmp == vDate);     // (" 
         << vTmp << " == " << vDate << ") == " << f << endcl;
    f = (vDate == vTmp);
    ostr << "f = (vDate == vTmp);     // (" 
         << vTmp << " == " << vDate << ") == " << f << endcl;
    f = (vTmp > vString);
    ostr << "f = (vTmp == vString);   // (" 
         << vTmp << " == " << vString << ") == " << f << endcl;
    f = (vTmp != vString);
    ostr << "f = (vTmp != vString);   // (" 
         << vTmp << " != " << vString << ") == " << f << endcl;

    ostr << ends;
    char * pch = ostr.str();
    vRet = pch;    
    // Since we grabbed the pointer, we must delete it
    delete[] pch;

    *pvInOut = _W("...back to you");
    *pvOut = _W("I'm out of here");
	return vRet;
  
  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  } 
}

Variant DLLAPI TestSA(SAFEARRAY ** ppsaiInOut, SAFEARRAY ** ppsasOut)
{
  try {

    /* TestSA deals with three arrays:
       
       - It receives a 2-D array of Integers (ppsaiInOut2), which
         it modifies and returns in the same parameter. 

       - It creates a 1-D array of Integers (psaiNew), which it 
         initializes and returns through a Variant return value. 

       - It creates a 1-D array of Strings (psasNew), which it 
         initializes and returns through an out parameter (ppsasOut).
    */

    HRESULT hres;
    int i;

    //@B Create
    // Create a new 1-D array of Integers
    SAFEARRAY * psaiNew; 
    SAFEARRAYBOUND aDim[1]; 
    aDim[0].lLbound = 1; 
    aDim[0].cElements = 8; 
    // Equivalent to: Dim aiNew(1 To 8) As Integer
    psaiNew = SafeArrayCreate(VT_I2, 1, aDim);
    if (psaiNew == NULL) throw ERROR_NOT_ENOUGH_MEMORY;
    //@E Create

    //@B Lock
    // Initialize Integer array to squares of index
    if (hres = SafeArrayLock(psaiNew)) throw hres;
    int iCur = aDim[0].lLbound;
    // Keep separate C++ index (i) and Basic index (iCur)
    for (i = 0; i < (int)aDim[0].cElements; i++, iCur++) {
        // Equivalent to: ai(iCur) = iCur * iCur
        ((Integer*)psaiNew->pvData)[i] = iCur * iCur;
    }
    if (hres = SafeArrayUnlock(psaiNew)) throw hres;
    //@E Lock

    // Create a new 1-D array of strings
    SAFEARRAY * psasNew; 
    aDim[0].lLbound = 3; 
    aDim[0].cElements = 6; 
    // Equivalent to: Dim asNew(3 To 9) As String
    psasNew = SafeArrayCreate(VT_BSTR, 1, aDim);
    if (psasNew == NULL) throw E_OUTOFMEMORY;

    // Initialize BSTR array
    WCHAR wsz[] = L"Fan";
    if (hres = SafeArrayLock(psasNew)) throw hres;
    for (i = 0; i < (int)aDim[0].cElements; i++) {
        wsz[0] = L'F' + (WCHAR)i;
        // Equivalent to: ai(iCur) = string
        ((BSTR *)psasNew->pvData)[i] = SysAllocString(wsz);
    }
    if (hres = SafeArrayUnlock(psasNew)) throw hres;

    // Analyze input array psaiInOut
    SAFEARRAY * psaiInOut = *ppsaiInOut; // Dereference for performance
    //@B GetInfo1
    long cDim = SafeArrayGetDim(psaiInOut); 
    long cbElem = SafeArrayGetElemsize(psaiInOut); 
    //@E GetInfo1

    // Get dimension bounds of input array
    //@B GetInfo2
    SAFEARRAYBOUND * aDims = new SAFEARRAYBOUND[cDim];
    long iT;
    for (i = 0; i < cDim; i++) {
        hres = SafeArrayGetLBound(psaiInOut, i + 1, &aDims[i].lLbound);
        if (hres) throw hres; 
        if (hres = SafeArrayGetUBound(psaiInOut, i + 1, &iT)) throw hres;
        // Calculate elements from upper and lower bound
        aDims[i].cElements = iT - aDims[i].lLbound + 1;
    }
    //@E GetInfo2

    //@B Redim
    // Double the size of the last dimension
    i = cDim - 1;
    aDims[i].cElements *= 2;
    if (hres = SafeArrayRedim(psaiInOut, &aDims[i])) throw hres;
    //@E Redim

    long x, xMin, xMax, y, yMin, yMax;
    //@B GetPut
    // Modify 2-D array with SafeArrayGetElement and SafeArrayGetElement 
    long ai[2];
    Integer iVal;
    xMin = aDims[0].lLbound;
    xMax = xMin + (int)aDims[0].cElements - 1;
    yMin = aDims[1].lLbound; 
    yMax = yMin + (int)aDims[1].cElements - 1;
    for (x = xMin; x <= xMax; x++) {
        ai[0] = x;
        for (y = yMin; y <= yMax; y++) {
            ai[1] = y;
            if (hres = SafeArrayGetElement(psaiInOut, ai, &iVal)) throw hres;
            // Equivalent to: aiInOut(x, y) = aiInOut(x, y) + 1
            iVal++;
            if (hres = SafeArrayPutElement(psaiInOut, ai, &iVal)) throw hres;
        }
    }
    //@E GetPut
    
    //@B PtrIndex
    // Lock 2-D array and modify
    xMin = aDims[0].lLbound; 
    xMax = xMin + (int)aDims[0].cElements - 1;
    yMin = aDims[1].lLbound; 
    yMax = yMin + (int)aDims[1].cElements - 1;
    // Set up dimension array and pointer to receive value
    Integer * piInOut;
    if (hres = SafeArrayLock(psaiInOut)) throw hres; 
    for (x = xMin; x <= xMax; x++) {
        ai[0] = x;
        for (y = yMin; y <= yMax; y++) {
            ai[1] = y;
            hres = SafeArrayPtrOfIndex(psaiInOut, ai, (void **)&piInOut);
            if (hres) throw hres;
            // Equivalent to: aiInOut(x, y) = aiInOut(x, y) + 1
            (*piInOut)++;
        }
    }
    if (hres = SafeArrayUnlock(psaiInOut)) throw hres;
    //@E PtrIndex

    //@B UglyCast
    // Set up dimension array and pointer to receive value
    if (hres = SafeArrayLock(psaiInOut)) throw hres; 
    Integer (*aiInOut)[4] = (Integer(*)[4])psaiInOut->pvData;
    for (x = 0; x < (int)aDims[0].cElements; x++) {
        for (y = 0; y < (int)aDims[1].cElements; y++) {
            // Equivalent to: aiInOut(x, y) = aiInOut(x, y) + 1
            // Switch x and y order for Basic storage order 
            aiInOut[y][x]++;
        }
    }
    if (hres = SafeArrayUnlock(psaiInOut)) throw hres;
    //@E UglyCast

    delete[] aDims;

    // Return through out parameter
    *ppsasOut = psasNew;

    //@B Copy
    // Copy from psaiNew to psaiRet
    SAFEARRAY * psaiRet; 
    if (hres = SafeArrayCopy(psaiNew, &psaiRet)) throw hres;
    //@E Copy

    // Destroy unneeded copy
    //@B Destroy
    if (hres = SafeArrayDestroy(psaiNew)) throw hres;
    //@E Destroy

    // Put copy into variant for return
    Variant vRet = psaiRet;
    // *ppsaiInOut = psaiRet;

    return vRet;

  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  } 
}

Variant DLLAPI TestSafeArray(ArrayInteger & aiInOut, 
                             ArrayString & asOut)
{
  try {

	Integer iVal;
    Long i, iMid;

    //@B GetSet
    iMid = aiInOut.LBound() + (aiInOut.Elements() / 2);
    // Get middle value of array
	iVal = aiInOut.Get(iMid);
    // Double it
    iVal *= 2; 
    // Put modified version back 
	aiInOut.Set(iVal, iMid);
    //@E GetSet

    //@B CppIndex
    // Square each value, C++ style
	aiInOut.Lock();
	for (i = 0; i < aiInOut.Elements(); i++) {
		aiInOut[i] *= aiInOut[i];
	}
	aiInOut.Unlock();
    //@E CppIndex
	
    //@B BasIndex
    // Divide each by two, Basic style
	aiInOut.Lock();
	for (i = aiInOut.LBound(); i <= aiInOut.UBound(); i++) {
		aiInOut(i) /= 2;
	}
	aiInOut.Unlock();
    //@E BasIndex

    //@B CopyArray
    // Copy an array
    ArrayInteger aiCopy = aiInOut;
    //@E CopyArray

    //@B ReDimIt
    // Redimension to throw away last element
    if (aiInOut.IsSizable()) {
        aiInOut.ReDim(Dim(aiInOut.LBound(), aiInOut.UBound() - 1)); 
    }
    //@E ReDimIt

    //@B AssignArray
    aiCopy = aiInOut;
    //@E AssignArray

    //@B ArrayString
    // Create array of strings
    ArrayString as = Dim(4, 9);
    String s = _W("Fan");
	for (i = as.LBound(); i <= as.UBound(); i++) {
        s[0] = L'F' + (WCHAR)i;
		as(i) = s;
	}
    // Return it through out parameter
    asOut = as;
    //@E ArrayString

    //@B ArrayDouble
    // Create array of doubles
    ArrayDouble adbl = Dim(-5, 5);
	for (i = adbl.LBound(); i <= adbl.UBound(); i++) {
		adbl(i) = i * 3.1416;
	}

    // Return through Variant return value
    Variant vRet = (Variant)adbl;
    return vRet;
    //@E ArrayDouble

    // Some illegal operations - uncomment and move up to test
    /*
    aiInOut[40] = 1;
    as(0) = s;
	iVal = aiInOut.Get(13);
	aiInOut.Set(iVal, -2);
    */

  } catch(Long e) {
    ErrorHandler(e);
    return BNULL;
  } 
}

//@B AddEmUp
double DLLAPI AddEmUp(ParamArray & avParams)
{
  try {
	double dblRet = 0;
    // Loop through the array, retrieving parameters
    avParams.Lock();
    for (long i = 0; i < avParams.Elements(); i++) {
        // Ignore missing ones
        if (!avParams[i].IsMissing()) {
			dblRet += (double)avParams[i];
		}
	}
    avParams.Unlock();
	return dblRet;
  } catch(Long e) {
    ErrorHandler(e);
    return 0.0;
  } 
}
//@E AddEmUp
//


