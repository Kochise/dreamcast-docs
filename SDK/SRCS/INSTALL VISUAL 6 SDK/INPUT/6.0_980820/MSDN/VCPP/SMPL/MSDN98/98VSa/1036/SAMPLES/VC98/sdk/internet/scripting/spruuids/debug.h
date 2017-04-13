//---------------------------------------------------------------------------
// Debug.H
//---------------------------------------------------------------------------
// Contains the various macros and the like which are only useful in DEBUG
// builds.
//---------------------------------------------------------------------------
// (C) Copyright 1995-1997 by Microsoft Corporation. All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// All the things required to handle our ASSERT mechanism
//---------------------------------------------------------------------------
#undef DEBUG
// ;begin_internal
// BUGBUG DisplayAssert is not coded in this release,
// until it is, debug builds do not get these debug functions
// ;end_internal

#ifdef DEBUG

VOID DisplayAssert(LPSTR pszMsg, LPSTR pszAssert, LPSTR pszFile, UINT line);

// *** Include this macro at the top of any source file using *ASSERT*() macros ***
#define SZTHISFILE	static char _szThisFile[] = __FILE__;

// Our versions of the ASSERT and FAIL macros.
#define ASSERT(fTest, szMsg)                                \
    if (!(fTest))                                           \
        {                                                   \
        static char szMsgCode[] = szMsg;                    \
        static char szAssert[] = #fTest;                    \
        DisplayAssert(szMsgCode, szAssert, _szThisFile, __LINE__); \
        }

#define FAIL(szMsg)                                         \
        { static char szMsgCode[] = szMsg;                    \
        DisplayAssert(szMsgCode, "FAIL", _szThisFile, __LINE__); }

#else  // DEBUG

#define SZTHISFILE
#define ASSERT(fTest, err)
#define FAIL(err)

#endif	// DEBUG


//---------------------------------------------------------------------------
// Macro that checks a pointer for validity on input
//---------------------------------------------------------------------------
#ifdef DEBUG
#define CHECK_POINTER(val) if (!(val) || IsBadWritePtr((void *)(val), sizeof(void *))) return E_POINTER
#else  // DEBUG
#define CHECK_POINTER(val)
#endif // DEBUG


//---------------------------------------------------------------------------
// Track signatures on objects for debugging
//---------------------------------------------------------------------------
#ifdef DEBUG

#define SIG_destroyed 'XxXx'
#define DECLARE_SIGNATURE(x)    DWORD __sig
#define CHECK_SIGNATURE(x)      ASSERT(this->__sig == (x), "Bad signature")
#define INIT_SIGNATURE(x)       this->__sig = (x)
#define DESTROY_SIGNATURE(x)    this->__sig = SIG_destroyed

#else // DEBUG

#define DECLARE_SIGNATURE(x)
#define CHECK_SIGNATURE(x)
#define INIT_SIGNATURE(x)
#define DESTROY_SIGNATURE(x)

#endif // DEBUG

//--- EOF -------------------------------------------------------------------
