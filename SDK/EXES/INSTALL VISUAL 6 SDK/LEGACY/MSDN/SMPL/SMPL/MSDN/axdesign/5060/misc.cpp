//=--------------------------------------------------------------------------=
// Misc.Cpp
//=--------------------------------------------------------------------------=
// various utility routines.
//
// marcwan, 1.96
//
#include "IPServer.H"

#include "Globals.H"
#include "Misc.H"
#include "Resource.H"
#include "Util.H"

#include <windowsx.h>

// for ASSERT and FAIL
//
SZTHISFILE



//=--------------------------------------------------------------------------=
// MiscCopyHeapStr
//=--------------------------------------------------------------------------=
// copys a HeapAlloced string
//
// Parameters:
//    LPSTR *        - [out] the copy
//    LPSTR          - [in]  the original
//
// Output:
//    BOOL           - FALSE means OOM
//
// Notes:
//
BOOL MiscCopyHeapStr
(
    LPSTR *ppsz,
    LPSTR  psz
)
{
    // if we have an input string, copy it over
    //
    if (psz) {
        *ppsz = (LPSTR)HeapAlloc(g_hHeap, 0, lstrlen(psz) + 1);
        if (!*ppsz) return FALSE;
        lstrcpy(*ppsz, psz);
    } else
        // just null it out
        //
        *ppsz = NULL;

    return TRUE;
}


//=--------------------------------------------------------------------------=
// Error
//=--------------------------------------------------------------------------=
// shows an error given two resource ids.  can be changed to support help
// contextids as well.
//
// Parameters:
//    HWND         - [in] hwnd to operate off
//    WORD         - [in] main text of message id
//    WORD         - [in] title id
//    DWORD        - [in] helpcontextid
//
// Notes:
//
void Error
(
    HWND  hwnd,
    WORD  wText,
    WORD  wTitle,
    DWORD dwHelpContextID
)
{
    // we've got code that'll already go ahead and do this ...
    //
    ResourceMessageBox(hwnd, wText, wTitle, MB_OK);
}

//=--------------------------------------------------------------------------=
// ErrorReplace
//=--------------------------------------------------------------------------=
// throws an error, but does text replacement first.
//
// Parameters:
//    HWND                  - [in] parent hwnd
//    WORD                  - [in] text string [must have a | in it]
//    WORD                  - [in] caption
//    LPSTR                 - [in] text to use for replacing
//    DWORD                 - [in] helpcontextid
//
// Output:
//    int                   - as for MessageBox() api.
//
// Notes:
//
void ErrorReplace
(
    HWND  hwndParent,
    WORD  wText,
    WORD  wCaption,
    LPSTR pszReplace,
    DWORD dwHelpContextID
)
{
    // we've got code that already does this!
    //
    ResourceMessageBoxReplace(hwndParent, wText, wCaption, pszReplace, MB_OK);
}

//=--------------------------------------------------------------------------=
// ErrorFromHresult
//=--------------------------------------------------------------------------=
// given an HRESULT, return a WORD error for it.
//
// Parameters:
//    HRESULT           - [in]  find my error id
//    WORD              - [in]  default if we couldn't find it
//
// Output:
//    WORD              - resource id error
//
// Notes:
//
WORD ErrorFromHresult
(
    HRESULT hr,
    WORD    wDefault
)
{
    // if it's already a word error, just return it!
    //
    if (HRESULT_FACILITY(hr) == FACILITY_CONTROL) return SCODE_CODE(hr);

    // try standard ones we know about.
    //
    switch (hr) {
        case E_OUTOFMEMORY:
            return IDS_ERR_OUTOFMEMORY;
    }

    // couldn't find it -- just return user's default
    //
    return wDefault;
}


// ResourceMessageBox
//=--------------------------------------------------------------------------=
// same as messagebox, but takes resource ids instead
//
// Parametesr:
//    HWND        - [in] parent
//    WORD        - [in] text
//    WORD        - [in] caption
//    UINT        - [in] messagebox flags
//
// Output:
//    int         - as per messagebox
//
// Notes:
//
int ResourceMessageBox
(
    HWND hwnd,
    WORD idText,
    WORD idTitle,
    UINT flags
)
{
    char szTmp1[256], szTmp2[256];

    // load in the two strings.  we're going to be pretty cavalier here and
    // skip on errors
    //
    LoadString(GetResourceHandle(), idText, szTmp1, sizeof(szTmp1));
    LoadString(GetResourceHandle(), idTitle, szTmp2, sizeof(szTmp2));

    return MessageBox(hwnd, szTmp1, szTmp2, flags);
}

//=--------------------------------------------------------------------------=
// ResourceMessageBoxReplace
//=--------------------------------------------------------------------------=
// shows a message box, but replaces all instances of | in a string with the
// string given as input.
//
// Parameters:
//    HWND                  - [in] parent hwnd
//    WORD                  - [in] text string [must have a | in it]
//    WORD                  - [in] caption
//    LPSTR                 - [in] text to use for replacing
//    DWORD                 - [in] helpcontextid
//
// Output:
//    int                   - as for MessageBox() api.
//
// Notes:
//
int ResourceMessageBoxReplace
(
    HWND  hwndParent,
    WORD  wText,
    WORD  wCaption,
    LPSTR pszReplace,
    UINT  flags
)
{
    LPSTR psz;
    char szText[384], szCaption[256];
    long l;

    // load in the text
    //
    LoadString(GetResourceHandle(), wText, szText, sizeof(szText));

    // now, look for the |.
    //
    psz = szText;
    while (!IsDBCSLeadByte(*psz) && *psz != '|')
        psz = CharNext(psz);

    ASSERT(*psz == '|', "D'oh! this resource doesn't have a | in it!!!");

    // got the location to replace things at.  copy out the rest of the string
    // [we'll use szCaption as a temp buffer]
    //
    lstrcpyn(szCaption, psz + 1, sizeof(szCaption));

    // copy over the replace string
    //
    *psz = '\0';
    lstrcpyn(psz, pszReplace, sizeof(szText) - lstrlen(szText));

    // finally, re-add the rest of the original message
    //
    l = lstrlen(szText);
    psz = szText + l;
    lstrcpyn(psz, szCaption, sizeof(szText) - l);

    // that's it for the text.  load in the caption
    //
    LoadString(GetResourceHandle(), wCaption, szCaption, sizeof(szCaption));

    return MessageBox(hwndParent, szText, szCaption, flags);
}

//=--------------------------------------------------------------------------=
// MiscReplaceHeapString
//=--------------------------------------------------------------------------=
// this little helper takes a string and a pointer to a string.  if the string
// and what the pointer to the string point at are different, it replaces
// the pointer to a string's value with the changed one. all this is done
// using Heap* apis.
//
// Parameters:
//    LPSTR *        - [in/out] compare to and replace if necessary
//    LPSTR          - [in]     compare to
//    int            - [in]     length of the second string
//
// Output:
//    BOOL           - true means we changed, false means we didn't
//
// Notes:
//    - to communicate out of memory, *ppszReplaceMe is left null
//
BOOL MiscReplaceHeapString
(
    LPSTR *ppszReplaceMe,
    LPSTR  pszCompareMe,
    int    iLen
)
{
    // if we don't have an output string or they're different, we have work
    // to do.
    //
    if (!*ppszReplaceMe || lstrcmpi(pszCompareMe, *ppszReplaceMe)) {

        if (*ppszReplaceMe) HeapFree(g_hHeap, 0, *ppszReplaceMe);

        // we don't want to copy a "" string ...
        //
        if (iLen) {
            *ppszReplaceMe = (LPSTR)HeapAlloc(g_hHeap, 0, iLen + 1);
            if (!*ppszReplaceMe) goto OutOfMemory;
            lstrcpy(*ppszReplaceMe, pszCompareMe);
        } else
            *ppszReplaceMe = NULL;

        return TRUE;
    }
    
    // no change
    //
    return FALSE;

  OutOfMemory:
    *ppszReplaceMe = NULL;
    return FALSE;
}

//=--------------------------------------------------------------------------=
// MiscLoadProperty
//=--------------------------------------------------------------------------=
// loads in a property given an istream.  doing a read for each property isn't
// overwhelmingly speedy, but this isn't a performance critical situation, and
// this will do more than well enough ..
//
// Parameters:
//    IStream *            - [in]     stream to write to
//    LPBYTE               - [in/out] where the data goes -- might put a buffer
//    int                  - [in]     size we're going to write
//    VARTYPE              - [in]     what's the type we're loading.
//
// Output:
//    HRESULT
//
// Notes:
//    - properties that are BSTRs are always saved out as ansi, in fact, and
//      are thus just loaded back into HeapAlloced ANSI strs ...
//
HRESULT MiscLoadProperty
(
    IStream *pStream,
    LPBYTE   pData,
    int      iSize,
    VARTYPE  vt
)
{
    HRESULT hr;
    LPSTR   psz;
    long    l;

    ASSERT(pData, "Dive! Dive!  bad pointer");

    // if it's not a string, then we just need to load in the data.
    //
    if (vt != VT_BSTR) {
        return pStream->Read(pData, iSize, NULL);
    }

    // otherwise, it's a string, so we have to first load in a length prefix,
    // and then get the string itself.
    //
    hr = pStream->Read(&l, sizeof(l), NULL);
    RETURN_ON_FAILURE(hr);

    // get a buffer that's big enough
    //
    psz = (LPSTR)HeapAlloc(g_hHeap, 0, l);
    RETURN_ON_NULLALLOC(psz);

    // got it.  load the string in to it.
    //
    hr = pStream->Read(psz, l, NULL);
    if (FAILED(hr)) {
        HeapFree(g_hHeap, 0, psz);
        return hr;
    }

    // copy it over and we're done. don't ,however, copy over "".  just
    // replace it with NULL
    //
    if (*psz)
        *((LPSTR *)pData) = psz;
    else {
        *((LPSTR *)pData) = NULL;
        HeapFree(g_hHeap, 0, psz);
    }

    return S_OK;
}

//=--------------------------------------------------------------------------=
// MiscSaveProperty
//=--------------------------------------------------------------------------=
// saves out an individual property to a binary stream.  we can do lots of
// stream operations here since we really don't care tootoo much about
// performance [ide situations only ...]
//
// Parameters:
//    IStream *            - [in]     stream to write to
//    LPBYTE               - [in]     where the data goes -- might put a buffer
//    int                  - [in]     size we're going to write
//    VARTYPE              - [in]     what's the type we're loading.
//
// Output:
//    HRESULT
//
// Notes:
//    - properties that are BSTRs are always saved out as ansi
//
HRESULT MiscSaveProperty
(
    IStream *pStream,
    LPBYTE   pData,
    int      iSize,
    VARTYPE  vt
)
{
    HRESULT hr;
    LPSTR   psz;
    long    l;

    ASSERT(pData, "Maggots!  This shouldn't happen");

    // for things that aren't strings, this is fantastically trivial.
    //
    if (vt != VT_BSTR)
        return pStream->Write(pData, iSize, NULL);

    // otherwise we need to write out a length prefix first ...
    //
    psz = (*((LPSTR *)pData)) ? *((LPSTR *)pData) : "";

    l = lstrlen(psz) + 1;
    hr = pStream->Write(&l, sizeof(l), NULL);
    RETURN_ON_FAILURE(hr);

    // save out the string
    //
    return pStream->Write(psz, l, NULL);
}

//=--------------------------------------------------------------------------=
// MiscGetWideHeapStr
//=--------------------------------------------------------------------------=
// given an ANSI string, get a wide heap string for it.
//
// Parameters:
//    LPWSTR *            - [out] wide heap string
//    LPSTR               - [in]  string to convert
//
// Output:
//    BOOL                - false is oom
//
// Notes:
//
BOOL MiscGetWideHeapStr
(
    LPWSTR *ppwsz,
    LPSTR   psz
)
{
    long l;

    // first figure out the length
    //
    l = MultiByteToWideChar(CP_ACP, 0, psz, -1, 0, 0);

    // allocate the new string
    //
    *ppwsz = (LPWSTR)HeapAlloc(g_hHeap, 0, sizeof(WCHAR) * l);
    if (!*ppwsz) return FALSE;

    // convert it!
    //
    MultiByteToWideChar(CP_ACP, 0, psz, -1, *ppwsz, l);
    return TRUE;
}

//=--------------------------------------------------------------------------=
// MiscGetAnsiHeapStr
//=--------------------------------------------------------------------------=
// given a wide string, return a heapalloc'd ansi string for it.
//
// Parameters:
//    LPSTR *        - [out]
//    LPWSTR
//
// Output:
//    BOOL           - false means oom
//
// Notes:
//
BOOL MiscGetAnsiHeapStr
(
    LPSTR *ppsz,
    LPWSTR pwsz
)
{
    long l;

    // first figure out the length
    //
    l = WideCharToMultiByte(CP_ACP, 0, pwsz, -1, 0, 0, NULL, NULL);

    // allocate a new string
    //
    *ppsz = (LPSTR)HeapAlloc(g_hHeap, 0, sizeof(char) * l);
    if (!*ppsz) return FALSE;

    // convert it!
    //
    WideCharToMultiByte(CP_ACP, 0, pwsz, -1, *ppsz, l, NULL, NULL);
    return TRUE;
}

