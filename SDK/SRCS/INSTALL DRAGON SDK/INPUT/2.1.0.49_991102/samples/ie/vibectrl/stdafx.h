#ifndef STDAFX_H
#define STDAFX_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef STRICT
#define STRICT
#endif //STRICT

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <ocidl.h>	// Added by ClassView


#ifndef MIDL_INTERFACE

#if _MSC_VER >= 1100
#define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)
#else
#define MIDL_INTERFACE(x)   struct
#endif

#endif

#endif // STDAFX_H

