/*
 *  M S P M S G . C
 *
 *  Code for the MAPI Sample Store Provider implementation of the
 *  IMessage object.  The implementation is, in fact, a thin
 *  wrapping layer around the implementation of IMessage on
 *  IStorage.  We wrap the IMessage object returned by IMsgOnIStg
 *  so that we can handle those methods (like SubmitMessage) not
 *  understood by a standalone message (e.g. one embedded in a word
 *  document) but which makes sense for a message in the context of
 *  a message store.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

#define MSG_ValidateParameters(pobj, intf, method, arglist)     \
        OBJ_ValidateParameters(pobj, intf, method, sizeof(IMSG), &vtblIMSG, arglist)

/* Manifest constants */

/* Number of properties to initialize a normal message with */
#define cpropIMSGInit       11
/* Number of properties to initialize a message-in-message with */
#define cpropMsgInMsgInit   3
/* Number of in-memory properties associated with a message object */
#define cpropIMSGInternal   4
/* The property attributes to set on the initial set of message properties */
#define grfpropattrIMSGInit (PROPATTR_MANDATORY | PROPATTR_READABLE)

#define IMSG_EnterCriticalSection(pimsg)    OBJ_EnterCriticalSection((POBJ)pimsg)
#define IMSG_LeaveCriticalSection(pimsg)    OBJ_LeaveCriticalSection((POBJ)pimsg)

typedef enum _mrflavor
{
    ENUM_ADD = 1,
    ENUM_MODIFY,
    ENUM_REMOVE
} MRFLAVOR;

/* internal functions */
static HRESULT HrSaveMsgInMsg(PIMSG pimsg, ULONG ulFlags);
static SCODE ScFillOneSBPval(PLMR plmr, LPVOID pvOrigBuf, ULONG ulPropTag,
    ULONG cb, LPBYTE lpbData, LPSPropValue pval);

/* Global variables */

/* Dispatch table for IMessage objects */
IMSG_Vtbl vtblIMSG =
{
    (IMSG_QueryInterface_METHOD *)  OBJ_QueryInterface,
    (IMSG_AddRef_METHOD *)          OBJ_AddRef,
    (IMSG_Release_METHOD *)         OBJ_Release,
    (IMSG_GetLastError_METHOD *)    IMS_GetLastError,
    IMSG_SaveChanges,
    IMSG_GetProps,
    IMSG_GetPropList,
    IMSG_OpenProperty,
    IMSG_SetProps,
    IMSG_DeleteProps,
    IMSG_CopyTo,
    IMSG_CopyProps,
    (IMSG_GetNamesFromIDs_METHOD *) IMS_GetNamesFromIDs,
    (IMSG_GetIDsFromNames_METHOD *) IMS_GetIDsFromNames,
    IMSG_GetAttachmentTable,
    IMSG_OpenAttach,
    IMSG_CreateAttach,
    IMSG_DeleteAttach,
    IMSG_GetRecipientTable,
    IMSG_ModifyRecipients,
    IMSG_SubmitMessage,
    IMSG_SetReadFlag
};

/*
 *  OBJECT METHODS
 */

/*
 *  IMSG_SaveChanges
 *
 *  Purpose:
 *      Saves changes made to a message object and all of its
 *      sub-objects (attachments, et al.).
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     Flags.  The following are defined:
 *                  KEEP_OPEN_READONLY  Do not invalidate the
 *                                      object, make it read-only.
 *                  KEEP_OPEN_READWRITE Don't invalidate the
 *                                      object, keep it open
 *                                      read/write.
 *                  FORCE_SAVE          Overwrite any changes made by
 *                                      others since message was openned.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 */
STDMETHODIMP IMSG_SaveChanges(PIMSG pimsg, ULONG ulFlags)
{
    HRESULT hr = hrSuccess;
    PIFLD pifldParent = NULL;   /* parent as an open folder */
    ULONG ulPropMsgFlags;       /* flags for save on property message */
    ULONG ulChangeType = TABLE_ROW_MODIFIED;
    BOOL fUnread = FALSE;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            SaveChanges,
            (pimsg, 
            ulFlags));

    IMSG_EnterCriticalSection(pimsg);

    /* Handle msg-in-msg separately. */
    if (OBJ_TestFlag(pimsg, MSGF_MSGINMSG))
    {
        hr = HrSaveMsgInMsg(pimsg, ulFlags);
        goto exit;
    }

    /* open up lpmsg's parent so we can update tables and contents counts */
    hr = HrOpenParent(pimsg->pims, pimsg->peid, MAPI_MODIFY, &pifldParent);
    if (hr != hrSuccess)
        goto exit;

    /* mark the new message as complete by updating its ENTRYID property */
    if (OBJ_TestFlag(pimsg, MSGF_NEWLYCREATED))
    {
        ULONG ulMF;
        PEID peidInt = NULL;

        ReplaceExt(pimsg->peid->szPath, MESSAGE_EXT);

        /* Assume that PR_ENTRYID is at position 0 in the in-memory */
        /* array. That's where it went in HrSetInternalProps. */

        AssertSz(pimsg->pval->ulPropTag == PR_ENTRYID,
            "The location of PR_ENTRYID in the in-memory array has changed");

        peidInt = (PEID) pimsg->pval->Value.bin.lpb;

        AssertSz(!FIsInvalidEID(pimsg->pval->Value.bin.cb, peidInt, NULL),
            "Invalid internal Entryid");

        if (peidInt)
            ReplaceExt(peidInt->szPath, MESSAGE_EXT);

        /* Now, we need to update PR_INSTANCE_KEY in the same way. Since */
        /* the message is just becoming permanent, it won't be in any */
        /* tables yet, so it can change without affecting any tables. */

        /* NOTE: this code assumes knowledge of the format of */
        /* PR_INSTANCE_KEY. */

        AssertSz(pimsg->pval[1].ulPropTag == PR_INSTANCE_KEY, "The location "
            "of PR_INSTANCE_KEY in the in-memory array has changed");

        peidInt = (PEID) pimsg->pval[1].Value.bin.lpb;

        AssertSz(!FIsInvalidEID(pimsg->pval[1].Value.bin.cb, peidInt, NULL),
            "Invalid internal Entryid");

        if (peidInt)
            ReplaceExt(peidInt->szPath, MESSAGE_EXT);

        hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pimsg->pims->lmr,
            PR_MESSAGE_FLAGS, &ulMF);
        if (hr != hrSuccess)
            goto exit;

        /* remember the message's unread status, and to update open tables */

        fUnread = !(ulMF & MSGFLAG_READ);
        ulChangeType = TABLE_ROW_ADDED;
    }

    /* When the spooler saves a message, from the client's perspective, it */
    /* hasn't been modified, because it has just arrived. */

    if (!OBJ_TestFlag(pimsg, MSGF_NEWLYCREATED)
        && !OBJ_TestFlag(pimsg->pims, MSF_SPOOLER))
    {
        /* unset the UNMODIFIED bit */
        hr = HrSetFlags(pimsg, UNSET, PR_MESSAGE_FLAGS, MSGFLAG_UNMODIFIED);
        if (hr != hrSuccess)
            goto exit;
    }

    /* save the changes but keep the property file open */
    ulPropMsgFlags = ulFlags;

    if (!(ulFlags & KEEP_OPEN_READWRITE))
        ulPropMsgFlags |= KEEP_OPEN_READONLY;

    hr = pimsg->lpmsg->lpVtbl->SaveChanges(pimsg->lpmsg, ulPropMsgFlags);
    if (hr != hrSuccess)
        goto exit;

    /* update the parent's contents table and parent folder properties */
    if (ulChangeType == TABLE_ROW_ADDED)
    {
        (void) HrIncrementOneROProp(pifldParent, 1, PR_CONTENT_COUNT);

        if (fUnread)
            (void) HrIncrementOneROProp(pifldParent, 1, PR_CONTENT_UNREAD);
    }

    ChangeTable(pimsg->pims, pifldParent->peid, pimsg->peid, MAPI_MESSAGE,
        ulChangeType, TRUE);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(pifldParent);

    if (hr == hrSuccess)
    {
        /* Unless the user requests to continue with modify access, switch */
        /* down to read-only access. This means that specifying neither of */
        /* the KEEP_OPEN flags means the same thing as KEEP_OPEN_READONLY. */
        if (!(ulFlags & KEEP_OPEN_READWRITE))
            OBJ_ClearFlag(pimsg, OBJF_MODIFY);

        OBJ_ClearFlag(pimsg, MSGF_NEWLYCREATED);
    }

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_SaveChanges, hr);
    return HrCheckHr(hr, IMAPIProp_SaveChanges);
}

/*
 *  IMSG_GetProps
 *
 *  Purpose:
 *      Returns to the caller the value(s) of one or more
 *      properties existent on an IMSG object.  The order of the
 *      properties in the returned ppval structure exactly
 *      matches the order in which the properties were requested in
 *      ptaga.  The caller must free the returned
 *      structure by calling MAPIFreeBuffer(*ppval), but
 *      only if the function returns zero or the error
 *      MAPI_W_ERRORS_RETURNED.  Uses the IMessage on IStorage
 *      property interface implementation.
 *
 *  Arguments:
 *      pimsg           Pointer to the object.
 *      ptaga   Pointer to a counted array of property tags
 *                      ("names") that identify the values to be
 *                      returned.
 *      ulFlags         UNICODE / String8
 *      pcval       Location in which to return the count of
 *                      elements in *ppval.
 *      ppval   Location in which to return an allocated
 *                      array of property values (the caller frees
 *                      by calling MAPIFreeBuffer).
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      If the call succeeded overall but access to one or more
 *      properties failed, the function returns the warning
 *      MAPI_W_ERRORS_RETURNED.  The calling application should
 *      then check the Property Tag of each of the returned
 *      properties to determine which ones failed.  Those that fail
 *      have their Property Type set to PT_ERROR and their value (a
 *      ULONG) indicates which error occurred.
 *
 *      MAPI_E_NO_ACCESS    The caller does not have access
 *                                  to the requested properties.
 *      MAPI_W_ERRORS_RETURNED      See above.
 *      MAPI_E_CALL_FAILED          The mechanism for making the
 *                                  call to the service provider
 *                                  failed.
 */
STDMETHODIMP IMSG_GetProps(PIMSG pimsg, LPSPropTagArray ptaga, ULONG ulFlags,
    ULONG *pcval, LPSPropValue *ppval)
{
    HRESULT hr = hrSuccess;
    BOOL fLocked = FALSE;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            GetProps,
            (pimsg, 
            ptaga, 
            ulFlags, 
            pcval, 
            ppval));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->GetProps(pimsg->lpmsg, ptaga, ulFlags,
        pcval, ppval);

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
    /* If not message-in-message then wrap values. */
    /* Note that this wrapping function takes as an */
    /* argument the HRESULT from the previous GetProps call. */
    /* We aren't ignoring the error. */

    if (!OBJ_TestFlag(pimsg, MSGF_MSGINMSG))
        hr = HrWrap_GetProps(hr, pimsg->pims, pimsg->cval, pimsg->pval,
            pcval, ppval, FALSE, (ptaga != NULL), (POBJ)pimsg);

    IMSG_LeaveCriticalSection(pimsg);

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_W_ERRORS_RETURNED)
        DebugTraceResult(IMSG_GetProps, hr);
    #endif

    return HrCheckHr(hr, IMAPIProp_GetProps);
}

/*
 *  IMSG_GetPropList
 *
 *  Purpose:
 *      Returns a list of all the properties currently accessible.
 *      Uses the IMessage on IStorage property implementation.
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     UNICODE / String8
 *      pptaga      Location in which to return a pointer
 *                  to a counted array of property tags.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NO_ACCESS    The caller does not have access
 *                                  to the requested properties.
 *      MAPI_E_CALL_FAILED          The mechanism for making the
 *                                  call to the service provider
 *                                  failed.
 */
STDMETHODIMP IMSG_GetPropList(PIMSG pimsg, ULONG ulFlags, LPSPropTagArray *pptaga)
{
    HRESULT hr = hrSuccess;
    LPSPropTagArray ptaga = NULL;
    LPSPropTagArray ptagaRet = NULL;
    UINT ind;
    SizedSPropTagArray(2, sptaToAdd) = 
        { 2,
            {   PR_MESSAGE_RECIPIENTS, 
                PR_MESSAGE_ATTACHMENTS
            }
        };

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            GetPropList,
            (pimsg, 
            ulFlags, 
            pptaga));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->GetPropList(pimsg->lpmsg, ulFlags, &ptaga);

    if (hr == hrSuccess && FIsUnsavedMsg(pimsg))
    {
        /* Remove PR_ENTRYID from the array. Since the message is unsaved, */
        /* don't return the entryid. Overwrite the PR_ENTRYID entry with */
        /* the last prop tag in the array. */
        /* //$ Should PR_INSTANCE_KEY be removed from the array too? */

        ULONG *pulPT;
        ULONG *pulPTMac;

        pulPT = ptaga->aulPropTag;
        pulPTMac = pulPT + ptaga->cValues;

        while (pulPT < pulPTMac)
        {
            if (*pulPT == PR_ENTRYID)
            {
                ptaga->cValues--;
                pulPTMac--;

                if (pulPT < pulPTMac)
                    memcpy(pulPT, pulPTMac, sizeof(ULONG));
                break;
            }

            ++pulPT;
        }
    }

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if(hr == hrSuccess)
    {
        if(!(hr = ResultFromScode(MAPIAllocateBuffer(
                        CbNewSPropTagArray(ptaga->cValues + sptaToAdd.cValues),
                         (LPVOID *)&ptagaRet))))
        {
            CopyMemory(ptagaRet, ptaga, CbNewSPropTagArray(ptaga->cValues));

            for(ind = 0; ind < sptaToAdd.cValues; ++ind)
            {
                if(!FContainsProp(sptaToAdd.aulPropTag[ind], ptaga))
                {
                    ptagaRet->aulPropTag[ptagaRet->cValues++] =
                        sptaToAdd.aulPropTag[ind];
                }
            }
            
        }
    }

    MAPIFreeBuffer(ptaga);
    
    if (hr == hrSuccess)
        *pptaga = ptagaRet;

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_GetPropList, hr);
    return HrCheckHr(hr, IMAPIProp_GetPropList);
}

/*
 *  IMSG_OpenProperty
 *
 *  Purpose:
 *      Open a requested interface on a property for further
 *      access.  Commonly used for stream access to a large binary
 *      or text property.  This is the only way to access a
 *      property of type PT_OBJECT, and may be used on other
 *      properties depending on the implementation.  Uses the
 *      IMessage on IStorage property implementation.
 *
 *  Arguments:
 *      pimsg           Pointer to the object.
 *      ulPropTag   Property tag for the desired property.  Only
 *                      the ID bits of the tag are used; the type bits
 *                      are ignored.
 *      lpiid           Pointer to the GUID identifying which interface
 *                      is desired.
 *      ulInterfaceOptions  specifies interface-specific behavior
 *      ulFlags     MAPI_CREATE, MAPI_MODIFY, MAPI_DEFERRED_ERRORS
 *      lppUnk      Location in which to return a pointer to the
 *                      newly created interface pointer.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_INTERFACE_NOT_SUPPORTED      An error occurred opening a
 *                                          supported interface.
 */
STDMETHODIMP IMSG_OpenProperty(PIMSG pimsg, ULONG ulPropTag, LPCIID lpiid,
    ULONG ulInterfaceOptions, ULONG ulFlags, LPUNKNOWN *lppUnk)
{
    HRESULT hr = hrSuccess;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            OpenProperty,
            (pimsg, 
            ulPropTag, 
            lpiid, 
            ulInterfaceOptions, 
            ulFlags, 
            lppUnk));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->OpenProperty(pimsg->lpmsg, ulPropTag, lpiid,
        ulInterfaceOptions, ulFlags, lppUnk);

    if (hr == hrSuccess
        && (ulFlags & (MAPI_MODIFY | MAPI_CREATE)))
        OBJ_ClearFlag(pimsg, MSGF_FRESH);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_OpenProperty, hr);
    return HrCheckHr(hr, IMAPIProp_OpenProperty);
}

/*
 *  IMSG_SetProps
 *
 *  Purpose:
 *      Sets the value of one or more properties.  This call passes
 *      a number of Property Value structures.  The Property Tag in
 *      each indicates which property is having its values set and
 *      the value indicates what should be stored.  The caller must
 *      free the returned property problem structure by calling
 *      MAPIFreeBuffer(*lppProblems), but only if the call
 *      succeeded overall.  Uses the IMessage on IStorage property
 *      implementation.
 *
 *  Arguments:
 *      pimsg           Pointer to the object.
 *      cValues         Number of values in lpPropArray.
 *      lpPropArray     Pointer to a Property Value array.
 *      lppProblems     Location in which to return a pointer to a
 *                      counted array of property problem
 *                      structures.
 *
 *  Returns:
 *      HRESULT.  If the call succeeds overall, a zero is returned.
 *      If there are problems with setting some or all of the
 *      selected values, and a non-NULL is passed for lppProblems,
 *      then a SPropProblemArray structure is returned with details
 *      about each problem.  The value returned in lppProblems is
 *      only valid if zero is returned in the HRESULT.  If an error
 *      occurs on the call such that a non-zero value is returned
 *      for the HRESULT then the contents of *lppProblems are
 *      undefined.  In particular, do not use or free the structure
 *      if an error occurs on the call.
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NO_ACCESS    The caller does not have access
 *                                  to the requested properties.
 *      MAPI_E_CALL_FAILED      A general problem affecting
 *                                  access to all of the object's
 *                                  properties occurred.
 *      MAPI_E_CALL_FAILED          The mechanism for making the
 *                                  call to the service provider
 *                                  failed.
 */
STDMETHODIMP IMSG_SetProps(PIMSG pimsg, ULONG cValues, LPSPropValue lpPropArray,
    LPSPropProblemArray *lppProblems)
{
    HRESULT hr;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            SetProps,
            (pimsg, 
            cValues, 
            lpPropArray, 
            lppProblems));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->SetProps(pimsg->lpmsg, cValues, lpPropArray,
        lppProblems);

    if (hr == hrSuccess)
        OBJ_ClearFlag(pimsg, MSGF_FRESH);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_SetProps, hr);
    return HrCheckHr(hr, IMAPIProp_SetProps);
}

/*
 *  IMSG_DeleteProps
 *
 *  Purpose:
 *      Deletes the list of properties given in ptaga.
 *      The caller must free the returned property problem
 *      structure by calling MAPIFreeBuffer(*ppErr), but only
 *      if the call succeeded overall.  Uses the IMessage on
 *      IStorage property implementation.
 *
 *  Arguments:
 *      pimsg           Pointer to the object.
 *      ptaga   Pointer to an array of Property Tags
 *                      identifying the properties to delete.
 *      ppErr       Location in which to return a pointer to a
 *                      counted array of property problem
 *                      structures.
 *
 *  Returns:
 *      HRESULT.  If the call succeeds overall, zero is returned.
 *      If there are problems with deleting some or all of the
 *      selected values, and a non-NULL is passed for ppErr,
 *      then a SPropProblemArray structure is returned with details
 *      about each problem.  The value returned in ppErr is
 *      only valid if zero is returned in the HRESULT.  If an error
 *      occurs on the call such that a non-zero value is returned
 *      for the HRESULT then the contents of *ppErr are
 *      undefined.  In particular, do not use or free the structure
 *      if an error occurs on the call.
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NO_ACCESS    The caller does not have access
 *                                  to the requested properties.
 *      MAPI_E_CALL_FAILED      A general problem affecting
 *                                  access to all of the object's
 *                                  properties occurred.
 *      MAPI_E_CALL_FAILED          The mechanism for making the
 *                                  call to the service provider
 *                                  failed.
 */
STDMETHODIMP IMSG_DeleteProps(PIMSG pimsg, LPSPropTagArray ptaga,
    LPSPropProblemArray *ppErr)
{
    HRESULT hr;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            DeleteProps,
            (pimsg, 
            ptaga, 
            ppErr));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->DeleteProps(pimsg->lpmsg, ptaga, ppErr);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_DeleteProps, hr);
    return HrCheckHr(hr, IMAPIProp_DeleteProps);
}

/*
 *  IMSG_CopyTo
 *
 *  Purpose:
 *      Copies the contents of the current object to a destination
 *      object.  The entire contents, including contained objects,
 *      are copied, or optionally the caller can provide a list of
 *      properties that are not to be copied.  Previous information
 *      in the destination object which is not overwritten by
 *      copied data is neither deleted nor modified.
 *
 *  Arguments:
 *      pimsg           Pointer to the source object.
 *      ciidExcl        Count of the excluded interfaces in
 *                      rgiidExcl.
 *      rgiidExcl   Array of interface IDs specifying
 *                      interfaces not to be attempted in trying to
 *                      copy supplemental information to the
 *                      destination object.
 *      ptagaExcl   Counted array of property tags of
 *                      properties that are not to be copied to the
 *                      destination object.  NULL indicates all
 *                      properties are to be copied.
 *      ulUIParam       Handle of parent window cast to ULONG.
 *      lpProgress      Callback for doing progress UI.
 *      piidDst     Interface ID of the interface of lpDestObj,
 *                      the destination object.
 *      lpDestObj       Pointer to the open destination object.
 *      ulFlags         Flags.  Defined as follows:
 *                      MAPI_MOVE       Indicates a move operation.
 *                                      The default is to copy.
 *                      MAPI_NOREPLACE  Indicates that existing
 *                                      properties should not be
 *                                      overridden.  The default is
 *                                      to overwrite existing
 *                                      properties.
 *                      MAPI_DIALOG     Display a progress dialog
 *                                      as the operation proceeds.
 *                      MAPI_STD_DIALOG Use MAPI standard dialog
 *                                      instead of
 *                                      provider-specific dialog.
 *      ppErr       Pointer to a variable that is filled in
 *                      with a pointer to a set of property
 *                      problems.  If NULL, no problem set is
 *                      returned on an error.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 */
STDMETHODIMP IMSG_CopyTo(PIMSG pimsg, ULONG ciidExcl, LPCIID rgiidExcl,
    LPSPropTagArray ptagaExcl, ULONG ulUIParam, LPMAPIPROGRESS lpProgress,
    LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray *ppErr)
{
    HRESULT hr;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            CopyTo,
            (pimsg, 
            ciidExcl, 
            rgiidExcl, 
            ptagaExcl, 
            ulUIParam, 
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags, 
            ppErr));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->CopyTo(pimsg->lpmsg, ciidExcl, rgiidExcl,
        ptagaExcl, ulUIParam, lpProgress, piidDst, lpDestObj,
        ulFlags, ppErr);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_CopyTo, hr);
    return HrCheckHr(hr, IMAPIProp_CopyTo);
}

/*
 *  IMSG_CopyProps
 *
 *  Purpose:
 *      Copies the specified properties of the current object to a destination
 *      object.  Previous information
 *      in the destination object which is not overwritten by
 *      copied data is neither deleted nor modified.
 *
 *  Arguments:
 *      pimsg           Pointer to the source object.
 *      ptagaIncl       Counted array of property tags of
 *                      properties that are not to be copied to the
 *                      destination object.  NULL indicates all
 *                      properties are to be copied.
 *      ulUIParam       Handle of parent window cast to ULONG.
 *      lpProgress      Callback for doing progress UI.
 *      piidDst         Interface ID of the interface of lpDestObj,
 *                      the destination object.
 *      lpDestObj       Pointer to the open destination object.
 *      ulFlags         Flags.  Defined as follows:
 *                      MAPI_MOVE       Indicates a move operation.
 *                                      The default is to copy.
 *                      MAPI_NOREPLACE  Indicates that existing
 *                                      properties should not be
 *                                      overridden.  The default is
 *                                      to overwrite existing
 *                                      properties.
 *                      MAPI_DIALOG     Display a progress dialog
 *                                      as the operation proceeds.
 *                      MAPI_DECLINE_OK
 *      ppErr       Pointer to a variable that is filled in
 *                      with a pointer to a set of property
 *                      problems.  If NULL, no problem set is
 *                      returned on an error.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 */
STDMETHODIMP IMSG_CopyProps(PIMSG pimsg,
    LPSPropTagArray ptagaIncl, ULONG ulUIParam, LPMAPIPROGRESS lpProgress,
    LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray *ppErr)
{
    HRESULT hr;

    MSG_ValidateParameters(
            pimsg,
            IMAPIProp,
            CopyProps,
            (pimsg,
            ptagaIncl, 
            ulUIParam, 
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags, 
            ppErr));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->CopyProps(pimsg->lpmsg,
        ptagaIncl, ulUIParam, lpProgress, piidDst, lpDestObj,
        ulFlags, ppErr);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_CopyProps, hr);
    return HrCheckHr(hr, IMAPIProp_CopyProps);
}

/*
 *  IMSG_GetAttachmentTable
 *
 *  Purpose:
 *      Returns, in table form, the list of attachments contained
 *      in this message (one row per attachment).  The table has at
 *      least the PR_ATTACH_NUM and PR_RENDERING_POSITION columns.
 *      Additional columns may be in the table depending on the
 *      implementation.  This table may change while it is open if
 *      the application calls CreateAttach() or DeleteAttach(), or
 *      if an attachment is modified in a way that some properties
 *      in the table get changed.
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     Flags.  Reserved for future use.  Ignored.
 *      lppTable    Pointer to a variable in which the address of
 *                  the returned table object is placed.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Unable to allocate memory for
 *                                  the returned table object or
 *                                  its underlying data.
 */
STDMETHODIMP
IMSG_GetAttachmentTable(PIMSG pimsg, ULONG ulFlags, LPMAPITABLE *lppTable)
{
    HRESULT hr;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            GetAttachmentTable,
            (pimsg, 
            ulFlags, 
            lppTable));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->GetAttachmentTable(pimsg->lpmsg, ulFlags,
        lppTable);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_GetAttachmentTable, hr);
    return HrCheckHr(hr, IMessage_GetAttachmentTable);
}

/*
 *  IMSG_OpenAttach
 *
 *  Purpose:
 *      Opens an existing attachment and returns a pointer which
 *      provides further access to the open attachment.  We get a
 *      pointer to the attachment object from the IMessage on
 *      IStorage implementation, and then wrap it with our own
 *      attachment object.
 *
 *  Arguments:
 *      pimsg           Pointer to the object.
 *      ulAttachmentNum Number of the attachment to be opened (the
 *                      value of this parameter comes from the
 *                      attachment table.
 *      piidDst     IID of interface requested for the
 *                      newly-opened object.  NULL or IID_IMAPIProp
 *                      means to open the object using the standard
 *                      MAPI 1.0 interface for the object.
 *                      IID_IUnknown means to open it using
 *                      the easiest interface you can open.
 *      ulFlags         Flags.  The following are defined:
 *                      MAPI_MODIFY     Write access is desired.
 *                                      The message must also be
 *                                      open for write access.
 *      lppAttach       Pointer to a variable which is to receive
 *                      the pointer to the open attachment object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      IStorage errors, plus,
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the new attachment instance.
 */
STDMETHODIMP IMSG_OpenAttach(PIMSG pimsg, ULONG ulAttachmentNum, LPCIID piidDst,
    ULONG ulFlags, LPATTACH *lppAttach)
{
    HRESULT hr = hrSuccess;
    LPATTACH lpattach = NULL;
    PIATCH piatch = NULL;
    BOOL fModify;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            OpenAttach,
            (pimsg, 
            ulAttachmentNum, 
            piidDst, 
            ulFlags, 
            lppAttach));

    IMSG_EnterCriticalSection(pimsg);

    /* Check for modification rights on the message. Switch to read-only */
    /* if the client asked for best access. */

    if (ulFlags & MAPI_BEST_ACCESS)
        fModify = !!OBJ_TestFlag(pimsg, OBJF_MODIFY);
    else
    {
        fModify = !!(ulFlags & MAPI_MODIFY);

        if (fModify && !OBJ_TestFlag(pimsg, OBJF_MODIFY))
        {
            hr = ResultFromScode(MAPI_E_NO_ACCESS);
            goto exit;
        }
    }

    hr = pimsg->lpmsg->lpVtbl->OpenAttach(pimsg->lpmsg, ulAttachmentNum,
        piidDst, ulFlags, &lpattach);
    if (hr != hrSuccess)
        goto exit;

    hr = HrNewIATCH(lpattach, pimsg, fModify, &piatch);

    UlRelease(lpattach);
    lpattach = NULL;

    if (hr != hrSuccess)
        goto exit;

    *lppAttach = (LPATTACH) piatch;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (hr != hrSuccess)
        UlRelease(piatch);

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_OpenAttach, hr);
    return HrCheckHr(hr, IMessage_OpenAttach);
}

/*
 *  IMSG_CreateAttach
 *
 *  Purpose:
 *      Creates a new attachment in a message and returns a pointer
 *      which provides further access to the open attachment.  We
 *      get a pointer to the attachment object from the IMessage on
 *      IStorage implementation, and then wrap it with our own
 *      attachment object.
 *
 *  Arguments:
 *      pimsg               Pointer to the object.
 *      piidDst         IID of interface requested for the
 *                          newly-opened object.  NULL or IID_IMAPIProp
 *                          means to open the object using the standard
 *                          MAPI 1.0 interface for the object.
 *                          IID_IUnknown means to open it using
 *                          the easiest interface you can open.
 *      ulFlags             Flags.  Reserved for future use.
 *                          Ignored.
 *      lpulAttachmentNum   Pointer to a variable which is to
 *                          receive the number of the newly created
 *                          attachment.  This number is valid only
 *                          within this message.
 *      lppAttach           Pointer to a variable which is to
 *                          receive the pointer to the open
 *                          attachment object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      IStorage errors, plus,
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the new attachment instance.
 */
STDMETHODIMP IMSG_CreateAttach(PIMSG pimsg, LPCIID piidDst, ULONG ulFlags,
    ULONG *lpulAttachmentNum, LPATTACH *lppAttach)
{
    HRESULT hr = hrSuccess;
    LPATTACH lpattach = NULL;
    PIATCH piatch = NULL;
    ULONG ulAttachNum = 0L;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            CreateAttach,
            (pimsg, 
            piidDst, 
            ulFlags, 
            lpulAttachmentNum, 
            lppAttach));

    IMSG_EnterCriticalSection(pimsg);

    if (!OBJ_TestFlag(pimsg, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    hr = pimsg->lpmsg->lpVtbl->CreateAttach(pimsg->lpmsg, piidDst,
        ulFlags, &ulAttachNum, &lpattach);
    if (hr != hrSuccess)
        goto exit;

    /* Wrap the attachment object returned by IMessage. */

    hr = HrNewIATCH(lpattach, pimsg, TRUE, &piatch);

    UlRelease(lpattach);
    lpattach = NULL;

    if (hr != hrSuccess)
        goto exit;

    *lpulAttachmentNum = ulAttachNum;
    *lppAttach = (LPATTACH) piatch;

    OBJ_ClearFlag(pimsg, MSGF_FRESH);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (hr != hrSuccess)
        UlRelease(piatch);

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_CreateAttach, hr);
    return HrCheckHr(hr, IMessage_CreateAttach);
}

/*
 *  IMSG_DeleteAttach
 *
 *  Purpose:
 *      Deletes an attachment in a message.  The current
 *      application should release all pointers to an attachment
 *      and its streams prior to deleting the attachment.  Deleted
 *      attachments are not permanently gone until changes to the
 *      message are saved.
 *
 *  Arguments:
 *      pimsg               Pointer to the object.
 *      ulAttachmentNum     Index of the attachment to be deleted.
 *      ulUIParam           Window handle cast to a ULONG.
 *      lpProgress          Callback for displaying progress UI.
 *      ulFlags             Flags.  Reserved for future use.
 *                          Ignored.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Invalidates all pointers to the attachment, if it is
 *      currently open (this is done by the IMessage on IStorage
 *      implementation).  These invalidated sub-objects then only
 *      support the Release, AddRef, and QueryInterface methods.
 *
 *  Errors:
 *      IStorage errors (MAPI_E_WRITE_FAULT, etc.).
 */
STDMETHODIMP IMSG_DeleteAttach(PIMSG pimsg, ULONG ulAttachmentNum,
    ULONG ulUIParam, LPMAPIPROGRESS lpProgress, ULONG ulFlags)
{
    HRESULT hr = hrSuccess;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            DeleteAttach,
            (pimsg, 
            ulAttachmentNum, 
            ulUIParam, 
            lpProgress, 
            ulFlags));

    IMSG_EnterCriticalSection(pimsg);

    if (!OBJ_TestFlag(pimsg, OBJF_MODIFY))
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
    else
        hr = pimsg->lpmsg->lpVtbl->DeleteAttach(pimsg->lpmsg, ulAttachmentNum,
            ulUIParam, lpProgress, ulFlags);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_DeleteAttach, hr);
    return HrCheckHr(hr, IMessage_DeleteAttach);
}

/*
 *  IMSG_GetRecipientTable
 *
 *  Purpose:
 *      Opens the recipient table in a message.  The recipient
 *      table for a received message or a message under composition
 *      contains one row for each recipient of the message.  The
 *      table will have at least the following columns:  PR_ROWID,
 *      PR_DISPLAY_NAME, PR_ENTRYID, PR_RECIPIENT_TYPE.  The
 *      additional properties PR_ADDRTYPE, PR_SENDER_NAME,
 *      PR_SENDER_ENTRYID, and PR_CLIENT_SUBMIT_TIME will appear in sent
 *      messages (messages not under composition).  Additional
 *      columns may be in the table, depending on the
 *      implementation.
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     Flags.  Reserved for future use.  Ignored.
 *      lppTable    Pointer to a variable in which the address of
 *                  the returned table object is placed.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Unable to allocate memory for
 *                                  the returned table object or
 *                                  its underlying data.
 */
STDMETHODIMP IMSG_GetRecipientTable(PIMSG pimsg, ULONG ulFlags,
    LPMAPITABLE *lppTable)
{
    HRESULT hr = hrSuccess;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            GetRecipientTable,
            (pimsg, 
            ulFlags, 
            lppTable));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->GetRecipientTable(pimsg->lpmsg, ulFlags,
        lppTable);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_GetRecipientTable, hr);
    return HrCheckHr(hr, IMessage_GetRecipientTable);
}

/*
 *  IMSG_ModifyRecipients
 *
 *  Purpose:
 *      Adds, deletes, and/or modifies the recipients in a message.
 *      The property set for each recipient being added or modified
 *      must include a PR_ROWID, PR_DISPLAY_NAME, PR_ADDRTYPE (it
 *      may be empty), PR_ENTRYID (it may be empty), and
 *      PR_RECIPIENT_TYPE.  Additional properties may be specified,
 *      but depending on the implementation they may be ignored or
 *      discarded.
 *
 *      The recipient table may be used to represent both
 *      "resolved" and "unresolved" entries.  An unresolved entry
 *      is one that consists only of a display name.  Applications
 *      which allow users to type recipient names directly will
 *      create these entries.  A resolved entry contains more
 *      information relating the display name to a recipient:  an
 *      email address type and an EntryID.  Unresolved entries are
 *      stored as entries with zero as a value for PR_ENTRYID and
 *      PR_ADDRTYPE.  A message with unresolved entries in the
 *      recipient table will generate a non-delivery-report if
 *      submitted.
 *
 *  Parameters
 *      pimsg       pointer to message object
 *      ulFlags     flags:  MESSAGE_REPLACE
 *      lpMods      Pointer to list of recipient modifications, additions, or
 *                  deletions to be performed on pimsg
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      This method converts all short-term EntryIDs to long-term
 *      EntryIDs.
 *
 *  Errors:
 */
STDMETHODIMP IMSG_ModifyRecipients(PIMSG pimsg, ULONG ulFlags, LPADRLIST lpMods)
{
    HRESULT hr = hrSuccess;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            ModifyRecipients,
            (pimsg, 
            ulFlags, 
            lpMods));

    IMSG_EnterCriticalSection(pimsg);

    hr = pimsg->lpmsg->lpVtbl->ModifyRecipients(pimsg->lpmsg, ulFlags, lpMods);

    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_ModifyRecipients, hr);
    return HrCheckHr(hr, IMessage_ModifyRecipients);
}

/*
 *  IMSG_SubmitMessage
 *
 *  Purpose:
 *      Mark a message as ready for sending and saves all changes
 *      to it and all its attachments.  Since this is not
 *      implemented in IMessage on IStorage, we must do it
 *      ourselves.
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     Flags.  Defined as follows:
 *                  FORCE_SUBMIT    If set, MAPI should submit the
 *                                  message even if it might not be
 *                                  sent right away.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      If the submission is successful, the pointer to the message
 *      and all associated sub-objects (messages, attachments,
 *      streams, tables) are no longer valid, except for their
 *      Release() methods.  No other operations on these pointers
 *      are permitted.  MAPI expects the application to release the
 *      message object and all associated sub-objects.
 *
 *  Errors:
 *      MAPI_E_NON_STANDARD     Unexpected queueing time is
 *                              possible.  This error is only
 *                              returned if the FORCE_SUBMIT flag
 *                              is not set.
 */
STDMETHODIMP IMSG_SubmitMessage(PIMSG pimsg, ULONG ulFlags)
{
    HRESULT hr = hrSuccess;
    LPMAPITABLE pmtRecip = NULL;
    PIMS pims;
    ULONG ulcRow = 0L;
    ULONG cValues = 0L;
    LPSPropValue pval = NULL;
    ULONG ulMF;
    LPSPropProblemArray pprba = NULL;
    SYSTEMTIME st;
    FILETIME ft;
    ULONG ulPrepareFlags;
    ULONG ulPreprocess;
    LPSRowSet prws = NULL;

#define NUM_FLAGTIME    3
    const static SizedSPropTagArray(NUM_FLAGTIME, proptagFlagTime) =
    {
        NUM_FLAGTIME,
        {
            PR_MESSAGE_FLAGS,
            PR_CLIENT_SUBMIT_TIME,
            PR_SUBMIT_FLAGS
        }
    };
#define NUM_RECIP_COLS  2
    const static SizedSPropTagArray(NUM_RECIP_COLS, proptagRecips) =
    {
        NUM_RECIP_COLS,
        {
            PR_ROWID,           /* make sure this stays first */
            PR_RESPONSIBILITY
        }
    };

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            SubmitMessage,
            (pimsg, 
            ulFlags));

    IMSG_EnterCriticalSection(pimsg);

    pims = pimsg->pims;

    if (OBJ_TestFlag(pimsg, MSGF_MSGINMSG))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    if (!OBJ_TestFlag(pimsg, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* Get message flag to check for resubmit. */

    hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pims->lmr,
        PR_MESSAGE_FLAGS, &ulMF);
    if (hr != hrSuccess)
        goto exit;

    /* Check to see if the message was already submitted. If so, clear the */
    /* Preprocess bit in PR_SUBMIT_FLAGS, save the message, and update the */
    /* outgoing queue. */

    if (ulMF & MSGFLAG_SUBMIT)
    {
        ULONG ulSF;

        AssertSz(OBJ_TestFlag(pimsg->pims, MSF_SPOOLER),
            "Message being resubmitted by other than the spooler");
        
        hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pims->lmr,
            PR_SUBMIT_FLAGS, &ulSF);
        if (hr != hrSuccess)
        {
            if (GetScode(hr) == MAPI_E_NOT_FOUND)
            {
                TraceSz1 ("SAMPLE MS: IMSG_SubmitMessage: Error %s getting "
                    "PR_SUBMIT_FLAGS during resubmit.",
                    SzDecodeScode(GetScode(hr)));

                hr = hrSuccess;
                ulSF = 0;
            }
            else
                goto exit;
        }

        ulSF &= ~SUBMITFLAG_PREPROCESS;

        hr = HrSetSingleProp((LPMAPIPROP) pimsg->lpmsg, &pims->lmr,
            PR_SUBMIT_FLAGS, &ulSF);
        if (hr != hrSuccess)
            goto exit;
    }
    else
    {
        /* Begin by making sure that all recipients have a PR_RESPONSIBILITY */
        /* property. If they don't, we need to put it in. */
    
        hr = pimsg->lpmsg->lpVtbl->GetRecipientTable(pimsg->lpmsg, 0L,
            &pmtRecip);
        if (hr != hrSuccess)
            goto exit;
    
        /* Get all columns and ensure that the PR_ROWID and PR_RESPONSIBILITY */
        /* columns are the first two table columns using the MAPI API function */
        /* HrAddColumns. */
    
        hr = HrAddColumns(pmtRecip, (LPSPropTagArray) &proptagRecips,
            pims->lmr.lpAllocBuf, pims->lmr.lpFreeBuf);
        if (hr != hrSuccess)
            goto exit;
    
        /* Check for PR_RESPONSIBILITY in each table row and set it if it's */
        /* missing. */
    
        while (TRUE)
        {
            LPSRow prw;
            LPSRow prwMac;
            LPSPropValue pvalT;
    
            /* Get 10 rows at a time. In general, GetRowCount may not */
            /* be supported by every provider. This loop does not count */
            /* on it working, even though I know that it would in this */
            /* implementation. */
    
            hr = pmtRecip->lpVtbl->QueryRows(pmtRecip, 10, 0L, &prws);
            if (hr != hrSuccess)
                goto exit;
    
            /* All table implementations will return zero rows from QueryRows */
            /* when you're actually at the end of the table. This routine */
            /* uses that to test when to exit this loop. Note that this loop */
            /* doesn't need to check for no recipients at all, because */
            /* ExpandRecips (below) will do that as part of its processing. */
            if (prws->cRows == 0)
                break;
    
            prw = prws->aRow;
            prwMac = prw + prws->cRows;
    
            /* Loop through the rows. For each row, put in PR_RESPONSIBILITY */
            /* if it's missing. Don't change recipients that already have */
            /* a PR_RESPONSIBILITY property (due to resubmission). */
    
            while (prw < prwMac)
            {
                AssertSz(prw->cValues >= NUM_RECIP_COLS,
                    "Bad # of values returned");
        
                pvalT = prw->lpProps;
        
                AssertSz(!IsBadReadPtr(pvalT, (UINT) prws->aRow->cValues
                    * sizeof(SPropValue)), "Bad pval array");
        
                /* PR_ROWID is in column zero. Leave it alone, and start */
                /* with the next column. */
                ++pvalT;
        
                /* We don't ever want responsibility for any recipient. */
                /* If this isn't the spooler calling, then force ALL */
                /* responsibilities to FALSE regardless of what they were. */
                if (PROP_TYPE(pvalT->ulPropTag) == PT_NULL
                    || !OBJ_TestFlag(pimsg->pims, MSF_SPOOLER))
                {
                    pvalT->ulPropTag = PR_RESPONSIBILITY;
                    pvalT->Value.b = FALSE;
                }
    
                ++prw;
            }
    
            /* modify the rows */
            hr = pimsg->lpmsg->lpVtbl->ModifyRecipients(pimsg->lpmsg,
                MODRECIP_MODIFY, (LPADRLIST) prws);
            if (hr != hrSuccess)
                goto exit;
    
            FreeProws(prws);
            prws = NULL;
        }
    
        /* We're done with the recip table now, so release it. */
        UlRelease(pmtRecip);
        pmtRecip = NULL;
    
        ulPrepareFlags = 0;
    
        hr = pims->psup->lpVtbl->PrepareSubmit(pims->psup, pimsg->lpmsg,
            &ulPrepareFlags);
        if (hr != hrSuccess)
            goto exit;
    
        /* ExpandRecips checks for no recip, and will return an error. */
        /* Therefore, this code doesn't need to check here for that case. */
    
        hr = pims->psup->lpVtbl->ExpandRecips(pims->psup, pimsg->lpmsg,
            &ulPreprocess);
        if (hr != hrSuccess)
            goto exit;
    
        /* Now, your store provider, if it wishes, may take responsibility */
        /* for any recipients that it wishes to handle. (For example, if */
        /* it is tightly coupled to a transport.) */
    
        /* Get the time to add to the message as PR_CLIENT_SUBMIT_TIME */
        GetSystemTime(&st);
        SideAssert(SystemTimeToFileTime(&st, &ft));
    
        /* get the old values of PR_MESSAGE_FLAGS & PR_CLIENT_SUBMIT_TIME */
    
        hr = pimsg->lpmsg->lpVtbl->GetProps(pimsg->lpmsg,
            (LPSPropTagArray) &proptagFlagTime, 0, /* ansi */
            &cValues, &pval);
        if (HR_FAILED(hr))
            goto exit;
    
        /* Warnings are OK from GetProps here. */
    
        /* turn on the MSGFLAG_SUBMIT bit of PR_MESSAGE_FLAGS */
        pval[0].ulPropTag = PR_MESSAGE_FLAGS;
        pval[0].Value.l = pval[0].Value.l | MSGFLAG_SUBMIT;
    
        /* set the client submission time */
        pval[1].ulPropTag = PR_CLIENT_SUBMIT_TIME;
        pval[1].Value.ft = ft;
    
        /* set the submit flag. If necessary, turn on the preprocess flag */
        pval[2].ulPropTag = PR_SUBMIT_FLAGS;
    
        if (ulPreprocess & NEEDS_PREPROCESSING)
            pval[2].Value.l = SUBMITFLAG_PREPROCESS;
        else
            pval[2].Value.l = 0L;
    
        hr = pimsg->lpmsg->lpVtbl->SetProps(pimsg->lpmsg, NUM_FLAGTIME, pval,
            &pprba);
        if (hr != hrSuccess || pprba)
            goto exit;
    }

    hr = pimsg->lpVtbl->SaveChanges(pimsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    /* add or update (for resubmit) the message in the outgoing queue */
    hr = HrUpdateOutgoingQueue(pims, pimsg, NULL, TABLE_ROW_ADDED);
    if (hr != hrSuccess)
        goto exit;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (pprba)
    {
        LMFree(&pims->lmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    UlRelease(pmtRecip);
    LMFree(&pims->lmr, pval);
    FreeProws(prws);

    if (hr == hrSuccess)
        OBJ_ClearFlag(pimsg, MSGF_NEWLYCREATED | OBJF_MODIFY);

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_SubmitMessage, hr);
    return HrCheckHr(hr, IMessage_SubmitMessage);
}

/*
 *  IMSG_SetReadFlag
 *
 *  Purpose:
 *      Sets the MSGFLAG_READ bit in the PR_MESSAGE_FLAGS property.
 *      In addition, it sends a read report to the originator, if
 *      appropriate.  A read report is only sent if the originator
 *      of the message requested it.  Applications generally cannot
 *      determine if a read report has been requested.
 *
 *  Arguments:
 *      pimsg       Pointer to the object.
 *      ulFlags     Flags.  SUPPRESS_RECEIPT
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      In order to generate a read report, a new message is
 *      created which gets filled in by MAPI and then submitted.
 *      This message will be in the same folder as pimsg, and will
 *      have the same filename, except that it will have the read
 *      receipt filename extension (.rrt) instead of the normal
 *      message filename extension (.msg).
 *
 *  Errors:
 *      All errors associated with property modification, message
 *      creation, or message submission.
 */
STDMETHODIMP IMSG_SetReadFlag(PIMSG pimsg, ULONG ulFlags)
{
    HRESULT hr;
    LPTSTR szFull = NULL;
    PEID peidCopy = NULL;
    PIMSG pimsgRRT = NULL;
    PIFLD pifldParent = NULL;
    ULONG ulObjType = 0L;
    PEID peidCopyFld = NULL;
    ULONG ulSeqNumber;
    PLMR plmr;
    WORD fRR;
    ULONG ulMF;
    LONG lUnreadChange;

    MSG_ValidateParameters(
            pimsg,
            IMessage,
            SetReadFlag,
            (pimsg, 
            ulFlags));

    IMSG_EnterCriticalSection(pimsg);

    plmr = &pimsg->pims->lmr;

    hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, plmr, PR_MESSAGE_FLAGS,
        &ulMF);
    if (hr != hrSuccess)
        goto exit;

    /* if the flag is already set correctly, don't do anything. */
    if (ulFlags & CLEAR_READ_FLAG)
    {
        if (!(ulMF & MSGFLAG_READ))
            goto exit;
        ulMF &= ~MSGFLAG_READ;

        lUnreadChange = 1;
    }
    else
    {
        if (ulMF & MSGFLAG_READ)
            goto exit;
        else
            ulMF |= MSGFLAG_READ;

        lUnreadChange = -1;
    }

    hr = HrSetSingleProp((LPMAPIPROP) pimsg->lpmsg, plmr, PR_MESSAGE_FLAGS, &ulMF);
    if (hr != hrSuccess)
        goto exit;

    hr = HrOpenParent(pimsg->pims, pimsg->peid, MAPI_MODIFY, &pifldParent);
    if (hr != hrSuccess)
        goto exit;

    /* see if read receipts are requested */
    hr = HrGetSingleProp((LPMAPIPROP) pimsg->lpmsg, plmr,
        PR_READ_RECEIPT_REQUESTED, &fRR);

    if (hr == hrSuccess
        && !(ulFlags & SUPPRESS_RECEIPT)
        && fRR
        && lUnreadChange == -1)
    {
        PIFLD pifldRoot = NULL;
        ULONG ulObjType;

        NFSideAssertSz(pimsg->peid,
            "PR_READ_RECEIPT_REQUESTED set on a message in a message ");

        /* Open the root folder */
        hr = pimsg->pims->lpVtbl->OpenEntry(pimsg->pims, 0, NULL,
            NULL, 0L, &ulObjType, (LPUNKNOWN *) &pifldRoot);
        if (hr != hrSuccess)
            goto exit;

        Assert(ulObjType == MAPI_FOLDER);

        /* Create a read receipt message in the root folder and call */
        /* IMAPISupport::ReadReceipt */

        hr = HrNewEID(pifldRoot, pimsg->pims, READRECEIPT_EXT,
            &ulSeqNumber, &peidCopy);

        UlRelease(pifldRoot);

        if (hr != hrSuccess)
            goto exit;

        hr = HrNewIMSG(peidCopy, pimsg->pims, TRUE, TRUE, ulSeqNumber,
                &szFull, &pimsgRRT);
        if (hr != hrSuccess)
            goto exit;

        hr = InitIMSGProps(pimsgRRT);
        if (hr != hrSuccess)
            goto exit;

        hr = pimsg->pims->psup->lpVtbl->ReadReceipt(pimsg->pims->psup, 0L,
            (LPMESSAGE) pimsg, (LPMESSAGE *) &pimsgRRT);
        if (hr != hrSuccess)
            goto exit;

        /* If ReadReceipt didn't release and NULL the returned message, */
        /* then submit it. */

        if (pimsgRRT)
        {
            hr = pimsgRRT->lpVtbl->SubmitMessage(pimsgRRT, FORCE_SUBMIT);
            if (hr != hrSuccess)
                goto exit;
        }
    }

    hr = pimsg->lpVtbl->SaveChanges(pimsg, KEEP_OPEN_READWRITE);
    if (HR_FAILED(hr))
        goto exit;

    /* Update the folder properties file -- WARNING:  if we fail from   */
    /* now until the end of the procedure, the folder unread count will */
    /* be inconsistent with the actual unread messages in this folder,  */
    /* and we have no transactional way of backing out changes.         */
    /* don't change folder properties for a message in a message        */

    if (!OBJ_TestFlag(pimsg, MSGF_MSGINMSG))
    {
        hr = HrIncrementOneROProp(pifldParent, lUnreadChange, PR_CONTENT_UNREAD);

        #ifdef DEBUG
        if (HR_FAILED(hr))
            TraceSz1("Sample MS: IMSG_SetReadFlag: error %s changing the "
                "unread count on a folder.", SzDecodeScode(GetScode(hr)));
        #endif

        /* Ignore the error. It isn't fatal. */
        hr = hrSuccess;
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    UlRelease(pimsgRRT);

    FreeNull(szFull);
    LMFree(plmr, peidCopy);
    LMFree(plmr, peidCopyFld);
    UlRelease(pifldParent);

    IMSG_LeaveCriticalSection(pimsg);

    DebugTraceResult(IMSG_SetReadFlag, hr);
    return HrCheckHr(hr, IMessage_SetReadFlag);
}

/*
 *  External functions (called from outside of this file).
 */

/*
 *  HrNewIMSG
 *
 *  Purpose:
 *      Allocates and initializes an IMSG object (internal
 *      implementation of IMessage).  Optionally creates storage
 *      for the object (else it tries to open existing storage).
 *
 *  Arguments:
 *      peid        Internal form of EntryID for message.
 *      pims        Message Store in which this message resides.
 *      fCreate     Boolean. TRUE means to create the storage for this message.
 *      fModify     Boolean. TRUE means to open the message for writing.
 *      ulSeqNum    The sequence number of the entryid.
 *      pszFull     Location in which to return the full pathname to the
 *                  file created or opened. If NULL, don't return the path.
 *      ppimsg      Location in which to return a pointer to the
 *                  newly created IMSG instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the IMSG instance.
 */
HRESULT HrNewIMSG(PEID peid, PIMS pims, BOOL fCreate, BOOL fModify,
    ULONG ulSeqNum, LPSTR *pszFull, PIMSG *ppimsg)
{
    HRESULT hr;
    LPTSTR szFull = NULL;

    LPMESSAGE lpmsg = NULL;
    PEID peidCopy = NULL;
    ULONG cbeid;
    PIMSG pimsgNew = NULL;
    BOOL fDoneCreate = FALSE;
    SCODE sc = S_OK;
    PEID peidParent = NULL;

    AssertSz(peid, "Bad peid");
    AssertSz(pims, "Bad pims");
    AssertSz(ppimsg, "Bad ppimsg");

    /* Get all the necessary parts of an IMSG */

    hr = HrFullPathName(pims->szStorePath, peid->szPath, NULL, &szFull);
    if (hr != hrSuccess)
        goto exit;

    ReplaceExt(szFull, MESSAGE_EXT);

    /* always open the internal message for modification so that */
    /* SetReadFlag will work. */

    hr = HrOpenIMsg(pims->pmsgsess, szFull, &pims->lmr, pims->psup, fCreate,
        TRUE, FALSE, &lpmsg);

    if (hr != hrSuccess)
        goto exit;

    if (fCreate)
        fDoneCreate = TRUE;

    cbeid = CbEID(peid);
    hr = HrAlloc(cbeid, (PPV) &peidCopy);
    if (hr != hrSuccess)
        goto exit;

    memcpy(peidCopy, peid, (UINT) cbeid);

    /* Allocate and initialize IMSG instance */

    sc = LMAllocZ(&pims->lmr, sizeof(IMSG), &pimsgNew);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    OBJ_Initialize(pimsgNew, &vtblIMSG, OT_MESSAGE, pims, pims->pcs);

    pimsgNew->peid = peidCopy;
    pimsgNew->lpmsg = lpmsg;

    if (fCreate)
    {
        OBJ_SetFlag(pimsgNew, MSGF_NEWLYCREATED);
        OBJ_SetFlag(pimsgNew, MSGF_FRESH);
    }
    else
    {
        ULONG ulMF;

        hr = HrGetSingleProp((LPMAPIPROP) lpmsg, &pims->lmr,
                PR_MESSAGE_FLAGS, &ulMF);
        if (hr != hrSuccess)
            goto exit;

        if (fModify
            && (ulMF & MSGFLAG_SUBMIT)
            && !OBJ_TestFlag(pims, MSF_SPOOLER))
        {
            hr = ResultFromScode(MAPI_E_SUBMITTED);
            goto exit;
        }
    }

    if (fModify)
        OBJ_SetFlag(pimsgNew, OBJF_MODIFY);

    hr = HrGetParentEID(&pims->lmr, peid, &peidParent);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetInternalProps(&pims->lmr, cpropIMSGInternal, &(pimsgNew->pval),
            &(pimsgNew->cval), peid, peidParent, ulSeqNum);
    if (hr != hrSuccess)
        goto exit;

    OBJ_Enqueue((POBJ) pimsgNew, (POBJ) pims);

exit:
    LMFree(&pims->lmr, peidParent);

    if (hr != hrSuccess)
    {
        UlRelease(lpmsg);
        FreeNull(peidCopy);
        if (fDoneCreate)
            DeleteFile(szFull);

        if (pimsgNew)
            LMFree(&pims->lmr, pimsgNew->pval);

        LMFree(&pims->lmr, pimsgNew);
        FreeNull(szFull);
    }
    else
    {
        *ppimsg = pimsgNew;

        if (pszFull)
            *pszFull = szFull;
        else
            FreeNull(szFull);
    }

    DebugTraceResult(HrNewIMSG, hr);
    return hr;
}

/*
 *  IMSG_Neuter
 *
 *  Purpose:
 *      Neuters an IMSG
 *
 *  Parameter
 *      pimsg       pointer to IMSG to be neutered
 */
void IMSG_Neuter(PIMSG pimsg)
{
    /* Free IMSG object's internal memory */

    UlRelease(pimsg->lpmsg);

    LMFree(&pimsg->pims->lmr, pimsg->pval);

    /* delete the file if it was never saved */
    if (OBJ_TestFlag(pimsg, MSGF_NEWLYCREATED))
    {
        LPTSTR szFull = NULL;   /* full path name of message */

        /* delete the file */
        if (HrFullPathName(pimsg->pims->szStorePath, pimsg->peid->szPath,
                NULL, &szFull) == hrSuccess)
        {
            ReplaceExt(szFull, MESSAGE_EXT);
            DeleteFile(szFull);
            FreeNull(szFull);
        }
    }

    FreeNull(pimsg->peid);
}

/*
 *  NewIMSGInIATCH
 *
 *  Purpose:
 *      Wraps an IMSG object around a message that is contained in
 *      an attachment (message in message).  A message in message
 *      has no EntryID, does not expose a PR_STORE_ENTRYID or
 *      PR_STORE_RECORD_KEY, and cannot be submitted.
 *
 *  Arguments:
 *      lpmsg       Message in message we get back from the
 *                  IMessage on IStorage implementation.
 *      pobj        Pointer to the parent object of the msg-in-msg.
 *      ulFlags     ulFlags from OpenProperty call
 *      ppimsg      Address in which to place a pointer to the
 *                  newly created IMSG instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the IMSG instance.
 */
HRESULT NewIMSGInIATCH(LPMESSAGE lpmsg, POBJ pobj, ULONG ulFlags, PIMSG *ppimsg)
{
    PIMSG pimsgNew = NULL;
    SCODE sc = S_OK;
    PIMS pims;

    AssertSz(lpmsg, "Bad lpmsg");
    AssertSz(pobj, "Bad pobj");
    AssertSz(ppimsg, "Bad ppimsg");

    pims = pobj->pims;

    /* Allocate and initialize IMSG instance */

    sc = LMAllocZ(&pims->lmr, sizeof(IMSG), (LPVOID *) &pimsgNew);
    if (sc != S_OK)
        goto exit;

    OBJ_Initialize(pimsgNew, &vtblIMSG, OT_MESSAGE, pims, pims->pcs);

    OBJ_SetFlag(pimsgNew, MSGF_MSGINMSG);

    if(ulFlags & MAPI_MODIFY)
        OBJ_SetFlag(pimsgNew, OBJF_MODIFY);

    pimsgNew->peid = NULL;
    pimsgNew->lpmsg = lpmsg;

    OBJ_Enqueue((POBJ) pimsgNew, pobj);

    *ppimsg = pimsgNew;

exit:
    if (sc != S_OK)
        LMFree(&pims->lmr, pimsgNew);

    DebugTraceSc(NewIMSGInIATCH, sc);
    return ResultFromScode(sc);
}

/*
 *  InitIMSGProps
 *
 *  Purpose:
 *      Sets the initial (and for read-only properties, the only)
 *      values for the base properties of the Message Object:
 *      takes as input parameters the values of those properties
 *      that are specific to this message and derives the values of
 *      those properties that are identical for all messages in the
 *      Microsoft Sample Store Provider.
 *
 *  Arguments:
 *      pimsg       Internal IMessage object instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the property arrays.
 */
HRESULT InitIMSGProps(PIMSG pimsg)
{
    HRESULT hr = hrSuccess;
    LPSPropValue pval = NULL;
    LPSPropProblemArray pprba = NULL;
    LPSPropTagArray ptaga = NULL;
    LPSPropAttrArray patra = NULL;
    ULONG cpropInit = 0L;
    BOOL fMsgInMsg;
    MAPIUID uid;
    PIMS pims;
    LPMESSAGE lpmsg;

    AssertSz(pimsg, "Bad pimsg");

    if (OBJ_TestFlag(pimsg, MSGF_MSGINMSG))
    {
        AssertSz(pimsg->peid == NULL, "Msg in msg has no entryid");

        fMsgInMsg = TRUE;
        cpropInit = cpropMsgInMsgInit;
    }
    else
    {
        fMsgInMsg = FALSE;
        cpropInit = cpropIMSGInit;
    }

    pims = pimsg->pims;
    lpmsg = pimsg->lpmsg;

    /* Allocate the property arrays. */
    hr = HrAllocPropArrays(cpropInit, &pval, &ptaga, &patra);
    if (hr != hrSuccess)
        goto exit;

    /* Initialize property value array and all property tags. */

    ptaga->cValues = patra->cValues = cpropInit;

    pval[0].ulPropTag = ptaga->aulPropTag[0] = PR_OBJECT_TYPE;
    pval[0].Value.l = MAPI_MESSAGE;
    pval[1].ulPropTag = ptaga->aulPropTag[1] = PR_MESSAGE_FLAGS;

    /* When the spooler creates a message, it is arriving into the store. */
    /* Therefore, the message should be unread, sent and unmodified. When */
    /* the client creates a message, it is unsent, read, and unmodified. */

    if (OBJ_TestFlag(pims, MSF_SPOOLER))
        pval[1].Value.l = MSGFLAG_UNMODIFIED;
    else
        pval[1].Value.l = MSGFLAG_READ | MSGFLAG_UNSENT | MSGFLAG_UNMODIFIED;

    pval[2].ulPropTag = ptaga->aulPropTag[2] = PR_MESSAGE_CLASS;
    pval[2].Value.LPSZ = TEXT("IPM");

    if (!fMsgInMsg)
    {
        hr = pims->psup->lpVtbl->NewUID(pims->psup, &uid);
        if (hr != hrSuccess)
            goto exit;

        pval[3].ulPropTag = ptaga->aulPropTag[3] = PR_SEARCH_KEY;
        pval[3].Value.bin.cb = sizeof(uid);
        pval[3].Value.bin.lpb = (LPBYTE) &uid;
        pval[4].ulPropTag = ptaga->aulPropTag[4] = PR_STORE_ENTRYID;
        pval[4].Value.bin.cb = pims->eidStore.cb;
        pval[4].Value.bin.lpb = pims->eidStore.lpb;
        pval[5].ulPropTag = ptaga->aulPropTag[5] = PR_STORE_RECORD_KEY;
        pval[5].Value.bin.cb = sizeof(pims->uidResource);
        pval[5].Value.bin.lpb = (LPBYTE) &pims->uidResource;
        pval[6].ulPropTag = ptaga->aulPropTag[6] = PR_MSG_STATUS;
        pval[6].Value.l = 0;

        /* Set PR_ENTRYID, PR_PARENT_ENTRYID, PR_RECORD_KEY and 
         * PR_INSTANCE_KEY to null strings to keep clients from writing over
         * them. We get the actual values internally.
         */
        pval[7].ulPropTag = ptaga->aulPropTag[7] = PR_ENTRYID;
        pval[7].Value.bin.cb = 1;
        pval[7].Value.bin.lpb = (LPBYTE) "";
        pval[8].ulPropTag = ptaga->aulPropTag[8] = PR_PARENT_ENTRYID;
        pval[8].Value.bin.cb = 1;
        pval[8].Value.bin.lpb = (LPBYTE) "";
        pval[9].ulPropTag = ptaga->aulPropTag[9] = PR_RECORD_KEY;
        pval[9].Value.bin.cb = 1;
        pval[9].Value.bin.lpb = (LPBYTE) "";
        pval[10].ulPropTag = ptaga->aulPropTag[10] = PR_INSTANCE_KEY;
        pval[10].Value.bin.cb = 1;
        pval[10].Value.bin.lpb = (LPBYTE) "";

        /* this message is not complete until changes have been saved */
        /* mark it as such so that others don't see a partial message */
    }

    /* Initialize the property attribute array. */

    patra->aPropAttr[0] = grfpropattrIMSGInit;
    patra->aPropAttr[1] = grfpropattrIMSGInit | PROPATTR_WRITEABLE;
    patra->aPropAttr[2] = grfpropattrIMSGInit | PROPATTR_WRITEABLE;

    if (!fMsgInMsg)
    {
        patra->aPropAttr[3] = grfpropattrIMSGInit | PROPATTR_WRITEABLE;
        patra->aPropAttr[4] = grfpropattrIMSGInit;
        patra->aPropAttr[5] = grfpropattrIMSGInit;
        patra->aPropAttr[6] = grfpropattrIMSGInit;
        patra->aPropAttr[7] = grfpropattrIMSGInit;
        patra->aPropAttr[8] = grfpropattrIMSGInit;
        patra->aPropAttr[9] = grfpropattrIMSGInit;
        patra->aPropAttr[10] = grfpropattrIMSGInit;
    }

    /* Set the property values. */

    hr = lpmsg->lpVtbl->SetProps(lpmsg, cpropInit, pval, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    /* Set the property attributes. */

    hr = SetAttribIMsgOnIStg(lpmsg, ptaga, patra, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    /* If we succeeded up to this point, commit the properties. */

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);
    /* if (hr), fall through to exit */

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No warning expected");

    if (pprba)
    {
        LMFree(&pims->lmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    FreePropArrays(&pval, &ptaga, &patra);

    DebugTraceResult(InitIMSGProps, hr);
    return hr;
}

/*
 *  HrSetFlags
 *
 *  Purpose
 *      Set the value of flag bits on a message property. The
 *      properties that this function is used for are PR_MESSAGE_FLAGS
 *      and PR_SUBMIT_FLAGS.
 *
 *  Parameters
 *      pimsg       A pointer to the message object.
 *      ulAction    SET or UNSET
 *      ulPropTag   the property tag to be changed.
 *      ulFlag      flags to be set or unset.
 */
HRESULT HrSetFlags(PIMSG pimsg, ULONG ulAction, ULONG ulPropTag, ULONG ulFlag)
{
    HRESULT hr;
    LPSPropValue pval = NULL;

    AssertSz1(ulPropTag == PR_MESSAGE_FLAGS || ulPropTag == PR_SUBMIT_FLAGS,
        "HrSetFlags: not designed for property %s", SzDecodeUlPropTag(ulPropTag));

    AssertSz1((ulAction == SET) || (ulAction == UNSET), "Bad ulAction: %08lX",
        ulAction);

    /* get the current value of the flag */
    hr = HrGetOneProp((LPMAPIPROP) pimsg, ulPropTag, &pval);

    /* compute and set the new value */
    if (HR_SUCCEEDED(hr))
    {
        LONG lOldFlag = pval->Value.l;

        if (ulAction & SET)
            pval->Value.l |= ulFlag;
        else
            pval->Value.l &= ~ulFlag;

        /* If the value that's there is correct, then don't set it. */

        if (pval->Value.l == lOldFlag)
            goto exit;
    }
    else if (GetScode(hr) == MAPI_E_NOT_FOUND)
    {
        pval->Value.l = (ulAction & SET) ? ulFlag : 0L;
        pval->ulPropTag = ulPropTag;
    }
    else
        goto exit;

    hr = HrSetOneProp((LPMAPIPROP) pimsg, pval);

exit:
    LMFree(&pimsg->pims->lmr, pval);

    return hr;
}

/*
 *  HrSetInternalProps
 *
 *  Purpose
 *      Sets up the in-memory array to hold properties that may change
 *      when the message or folder object is moved or copied. See the
 *      routine ProcessGetProps in mspmisc.c for details of how this
 *      array is used.
 *
 *  Parameters
 *      plmr: A pointer to the linked memory allocation routines.
 *      cprop: The number of properties to set into the in-memory array.
 *          Note that the properties that are saved in-memory are placed
 *          into the array in a hard-coded order (see below). Therefore,
 *          changing cprop to a smaller number eliminates specific props
 *          from the array.
 *      ppval: A pointer to the location to place the in-memory pval array.
 *      pcval: A pointer to the location to place the number of properties
 *          placed into *ppval.
 *      peid: The object's entryid that we are saving in-memory props for.
 *          (Used to get the value for PR_ENTRYID and PR_INSTANCE_KEY).
 *      peidParent: The entryid of the parent object. (Used to get the value
 *          for PR_PARENT_ENTRYID).
 *      ulSeqNum: The value with which to fill PR_RECORD_KEY. (Only used
 *          on message objects).
 *
 *  Returns
 *      HRESULT. Only errors are from memory allocation failures.
 */
HRESULT HrSetInternalProps(PLMR plmr, ULONG cprop, LPSPropValue *ppval,
    ULONG *pcval, PEID peid, PEID peidParent, ULONG ulSeqNum)
{
    LPSPropValue pval = NULL;
    LPSPropValue pvalT;
    LPSPropValue pvalTMac;
    SCODE sc;

    AssertSz(*ppval == NULL, "pval already allocated");
    AssertSz(*pcval == 0, "cval already non-zero");

    /* Allocate the property array. */
    sc = LMAlloc(plmr, cprop * sizeof(SPropValue), &pval);
    if (sc != S_OK)
        goto exit;

    pvalT = pval;
    pvalTMac = pvalT + cprop;

    if (pvalT < pvalTMac)
    {
        sc = ScFillOneSBPval(plmr, (LPVOID) pval, PR_ENTRYID,
            CbEID(peid), (LPBYTE) peid, pvalT);
        if (sc != S_OK)
            goto exit;
    
        pvalT++;
    }

    if (pvalT < pvalTMac)
    {
        sc = ScFillOneSBPval(plmr, (LPVOID) pval, PR_INSTANCE_KEY,
            CbEID(peid), (LPBYTE) peid, pvalT);
        if (sc != S_OK)
            goto exit;
    
        pvalT++;
    }

    if (pvalT < pvalTMac)
    {
        sc = ScFillOneSBPval(plmr, (LPVOID) pval, PR_PARENT_ENTRYID,
            CbEID(peidParent), (LPBYTE) peidParent, pvalT);
        if (sc != S_OK)
            goto exit;

        pvalT++;
    }

    if (pvalT < pvalTMac)
    {
        sc = ScFillOneSBPval(plmr, (LPVOID) pval, PR_RECORD_KEY,
            sizeof(ulSeqNum), (LPBYTE) &ulSeqNum, pvalT);
        if (sc != S_OK)
            goto exit;

        pvalT++;
    }

    AssertSz(pvalT == pvalTMac, "Not enough values to fill internal array");

    *pcval = cprop;
    *ppval = pval;

exit:
    if (sc != S_OK)
        LMFree(plmr, pval);

    DebugTraceSc(HrSetInternalProps, sc);
    return ResultFromScode(sc);
}

/*
 * Internal functions (called only from within this file).
 *
 */

/* HrSaveMsgInMsg
 *
 * Perform the necessary steps to save changes on a msg-in-msg type message.
 *
 */
static HRESULT HrSaveMsgInMsg(PIMSG pimsg, ULONG ulFlags)
{
    ULONG ulPropMsgFlags = ulFlags;

    if (!(ulFlags & KEEP_OPEN_READWRITE))
        ulPropMsgFlags |= KEEP_OPEN_READONLY;

    return pimsg->lpmsg->lpVtbl->SaveChanges(pimsg->lpmsg, ulPropMsgFlags);
}

/* Fills in an SBinary PropValue via AllocMore. */

static SCODE ScFillOneSBPval(PLMR plmr, LPVOID pvOrigBuf, ULONG ulPropTag,
    ULONG cb, LPBYTE lpbData, LPSPropValue pval)
{
    SCODE sc;

    sc = LMAllocMore(plmr, cb, pvOrigBuf, &(pval->Value.bin.lpb));
    if (sc == S_OK)
    {
        pval->ulPropTag = ulPropTag;
        pval->Value.bin.cb = cb;
        if (cb)
            memcpy(pval->Value.bin.lpb, lpbData, (UINT) cb);
    }

    return sc;
}


