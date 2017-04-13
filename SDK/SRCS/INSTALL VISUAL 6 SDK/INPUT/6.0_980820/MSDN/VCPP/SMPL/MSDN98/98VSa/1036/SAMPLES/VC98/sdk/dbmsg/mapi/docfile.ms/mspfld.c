/*
 *  M S P F L D . C
 *
 *  Code that implements the object methods of IMAPIFolder.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

#define FLD_ValidateParameters(pobj, intf, method, arglist)     \
        OBJ_ValidateParameters(pobj, intf, method, sizeof(IFLD), &vtblIFLD, arglist)

static BOOL IFLD_IsInvalid(PIFLD pifld);
static HRESULT HrCreateContTblMutex(HANDLE *phCTMutex);
static BOOL FFoldInSameStore(PIFLD pifld, PIFLD lpDestFld);
static BOOL FIsAncestor(PIFLD pifldAncestor, PIFLD pifldDescendent);
static HRESULT HrGetSortOrder(PIFLD pifld, LPSSortOrderSet *lppsSortOrder);
static HRESULT HrFillHierarchyTable(PIFLD pifld, LPTABLEDATA lptbl);
static HRESULT HrIsRead(PIFLD pifld, PEID peidMsg, BOOL *pfRead);
static HRESULT HrCreateFolder(PIFLD pifldParent, LPSTR szName, LPSTR szComment,
    BOOL fOpenIfExists, PIFLD *ppifldNew, BOOL *pfCreated);
static HRESULT HrDeleteSubDirectory(PIFLD pifldParent, PEID peidToDelete,
    ULONG ulFlags, BOOL fContentsOnly);
static HRESULT HrCopyContents(PIFLD pifldSrc, PIFLD pifldDst, ULONG ulFlags,
    LPSPropTagArray ptagaExcl);
static BOOL FFolderExists(PEID peid, PIMS pims);
static HRESULT HrSetSubFolderProp(PIFLD pifld, BOOL fSubFolder);
static HRESULT HrSetOneROFolderProp(PIFLD pifld, LONG lValue, ULONG ulPT);
static HRESULT HrEIDFromDisplayName(LPMAPITABLE pmt, LPSTR szName, PLMR plmr,
    PEID *ppeid);
static HRESULT HrCreateMessageList(PIFLD pifld, LPENTRYLIST *lppEntryList);
static void DestroyMessageList(PLMR plmr, LPENTRYLIST *lppEntryList);

#define NUM_RW_FOLDER_PROPS      2  /* number read write initial folder props */

#define IFLD_EnterCriticalSection(pifld)    OBJ_EnterCriticalSection((POBJ)pifld)
#define IFLD_LeaveCriticalSection(pifld)    OBJ_LeaveCriticalSection((POBJ)pifld)

CALLERRELEASE ViewRelease;

TCHAR szSubfolderPropFile[] = TEXT("subfoldr.prp");
TCHAR szAllFilesTemplate[] = TEXT("*.*");

/* properties excluded on a copy of folders' .prp file */
const static SizedSPropTagArray(13, sptaExclFldProps) =
{
    13,
    {
        PR_CONTENT_COUNT,
        PR_CONTENT_UNREAD,
        PR_ENTRYID,
        PR_INSTANCE_KEY,
        PR_PARENT_ENTRYID,
        PR_OBJECT_TYPE,
        PR_STORE_ENTRYID,
        PR_STORE_RECORD_KEY,
        PR_RECORD_KEY,
        PR_FOLDER_TYPE,
        PR_SUBFOLDERS,
        PR_MESSAGE_RECIPIENTS,
        PR_MESSAGE_ATTACHMENTS
    }
};

/* read only property proptags */
/* order must match order initialized on CreateFolderStorage */
#define NUM_RO_FOLDER_PROPS     11  /* number read only initial folder props */
const static SizedSPropTagArray(NUM_RO_FOLDER_PROPS, sptaReadOnly) =
{
    NUM_RO_FOLDER_PROPS,
    {
        PR_OBJECT_TYPE,
        PR_RECORD_KEY,
        PR_FOLDER_TYPE,
        PR_CONTENT_COUNT,
        PR_CONTENT_UNREAD,
        PR_STORE_ENTRYID,
        PR_STORE_RECORD_KEY,
        PR_SUBFOLDERS,
        PR_ENTRYID,
        PR_PARENT_ENTRYID,
        PR_INSTANCE_KEY
    }
};

/* read only property attributes */
const static SizedSPropAttrArray(NUM_RO_FOLDER_PROPS, spaReadOnly) =
{
    NUM_RO_FOLDER_PROPS,
    {
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE,
        PROPATTR_READABLE
    }
};

/* initial sort order set for a contents table */
static SizedSSortOrderSet(1, sSortOrderContentsDefault) =
{
    1,
    0,
    0,
    {
        PR_INSTANCE_KEY,                /* the index column */
        TABLE_SORT_ASCEND
    }
};

/* message status property array */
static SPropTagArray sptaMessageStatus =
{
    1,
    {
        PR_MESSAGE_FLAGS
    }
};

/* DISPATCH TABLE */
IFLD_Vtbl vtblIFLD =
{
    (IFLD_QueryInterface_METHOD *)  OBJ_QueryInterface,
    (IFLD_AddRef_METHOD *)          OBJ_AddRef,
    IFLD_Release,
    (IFLD_GetLastError_METHOD *)    IMS_GetLastError,
    (IFLD_SaveChanges_METHOD *)     IMS_SaveChanges,
    IFLD_GetProps,
    IFLD_GetPropList,
    IFLD_OpenProperty,
    IFLD_SetProps,
    IFLD_DeleteProps,
    IFLD_CopyTo,
    IFLD_CopyProps,
    (IFLD_GetNamesFromIDs_METHOD *) IMS_GetNamesFromIDs,
    (IFLD_GetIDsFromNames_METHOD *) IMS_GetIDsFromNames,
    IFLD_GetContentsTable,
    IFLD_GetHierarchyTable,
    (IFLD_OpenEntry_METHOD *)       IMS_OpenEntry,
    IFLD_SetSearchCriteria,
    IFLD_GetSearchCriteria,
    IFLD_CreateMessage,
    IFLD_CopyMessages,
    IFLD_DeleteMessages,
    IFLD_CreateFolder,
    IFLD_CopyFolder,
    IFLD_DeleteFolder,
    IFLD_SetReadFlags,
    IFLD_GetMessageStatus,
    IFLD_SetMessageStatus,
    IFLD_SaveContentsSort,
    IFLD_EmptyFolder
};

/****************************************************
*           Methods on IMAPIFolder                  *
*****************************************************/

/****************************************************************
    Folder properties are all implemented by creating a file
    (FOLDER.PRP) inside each folder and using message properties
    on it.
*************************************************************/

/***************************************************************************
 -  IFLD_Release
 -
 *  Purpose:
 *      Given a valid folder object, decrements the reference count, and if
 *      zero, NULLS out the lpVtbl. If no child objects of the folder remain
 *      open, and no contents or hierarchy tables remain open, the routine
 *      also destroys the object (see OBJ_Destroy for details of that action).
 *
 *      This release method is very similar to the standard one found in
 *      mspobj.c. The only difference is that this one also checks for any
 *      open contents or hierarchy tables, and doesn't actually destroy
 *      the folder until they are gone. See ViewRelease() for the other side
 *      of this implementation.
 *
 *  Parameters
 *       pifld      The folder object to release
 *
 *  Returns:
 *       ULONG: The value of the reference count on the whole object. When
 *              fully released, it is zero. This information can be used for
 *              diagnostic and testing purposes only. It CANNOT be used by
 *              shipping code. See the OLE 2.0 programmers reference for more
 *              details. Note that this function will also return zero when
 *              the identity of the object has been destroyed. Therefore,
 *              clients may not rely on zero having any special significance
 *              other than for debugging purposes.
 */
STDMETHODIMP_(ULONG) IFLD_Release(PIFLD pifld)
{
    LONG cRef;
    POBJ pobj;

    if (IFLD_IsInvalid(pifld))
    {
        TraceSz1("SampleMS: IFLD_Release(pifld=%08lX): Folder is invalid and is "
            "being ignored", pifld);
        return (0);
    }

    IFLD_EnterCriticalSection(pifld);

    pobj = (POBJ) pifld;

    AssertSz(pobj->cRef > 0, "IFLD_Release(): Too many releases");

    cRef = --pobj->cRef;

    if (cRef == 0)
    {
        pobj->lpVtbl = 0;   /* should prevent being called again. */

        if (    pobj->pobjHead == 0
            &&  pifld->lptblContents == NULL
            &&  pifld->lptblHierarchy == NULL)
        {
            OBJ_Destroy(pobj);  /* will leave the critical section */
            return (0);
        }
    }

    IFLD_LeaveCriticalSection(pifld);

    return (cRef);
}

/***************************************************************************
 -  IFLD_GetProps
 -
 *  Purpose:
 *      Returns in pcval and ppval the values of the properties
 *      in ptaga.  If the latter is NULL, all properties in the folder
 *      are returned.
 *
 *  Parameters
 *       pifld      The folder object whose properties are requested
 *       ptaga      Pointer to a counted array of property tags of
 *                  properties requested
 *       ulFlags    UNICODE / String8
 *       pcval      Pointer to number of values returned
 *       ppval      Pointer to a variable in which the address of the
 *                  returned property values is placed
 *
 *  Returns:
 *       HRESULT
 *
 */
STDMETHODIMP IFLD_GetProps(PIFLD pifld, LPSPropTagArray ptaga, ULONG ulFlags,
    ULONG *pcval, LPSPropValue *ppval)
{
    LPMESSAGE lpmsg = NULL;     /* open property message */
    HRESULT hr = hrSuccess;

    FLD_ValidateParameters(
            pifld, 
            IMAPIProp,
            GetProps,
            (pifld, 
            ptaga, 
            ulFlags,
            pcval, 
            ppval));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IFLD_EnterCriticalSection(pifld);

    /* open the property message */
    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims, FALSE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    /* Pass the call off to IMessage */
    hr = lpmsg->lpVtbl->GetProps(lpmsg, ptaga, ulFlags, pcval, ppval);

    UlRelease(lpmsg);

    {if(HR_SUCCEEDED(hr))
    {
        LPSPropValue pvalStoreSupMask = PpropFindProp(*ppval, *pcval, 
                    PROP_TAG(PT_UNSPECIFIED, PROP_ID(PR_STORE_SUPPORT_MASK)));
        if(pvalStoreSupMask)
        {
            pvalStoreSupMask->ulPropTag = PR_STORE_SUPPORT_MASK;
            pvalStoreSupMask->Value.l = SMS_SUPPORTMASK;

            /* fix up hr */
            if(ptaga->cValues == 1)
                hr = hrSuccess;
        }
    }
    }

    /* Wrap internal properties. Note that this function takes as an */
    /* argument the HRESULT from the previous IMessage::GetProps call. */
    /* We aren't ignoring the error. */

    hr = HrWrap_GetProps(hr, pifld->pims, pifld->cval, pifld->pval, pcval,
        ppval, FALSE, (ptaga != NULL), (POBJ)pifld);

exit:
    IFLD_LeaveCriticalSection(pifld);

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_W_ERRORS_RETURNED)
        DebugTraceResult(IFLD_GetProps, hr);
    #endif

    return HrCheckHr(hr, IMAPIProp_GetProps);
}

/***************************************************************************
 -  IFLD_GetPropList
 -
 *  Purpose:
 *      Returns in ptaga the list of all currently accessible properties
 *      of pifld.
 *
 *  Parameters
 *       pifld          The folder object whose properties are requested
 *       ulFlags        UNICODE / String8
 *       pptaga         Pointer to a counted array of property tags of
 *                      properties requested
 *  Returns:
 *       hr
 *
 */
STDMETHODIMP IFLD_GetPropList(PIFLD pifld, ULONG ulFlags, LPSPropTagArray *pptaga)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL;

    FLD_ValidateParameters(
            pifld, 
            IMAPIProp,
            GetPropList,
            (pifld, 
            ulFlags, 
            pptaga));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IFLD_EnterCriticalSection(pifld);

    /* open the property message */
    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims, FALSE,
            &lpmsg);

    /* If the property message was successfully opened, then pass the */
    /* call off to IMessage */

    if (hr == hrSuccess)
        hr = lpmsg->lpVtbl->GetPropList(lpmsg, ulFlags, pptaga);

    UlRelease(lpmsg);

    IFLD_LeaveCriticalSection(pifld);
    DebugTraceResult(IFLD_GetPropList, hr);
    return HrCheckHr(hr, IMAPIProp_GetPropList);
}

/***************************************************************************
 -  IFLD_OpenProperty
 -
 *  Purpose:
 *      Returns in *lppUnk a pointer to a newly created interface for the
 *                  propery of pifld in ulPropTag
 *      Not supported on folders.
 *
 *  Parameters
 *       pifld          the folder object whose property interface is requested
 *       ulPropTag          Property tag for the desired property--only ID is used.
 *       lpiid              Pointer to the GUID for the interface
 *       ulInterfaceOptions Specifies interface-specific behavior
 *       ulFlags            MAPI_CREATE, MAPI_MODIFY, MAPI_DEFERRED_ERRORS
 *       lppUnk             Pointer to the newly created interface pointer
 *
 *  Returns:
 *       hr
 *
 */
STDMETHODIMP IFLD_OpenProperty(PIFLD pifld, ULONG ulPropTag, LPCIID lpiid,
    ULONG ulInterfaceOptions, ULONG ulFlags, LPUNKNOWN *lppUnk)
{
    SCODE sc;

    FLD_ValidateParameters(
            pifld, 
            IMAPIProp,
            OpenProperty,
            (pifld, 
            ulPropTag, 
            lpiid, 
            ulInterfaceOptions, 
            ulFlags, 
            lppUnk));

    sc = MAPI_E_NO_SUPPORT;
    
    DebugTraceSc(IFLD_OpenProperty, sc);
    return ResultFromScode(sc);
}

/***************************************************************************
 -  IFLD_SetProps
 -
 *  Purpose:
 *      Sets the properties in pval for pifld.
 *      lppProblems is a pointer to a structure of problems,
 *      NULL If there weren't any.
 *
 *  Parameters
 *       pifld          the folder object whose properties are to be set
 *       cValues            count of properties to be set
 *       pval               Pointer to a an array of property value structures.
 *       ppErr      Pointer to address of a property problem structure
 *                              to be returned.
 *
 *  Returns:
 *       hr         PROP_E_SECURITY_VIOLATION, PROP_E_CALL_FAILED,
 *                          PROP_E_CALL_FAILED
 *
 */
STDMETHODIMP IFLD_SetProps(PIFLD pifld, ULONG cValues, LPSPropValue pval,
    LPSPropProblemArray *ppErr)
{
    LPMESSAGE lpmsgNew = NULL;      /* new instance of property message */
    HRESULT hr;

    FLD_ValidateParameters(
            pifld, 
            IMAPIProp,
            SetProps,
            (pifld, 
            cValues, 
            pval, 
            ppErr));

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* open the property message */
    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims,
        TRUE, &lpmsgNew);
    if (hr != hrSuccess)
        goto exit;

    /* set props on the property message */
    hr = lpmsgNew->lpVtbl->SetProps(lpmsgNew, cValues, pval, ppErr);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsgNew->lpVtbl->SaveChanges(lpmsgNew, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    /* Must release the message before trying to update the hierarchy */
    /* table. Multiple opens on the internal message are not allowed by */
    /* IStorage. */

    UlRelease(lpmsgNew);
    lpmsgNew = NULL;

    /* If this isn't the root folder, get the parent entryid, and call */
    /* ChangeTable so that any new properties are updated in its */
    /* hierarchy table row. */

    if (FIsRoot(pifld->peid) == FALSE)
    {
        PEID peidParent = NULL;
        PIMS pims = pifld->pims;

        hr = HrGetParentEID(&pims->lmr, pifld->peid, &peidParent);
        if (hr == hrSuccess)
        {
            ChangeTable(pims, peidParent, pifld->peid, MAPI_FOLDER,
                TABLE_ROW_MODIFIED, TRUE);
            LMFree(&pims->lmr, peidParent);
        }
        else
        {
            TraceSz1("Sample MS: IFLD_SetProps: failed to change hierarchy "
                "table. sc == %s\n", SzDecodeScode(GetScode(hr)));
            hr = hrSuccess;
        }
    }

exit:
    UlRelease(lpmsgNew);

    IFLD_LeaveCriticalSection(pifld);
    DebugTraceResult(IFLD_SetProps, hr);
    return HrCheckHr(hr, IMAPIProp_SetProps);
}

/***************************************************************************
 -  IFLD_DeleteProps
 -
 *  Purpose:
 *      Deletes the properties in ptaga for pifld.  ppErr
 *      is a pointer to a structure of problems, NULL If there weren't any.
 *
 *  Parameters
 *       pifld          the folder object whose properties are to be deleted
 *       ptaga      Pointer to a counted array of property tags of the
 *                          properties to be deleted.  Must not be NULL.
 *       ppErr      Pointer to address of a property problem structure
 *                          to be returned.
 *  Returns:
 *       hr         PROP_E_SECURITY_VIOLATION, PROP_E_CALL_FAILED,
 *                          PROP_E_CALL_FAILED
 */
STDMETHODIMP IFLD_DeleteProps(PIFLD pifld, LPSPropTagArray ptaga,
    LPSPropProblemArray *ppErr)
{
    LPMESSAGE lpmsgNew = NULL;  /* new instance of property message */
    HRESULT hr = hrSuccess;

    FLD_ValidateParameters(
            pifld, 
            IMAPIProp,
            DeleteProps,
            (pifld, 
            ptaga, 
            ppErr));

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* open the property message */
    hr = HrOpenPropertyMessageRetry(pifld->peid,
        pifld->pims, TRUE, &lpmsgNew);
    if (hr != hrSuccess)
        goto exit;

    /* Pass the call off to IMessage */
    hr = lpmsgNew->lpVtbl->DeleteProps(lpmsgNew, ptaga, ppErr);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsgNew->lpVtbl->SaveChanges(lpmsgNew, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    /* Must release the message before trying to update the hierarchy */
    /* table. Multiple opens on the internal message are not allowed by */
    /* IStorage. */

    UlRelease(lpmsgNew);
    lpmsgNew = NULL;

    /* If this isn't the root folder, get the parent entryid, and call */
    /* ChangeTable so that any new properties are updated in its */
    /* hierarchy table row. */

    if (FIsRoot(pifld->peid) == FALSE)
    {
        PEID peidParent = NULL;
        PIMS pims = pifld->pims;

        hr = HrGetParentEID(&pims->lmr, pifld->peid, &peidParent);
        if (hr == hrSuccess)
        {
            ChangeTable(pims, peidParent, pifld->peid, MAPI_FOLDER,
                TABLE_ROW_MODIFIED, TRUE);
            LMFree(&pims->lmr, peidParent);
        }
        else
        {
            TraceSz1("Sample MS: IFLD_DeleteProps: failed to change hierarchy "
                "table. sc == %s\n", SzDecodeScode(GetScode(hr)));
            hr = hrSuccess;
        }
    }

exit:
    UlRelease(lpmsgNew);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_DeleteProps, hr);
    return HrCheckHr(hr, IMAPIProp_DeleteProps);
}

/***************************************************************************
 -  IFLD_CopyTo
 -
 *  Purpose:
 *      Copy the properties and/or contents of the current object
 *          to a destination object
 *
 *  Parameters
 *       pifldSrc       current object
 *       ciidExcl       Count of excluded interfaces in rgiidExcl
 *       rgiidExcl      Array of iid's specifying excluded interfaces
 *       ptagaExcl      Pointer to a counted array of property tags of
 *                      properties not to be copied, can be NULL
 *       ulUIParam      Handle of parent window cast to ULONG, NULL if
 *                      no dialog requested
 *       piidDst        Interface ID of the interface of lpDestObj
 *       lpDestObj      destination object
 *       ulFlags        MAPI_MOVE, MAPI_NOREPLACE, MAPI_DIALOG, MAPI_DECLINE_OK
 *       pprba          Pointer to address of a property problem
 *                      structure to be returned.
 *
 *  Returns:
 *       hr
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_CopyTo(PIFLD pifldSrc, ULONG ciidExcl, LPCIID rgiidExcl,
    LPSPropTagArray ptagaExcl, ULONG ulUIParam, LPMAPIPROGRESS lpProgress,
    LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlagsIn,
    LPSPropProblemArray *pprba)
{
    HRESULT hr = hrSuccess;
    BOOL fIsIMapiProp = TRUE;   /* TRUE if are to copy as imapiprop */
    BOOL fIsIMAPIFolder = TRUE;     /* TRUE if are to copy as IMAPIFolder */
    SCODE sc = S_OK;
    LPCIID piid;
    LPCIID piidMax;
    ULONG ulFlags;

    FLD_ValidateParameters(
            pifldSrc, 
            IMAPIProp,
            CopyTo,
            (pifldSrc, 
            ciidExcl, 
            rgiidExcl,
            ptagaExcl, 
            ulUIParam, 
            lpProgress,
            piidDst, 
            lpDestObj, 
            ulFlagsIn,
            pprba));

    IFLD_EnterCriticalSection(pifldSrc);

    /* Turn off MAPI_DIALOG flag, since we don't support it. */
    ulFlags = (ulFlagsIn & ~MAPI_DIALOG);

    piid = rgiidExcl;
    piidMax = piid + ciidExcl;

    /* find the interface to copy : IMAPIPROP or IMAPIFOLDER */
    while (piid < piidMax)
    {
        if (IsEqualIID(piid, &IID_IMAPIFolder))
            fIsIMAPIFolder = FALSE;
        else if (IsEqualIID(piid, (LPIID) &IID_IMAPIProp))
            fIsIMapiProp = FALSE;
        piid++;
    }

    /* make sure that the destination can support this */
    if (fIsIMAPIFolder && !IsEqualIID(piidDst, (LPIID) &IID_IMAPIFolder))
    {
        LPMAPIFOLDER pfld = NULL;

        hr = ((LPUNKNOWN) lpDestObj)->lpVtbl->QueryInterface(lpDestObj,
            (LPIID) &IID_IMAPIFolder, (LPVOID *) &pfld);
        if (hr != hrSuccess)
        {
            Assert(GetScode(hr) == MAPI_E_INTERFACE_NOT_SUPPORTED);
            goto exit;
        }
        UlRelease(pfld);
    }
    else if (fIsIMapiProp &&
            !(IsEqualIID(piidDst, (LPIID) &IID_IMAPIProp) ||
            IsEqualIID(piidDst, (LPIID) &IID_IMAPIFolder)))
    {
        LPMAPIPROP pmp = NULL;

        hr = ((LPUNKNOWN) lpDestObj)->lpVtbl->QueryInterface(lpDestObj,
            (LPIID) &IID_IMAPIProp, (LPVOID *) &pmp);
        if (hr != hrSuccess)
        {
            Assert(GetScode(hr) == MAPI_E_INTERFACE_NOT_SUPPORTED);
            goto exit;
        }
        UlRelease(pmp);
    }

    if (!FFoldInSameStore(pifldSrc, (PIFLD) lpDestObj))
    {
        LPMAPISUP psup = pifldSrc->pims->psup;

        /* leave critical section before calling back to MAPI */
        IFLD_LeaveCriticalSection(pifldSrc);

        /* call MAPI's CopyProps */
        hr = psup->lpVtbl->DoCopyTo(psup, (LPIID) &IID_IMAPIFolder, (LPVOID) pifldSrc,
            ciidExcl, rgiidExcl, ptagaExcl, ulUIParam,
            lpProgress, piidDst, lpDestObj, ulFlagsIn, pprba);

        DebugTraceResult(IFLD_CopyTo, hr);
        return (HrCheckHr(hr, IMAPIProp_CopyTo));
    }

    /* copy them as folders */
    if (fIsIMAPIFolder)
    {
        PIFLD pifldDst = (PIFLD) lpDestObj;

        /* make sure we have write access */

        if (!OBJ_TestFlag(pifldDst, OBJF_MODIFY))
        {
            hr = ResultFromScode(MAPI_E_NO_ACCESS);
            goto exit;
        }

        if (!FContainsProp(PR_CONTAINER_HIERARCHY, ptagaExcl))
        {
            /* can not move or copy a folder to a decendant or itself */
            if (FIsAncestor(pifldSrc, pifldDst))
                hr = ResultFromScode(MAPI_E_NO_ACCESS);
        }
        else if (ulFlags & MAPI_MOVE)
        {
            /* Can't set MAPI_MOVE and also exclude subfolders. */
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
        }

        if (hr != hrSuccess)
            goto exit;

        if (!(ulFlags & MAPI_NOREPLACE))
        {
            /* Empty the destination folder before beginning. */
            hr = pifldDst->lpVtbl->EmptyFolder(pifldDst, 0, NULL, 0);
            if (hr != hrSuccess)
                goto exit;
        }

        /* copy the contents of the source folder to the destination folder */
        hr = HrCopyContents(pifldSrc, pifldDst, ulFlags, ptagaExcl);
        if (hr != hrSuccess)
            goto exit;
    }

    /* copy the properties */
    if (fIsIMapiProp || fIsIMAPIFolder)
    {
        LPMESSAGE lpmsg;
        BOOL fModify = FALSE;

        if (ulFlags & MAPI_MOVE)
            fModify = TRUE;

        hr = HrOpenPropertyMessageRetry(pifldSrc->peid,
            pifldSrc->pims, fModify, &lpmsg);
        if (hr != hrSuccess)
            goto exit;

        hr = lpmsg->lpVtbl->CopyTo(lpmsg, ciidExcl,
            rgiidExcl, ptagaExcl, ulUIParam, lpProgress,
            (LPIID) &IID_IMAPIProp, lpDestObj, ulFlags, pprba);

        if (hr == hrSuccess && fModify)
            lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);

        UlRelease(lpmsg);
    }

exit:
    IFLD_LeaveCriticalSection(pifldSrc);

    DebugTraceResult(IFLD_CopyTo, hr);
    return HrCheckHr(hr, IMAPIProp_CopyTo);
}

/***************************************************************************
 -  IFLD_CopyProps
 -
 *  Purpose:
 *      Copy the properties and/or contents of the current object
 *          to a destination object
 *
 *  Parameters
 *       pifldSrc       current object
 *       ptagaIncl      Pointer to a counted array of property tags of
 *                      properties to be copied
 *       ulUIParam      Handle of parent window cast to ULONG, NULL if
 *                      no dialog requested
 *       piidDst        Interface ID of the interface of lpDestObj
 *       lpDestObj      destination object
 *       ulFlags        MAPI_MOVE, MAPI_NOREPLACE, MAPI_DIALOG, MAPI_DECLINE_OK
 *       pprba          Pointer to address of a property problem
 *                      structure to be returned.
 *
 *  Returns:
 *       hr
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_CopyProps(PIFLD pifldSrc,
    LPSPropTagArray ptagaIncl, ULONG ulUIParam, LPMAPIPROGRESS lpProgress,
    LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlagsIn,
    LPSPropProblemArray *pprba)
{
    HRESULT hr = hrSuccess;

#ifdef WHEN_WORKING
    PIFLD pifldDst = NULL;      /* lpDestObj if it's a folder */
    BOOL fIsIMAPIFolder;        /* TRUE if are to copy as IMAPIFolder */
    SCODE sc = S_OK;
    LPIID piid;
    LPIID piidMax;
    ULONG ulFlags;
#endif /* WHEN_WORKING */

    FLD_ValidateParameters(
            pifldSrc, 
            IMAPIProp,
            CopyProps,
            (pifldSrc,
            ptagaIncl, 
            ulUIParam, 
            lpProgress,
            piidDst, 
            lpDestObj, 
            ulFlagsIn,
            pprba));

    IFLD_EnterCriticalSection(pifldSrc);

#ifdef WHEN_WORKING
    /* Turn off MAPI_DIALOG flag, since we don't support it. */
    ulFlags = (ulFlagsIn & ~MAPI_DIALOG);

    fIsIMAPIFolder =   FContainsProp(PR_CONTAINER_HIERARCHY, ptagaIncl)
                    || FContainsProp(PR_CONTAINER_CONTENTS, ptagaIncl);
    /* make sure that the destination can support this */
    if (fIsIMAPIFolder && !IsEqualIID(piidDst, (LPIID) &IID_IMAPIFolder))
    {
        LPMAPIFOLDER pfld = NULL;

        hr = ((LPUNKNOWN) lpDestObj)->lpVtbl->QueryInterface(lpDestObj,
            (LPIID) &IID_IMAPIFolder, (LPVOID *) &pfld);
        if (hr != hrSuccess)
        {
            Assert(GetScode(hr) == MAPI_E_INTERFACE_NOT_SUPPORTED);
            goto exit;
        }
        UlRelease(pfld);
    }
    else if (!(IsEqualIID(piidDst, (LPIID) &IID_IMAPIProp) ||
            IsEqualIID(piidDst, (LPIID) &IID_IMAPIFolder)))
    {
        LPMAPIPROP pmp = NULL;

        hr = ((LPUNKNOWN) lpDestObj)->lpVtbl->QueryInterface(lpDestObj,
            (LPIID) &IID_IMAPIProp, (LPVOID *) &pmp);
        if (hr != hrSuccess)
        {
            Assert(GetScode(hr) == MAPI_E_INTERFACE_NOT_SUPPORTED);
            goto exit;
        }
        UlRelease(pmp);
    }

    if (!FFoldInSameStore(pifldSrc, (PIFLD) lpDestObj))
    {
        LPMAPISUP psup = pifldSrc->pims->psup;

        /* leave critical section before calling back to MAPI */
        IFLD_LeaveCriticalSection(pifldSrc);

        /* call MAPI's CopyProps */
        hr = psup->lpVtbl->DoCopyProps(psup, (LPIID) &IID_IMAPIFolder,
            (LPVOID) pifldSrc, ptagaIncl, ulUIParam,
            lpProgress, piidDst, lpDestObj, ulFlagsIn, pprba);

        DebugTraceResult(IFLD_CopyProps, hr);
        return (HrCheckHr(hr, IMAPIProp_CopyProps));
    }

    /* copy them as folders */
    if (fIsIMAPIFolder)
    {
        PIFLD pifldDst = (PIFLD) lpDestObj;

        /* make sure we have write access */

        if (!OBJ_TestFlag(pifldDst, OBJF_MODIFY))
        {
            hr = ResultFromScode(MAPI_E_NO_ACCESS);
            goto exit;
        }

        if (FContainsProp(PR_CONTAINER_HIERARCHY, ptagaIncl))
        {
            /* can not move or copy a folder to a decendant or itself */
            if (FIsAncestor(pifldSrc, pifldDst))
                hr = ResultFromScode(MAPI_E_NO_ACCESS);
        }
        else if (ulFlags & MAPI_MOVE)
        {
            /* Can't set MAPI_MOVE and also exclude subfolders. */
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
        }

        if (hr != hrSuccess)
            goto exit;

        if (!(ulFlags & MAPI_NOREPLACE))
        {
            /* Empty the destination folder before beginning. */
            hr = pifldDst->lpVtbl->EmptyFolder(pifldDst, 0, NULL, 0);
            if (hr != hrSuccess)
                goto exit;
        }


        if (FContainsProp(PR_CONTAINER_CONTENTS, ptagaIncl))
        {
            /* copy the contents of the source folder to the destination folder */
            hr = HrCopyContents(pifldSrc, pifldDst, ulFlags, NULL);
        }
        if (hr != hrSuccess)
            goto exit;
    }

    /* copy the properties */
    /* //$ Rebuild ptagaIncl without Contents and Hierarchy */
    {
        LPMESSAGE lpmsg;
        BOOL fModify = FALSE;

        if (ulFlags & MAPI_MOVE)
            fModify = TRUE;

        hr = HrOpenPropertyMessageRetry(pifldSrc->peid,
            pifldSrc->pims, fModify, &lpmsg);
        if (hr != hrSuccess)
            goto exit;

        hr = lpmsg->lpVtbl->CopyProps(lpmsg,
            ptagaIncl, ulUIParam, lpProgress,
            (LPIID) &IID_IMAPIProp, lpDestObj, ulFlags, pprba);

        if (hr == hrSuccess && fModify)
            lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);

        UlRelease(lpmsg);
    }


exit:
    IFLD_LeaveCriticalSection(pifldSrc);

#else

    IFLD_LeaveCriticalSection(pifldSrc);

    /* call MAPI's CopyProps */
    hr = pifldSrc->pims->psup->lpVtbl->DoCopyProps(pifldSrc->pims->psup,
        (LPIID) &IID_IMAPIFolder, (LPVOID) pifldSrc, ptagaIncl, ulUIParam,
        lpProgress, piidDst, lpDestObj, ulFlagsIn, pprba);

#endif  /* WHEN_WORKING */

    DebugTraceResult(IFLD_CopyProps, hr);
    return HrCheckHr(hr, IMAPIProp_CopyProps);
}

/***************************************************************************
 -  IFLD_GetContentsTable
 -
 *  Purpose:
 *      Returns a table with the summary information about the messages
 *      in the folder
 *
 *  Parameters
 *       pifld  the folder object
 *       ulFlags    MAPI_DEFERRED_ERRORS, MAPI_ASSOCIATED
 *       lppTable   location to place the table object
 *
 *  Returns:
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_GetContentsTable(PIFLD pifld, ULONG ulFlags,
    LPMAPITABLE *lppTable)
{
    HRESULT hr = hrSuccess;
    SCODE sc;
    HANDLE hFindFile = FAILED_SEARCH;
    LPTSTR szMessageTemplate = NULL;    /* template for a message name */
    LPSSortOrderSet lpsSortOrder = NULL;
    BOOL fTableCreated = FALSE;
    BOOL fInMutex = FALSE;
    PIMS pims;

    FLD_ValidateParameters(
            pifld, 
            IMAPIContainer,
            GetContentsTable,
            (pifld, 
            ulFlags,
            lppTable));

    #ifdef VALIDATE
    if (ulFlags & MAPI_ASSOCIATED)
        return ResultFromScode(MAPI_E_NO_SUPPORT);
    
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IFLD_EnterCriticalSection(pifld);

    pims = pifld->pims;

    /* If the table mutex doesn't yet exist on this process, create it. */

    if (pims->hContTblMutex == NULL)
    {
        hr = HrCreateContTblMutex(&pims->hContTblMutex);
        if (hr != hrSuccess)
            goto exit;
    }

    if (pifld->lptblContents == NULL)
    {
        PINST pinst = (PINST) PvGetInstanceGlobals();
        PLMR plmr = &pifld->pims->lmr;

        if (pinst == NULL)
        {
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            goto exit;
        }

        /* create the data for the table */
        sc = CreateTable((LPIID) &IID_IMAPITableData,
            plmr->lpAllocBuf, plmr->lpAllocMore,
            plmr->lpFreeBuf, pinst->lpmalloc, TBLTYPE_DYNAMIC,
            PR_INSTANCE_KEY, (LPSPropTagArray) &sPropTagsContents,
            &(pifld->lptblContents));

        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }
        fTableCreated = TRUE;

        /* Get the table mutex so that we can access the file without */
        /* crossing paths with another process. */

        WaitForSingleObject(pims->hContTblMutex, INFINITE);
        fInMutex = TRUE;

        hr = HrReadTableFromDisk(pifld->lptblContents, (POBJ) pifld,
            pifld->peid->szPath, CONTENTS_COLUMNS, szContentsFileName);
        if (hr != hrSuccess)
        {
            /* non-fatal. If the data on disk is missing or invalid, we */
            /* should regenerate the data via HrSyncContentsTable. */

            TraceSz1("SMS: Error %s reading table from disk. Regenerating "
                "table on disk.", SzDecodeScode(GetScode(hr)));

            hr = hrSuccess;
        }
    }

    /* If we don't already have the mutex, get it so that we can access */
    /* the file without crossing paths with another process. */

    if (!fInMutex)
    {
        WaitForSingleObject(pims->hContTblMutex, INFINITE);
        fInMutex = TRUE;
    }

    hr = HrSyncContentsTable(pifld, TRUE);

    Assert(fInMutex);

    ReleaseMutex(pims->hContTblMutex);
    fInMutex = FALSE;

    if (hr != hrSuccess)
        goto exit;

    /* open a view to the table */
    /* get the sort order from the PR_SMS_CONTENTS_SORT_ORDER property */
    hr = HrGetSortOrder(pifld, &lpsSortOrder);
    if (hr != hrSuccess)
        goto exit;

    /* get the view */
    hr = pifld->lptblContents->lpVtbl->HrGetView(pifld->lptblContents,
        lpsSortOrder, ViewRelease, (ULONG) pifld, lppTable);
    if (hr != hrSuccess)
        goto exit;

    /* record this view in pifld */
    pifld->cContentsViews++;

exit:
    if (fInMutex)
        ReleaseMutex(pims->hContTblMutex);

    /* free the sort order */
    LMFree(&pifld->pims->lmr, lpsSortOrder);

    /* remove the table if it is created in error */
    if (hr != hrSuccess && fTableCreated)
    {
        UlRelease(pifld->lptblContents);
        pifld->cContentsViews = 0;
        pifld->lptblContents = NULL;
    }

    CloseIDSearch(&hFindFile, &szMessageTemplate);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_GetContentsTable, hr);
    return HrCheckHr(hr, IMAPIFolder_GetContentsTable);
}

/***************************************************************************
 -  IFLD_GetHierarchyTable
 -
 *  Purpose:
 *      Returns a table with the summary information about the child
 *      folders of the current folder
 *
 *  Parameters
 *       pifld      the folder object
 *       ulFlags    CONVENIENT_DEPTH if set indicates pre-order traversal
 *                  MAPI_DEFERRED_ERRORS
 *                  MAPI_UNICODE
 *       lppTable   location to place the table object
 *
 *  Returns:
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_GetHierarchyTable(PIFLD pifld, ULONG ulFlags,
    LPMAPITABLE *lppTable)
{
    HRESULT hr;
    LPTABLEDATA lptad = NULL;

    FLD_ValidateParameters(
            pifld, 
            IMAPIContainer,
            GetHierarchyTable,
            (pifld, 
            ulFlags, 
            lppTable));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IFLD_EnterCriticalSection(pifld);

    /* if table needs refreshing */
    if (pifld->lptblHierarchy == NULL)
    {
        PINST pinst = (PINST) PvGetInstanceGlobals();
        SCODE sc;
        PLMR plmr = &pifld->pims->lmr;

        pifld->cHierarchyViews = 0;

        if (pinst == NULL)
        {
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            goto exit;
        }

        /* create the table */
        sc = CreateTable((LPIID) &IID_IMAPITableData,
            plmr->lpAllocBuf, plmr->lpAllocMore,
            plmr->lpFreeBuf, pinst->lpmalloc, TBLTYPE_DYNAMIC,
            PR_INSTANCE_KEY, (LPSPropTagArray) &sPropTagsHierarchy, &lptad);

        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        /* add a row or traversal for each subfolder of pifld */
        /* Note that the sample store only supports a max depth of 1. */

        hr = HrFillHierarchyTable(pifld, lptad);
        if (hr != hrSuccess)
            goto exit;

        pifld->lptblHierarchy = lptad;
        lptad = NULL;
    }

    /* open a view to the table */
    hr = pifld->lptblHierarchy->lpVtbl->HrGetView(pifld->lptblHierarchy,
        NULL, ViewRelease, (ULONG) pifld, lppTable);
    if (hr != hrSuccess)
        goto exit;

    /* record this view in pifld */
    pifld->cHierarchyViews++;

exit:
    /* remove the table if it is created in error */
    if (hr != hrSuccess && lptad)
        UlRelease(lptad);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_GetHierarchyTable, hr);
    return HrCheckHr(hr, IMAPIFolder_GetHierarchyTable);
}

/***************************************************************************
 -  IFLD_CreateMessage
 -
 *  Purpose:
 *      Creates a new message in the store
 *
 *  Parameters
 *      pifld           the folder object
 *      ulFlags         flags. Valid flags to pass are MAPI_DEFERRED_ERRORS
 *                      and MAPI_ASSOCIATED. The sample store doesn't support
 *                      MAPI_ASSOCIATED, so the code returns no support if
 *                      that flag is passed.
 *      piid            reserved for future use
 *      lppMessage      location to place the message object
 *
 *  Returns:
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_CreateMessage(PIFLD pifld, LPCIID piid, ULONG ulFlags,
    LPMESSAGE *lppMessage)
{
    HRESULT hr;
    PEID peid = NULL;
    ULONG ulSeqNumber;
    PIMSG pimsg = NULL;
    LPTSTR szFull = NULL;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            CreateMessage,
            (pifld, 
            piid, 
            ulFlags, 
            lppMessage));

    #ifdef VALIDATE
    if (ulFlags & MAPI_ASSOCIATED)
        return ResultFromScode(MAPI_E_NO_SUPPORT);

    if (piid && !FQueryInterface(OT_MESSAGE, piid))
        return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
    #endif

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* create the message */

    hr = HrNewEID(pifld, pifld->pims, TEMP_EXT, &ulSeqNumber, &peid);
    if (hr != hrSuccess)
        goto exit;

    hr = HrNewIMSG(peid, pifld->pims, TRUE, TRUE, ulSeqNumber, &szFull, &pimsg);
    if (hr != hrSuccess)
        goto exit;

    hr = InitIMSGProps(pimsg);
    if (hr != hrSuccess)
        goto exit;

    /* folder contents counts and tables are not updated until message */
    /* has changes saved */

exit:
    LMFree(&pifld->pims->lmr, peid);

    if (hr == hrSuccess)
        *lppMessage = (LPMESSAGE) pimsg;
    else if (pimsg)
    {
        UlRelease(pimsg);

        Assert(szFull);
        DeleteFile(szFull);
    }

    FreeNull(szFull);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_CreateMessage, hr);
    return HrCheckHr(hr, IMAPIFolder_CreateMessage);
}

/***************************************************************************
 -  IFLD_CopyMessages
 -
 *  Purpose:
 *      Moves/Copies messages from the source folder to the destination folder
 *      EntryId's are not changed here since they get stamped in when the
 *      messages are opened.
 *
 *  Parameters
 *      pifld                   the source folder
 *      lpMsgList               the list of messages to be moved/copied
 *      piid                    the interface id of destination folder
 *      lpfolderDst             the destination folder
 *      ulUIParam               Handle of parent window,
 *                                  ignored if MESSAGE_DIALOG not set
 *      lpProgress              points to progress dialog object
 *      ulFlags                 MAPI_DECLINE_OK, MESSAGE_MOVE, or MESSAGE_DIALOG
 */
STDMETHODIMP IFLD_CopyMessages(PIFLD pifld, LPENTRYLIST lpMsgList,
    LPCIID piid, LPMAPIFOLDER lpfolderDst, ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    LONG cHandled = 0;          /* number messages copied/moved */
    LPTSTR szSrcName = NULL;    /* name of file to be moved */
    LPTSTR szDestName = NULL;   /* name of the file after it is moved */
    ULONG cbSrcPath = 0;        /* length in bytes of path to src fld */
    ULONG cbDestPath = 0;       /* length in bytes of path to dest fld */
    ULONG cbStorePath = 0;      /* length in bytes of path to root of store */
    TCHAR szBlanks[CCH_NAME] = TEXT("        .   ");
    HRESULT hr = hrSuccess;
    PIFLD pifldDst;
    BOOL fMove;
    SBinary *psb;
    SBinary *psbMax;
    PIMS pims;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            CopyMessages,
            (pifld, 
            lpMsgList, 
            piid, 
            lpfolderDst, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    pifldDst = (PIFLD) lpfolderDst;
    pims = pifld->pims;

    /* if the folders aren't in the same store, call back to MAPI */

    if (!FFoldInSameStore(pifld, pifldDst))
    {
        /* leave critical section before calling back to MAPI */
        IFLD_LeaveCriticalSection(pifld);

        return pims->psup->lpVtbl->CopyMessages(pims->psup,
            (LPIID) &IID_IMAPIFolder, (LPVOID) pifld, lpMsgList, piid,
            (LPVOID) lpfolderDst, ulUIParam, lpProgress, ulFlags);
    }

    fMove   = !!(ulFlags & MESSAGE_MOVE);

    if (    !OBJ_TestFlag(pifldDst, OBJF_MODIFY)
        ||  (   fMove
            &&  !OBJ_TestFlag(pifld, OBJF_MODIFY)))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    if (fMove)
    {
        /* If moving messages and the source and destination are the same */
        /* folder, we are done even before we begin. */

        ULONG ulTheSame;

        hr = pims->lpVtbl->CompareEntryIDs(pims,
                CbEID(pifldDst->peid), (LPENTRYID) pifldDst->peid,
                CbEID(pifld->peid), (LPENTRYID) pifld->peid, 0L, &ulTheSame);
        if (hr != hrSuccess)
            goto exit;

        if (ulTheSame)
        {
            hr = hrSuccess;
            goto exit;
        }
    }

    /* get storage for the path names */
    cbStorePath = Cbtszsize(pims->szStorePath);
    cbSrcPath = cbStorePath + CbEIDPath(pifld->peid);
    if (FIsRoot(pifld->peid))
        cbSrcPath--;

    cbDestPath = cbStorePath + CbEIDPath(pifldDst->peid);
    if (FIsRoot(pifldDst->peid))
        cbDestPath--;

    hr = HrFullPathName(pims->szStorePath, pifld->peid->szPath,
        szBlanks, &szSrcName);
    if (hr != hrSuccess)
        goto exit;

    hr = HrFullPathName(pims->szStorePath, pifldDst->peid->szPath,
        szBlanks, &szDestName);
    if (hr != hrSuccess)
        goto exit;

    psb = lpMsgList->lpbin;
    psbMax = psb + lpMsgList->cValues;

    /* move/copy each message */
    while (psb < psbMax)
    {
        ULONG ulMF;
        ULONG ulObjType;
        BOOL fLocked;
        BOOL fRead;
        PIMSG pimsg;
        LPSTR szRelativePath;
        PEID peidNewID;
        PEID peidToCopy;
        ULONG cbEntryID;

        cbEntryID = psb->cb;
        peidToCopy = (PEID) (psb->lpb);

        if (    FIsInvalidEID(cbEntryID, peidToCopy, pims)
            ||  !FIsMessage((PEID) peidToCopy))
        {
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
            goto exit;
        }

        /* open the message */
        hr = pifld->lpVtbl->OpenEntry(pifld, CbEID(peidToCopy),
                (LPENTRYID) peidToCopy, NULL, 0L, &ulObjType,
                (LPUNKNOWN *) &pimsg);
        if (hr != hrSuccess)
            goto exit;

        Assert(ulObjType == MAPI_MESSAGE);

        /* retrieve the PR_MESSAGE_FLAGS property */
        hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pims->lmr,
                PR_MESSAGE_FLAGS, &ulMF);

        UlRelease(pimsg);

        if (hr != hrSuccess)
            goto exit;

        fLocked = !!(ulMF & MSGFLAG_SUBMIT);
        fRead = !!(ulMF & MSGFLAG_READ);

        /* if the message is locked then this is an error */
        if (fLocked)
        {
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
            goto exit;
        }

        /* store in szSrcName the root relative path of the message to be moved*/
        lstrcpy(szSrcName + cbSrcPath, SzBaseName(peidToCopy));

        /* store in szDestName the store relative path name of */
        /* destination file */
        if (fMove)
            lstrcpy(szDestName + cbDestPath, SzBaseName(peidToCopy));
        else
        {
            /* If we're copying, we need to generate a new filename for the */
            /* message, or else we will have two messages with the same */
            /* filename, and copying again (or moving back) will fail. */

            PEID peidTemp = NULL;

            hr = HrNewEID(pifld, pims, MESSAGE_EXT, NULL, &peidTemp);
            if (hr != hrSuccess)
                goto exit;

            lstrcpy(szDestName + cbDestPath, SzBaseName(peidTemp));

            LMFree(&pims->lmr, peidTemp);
        }

        /* either move or copy the message */
        if (fMove)
        {
            if (!MoveFile(szSrcName, szDestName))
            {
                TraceSz1("MoveFile failed: OS error %08lX.", GetLastError());
                hr = ResultFromScode(MAPI_E_NO_ACCESS);
                goto exit;
            }

            /* remove this message from contents tables */

            (void) HrIncrementOneROProp(pifld, -1, PR_CONTENT_COUNT);

            if (!fRead)
                (void) HrIncrementOneROProp(pifld, -1, PR_CONTENT_UNREAD);

            ChangeTable(pims, pifld->peid, peidToCopy, MAPI_MESSAGE,
                TABLE_ROW_DELETED, TRUE);
        }
        else
        {
            if (!CopyFile(szSrcName, szDestName, TRUE))
            {
                TraceSz1("CopyFile failed: OS error %08lX.", GetLastError());
                hr = ResultFromScode(MAPI_E_NO_ACCESS);
                goto exit;
            }
        }

        /* get new entryid for this message */
        hr = HrFullToRelative(szDestName, pims, &szRelativePath);
        if (hr != hrSuccess)
            goto exit;

        hr = HrConstructEID(&(peidToCopy->uidResource), &pims->lmr,
                szRelativePath, &peidNewID);

        FreeNull(szRelativePath);

        if (hr != hrSuccess)
            goto exit;

        /* If we're copying, then we just used a new name for the file. */
        /* Note that PR_RECORD_KEY, PR_ENTRYID, PR_INSTANCE_KEY, and */
        /* PR_PARENT_ENTRYID are now different, but since these are stored */
        /* in the opened msg, everything should be fine. */

        /* add a row to the contents table of the destination folder */
        (void) HrIncrementOneROProp(pifldDst, 1, PR_CONTENT_COUNT);

        if (!fRead)
            (void) HrIncrementOneROProp(pifldDst, 1, PR_CONTENT_UNREAD);

        ChangeTable(pims, pifldDst->peid, peidNewID, MAPI_MESSAGE,
            TABLE_ROW_ADDED, TRUE);

        LMFree(&pims->lmr, peidNewID);

        cHandled++;
        psb++;
    }

exit:
    FreeNull(szDestName);
    FreeNull(szSrcName);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_CopyMessages, hr);
    return HrCheckHr(hr, IMAPIFolder_CopyMessages);
}

/***************************************************************************
 -  IFLD_DeleteMessages
 -
 *  Purpose:
 *      Deletes from the folder pifld all messages in the list lpMsgList
 *
 *  Parameters
 *      pifld           the folder from which messages are to be deleted
 *      lpMsgList       the list of messages to be deleted
 *      ulUIParam       handle to main window, cast to ULONG
 *      lpProgress      points to progress dialog information
 *      ulFlags         MESSAGE_DIALOG
 *
 *  Returns:
 *
 *  Side effects:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_DeleteMessages(PIFLD pifld, LPENTRYLIST lpMsgList,
    ULONG ulUIParam, LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    PEID peidToDelete = NULL;   /* pointer to next eid to be deleted */
    LONG cDeleted = 0;          /* number messages deleted */
    LONG cUnreadDeleted = 0;    /* number of unread messages deleted */
    LPTSTR szToDeleteName = NULL;   /* name of the next message to be deleted */
    HRESULT hr = hrSuccess;
    LPTSTR szBlankName = TEXT("        .   ");
    ULONG cchPath;              /* length of path to message */
    BOOL fIsRead;               /* TRUE if deleting a read message */
    DWORD dwErr;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            DeleteMessages,
            (pifld, 
            lpMsgList,
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    hr = HrFullPathName(pifld->pims->szStorePath, pifld->peid->szPath,
        szBlankName, &szToDeleteName);
    if (hr != hrSuccess)
        goto exit;

    cchPath = lstrlen(szToDeleteName) - lstrlen(szBlankName);

    /* delete each message in lpMsgList up until the first error */
    while ((ULONG) cDeleted < lpMsgList->cValues)
    {
        peidToDelete = (PEID) (lpMsgList->lpbin[cDeleted].lpb);

        /* make sure that this is a message's eid */
        if (!FIsMessage(peidToDelete))
        {
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
            goto exit;
        }

        /* make sure the message is not submitted */
        if (FIsSubmittedMessage(pifld->pims, peidToDelete))
        {
            hr = ResultFromScode(MAPI_E_SUBMITTED);
            goto exit;
        }

        /* See if it has been read */
        hr = HrIsRead(pifld, peidToDelete, &fIsRead);
        if (hr != hrSuccess)
            goto exit;

        /* remove the message from disk */
        lstrcpy(szToDeleteName + cchPath, SzBaseName(peidToDelete));
        if (!DeleteFile(szToDeleteName))
        {
            dwErr = GetLastError();

            if ((dwErr != ERROR_FILE_NOT_FOUND && dwErr != ERROR_PATH_NOT_FOUND)
                || lpMsgList->cValues == 1)
            {
                hr = ResultFromScode(MAPI_E_NO_ACCESS);
                goto exit;
            }
        }

        /* remove this message from any open tables */
        ChangeTable(pifld->pims, pifld->peid, peidToDelete, MAPI_MESSAGE,
            TABLE_ROW_DELETED, TRUE);

        if (!fIsRead)
            cUnreadDeleted++;

        cDeleted++;
    }

exit:

    FreeNull(szToDeleteName);

    if (cDeleted)
        (void) HrIncrementOneROProp(pifld, -cDeleted, PR_CONTENT_COUNT);
    if (cUnreadDeleted)
        (void) HrIncrementOneROProp(pifld, -cUnreadDeleted, PR_CONTENT_UNREAD);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_DeleteMessages, hr);
    return HrCheckHr(hr, IMAPIFolder_DeleteMessages);
}

/***************************************************************************
 -  IFLD_CreateFolder
 -
 *  Purpose:
 *      Create a new folder within the message store
 *
 *  Parameters
 *      pifld               the parent folder of the newly created folder
 *      ulFldType           type of folder to be created
 *      szFldName           name of the new folder
 *      szComment           comment string for the new folder
 *      piid                Reserved; must be NULL.
 *      ulFlags             MAPI_UNICODE and/or MAPI_DEFERRED_ERRORS
 *      lppfolder           pointer to variable to receive new folder object
 *
 */
STDMETHODIMP IFLD_CreateFolder(PIFLD pifld, ULONG ulFldType, LPSTR szFldName,
    LPSTR szComment, LPCIID piid, ULONG ulFlags, LPMAPIFOLDER *lppfolder)
{
    HRESULT hr;
    PIFLD pifldNew = NULL;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            CreateFolder,
            (pifld, 
            ulFldType, 
            szFldName, 
            szComment, 
            piid, 
            ulFlags, 
            lppfolder));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);

    if (piid && !FQueryInterface(OT_FOLDER, piid))
        return ResultFromScode(MAPI_E_INTERFACE_NOT_SUPPORTED);
    #endif

    /* Sample store can only create generic folders. */
    if (ulFldType != FOLDER_GENERIC)
        return ResultFromScode(MAPI_E_NO_SUPPORT);

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    hr = HrCreateFolder(pifld, szFldName, szComment,
        !!(ulFlags & OPEN_IF_EXISTS), &pifldNew, NULL);

    if (hr != hrSuccess)
        UlRelease(pifldNew);
    else
        *lppfolder = (LPMAPIFOLDER) pifldNew;

exit:
    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_CreateFolder, hr);
    return HrCheckHr(hr, IMAPIFolder_CreateFolder);
}

/***************************************************************************
 -  IFLD_CopyFolder
 -
 *  Purpose:
 *      Copy my child folder to the specified parent
 *
 *  Parameters
 *      pifld           the parent folder of the newly created folder
 *      cbEntryID       length of entry ID of folder to copy
 *      lpEntryID       entry ID of folder to copy
 *      lpiid           interface to the destination folder
 *      lpfolder        pointer to destination object
 *      szNewName       new name to give the copied folder, may be NULL
 *      ulUIParam       Handle of parent window,
 *                      ignored if MESSAGE_DIALOG not set
 *      lpProgress      points to progress dialog information
 *      ulFlags         control flags
 *
 */
STDMETHODIMP IFLD_CopyFolder(PIFLD pifld, ULONG cbEntryID, LPENTRYID lpEntryID,
    LPCIID piid, LPVOID lpfolder, LPSTR szNewName,
    ULONG ulUIParam, LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    HRESULT hr;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            CopyFolder,
            (pifld, 
            cbEntryID, 
            lpEntryID,
            piid, 
            lpfolder, 
            szNewName, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    /* For now, all we do is call back to mapi. */

    hr = pifld->pims->psup->lpVtbl->CopyFolder(pifld->pims->psup,
        (LPIID) &IID_IMAPIFolder, (LPVOID) pifld, cbEntryID, lpEntryID,
        piid, lpfolder, szNewName, ulUIParam, lpProgress, ulFlags);

    DebugTraceResult(IFLD_CopyFolder, hr);
    return HrCheckHr(hr, IMAPIFolder_CopyFolder);
}

/***************************************************************************
 -  IFLD_DeleteFolder
 -
 *  Purpose:
 *      Deletes a subfolder
 *
 *  Parameters
 *      pifld               the current folder
 *      cbEntryID           byte count of lpEntryID
 *      lpEntryID           entryID of subfolder to be deleted
 *      ulUIParam           handle to main window cast to ULONG
 *      lpProgress          pointer to progess dialog information
 *      ulFlags             DEL_MESSAGES and/or DEL_FOLDERS
 *                                  and/or FOLDER_DIALOG
 *
 *  Returns:
 *
 *  Errors:
 */
STDMETHODIMP IFLD_DeleteFolder(PIFLD pifld, ULONG cbEntryID,
    LPENTRYID lpEntryID, ULONG ulUIParam, LPMAPIPROGRESS lpProgress,
    ULONG ulFlags)
{
    HRESULT hr = hrSuccess;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            DeleteFolder,
            (pifld, 
            cbEntryID,
            lpEntryID, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    if (FIsInvalidEID(cbEntryID, (PEID) lpEntryID, pifld->pims)
        || !FIsFolder((PEID) lpEntryID))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* delete this subdirectory of the current directory */
    hr = HrDeleteSubDirectory(pifld, (PEID) lpEntryID, ulFlags, FALSE);

exit:
    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_DeleteFolder, hr);
    return HrCheckHr(hr, IMAPIFolder_DeleteFolder);
}

STDMETHODIMP IFLD_SetSearchCriteria(PIFLD pifld, LPSRestriction lpRestriction,
    LPENTRYLIST lpentrylist, ULONG ulSearchFlags)
{
    DebugTraceSc(IFLD_SetSearchCriteria, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

STDMETHODIMP IFLD_GetSearchCriteria(PIFLD pifld, ULONG ulFlags,
    LPSRestriction *lppRestriction, LPENTRYLIST *lppfolderList, 
    ULONG *lpulSearchState)
{
    DebugTraceSc(IFLD_GetSearchCriteria, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

/***************************************************************************
 -  IFLD_SetReadFlags
 -
 *  Purpose:
 *      Sets the READ flag for each of the given messages.
 *
 *  Parameters
 *      pifld                   the source folder
 *      lpMsgList               the list of messages to be moved/copied
 *      ulUIParam               Handle of parent window,
 *                                  ignored if MESSAGE_DIALOG not set
 *      lpProgress              points to progress dialog object
 *      ulFlags                 SUPPRESS_RECEIPT, CLEAR_READ_FLAG
 */
STDMETHODIMP IFLD_SetReadFlags(PIFLD pifld, LPENTRYLIST lpMsgList,
    ULONG ulUIParam, LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    HRESULT hr = hrSuccess;
    LPENTRYLIST pelst = NULL;
    BOOL fFreeList = FALSE;
    SBinary *psb;
    SBinary *psbMax;
    BOOL fMultipleNotifs = TRUE;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            SetReadFlags,
            (pifld, 
            lpMsgList, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    pelst = lpMsgList;

    if (pelst == NULL)
    {
        /* Create the message list if the caller didn't give us one. */

        hr = HrCreateMessageList(pifld, &pelst);
        if (hr != hrSuccess)
            goto exit;

        fFreeList = TRUE;
    }

    if (pelst->cValues > 5)
        fMultipleNotifs = FALSE;

    psb = pelst->lpbin;
    psbMax = psb + pelst->cValues;

    /* Call IMessage::SetReadFlag on each message */

    while (psb < psbMax)
    {
        ULONG ulObjType;
        PIMSG pimsg;
        PEID peid;
        ULONG cbEntryID;

        cbEntryID = psb->cb;
        peid = (PEID) (psb->lpb);

        if (    FIsInvalidEID(cbEntryID, peid, pifld->pims)
            ||  !FIsMessage((PEID) peid))
        {
            hr = ResultFromScode(MAPI_E_INVALID_PARAMETER);
            goto exit;
        }

        /* open the message */
        hr = pifld->lpVtbl->OpenEntry(pifld, CbEID(peid),
                (LPENTRYID) peid, NULL, 0L, &ulObjType,
                (LPUNKNOWN *) &pimsg);
        if (hr != hrSuccess)
            goto exit;

        Assert(ulObjType == MAPI_MESSAGE);

        hr = pimsg->lpVtbl->SetReadFlag(pimsg, ulFlags);

        if (hr == hrSuccess && fMultipleNotifs)
            ChangeTable(pimsg->pims, pifld->peid, pimsg->peid, MAPI_MESSAGE,
                TABLE_ROW_MODIFIED, TRUE);

        UlRelease(pimsg);

        if (hr != hrSuccess)
            goto exit;

        psb++;
    }

    /* If several messages changed, then just send one notification to */
    /* re-sync the entire contents table on other processes. */

    if (!fMultipleNotifs)
        ChangeTable(pifld->pims, pifld->peid, NULL, MAPI_MESSAGE,
            TABLE_CHANGED, TRUE);

exit:
    if (fFreeList)
        DestroyMessageList(&pifld->pims->lmr, &pelst);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_SetReadFlags, hr);
    return HrCheckHr(hr, IMAPIFolder_SetReadFlags);
}

/***************************************************************************
 -  GetMessageStatus
 -
 *  Purpose:
 *      Retrieves the status associated with a message in a folder
 *
 *  Parameters
 *      pifld               the current folder
 *      cbEntryID           byte count of lpEntryID
 *      lpEntryID           entryID of the message
 *      ulFlags             reserved for future use, must be 0
 *      lpulMessageStatus   pointer to variable to receive the status
 *
 */
STDMETHODIMP IFLD_GetMessageStatus(PIFLD pifld, ULONG cbEntryID,
    LPENTRYID lpEntryID, ULONG ulFlags, ULONG *lpulMessageStatus)
{
    LPMESSAGE lpmsgMsg = NULL;  /* lpEntryID as an open message */
    ULONG ulObjType;            /* type of object opened */
    HRESULT hr = hrSuccess;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            GetMessageStatus,
            (pifld, 
            cbEntryID, 
            lpEntryID, 
            ulFlags, 
            lpulMessageStatus));

    IFLD_EnterCriticalSection(pifld);

    if (FIsInvalidEID(cbEntryID, (PEID) lpEntryID, pifld->pims)
        || !FIsMessage((PEID) lpEntryID))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    /* open up lpEntryID */
    hr = pifld->lpVtbl->OpenEntry(pifld, cbEntryID,
        lpEntryID, NULL, 0L, &ulObjType, (LPUNKNOWN *) &lpmsgMsg);
    if (hr != hrSuccess)
        goto exit;

    /* get the property */
    hr = HrGetSingleProp((LPMAPIPROP) lpmsgMsg, &pifld->pims->lmr,
        PR_MSG_STATUS, lpulMessageStatus);

    if (hr != hrSuccess)
        goto exit;

exit:
    UlRelease(lpmsgMsg);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_GetMessageStatus, hr);
    return HrCheckHr(hr, IMAPIFolder_GetMessageStatus);
}

/***************************************************************************
 -  SetMessageStatus
 -
 *  Purpose:
 *      Sets the 32-bit status associated with a message in a folder
 *
 *  Parameters
 *      pifld               the current folder
 *      cbEntryID           byte count of lpentryID
 *      lpEntryID           entryID of the message
 *      ulNewStatus         new status to be assigned
 *      ulNewStatusMask     mask applied to new status indicating bits to set
 *      lpulOldStatus       pointer to variable to hold previous status
 *
 */
STDMETHODIMP IFLD_SetMessageStatus(PIFLD pifld, ULONG cbEntryID,
    LPENTRYID lpEntryID, ULONG ulNewStatus, ULONG ulNewStatusMask,
    ULONG *lpulOldStatus)
{
    PIMSG pimsg = NULL;
    LPMESSAGE lpmsg;
    ULONG ulObjType;            /* type of object just opened */
    HRESULT hr = hrSuccess;
    ULONG ulStatus;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            SetMessageStatus,
            (pifld, 
            cbEntryID, 
            lpEntryID, 
            ulNewStatus, 
            ulNewStatusMask, 
            lpulOldStatus));

    IFLD_EnterCriticalSection(pifld);

    if (FIsInvalidEID(cbEntryID, (PEID) lpEntryID, pifld->pims) ||
        !FIsMessage((PEID) lpEntryID))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    if (    ulNewStatusMask
        &&  !OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* open up lpEntryID */
    hr = pifld->lpVtbl->OpenEntry(pifld, CbEID((PEID) lpEntryID),
        lpEntryID, NULL, 0L, &ulObjType, (LPUNKNOWN *) &pimsg);
    if (hr != hrSuccess)
        goto exit;

    lpmsg = pimsg->lpmsg;

    /* get the old status */
    hr = HrGetSingleProp((LPMAPIPROP) lpmsg, &pifld->pims->lmr,
        PR_MSG_STATUS, &ulStatus);
    if (hr != hrSuccess)
        goto exit;

    if (lpulOldStatus)
        *lpulOldStatus = ulStatus;

    if (ulNewStatusMask)
    {
        ulNewStatus &= ulNewStatusMask;
        ulStatus &= ~ulNewStatusMask;
        ulStatus |= ulNewStatus;

        hr = HrSetOneROProp(lpmsg, &pifld->pims->lmr, PR_MSG_STATUS,
            &ulStatus);
        if (hr != hrSuccess)
            goto exit;

        hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);

        UlRelease(pimsg);
        pimsg = NULL;

        if (hr != hrSuccess)
            goto exit;

        ChangeTable(pifld->pims, pifld->peid, (PEID) lpEntryID, MAPI_MESSAGE,
            TABLE_ROW_MODIFIED, TRUE);
    }

exit:
    UlRelease(pimsg);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_SetMessageStatus, hr);
    return HrCheckHr(hr, IMAPIFolder_SetMessageStatus);
}

/***************************************************************************
 -  IFLD_SaveContentsSort
 -
 *  Purpose:
 *      set default sort order for contents tables on pifld
 *
 *  Parameters
 *      pifld               the current folder
 *      lpSortCriteria      points to the sort criteria
 *      ulFlags             RECURSIVE_SORT
 *
 */
STDMETHODIMP IFLD_SaveContentsSort(PIFLD pifld, LPSSortOrderSet lpSortCriteria,
    ULONG ulFlags)
{
    SPropValue pval;            /* sort order property value */
    LPSPropProblemArray pprba = NULL;
    HRESULT hr = hrSuccess;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            SaveContentsSort,
            (pifld, 
            lpSortCriteria,
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    pval.Value.MVl.lpl = NULL;

    /* store the sort order in pval */
    pval.ulPropTag = PR_SMS_CONTENTS_SORT_ORDER;
    pval.Value.MVl.cValues = 2 * lpSortCriteria->cSorts;
    pval.Value.MVl.lpl = (LONG *) lpSortCriteria->aSort;

    /*  set the sort order property */
    hr = pifld->lpVtbl->SetProps(pifld, 1, &pval, &pprba);

    if (pprba)
    {
        LMFree(&pifld->pims->lmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_SaveContentsSort, hr);
    return HrCheckHr(hr, IMAPIFolder_SaveContentsSort);
}

/*
 *  IFLD_EmptyFolder
 *
 *  Purpose:
 *      This function empties a folder based on the flags given. It will never
 *      actually delete the folder itself, and will only empty the specified
 *      items.
 *
 *  Parameters
 *      pifld           The address of the folder object to empty.
 *      ulUIParam       Handle of the parent window. (for progress). NYI
 *      lpProgress      Address of progress dialog object
 *      ulFlags         Control flags. Setting DEL_ASSOCIATED causes FAI
 *                      to also be deleted. The FOLDER_DIALOG flag is NYI.
 *                      DEL_ASSOCIATED has no meaning to the sample store.
 *
 *  Returns:
 */
STDMETHODIMP IFLD_EmptyFolder(PIFLD pifld, ULONG ulUIParam,
    LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    HRESULT hr;
    PIFLD pifldParent = NULL;

    FLD_ValidateParameters(
            pifld, 
            IMAPIFolder,
            EmptyFolder,
            (pifld, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IFLD_EnterCriticalSection(pifld);

    if (!OBJ_TestFlag(pifld, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* Empty the folder. */

    hr = HrOpenParent(pifld->pims, pifld->peid, MAPI_MODIFY, &pifldParent);
    if (hr != hrSuccess)
        goto exit;

    hr = HrDeleteSubDirectory(pifldParent, pifld->peid,
        (DEL_MESSAGES | DEL_FOLDERS), TRUE);
    if (hr != hrSuccess)
        goto exit;

exit:
    UlRelease(pifldParent);

    IFLD_LeaveCriticalSection(pifld);

    DebugTraceResult(IFLD_EmptyFolder, hr);
    return HrCheckHr(hr, IMAPIFolder_EmptyFolder);
}

/****************************************************
 *          Private Functions                       *
 ****************************************************/

/*
 *  IFLD_IsInvalid
 *
 *  Purpose         check if pifld points to an invalid folder.
 *
 *  Parameter
 *      pifld       pointer to the folder
 *
 *  Returns: BOOL - TRUE means the folder is invalid.
 */

static BOOL IFLD_IsInvalid(PIFLD pifld)
{
    return (IsBadWritePtr(pifld, sizeof(IFLD)) ||
        pifld->lpVtbl != &vtblIFLD);
}

/* 
 * HrCreateContTblMutex
 *
 *  Purpose
 *      Create the contents table mutex, and return it to the caller.
 *
 *  Arguments
 *      phCTMutex: Pointer to the location to return the new mutex.
 *
 *  Returns:
 *      HRESULT: Will return an error only if the CreateMutex call fails.
 */
static HRESULT HrCreateContTblMutex(HANDLE *phCTMutex)
{
    HRESULT hr = hrSuccess;
    HANDLE hMutex;
    LPTSTR szMutexName = "SMS_CONTTBLFILE_MUTEX";

    hMutex = CreateMutex(NULL, FALSE, szMutexName);

    if (hMutex)
        *phCTMutex = hMutex;

    #ifndef WIN16
    else
    {
        TraceSz1("SampleMS: HrCreateContTblMutex: call to"
            " CreateMutex failed (error %08lX)", GetLastError());
        
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }
    #endif

    DebugTraceResult(HrCreateContTblMutex, hr);
    return hr;
}

/*
 *  FFoldInSameStore
 *
 *  Purpose
 *      Given that the source folder is a folder object within
 *      our store (i.e. it's a PIFLD, not LPMAPIFOLDER), check if the
 *      destination folder object is also within the same store.
 *
 *  Parameters
 *      pifld: The folder that we already know is within this store.
 *      lpDestFld: The folder that we are checking. It may not be in this store.
 *
 *  Returns: BOOL - TRUE means the folders are both in this store.
 *
 */

static BOOL FFoldInSameStore(PIFLD pifld, PIFLD lpDestFld)
{
    if (IsBadWritePtr(lpDestFld, sizeof(IFLD)))
        return FALSE;

    if (lpDestFld->lpVtbl != &vtblIFLD)
        return FALSE;

    if (pifld->pims != lpDestFld->pims)
        return FALSE;

    return TRUE;
}

/***************************************************************************
 *  IFLD_Neuter
 *
 *  Purpose     Free all memory allocated inside a folder object, and release
 *              any objects held inside a folder object. Leaves the object
 *              itself alone (the caller will free it).
 *
 *  Argument    pifld       the folder to be cleaned out.
 *
 */
void IFLD_Neuter(PIFLD pifld)
{
    /* free allocated memory */
    FreeNull(pifld->peid);

    LMFree(&pifld->pims->lmr, pifld->pval);

    /* remove any tables */
    if (pifld->lptblContents)
    {
        TraceSz1("SampleMS (IFLD_Neuter): %d contents table views left",
            pifld->cContentsViews);

        UlRelease(pifld->lptblContents);
        pifld->cContentsViews = 0;
        pifld->lptblContents = NULL;
    }

    if (pifld->lptblHierarchy)
    {
        TraceSz1("SampleMS (IFLD_Neuter): %d hierarchy table views left",
            pifld->cHierarchyViews);

        UlRelease(pifld->lptblHierarchy);
        pifld->cHierarchyViews = 0;
        pifld->lptblHierarchy = NULL;
    }

    return;
}

/*
 -  ViewRelease
 -
 *  Purpose:
 *      Call back function from itable on release of a view
 *      removes the view from the list of open views
 *      releases the table if there are no more open views on it
 *
 *  Parameters
 *       ulCallerData   pointer to folder object
 *       lptbl          pointer to the table on which this is a view
 *       lpvtView       pointer to the view that was released
 *
 *
 */
STDAPI_(void)ViewRelease(ULONG ulCallerData, LPTABLEDATA lptbl,
    LPMAPITABLE lpvtView)
{
    PIFLD pifld;                /* folder object for this view */
    ULONG *pulViewsLeft;        /* ptr to number of open views left */
    LPTABLEDATA *pptbl;         /* ptr to folder's internal table data */

    pifld = (PIFLD) ulCallerData;

    /* do nothing if the folder is invalid. Don't use IFLD_IsInvalid */
    /* because the folder may have already been released, and we still */
    /* want to release the view in that case. */
    if (IsBadWritePtr(pifld, sizeof(IFLD)))
        return;

    IFLD_EnterCriticalSection(pifld);

    /* find the kind of table this view is on */
    if (pifld->lptblContents == lptbl)
    {
        pulViewsLeft = &(pifld->cContentsViews);
        pptbl = &(pifld->lptblContents);
    }
    else if (pifld->lptblHierarchy == lptbl)
    {
        pulViewsLeft = &(pifld->cHierarchyViews);
        pptbl = &(pifld->lptblHierarchy);
    }
    else
    {
        /* invalid table */
        TrapSz("Invalid call to ViewRelease");
        goto exit;
    }

    AssertSz(*pptbl == lptbl, "Different table data given to ViewRelease");

    /* decrement count of views and release*/
    /* the table data if the viewlist is empty */
    if (--(*pulViewsLeft) == 0)
    {
        POBJ pobj = (POBJ) pifld;

        UlRelease(lptbl);
        *pptbl = NULL;

        /* These tests are the same as IFLD_Release in this module. That is */
        /* the release method that folders use. */

        if (    pobj->cRef == 0
            &&  pobj->pobjHead == 0
            &&  pifld->lptblContents == NULL
            &&  pifld->lptblHierarchy == NULL)
        {
            OBJ_Destroy(pobj);  /* will leave the critical section */
            return;
        }

    }

exit:
    IFLD_LeaveCriticalSection(pifld);

    return;
}

/*
 *  HrIsRead
 *
 *  Purpose
 *      Given a parent folder and the entryid of a message, determine
 *      whether the message has been read (i.e., whether the MSGFLAG_READ
 *      bit inside the PR_MESSAGE_FLAGS property is set).
 *
 *  Parameters
 *      pifld       A pointer to the parent folder object of the message.
 *      peidMsg     The entryid of the message.
 *      pfRead      A pointer to the location to return a BOOL saying
 *                  whether or not the message was read. Set to TRUE
 *                  if the message was read, FALSE otherwise.
 */
static HRESULT HrIsRead(PIFLD pifld, PEID peidMsg, BOOL *pfRead)
{
    HRESULT hr;
    PIMSG pimsg = NULL;         /* opened version of lpidMsg */
    ULONG ulObjType;            /* type of object opened */
    ULONG ulMF;

    /* open the message */
    hr = pifld->lpVtbl->OpenEntry(pifld, CbEID(peidMsg), (LPENTRYID) peidMsg,
        NULL, 0L, &ulObjType, (LPUNKNOWN *) &pimsg);
    if (hr != hrSuccess)
        goto exit;

    Assert(ulObjType == MAPI_MESSAGE);

    /* retrieve the PR_MESSAGE_FLAGS property */
    hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pifld->pims->lmr,
            PR_MESSAGE_FLAGS, &ulMF);

    /* set pfRead: no PR_MESSAGE_FLAGS means unread */
    /* The "!!" operator is used to change a bit that is set anywhere in a */
    /* word to exactly TRUE (only one bit set at the far right of the word). */
    /* The first "!" is NOT, which makes all zeros in the value into TRUE, */
    /* and anything else into FALSE. The second "!" reverses that back, so */
    /* that all zeros become FALSE, and anything else becomes TRUE. */

    if (hr == hrSuccess)
        *pfRead = !!(ulMF & MSGFLAG_READ);
    else if (GetScode(hr) == MAPI_E_NOT_FOUND)
    {
        *pfRead = FALSE;
        hr = hrSuccess;
    }

    UlRelease(pimsg);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    DebugTraceResult(HrIsRead, hr);
    return hr;
}

/*
 *  HrRemoveRow
 *
 *  Purpose     remove a row from a contents or hierarchy table
 *
 *  Argument    lptbl       the table whose row is to be deleted
 *              peid        the entryid of row to be deleted. Used to
 *                          generate the instance key.
 *
 */
HRESULT HrRemoveRow(LPTABLEDATA lptbl, PEID peid)
{
    SPropValue valIK;   /* instance key stored in a property value */
    HRESULT hr;

    if (lptbl == NULL)
        return hrSuccess;

    /* make the instance key into a property value */
    valIK.ulPropTag = PR_INSTANCE_KEY;
    valIK.Value.bin.cb = CbEID(peid);
    valIK.Value.bin.lpb = (BYTE *) peid;

    /* delete the row from the table */
    hr = lptbl->lpVtbl->HrDeleteRow(lptbl, &valIK);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    DebugTraceResult(HrRemoveRow, hr);
    return hr;
}

/*
 *  HrUpdateRow
 *
 *  Purpose
 *      alter the row in the table with the given index property
 *      to the properties in the proptag array.  If the index is
 *      not present, a new row is added to the table. The index
 *      property MUST be the first in pPTA.
 *      For contents table, an entry is made only if the object has
 *      been saved (and therefore has a PR_ENTRYID property).
 *
 *  Parameters
 *      pims            A pointer to the message store object.
 *      lptbl           A pointer to the table data object to update.
 *      peid            EntryID of object whose row is to be added
 *      pPTA            array of property tags of properties to appear in
 *                      this row
 *      pft             pointer to the file time to write
 *      ulObjType       MAPI_MESSAGE (for contents table) or MAPI_FOLDER
 *                      (for hierarchy table)
 *
 */
HRESULT HrUpdateRow(PIMS pims, LPTABLEDATA lptbl, PEID peid,
    LPSPropTagArray pPTA, FILETIME *pft, ULONG ulObjType)
{
    SRow srUpdateRow;           /* new table row */
    LPSPropValue pval = NULL;
    LPMAPIPROP lpEntry = NULL;  /* szName as an open mapiprop */
    ULONG ulObjectType;         /* type of object szName is */
    HRESULT hr = hrSuccess;
    ULONG cbEID;                /* number of bytes in lpEntryID */
    ULONG cValues;

    if (lptbl == NULL)
        return hrSuccess;

    cbEID = CbEID(peid);

    /* Don't add a contents table row for unsaved messages */
    if (ulObjType == MAPI_MESSAGE && FIsUnsavedEID(peid))
        goto exit;

    /* open this object. Do not open with MAPI_MODIFY because if the */
    /* store is open read-only, the OpenEntry will fail. */

    hr = ((LPMDB) pims)->lpVtbl->OpenEntry((LPMDB) pims, cbEID,
        (LPENTRYID) peid, NULL, 0L, &ulObjectType, (LPUNKNOWN *) &lpEntry);
    if (hr != hrSuccess)
        goto exit;

    if (ulObjType == MAPI_MESSAGE && FIsUnsavedMsg((PIMSG) lpEntry))
    {
        UlRelease(lpEntry);
        goto exit;
    }

    hr = lpEntry->lpVtbl->GetProps(lpEntry, pPTA, 0, /* ansi */
            &cValues, &pval);

    UlRelease(lpEntry);

    if (HR_FAILED(hr))
        goto exit;

    hr = hrSuccess;             /* ignore warnings */

    Assert(cValues == pPTA->cValues);

    /* add depth if this is a hierarchy table */
    if (ulObjType == MAPI_FOLDER)
    {
        AssertSz(PROP_ID(pval[cValues - 1].ulPropTag) == PROP_ID(PR_DEPTH),
            "Invalid assumption. PR_DEPTH must be last in hier ptags.");

        pval[cValues - 1].ulPropTag = PR_DEPTH;
        pval[cValues - 1].Value.l = 1L;
    }

    /* stamp in the last mod time (based on what's passed in) */
    /* Note assumption of where the proptag is. */

    AssertSz1(pPTA->aulPropTag[MODIFY_INDEX] == PR_LAST_MODIFICATION_TIME,
        "Invalid assumption. PR_LAST_MODIFICATION_TIME must be at "
        "index %d in pPTA.", MODIFY_INDEX);

    pval[MODIFY_INDEX].ulPropTag = PR_LAST_MODIFICATION_TIME;
    pval[MODIFY_INDEX].Value.ft = *pft;

    /* add the row */
    srUpdateRow.cValues = cValues;
    srUpdateRow.lpProps = pval;

    hr = lptbl->lpVtbl->HrModifyRow(lptbl, &srUpdateRow);

    /* Fall through to exit */

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    LMFree(&pims->lmr, pval);

    DebugTraceResult(HrUpdateRow, hr);
    return hr;
}

/*
 * HrCreateFolder
 *
 * This routine searches for a child folder of the given parent folder
 * for a folder with the specified PR_DISPLAY_NAME. If found and the caller
 * wishes to open if exists, then the found folder is opened and returned. If
 * found and the caller doesn't want to open if exists, then the error
 * MAPI_E_COLLISION is returned. If no child folder with the matching display
 * name is found, then a child folder with the correct display name is created
 * and the new folder is returned.
 *
 * Parameters
 *
 * pifldParent: The parent folder in which to search for matching display names,
 *              and, if necessary, to create the child folder.
 * szName:      The display name to search for and to create the child folder
 *              with.
 * szComment:   If a child folder is created, the value to set its PR_COMMENT
 *              property to.
 * fOpenIfExists: If a child folder with a matching PR_DISPLAY_NAME is found,
 *              open the matching folder when this BOOL is TRUE. If this
 *              BOOL is FALSE, and a match is found, return MAPI_E_COLLISION.
 *              If no match is found, this parameter is not referenced.
 * ppifldNew:   The location to return the newly created or opened folder.
 * pfCreated:   The location to return whether this function created or opened
 *              the child folder. Returning TRUE means the folder was created.
 *
 * Errors: memory or disk errors, and MAPI_E_COLLISION.
 *
 */
static HRESULT HrCreateFolder(PIFLD pifldParent, LPSTR szName, LPSTR szComment,
    BOOL fOpenIfExists, PIFLD *ppifldNew, BOOL *pfCreated)
{
    HRESULT hr;
    BOOL fCreated = FALSE;
    PEID peid = NULL;
    PIFLD pifldNew = NULL;
    LPMAPITABLE pmt = NULL;
    PIMS pims = pifldParent->pims;
    ULONG ulRowCount;
    BOOL fFirstSubFld;

    hr = pifldParent->lpVtbl->GetHierarchyTable(pifldParent, 0, &pmt);
    if (hr != hrSuccess)
        goto exit;

    hr = pmt->lpVtbl->GetRowCount(pmt, 0, &ulRowCount);
    if (hr != hrSuccess)
        goto exit;

    fFirstSubFld = (ulRowCount == 0);
        
    if (!fFirstSubFld)
    {
        hr = HrEIDFromDisplayName(pmt, szName, &pims->lmr, &peid);
    
        if (hr != hrSuccess)
            goto exit;
    
        /* If we found a duplicate, and we don't want it, we have an error. */
    
        if ((peid != NULL) && (fOpenIfExists == FALSE))
        {
            hr = ResultFromScode(MAPI_E_COLLISION);
            goto exit;
        }
    }
    
    UlRelease(pmt);
    pmt = NULL;
    
    if (peid == NULL)
    {
        /* //$ Need to handle cleanup of directory and propfile when errors */
        /* //$ occur later in this function... */

        hr = HrCreateFolderStorage(pifldParent, FOLDER_GENERIC, szName,
            szComment, TRUE, pims, &peid);

        if (hr != hrSuccess)
            goto exit;

        fCreated = TRUE;
    }

    /* Create the instance data */
    hr = HrNewIFLD(peid, pims, TRUE, &pifldNew);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetInternalProps(&pims->lmr, cpropIFLDInternal, &(pifldNew->pval),
            &(pifldNew->cval), peid, pifldParent->peid, 0);
    if (hr != hrSuccess)
        goto exit;

    /* update the hierarchy tables, if any */
    if (fCreated)
    {
        if (fFirstSubFld)
        {
            hr = HrSetSubFolderProp(pifldParent, TRUE);
            if (hr != hrSuccess)
                goto exit;
        }

        ChangeTable(pims, pifldParent->peid, peid, MAPI_FOLDER,
            TABLE_ROW_ADDED, TRUE);
    }

    if (pfCreated)
        *pfCreated = fCreated;

    *ppifldNew = pifldNew;

exit:
    UlRelease(pmt);
    LMFree(&pims->lmr, peid);

    if (hr != hrSuccess)
        UlRelease(pifldNew);

    DebugTraceResult(HrCreateFolder, hr);
    return hr;
}

/*
 *  HrIsParent
 *
 *  Purpose
 *      Checks if peidParent is the parent of peidChild. Note that peidChild
 *      may be either a message or a folder entryid. Returns answer
 *      (TRUE or FALSE) in *pfIsParent.
 *
 *  Parameters
 *      peidParent      A pointer to the entryid of the potential parent.
 *      peidChild       A pointer to the entryid of the potential child.
 *      pfIsParent      A pointer to the location to return the answer.
 */
HRESULT HrIsParent(PEID peidParent, PEID peidChild, BOOL *pfIsParent)
{
    SCODE sc = S_OK;
    LPSTR szLastSlash;          /* pointer to last slash in Childs' path */
    BOOL fAnswer = FALSE;
    LPSTR szTemp = NULL;
    ULONG cbPathCopy;

    if (!IsEqualMAPIUID(&(peidParent->uidResource), &(peidChild->uidResource)))
        goto exit;

    szLastSlash = SzFindLastCh(peidChild->szPath, '\\');
    if (szLastSlash == NULL)
    {
        /* if child is the root it can have no parent */
        /* otherwise, check if child lives in the root folder */

        if (*(peidChild->szPath) != '\0')
            fAnswer = (*(peidParent->szPath) == '\0');

        goto exit;
    }

    cbPathCopy = ((szLastSlash - peidChild->szPath) * sizeof(TCHAR))
        + sizeof(TCHAR);

    sc = ScAlloc(cbPathCopy, &szTemp);
    if (sc != S_OK)
        goto exit;

    memcpy(szTemp, peidChild->szPath, (UINT) cbPathCopy);
    szTemp[cbPathCopy - 1] = '\0';

    /* see if paths are the same */
    fAnswer = !lstrcmpi(peidParent->szPath, szTemp);

exit:
    if (sc == S_OK)
        *pfIsParent = fAnswer;

    FreeNull(szTemp);

    DebugTraceSc(HrIsParent, sc);
    return ResultFromScode(sc);
}

/*
 *  FIsAncestor
 *
 *  Purpose
 *      returns TRUE if pifldDescendent is a descendent of pifldAncestor
 *
 *  Parameters
 *      pifldAncestor       the ancestor(?) folder
 *      pifldDescendent     the descendent(?) folder
 *
 */
static BOOL FIsAncestor(PIFLD pifldAncestor, PIFLD pifldDescendent)
{
    PEID peidAncestor;          /* entryID of pifldAncestor */
    PEID peidDescendent;        /* entryID of pifldDescendent */
    LPTSTR szFirstOccurrence = NULL;    /* pointer to first occurrence in */

    /* pifldDescendent's path of */
    /* pifldAncestor's path */

    if (pifldAncestor == NULL || pifldDescendent == NULL)
        return FALSE;

    peidAncestor = pifldAncestor->peid;
    peidDescendent = pifldDescendent->peid;

    if (!IsEqualMAPIUID(&(peidAncestor->uidResource),
            &(peidDescendent->uidResource)))
        return FALSE;

    /* check for either one being the root */
    if (FIsRoot(peidAncestor))
        return TRUE;
    if (FIsRoot(peidDescendent))
        return FALSE;

    szFirstOccurrence = SzFindSz(peidDescendent->szPath,
        peidAncestor->szPath);

    return (BOOL) (szFirstOccurrence == peidDescendent->szPath);
}

/*
 *  HrFullToRelative
 *
 *  Purpose             given a full path name and store, returns the
 *                      root relative path.  Free with FreeNull.
 *
 *  Parameters
 *      szFullPath      the full path
 *      pims            the store object
 *      pszRelative     [out] pointer to the relative path
 *
 *  NB      memory is allocated using ScAlloc and should be freed
 *          with FreeNull
 */
HRESULT HrFullToRelative(LPTSTR szFullPath, PIMS pims, LPTSTR *pszRelative)
{
    ULONG cchStore;     /* length of the store path in tchars */
    ULONG cchFull;      /* length of the full path in tchars */
    SCODE sc;

    cchStore = lstrlen(pims->szStorePath);
    cchFull = lstrlen(szFullPath);

    Assert(cchFull >= cchStore);

    sc = ScAlloc((cchFull - cchStore + sizeof(TCHAR)), (PPV) pszRelative);

    if (sc != S_OK)
    {
        DebugTraceSc(HrFullToRelative, sc);
        return ResultFromScode(sc);
    }

    lstrcpy(*pszRelative, szFullPath + cchStore + 1);

    return hrSuccess;
}

/*
 *  HrFullPathName
 *
 *  Purpose         Allocate space for and return a pointer to the full path
 *                  name of the given object. Free with FreeNull.
 *
 *  Parameters
 *      szStorePath     full path to the store root
 *      szPath1         first portion of path past the store root.
 *                      May be NULL.
 *      szPath2         second portion of path to the object
 *                      whose full path name is needed, may be NULL.
 *      pszName         Pointer to a location to return the full pathname
 *
 *  Returns:
 *      HRESULT
 */
HRESULT HrFullPathName(LPTSTR szStorePath, LPTSTR szPath1, LPTSTR szPath2,
    LPTSTR *pszName)
{
    UINT cbPath1 = 0;           /* length in bytes of first portion of path */

    /* excluding NULL */
    UINT cbPath2 = 0;           /* length in bytes of second portion of path */

    /* excluding NULL */
    UINT cbStorePath = 0;
    SCODE sc;

    Assert(!IsBadWritePtr(pszName, sizeof(LPSTR)));
    Assert(!IsBadStringPtr(szStorePath, (UINT) -1));

    Assert(szPath1 == NULL || !IsBadStringPtr(szPath1, (UINT) -1));
    Assert(szPath2 == NULL || !IsBadStringPtr(szPath2, (UINT) -1));

    cbStorePath = lstrlen(szStorePath) * sizeof(TCHAR);

    if (szPath1 != NULL)
        cbPath1 = lstrlen(szPath1) * sizeof(TCHAR);

    if (szPath2 != NULL)
        cbPath2 = lstrlen(szPath2) * sizeof(TCHAR);

    /* allocate space for the path name */
    sc = ScAlloc(cbStorePath + cbPath1 + cbPath2 + (3 * sizeof(TCHAR)),
        (PPV) pszName);

    if (sc != S_OK)
    {
        DebugTraceSc(HrFullPathName, sc);
        return ResultFromScode(sc);
    }

    /* fill in the name */
    lstrcpy(*pszName, szStorePath);

    if (cbPath1 != 0)
    {
        lstrcat(*pszName, TEXT("\\"));
        lstrcat(*pszName, szPath1);
    }

    if (cbPath2 != 0)
    {
        lstrcat(*pszName, TEXT("\\"));
        lstrcat(*pszName, szPath2);
    }

    return hrSuccess;
}

/*
 -  HrNewEID
 -
 *  Purpose     Return the EID of a new object (folder or message)
 *
 *  Parameters
 *      pifld           Parent folder of object to receive new ID, NULL
 *                      means we need EID of the root folder
 *      pims            Store containing the new object
 *      szExtension     File extension of new object, including '.'
 *      lpulSeqNumber   pointer to sequence number of this entryID (optional)
 *      ppeid           Pointer to pointer to new entryID
 *
 *  Returns:
 *      HRESULT
 */
HRESULT HrNewEID(PIFLD pifld, PIMS pims, LPTSTR szExtension,
    ULONG *lpulSeqNumber, PEID *ppeid)
{
    PEID peidNew = NULL;
    LPSTR szNewPath = NULL;
    HRESULT hr = hrSuccess;
    MAPIUID uid;
    ULONG ulSeq;
    LPSTR szNewObjName = NULL;  /* name of new object */

    Assert(ppeid);
    Assert(pims);

    /* get the new name of the object, and a unique sequence number. */
    hr = HrUniqueFileName(pims, &ulSeq, &szNewObjName);
    if (hr != hrSuccess)
        goto exit;

    /* code in the sample store depends on the number of chars in the */
    /* file / folder name being OK. Verify that it is. */

    Assert(lstrlen(szNewObjName) == CCH_BASE);

    GetResourceUID(pims, &uid);

    if (pifld == NULL)
    {
        CHAR ch = '\0';

        /* Construct the EID for the root folder */
        hr = HrConstructEID(&uid, &pims->lmr, (LPSTR) &ch, &peidNew);
        if (hr != hrSuccess)
            goto exit;
    }
    else
    {
        ULONG cbPath;
        LPSTR szPath = NULL;
        SCODE sc;
        BOOL fIsRoot;

        /* Add 1 TCHAR for the NULL terminator */
        cbPath = (lstrlen(szNewObjName) + lstrlen(szExtension)) * sizeof(TCHAR)
            + sizeof(TCHAR);

        fIsRoot = FIsRoot(pifld->peid);

        if (fIsRoot == FALSE)
        {
            /* Add 1 TCHAR for the slash between the folder and the new name */
            /* Subtract 1 TCHAR because we don't need to count the NULL term */

            cbPath += CbEIDPath(pifld->peid) + sizeof(TCHAR) - sizeof(TCHAR);
        }

        /* allocate space for the new path */
        sc = ScAlloc(cbPath, &szPath);
        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        *szPath = 0;

        if (fIsRoot == FALSE)
        {
            lstrcpy(szPath, pifld->peid->szPath);
            lstrcat(szPath, TEXT("\\"));
        }

        lstrcat(szPath, szNewObjName);
        lstrcat(szPath, szExtension);

        hr = HrConstructEID(&uid, &pims->lmr, szPath, &peidNew);

        FreeNull(szPath);

        if (hr != hrSuccess)
            goto exit;
    }

    *ppeid = peidNew;

    if (lpulSeqNumber)
        *lpulSeqNumber = ulSeq;

    Assert(hr == hrSuccess);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (hr != hrSuccess)
        LMFree(&pims->lmr, peidNew);

    FreeNull(szNewObjName);

    DebugTraceResult(HrNewEID, hr);
    return hr;
}

/*
 * HrOpenPropertyMessage
 *
 *  Purpose         open the property message for the folder with entryid
 *                  pointed to peid
 *
 *  Parameters
 *      peid                pointer to folder's entryid
 *      pims                pointer to the message store object
 *      fModifyExclusive    TRUE if we want to open for read/write,
 *                          exclusive access.
 *      lppmsg              pointer to location to return the open message
 *                          object
 *
 *  Returns: Storage and IMSG errors.
 */
static HRESULT HrOpenPropertyMessage(PEID peid, PIMS pims, BOOL fModifyExclusive,
    LPMESSAGE *lppmsg)
{
    LPTSTR szPropFolderPathName = NULL;
    HRESULT hr;

    /* get full path to message file */
    hr = HrFullPathName(pims->szStorePath, peid->szPath, szPropertyFileName,
        &szPropFolderPathName);
    if (hr != hrSuccess)
        goto exit;

    hr = HrOpenIMsg(pims->pmsgsess, szPropFolderPathName, &pims->lmr,
        pims->psup, FALSE, fModifyExclusive, fModifyExclusive, lppmsg);

    if (hr != hrSuccess)
    {
        if (GetScode(hr) == MAPI_E_NOT_FOUND)
            hr = ResultFromScode(MAPI_E_OBJECT_DELETED);
        goto exit;
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    FreeNull(szPropFolderPathName);

    DebugTraceResult(HrOpenPropertyMessage, hr);
    return hr;
}

/*
 * HrOpenPropertyMessageRetry
 *
 *  Purpose         open the property message for the folder with entryid
 *                  pointed to peid. The function will retry if message is busy
 *                  for the specified number of times.
 *
 *  Parameters
 *      peid                pointer to folder's eid
 *      pims                pointer to the message store object
 *      fModifyExclusive    TRUE if we want to open for read/write,
 *                          exclusive access.
 *      lppmsg              pointer to location to return the open message
 *                          object
 *
 */
HRESULT HrOpenPropertyMessageRetry(PEID peid, PIMS pims,
    BOOL fModifyExclusive, LPMESSAGE *lppmsg)
{
    UINT iRetry;                /* number of attempts to open */
    HRESULT hr = hrSuccess;

    iRetry = 0;
    while (TRUE)
    {
        hr = HrOpenPropertyMessage(peid, pims, fModifyExclusive, lppmsg);

        if (GetScode(hr) != MAPI_E_NO_ACCESS || ++iRetry >= NUM_RETRIES)
            break;

        Sleep(500);
    }

    #ifdef DEBUG
    if (iRetry >= NUM_RETRIES)
        TraceSz("HrOpenPropertyMessageRetry: Failing open. Too many tries.");
    #endif

    DebugTraceResult(HrOpenPropertyMessageRetry, hr);
    return hr;
}

/*
 * HrGetFileModTime
 *
 * Gets the last write time of the file from the OS by calling
 * FindFirstFile, and retrieving it from the FIND_DATA.
 *
 * szStorePath: the path to the message store.
 * szFileName: the relative path to the file.
 * pft: a pointer to the location to return the FILETIME
 *
 */
HRESULT HrGetFileModTime(LPTSTR szStorePath, LPTSTR szFileName,
    FILETIME *pft)
{
    HRESULT hr;
    LPSTR szFullPath;

    hr = HrFullPathName(szStorePath, szFileName, NULL, &szFullPath);

    if (hr == hrSuccess)
    {
        HANDLE hFile;
        WIN32_FIND_DATA ffd;

        hFile = FindFirstFile(szFullPath, &ffd);
    
        if (hFile == FAILED_SEARCH)
            hr = ResultFromScode(MAPI_E_NOT_FOUND);
        else
        {
            *pft = ffd.ftLastWriteTime;
            FindClose(hFile);
        }
    
        FreeNull(szFullPath);
    }

    DebugTraceResult(HrGetFileModTime, hr);
    return hr;
}

/*
 *  HrFindFirstID
 *
 *  Purpose         returns in *ppeid the entryid of the
 *                  first object in pifldParent whose name is of the
 *                  form specified in szTemplate. The caller must free
 *                  storage with CloseIDSearch even in error,
 *                  except *ppeid is always freed with LMFree.
 *
 *  Parameters
 *      pifldParent     parent folder
 *      szTemplate      template local name for object to be found
 *      pichLocal       pointer to variable for position of start of local
 *                      name of the found object
 *      pszRRPath       pointer to root relative path of next object
 *      phFindFile      pointer to location to return search handle
 *      pffd            pointer to location to return Windows find file data
 *                      struct for use by HrFindNextID.
 *      ppeid           pointer to eid of found object
 *
 *  Returns:
 *      HRESULT
 */
HRESULT HrFindFirstID(PIFLD pifldParent, LPTSTR szTemplate, ULONG *pichLocal,
    LPTSTR *pszRRPath, HANDLE *phFindFile, WIN32_FIND_DATA *pffd, PEID *ppeid)
{
    HRESULT hr = hrSuccess;
    MAPIUID uidStore;           /* uid for message store */
    LPTSTR szSubObject = NULL;  /* template name of subobject */
    PEID peid = NULL;
    PLMR plmr;
    LPSTR szRRPath = NULL;
    ULONG ichLocal = 0;
    HANDLE hFindFile = 0;
    WIN32_FIND_DATA ffd;

    plmr = &pifldParent->pims->lmr;

    /* find the first subobject */
    hr = HrFullPathName(pifldParent->pims->szStorePath,
        pifldParent->peid->szPath, szTemplate, &szSubObject);
    if (hr != hrSuccess)
        goto exit;

    hFindFile = FindFirstFile(szSubObject, &ffd);

    if (hFindFile == FAILED_SEARCH)
    {
        hr = ResultFromScode(MAPI_E_NOT_FOUND);
        goto exit;
    }

    /* get components of entryids for messages in this folder */
    GetResourceUID(pifldParent->pims, &uidStore);

    /* get the root relative path */
    hr = HrAlloc(CbEIDPath(pifldParent->peid)
        + (CCH_NAME * sizeof(TCHAR)), (PPV) &szRRPath);
    if (hr != hrSuccess)
        goto exit;

    lstrcpy(szRRPath, pifldParent->peid->szPath);
    if (*szRRPath != (TCHAR) 0)
        lstrcat(szRRPath, TEXT("\\"));

    ichLocal = lstrlen(szRRPath);

    lstrcpy(szRRPath + ichLocal, ffd.cFileName);

    /* construct the ID */
    hr = HrConstructEID(&uidStore, plmr, szRRPath, &peid);
    /* fall through to exit */

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (hr != hrSuccess)
    {
        LMFree(plmr, peid);
        FreeNull(szRRPath);

        if (hFindFile && hFindFile != FAILED_SEARCH)
            FindClose(hFindFile);
    }
    else
    {
        *ppeid = peid;
        *pszRRPath = szRRPath;
        *phFindFile = hFindFile;
        *pichLocal = ichLocal;
        *pffd = ffd;
    }

    FreeNull(szSubObject);

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_E_NOT_FOUND)
        DebugTraceResult(HrFindFirstID, hr);
    #endif

    return hr;
}

/*
 *  HrFindNextID
 *
 *  Purpose         returns in ppeid the eid of the next object in the search
 *                  free *ppeid with LMFree.
 *
 *  Parameters
 *      pifldParent     parent folder
 *      ichLocal        position of start of local name of the found object
 *      szRRPath        name of found object from last search
 *      hFindFile       search handle
 *      pffd            [in/out] pointer to location to use and return
 *                      Windows find file data struct.
 *      ppeid           pointer to location to return eid of next file.
 *
 *  Returns:
 *      HRESULT
 */
HRESULT HrFindNextID(PIFLD pifldParent, ULONG ichLocal, LPTSTR szRRPath,
    HANDLE hFindFile, WIN32_FIND_DATA *lpFindFileData, PEID *ppeid)
{
    HRESULT hr = hrSuccess;
    MAPIUID uidStore;           /* resource uid of store */
    PLMR plmr;
    PEID peid = NULL;

    plmr = &pifldParent->pims->lmr;

    if (FindNextFile(hFindFile, lpFindFileData))
    {
        lstrcpy(szRRPath + ichLocal, lpFindFileData->cFileName);
        GetResourceUID(pifldParent->pims, &uidStore);

        /* construct the ID */
        hr = HrConstructEID(&uidStore, plmr, szRRPath, &peid);
    }
    else
        hr = ResultFromScode(MAPI_E_NOT_FOUND);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (hr != hrSuccess)
        LMFree(plmr, peid);
    else
        *ppeid = peid;

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_E_NOT_FOUND)
        DebugTraceResult(HrFindNextID, hr);
    #endif

    return hr;
}

/*
 *  CloseIDSearch
 *
 *  Purpose         
 *      Calls FindClose on the search handle, and FreeNull on the root-relative
 *      pathname given as arguments. After cleaning up these values, the
 *      function also invalidates the pointers.
 *
 *  Parameters
 *      lphFindFile     pointer to search handle, returned with FAILED_SEARCH.
 *      pszRRPath       pointer to name of found object from last search,
 *                      returned with NULL.
 *
 *  Returns: void.
 */
void CloseIDSearch(HANDLE *lphFindFile, LPTSTR *pszRRPath)
{
    if (lphFindFile && *lphFindFile && *lphFindFile != FAILED_SEARCH)
    {
        FindClose(*lphFindFile);
        *lphFindFile = FAILED_SEARCH;
    }

    FreeNull(*pszRRPath);
    *pszRRPath = NULL;
}

/*
 *  HrNewIFLD
 *
 *  Purpose:
 *      Allocates and initializes new instance data for a folder
 *
 *  Parameters
 *      peid            EID of folder
 *      pims            address of the message store for this folder
 *      fModify         TRUE if caller wants to modify, FALSE otherwise
 *      ppifld          pointer to newly created instance data
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Allocates memory for IFLD object.  Freed by calling Release.
 *
 */
HRESULT HrNewIFLD(PEID peid, PIMS pims, BOOL fModify, PIFLD *ppifld)
{
    SCODE sc;
    PIFLD pifld = NULL;         /* pointer to new instance data */

    Assert(peid);
    Assert(pims);
    Assert(ppifld);

    /* Don't open the folder object unless the directory and the property */
    /* file are present on disk. */

    if (!FFolderExists(peid, pims))
    {
        sc = MAPI_E_NOT_FOUND;
        goto exit;
    }

    /* Allocate memory for the instance data */
    sc = LMAllocZ(&pims->lmr, sizeof(IFLD), &pifld);
    if (sc != S_OK)
        goto exit;

    /* allocate memory to hold the folder's eid */
    sc = ScAllocZ(CbEID(peid), &pifld->peid);
    if (sc != S_OK)
        goto exit;

    Assert(CbEIDPath(peid) == (UINT) Cbtszsize(peid->szPath));

    OBJ_Initialize(pifld, &vtblIFLD, OT_FOLDER, pims, pims->pcs);

    memcpy(pifld->peid, peid, CbEID(peid));

    if (fModify)
        OBJ_SetFlag(pifld, OBJF_MODIFY);

    OBJ_Enqueue((POBJ) pifld, (POBJ) pims);

    *ppifld = pifld;

exit:
    AssertSz(sc == S_OK || FAILED(sc), "No warning expected");

    if (sc != S_OK && pifld)
    {
        FreeNull(pifld->peid);
        LMFree(&pims->lmr, pifld);
    }

    DebugTraceSc(HrNewIFLD, sc);
    return ResultFromScode(sc);
}

/* 
 * FFolderExists
 *
 * Check for the existence of the folder's property file inside the folder
 * passed in. If the file isn't there or we can't get to it, return FALSE.
 * If the file is there, return TRUE.
 *
 * Parameters:
 *      peid -- The entryid of the folder to test.
 *      pims -- a pointer to the message store object.
 *
 * Returns: TRUE if the folder's property file is found.
 *          FALSE in all other cases.
 *
 */
BOOL FFolderExists(PEID peid, PIMS pims)
{
    LPTSTR  szPropFolderPathName = NULL;
    HRESULT hr;
    BOOL    fFolderValid = FALSE;

    /* get full path to message file */
    hr = HrFullPathName(pims->szStorePath, peid->szPath, szPropertyFileName,
        &szPropFolderPathName);

    if (hr == hrSuccess)
    {
        HANDLE hFile;
        WIN32_FIND_DATA ffd;

        hFile = FindFirstFile(szPropFolderPathName, &ffd);
    
        if (hFile != FAILED_SEARCH)
        {
            fFolderValid = TRUE;  /* it's there! */
            FindClose(hFile);
        }
    
        FreeNull(szPropFolderPathName);
    }

    return fFolderValid;
}

/*
 -  HrCreateFolderStorage
 -
 *  Purpose:
 *      Create a new folder directory and its property file
 *
 *  Parameters
 *      pifld               the parent folder of the newly created folder
 *                          If NULL, the new folder is the root folder.
 *      ulFolderType        type of folder to be created
 *      szFolderName        name of the new folder
 *      szFolderComment     comment string for the new folder
 *      fCreateDir          TRUE means create directory for folder
 *      pims                pointer to store in which new folder resides
 *      ppeid               pointer to entryID of new folder
 *
 *  Returns:
 *
 *  Side effects:   Sets PR_COMMENT property to szFolderComment.
 *
 *  Errors:
 *
*/
HRESULT HrCreateFolderStorage(PIFLD pifld, ULONG ulFolderType,
    LPSTR szFolderName, LPSTR szFolderComment, BOOL fCreateDir,
    PIMS pims, PEID *ppeid)
{
    HRESULT hr;
    PEID peid = NULL;
    ULONG ulSeqNumber;          /* sequence number of new folder*/
    SPropValue pvalRO[NUM_RO_FOLDER_PROPS];
    SPropValue pvalRW[NUM_RW_FOLDER_PROPS];
    ULONG cSet;
    LPSPropProblemArray pprba = NULL;
    LPMESSAGE lpmsgProp = NULL; /* property message for this folder */
    BOOL fDirCreated = FALSE;
    BOOL fFolderPropFileCreated = FALSE;

    LPTSTR szNewDirectoryName = NULL;
    LPTSTR szPropertyFolderName = NULL;

    Assert(pims);
    Assert(ppeid);

    hr = HrNewEID(pifld, pims, FOLDER_EXT, &ulSeqNumber, &peid);
    if (hr != hrSuccess)
        goto exit;

    /* create new directory for the new folder object */
    hr = HrFullPathName(pims->szStorePath, peid->szPath, NULL,
        &szNewDirectoryName);
    if (hr != hrSuccess)
        goto exit;

    if (fCreateDir)
    {
        if (!CreateDirectory(szNewDirectoryName, NULL))
        {
            hr = ResultFromScode(MAPI_E_NO_ACCESS);
            goto exit;
        }
        fDirCreated = TRUE;
    }

    hr = HrFullPathName(pims->szStorePath, peid->szPath,
        szPropertyFileName, &szPropertyFolderName);
    if (hr != hrSuccess)
        goto exit;

    /* create and open the message object for properites */
    hr = HrOpenIMsg(pims->pmsgsess, szPropertyFolderName, &pims->lmr,
        pims->psup, TRUE, TRUE, TRUE, &lpmsgProp);

    if (hr != hrSuccess)
        goto exit;

    fFolderPropFileCreated = TRUE;

    /* set the initial read only properties */

    pvalRO[0].ulPropTag = sptaReadOnly.aulPropTag[0];
    pvalRO[1].ulPropTag = sptaReadOnly.aulPropTag[1];
    pvalRO[2].ulPropTag = sptaReadOnly.aulPropTag[2];
    pvalRO[3].ulPropTag = sptaReadOnly.aulPropTag[3];
    pvalRO[4].ulPropTag = sptaReadOnly.aulPropTag[4];
    pvalRO[5].ulPropTag = sptaReadOnly.aulPropTag[5];
    pvalRO[6].ulPropTag = sptaReadOnly.aulPropTag[6];
    pvalRO[7].ulPropTag = sptaReadOnly.aulPropTag[7];
    pvalRO[8].ulPropTag = sptaReadOnly.aulPropTag[8];
    pvalRO[9].ulPropTag = sptaReadOnly.aulPropTag[9];
    pvalRO[10].ulPropTag = sptaReadOnly.aulPropTag[10];

    pvalRO[0].Value.l = MAPI_FOLDER;
    pvalRO[1].Value.bin.cb = sizeof(ULONG);
    pvalRO[1].Value.bin.lpb = (BYTE *) &ulSeqNumber;
    pvalRO[2].Value.l = (pifld == NULL) ? FOLDER_ROOT : FOLDER_GENERIC;
    pvalRO[3].Value.l = 0;
    pvalRO[4].Value.l = 0;

    pvalRO[5].Value.bin.cb = pims->eidStore.cb;
    pvalRO[5].Value.bin.lpb = pims->eidStore.lpb;

    pvalRO[6].Value.bin.cb = sizeof(pims->uidResource);
    pvalRO[6].Value.bin.lpb = (LPBYTE) &pims->uidResource;

    pvalRO[7].Value.b = FALSE;

    /* Set PR_ENTRYID, PR_PARENT_ENTRYID and PR_INSTANCE_KEY to null */
    /* strings to keep clients from writing over them. */
    /* We get the actual values internally. */

    pvalRO[8].Value.bin.cb = 1;
    pvalRO[8].Value.bin.lpb = (LPBYTE) "";

    pvalRO[9].Value.bin.cb = 1;
    pvalRO[9].Value.bin.lpb = (LPBYTE) "";

    pvalRO[10].Value.bin.cb = 1;
    pvalRO[10].Value.bin.lpb = (LPBYTE) "";

    /* set these read only props */
    hr = lpmsgProp->lpVtbl->SetProps(lpmsgProp, NUM_RO_FOLDER_PROPS,
        pvalRO, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    Assert(sptaReadOnly.cValues == NUM_RO_FOLDER_PROPS);
    Assert(spaReadOnly.cValues == NUM_RO_FOLDER_PROPS);

    hr = SetAttribIMsgOnIStg(lpmsgProp, (LPSPropTagArray) &sptaReadOnly,
        (LPSPropAttrArray) &spaReadOnly, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    /* set the read write properties */

    cSet = NUM_RW_FOLDER_PROPS;

    pvalRW[0].ulPropTag = PR_DISPLAY_NAME;

    /* must be last since it is optional */
    pvalRW[1].ulPropTag = PR_COMMENT;

    pvalRW[0].Value.LPSZ = szFolderName;
    if (szFolderComment != NULL)
        pvalRW[1].Value.LPSZ = szFolderComment;
    else
        cSet--;

    /* set the ReadWrite properties */

    hr = lpmsgProp->lpVtbl->SetProps(lpmsgProp, cSet, pvalRW, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    hr = lpmsgProp->lpVtbl->SaveChanges(lpmsgProp, 0);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(lpmsgProp);

    /* free the property problem structure */
    if (pprba)
    {
        LMFree(&pims->lmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    if (hr != hrSuccess)
    {
        LMFree(&pims->lmr, peid);

        if (fFolderPropFileCreated == TRUE)
            DeleteFile(szPropertyFolderName);

        if (fDirCreated == TRUE)
            RemoveDirectory(szNewDirectoryName);
    }
    else
        *ppeid = peid;

    FreeNull(szNewDirectoryName);
    FreeNull(szPropertyFolderName);

    DebugTraceResult(HrCreateFolderStorage, hr);
    return hr;
}

/*
 *  HrIncrementOneROProp
 *
 *  Purpose     increment the read only property by delta. Only works on
 *              properties of type PT_LONG.
 *
 *  Argument    pifld   pointer to the folder object
 *              lDelta  size of increment
 *              ulPT    the property tag to be changed
 */
HRESULT HrIncrementOneROProp(PIFLD pifld, LONG lDelta, ULONG ulPT)
{
    LONG lValue;
    HRESULT hr;
    LPMESSAGE lpmsg = NULL; /* property message for pifld */
    PLMR plmr = &pifld->pims->lmr;

    AssertSz1(PROP_TYPE(ulPT) == PT_LONG,
        "Trying to increment property %s; not PT_LONG",
        SzDecodeUlPropTag(ulPT));

    /* open the property message exclusively */
    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims,
        TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    /* get the current value of the properties */

    hr = HrGetSingleProp((LPMAPIPROP) lpmsg, plmr, ulPT, &lValue);
    if (hr != hrSuccess)
        goto exit;

    lValue += lDelta;

    /* reset the new value */

    hr = HrSetOneROProp(lpmsg, plmr, ulPT, &lValue);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, FORCE_SAVE);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(lpmsg);

    DebugTraceResult(HrIncrementOneROProp, hr);
    return hr;
}

/*
 *  HrSetOneROFolderProp
 *
 *  Purpose     set the read only folder property to the value given. The
 *              property must be of type PT_LONG.
 *
 *  Argument    pifld   pointer to the folder object
 *              lValue  value to set the property to.
 *              ulPT    the property tag to be changed
 */
static HRESULT HrSetOneROFolderProp(PIFLD pifld, LONG lValue, ULONG ulPT)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL; /* property message for pifld */
    PLMR plmr = &pifld->pims->lmr;

    AssertSz1(PROP_TYPE(ulPT) == PT_LONG,
        "Trying to increment property %s; not PT_LONG",
        SzDecodeUlPropTag(ulPT));

    /* open the property message exclusively */
    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims,
        TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    /* reset the new value */

    hr = HrSetOneROProp(lpmsg, plmr, ulPT, &lValue);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, FORCE_SAVE);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(lpmsg);

    DebugTraceResult(HrSetOneROFolderProp, hr);
    return hr;
}

/*
 *  HrSetSubFolderProp
 *
 *  Purpose     set the PR_SUBFOLDERS property
 *
 *  Argument    pifld       pointer to the folder object
 *              fSubFolder  the value to write into the PR_SUBFOLDER property
 */
static HRESULT HrSetSubFolderProp(PIFLD pifld, BOOL fSubFolder)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL; /* property message for pifld */
    PIFLD pifldParent = NULL;
    PLMR plmr = &pifld->pims->lmr;
    PEID peid = pifld->peid;

    /* open the property message exclusively */
    hr = HrOpenPropertyMessageRetry(peid, pifld->pims, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    /* set the new value */

    hr = HrSetOneROProp(lpmsg, plmr, PR_SUBFOLDERS, &fSubFolder);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, FORCE_SAVE);
    if (hr != hrSuccess)
        goto exit;

    UlRelease(lpmsg);
    lpmsg = NULL;

    /* If this isn't the root folder, get the parent entryid, and call */
    /* ChangeTable so that any new properties are updated in its */
    /* hierarchy table row. */

    if (FIsRoot(peid) == FALSE)
    {
        PEID peidParent = NULL;
        PIMS pims = pifld->pims;

        hr = HrGetParentEID(&pims->lmr, pifld->peid, &peidParent);
        if (hr == hrSuccess)
        {
            ChangeTable(pims, peidParent, peid, MAPI_FOLDER,
                TABLE_ROW_MODIFIED, TRUE);
            LMFree(&pims->lmr, peidParent);
        }
        else
        {
            TraceSz1("Sample MS: HrSetSubFolderProp: failed to change "
                "hierarchy table. sc == %s\n", SzDecodeScode(GetScode(hr)));
            hr = hrSuccess;
        }
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(lpmsg);
    UlRelease(pifldParent);

    DebugTraceResult(HrSetSubFolderProp, hr);
    return hr;
}

/*
 *  ChangeTable
 *
 * Purpose
 *  Changes all contents or hierarchy tables in all open folders to reflect
 *  the change specified. Also updates the folder's content and unread counts.
 *  Never updates the table on disk. That will happen when the table is
 *  read-in and verified.
 *
 *  Parameters
 *
 *      pims            Pointer to the message store object.
 *      peidTable       EID of the parent folder of the table to change
 *      peidObject      the object that has been added or deleted or modified.
 *                      May be NULL if ulTableEvent is TABLE_CHANGED. This 
 *                      means multiple items changed.
 *      ulObjType       MAPI_MESSAGE (for contents tables) or MAPI_FOLDER
 *                      (for hierarchy tables)
 *      ulTableEvent    either TABLE_ROW_ADDED, DELETED, MODIFIED, or
 *                      TABLE_CHANGED (TABLE_CHANGED for contents tables only)
 *      fSendNotif      TRUE if this routine should send notifications to
 *                      other processes about this change.
 *
 */
void ChangeTable(PIMS pims, PEID peidTable, PEID peidObject,
    ULONG ulObjType, ULONG ulTableEvent, BOOL fSendNotif)
{
    HRESULT hr = hrSuccess;
    ULONG cbEIDTable;
    LPSPropTagArray pPTA;       /* proptags of column headings */
    POBJ pobj;

    Assert(pims);
    Assert(peidTable);
    AssertSz1(ulTableEvent == TABLE_ROW_ADDED
        || ulTableEvent == TABLE_ROW_MODIFIED
        || ulTableEvent == TABLE_ROW_DELETED
        || ulTableEvent == TABLE_CHANGED, "Bad ulTableEvent %08lX",
        ulTableEvent);
    AssertSz1(ulObjType == MAPI_MESSAGE || ulObjType == MAPI_FOLDER,
        "Bad ulObjType %08lX", ulObjType);

    /*
     * Look for all open tables within this process. We find them
     * by search the open object chain for folders whose entryids match
     * the eid of the folder passed in. We only update open tables.
     * Therefore, don't bother checking objects that aren't folders or 
     * folder objects without open tables.
     */
    cbEIDTable = CbEID(peidTable);

    for (pobj = pims->pobjHead; pobj != NULL; pobj = pobj->pobjNext)
    {
        PIFLD pifld;
        ULONG ulTheSame;
        LPTABLEDATA lptbl;
        FILETIME ft;

        if (pobj->wType != OT_FOLDER)
            continue;

        pifld = (PIFLD) pobj;

        if (ulObjType == MAPI_MESSAGE)
        {
            pPTA = (LPSPropTagArray) &sPropTagsContents;
            lptbl = pifld->lptblContents;
        }
        else
        {
            pPTA = (LPSPropTagArray) &sPropTagsHierarchy;
            lptbl = pifld->lptblHierarchy;
        }

        if (lptbl == NULL)
            continue;

        hr = pims->lpVtbl->CompareEntryIDs(pims, cbEIDTable,
                (LPENTRYID) peidTable, CbEID(pifld->peid),
                (LPENTRYID) pifld->peid, 0L, &ulTheSame);
        if (hr != hrSuccess)
            goto exit;

        if (!ulTheSame)
            continue;

        switch (ulTableEvent)
        {
        case TABLE_CHANGED:
            if (ulObjType != MAPI_MESSAGE)
            {
                TrapSz("ChangeTable doesn't handle TABLE_CHANGED on"
                    " hierarchy tables");
                goto exit;
            }

            /* Don't update the file on disk. */
            hr = HrSyncContentsTable(pifld, FALSE);
            if (hr != hrSuccess)
                goto exit;
            break;

        case TABLE_ROW_DELETED:
            hr = HrRemoveRow(lptbl, peidObject);
            if (hr != hrSuccess)
            {
                if (GetScode(hr) == MAPI_E_NOT_FOUND)
                    hr = hrSuccess;
                else
                    goto exit;
            }
            break;

        case TABLE_ROW_ADDED:
        case TABLE_ROW_MODIFIED:
            hr = HrGetFileModTime(pims->szStorePath, peidObject->szPath, &ft);
            if (hr != hrSuccess)
                goto exit;

            hr = HrUpdateRow(pims, lptbl, peidObject, pPTA, &ft, ulObjType);
            if (hr != hrSuccess)
                goto exit;
            break;

        default:
            /* We've already asserted this above. */
            goto exit;
        }
    }

    if (fSendNotif)
        hr = HrSendNotif(pims, peidTable, peidObject, ulTableEvent, ulObjType);

exit:
    if (hr != hrSuccess)
        TraceSz1("SampleMS: ChangeTable: failed to update "
            "table. Error %s.\n", SzDecodeScode(GetScode(hr)));

    return;
}

/*
 *  HrDestroyFolderStorage
 *
 *  Purpose         Removes storage associated with a folder
 *
 *  Parameters
 *
 *      szFullPath  full path name of the folder to be removed
 *
 */
HRESULT HrDestroyFolderStorage(LPTSTR szFullPath)
{
    HRESULT hr;
    LPTSTR szAll = NULL;    /* path to all files in the folder */
    HANDLE hFile;
    WIN32_FIND_DATA ffd;

    /* Find all files in the directory, and attempt to delete them. */
    /* Note that if somehow a subdirectory was created in this directory, */
    /* this function will fail. The loop below (that deletes files) goes */
    /* ahead regardless of error until it has tried to delete all files. */
    /* The only fatal error occurs if we can't remove the directory itself. */

    hr = HrAppendPath(szFullPath, szAllFilesTemplate, &szAll);
    if (hr != hrSuccess)
        goto exit;

    hFile = FindFirstFile(szAll, &ffd);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        while (TRUE)
        {
            LPTSTR szTemp = NULL;

            /* Don't even attempt to delete directories. The directories */
            /* named "." and ".." are always included in the contents of */
            /* a directory listing, and this avoids the attempt to delete */
            /* them. */

            if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                if (HrAppendPath(szFullPath, ffd.cFileName, &szTemp)
                    == hrSuccess)
                {
                    DeleteFile(szTemp);
                    FreeNull(szTemp);
                }
            }
    
            if (!FindNextFile(hFile, &ffd))
            {
                FindClose(hFile);
                break;
            }
        }
    }

    /* Attempt to delete the folder itself. */
    if (!RemoveDirectory(szFullPath))
        hr = ResultFromScode(MAPI_E_NO_ACCESS);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    FreeNull(szAll);

    DebugTraceResult(HrDestroyFolderStorage, hr);
    return hr;
}

/*
 *  HrFillHierarchyTable
 *
 *  Purpose     Construct table data for hierarchy below the folder pifld
 *
 *  Argument
 *              pifld       pointer to the folder to be added to
 *                          the hierarchy table.
 *              lptbl       underlying table data
 *
 */
static HRESULT HrFillHierarchyTable(PIFLD pifld, LPTABLEDATA lptbl)
{
    HRESULT hr;
    PEID peidSub = NULL;
    LPTSTR szSubFolder = NULL;  /* template for subfolder of szFolder */
    HANDLE hFindFile = FAILED_SEARCH;
    ULONG ichLocal;
    WIN32_FIND_DATA ffd;
    PIMS pims = pifld->pims;

    /* build a hierarchy entry for each subfolder */
    hr = HrFindFirstID(pifld, szFolderTemplate, &ichLocal,
        &szSubFolder, &hFindFile, &ffd, &peidSub);

    while (hr == hrSuccess)
    {
        /* build hierarchy entry for this subfolder */
        hr = HrUpdateRow(pims, lptbl, peidSub,
            (LPSPropTagArray) &sPropTagsHierarchy,
            &(ffd.ftLastWriteTime), MAPI_FOLDER);
        if (hr != hrSuccess)
            goto exit;

        LMFree(&pims->lmr, peidSub);
        peidSub = NULL;

        hr = HrFindNextID(pifld, ichLocal, szSubFolder,
            hFindFile, &ffd, &peidSub);
    }

    if (GetScode(hr) == MAPI_E_NOT_FOUND)
        hr = hrSuccess;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    /* close the search */
    CloseIDSearch(&hFindFile, &szSubFolder);
    LMFree(&pims->lmr, peidSub);

    DebugTraceResult(HrFillHierarchyTable, hr);
    return hr;
}

/*
 * HrDuplicateIFLD
 *
 *  Searches the existing subfolders of pifldParent for a folder with
 *  PR_DISPLAY_NAME of szName. If it finds a match, opens it and returns
 *  the matching folder (doing nothing else). If no folder matches, then
 *  the routine creates a new folder and copies all properties from the
 *  old folder into the new folder.
 *
 *      pifld           the old folder
 *      pifldParent     parent of the new folder
 *      szName          name of new folder
 *      szComment       comment for new folder
 *      ppifldNew       pointer to the location to return the new folder
 *
 */
static HRESULT HrDuplicateIFLD(PIFLD pifld, PIFLD pifldParent, LPTSTR szName,
    LPTSTR szComment, PIFLD *ppifldNew)
{
    HRESULT hr = hrSuccess;
    BOOL fCreated = FALSE;
    PIFLD pifldNew = NULL;

    /* create new folder */

    hr = HrCreateFolder(pifldParent, szName, szComment, TRUE, &pifldNew,
        &fCreated);
    if (hr != hrSuccess)
        goto exit;

    /* copy pifld's properties over except excluded stuff (see */
    /* sptaExclFldProps definition). */

    if (fCreated)
    {
        LPSPropProblemArray pprba = NULL;
        LPMESSAGE lpmsgPropSrc = NULL;  /* pifld's property message */
        LPMESSAGE lpmsgPropNew = NULL;  /* new ifld's property message */

        hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims, FALSE,
                &lpmsgPropSrc);

        if (hr == hrSuccess)
            hr = HrOpenPropertyMessageRetry(pifldNew->peid,
                    pifldNew->pims, TRUE, &lpmsgPropNew);

        if (hr == hrSuccess)
            hr = lpmsgPropSrc->lpVtbl->CopyTo(lpmsgPropSrc, 0, NULL,
                    (LPSPropTagArray) &sptaExclFldProps, 0, NULL,
                    (LPIID) &IID_IMessage, lpmsgPropNew, 0L, &pprba);

        UlRelease(lpmsgPropSrc);
        UlRelease(lpmsgPropNew);

        if (pprba)
        {
            Assert(hr == hrSuccess);
            LMFree(&pifld->pims->lmr, pprba);
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
        }
    }

    if (hr != hrSuccess)
        goto exit;

    *ppifldNew = pifldNew;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    DebugTraceResult(HrDuplicateIFLD, hr);
    return hr;
}

/*
 -  HrGetSortOrder
 -
 *  Purpose:
 *      returns in *lppsSortOrder the order of contents tables.
 *      Caller must use MAPIFreeBuffer to release *lppsSortOrder.
 *
 *  Parameters
 *       pifld          folder whose contents table is referred to
 *       lppsSortOrder  pointer to sort order variable
 *
 *  Returns:
 *      HRESULT
 *
 */
static HRESULT HrGetSortOrder(PIFLD pifld, LPSSortOrderSet *lppsSortOrder)
{
    ULONG cValues;              /* number of property values returned */
    LPSPropValue pval = NULL;   /* returned property array */
    HRESULT hr;
    ULONG cbSos;                /* number of bytes in sort order */
    SCODE sc;
    static SizedSPropTagArray(1, sptaSortOrder) =
    {
        1,
        {
            PR_SMS_CONTENTS_SORT_ORDER
        }
    };

    Assert(pifld);
    Assert(lppsSortOrder);

    /* get the sort order property */
    hr = pifld->lpVtbl->GetProps(pifld,
        (LPSPropTagArray) &sptaSortOrder, 0, /* ansi */
        &cValues, &pval);

    if (hr != hrSuccess)
    {
        Assert(HR_FAILED(hr) || GetScode(hr) == MAPI_W_ERRORS_RETURNED);
        cbSos = CbSSortOrderSet((LPSSortOrderSet) &sSortOrderContentsDefault);

        /* sort order is the default */
        sc = LMAlloc(&pifld->pims->lmr, cbSos, lppsSortOrder);
        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        memcpy(*lppsSortOrder, &sSortOrderContentsDefault, (UINT) cbSos);
    }
    else
    {
        /* This property should contain a flattened array of */
        /* SSortOrder structures. */

        Assert(cValues == 1L);
        cbSos = sizeof(ULONG) * pval->Value.MVl.cValues;

        sc = LMAlloc(&pifld->pims->lmr, offsetof(SSortOrderSet, aSort) + cbSos,
            lppsSortOrder);
        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        (*lppsSortOrder)->cSorts = pval->Value.MVl.cValues / 2;
        (*lppsSortOrder)->cCategories = 0;
        (*lppsSortOrder)->cExpanded = 0;
        memcpy((*lppsSortOrder)->aSort, pval->Value.MVl.lpl, (UINT) cbSos);
    }
    hr = hrSuccess;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    LMFree(&pifld->pims->lmr, pval);
    DebugTraceResult(HrGetSortOrder, hr);
    return hr;
}

/*
 -  DestroyMessageList
 -
 *  Purpose:
 *      frees allocated memory inside lppEntryList. The cValues field
 *      inside the entrylist must contain the count of the number of
 *      entryids that are in the entrylist so that the entryids can be
 *      freed.
 *
 *  Parameters
 *       lppEntryList   pointer to a list of entryids; returned NULL
 *
 */
static void DestroyMessageList(PLMR plmr, LPENTRYLIST *lppEntryList)
{
    Assert(lppEntryList);

    if (*lppEntryList != NULL && (*lppEntryList)->lpbin != NULL)
    {
        ULONG cValues = (*lppEntryList)->cValues;
        LPSBinary lpbin = (*lppEntryList)->lpbin;

        Assert(cValues <= UINT_MAX / sizeof(SBinary));
        Assert(!IsBadReadPtr(lpbin, (UINT) cValues * sizeof(SBinary)));

        for (; cValues; cValues--, lpbin++)
        {
            Assert(lpbin->cb <= UINT_MAX);
            Assert(!IsBadReadPtr(lpbin->lpb, (UINT) lpbin->cb));
            LMFree(plmr, lpbin->lpb);
        }

        FreeNull(*lppEntryList);
    }

    *lppEntryList = NULL;
    return;
}

/*
 -  HrCreateMessageList
 -
 *  Purpose:
 *      Counts up and returns a list of entryids for every message in
 *      the given folder. If no messages are found in the folder, returns
 *      NULL instead of the list. To get the count, this routine uses
 *      FindFirstFile, FindNextFile on all files with a ".msg" extension.
 *      We use PR_CONTENT_COUNT to get an estimate of how many msgs are in
 *      the folder, but don't depend on that property being correct. If
 *      the property is incorrect, this routine updates it (SIDE EFFECT)
 *      before returning to the caller.
 *
 *  Parameters
 *       pifld          the folder object
 *       lppEntryList   [out] pointer to the location to return a list of
 *                      entryids of messages in pifld.
 *
 */
static HRESULT HrCreateMessageList(PIFLD pifld, LPENTRYLIST *lppEntryList)
{
    HRESULT hr;
    LONG cMsgsOrig;             /* value of PR_CONTENT_COUNT property */
    LONG cMsgsAlloced;          /* number of msgs allocated in pent->lpbin */
    ULONG ichLocal;             /* start of message name in full path name */
    LPSBinary lpbin;
    LPSBinary lpbinMac;

    PEID peidNext = NULL;       /* next entryID to be added to the list */
    WIN32_FIND_DATA ffd;
    LPTSTR szFile = NULL;
    HANDLE hFindFile = FAILED_SEARCH;
    LPENTRYLIST pent = NULL;

    /* get the number of messages in pifld */
    /* This value may be incorrect, so use it to simply get an idea */
    /* of how many messages are in the folder. Allocate extra space */
    /* for extra (uncounted) messages, and, if necessary, realloc */
    /* the array until we really count all of them. After we've counted */
    /* all messages, update PR_CONTENT_COUNT with the correct number. */
    /* Assuming that there are extra messages in the folder avoids having */
    /* to realloc the array as often when there actually are extra ones. */

#define CMSGS_EXTRA     10  /* # of extra spaces to alloc in msg array */

    hr = HrGetSingleProp((LPMAPIPROP) pifld, &pifld->pims->lmr,
            PR_CONTENT_COUNT, &cMsgsOrig);

    /* Don't allow the failure to get PR_CONTENT_COUNT to keep this call */
    /* from succeeding. Go ahead and do the call anyway. */

    if (hr != hrSuccess)
    {
        hr = hrSuccess;

        /* We failed to get the property. Set the "original value" */
        /* to an impossible value so that we will attempt to update it */
        /* at the bottom of this function. */

        cMsgsOrig = -1;
        cMsgsAlloced = CMSGS_EXTRA;
    }
    else
        cMsgsAlloced = cMsgsOrig + CMSGS_EXTRA;

    /* Allocate space for the entrylist. */

    hr = HrAlloc(sizeof(SBinaryArray) + (cMsgsAlloced * sizeof(SBinary)),
        &pent);
    if (hr != hrSuccess)
        goto exit;

    /* We allocated the space all at once; therefore, we initialize the */
    /* lpbin pointer to point just past the binary array. */

    pent->lpbin = (LPSBinary) ((LPBYTE) pent + sizeof(SBinaryArray));

    /* The cValues field of the entrylist must be kept up-to-date as we */
    /* add entryids to the entrylist. DestroyMessageList (see above) uses */
    /* that field when it frees up the entryids, and if it is wrong, the */
    /* wrong number of entryids will get freed (resulting in a crash if */
    /* it is too big, or a memory leak if it is too small). */

    pent->cValues = 0;

    lpbin = pent->lpbin;
    lpbinMac = lpbin + cMsgsAlloced;

    /* get the first entryID */
    hr = HrFindFirstID(pifld, szMessageTemplate, &ichLocal,
        &szFile, &hFindFile, &ffd, &peidNext);

    if (hr != hrSuccess)
    {
        /* MAPI_E_NOT_FOUND means that there are no more messages in */
        /* the folder. This is not an error. Because this was the first */
        /* file, there were no messages in the folder at all. Therefore, */
        /* free any allocated memory, reset hr, and get out. */

        if (GetScode(hr) == MAPI_E_NOT_FOUND)
        {
            DestroyMessageList(&pifld->pims->lmr, &pent);

            /* pent should be NULL now. We're going to return it to */
            /* our caller below. */

            AssertSz(pent == NULL, "DestroyMessageList is broken.");

            hr = hrSuccess;
        }

        goto exit;
    }

    while (TRUE)
    {
        lpbin->cb = CbEID(peidNext);
        lpbin->lpb = (LPBYTE) peidNext;

        ++(pent->cValues);

        hr = HrFindNextID(pifld, ichLocal, szFile, hFindFile, &ffd, &peidNext);

        if (hr != hrSuccess)
        {
            /* MAPI_E_NOT_FOUND means that there are no more messages in */
            /* the folder. This is not an error. */

            if (GetScode(hr) == MAPI_E_NOT_FOUND)
                hr = hrSuccess;

            goto exit;
        }

        lpbin++;

        if (lpbin >= lpbinMac)
        {
            /* We need to realloc the array. */
            cMsgsAlloced += CMSGS_EXTRA;

            hr = HrRealloc((cMsgsAlloced * sizeof(SBinary))
                + sizeof(SBinaryArray), pent, &pent);
            if (hr != hrSuccess)
                goto exit;

            /* reset the pointer to the end of the array. */
            lpbinMac = pent->lpbin + cMsgsAlloced;
        }
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    /* close the search */
    CloseIDSearch(&hFindFile, &szFile);

    if (hr == hrSuccess)
    {
        LONG cMsgsFound = 0;

        /* If PR_CONTENT_COUNT was incorrect, then update it. Note that */
        /* the number of messages we found is kept in pent->cValues unless */
        /* we didn't find any messages (in which case, pent is NULL, and */
        /* we assume no messages were found). */

        if (pent)
            cMsgsFound = pent->cValues;

        if (cMsgsFound != cMsgsOrig)
            (void) HrSetOneROFolderProp(pifld, cMsgsFound, PR_CONTENT_COUNT);

        *lppEntryList = pent;
    }
    else if (pent)
        DestroyMessageList(&pifld->pims->lmr, &pent);

    DebugTraceResult(HrCreateMessageList, hr);
    return hr;
}

/*
 -  HrDeleteSubDirectory
 -
 *  Purpose:
 *      Delete a subdirectory of the current directory
 *
 *  Parameters
 *       pifldParent    parent folder of folder to delete
 *       peid           entryid of folder to be deleted
 *       ulFlags        DEL_FOLDERS and/or DEL_MESSAGES
 *       fContentsOnly  BOOL. If TRUE, don't delete peid itself.
 *
 *  Side effects:
 *      If either flag is set, it deletes all that it can before returning.
 *      It is possible for the subdirectory to fail at being deleted but to
 *      have some of its contents removed.
 *
 */
static HRESULT HrDeleteSubDirectory(PIFLD pifldParent, PEID peidToDelete,
    ULONG ulFlags, BOOL fContentsOnly)
{

    HANDLE hFindFile = FAILED_SEARCH;
    LPTSTR szToDelete = NULL;   /* full path name of subdir to be deleted */
    PEID peidSubDir = NULL;     /* eid of subdirectory */
    PIFLD pifldToDelete = NULL; /* opened subdirectory to delete */
    ULONG ulOffset;             /* start of local name of subdir in szSubDir */
    ULONG ulObjType;
    LPENTRYLIST lpMessages = NULL;  /* list of messages to be deleted */
    LPTSTR szRelativePath = NULL;   /* relative path for id searches */
    WIN32_FIND_DATA ffd;
    HRESULT hr = hrSuccess;
    PIMS pims = pifldParent->pims;

    hr = HrFullPathName(pims->szStorePath, peidToDelete->szPath,
        NULL, &szToDelete);
    if (hr != hrSuccess)
        goto exit;

    /* open up the folder to be deleted */
    hr = pifldParent->lpVtbl->OpenEntry(pifldParent, CbEID(peidToDelete),
        (LPENTRYID) peidToDelete, NULL, MAPI_MODIFY,
        &ulObjType, (LPUNKNOWN *) &pifldToDelete);

    if (hr != hrSuccess)
        goto exit;

    if (!(ulFlags & DEL_FOLDERS))
    {
        /* The caller didn't specify DEL_FOLDERS. Check to make sure that */
        /* there aren't any subfolders before allowing the deletion to */
        /* continue. If there are subfolders, return MAPI_E_HAS_FOLDERS. */

        /* Look for any subfolders */

        hr = HrFindFirstID(pifldToDelete, szFolderTemplate, &ulOffset,
            &szRelativePath, &hFindFile, &ffd, &peidSubDir);

        CloseIDSearch(&hFindFile, &szRelativePath);

        if (hr == hrSuccess)
        {
            /* release the eid */
            LMFree(&pims->lmr, peidSubDir);
            peidSubDir = NULL;

            hr = ResultFromScode(MAPI_E_HAS_FOLDERS);
            goto exit;
        }
        else if (GetScode(hr) != MAPI_E_NOT_FOUND)
            goto exit;

        hr = hrSuccess;
    }
    else
    {
        /* set up the search for subdirectories */
        hr = HrFindFirstID(pifldToDelete, szFolderTemplate, &ulOffset,
            &szRelativePath, &hFindFile, &ffd, &peidSubDir);
    
        /* Delete each subdirectory*/
        while (hr == hrSuccess)
        {
            hr = HrDeleteSubDirectory(pifldToDelete, peidSubDir, ulFlags, FALSE);
    
            /* release the eid */
            LMFree(&pims->lmr, peidSubDir);
            peidSubDir = NULL;
    
            /* Errors returned from HrDeleteSubDirectory should be fatal. */
            /* Don't ignore them, because if we do, then we will leave a */
            /* corrupt message store behind. MAPI_E_HAS_MESSAGES can come */
            /* back from below, as well as MAPI_E_SUBMITTED, etc. */

            if (hr != hrSuccess)
                goto exit;

            /* Delete the other subdirectories */
            hr = HrFindNextID(pifldToDelete, ulOffset, szRelativePath,
                hFindFile, &ffd, &peidSubDir);
        }
    
        if (GetScode(hr) == MAPI_E_NOT_FOUND)
            hr = hrSuccess;
        else
            goto exit;
    
        /* end the search */
        CloseIDSearch(&hFindFile, &szRelativePath);
    }

    /* delete all messages if DEL_MESSAGES */
    hr = HrCreateMessageList(pifldToDelete, &lpMessages);
    if (hr != hrSuccess)
        goto exit;

    if (lpMessages && !(ulFlags & DEL_MESSAGES))
    {
        hr = ResultFromScode(MAPI_E_HAS_MESSAGES);
        goto exit;
    }

    if (lpMessages)
    {
        hr = pifldToDelete->lpVtbl->DeleteMessages(pifldToDelete,
            lpMessages, 0L, NULL, 0L);
        if (hr != hrSuccess)
            goto exit;
    }

    UlRelease(pifldToDelete);
    pifldToDelete = NULL;

    if (!fContentsOnly)
    {
        ULONG ulRowCount;
        LPMAPITABLE pmt;

        /* delete the files on the filesystem */
        hr = HrDestroyFolderStorage(szToDelete);
        if (hr != hrSuccess)
            goto exit;

        ChangeTable(pims, pifldParent->peid, peidToDelete, MAPI_FOLDER,
            TABLE_ROW_DELETED, TRUE);

        hr = pifldParent->lpVtbl->GetHierarchyTable(pifldParent, 0, &pmt);

        if (hr == hrSuccess)
        {
            hr = pmt->lpVtbl->GetRowCount(pmt, 0, &ulRowCount);
            UlRelease(pmt);
        }

        if (hr == hrSuccess && ulRowCount == 0)
            hr = HrSetSubFolderProp(pifldParent, FALSE);        

        /* Ignore errors changing and updating the hierarchy table. */
        /* The entire delete shouldn't fail simply because we couldn't */
        /* update the hierarchy table. */

        #ifdef DEBUG
        if (hr != hrSuccess)
        {
            TraceSz1("HrDeleteSubDirectory: Ignoring partial failure (%s)"
                " fixing hierarchy table.", SzDecodeScode(GetScode(hr)));
        }
        #endif

        hr = hrSuccess;
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(pifldToDelete);

    LMFree(&pims->lmr, peidSubDir);
    FreeNull(szToDelete);

    CloseIDSearch(&hFindFile, &szRelativePath);

    if (lpMessages)
        DestroyMessageList(&pims->lmr, &lpMessages);

    DebugTraceResult(HrDeleteSubDirectory, hr);
    return hr;
}

/*
 -  HrCopyFolder
 -
 *  Purpose:
 *      moves or copies one folder into another
 *
 *  Parameters
 *      peidFldSrc      pointer to the entryid of the folder to copy or move.
 *      pifldDst        the parent folder into which we copy or move
 *      ulFlags         MAPI_MOVE, MAPI_NOREPLACE
 *      ptagaExcl       List of properties to exclude from the copy.
 *
 *  Returns:
 *
 *  Errors:
 */
static HRESULT HrCopyFolder(PEID peidFldSrc, PIFLD pifldDstPar, ULONG ulFlags,
    LPSPropTagArray ptagaExcl)
{
    HRESULT hr;
    PIFLD pifldSrc = NULL;

    PIFLD pifldCopy = NULL;     /* copy of pifldSrc */
    LPTSTR szComment = NULL;    /* comment for copy of pifldSrc */
    PIMS pims = pifldDstPar->pims;
    ULONG ulObjType;
    LPSTR szNewFolderName;
    PIFLD pifldParent = NULL;
    ULONG cValNC;
    LPSPropValue pvalNC = NULL;
    const static SizedSPropTagArray(2, sptaNC) =
    {
        2,
        {
            PR_DISPLAY_NAME,
            PR_COMMENT
        }
    };

    /* Open the source folder for modification only if we are moving */

    hr = pims->lpVtbl->OpenEntry(pims, CbEID(peidFldSrc),
        (LPENTRYID) peidFldSrc, NULL, (ulFlags & MAPI_MOVE) ? MAPI_MODIFY : 0L,
        &ulObjType, (LPUNKNOWN *) &pifldSrc);
    if (hr != hrSuccess)
        goto exit;

    /* if this is a move, make sure the source folder is not in use */
    if ((ulFlags & MAPI_MOVE) && pifldSrc->cRef > 1)
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* get the name and comment from pifldSrc */
    hr = pifldSrc->lpVtbl->GetProps(pifldSrc,
        (LPSPropTagArray) &sptaNC, 0, /* ansi */
        &cValNC, &pvalNC);
    if (hr != hrSuccess)
    {
        if (GetScode(hr) == MAPI_W_ERRORS_RETURNED)
        {
            if (PROP_TYPE(pvalNC->ulPropTag) == PT_ERROR)
            {
                hr = ResultFromScode(pvalNC->Value.err);
                goto exit;
            }

            hr = hrSuccess;
        }
        else
            goto exit;
    }

    /* create new folder for the copy */
    szNewFolderName = pvalNC[0].Value.LPSZ;

    if (PROP_TYPE(pvalNC[1].ulPropTag) != PT_ERROR)
        szComment = pvalNC[1].Value.LPSZ;
    else
        szComment = NULL;

    hr = HrDuplicateIFLD(pifldSrc, pifldDstPar, szNewFolderName, szComment,
        &pifldCopy);
    if (hr != hrSuccess)
        goto exit;

    /* move or copy the interior of this folder (recursive) */
    hr = HrCopyContents(pifldSrc, pifldCopy, ulFlags, ptagaExcl);
    if (hr != hrSuccess)
        goto exit;

    UlRelease(pifldSrc);
    pifldSrc = NULL;

    /* invalidate the source folder if this is a move */
    if (ulFlags & MAPI_MOVE)
    {
        LPMAPITABLE pmt;
        ULONG ulRowCount;
        LPTSTR szFullPathFolder;

        hr = HrFullPathName(pims->szStorePath,
            peidFldSrc->szPath, NULL, &szFullPathFolder);
        if (hr != hrSuccess)
            goto exit;

        /* delete it */
        hr = HrDestroyFolderStorage(szFullPathFolder);

        FreeNull(szFullPathFolder);

        if (hr != hrSuccess)
            goto exit;

        /* update the hierarchy table of the source's parent */
        hr = HrOpenParent(pims, peidFldSrc, MAPI_MODIFY, &pifldParent);
        if (hr != hrSuccess)
            goto exit;

        ChangeTable(pims, pifldParent->peid, peidFldSrc, MAPI_FOLDER,
            TABLE_ROW_DELETED, TRUE);

        hr = pifldParent->lpVtbl->GetHierarchyTable(pifldParent, 0, &pmt);

        if (hr == hrSuccess)
            hr = pmt->lpVtbl->GetRowCount(pmt, 0, &ulRowCount);

        UlRelease(pmt);

        if (hr == hrSuccess && ulRowCount == 0)
            hr = HrSetSubFolderProp(pifldParent, FALSE);        
    }

exit:
    UlRelease(pifldSrc);

    LMFree(&pims->lmr, pvalNC);
    UlRelease(pifldParent);

    UlRelease(pifldCopy);

    DebugTraceResult(HrCopyFolder, hr);
    return hr;
}

/*
 * HrCopyContents
 *
 *  Purpose         copy or move the contents of the source folder to
 *                  the destination
 *
 *  Parameters
 *      pifldSrc        source folder
 *      pifldDst        destination folder
 *      ulFlags         MAPI_MOVE, MAPI_NOREPLACE, MAPI_DIALOG
 *      ptagaExcl       List of properties to exclude from the copy.
 *
 */
static HRESULT HrCopyContents(PIFLD pifldSrc, PIFLD pifldDst, ULONG ulFlags,
    LPSPropTagArray ptagaExcl)
{
    PEID peidNext = NULL;       /* eid of next folder to move */
    ULONG ichLocal;
    PLMR plmr = &pifldSrc->pims->lmr;

    /* relative path name of next folder to be moved */
    LPTSTR szFile = NULL;
    HANDLE hFindFile = FAILED_SEARCH;
    HRESULT hr = hrSuccess;
    ULONG ulMessageFlags = 0L;  /* flags for the message copy */
    WIN32_FIND_DATA ffd;

    /* move or copy each message inside the folder */
    if (ulFlags & MAPI_MOVE)
        ulMessageFlags = MESSAGE_MOVE;

    if (!FContainsProp(PR_CONTAINER_CONTENTS, ptagaExcl))
    {
        LPENTRYLIST lpMessages = NULL;

        /* make a message list */
        hr = HrCreateMessageList(pifldSrc, &lpMessages);
        if (hr != hrSuccess)
            goto exit;

        /* move/copy messages */
        if (lpMessages)
        {
            hr = pifldSrc->lpVtbl->CopyMessages(pifldSrc,
                lpMessages, 0, (LPMAPIFOLDER) pifldDst, 0,
                NULL, ulMessageFlags);

            DestroyMessageList(plmr, &lpMessages);

            if (hr != hrSuccess)
                goto exit;
        }
    }

    /* move/copy subfolders if required */
    if ((ulFlags & MAPI_MOVE)
        || (!FContainsProp(PR_CONTAINER_HIERARCHY, ptagaExcl)))
    {
        /* get the first entryID for a subfolder */
        hr = HrFindFirstID(pifldSrc, szFolderTemplate, &ichLocal,
            &szFile, &hFindFile, &ffd, &peidNext);

        while (hr == hrSuccess)
        {
            /* copy the eid to the destination */
            hr = HrCopyFolder(peidNext, pifldDst, ulFlags, ptagaExcl);
            if (hr != hrSuccess)
                goto exit;

            LMFree(plmr, peidNext);
            peidNext = NULL;

            if (ulFlags & MAPI_MOVE)
            {
                /* The folder should have been destroyed; therefore, */
                /* start the search again. */

                CloseIDSearch(&hFindFile, &szFile);

                hr = HrFindFirstID(pifldSrc, szFolderTemplate, &ichLocal,
                    &szFile, &hFindFile, &ffd, &peidNext);
            }
            else
                hr = HrFindNextID(pifldSrc, ichLocal, szFile,
                    hFindFile, &ffd, &peidNext);
        }

        if (GetScode(hr) != MAPI_E_NOT_FOUND)
            goto exit;          /* uh oh.  got a real error */

        hr = hrSuccess;
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    /* close the search */
    CloseIDSearch(&hFindFile, &szFile);
    LMFree(plmr, peidNext);

    DebugTraceResult(HrCopyContents, hr);
    return hr;
}

/*
 * HrEIDFromDisplayName
 *
 *  Purpose
 *      Searches the table given, looking for a matching PR_DISPLAY_NAME.
 *      If found, the routine returns the value of the corresponding
 *      PR_ENTRYID column, converted to an internal PEID. If not found, the
 *      routine returns a NULL.
 *
 *  Parameters
 *      pmt: The IMAPITable object to search for the display name.
 *      szName: The display name to search for.
 *      plmr: A pointer to the linked memory routines to allow freeing memory.
 *      ppeid: A pointer to the location to return the internal entryid of
 *          the PR_ENTRYID column that corresponds to the matching display
 *          name. If no matching display name was found, the routine returns
 *          NULL in this location.
 *  
 */
static HRESULT HrEIDFromDisplayName(LPMAPITABLE pmt, LPSTR szName, PLMR plmr,
    PEID *ppeid)
{
    HRESULT hr;
    LPSRowSet prws = NULL;
    PEID peid = NULL;

    SizedSPropTagArray(2, spta) =
    {
        2,
        {
            PR_ENTRYID,
            PR_DISPLAY_NAME
        }
    };

    hr = pmt->lpVtbl->SetColumns(pmt, (LPSPropTagArray) &spta, 0);
    if (hr != hrSuccess)
        goto exit;

    hr = pmt->lpVtbl->SeekRow(pmt, BOOKMARK_BEGINNING, 0, NULL);
    if (hr != hrSuccess)
        goto exit;

    while (TRUE)
    {
        LPSTR szCurName;
        LPSPropValue pval;

        hr = pmt->lpVtbl->QueryRows(pmt, 1, 0, &prws);
        if (hr != hrSuccess)
            goto exit;

        if (prws->cRows == 0)
            break;

        Assert(prws);
        Assert(prws->cRows == 1);
        Assert(prws->aRow[0].lpProps);
        Assert(prws->aRow[0].lpProps[0].ulPropTag == PR_ENTRYID);
        Assert(prws->aRow[0].lpProps[1].ulPropTag == PR_DISPLAY_NAME);

        pval = prws->aRow[0].lpProps;

        szCurName = (LPSTR) pval[1].Value.lpszA;

        if (lstrcmpi(szName, szCurName) == 0)
        {
            SCODE sc;
            PEID peidTemp = (PEID) pval->Value.bin.lpb;
            UINT cbEID = (UINT) pval->Value.bin.cb;

            sc = LMAlloc(plmr, cbEID, &peid);
            if (sc != S_OK)
            {
                hr = ResultFromScode(sc);
                goto exit;
            }

            if (cbEID)
                memcpy(peid, peidTemp, cbEID);

            break;
        }

        FreeProws(prws);
        prws = NULL;
    }

exit:
    if (prws)
    {
        if (prws->cRows && prws->aRow[0].lpProps)
            LMFree(plmr, prws->aRow[0].lpProps);

        LMFree(plmr, prws);
    }

    if (hr == hrSuccess)
    {
        AssertSz(!IsBadWritePtr(ppeid, sizeof(PEID)), "Bad parameter (ppeid) "
            "passed to HrEIDFromDisplayName");
        *ppeid = peid;
    }

    DebugTraceResult(HrEIDFromDisplayName, hr);
    return hr;
}

