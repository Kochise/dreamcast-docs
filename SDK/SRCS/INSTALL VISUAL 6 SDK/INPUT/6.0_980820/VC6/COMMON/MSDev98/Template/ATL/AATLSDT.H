#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
[!if=(ProjectType, "EXE")]
class C[!ProjectNameSafe]Module : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
[!if!=(MFCOLE, "1")]
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
[!endif]

	DWORD dwThreadID;
};
extern C[!ProjectNameSafe]Module _Module;
[!else]
extern CComModule _Module;
[!endif]

#include <atlcom.h>
