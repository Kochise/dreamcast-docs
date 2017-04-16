#ifndef _TOOLS_H_
#define _TOOLS_H_


Long DLLAPI GetRefPtr(LPVOID lpVoid);

Integer DLLAPI LoByte(Integer w);
Integer DLLAPI HiByte(Integer w);
Integer DLLAPI MakeWord(Integer bHi, Integer bLo);
Integer DLLAPI RShiftWord(Integer w, Integer c);
Integer DLLAPI LShiftWord(Integer w, Integer c);
Integer DLLAPI HiWord(Long dw);
Integer DLLAPI LoWord(Long dw);
Long DLLAPI MakeDWord(Long wHi, Long wLo);
Long DLLAPI RShiftDWord(Long dw, Long c);
Long DLLAPI LShiftDWord(Long dw, Long c);
Boolean DLLAPI ExistFile(LPCSTR lpFileName);
Long DLLAPI InStrR(Variant * pvStart, Variant * pvTarget, 
                   Variant * pvFind, Variant * pvCompare);

#endif // _TOOLS_H_
