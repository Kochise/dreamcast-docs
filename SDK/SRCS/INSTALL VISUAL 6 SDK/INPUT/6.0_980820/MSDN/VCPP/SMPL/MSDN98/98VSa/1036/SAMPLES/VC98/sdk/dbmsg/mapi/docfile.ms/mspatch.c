/*
 *  M S P A T C H . C
 *
 *  Code for the MAPI Sample Store Provider implementation of the
 *  IAttach object.  The implementation is, in reality, a thin
 *  wrapping layer around the implementation of IMessage on
 *  IStorage.  We wrap the IAttach object returned by IMsgOnIStg so
 *  that we can handle those methods (like GetLastError) not
 *  understood by a standalone attachment (e.g. one embedded in a
 *  word document) but which makes sense for a message in the
 *  context of a message store.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

#define ATCH_ValidateParameters(pobj, intf, method, arglist)        \
        OBJ_ValidateParameters(pobj, intf, method, sizeof(IATCH), &vtblIATCH, arglist)

#define IATCH_EnterCriticalSection(piatch) OBJ_EnterCriticalSection((POBJ)piatch)
#define IATCH_LeaveCriticalSection(piatch) OBJ_LeaveCriticalSection((POBJ)piatch)

/* Manifest constants */

#define cInitIATCHProps         3
#define grfInitIATCHPropAttr    (PROPATTR_MANDATORY | PROPATTR_READABLE)

/* Global variables */

/* Dispatch table for IAttach objects */
IATCH_Vtbl vtblIATCH =
{
    (IATCH_QueryInterface_METHOD *)     OBJ_QueryInterface,
    (IATCH_AddRef_METHOD *)             OBJ_AddRef,
    (IATCH_Release_METHOD *)            OBJ_Release,
    (IATCH_GetLastError_METHOD *)       IMS_GetLastError,
    IATCH_SaveChanges,
    IATCH_GetProps,
    IATCH_GetPropList,
    IATCH_OpenProperty,
    IATCH_SetProps,
    IATCH_DeleteProps,
    IATCH_CopyTo,
    IATCH_CopyProps,
    (IATCH_GetNamesFromIDs_METHOD *)    IMS_GetNamesFromIDs,
    (IATCH_GetIDsFromNames_METHOD *)    IMS_GetIDsFromNames
};

/*
 *  Object methods
 */

/*
 *  IATCH_SaveChanges
 *
 *  Purpose:
 *      Saves changes made to an attachment object and all of its
 *      sub-objects (messages, et al.).  Since the IMessage on
 *      IStorage implementation handles the invalidation of objects
 *      after SaveChanges is called, we do not need to worry about
 *      it at this level.
 *
 *  Arguments:
 *      piatch      Pointer to the object.
 *      ulFlags     Flags.  The following are defined:
 *                  KEEP_OPEN_READONLY  Do not invalidate the
 *                                      object, make it read-only.
 *                  KEEP_OPEN_READWRITE Don't invalidate the
 *                                      object, keep it open
 *                                      read/write.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 */
STDMETHODIMP IATCH_SaveChanges(PIATCH piatch, ULONG ulFlags)
{
    HRESULT hr;
    PIMSG pimsg;
    PLMR plmr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            SaveChanges,
            (piatch, 
            ulFlags));

    IATCH_EnterCriticalSection(piatch);

    pimsg = (PIMSG) piatch->pobjParent;
    plmr = &piatch->pims->lmr;

    if (!OBJ_TestFlag(piatch, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    hr = piatch->lpattach->lpVtbl->SaveChanges(piatch->lpattach, ulFlags);
    if (hr != hrSuccess)
        goto exit;

    if (!(ulFlags & KEEP_OPEN_READWRITE))
        OBJ_ClearFlag(piatch, OBJF_MODIFY);

exit:
    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_SaveChanges, hr);
    return HrCheckHr(hr, IMAPIProp_SaveChanges);
}

/*
 *  IATCH_GetProps
 *
 *  Purpose:
 *      Returns to the caller the value(s) of one or more
 *      properties existent on an IATCH object.  The order of the
 *      properties in the returned lppPropArray structure exactly
 *      matches the order in which the properties were requested in
 *      lpPropTagArray.  The caller must free the returned
 *      structure by calling MAPIFreeBuffer(*lppPropArray), but
 *      only if the function returns zero or the error
 *      MAPI_W_ERRORS_RETURNED.  Uses the IMessage on IStorage
 *      property interface implementation.
 *
 *  Arguments:
 *      piatch          Pointer to the object.
 *       ptaga          Pointer to a counted array of property tags of
 *                      properties requested
 *       ulFlags        UNICODE / String8
 *       pcval          Pointer to number of values returned
 *       ppval          Pointer to a variable in which the address of the
 *                      returned property values is placed
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
STDMETHODIMP IATCH_GetProps(PIATCH piatch, LPSPropTagArray ptaga, ULONG ulFlags,
    ULONG *pcval, LPSPropValue *ppval)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            GetProps,
            (piatch, 
            ptaga, 
            ulFlags,
            pcval, 
            ppval));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IATCH_EnterCriticalSection(piatch);

    /* Pass the call off to IMessage */
    hr = piatch->lpattach->lpVtbl->GetProps(piatch->lpattach, ptaga, ulFlags, 
            pcval, ppval);

    /* Wrap specific store properties. Note that this function takes as an */
    /* argument the HRESULT from the previous GetProps call. */
    /* We aren't ignoring the error. */

    hr = HrWrap_GetProps(hr, piatch->pims, 0, NULL, pcval, ppval, FALSE,
        (ptaga != NULL), (POBJ)piatch);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_GetProps, hr);
    return HrCheckHr(hr, IMAPIProp_GetProps);
}

/*
 *  IATCH_GetPropList
 *
 *  Purpose:
 *      Returns a list of all the properties currently accessible.
 *      Uses the IMessage on IStorage property implementation.
 *
 *  Arguments:
 *      piatch              Pointer to the object.
 *      ulFlags             UNICODE / String8
 *      lppPropTagArray     Location in which to return a pointer
 *                          to a counted array of property tags.
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
STDMETHODIMP
IATCH_GetPropList(PIATCH piatch, ULONG ulFlags, LPSPropTagArray *lppPropTagArray)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            GetPropList,
            (piatch, 
            ulFlags, 
            lppPropTagArray));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IATCH_EnterCriticalSection(piatch);

    hr = piatch->lpattach->lpVtbl->GetPropList(piatch->lpattach, ulFlags,
        lppPropTagArray);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_GetPropList, hr);
    return HrCheckHr(hr, IMAPIProp_GetPropList);
}

/*
 *  IATCH_OpenProperty
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
 *      piatch      Pointer to the object.
 *      ulPropTag   Property tag for the desired property.  Only
 *                  the ID bits of the tag are used; the type bits
 *                  are ignored.
 *      lpiid       Pointer to the GUID identifying which interface
 *                  is desired.
 *      lppUnk      Location in which to return a pointer to the
 *                  newly created interface pointer.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_CALL_FAILED      An error occurred opening a
 *                              supported interface.
 *      MAPI_E_NO_SUPPORT   The requested interface is not
 *                              available on the given property.
 */
STDMETHODIMP IATCH_OpenProperty(PIATCH piatch, ULONG ulPropTag, LPCIID lpiid,
    ULONG ulInterfaceOptions, ULONG ulFlags, LPUNKNOWN * lppUnk)
{
    HRESULT hr;
    LPUNKNOWN lpunk = NULL;
    PIMSG pimsg = NULL;
    LPSPropTagArray ptaga = NULL;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            OpenProperty,
            (piatch, 
            ulPropTag, 
            lpiid,
            ulInterfaceOptions, 
            ulFlags, 
            lppUnk));

    IATCH_EnterCriticalSection(piatch);

    /* If input parameters are okay, make OpenProperty call on lpmsg. */

    hr = piatch->lpattach->lpVtbl->OpenProperty(piatch->lpattach,
        ulPropTag, lpiid, ulInterfaceOptions, ulFlags, &lpunk);
    if (hr != hrSuccess)
        goto exit;

    /* If it's a message in message, we need to wrap the returned object */

    if (ulPropTag == PR_ATTACH_DATA_OBJ
        && IsEqualIID(lpiid, (LPIID) &IID_IMessage))
    {
        hr = NewIMSGInIATCH((LPMESSAGE) lpunk, (POBJ) piatch, ulFlags, &pimsg);
        if (hr != hrSuccess)
            goto exit;

        hr = pimsg->lpVtbl->GetPropList(pimsg, 0, /* ansi */
                &ptaga);
        if (hr != hrSuccess)
            goto exit;

        if (ptaga->cValues == 0)
        {
            hr = InitIMSGProps(pimsg);
            if (hr != hrSuccess)
                goto exit;
        }

        *lppUnk = (LPUNKNOWN) pimsg;
    }
    else
        *lppUnk = lpunk;

exit:
    LMFree(&piatch->pims->lmr, ptaga);

    if (hr != hrSuccess)
    {
        UlRelease(pimsg);
        UlRelease(lpunk);
    }

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_OpenProperty, hr);
    return HrCheckHr(hr, IMAPIProp_OpenProperty);
}

/*
 *  IATCH_SetProps
 *
 *  Purpose:
 *      Sets the value of one or more properties.  This call passes
 *      a number of Property Value structures.  The Property Tag in
 *      each indicates which property is having its values set and
 *      the value indicates what should be stored.  The caller must
 *      free the returned property problem structure by calling
 *      MAPIFreeBuffer(*pprba), but only if the call
 *      succeeded overall.  Uses the IMessage on IStorage property
 *      implementation.
 *
 *  Arguments:
 *      piatch          Pointer to the object.
 *      cValues         Number of values in pval.
 *      pval            Pointer to a Property Value array.
 *      pprba           Location in which to return a pointer to a
 *                      counted array of property problem
 *                      structures.
 *
 *  Returns:
 *      HRESULT.  If the call succeeds overall, a zero is returned.
 *      If there are problems with setting some or all of the
 *      selected values, and a non-NULL is passed for pprba,
 *      then a SPropProblemArray structure is returned with details
 *      about each problem.  The value returned in pprba is
 *      only valid if zero is returned in the HRESULT.  If an error
 *      occurs on the call such that a non-zero value is returned
 *      for the HRESULT then the contents of *pprba are
 *      undefined.  In particular, do not use or free the structure
 *      if an error occurs on the call.
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
STDMETHODIMP IATCH_SetProps(PIATCH piatch, ULONG cValues, LPSPropValue pval,
    LPSPropProblemArray *pprba)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            SetProps,
            (piatch, 
            cValues, 
            pval,
            pprba));

    IATCH_EnterCriticalSection(piatch);

    hr = piatch->lpattach->lpVtbl->SetProps(piatch->lpattach, cValues,
        pval, pprba);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_SetProps, hr);
    return HrCheckHr(hr, IMAPIProp_SetProps);
}

/*
 *  IATCH_DeleteProps
 *
 *  Purpose:
 *      Deletes the list of properties given in ptaga.
 *      The caller must free the returned property problem
 *      structure by calling MAPIFreeBuffer(*pprba), but only
 *      if the call succeeded overall.  Uses the IMessage on
 *      IStorage property implementation.
 *
 *  Arguments:
 *      piatch          Pointer to the object.
 *      ptaga   Pointer to an array of Property Tags
 *                      identifying the properties to delete.
 *      pprba       Location in which to return a pointer to a
 *                      counted array of property problem
 *                      structures.
 *
 *  Returns:
 *      HRESULT.  If the call succeeds overall, a zero is returned.
 *      If there are problems with deleting some or all of the
 *      selected values, and a non-NULL is passed for pprba,
 *      then a SPropProblemArray structure is returned with details
 *      about each problem.  The value returned in pprba is
 *      only valid if zero is returned in the HRESULT.  If an error
 *      occurs on the call such that a non-zero value is returned
 *      for the HRESULT then the contents of *pprba are
 *      undefined.  In particular, do not use or free the structure
 *      if an error occurs on the call.
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
STDMETHODIMP IATCH_DeleteProps(PIATCH piatch, LPSPropTagArray ptaga,
    LPSPropProblemArray * pprba)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            DeleteProps,
            (piatch, 
            ptaga,
            pprba));

    IATCH_EnterCriticalSection(piatch);

    hr = piatch->lpattach->lpVtbl->DeleteProps(piatch->lpattach, ptaga, pprba);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_DeleteProps, hr);
    return HrCheckHr(hr, IMAPIProp_DeleteProps);
}

/*
 *  IATCH_CopyTo
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
 *      piatch          Pointer to the source object.
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
 *      pprba       Pointer to a variable that is filled in
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
 *  Errors:
 */
STDMETHODIMP IATCH_CopyTo(PIATCH piatch, ULONG ciidExcl, LPCIID rgiidExcl,
    LPSPropTagArray ptagaExcl, ULONG ulUIParam, LPMAPIPROGRESS
    lpProgress, LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray * pprba)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            CopyTo,
            (piatch, 
            ciidExcl, 
            rgiidExcl,
            ptagaExcl, 
            ulUIParam, 
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags,
            pprba));

    IATCH_EnterCriticalSection(piatch);

    hr = piatch->lpattach->lpVtbl->CopyTo(piatch->lpattach, ciidExcl,
        rgiidExcl, ptagaExcl, ulUIParam, lpProgress, piidDst,
        lpDestObj, ulFlags, pprba);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_CopyTo, hr);
    return HrCheckHr(hr, IMAPIProp_CopyTo);
}

/*
 *  IATCH_CopyProps
 *
 *  Purpose:
 *      Copies the specified properties of the current object to a destination
 *      object.
 *
 *  Arguments:
 *      piatch          Pointer to the source object.
 *      ptagaIncl       Counted array of property tags of
 *                      properties that are to be copied to the
 *                      destination object.
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
 *                      MAPI_DECLINE_OK
 *      pprba       Pointer to a variable that is filled in
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
 *  Errors:
 */
STDMETHODIMP IATCH_CopyProps(PIATCH piatch,
    LPSPropTagArray ptagaIncl, ULONG ulUIParam, LPMAPIPROGRESS
    lpProgress, LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray * pprba)
{
    HRESULT hr;

    ATCH_ValidateParameters(
            piatch,
            IMAPIProp,
            CopyProps,
            (piatch,
            ptagaIncl, 
            ulUIParam, 
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags,
            pprba));

    IATCH_EnterCriticalSection(piatch);

    hr = piatch->lpattach->lpVtbl->CopyProps(piatch->lpattach,
        ptagaIncl, ulUIParam, lpProgress, piidDst,
        lpDestObj, ulFlags, pprba);

    IATCH_LeaveCriticalSection(piatch);

    DebugTraceResult(IATCH_CopyProps, hr);
    return HrCheckHr(hr, IMAPIProp_CopyProps);
}

/*
 *  External functions
 */

/*
 * IATCH_Neuter
 *
 * Purpose
 *  free storage for an attachment
 *
 * Parameter
 *      piatch      pointer to the open attachment
 *
 */
void IATCH_Neuter(PIATCH piatch)
{
    UlRelease(piatch->lpattach);
}

/*
 *  HrNewIATCH
 *
 *  Purpose:
 *      Allocates and initializes an IATCH object (internal
 *      implementation of IAttach).  This is just a thin wrapper
 *      around the attachment object of the IMessage on IStorage
 *      implementation -- we wrap it to catch certain methods,
 *      see below.
 *
 *  Arguments:
 *      lpattach    Pointer to an attachment object returned by
 *                  IMessage on IStorage.
 *      pimsg       Pointer to the attachment's parent message object.
 *      fModify     TRUE if the caller wants the attach opened for writing.
 *      ppiatch Location in which to return a pointer to the
 *                  newly created IATCH instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the IATCH instance.
 */
HRESULT HrNewIATCH(LPATTACH lpattach, PIMSG pimsg, BOOL fModify, PIATCH * ppiatch)
{
    HRESULT hr = hrSuccess;
    PIATCH piatchNew = NULL;
    SCODE sc;
    PIMS pims;

    AssertSz(lpattach, "Bad lpattach");
    AssertSz(pimsg, "Bad pimsg");
    AssertSz(ppiatch, "Bad ppiatch");

    pims = pimsg->pims;

    /* Allocate and initialize IATCH instance */

    sc = LMAllocZ(&pims->lmr, sizeof(IATCH), &piatchNew);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    /* Initialize member variables */

    OBJ_Initialize(piatchNew, &vtblIATCH, OT_ATTACH, pims, pims->pcs);

    UlAddRef(lpattach); /* we're keeping a reference */

    piatchNew->lpattach = lpattach;

    if (fModify)
        OBJ_SetFlag(piatchNew, OBJF_MODIFY);

    OBJ_Enqueue((POBJ) piatchNew, (POBJ) pimsg);

    *ppiatch = piatchNew;

exit:
    if (hr != hrSuccess)
        LMFree(&pims->lmr, piatchNew);

    DebugTraceResult(HrNewIATCH, hr);
    return hr;
}

