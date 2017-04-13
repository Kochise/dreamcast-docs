///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPFOLDER.CPP
//
//  Description
//      This file implements the IMAPIFolder interface with the methods 
//      specified in the MAPI SPI 1.0.
//
//  Authors
//      Irving De la Cruz
//      Les Thaler
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "XPWDSR.H"

// Remark this line to turn verbose tracing OFF
#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)   TraceInfoMessage(a)
#else
#define InfoTrace(a)   
#endif // DO_INFO_TRACES

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CMAPIFolder()
//
//    Parameters
//      pStatusObj      Pointer to parent status object
//      pLogonObj       Pointer to logon session
//
//    Purpose
//      Constructor of the object. Parameters are passed to initialize the
//      data members with the appropiate values.
//
//    Return Value
//      None
//
CMAPIFolder::CMAPIFolder (CMAPIStatus * pStatusObj,
                          CXPLogon *    pLogonObj)
{
    InfoTrace ("CMAPIFolder: Constructor called");
    m_cRef = 1;
    m_pTableData = NULL;
    m_pLogon = pLogonObj;
    m_pLogon->AddRef();
    m_pStatusObj = pStatusObj;
//    m_pStatusObj->AddRef(); the status object holds a reference to us, so
//  addref will result in circular reference.
    m_fNoHeadersFile = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::~CMAPIFolder()
//
//    Parameters
//      None
//
//    Purpose
//      Destructor of CMAPIFolder. Releases memory allocated for internal 
//      properties during the life of this transport logon object.
//
//    Return Value
//      None
//
CMAPIFolder::~CMAPIFolder ()
{
    InfoTrace ("CMAPIFolder: Destructor called");
    if (m_pTableData)
    {
        m_pTableData->Release();
        m_pTableData = NULL;
    }
//    m_pStatusObj->Release(); we didn't addref it in the constructor.
    m_pStatusObj = NULL;
    m_pLogon->Release();
    m_pLogon = NULL;
    m_fNoHeadersFile = FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::QueryInterface()
//
//    Parameters
//      { Refer to OLE Documentation on this method }
//
//    Purpose
//      Returns a pointer to a interface requested if the interface is 
//      supported and implemented by this object. If it is not supported, it
//      returns NULL
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::QueryInterface (REFIID riid, LPVOID * ppvObj)
{
    // OLE requires NULLing parameter
    *ppvObj = NULL;
    // If this is one of the two IID return an interface pointer to it
    if (riid == IID_IMAPIFolder || riid == IID_IMAPIContainer || riid == IID_IMAPIProp)
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    // OLE's COM rules for IUnknown establish that if an interface B
    // was obtained using QueryInterface() on interface A, querying B for
    // its IUnknown IID, should return a pointer to the A interface.
    // Since this IMAPIFolder interface was obtained from IMAPIStatus::QueryInterface,
    // when requested for IUnknown, return the contained pointer to the parent status
    // object
    if (riid == IID_IUnknown)
    {
        *ppvObj = (LPVOID)m_pStatusObj;
        // Increase usage count of this object
        m_pStatusObj->AddRef();
        return S_OK;
    }
    // This object does not support the interface requested
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::Release()
//
//    Parameters
//      None
//
//    Purpose
//      Decrements the usage count of the Folder object.
//
//    Return Value
//      Usage count of this object.
//
STDMETHODIMP_(ULONG) CMAPIFolder::Release()
{
    ULONG ulCount = --m_cRef;
    if (!ulCount)
    {
        delete this;
    }
    // If the count is 1, is only the internal reference kept in the parent
    // status object. This is the time to flush the contents table to
    // the headers file.
    if (1 == ulCount)
    {
        CopyTableToFile();
    }
    return ulCount;
}

///////////////////////////////////////////////////////////////////////////////
// IMAPIProp virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetLastError()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      This function finds a string for the hError passed. The hError is the
//      last error that occurred in one of our methods. Here we call a
//      function to allocate a MAPIERROR structure and passed the information
//      to the caller.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::GetLastError (HRESULT        hError,
                                        ULONG          ulFlags,
                                        LPMAPIERROR *  ppMAPIError)
{
    InfoTrace ("CMAPIFolder::GetLastError method called");
    Validate_IMAPIProp_GetLastError (this, hError, ulFlags, ppMAPIError);

    // Allocate and fill a MAPIERROR structure with the error passed in.
    // Use the common helper function GetMAPIError
    return GetMAPIError (ppMAPIError, ulFlags, hError, m_pLogon->GetInstance());
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SaveChanges()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      We don't implement this. Besides, folder objects are not transacted.
//
//    Return Value
//      S_OK always.
//
STDMETHODIMP CMAPIFolder::SaveChanges (ULONG ulFlags)
{
    InfoTrace ("CMAPIFolder::SaveChanges method called");
    Validate_IMAPIProp_SaveChanges (this, ulFlags);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Gets the properties of the remote message folder container. A client
//      requests the properties it needs by passing an array of property tags
//      in pTags. If the array pointer is NULL, we return ALL the properties
//      we have.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::GetProps (LPSPropTagArray pTags,
                                    ULONG           ulFlags,
                                    ULONG *         pcValues,
                                    LPSPropValue *  ppPropArray)
{
    InfoTrace ("CMAPIFolder::GetProps method called");
    Validate_IMAPIProp_GetProps (this, pTags, ulFlags, pcValues, ppPropArray);

    #ifdef DO_INFO_TRACES
    if (!pTags)
    {
        TraceInfoMessage ("CMAPIFolder::GetProps: All properties requested");
    }
    else
    {
        TraceMessage ("CMAPIFolder::GetProps Properties requested..."); for (ULONG j=0; j<pTags->cValues; j++) { TraceProp (pTags->aulPropTag[j]); }
    }
    #endif // DO_INFO_TRACES

    BOOL fGetAllProps = pTags ? FALSE : TRUE;
    if (!pTags)
    {
        pTags = (LPSPropTagArray)&sptFolderProps;
    }
    *pcValues = pTags->cValues;
    HRESULT hResult = gpfnAllocateBuffer (sizeof(SPropValue)*(*pcValues), (LPVOID *)ppPropArray);
    if (hResult)
    {
        TraceResult ("CMAPIFolder::GetProps: Memory allocation failed", hResult);
        return hResult;
    }
    if (fGetAllProps)
    {
        for (ULONG i=0; i<sptFolderProps.cValues; i++)
        {
            (*ppPropArray)[i].ulPropTag = sptFolderProps.aulPropTag[i];
        }
    }
    else
    {
        // A client of the IMAPIProp::GetProps() method can pass PT_UNSPECIFIED in the
        // tag of a property. Is the provider's responsiblity to return
        // the proper type of the property.
        for (ULONG k=0; k<pTags->cValues; k++)
        {
            for (ULONG i=0; i<sptFolderProps.cValues; i++)
            {
                if (PROP_ID(pTags->aulPropTag[k]) == PROP_ID(sptFolderProps.aulPropTag[i]))
                {
                    (*ppPropArray)[k].ulPropTag = sptFolderProps.aulPropTag[i];
                }
                else
                {
                    (*ppPropArray)[k].ulPropTag = pTags->aulPropTag[k];
                }
            }
        }
    }
    TCHAR szBuffer[64];
    BOOL fGotErrors = FALSE;    
    LPVOID pSrc, pDst;
    ULONG cbSize;
    for (ULONG i=0; i<*pcValues; i++)
    {
        hResult = S_OK;
        switch ((*ppPropArray)[i].ulPropTag)
        {
            case PR_NULL :
                (*ppPropArray)[i].Value.err = S_OK;
                break;
            case PR_CREATION_TIME :
                if (m_fNoHeadersFile)
                {
                    hResult = MAPI_E_NOT_FOUND;
                }
                else
                {
                    (*ppPropArray)[i].Value.ft = m_ftLastUpdate;
                }
                break;
            case PR_CONTENT_COUNT :
                hResult = MAPI_E_NOT_FOUND;
                if (m_pTableData)
                {
                    LPMAPITABLE pTable;
                    if (!m_pTableData->HrGetView (NULL, NULL, 0, &pTable))
                    {
                        if (!pTable->GetRowCount (0, &(*ppPropArray)[i].Value.ul))
                        {
                            hResult = S_OK;
                        }
                        pTable->Release();
                    }
                }
                break;
            case PR_ASSOC_CONTENT_COUNT :
                (*ppPropArray)[i].Value.l = 0;
                break;
            case PR_ACCESS :
                (*ppPropArray)[i].Value.l = MAPI_ACCESS_READ;
                break;
            case PR_ACCESS_LEVEL :
                (*ppPropArray)[i].Value.l = 0;
                break;
            case PR_FOLDER_TYPE :
                (*ppPropArray)[i].Value.l = FOLDER_GENERIC;
                break;
            case PR_OBJECT_TYPE :
                (*ppPropArray)[i].Value.l = MAPI_FOLDER;
                break;
            case PR_DISPLAY_TYPE :
                (*ppPropArray)[i].Value.l = DT_FOLDER;
                break;
            case PR_SUBFOLDERS :
                (*ppPropArray)[i].Value.b = FALSE;
                break;
            case PR_CREATION_VERSION :
                (*ppPropArray)[i].Value.li.LowPart = TRANSPORT_VERSION_MAJOR;
                (*ppPropArray)[i].Value.li.HighPart = TRANSPORT_VERSION_MINOR;
                break;
            case PR_CURRENT_VERSION :
                (*ppPropArray)[i].Value.li.LowPart = TRANSPORT_VERSION_MAJOR;
                (*ppPropArray)[i].Value.li.HighPart = TRANSPORT_VERSION_MINOR;
                break;
            case PR_DISPLAY_NAME :
                szBuffer[0] = 0;
                LoadString (m_pLogon->GetInstance(), IDS_MSG_REMOTE_FOLDER_VIEW_NAME, szBuffer, 64);
                pSrc = (LPVOID)szBuffer;
                break;
            default:
                hResult = MAPI_E_NOT_FOUND;
                #ifdef DO_INFO_TRACES
                TraceRaw ("CMAPIFolder::GetProps: Not Found - "); TraceProp ((*ppPropArray)[i].ulPropTag);
                #endif // #DO_INFO_TRACES
                break;
        }
        if (!hResult && 
            (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_BINARY ||
             PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_TSTRING))
        {
            if (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_TSTRING)
            {
                cbSize = Cbtszsize ((LPTSTR)pSrc);
            }
            hResult = gpfnAllocateMore (cbSize, *ppPropArray, &pDst);
            if (!hResult)
            {
                CopyMemory (pDst, pSrc, cbSize);
                if (PROP_TYPE((*ppPropArray)[i].ulPropTag) == PT_BINARY)
                {
                    (*ppPropArray)[i].Value.bin.cb  = cbSize;
                    (*ppPropArray)[i].Value.bin.lpb = (LPBYTE)pDst;
                }
                else
                {
                    (*ppPropArray)[i].Value.LPSZ = (LPTSTR)pDst;
                }
            }
        }
        if (hResult)
        {
            (*ppPropArray)[i].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID((*ppPropArray)[i].ulPropTag));
            (*ppPropArray)[i].Value.err = hResult;
            fGotErrors = TRUE;
        }
    }
    if (fGotErrors)
    {
        hResult = MAPI_W_ERRORS_RETURNED;
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetPropList()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Returns an array with all the property tags that we support in
//      this folder
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::GetPropList (ULONG ulFlags, LPSPropTagArray * ppTags)
{
    InfoTrace ("CMAPIFolder::GetPropList method called");
    Validate_IMAPIProp_GetPropList (this, ulFlags, ppTags);

    ULONG cbTagsArraySize = CbNewSPropTagArray(NUM_FOLDER_PROPS);
    // Allocate the required amount of memory
    HRESULT hResult = gpfnAllocateBuffer (cbTagsArraySize, (LPVOID *)ppTags);
    TraceResult ("CMAPIFolder::GetPropList: Memory allocation failed", hResult);
    if (!hResult)
    {
        // Copy the contents of our property tag array into the buffer
        CopyMemory (*ppTags, &sptFolderProps, cbTagsArraySize);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::OpenProperty()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::OpenProperty (ULONG       ulPropTag,
                                        LPCIID      piid,
                                        ULONG       ulInterfaceOptions,
                                        ULONG       ulFlags,
                                        LPUNKNOWN * ppUnk)
{
    InfoTrace ("CMAPIFolder::OpenProperty method called");
    Validate_IMAPIProp_OpenProperty (this, ulPropTag,  piid, ulInterfaceOptions, ulFlags, ppUnk);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SetProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::SetProps (ULONG                   cValues,
                                    LPSPropValue            pPropArray,
                                    LPSPropProblemArray *   ppProblems)
{
    InfoTrace ("CMAPIFolder::SetProps method called");
    Validate_IMAPIProp_SetProps (this, cValues, pPropArray, ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::DeleteProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::DeleteProps (LPSPropTagArray       pPropTagArray,
                                       LPSPropProblemArray * ppProblems)
{
    InfoTrace ("CMAPIFolder::DeleteProps method called");
    Validate_IMAPIProp_DeleteProps (this, pPropTagArray, ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CopyTo()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CopyTo (ULONG                 ciidExclude,
                                  LPCIID                rgiidExclude,
                                  LPSPropTagArray       pExcludeProps,
                                  ULONG                 ulUIParam,
                                  LPMAPIPROGRESS        pProgress,
                                  LPCIID                pInterface,
                                  LPVOID                pDestObj,
                                  ULONG                 ulFlags,
                                  LPSPropProblemArray * ppProblems)
{
    InfoTrace ("CMAPIFolder::CopyTo method called");
    Validate_IMAPIProp_CopyTo (this,
                               ciidExclude,
                               rgiidExclude,
                               pExcludeProps,
                               ulUIParam,
                               pProgress,
                               pInterface,
                               pDestObj,
                               ulFlags,
                               ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CopyProps()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CopyProps (LPSPropTagArray        pIncludeProps,
                                     ULONG                  ulUIParam,
                                     LPMAPIPROGRESS         pProgress,
                                     LPCIID                 pInterface,
                                     LPVOID                 pDestObj,
                                     ULONG                  ulFlags,
                                     LPSPropProblemArray *  ppProblems)
{
    InfoTrace ("CMAPIFolder::CopyProps method called");
    Validate_IMAPIProp_CopyProps (this,
                                  pIncludeProps,
                                  ulUIParam,
                                  pProgress,
                                  pInterface,
                                  pDestObj,
                                  ulFlags,
                                  ppProblems);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetNamesFromIDs()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::GetNamesFromIDs (LPSPropTagArray *    ppPropTags,
                                           LPGUID               pPropSetGuid,
                                           ULONG                ulFlags,
                                           ULONG *              pcPropNames,
                                           LPMAPINAMEID **      pppPropNames)
{
    InfoTrace ("CMAPIFolder::GetNamesFromIDs method called");
    Validate_IMAPIProp_GetNamesFromIDs (this,
                                        ppPropTags,
                                        pPropSetGuid,
                                        ulFlags,
                                        pcPropNames,
                                        pppPropNames);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetIDsFromNames()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::GetIDsFromNames (ULONG                cPropNames,
                                           LPMAPINAMEID *       ppPropNames,
                                           ULONG                ulFlags,
                                           LPSPropTagArray *    ppPropTags)
{
    InfoTrace ("CMAPIFolder::GetIDsFromNames method called");
    Validate_IMAPIProp_GetIDsFromNames (this,
                                        cPropNames,
                                        ppPropNames,
                                        ulFlags,
                                        ppPropTags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
// IMAPIContainer virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetContentsTable()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::GetContentsTable (ULONG ulFlags, LPMAPITABLE * ppTable)
{
    InfoTrace ("CMAPIFolder::GetContentsTable method called");
    Validate_IMAPIContainer_GetContentsTable (this, ulFlags, ppTable);

    if (MAPI_ASSOCIATED & ulFlags)
    {
        TraceMessage ("CMAPIFolder::GetContentsTable: We don't have associated messages");
        return MAPI_E_NO_SUPPORT;
    }
    HRESULT hResult;
    // If we don't have an ITableData interface pointer instantiated, create one.
    if (!m_pTableData)
    {
        hResult = CreateTable (&IID_IMAPITableData,
                               gpfnAllocateBuffer,
                               gpfnAllocateMore,
                               gpfnFreeBuffer,
                               NULL,
                               TBLTYPE_DYNAMIC,
                               PR_ENTRYID,
                               (LPSPropTagArray)&sptFldContents,
                               &m_pTableData);
        if (hResult)
        {
            TraceResult ("CMAPIFolder::GetContentsTable: Failed to create an ITableData object", hResult);
            return hResult;
        }

        // Populate the data for the table here
        hResult = FillContentsTable (m_pLogon->GetLocalHeadersCache());
        if (hResult)
        {
            TraceResult ("CMAPIFolder::GetContentsTable: Failed to populate table data", hResult);
            return hResult;
        }
    }
    hResult = m_pTableData->HrGetView (NULL, NULL, 0, ppTable);
    // If any, trace out the error code.
    TraceResult ("CMAPIFolder::GetContentsTable: Failed to create a view of the table data", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetHierarchyTable()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::GetHierarchyTable (ULONG          ulFlags,
                                             LPMAPITABLE *  ppTable)
{
    InfoTrace ("CMAPIFolder::GetHierarchyTable method called");
    Validate_IMAPIContainer_GetHierarchyTable (this, ulFlags, ppTable);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::OpenEntry()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::OpenEntry (ULONG          cbEntryID,
                                     LPENTRYID      pEntryID,
                                     LPCIID         pInterface,
                                     ULONG          ulFlags,
                                     ULONG *        pulObjType,
                                     LPUNKNOWN *    ppUnk)
{
    InfoTrace ("CMAPIFolder::OpenEntry method called");
    Validate_IMAPIContainer_OpenEntry (this,
                                       cbEntryID,
                                       pEntryID,
                                       pInterface,
                                       ulFlags,
                                       pulObjType,
                                       ppUnk);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SetSearchCriteria()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::SetSearchCriteria (LPSRestriction pRestriction,
                                             LPENTRYLIST    pContainerList,
                                             ULONG          ulSearchFlags)
{
    InfoTrace ("CMAPIFolder::SetSearchCriteria method called");
    Validate_IMAPIContainer_SetSearchCriteria (this, pRestriction, pContainerList, ulSearchFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetSearchCriteria()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::GetSearchCriteria (ULONG             ulFlags,
                                             LPSRestriction *  ppRestriction,
                                             LPENTRYLIST *     ppContainerList,
                                             ULONG *           pulSearchState)
{
    InfoTrace ("CMAPIFolder::GetSearchCriteria method called");
    Validate_IMAPIContainer_GetSearchCriteria (this, ulFlags, ppRestriction, ppContainerList, pulSearchState);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
// IMAPIFolder virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CreateMessage()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CreateMessage (LPCIID         pInterface,
                                         ULONG          ulFlags,
                                         LPMESSAGE *    ppMessage)
{
    InfoTrace ("CMAPIFolder::CreateMessage method called");
    Validate_IMAPIFolder_CreateMessage (this, pInterface, ulFlags, ppMessage);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CopyMessages()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CopyMessages (LPENTRYLIST     pMsgList,
                                        LPCIID          pInterface,
                                        LPVOID          pDestFolder,
                                        ULONG           ulUIParam,
                                        LPMAPIPROGRESS  pProgress,
                                        ULONG           ulFlags)
{
    InfoTrace ("CMAPIFolder::CopyMessages method called");
    Validate_IMAPIFolder_CopyMessages (this,
                                       pMsgList,
                                       pInterface,
                                       pDestFolder,
                                       ulUIParam,
                                       pProgress,
                                       ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::DeleteMessages()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::DeleteMessages (LPENTRYLIST       pMsgList,
                                          ULONG             ulUIParam,
                                          LPMAPIPROGRESS    pProgress,
                                          ULONG             ulFlags)
{
    InfoTrace ("CMAPIFolder::DeleteMessages method called");
    Validate_IMAPIFolder_DeleteMessages (this,
                                         pMsgList,
                                         ulUIParam,
                                         pProgress,
                                         ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CreateFolder()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CreateFolder (ULONG           ulFolderType,
                                        LPTSTR          pszFolderName,
                                        LPTSTR          pszFolderComment,
                                        LPCIID          pInterface,
                                        ULONG           ulFlags,
                                        LPMAPIFOLDER *  ppFolder)
{
    InfoTrace ("CMAPIFolder::CreateFolder method called");
    Validate_IMAPIFolder_CreateFolder (this,
                                       ulFolderType,
                                       pszFolderName,
                                       pszFolderComment,
                                       pInterface,
                                       ulFlags,
                                       ppFolder);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CopyFolder()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::CopyFolder (ULONG             cbEntryID,
                                      LPENTRYID         pEntryID,
                                      LPCIID            pInterface,
                                      LPVOID            pDestFolder,
                                      LPTSTR            pszNewFolderName,
                                      ULONG             ulUIParam,
                                      LPMAPIPROGRESS    pProgress,
                                      ULONG             ulFlags)
{
    InfoTrace ("CMAPIFolder::CopyFolder method called");
    Validate_IMAPIFolder_CopyFolder (this,
                                     cbEntryID,
                                     pEntryID,
                                     pInterface,
                                     pDestFolder,
                                     pszNewFolderName,
                                     ulUIParam,
                                     pProgress,
                                     ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::DeleteFolder()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::DeleteFolder (ULONG           cbEntryID,
                                        LPENTRYID       pEntryID,
                                        ULONG           ulUIParam,
                                        LPMAPIPROGRESS  pProgress,
                                        ULONG           ulFlags)
{
    InfoTrace ("CMAPIFolder::DeleteFolder method called");
    Validate_IMAPIFolder_DeleteFolder (this,
                                       cbEntryID,
                                       pEntryID,
                                       ulUIParam,
                                       pProgress,
                                       ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SetReadFlags()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::SetReadFlags (LPENTRYLIST     pMsgList,
                                        ULONG           ulUIParam,
                                        LPMAPIPROGRESS  pProgress,
                                        ULONG           ulFlags)
{
    InfoTrace ("CMAPIFolder::SetReadFlags method called");
    Validate_IMAPIFolder_SetReadFlags (this,
                                       pMsgList,
                                       ulUIParam,
                                       pProgress,
                                       ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::GetMessageStatus()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::GetMessageStatus (ULONG       cbEntryID,
                                            LPENTRYID   pEntryID,
                                            ULONG       ulFlags,
                                            ULONG *     pulMessageStatus)
{
    InfoTrace ("CMAPIFolder::GetMessageStatus method called");
    Validate_IMAPIFolder_GetMessageStatus (this,
                                           cbEntryID,
                                           pEntryID,
                                           ulFlags,
                                           pulMessageStatus);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SetMessageStatus()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::SetMessageStatus (ULONG       cbEntryID,
                                            LPENTRYID   pEntryID,
                                            ULONG       ulNewStatus,
                                            ULONG       ulNewStatusMask,
                                            ULONG *     pulOldStatus)
{
    InfoTrace ("CMAPIFolder::SetMessageStatus method called");
    Validate_IMAPIFolder_SetMessageStatus (this,
                                           cbEntryID,
                                           pEntryID,
                                           ulNewStatus,
                                           ulNewStatusMask,
                                           pulOldStatus);

    ASSERT (TRANSPORT_MESSAGE_EID_SIZE == cbEntryID);
    SPropValue spvSearchProp;
    spvSearchProp.ulPropTag     = PR_ENTRYID;
    spvSearchProp.Value.bin.cb  = cbEntryID;
    spvSearchProp.Value.bin.lpb = (LPBYTE)pEntryID;

    LPSRow psrTargetRow;
    HRESULT hResult = m_pTableData->HrQueryRow (&spvSearchProp, &psrTargetRow, NULL);
    if (hResult)
    {
        TraceResult ("CMAPIFolder::SetMessageStatus: Failed to query row from internal table", hResult);
        return hResult;
    }

    BOOL bFound = FALSE;
    ULONG ulOldStatus;
    for (ULONG i=0; i<psrTargetRow->cValues; i++)
    {
        if (PR_MSG_STATUS == psrTargetRow->lpProps[i].ulPropTag)
        {
            bFound = TRUE;
            ulOldStatus = psrTargetRow->lpProps[i].Value.l;
            if (pulOldStatus)
            {
                *pulOldStatus = ulOldStatus;
            }
            ulOldStatus &= ulNewStatusMask;
            ulNewStatus &= ulNewStatusMask;
            if (ulNewStatus != ulOldStatus)
            {
                psrTargetRow->lpProps[i].Value.l &= ~ulNewStatusMask;
                psrTargetRow->lpProps[i].Value.l |= ulNewStatus;
                hResult= m_pTableData->HrModifyRow (psrTargetRow);
                // If any, trace out the error code.
                TraceResult ("CMAPIFolder::SetMessageStatus: Failed to modify row in the internal table", hResult);
            }
            break; // Out of the FOR() loop
        }
    }
    if (!hResult && !bFound)
    {
        TraceMessage ("CMAPIFolder::SetMessageStatus: Could not find property in table row");
        hResult = MAPI_E_NOT_FOUND;
    }
    gpfnFreeBuffer (psrTargetRow);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::SaveContentsSort()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::SaveContentsSort (LPSSortOrderSet pSortCriteria,
                                            ULONG           ulFlags)
{
    InfoTrace ("CMAPIFolder::SaveContentsSort method called");
    Validate_IMAPIFolder_SaveContentsSort (this, pSortCriteria, ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::EmptyFolder()
//
//    Parameters
//      { Refer to MAPI Documentation on this method }
//
//    Purpose
//      Stub method.
//
//    Return Value
//      MAPI_E_NO_SUPPORT always.
//
STDMETHODIMP CMAPIFolder::EmptyFolder (ULONG            ulUIParam,
                                       LPMAPIPROGRESS   pProgress,
                                       ULONG            ulFlags)
{
    InfoTrace ("CMAPIFolder::EmptyFolder method called");
    Validate_IMAPIFolder_EmptyFolder (this, ulUIParam, pProgress, ulFlags);
    return MAPI_E_NO_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
// Other member functions specific to this class
//

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::FillContentsTable()
//
//    Parameters
//      pszHeaderFileName       String with a fully qualified path to the
//                              headers data file
//    Purpose
//      This function reads the file with the headers information to
///     populate the table of contents of the remote mail bag folder.
//      The data is store in a file whose path is given in the
//      pszHeaderFileName parameter.
//
//    Return Value
//      S_OK  If the function is successful or an hResult with the
//      error that occurr
//
STDMETHODIMP CMAPIFolder::FillContentsTable (LPTSTR pszHeaderFileName)
{
    ASSERT(pszHeaderFileName);
    if (NULL == m_pTableData)
    {
        // Nothing to do
        return S_OK;
    }

    HRESULT hResult = m_pTableData->HrDeleteRows (TAD_ALL_ROWS, NULL, NULL);
    TraceResult ("CMAPIFolder::FillContentsTable: Failed to delete all rows in internal table", hResult);

    // Check that the file exists. If it doesn't exist, then there is no headers file.
    HANDLE hFile = CreateFile (pszHeaderFileName,
                               GENERIC_READ,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                               NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        // Set the internal flag that the user HAS NOT downloaded headers from the server
        m_fNoHeadersFile = TRUE;
        return S_OK;
    }
    else
    {
        // The time the headers file was last updated, is the last time the file was written to
        if (GetFileTime (hFile, NULL, NULL, &m_ftLastUpdate))
        {
            // Set the internal flag that the user HAS downloaded headers from the server
            m_fNoHeadersFile = FALSE;
        }
        TraceResult ("CMAPIFolder::FillContentsTable: Failed to get info about the headers file", ::GetLastError()); // Call the Win32 API
    }
    if (!GetFileSize (hFile, NULL))
    {
        CloseHandle(hFile);
        return S_OK;
    }

    SRow srTblRow;
    // Allocate an array of properties for the colums in the contents
    // tables of the folder
    hResult = gpfnAllocateBuffer (NUM_HDR_PROPS*sizeof(SPropValue), (LPVOID *)&(srTblRow.lpProps));
    if (hResult)
    {
        TraceResult ("CMAPIFolder::FillContentsTable: Failed to allocate memory for properties", hResult);
        CloseHandle (hFile);
        return hResult;
    }

    // Initialize the property tags in the row set
    srTblRow.cValues = NUM_HDR_PROPS;
    for (UINT i=0; i<NUM_HDR_PROPS; i++)    
    {
        srTblRow.lpProps[i].ulPropTag = sptFldContents.aulPropTag[i];
    }
    // The MS Exchange remote viewer wants PR_MESSAGE_DOWNLOAD_TIME in the rows of the contents table.
    // However in our transport we compute it. This property gets set when we download the message.
    // This property is listed and shown here for information purposes only.
    srTblRow.lpProps[HDR_DOWNLOAD_TIME].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_MESSAGE_DOWNLOAD_TIME));
    srTblRow.lpProps[HDR_DOWNLOAD_TIME].Value.err = S_OK;
    srTblRow.lpProps[HDR_OBJ_TYPE].Value.l = MAPI_MESSAGE;
    
    DWORD dwBytesRead, dwInstanceKey = 1;
    srTblRow.lpProps[HDR_INST_KEY].Value.bin.cb  = sizeof (DWORD); // This is a fixed size.
    srTblRow.lpProps[HDR_INST_KEY].Value.bin.lpb = (LPBYTE)&dwInstanceKey;
    ULONG ulHeaderSize, iNextField;
    LONG lFieldSize, lValue = 0;
    LPTSTR pStr, pszMsgClass;
    TCHAR szDisplayTo[256], szSubject[256], szSender[256];
    BYTE abBuffer[IO_BUFFERSIZE];
    __try
    {
        do
        {
            ZeroMemory (szDisplayTo, 256);
            ZeroMemory (szSubject, 256);
            ZeroMemory (szSender, 256);
            if (ReadFile (hFile, &ulHeaderSize, sizeof(ULONG), &dwBytesRead, NULL))
            {
                if (ReadFile (hFile, abBuffer, ulHeaderSize, &dwBytesRead, NULL))
                {
                    if (dwBytesRead)
                    {
                        // Put the data into the property value members
                        srTblRow.lpProps[HDR_EID].Value.bin.cb  = TRANSPORT_MESSAGE_EID_SIZE; // This is a fixed size.
                        srTblRow.lpProps[HDR_EID].Value.bin.lpb = abBuffer;                   // It will only read the first 16 bytes
                        iNextField = TRANSPORT_MESSAGE_EID_SIZE;                              // Skip the entry ID

                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lFieldSize = atol (pStr);
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        CopyMemory (szSender, &abBuffer[iNextField], lFieldSize);
                        iNextField += lstrlen (szSender) + 1;   // +1 to skip the comma
                        srTblRow.lpProps[HDR_SNDR].Value.LPSZ = szSender;
                        srTblRow.lpProps[HDR_REPR].Value.LPSZ = szSender;

                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lFieldSize = atol (pStr);
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        CopyMemory (szDisplayTo, &abBuffer[iNextField], lFieldSize);
                        srTblRow.lpProps[HDR_DISP_TO].Value.LPSZ = szDisplayTo;
                    
                        iNextField += lFieldSize + 1;       // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lFieldSize = atol (pStr);
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        CopyMemory (szSubject, &abBuffer[iNextField], lFieldSize);
                        srTblRow.lpProps[HDR_SUBJ].Value.LPSZ = szSubject;
                        srTblRow.lpProps[HDR_NORM_SUBJ].Value.LPSZ = szSubject;

                        iNextField += lFieldSize + 1;       // +1 to skip the comma
                        pszMsgClass = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        srTblRow.lpProps[HDR_CLASS].Value.LPSZ = pszMsgClass;
                    
                        iNextField += lstrlen (pszMsgClass) + 1;       // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_FLAGS].Value.l = lValue;

                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_SIZE].Value.l = lValue;

                    
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_PRIOR].Value.l = lValue;
                    
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_IMPORTANCE].Value.l = lValue;

                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_SENS].Value.l = lValue;

                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_TIME].Value.ft.dwLowDateTime = lValue;
                    
                        iNextField += lstrlen (pStr) + 1;   // +1 to skip the comma
                        pStr = strtok ((LPTSTR)&abBuffer[iNextField], ",");
                        lValue = atol (pStr);
                        srTblRow.lpProps[HDR_TIME].Value.ft.dwHighDateTime = lValue;

                        srTblRow.lpProps[HDR_STAT].Value.l = 0;

                        srTblRow.lpProps[HDR_HASATTACH].Value.l = (BOOL)!!(srTblRow.lpProps[HDR_FLAGS].Value.l & MSGFLAG_HASATTACH);
                    
                        hResult = m_pTableData->HrModifyRow (&srTblRow);
                        if (hResult)
                        {
                            TraceResult ("CMAPIFolder::FillContentsTable: Failed to add row to table data", hResult);
                        }
                        dwInstanceKey++;
                    }
                }
                else
                {
                    hResult = ::GetLastError(); // Call the Win32 API
                    TraceResult ("CMAPIFolder::FillContentsTable: Failed to read header data", hResult);
                    hResult = HRESULT_FROM_WIN32 (hResult);
                }
            }
            else
            {
                hResult = ::GetLastError(); // Call the Win32 API
                TraceResult ("CMAPIFolder::FillContentsTable: Failed to read header size", hResult);
                hResult = HRESULT_FROM_WIN32 (hResult);
            }
        } while (dwBytesRead && !hResult);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        TraceString1 ("CMAPIFolder::FillContentsTable: An exception occured. Exception code: %d", GetExceptionCode());
        hResult = MAPI_E_CORRUPT_DATA;
    }

    // Free the array and close the file
    gpfnFreeBuffer (srTblRow.lpProps);
    CloseHandle (hFile);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CMAPIFolder::CopyTableToFile()
//
//    Parameters
//      None.
//
//    Purpose
//      This function copies the data from the in-memory contents table into
//      the headers file. If the user selected any action on the messages in
//      the contents table, those changes will be reflected in the headers
//      file and restored the next time the remote viewer is brought up.
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CMAPIFolder::CopyTableToFile()
{
    if (!m_pTableData)
    {
        return S_OK;
    }
    HRESULT hResult;
    HANDLE hFile = CreateFile (m_pLogon->GetLocalHeadersCache(),
                               GENERIC_WRITE,
                               0,
                               NULL,
                               CREATE_ALWAYS,
                               FILE_FLAG_SEQUENTIAL_SCAN,
                               NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        hResult = ::GetLastError();
        TraceResult ("CMAPIFolder::CopyTableToFile: Failed to open local headers file", hResult);
        return HRESULT_FROM_WIN32(hResult);
    }
    BOOL fDeleteFile = TRUE;
    LPMAPITABLE pTable = NULL;
    hResult = m_pTableData->HrGetView (NULL, NULL, 0, &pTable);
    if (hResult)
    {
        TraceResult ("CMAPIFolder::CopyTableToFile: Failed to get a view of the table data", hResult);
        goto ErrorExit;
    }
    
    hResult = pTable->SetColumns ((LPSPropTagArray)&sptFldContents, 0);
    if (hResult)
    {
        TraceResult ("CMAPIFolder::CopyTableToFile: Failed to set the columns", hResult);
        goto ErrorExit;
    }
    
    LPSPropValue pProps;
    BYTE abBuffer[IO_BUFFERSIZE];
    LPSRowSet pRows;
    LPVOID pVoid;
    DWORD i, cbSize, dwBytesWrittem;
    BOOL fSuccess;
    while (TRUE)
    {
        #define QUERY_SIZE  10
        hResult = pTable->QueryRows (QUERY_SIZE, 0, &pRows);
        if (hResult)
        {
            TraceResult ("CMAPIFolder::CopyTableToFile: Failed to query the rows in the table", hResult);
            goto ErrorExit;
        }
        // Did we finish reading all the rows?
        if (!pRows->cRows)
        {
            FreeProws (pRows);
            break; // Out of the WHILE() loop
        }
        for (i=0; i<pRows->cRows; i++)
        {
            pProps = pRows->aRow[i].lpProps;
            if (pProps[HDR_EID].ulPropTag != PR_ENTRYID ||
                pProps[HDR_SNDR].ulPropTag != PR_SENDER_NAME ||
                pProps[HDR_DISP_TO].ulPropTag != PR_DISPLAY_TO ||
                pProps[HDR_SUBJ].ulPropTag != PR_SUBJECT ||
                pProps[HDR_CLASS].ulPropTag != PR_MESSAGE_CLASS ||
                pProps[HDR_FLAGS].ulPropTag != PR_MESSAGE_FLAGS ||
                pProps[HDR_SIZE].ulPropTag != PR_MESSAGE_SIZE ||
                pProps[HDR_PRIOR].ulPropTag != PR_PRIORITY ||
                pProps[HDR_IMPORTANCE].ulPropTag != PR_IMPORTANCE ||
                pProps[HDR_SENS].ulPropTag != PR_SENSITIVITY ||
                pProps[HDR_TIME].ulPropTag != PR_MESSAGE_DELIVERY_TIME ||
                pProps[HDR_STAT].ulPropTag != PR_MSG_STATUS)
            {
                TraceMessage ("CMAPIFolder::CopyTableToFile: Missing property in a row. Skipping it");
                continue; // The FOR() loop
            }
            
            ZeroMemory (abBuffer, IO_BUFFERSIZE);
        
            // Put the properties' data into the buffer.
            pVoid = (LPVOID)abBuffer;
            CopyMemory (pVoid, pProps[HDR_EID].Value.bin.lpb, TRANSPORT_MESSAGE_EID_SIZE);
            cbSize = (DWORD)pVoid + TRANSPORT_MESSAGE_EID_SIZE;
            pVoid = (LPVOID)cbSize;

            wsprintf ((LPTSTR)pVoid,
                      TEXT("%d,%s,%d,%s,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,"),
                      lstrlen (pProps[HDR_SNDR].Value.LPSZ),
                      pProps[HDR_SNDR].Value.LPSZ,
                      lstrlen (pProps[HDR_DISP_TO].Value.LPSZ),
                      pProps[HDR_DISP_TO].Value.LPSZ,
                      lstrlen (pProps[HDR_SUBJ].Value.LPSZ),
                      pProps[HDR_SUBJ].Value.LPSZ,
                      pProps[HDR_CLASS].Value.LPSZ,
                      pProps[HDR_FLAGS].Value.l,
                      pProps[HDR_SIZE].Value.l,
                      pProps[HDR_PRIOR].Value.l,
                      pProps[HDR_IMPORTANCE].Value.l,
                      pProps[HDR_SENS].Value.l,
                      pProps[HDR_TIME].Value.ft.dwLowDateTime,
                      pProps[HDR_TIME].Value.ft.dwHighDateTime);

            cbSize = TRANSPORT_MESSAGE_EID_SIZE + lstrlen ((LPTSTR)pVoid);
            fSuccess = WriteFile (hFile, &cbSize, sizeof(DWORD), &dwBytesWrittem, NULL);
            if (fSuccess)
            {
                fSuccess = WriteFile (hFile, abBuffer, cbSize, &dwBytesWrittem, NULL);
                if (fSuccess)
                {
                    fDeleteFile = FALSE;
                }
            }
            if (!fSuccess)
            {
                hResult = ::GetLastError();
                TraceResult ("CMAPIFolder::CopyTableToFile: Write header data to file", hResult);
                hResult = HRESULT_FROM_WIN32(hResult);
                break; // Ouf of the FOR() loop
            }
        }
        FreeProws (pRows);
        if (hResult)
        {
            goto ErrorExit;
        }
    }

ErrorExit:
    if (pTable)
    {
        pTable->Release();
    }
    CloseHandle (hFile);
    if (hResult && fDeleteFile)
    {
        DeleteFile (m_pLogon->GetLocalHeadersCache());
    }
    m_pTableData->Release();
    m_pTableData = NULL;
    return hResult;
}

// End of file for XPFOLDER.CPP
