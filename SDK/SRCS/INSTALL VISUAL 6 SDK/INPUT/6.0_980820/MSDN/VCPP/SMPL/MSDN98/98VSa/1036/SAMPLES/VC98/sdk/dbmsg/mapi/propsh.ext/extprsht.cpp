///////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      EXTPRSHT.CPP 
//
//  Description
//      Implementation of MyExchExt and MyExchExtPropertySheets along
//      with helper functions towards the end.
//
//      IExchExt interface methods:
//          MyExchExt::QueryInterface()
//          MyExchExt::AddRef()
//          MyExchExt::Release()
//
//          MyExchExt::Install()
//
//      IExchExtPropertySheets interface methods:
//          IExchExtPropertySheets::QueryInterface()
//          IExchExtPropertySheets::AddRef()
//          IExchExtPropertySheets::Release()
//
//          IExchExtPropertySheets::GetMaxPageCount()
//          IExchExtPropertySheets::GetPages()
//          IExchExtPropertySheets::FreePages()
//
//  Author
//      Gary Peluso
//
//  Revision: 1.01
//
//  History
//  9/21/95 - changed QI for MyExchExtPropertySheets to return pointer to MyExchExt 
//            when IID_IUNKNOWN is requested
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//
#define INITGUID
#define USES_IID_IExchExt
#define USES_IID_IExchExtAdvancedCriteria
#define USES_IID_IExchExtAttachedFileEvents
#define USES_IID_IExchExtCommands
#define USES_IID_IExchExtMessageEvents
#define USES_IID_IExchExtPropertySheets
#define USES_IID_IExchExtSessionEvents
#define USES_IID_IExchExtUserEvents
#define USES_IID_IMAPIFolder
#define USES_IID_IMAPIFormInfo
#define USES_PS_PUBLIC_STRINGS

#include "EXTPRSHT.H"

#include <INITGUID.H>
#include <MAPIGUID.H>

///////////////////////////////////////////////////////////////////////////////
//  tag enumeration definitions and arrays
//
// 
 enum { MESSAGE_CLASS, OBJECT_TYPE, OBJPROPTAGS };

static const SizedSPropTagArray(OBJPROPTAGS,  ObjPropTags) =
      { OBJPROPTAGS, 
        { 
         PR_MESSAGE_CLASS,
         PR_OBJECT_TYPE,        
        } 
      };

 enum { LASTEDIT, MORETAGS };

static const SizedSPropTagArray(MORETAGS,  MoreObjTags) =
      { MORETAGS, 
        { 
         PR_LAST_MODIFICATION_TIME,
        } 
      };



///////////////////////////////////////////////////////////////////////////////
//    Office Document Named Properties
//

enum { KEYWORDS = 0, COMMENTS, AUTHOR, COMPANY, 
       APPNAME, CATEGORY, TITLE, DOCSUBJECT, 
       NAMEIDS // number of properties
};

LPWSTR awszDocProperties[] = { L"Keywords", L"Comments", L"Author", L"Company", 
                               L"AppName",  L"Category", L"Title", L"Subject"};


// array of property tags for named properties
SizedSPropTagArray(NAMEIDS, tagaDoc);

// arrays for summary sheet properties  
LPSPropValue pSummaryProps = NULL;
LPSPropValue pMoreDocProps = NULL;

// instance handle of DLL
static HINSTANCE ghInstDLL = NULL;

// flag to prevent reentrancy
BOOL bBusy = FALSE;


///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: DLLMain()
//
//    Purpose
//    Do initilization processesing
//
//    Return Value
//    TRUE - DLL successfully loads and LoadLibrary will succeed.
//    FALSE - will cause an Exchange error message saying it cannot locate
//            the extension DLL.
//
//    Comments
//    We only need to get a copy of the DLL's HINSTANCE.
//
BOOL WINAPI DllMain(
    HINSTANCE  hinstDLL,
    DWORD  fdwReason,   
    LPVOID  lpvReserved) 
{
 if (DLL_PROCESS_ATTACH == fdwReason)
 {
    ghInstDLL = hinstDLL;

 }
 return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: ExchEntryPoint
//
//    Parameters - none
//
//    Purpose
//    The entry point called by Exchange.
//
//    Return Value
//    Pointer to Exchange Extension (IExchExt) interface
//
//    Comments
//    Exchange Client calls this for each context entry.  
//

LPEXCHEXT CALLBACK ExchEntryPoint(void)
{
        
     return new MyExchExt;


}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::MyExchExt()
//
//    Parameters - none
//
//    Purpose
//    Comstructor.  Called during instantiation of MyExchExt object.
//
//

MyExchExt::MyExchExt()
{
  m_cRef = 1; 
  m_context = 0;
  
  m_pExchExtPropertySheets = new MyExchExtPropertySheets(this);

};



///////////////////////////////////////////////////////////////////////////////
//  IExchExt virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtPropertySheets::Release()
//
//    Parameters - none
//
//    Purpose
//    Frees memory when interface is not referenced any more
//
//    Return value
//    reference count of interface
//

STDMETHODIMP_(ULONG) MyExchExt::Release() 
{ 
 ULONG ulCount = --m_cRef;
                         
 if (!ulCount) 
 { 
  tagaDoc.cValues = 0;
  delete this;
 }

return ulCount;

}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Returns a pointer to an interface object that is requested by ID.
//
//    Comments
//    The interfaces are requested everytime a new context is entered.  The 
//    IID_IExchExt* interfaces are ignored if not specified in the Exchange
//    extensions registry.
//
//    If an interface pointer is returned for more than one context, that
//    interface is used by the client for each of those contexts.  Check the
//    current context to verify if it is appropriate to pass back an interface
//    pointer.
//    
//    Return Value - none
//

STDMETHODIMP MyExchExt::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    HRESULT hResult = S_OK;

    *ppvObj = NULL;

    if (( IID_IUnknown == riid) || ( IID_IExchExt == riid) )
    {
        *ppvObj = (LPUNKNOWN)this;
    }
    else if (IID_IExchExtPropertySheets == riid)
    {
        *ppvObj = (LPUNKNOWN) m_pExchExtPropertySheets;
    }
    else
        hResult = E_NOINTERFACE;

    if (NULL != *ppvObj)
        ((LPUNKNOWN)*ppvObj)->AddRef();

    return hResult;
}



///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::Install()
//
//    Parameters
//    peecb     -- pointer to Exchange Extension callback function
//    eecontext -- context code at time of being called.
//
//    Purpose
//    Called once for each new context that is entered.
//
//    Return Value
//    S_OK - the installation succeeded for the context
//    S_FALSE - deny the installation fo the extension for the context
//
STDMETHODIMP MyExchExt::Install(LPEXCHEXTCALLBACK peecb, ULONG eecontext, ULONG ulFlags)
{
    ULONG ulBuildVersion;
    HRESULT hr;

    m_context = eecontext;
       
    // make sure this is the right version 
    peecb->GetVersion(&ulBuildVersion, EECBGV_GETBUILDVERSION);
    if (EECBGV_BUILDVERSION_MAJOR != (ulBuildVersion & 
                                      EECBGV_BUILDVERSION_MAJOR_MASK))
        return S_FALSE;


    switch (eecontext)
    {
     case EECONTEXT_PROPERTYSHEETS:
        hr = S_OK;
        break;

     default:
        hr = S_FALSE;
        break;
    }


    return hr;

}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtPropertySheets virtual member functions implementation
//


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtPropertySheets::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Return interface object upon request
//    
//    Return Value - none
//
//    Comments
//    Currently the Exchange client does not call QueryInterface from any object
//    except for IExchExt.  This is implemented in case features are added to
//    Exchange to require QueryInterface from any object.  Also, as a "rule of
//    OLE COM" this is the proper implementation of QueryInterface.
//

STDMETHODIMP MyExchExtPropertySheets::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{   

    *ppvObj = NULL;
    if (riid == IID_IExchExtPropertySheets)
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }    
    if (riid == IID_IUnknown)
    {
     // return MyExchExt as a rule of OLE COM since MyExchExtPropertySheets
     // was obtained vi MyExchExt::QueryInterface
        *ppvObj = (LPVOID)m_pExchExt;
        m_pExchExt->AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;

}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtPropertySheets::GetMaxPageCount()
//
//    Parameters
//    ulFlags -- a bitmask indicating what type of property sheet is being 
//               displayed
//
//    Purpose
//    Returns the number of property pages which are to be added.
//
//    Return Value - maximum number of custom pages for the property sheet
//
//    Exchange Calls this to know how many PROPSHEETPAGE buffers it needs
//    to allocate.
//

ULONG MyExchExtPropertySheets::GetMaxPageCount(ULONG ulFlags)          
{
 ULONG ulNumExtSheets;

    switch (ulFlags)
    {
     // ignore these objects.
     case EEPS_FOLDER:
     case EEPS_STORE:
     case EEPS_TOOLSOPTIONS:
        ulNumExtSheets = 0;
        break;
         
     case EEPS_MESSAGE:
        ulNumExtSheets = 1;
        break;

     default:
        ulNumExtSheets = 0;
        break;
    }

    return ulNumExtSheets;   // adding one propery page
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtPropertySheets::GetPages()
//
//    Parameters
//    peecb   -- pointer to Exchange callback interface
//    ulFlags -- a bitmask indicating what type of property sheet is being 
//               displayed
//    ppsp    -- output parm pointing to pointer to list of property sheets
//    pcpsp   -- output parm pointing to buffer contaiing number of property
//               sheets actually used.
//
//    Purpose
//    Fills the PROPSHEETPAGE members for the custom property page.
//
//    Return Value
//    S_FALSE - do not add a new page
//    S_OK - use the ppsp information for new pages.
//
//    Comments
//    Exchange calls this method to gather information for any custom
//    property pages to be added to the sheet.  Here we are only adding
//    one.  ppsp may be an array of PROPSHEETPAGE structures to allow you
//    to all multiple property pages.
//

STDMETHODIMP MyExchExtPropertySheets::GetPages(LPEXCHEXTCALLBACK peecb,
                      ULONG ulFlags, LPPROPSHEETPAGE ppsp, ULONG FAR * pcpsp)
{
    HRESULT     hr;
    LPMDB       pMDB = NULL;
    LPMESSAGE   pItem = NULL;

    *pcpsp = 0;

    // Check for reentrancy
    if (bBusy)
    {
        hr = MAPI_E_BUSY;
        ErrorMessageBox(NULL, hr, "GetPages", "The summary sheet is already open");
        return hr;
    }
    
    bBusy = TRUE;

    // Get our message from the caller
    hr = peecb->GetObject(&pMDB, (LPMAPIPROP *)&pItem);
    if (pItem == NULL)
    {
        ErrorMessageBox(NULL, hr, "GetPages", "GetObject failed");
        goto error_return;
    }

    // If the message does not belong to a document class, we don't
    // do anything
    if (!ValidDocObject(pItem))
    {
        // nothing to do, must clear bBusy
        bBusy = FALSE;
        hr = S_OK;
        goto error_return;
    }

    // Retrieve document summary properties from the message
    if (!GetSummarySheetInfo(pItem))
    {
        ErrorMessageBox(NULL, 0, "GetPages", "Could not get summary sheet information");
        hr = E_FAIL;
        goto error_return;
    }

    // fill out members for the property page
    ppsp[0].dwSize = sizeof (PROPSHEETPAGE);
    ppsp[0].dwFlags = PSP_DEFAULT;
    ppsp[0].hInstance = ghInstDLL;
    ppsp[0].pszTemplate = MAKEINTRESOURCE(IDD_SUMMARY);
    ppsp[0].hIcon = NULL;     // not used in this sample
    ppsp[0].pszTitle = NULL;  // not used in this sample
    ppsp[0].pfnDlgProc = (DLGPROC)SummaryPageDlgProc;
    ppsp[0].lParam = 0;     
    ppsp[0].pfnCallback = NULL;
    ppsp[0].pcRefParent = NULL; // not used in this sample

    *pcpsp = 1;
    // DO NOT clear bBusy in this case. It will be cleared evenmtually
    // when the property sheet is dismissed.
    hr = S_OK;

error_return:

    UlRelease(pItem);
    UlRelease(pMDB);

    if (hr)
        bBusy = FALSE;

    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtPropertySheets::FreePages()
//
//    Parameters
//    ppsp -- pointer to a pointer to the first of a list of property pages
//    cpsp -- number of custom property pages in the list
//    ulFlags -- type of property page
//    
//    Purpose
//    Free any memory associated to the property sheet.
//
//    Return Value - none
//
//    Comments
//    No parameters are used in this example but the function is used as
//    a signal that the property sheet is going away and so memory may
//    be freed.
//
                         
VOID MyExchExtPropertySheets::FreePages(LPPROPSHEETPAGE ppsp, ULONG ulFlags, 
                                        ULONG cpsp)          
{
    MAPIFreeBuffer(pSummaryProps);
    pSummaryProps = NULL;

    MAPIFreeBuffer(pMoreDocProps);
    pMoreDocProps = NULL;

    // Clear the reentrancy flag.
    // This must be done here rather than in the dialog proc, because
    // our property page may be dismissed without ever having been 
    // displayed.
    bBusy = FALSE;
}


///////////////////////////////////////////////////////////////////////////////
//  Helper Functions
//

///////////////////////////////////////////////////////////////////////////////
//    ErrorMessageBox()
//
//    Parameters
//    hWnd       -- parent window
//    hr         -- HRESULT value
//    szFunction -- function name in which the error occurred
//    szMessage  -- error message
//
//    Purpose
//    Displays an error message using MessageBox
//
//    Return Value - none
//
//    Comments
//    Pass 0 for hr to not display an error number.  Pass NULL for
//    szFunction to not display a function name.  Use these options
//    to display error messages for public consumption.  Use hr and
//    function name for internal errors and for debugging.  szMessage
//    is mandatory.
//
void ErrorMessageBox(HWND hWnd, HRESULT hr, LPSTR szFunction, LPSTR szMessage)
{
 static char szError[256];

 if (szMessage == NULL)
 {
    MessageBox(hWnd, 
         "An unknown error occured in\nSample property sheet extension",
         "Sample Property Sheet Extension", MB_ICONEXCLAMATION | MB_OK);
    return;
 }

 if ((hr == 0) && (szFunction == NULL))
 {
    MessageBox(hWnd, szMessage, "Sample Extension Error", MB_ICONEXCLAMATION | MB_OK);
    return;
 }


 if (szFunction != NULL) 
 {
  wsprintf(szError, "Error %08X in %s\n%s", hr, szFunction, szMessage);
  MessageBox(hWnd, szError, "Sample Extension Error", MB_ICONEXCLAMATION | MB_OK);
 }

}



///////////////////////////////////////////////////////////////////////////////
//    GetSummarySheetInfo()
//
//    Parameters
//    pMessage -- pointer to an Office Document object, message object of
//                class IPM.Document
//
//    Purpose
//    gathers the summary sheet information from the properties of a message
//
//    Return Value
//    TRUE if everything succeeded
//    FALSE something failed, inform the caller
//
//    Comments
//    The pointers to the buffers are defined in the PRSHTDLG.CPP file and are
//    externally referenced here.
//
//    tagaDoc is a static array of property tags from GetNamedIDs
//    Only need to call this function once when tags are first needed.
//    The buffer for the tags are freed in the Release method of MyExchExt when
//    Exchange is closing down.
//

BOOL GetSummarySheetInfo(LPMESSAGE pMessage)
{
    HRESULT     hr;
    ULONG       ulcValues;
    BOOL        bSuccess;
 
    bSuccess = FALSE;

    if (pMessage == NULL)
    {
        ErrorMessageBox(NULL, 0, "GetSummarySheetInfo", "Null pMessage");
        goto error_return;
    }

    // Retrieve property IDs of the summary properties from the message.
    tagaDoc.cValues = 0;
    if (!GetNamedIDs(pMessage))
    {
        ErrorMessageBox(NULL, 0, "GetSummarySheetInfo", "GetNamedIDs failed");
        goto error_return;
    }        


    hr = pMessage->GetProps((LPSPropTagArray)&tagaDoc, 0, &ulcValues,
        &pSummaryProps);
    if (FAILED(hr))
    {
        ErrorMessageBox(NULL, hr, "GetSummarySheetInfo", "GetProps failed");
        goto error_return;
    }


    // These must be validated in the same order as the named id property tag
    // array. See GetNamedIDs below.

    if (PROP_TYPE(pSummaryProps[KEYWORDS].ulPropTag) == PT_MV_STRING8)
        mvszKeywords = pSummaryProps[KEYWORDS].Value.MVszA;
    else
    {
        char szDefault[] = "No Keywords";
        szDocKeywords = (LPSTR)malloc(lstrlen(szDefault) + 1);
        lstrcpy (szDocKeywords, szDefault);
        mvszKeywords.cValues = 0;
    }


    if (PROP_TYPE(pSummaryProps[COMMENTS].ulPropTag) == PT_STRING8)
        szDocComments = pSummaryProps[COMMENTS].Value.lpszA;
    else
        szDocComments = "No Comments";


    if (PROP_TYPE(pSummaryProps[AUTHOR].ulPropTag) == PT_STRING8)
        szDocAuthor = pSummaryProps[AUTHOR].Value.lpszA;
    else
        szDocAuthor = "No Author";

    if (PROP_TYPE(pSummaryProps[COMPANY].ulPropTag) == PT_STRING8)
        szDocCompany = pSummaryProps[COMPANY].Value.lpszA;
    else
        szDocCompany = "No Company";

    if (PROP_TYPE(pSummaryProps[APPNAME].ulPropTag) == PT_STRING8)
        szDocApplication = pSummaryProps[APPNAME].Value.lpszA;
    else
        szDocApplication = "No Application";

    if (PROP_TYPE(pSummaryProps[CATEGORY].ulPropTag) == PT_STRING8)
        szDocCategory = pSummaryProps[CATEGORY].Value.lpszA;
    else
        szDocCategory = "No Category";

    if (PROP_TYPE(pSummaryProps[TITLE].ulPropTag) == PT_STRING8)
        szDocTitle = pSummaryProps[TITLE].Value.lpszA;
    else
        szDocTitle = "No Title";

    if (PROP_TYPE(pSummaryProps[DOCSUBJECT].ulPropTag) == PT_STRING8)
        szDocSubject = pSummaryProps[DOCSUBJECT].Value.lpszA;
    else
        szDocSubject = "No Subject";

    // Retrieve additional non-named properties
    hr = pMessage->GetProps((LPSPropTagArray)&MoreObjTags, 0, &ulcValues, &pMoreDocProps);
    if (FAILED(hr))
    {
        ErrorMessageBox(NULL, hr, "GetSummarySheetInfo", "GetProps failed");
        goto error_return;
    }

    if (PROP_TYPE(pMoreDocProps[LASTEDIT].ulPropTag) == PT_SYSTIME)
        szDocLastSaved = GetFileTimeString(&(pMoreDocProps[LASTEDIT].Value.ft));
    else
        szDocLastSaved = "No last saved time";

    bSuccess = TRUE;

error_return:

return bSuccess;

}


///////////////////////////////////////////////////////////////////////////////
//    GetNamedIDs()
//
//    Parameters
//    pMessage -- message object of which to call GetIDsFromNames()
//
//    Purpose
//    This function retrieves the property IDs of names from Office Document
//    summary sheet properties.
//
//    Return Value - none
//
//    Comments
//    The name strings used were found imperically because there were no
//    documentation publishing the Office document named properties at the
//    time this sample was implemented.  It is possible to get a list
//    of all public named properties by calling GetNamesFromIDs().
//
//    tagaDoc is a global variable listed at the top of this file.
//
BOOL GetNamedIDs(LPMESSAGE pMessage)
{
    HRESULT         hr;
    LPMAPINAMEID    apMAPINameId[NAMEIDS];
    MAPINAMEID      aMAPINameId[NAMEIDS];
    UINT            i;
    LPSPropTagArray pTags = NULL;
    BOOL            bSucceeded = FALSE;

    if (pMessage == NULL)
    {
        ErrorMessageBox(NULL, 0, "GetNamedIDs", "Null pMessage");
        goto error_return;
    }

    memset(apMAPINameId, 0, NAMEIDS * sizeof(LPMAPINAMEID));
    memset(aMAPINameId, 0, NAMEIDS * sizeof(MAPINAMEID));

    // create an array of property names
    for (i=0; i<NAMEIDS; i++)
    {
        aMAPINameId[i].lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
        aMAPINameId[i].ulKind = MNID_STRING;
        aMAPINameId[i].Kind.lpwstrName = awszDocProperties[i];

        apMAPINameId[i] = &aMAPINameId[i];
    }


    // Get the property IDs for these names from the message.
    // A PT_ERROR tag is returned for any unrecognized names.
    hr = pMessage->GetIDsFromNames(NAMEIDS, apMAPINameId, 0, &pTags);
    if (FAILED(hr))
    {
        ErrorMessageBox(NULL, hr, "GetNamedIDs", "GetIDsFromNames failed");
        goto error_return;
    }


    // Copy the returned property tags to the global array tagaDoc.
    // For the unrecognized properties, substitute a tag that GetProps
    // will ignore.
    for (i=0; i<NAMEIDS; ++i)
    {
        if (PT_ERROR != PROP_TYPE(pTags->aulPropTag[i]))
            tagaDoc.aulPropTag[i] = pTags->aulPropTag[i];
        else
            tagaDoc.aulPropTag[i] = PR_NULL;
    }

    tagaDoc.cValues = NAMEIDS;

    bSucceeded = TRUE;

error_return:

    MAPIFreeBuffer(pTags);
    return bSucceeded;
}


///////////////////////////////////////////////////////////////////////////////
//    ValidDocObject()
//
//    Parameters
//    pObject -- pointer to property object validate
//
//    Purpose
//    Inspects the properties of the object to see if the selected object
//    is a message type object and has the proper class.
//
//    Return Value
//    TRUE if the object is MAPI_MESSAGE and the class is IPM.Document
//    FALSE if either the object is not MAPI_MESSAGE or class is not
//    IPM.Document
//
//    Comments
//    This function is intended to be called from GetPages with an
//    object pointer from GetObject.
//
BOOL ValidDocObject(LPMAPIPROP pObject)
{
    HRESULT         hr;
    ULONG           ulcValues;
    LPSPropValue    pObjectProps = NULL;
    BOOL            bRet;

    bRet = FALSE;   // assume invalid object

    if (!pObject)
    {
        ErrorMessageBox(NULL, 0, "ValidDocObject", "Null pObject");
        return FALSE;
    }

    hr = pObject->GetProps((LPSPropTagArray)&ObjPropTags, 0, &ulcValues, 
        &pObjectProps);
    if (FAILED(hr))
    {
        ErrorMessageBox(NULL, hr, "ValidDocObject", "pObject->GetProps failed");
        goto error_return;
    }

    if ( (pObjectProps[OBJECT_TYPE].Value.l == MAPI_MESSAGE)  &&
         (pObjectProps[MESSAGE_CLASS].ulPropTag == PR_MESSAGE_CLASS) &&
         (strstr(pObjectProps[MESSAGE_CLASS].Value.lpszA, "IPM.Document")) )
        bRet = TRUE;


    // clean up
error_return:

    MAPIFreeBuffer(pObjectProps);
    return bRet;
}

///////////////////////////////////////////////////////////////////////////////
//    GetFileTimeString()
//
//    Parameters
//    pft -- filetime structure pointer
//
//    Purpose
//    convert the given filetime date into a string.
//
//    Return Value
//    pointer to a string buffer containing formatted filed time.
//
//    Comments
//    The filetime is formated into dd/mm/yy hh:mm.  The string buffer
//    is static (not on the stack) because it is referred to outside this
//    function.
//

LPSTR GetFileTimeString(FILETIME * pft)
{
 static char szTimeStringBuff[25];
 FILETIME ftLocal;
 SYSTEMTIME systime;
 WORD wAdjustedHour;
 LPSTR pszAMPM[2] = { "AM", "PM" };
 int nAMPM;

 FileTimeToLocalFileTime(pft, &ftLocal);
 FileTimeToSystemTime(&ftLocal, &systime);
 
 szTimeStringBuff[0] = '\0';
 
// convert from Military time to Civilian time format 
 wAdjustedHour = systime.wHour;

 nAMPM = 1;  // assume PM time
 if ( wAdjustedHour < 12 )
    nAMPM = 0;   // AM time

 if (wAdjustedHour > 12)
 {
    wAdjustedHour-=12;
 }
 
 wsprintf(szTimeStringBuff, "%02d/%02d/%02d %02d:%02d%s", 
            systime.wMonth,
            systime.wDay,
            systime.wYear,
            wAdjustedHour,
            systime.wMinute,
            pszAMPM[nAMPM]);

 return szTimeStringBuff;

}



