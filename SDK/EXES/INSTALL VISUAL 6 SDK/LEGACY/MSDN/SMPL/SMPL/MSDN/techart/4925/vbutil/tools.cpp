// TOOLS.Cpp - Example DLL for Visual Basic applications.

#include "VBUtil.H"
#include "OleType.H"
#include "Tools.H"

// Check for file existence
//@B ExistFile
Boolean DLLAPI ExistFile(LPCSTR szFile)
{                  
	return ((szFile == NULL) ? FALSE : !_access(szFile, 0));
}
//@E ExistFile

// Return Basic pointer to thing passed by reference
// Declare Function GetRefPtr LIB "VBUTIL*" (lpVoid As Any) As Long
Long DLLAPI GetRefPtr( LPVOID lpVoid )
{
    return (Long)lpVoid;
}


// Extract Word's most significant Byte
Integer DLLAPI HiByte(Integer w)
{
   return w >> 8;
}

// Extract Word's least significant Byte
Integer DLLAPI LoByte(Integer w)
{
   return w & 0x00FF;
}

// Combine two Bytes into a Word
Integer DLLAPI MakeWord(Integer bHi, Integer bLo)
{
   return (bHi << 8) | (bLo & 0x00FF);
}

// Shift bits of Word right
Integer DLLAPI RShiftWord(Integer w, Integer c)
{
   return w >> c;
}

// Shift bits of Word left
Integer DLLAPI LShiftWord(Integer w, Integer c)
{
   return w << c;
}

// Extract DWord's most significant Integer
Integer DLLAPI HiWord(Long dw)
{
   return Integer(dw >> 16);
}

// Extract DWord's least significant Word
Integer DLLAPI LoWord(Long dw)
{
   return (Integer)(dw & 0x0000FFFFL);
}

// Combines two Words into DWord
//@B MakeDWord
Long DLLAPI MakeDWord(Long wHi, Long wLo)
{
   return (wHi << 16) | (wLo & 0x0000FFFFL);
}
//@E MakeDWord

// Shift bits of DWord right
Long DLLAPI RShiftDWord(Long dw, Long c)
{
   return dw >> c;
}

// Shift bits of DWord left
Long DLLAPI LShiftDWord(Long dw, Long c)
{
    return dw << c;
}

// Search backward for one string in another
//@B InStrR
Long DLLAPI InStrR(Variant vStart, Variant vTarget, 
                   Variant vFind, Variant vCompare) 
{
  try {

    Long iStart = -1, afCompare = ffReverse;
    String sTarget, sFind;

    // Assign strings depending on whether vStart is given
    if (vStart.Type() == VT_BSTR) {
        if (!vFind.IsMissing()) {
            afCompare |= ((Long)vFind ? ffIgnoreCase : 0);
        }
        sTarget = vStart;
        sFind = vTarget;

    } else {
        iStart = vStart;
        if (iStart < 1) throw ERROR_INVALID_PARAMETER;
        if (!vCompare.IsMissing()) {
            afCompare |= ((Long)vCompare ? ffIgnoreCase : 0);
        }
        sTarget = vTarget;
        sFind = vFind;
    }
    // Find the string
    return sTarget.Find(sFind, afCompare, iStart);

  } catch(Long e) {
    ErrorHandler(e);
    return 0;
  }
}
//@E InStrR
//
