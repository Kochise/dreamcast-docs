/*
 *  M S P M S . C
 *
 *  Code for the MAPI Sample Store Provider implementation of the
 *  IMsgStore object.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"
#include <stdarg.h>

#define MS_ValidateParameters(pobj, intf, method, arglist)      \
        OBJ_ValidateParameters(pobj, intf, method, sizeof(IMS), &vtblIMS, arglist)

static HRESULT HrGetSequenceNum(PEID peid, ULONG *pulSequenceNum);
static HRESULT HrGetSMSStandardNotifKey(PIMS pims, PEID peid,
    LPNOTIFKEY * lppKey);

/* Dispatch table for IMsgStore objects */
IMS_Vtbl vtblIMS =
{
    (IMS_QueryInterface_METHOD *)   OBJ_QueryInterface,
    (IMS_AddRef_METHOD *)           OBJ_AddRef,
    (IMS_Release_METHOD *)          OBJ_Release,
    IMS_GetLastError,
    IMS_SaveChanges,
    IMS_GetProps,
    IMS_GetPropList,
    IMS_OpenProperty,
    IMS_SetProps,
    IMS_DeleteProps,
    IMS_CopyTo,
    IMS_CopyProps,
    IMS_GetNamesFromIDs,
    IMS_GetIDsFromNames,

    IMS_Advise,
    IMS_Unadvise,
    IMS_CompareEntryIDs,
    IMS_OpenEntry,
    IMS_SetReceiveFolder,
    IMS_GetReceiveFolder,
    IMS_GetReceiveFolderTable,
    IMS_StoreLogoff,
    IMS_AbortSubmit,

    IMS_GetOutgoingQueue,
    IMS_SetLockState,
    IMS_FinishedMsg,
    IMS_NotifyNewMail,
};

/* definitions for outgoing queues */
CALLERRELEASE OutgoingViewRelease;

/*
 *  Object methods
 */

/*
 *  IMS_GetLastError [also called by IMSLogon, IMAPIFolder, IMessage, and IAttach]
 *
 *  Purpose:
 *      Returns a localized text error message associated with the
 *      last error which occurred on a specific object (in
 *      actuality, the SCODE used is associated with the HRESULT
 *      passed in, and it is not checked that this HRESULT matches
 *      that of the last error on this object -- providing a
 *      different HRESULT will very likely return an inconsistent
 *      error message, though).
 *
 *  Arguments:
 *      pobj            Pointer to the object.
 *      hError          HRESULT containing the error code returned
 *                      by the last failed call on this object.
 *      ulFlags         MAPI_UNICODE, string8 is default
 *      pulLLErr        location to place the low level error code
 *                      (may be NULL)
 *      pszMessage      Location in which to return an address to
 *                      an allocated buffer containing the
 *                      localized text error message.
 *      pszComponent    Location in which to return an address to
 *                      an allocated buffer containing the
 *                      name of the component producing the error.
 *      lpulContext     Location in which to return a context number
 *                      for finding help within the Component's help file.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Unable to allocate memory for
 *                                  the return parameter.
 *      MAPI_E_INVALID_PARAMETER    hError contains an unknown
 *                                  SCODE.
 */
STDMETHODIMP IMS_GetLastError(PIMS pobj, HRESULT hError, ULONG ulFlags,
    LPMAPIERROR * lppMapiError)
{
    HRESULT hr = hrSuccess;
    SCODE   sc;
    PIMS pims;
    LPTSTR pszMessage   = NULL;
    
    #ifdef VALIDATE
    if (IsBadWritePtr(pobj, sizeof(OBJ))
        || (pobj->lpVtbl != (IMS_Vtbl *) &vtblIMS
            && pobj->lpVtbl != (IMS_Vtbl *) &vtblMSL
            && pobj->lpVtbl != (IMS_Vtbl *) &vtblIFLD
            && pobj->lpVtbl != (IMS_Vtbl *) &vtblIMSG
            && pobj->lpVtbl != (IMS_Vtbl *) &vtblIATCH))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);
        
    Validate_IMAPIProp_GetLastError(pobj, hError, ulFlags, lppMapiError);

    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    OBJ_EnterCriticalSection((POBJ) pobj);

    pims = pobj->pims;

    /* //$ Add param checking and correctly return Component & Context */
    *lppMapiError = NULL;
    
    sc = LMAlloc( &pims->lmr, sizeof( MAPIERROR ), lppMapiError );
    if ( FAILED( sc ) )
    {
        hr = ResultFromScode( sc );
        goto ret;
    }
    
    memset( *lppMapiError, 0, sizeof( MAPIERROR ) );
    
    (*lppMapiError)->ulVersion = MAPI_ERROR_VERSION;    

    hr = MapScodeSz(GetScode(hError), pims, &pszMessage);
    if ( HR_FAILED( hr ) )
        goto ret;
    
    sc = LMAllocMore( &pims->lmr, Cbtszsize( pszMessage ), *lppMapiError,
            &(*lppMapiError)->lpszError );
    
    if ( FAILED( sc ) )
    {
        hr = ResultFromScode( sc );
        goto ret;
    }
    
    lstrcpy( (*lppMapiError)->lpszError, pszMessage );

ret:
    
    if ( hr )   
    {
        LMFree( &pims->lmr, *lppMapiError );
        *lppMapiError = NULL;
    }
    
    LMFree( &pims->lmr, pszMessage );
    
    OBJ_LeaveCriticalSection(pobj);

    DebugTraceResult(IMS_GetLastError, hr);
    return HrCheckHr(hr, IUnknown_GetLastError);
}

/*
 *  IMS_SaveChanges [Also used by IMAPIFolder]
 *
 *  Purpose:
 *      Saves changes made to the message store object properties
 *      (does not propagate to sub-objects).  Because changes to
 *      message store object properties show up immediately,
 *      however, this call does nothing (but returns success).
 *
 *  Arguments:
 *      pims        Pointer to the object.
 *      ulFlags     Flags.  The following are defined:
 *                  KEEP_OPEN_READONLY  Do not invalidate the
 *                                      object, make it read-only.
 *                  KEEP_OPEN_READWRITE Don't invalidate the
 *                                      object, keep it open
 *                                      read/write.
 *                  FORCE_SAVE          Overwrite any changes made by
 *                                      others since store was opened
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_SaveChanges(PIMS pims, ULONG ulFlags)
{
    #ifdef VALIDATE
    if (    IsBadWritePtr(pims, sizeof(OBJ))
        ||  (   pims->lpVtbl != (IMS_Vtbl *) &vtblIMS
            &&  pims->lpVtbl != (IMS_Vtbl *) &vtblIFLD))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMAPIProp_SaveChanges(pims, ulFlags);
    #endif

    return hrSuccess;
}

/*
 *  IMS_GetProps
 *
 *  Purpose:
 *      Returns to the caller the value(s) of one or more
 *      properties existent on an IMS object.  The order of the
 *      properties in the returned ppval structure exactly
 *      matches the order in which the properties were requested in
 *      ptaga.  The caller must free the returned
 *      structure by calling MAPIFreeBuffer(*ppval), but
 *      only if the function returns zero or the error
 *      MAPI_W_ERRORS_RETURNED.  Uses the IMessage on IStorage
 *      property interface implementation.
 *
 *  Arguments:
 *      pims            Pointer to the object.
 *      ptaga           Pointer to a counted array of property tags
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
STDMETHODIMP IMS_GetProps(PIMS pims, LPSPropTagArray ptaga, ULONG ulFlags,
    ULONG *pcval, LPSPropValue *ppval)
{
    HRESULT hr = hrSuccess;
    LPMESSAGE lpmsg = NULL;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            GetProps,
            (pims, 
            ptaga, 
            ulFlags, 
            pcval, 
            ppval));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IMS_EnterCriticalSection(pims);

    /* If input parameters are okay, make GetProps call on lpmsgProps. */

    *pcval = 0L;
    *ppval = NULL;

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, FALSE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->GetProps(lpmsg, ptaga, ulFlags, pcval, ppval);

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
    /* Wrap the store entryids. Note that this function takes as an */
    /* argument the HRESULT from the previous GetProps call. */
    /* We aren't ignoring the error. */

    hr = HrWrap_GetProps(hr, pims, 0, NULL, pcval, ppval, TRUE,
        (ptaga != NULL), (POBJ)pims);

exit:
    UlRelease(lpmsg);

    IMS_LeaveCriticalSection(pims);

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_W_ERRORS_RETURNED)
        DebugTraceResult(IMS_GetProps, hr);
    #endif

    return HrCheckHr(hr, IMAPIProp_GetProps);
}

/*
 *  IMS_GetPropList
 *
 *  Purpose:
 *      Returns a list of all the properties currently accessible.
 *      Uses the IMessage on IStorage property implementation.
 *
 *  Arguments:
 *      pims        Pointer to the object.
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
 *                          to the requested properties.
 *      MAPI_E_CALL_FAILED  The mechanism for making the
 *                          call to the service provider
 *                          failed.
 */
STDMETHODIMP IMS_GetPropList(PIMS pims, ULONG ulFlags, LPSPropTagArray * pptaga)
{
    HRESULT hr = hrSuccess;
    LPMESSAGE lpmsg = NULL;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            GetPropList,
            (pims, 
            ulFlags, 
            pptaga));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif
        
    IMS_EnterCriticalSection(pims);

    /* If input parameters are okay, make GetPropList call on lpmsgProps. */

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, FALSE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->GetPropList(lpmsg, ulFlags, pptaga);
    /* if ( hr ) fall through to exit */

exit:
    UlRelease(lpmsg);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_GetPropList, hr);
    return HrCheckHr(hr, IMAPIProp_GetPropList);
}

/*
 *  IMS_OpenProperty
 *
 *  Purpose:
 *      Open a requested interface on a property for further
 *      access.  Commonly used for stream access to a large binary
 *      or text property.  This is the only way to access a
 *      property of type PT_OBJECT, and may be used on other
 *      properties depending on the implementation.  Uses the
 *      IMessage on IStorage property implementation, but since the
 *      transaction model for IMsgOnIStg does not match that for
 *      IMsgStore, we fail this call.  (We could do a lot of work
 *      to wrap the interface that IMsgOnIStg returns to us before
 *      returning it to the client, but we don't.)
 *
 *  Arguments:
 *      pims        Pointer to the object.
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
 *  Errors:
 *      MAPI_E_INVALID_PARAMETER
 *      MAPI_E_NO_SUPPORT   The requested interface is not
 *                              available on the given property.
 */
STDMETHODIMP IMS_OpenProperty(PIMS pims, ULONG ulPropTag, LPCIID lpiid,
    ULONG ulInterfaceOptions, ULONG ulFlags, LPUNKNOWN * lppUnk)
{
    SCODE sc;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            OpenProperty,
            (pims, 
            ulPropTag, 
            lpiid, 
            ulInterfaceOptions, 
            ulFlags, 
            lppUnk));

    sc = MAPI_E_NO_SUPPORT;
    
    DebugTraceSc(IFLD_OpenProperty, sc);
    return ResultFromScode(sc);
}

/*
 *  IMS_SetProps
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
 *      pims            Pointer to the object.
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
STDMETHODIMP IMS_SetProps(PIMS pims, ULONG cValues, LPSPropValue lpPropArray,
    LPSPropProblemArray * lppProblems)
{
    HRESULT hr = hrSuccess;
    LPMESSAGE lpmsg = NULL;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            SetProps,
            (pims, 
            cValues, 
            lpPropArray, 
            lppProblems));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* If input parameters are okay, make SetProps call on lpmsgProps. */

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SetProps(lpmsg, cValues, lpPropArray, lppProblems);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);
    /* if ( hr ), fall through to exit */

exit:
    UlRelease(lpmsg);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_SetProps, hr);
    return HrCheckHr(hr, IMAPIProp_SetProps);
}

/*
 *  IMS_DeleteProps
 *
 *  Purpose:
 *      Deletes the list of properties given in ptaga.
 *      The caller must free the returned property problem
 *      structure by calling MAPIFreeBuffer(*pprba), but only
 *      if the call succeeded overall.  Uses the IMessage on
 *      IStorage property implementation.
 *
 *  Arguments:
 *      pims    Pointer to the object.
 *      ptaga   Pointer to an array of Property Tags
 *              identifying the properties to delete.
 *      pprba   Location in which to return a pointer to a
 *              counted array of property problem
 *              structures.
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
 *      MAPI_E_CALL_FAILED      A general problem affecting
 *                                  access to all of the object's
 *                                  properties occurred.
 *      MAPI_E_CALL_FAILED          The mechanism for making the
 *                                  call to the service provider
 *                                  failed.
 */
STDMETHODIMP IMS_DeleteProps(PIMS pims, LPSPropTagArray ptaga,
    LPSPropProblemArray *pprba)
{
    HRESULT hr = hrSuccess;
    LPMESSAGE lpmsg = NULL;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            DeleteProps,
            (pims, 
            ptaga, 
            pprba));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    /* If input parameters are okay, make DeleteProps call on lpmsg. */

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->DeleteProps(lpmsg, ptaga, pprba);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);
    /* if ( hr ), fall through to exit */

exit:
    UlRelease(lpmsg);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_DeleteProps, hr);
    return HrCheckHr(hr, IMAPIProp_DeleteProps);
}

/*
 *  IMS_CopyTo
 *
 *  Purpose:
 *      Copies the contents of the current object to a destination
 *      object.  The entire contents, including contained objects,
 *      are copied, or optionally the caller can provide a list of
 *      properties that are not to be copied.  Previous information
 *      in the destination object which is not overwritten by
 *      copied data is neither deleted nor modified.  It is not a
 *      requirement in MAPI 1.0, however, that CopyTo semantics
 *      understood by the message store object or folder objects,
 *      and so this method always returns MAPI_E_NO_SUPPORT.
 *
 *  Arguments:
 *      pims            Pointer to the source object.
 *      ciidExclude     Count of the excluded interfaces in
 *                      rgiidExclude.
 *      rgiidExclude    Array of interface IDs specifying
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
 *      MAPI_E_NO_SUPPORT   This method is not supported by
 *                              this type of object.
 */
STDMETHODIMP IMS_CopyTo(PIMS pims, ULONG ciidExcl, LPCIID rgiidExcl,
    LPSPropTagArray ptagaExcl, ULONG ulUIParam, LPMAPIPROGRESS
    lpProgress, LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray *pprba)
{
    SCODE sc;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            CopyTo,
            (pims, 
            ciidExcl, 
            rgiidExcl, 
            ptagaExcl, 
            ulUIParam,  
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags, 
            pprba));

    sc = MAPI_E_NO_SUPPORT;

    DebugTraceSc(IMS_CopyTo, sc);
    return ResultFromScode(sc);
}

/*
 *  IMS_CopyProps
 *
 *  Purpose:
 *      Copies the specified properties of the current object to a destination
 *      object.
 *
 *  Arguments:
 *      pims            Pointer to the source object.
 *      ptagaIncl       Counted array of property tags of
 *                      properties that are to be copied to the
 *                      destination object.
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
 *      MAPI_E_NO_SUPPORT   This method is not supported by
 *                              this type of object.
 */
STDMETHODIMP IMS_CopyProps(PIMS pims,
    LPSPropTagArray ptagaIncl, ULONG ulUIParam, LPMAPIPROGRESS
    lpProgress, LPCIID piidDst, LPVOID lpDestObj, ULONG ulFlags,
    LPSPropProblemArray *pprba)
{
    SCODE sc;

    MS_ValidateParameters(
            pims, 
            IMAPIProp,
            CopyProps,
            (pims, 
            ptagaIncl, 
            ulUIParam,  
            lpProgress, 
            piidDst, 
            lpDestObj, 
            ulFlags, 
            pprba));

    sc = MAPI_E_NO_SUPPORT;

    DebugTraceSc(IMS_CopyProps, sc);
    return ResultFromScode(sc);
}

/*
 *  IMS_GetNamesFromIDs [also used by IFLD, IMSG, IATCH]
 *
 *  Purpose:
 *
 *  Arguments:
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *
 *  Errors:
 *      MAPI_E_NO_SUPPORT   This method is not yet supported in the sample ms.
 */
STDMETHODIMP IMS_GetNamesFromIDs(PIMS pobj, LPSPropTagArray * pptaga,
    LPGUID lpguid, ULONG ulFlags, ULONG * pcNames, LPMAPINAMEID ** pppNames)
{
    HRESULT hr = hrSuccess;
    LPMAPIPROP pmp = NULL;
    BOOL fReleasePMP = FALSE;

    /* Check input parameters. */

    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        || (    pobj->lpVtbl != (IMS_Vtbl *) &vtblIMS
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIFLD
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIMSG
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIATCH))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMAPIProp_GetNamesFromIDs(
                pobj, 
                pptaga, 
                lpguid, 
                ulFlags, 
                pcNames, 
                pppNames);
    #endif

    OBJ_EnterCriticalSection(pobj);

    switch(pobj->wType)
    {
        case OT_MSGSTORE:
        {
            PIMS pims = pobj->pims;
    
            hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps,
                &pims->lmr, pims->psup, FALSE, (LPMESSAGE *) &pmp);
            if (hr != hrSuccess)
                goto exit;
    
            fReleasePMP = TRUE;
            break;
        }
    
        case OT_FOLDER:
        {
            PIFLD pifld = (PIFLD) pobj;
    
            hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims, FALSE,
                (LPMESSAGE *) &pmp);
            if (hr != hrSuccess)
                goto exit;
    
            fReleasePMP = TRUE;
            break;
        }
    
        case OT_MESSAGE:
            pmp = (LPMAPIPROP) ((PIMSG) pobj)->lpmsg;
            break;
    
        case OT_ATTACH:
            pmp = (LPMAPIPROP) ((PIATCH) pobj)->lpattach;
            break;
    
        default:
            TrapSz1("Invalid Object Type %08lX found", pobj->wType);
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            break;
    }

    hr = pmp->lpVtbl->GetNamesFromIDs(pmp, pptaga, lpguid, ulFlags, pcNames,
        pppNames);

exit:
    if (fReleasePMP)
        UlRelease(pmp);

    OBJ_LeaveCriticalSection(pobj);

    DebugTraceResult(IMS_GetNamesFromIDs, hr);
    return hr;
}

/*
 *  IMS_GetIDsFromNames [also used by IFLD, IMSG, IATCH]
 *
 *  Purpose:
 *
 *  Arguments:
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 */
STDMETHODIMP IMS_GetIDsFromNames(PIMS pobj, ULONG cNames,
    LPMAPINAMEID * ppNames, ULONG ulFlags, LPSPropTagArray * pptaga)
{
    HRESULT hr = hrSuccess;
    LPMAPIPROP pmp = NULL;
    BOOL fSaveReleasePMP = FALSE;
    BOOL fModifyAccess;

    /* Check input parameters. */
    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        || (    pobj->lpVtbl != (IMS_Vtbl *) &vtblIMS
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIFLD
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIMSG
            &&  pobj->lpVtbl != (IMS_Vtbl *) &vtblIATCH))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMAPIProp_GetIDsFromNames(pobj, cNames, ppNames, ulFlags, pptaga);
    #endif

    OBJ_EnterCriticalSection(pobj);

    fModifyAccess = !!(ulFlags & MAPI_CREATE);

    // Check for correct access mode
    if (    fModifyAccess
        &&  !OBJ_TestFlag(pobj, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    switch(pobj->wType)
    {
        case OT_MSGSTORE:
        {
            PIMS pims = pobj->pims;
    
            hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps,
                &pims->lmr, pims->psup, fModifyAccess, (LPMESSAGE *) &pmp);
            if (hr != hrSuccess)
                goto exit;
    
            fSaveReleasePMP = TRUE;
            break;
        }
    
        case OT_FOLDER:
        {
            PIFLD pifld = (PIFLD) pobj;
    
            hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims,
                fModifyAccess, (LPMESSAGE *) &pmp);
            if (hr != hrSuccess)
                goto exit;
    
            fSaveReleasePMP = TRUE;
            break;
        }
    
        case OT_MESSAGE:
            pmp = (LPMAPIPROP) ((PIMSG) pobj)->lpmsg;
            break;
    
        case OT_ATTACH:
            pmp = (LPMAPIPROP) ((PIATCH) pobj)->lpattach;
            break;
    
        default:
            TrapSz1("Invalid Object Type %08lX found", pobj->wType);
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            break;
    }

    // CAN RETURN WARNINGS!!! Should still continue even when a warning
    // is returned.

    hr = pmp->lpVtbl->GetIDsFromNames(pmp, cNames, ppNames, ulFlags, pptaga);
    if (HR_FAILED(hr))
        goto exit;

    if (fSaveReleasePMP && fModifyAccess)
    {
        HRESULT hrT;

        hrT = pmp->lpVtbl->SaveChanges(pmp, 0);
        if (HR_FAILED(hrT))
        {
            LMFree(&pobj->lmr, *pptaga);
            *pptaga = NULL;
            hr = hrT;
        }
    }

exit:
    if (fSaveReleasePMP)
        UlRelease(pmp);

    OBJ_LeaveCriticalSection(pobj);

    #ifdef DEBUG
    if (GetScode(hr) != MAPI_W_ERRORS_RETURNED)
        DebugTraceResult(IMS_GetIDsFromNames, hr);
    #endif

    return hr;
}

/*
 *  IMS_Advise [Also used by IMSLogon]
 *
 *  Purpose:
 *      Register a client's interest in a set of events that could
 *      occur to an object in this store.  The client's particular
 *      interest is expressed in a ulEventMask, and he is told of
 *      changes through an Advise object which he gives us.
 *      The Sample Store uses the MAPI
 *      Notification Engine to handle notifications, so the
 *      Advise call is translated into a notification
 *      subscription with MAPI.  When events occur in the store
 *      which would cause interested clients to be notified, the
 *      store calls back to MAPI to request that the occurrence of
 *      an event be broadcast.
 *
 *  Arguments:
 *      pims                Pointer to the message store object.
 *      cbEntryID           Size of lpEntryID.
 *      lpEntryID           Pointer to the ID for the object for
 *                          which interest is being registered.
 *                          if NULL then registration is for all changes.
 *      ulEventMask         Indicates the events of interest and
 *                          how to see them.
 *      lpAdviseSink        Pointer to client's Advise Sink object.
 *      lpulConnection      Pointer to a variable in which the
 *                          client gets a cookie for cancelling
 *                          the notifications.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_INVALID_ENTRYID      The EntryID is not recognized
 *                                  as belonging to this store.
 *      MAPI_E_NO_SUPPORT       The implementation does not
 *                                  support notification on this
 *                                  object.
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for a
 *                                  needed buffer.
 */
STDMETHODIMP IMS_Advise(PIMS pobj, ULONG cbEntryID, LPENTRYID lpEntryID,
    ULONG ulEventMask, LPMAPIADVISESINK lpAdviseSink,
    ULONG *lpulConnection)
{
    HRESULT hr = hrSuccess;
    LPNOTIFKEY lpnotifkey = NULL;
    PIMS pims;
    PEID peid;

    /* Check input parameters. */

    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        || (    pobj->lpVtbl != (IMS_Vtbl *)&vtblIMS
            &&  pobj->lpVtbl != (IMS_Vtbl *)&vtblMSL))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMsgStore_Advise(
            pobj, 
            cbEntryID, 
            lpEntryID, 
            ulEventMask, 
            lpAdviseSink, 
            lpulConnection);
    #endif

    /* If this is an EntryID for which we support notifications, call the */
    /* MAPI registration function and return the notification object.     */

    OBJ_EnterCriticalSection(pobj);

    pims = pobj->pims;
    peid = (PEID) lpEntryID;
    *lpulConnection = 0;

    if (cbEntryID && FIsInvalidEID(cbEntryID, peid, pims))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    if (cbEntryID && !FIsFolder(peid) && !FIsMessage(peid))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    if (cbEntryID == 0)
        peid = NULL;

    hr = HrGetSMSStandardNotifKey(pims, peid, &lpnotifkey);
    if (hr != hrSuccess)
        goto exit;

    if (pims->psup)
    {
        hr = pims->psup->lpVtbl->Subscribe(pims->psup,
            lpnotifkey, ulEventMask, 0L, lpAdviseSink, lpulConnection);
        if (hr != hrSuccess)
            goto exit;
    }
    else
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        /* fall through to exit */
    }

exit:
    OBJ_LeaveCriticalSection(pobj);

    FreeNull(lpnotifkey);

    DebugTraceResult(IMS_Advise, hr);
    return HrCheckHr(hr, IMsgStore_Advise);
}

/*
 *  IMS_Unadvise [Also used by IMSLogon]
 *
 *  Purpose:
 *      Deregister a previous notification.
 *
 *  Arguments:
 *      pims                Pointer to the message store object.
 *      ulConnection        Cookie given out at Advise time.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 */
STDMETHODIMP IMS_Unadvise(PIMS pobj, ULONG ulConnection)
{
    HRESULT hr = hrSuccess;
    LPMAPISUP psup;

    /* Check input parameters. */

    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        ||  (   pobj->lpVtbl != (IMS_Vtbl *)&vtblIMS
            &&  pobj->lpVtbl != (IMS_Vtbl *)&vtblMSL))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMsgStore_Unadvise(pobj, ulConnection);
    #endif

    OBJ_EnterCriticalSection(pobj);

    psup = pobj->pims->psup;

    if (psup)
        hr = psup->lpVtbl->Unsubscribe(psup, ulConnection);
    else
        hr = ResultFromScode(MAPI_E_CALL_FAILED);

    OBJ_LeaveCriticalSection(pobj);

    DebugTraceResult(IMS_Unadvise, hr);
    return HrCheckHr(hr, IMsgStore_Unadvise);
}

/*
 *  IMS_CompareEntryIDs
 *
 *  Purpose:
 *      Compares two EntryIDs to determine if they refer to the
 *      same object.  This is useful because, in general, an object
 *      may have more than one valid EntryID.  For the Sample
 *      Store, however, an object only has one valid EntryID at any
 *      time and so this function reduces to a check for binary
 *      equality of the EntryIDs.
 *
 *  Arguments:
 *      pims        Pointer to the Message Store Object.
 *      cbEntryID1  Size of first EntryID.
 *      lpEntryID1  Pointer to the first EntryID.
 *      cbEntryID2  Size of second EntryID.
 *      lpEntryID2  Pointer to the second EntryID.
 *      ulFlags     Flags.  Reserved.  Must be zero.
 *      lpulResult  Pointer to a variable in which the result of
 *                  the comparison (TRUE or FALSE) is placed.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_INVALID_ENTRYID  An EntryID is not recognized as
 *                              belonging to this store.
 */
STDMETHODIMP IMS_CompareEntryIDs(PIMS pobj, ULONG cbEntryID1,
    LPENTRYID lpEntryID1, ULONG cbEntryID2, LPENTRYID lpEntryID2, ULONG ulFlags,
    ULONG *lpulResult)
{
    HRESULT hr = hrSuccess;
    PEID peid1;
    PEID peid2;
    PIMS pims;
    BOOL fEID1IsRoot = FALSE;
    BOOL fEID2IsRoot = FALSE;

    /* Check input parameters. */

    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        || (    pobj->lpVtbl != (IMS_Vtbl *)&vtblIMS
            &&  pobj->lpVtbl != (IMS_Vtbl *)&vtblMSL))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMsgStore_CompareEntryIDs(
                pobj, 
                cbEntryID1, 
                lpEntryID1, 
                cbEntryID2, 
                lpEntryID2, 
                ulFlags, 
                lpulResult);
    #endif

    OBJ_EnterCriticalSection(pobj);

    /* Do a binary comparison of the EIDs, if they're the same size AND */
    /* if we recognize one of them as belonging to this store.          */

    peid1 = (PEID) lpEntryID1;
    peid2 = (PEID) lpEntryID2;
    pims = pobj->pims;

    if ((cbEntryID1 && FIsInvalidEID(cbEntryID1, peid1, pims))
        || (cbEntryID2 && FIsInvalidEID(cbEntryID2, peid2, pims)))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    if (cbEntryID1 == 0 || FIsRoot(peid1))
        fEID1IsRoot = TRUE;

    if (cbEntryID2 == 0 || FIsRoot(peid2))
        fEID2IsRoot = TRUE;

    *lpulResult = FALSE;

    if (fEID1IsRoot == fEID2IsRoot && fEID1IsRoot == TRUE)
        *lpulResult = TRUE;
    else if (cbEntryID1 == cbEntryID2
            && memcmp(peid1, peid2, offsetof(EID, szPath)) == 0
            && peid1->bVersion == SMPMS_VERSION
        && lstrcmpi(peid1->szPath, peid2->szPath) == 0)
        *lpulResult = TRUE;

exit:
    OBJ_LeaveCriticalSection(pobj);

    DebugTraceResult(IMS_CompareEntryIDs, hr);
    return hr;
}

/*
 *  IMS_OpenEntry [Also used by IMSLogon and IMAPIFolder]
 *
 *  Purpose:
 *      Opens an object in this message store.
 *
 *  Arguments:
 *      pobj            Message store on which this function was
 *                      called.
 *      cbEntryID       Size of lpEntryID.
 *      lpEntryID       EntryID of object to open.
 *      piid            IID of interface requested for the
 *                      newly-opened object.  NULL or IID_IMAPIProp
 *                      means to open the object using the standard
 *                      MAPI 1.0 interface for the object.
 *                      IID_IUnknown means to open it using
 *                      the easiest interface you can open.
 *      ulFlags         Flags.  The following are defined:
 *                      MAPI_MODIFY             Write access desired.
 *                      MAPI_DEFERRED_ERRORS    Delayed "open" errors OKAY.
 *                      MAPI_BEST_ACCESS        Open for writing if possible,
 *                                              otherwise, open for reading.
 *      lpulObjType     Address in which to place the type of the
 *                      opened object.
 *      lppUnk          Address in which to place a pointer to the
 *                      opened object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate memory for
 *                                  the to-be-opened object.
 *      MAPI_E_INVALID_ENTRYID      This message store does not
 *                                  recognize this EntryID.
 *      MAPI_E_UNKNOWN_FLAGS
 *      MAPI_E_INVALID_PARAMETER
 */
STDMETHODIMP IMS_OpenEntry(PIMS pobj, ULONG cbEntryID, LPENTRYID lpEntryID,
    LPCIID piid, ULONG ulFlags, ULONG *lpulObjType, LPUNKNOWN *lppUnk)
{
    HRESULT hr = hrSuccess;
    PIMSG pimsg = NULL;
    PIFLD pifld = NULL;
    PEID peidParent = NULL;
    BOOL fEIDIsRoot = FALSE;
    BOOL fModify;
    BOOL fBestAcc;
    PIMS pims;
    PEID peid;

    /* Check input parameters. */

    #ifdef VALIDATE
    if (    IsBadWritePtr(pobj, sizeof(OBJ))
        ||  (   pobj->lpVtbl != (IMS_Vtbl *)&vtblIFLD
             && pobj->lpVtbl != (IMS_Vtbl *)&vtblIMS
             && pobj->lpVtbl != (IMS_Vtbl *)&vtblMSL))
        return ResultFromScode(MAPI_E_INVALID_PARAMETER);

    Validate_IMAPIContainer_OpenEntry(
                pobj, 
                cbEntryID, 
                lpEntryID, 
                piid, 
                ulFlags, 
                lpulObjType, 
                lppUnk);
    #endif

    OBJ_EnterCriticalSection(pobj);

    /* Get the real pims object in case pobj is a PIFLD or PMSL */
    pims = pobj->pims;

    peid = (PEID) lpEntryID;

    /* If parameters are okay, see if this is an EntryID we understand. */

    if (cbEntryID && FIsInvalidEID(cbEntryID, peid, pims))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    if (cbEntryID == 0 || FIsRoot(peid))
        fEIDIsRoot = TRUE;

    /* determine if the caller wants modification access */
    fModify = (ulFlags & (MAPI_MODIFY | MAPI_BEST_ACCESS)) != 0;
    fBestAcc = (ulFlags & MAPI_BEST_ACCESS) != 0;

    /* Fail if attempting to open an object for */
    /* modification in a read-only store.       */

    if (fModify
        && !OBJ_TestFlag(pims, OBJF_MODIFY))
    {
        if (fBestAcc)
            fModify = FALSE;
        else
        {
            hr = ResultFromScode(MAPI_E_NO_ACCESS);
            goto exit;
        }
    }

    /* Open the object */

    if (fEIDIsRoot)
    {
        PEID peidRoot = NULL;
        CHAR ch = '\0';
        MAPIUID uid;

        if (piid && !FQueryInterface(OT_FOLDER, piid))
        {
            hr = ResultFromScode(E_NOINTERFACE);
            goto exit;
        }

        GetResourceUID(pims, &uid);

        hr = HrConstructEID(&uid, &pims->lmr, (LPSTR) &ch, &peidRoot);
        if (hr != hrSuccess)
            goto exit;

        hr = HrNewIFLD(peidRoot, pims, fModify, &pifld);

        if (hr == hrSuccess)
            hr = HrSetInternalProps(&pims->lmr, cpropIFLDInternal,
                &(pifld->pval), &(pifld->cval), peidRoot, peidRoot, 0);

        LMFree(&pims->lmr, peidRoot);

        if (hr != hrSuccess)
            goto exit;

        *lppUnk = (LPUNKNOWN) pifld;
        *lpulObjType = MAPI_FOLDER;
    }
    else
    {
        hr = HrGetParentEID(&pims->lmr, peid, &peidParent);
        if (hr != hrSuccess)
            goto exit;

        if (FIsMessage(peid))
        {
            ULONG ulSeqNum;

            if (piid && !FQueryInterface(OT_MESSAGE, piid))
            {
                hr = ResultFromScode(E_NOINTERFACE);
                goto exit;
            }

            hr = HrGetSequenceNum(peid, &ulSeqNum);

            hr = HrNewIMSG(peid, pims, FALSE, fModify, ulSeqNum, NULL, &pimsg);

            if (GetScode(hr) == MAPI_E_SUBMITTED && fBestAcc && fModify)
            {
                fModify = FALSE;
                hr = HrNewIMSG(peid, pims, FALSE, fModify, ulSeqNum, NULL, &pimsg);
            }

            if (hr != hrSuccess)
                goto exit;

            *lppUnk = (LPUNKNOWN) pimsg;
            *lpulObjType = MAPI_MESSAGE;
        }
        else /* a folder */
        {
            if (!FIsFolder(peid))
            {
                TrapSz("Logic error");
                hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
                goto exit;
            }

            if (piid && !FQueryInterface(OT_FOLDER, piid))
            {
                hr = ResultFromScode(E_NOINTERFACE);
                goto exit;
            }

            hr = HrNewIFLD(peid, pims, fModify, &pifld);
            if (hr != hrSuccess)
                goto exit;

            hr = HrSetInternalProps(&pims->lmr, cpropIFLDInternal,
                &(pifld->pval), &(pifld->cval), peid, peidParent, 0);
            if (hr != hrSuccess)
                goto exit;

            *lppUnk = (LPUNKNOWN) pifld;
            *lpulObjType = MAPI_FOLDER;
        }
    }

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No Warnings expected");

    LMFree(&pims->lmr, peidParent);

    if (hr != hrSuccess)
    {
        UlRelease(pimsg);
        UlRelease(pifld);
    }

    OBJ_LeaveCriticalSection(pobj);

    DebugTraceResult(IMS_OpenEntry, hr);
    return HrCheckHr(hr, IMsgStore_OpenEntry);
}

/*
 *  IMS_SetReceiveFolder
 *
 *  Purpose:
 *      Sets the receive folder for a particular message class.  A
 *      message class is a string with "." delimiters, e.g
 *      "IPM.Note".  This method also removes a setting if the
 *      EntryID parameter (see below) is NULL.  Because there must
 *      be only one set of receive folder settings per store (NOT
 *      per logon), the settings are stored on disk in an OLE2
 *      docfile, and all access to them is done on disk, not in
 *      memory (see recfldr.c, recfldr.h for details).
 *
 *  Arguments:
 *      pims                Pointer to the object.
 *      szMessageClass  String identifying a message class.  If
 *                          NULL, then the default receive folder
 *                          is set.
 *      ulFlags             Flags.
 *      cbEntryID           Size of lpEntryID.
 *      lpEntryID           Pointer to the identifier of a
 *                          particular folder in the store.  If
 *                          this pointer is NULL, the receive
 *                          folder setting is removed.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      IMS_SetReceiveFolder will not actually check to see if the
 *      EntryID it is given exists in the store at this time, so
 *      will go ahead and create an invalid receive folder setting
 *      for that particular message class.
 *
 *  Errors:
 *      MAPI_E_INVALID_ENTRYID  The store doesn't recognize this
 *                              EntryID as belonging to it.
 */
STDMETHODIMP IMS_SetReceiveFolder(PIMS pims, LPTSTR szMessageClass,
    ULONG ulFlags, ULONG cbEntryID, LPENTRYID lpEntryID)
{
    SCODE sc;
    HRESULT hr = hrSuccess;
    TCHAR rgchDefMsgClass[] = TEXT("");
    LPTSTR szNormalizedClass = NULL;
    RFN rfn;
    PEID peid;

    /* Check input parameters. */

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            SetReceiveFolder,
            (pims, 
            szMessageClass, 
            ulFlags, 
            cbEntryID, 
            lpEntryID));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, OBJF_MODIFY))
    {
        hr = ResultFromScode(MAPI_E_NO_ACCESS);
        goto exit;
    }

    peid = (PEID) lpEntryID;

    /* don't allow removal of the default settings */
    if (peid == NULL &&
        (szMessageClass == NULL || *szMessageClass == '\0'))
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    /* If parameters are okay, see if this is an EntryID we understand. */

    if (cbEntryID && FIsInvalidEID(cbEntryID, peid, pims))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    /* The RFS module always expects a valid string */
    if (!szMessageClass)
        szMessageClass = rgchDefMsgClass;

    /* Make a copy of the szMessageClass that is normalized */

    sc = LMAlloc(&pims->lmr, Cbtszsize(szMessageClass), &szNormalizedClass);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }
    lstrcpy (szNormalizedClass, szMessageClass);
    CharUpper (szNormalizedClass);
        
    if (cbEntryID)
    {
        PRFN prfnExisting = NULL;

        rfn.szClass = szNormalizedClass;
        rfn.szName = peid->szPath;

        hr = GetRFN(pims->prfs, szNormalizedClass, &prfnExisting);
        if (hr != hrSuccess)
        {
            if (GetScode(hr) == MAPI_E_NOT_FOUND)
                hr = hrSuccess;
            else
                goto exit;
        }
        else
        {
            /* Remove the existing receive folder setting, but only if it */
            /* _exactly_ matches the one that we're adding.               */
            /*  //$ Are message classes case-sensitive? */

            if (!lstrcmp(szMessageClass, prfnExisting->szClass))
                hr = DeleteRFN(pims->prfs, szNormalizedClass);

            FreeRFN(prfnExisting);

            if (hr != hrSuccess)
                goto exit;
        }

        /* WARNING:  If the addition fails, we can't easily  */
        /* revert to a previous version of the RFS settings. */

        hr = AddRFN(pims->prfs, &rfn);
        /* if ( hr ), fall through to exit */
    }
    else
    {
        hr = DeleteRFN(pims->prfs, szNormalizedClass);
        /* if ( hr ), fall through to exit */
    }

exit:
    LMFree(&pims->lmr, szNormalizedClass);
    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_SetReceiveFolder, hr);
    return HrCheckHr(hr, IMsgStore_SetReceiveFolder);
}

/*
 *  IMS_GetReceiveFolder
 *
 *  Purpose:
 *      Obtains the receive folder setting for a particular message
 *      class and other information about the receive behavior of
 *      that message class.  This function obtains the EntryID of
 *      the folder where messages of a specific class are placed.
 *      If szMessageClass does not explicitly set a receive
 *      folder, then the receive folder of the first superclass of
 *      szMessageClass which does explicitly set a receive folder
 *      is returned.  Whichever message class that explicitly sets
 *      the receive folder is returned in pszExplicitClass.  For
 *      example, if the receive folder of the message class
 *      "IPM.Note" has been set to the EntryID of the Inbox and an
 *      application calls GetReceiveFolder() on the message class
 *      "IPM.Note.Phone," the EntryID of the Inbox is returned as
 *      the lppEntryID, and "IPM.Note" is retuned in
 *      pszExplicitClass.  The converse is not true:  if the
 *      receive folder setting of "IPM.Note.Phone" is the Inbox and
 *      the client asks for the setting of "IPM.Note", NULL is
 *      returned.
 *
 *  Arguments:
 *      pims                Pointer to the object.
 *      szMessageClass  Identifies the particular message
 *                          class.  If this pointer is NULL, then
 *                          the default is returned.
 *      ulFlags             Flags.
 *      lpcbEntryID         Address of the location in which to
 *                          return the size of the EntryID in
 *                          *lppEntryID.
 *      lppEntryID          Address of the location in which to
 *                          return a pointer to an EntryID which is
 *                          the identifier of the receive folder.
 *      pszExplicitClass    Address of the location in which to
 *                          return a pointer a buffer containing
 *                          the message class that explicitly sets
 *                          its receive folder to *lppEntryID.  If
 *                          NULL indicates that no class name
 *                          should be returned.  If it is exactly
 *                          equal to szMessageClass, nothing is
 *                          returned (*pszExplicitClass == NULL).
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_GetReceiveFolder(PIMS pims, LPTSTR szMessageClass,
    ULONG ulFlags, ULONG *lpcbEntryID, LPENTRYID *lppEntryID,
    LPTSTR *pszExplicitClass)
{
    HRESULT hr = hrSuccess;
    ULONG cbeid = 0L;
    PEID peid = NULL;
    LPTSTR szExCls = NULL;
    PRFN prfn = NULL;
    TCHAR rgchDefMsgClass[] = TEXT("");
    LPTSTR szNormalizedClass = NULL;
    MAPIUID uid;
    SCODE sc = S_OK;

    /* Check input parameters. */

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            GetReceiveFolder,
            (pims, 
            szMessageClass, 
            ulFlags, 
            lpcbEntryID, 
            lppEntryID, 
            pszExplicitClass));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    IMS_EnterCriticalSection(pims);

    *lpcbEntryID = 0L;
    *lppEntryID = NULL;

    if (pszExplicitClass)
        *pszExplicitClass = NULL;

    /* The RFS module always expects a valid string */

    if (!szMessageClass)
        szMessageClass = rgchDefMsgClass;

    /* Make a copy of the szMessageClass that is normalized */

    sc = LMAlloc(&pims->lmr, Cbtszsize(szMessageClass), &szNormalizedClass);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }
    lstrcpy (szNormalizedClass, szMessageClass);
    CharUpper (szNormalizedClass);

    hr = GetRFN(pims->prfs, szNormalizedClass, &prfn);
    if (hr != hrSuccess)
        goto exit;

    /* Allocate and set return variables. */

    GetResourceUID(pims, &uid);

    hr = HrConstructEID(&uid, &pims->lmr, prfn->szName, &peid);
    if (hr != hrSuccess)
        goto exit;

    cbeid = CbEID(peid);

    if (pszExplicitClass)
    {
        sc = LMAlloc(&pims->lmr, Cbtszsize(prfn->szClass), &szExCls);
        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        lstrcpy(szExCls, prfn->szClass);
        *pszExplicitClass = szExCls;
    }

    *lpcbEntryID = cbeid;
    *lppEntryID = (LPENTRYID) peid;

exit:
    FreeRFN(prfn);
    LMFree(&pims->lmr, szNormalizedClass);
    if (hr != hrSuccess)
    {
        LMFree(&pims->lmr, peid);
        LMFree(&pims->lmr, szExCls);
    }

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_GetReceiveFolder, hr);
    return HrCheckHr(hr, IMsgStore_GetReceiveFolder);
}

STDMETHODIMP IMS_GetReceiveFolderTable(PIMS pims, ULONG ulFlags,
    LPMAPITABLE *lppTable)
{
    MS_ValidateParameters(
            pims, 
            IMsgStore,
            GetReceiveFolderTable,
            (pims, 
            ulFlags, 
            lppTable));

    #ifdef VALIDATE
    if (ulFlags & MAPI_UNICODE)
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    #endif

    DebugTraceSc(IMS_GetReceiveFolderTable, MAPI_E_NO_SUPPORT);
    return ResultFromScode(MAPI_E_NO_SUPPORT);
}

/*
 *  IMS_StoreLogoff
 *
 *  Purpose:
 *      Allows the orderly release of a store under client control.
 *      Use of this function to release a store allows some client
 *      control over what MAPI will do about transport activity.
 *      The client can either put itself in the loop by setting the
 *      appropriate flags, or it can allow MAPI to either abort the
 *      sending of mail or to complete it prior to invalidating the
 *      object.  This behavior will only occur when the client is
 *      the only application which is using the message store, and 
 *      will happen during release of the store object.  If
 *      another client is still using the store, the store object
 *      will remember the flags and will issue the call during the 
 *      final release.
 *
 *  Arguments:
 *      pims        Pointer to the object.
 *      pulFlags    Flags.  The following are defined as input:
 *                  LOGOFF_NO_WAIT  Don't wait for the transports.
 *                                  All outboutnd mail that is
 *                                  ready to be sent will be sent.
 *                                  Control is returned to the
 *                                  client immediately.
 *                  LOGOFF_ORDERLY  Don't wait for the transports.
 *                                  Any currently in-process
 *                                  message on the store is
 *                                  completed; no new ones are
 *                                  started.  Control is returned
 *                                  to the client immediately.
 *                  LOGOFF_PURGE    Same as LOGOFF_NO_WAIT but
 *                                  PurgeQueues() called for
 *                                  appropriate transports and
 *                                  client waits for completion.
 *                  LOGOFF_ABORT    Any transport activity on this
 *                                  store should be aborted.
 *                                  Control is returned to the
 *                                  client when abort completes.
 *                  LOGOFF_QUIET    If any transport activity is
 *                                  taking place, the logoff will
 *                                  not occur.
 *                  The following are defined as output flags:
 *                  LOGOFF_COMPLETE         All resources
 *                                          associated with the
 *                                          store have been
 *                                          released and the object
 *                                          invalidated.
 *                  LOGOFF_INBOUND          A message is currently
 *                                          coming into the store
 *                                          from one or more
 *                                          transports.
 *                  LOGOFF_OUTBOUND         A message is currently
 *                                          being sent from the
 *                                          store by one or more
 *                                          transports.
 *                  LOGOFF_OUTBOUND_QUEUE   Messages are currently
 *                                          in the outbound queue
 *                                          for the store.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      See flag description for possible side effects.
 *
 *  Errors:
 *      Various.
 */

STDMETHODIMP IMS_StoreLogoff(PIMS pims, ULONG * pulFlags)
{
    HRESULT hr = 0;
    LPMAPISUP psup = NULL;

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            StoreLogoff,
            (pims,
            pulFlags));

    IMS_EnterCriticalSection(pims);

    pims->ulFlagsSLT = *pulFlags;
    *pulFlags = LOGOFF_COMPLETE;

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_StoreLogoff, hr);
    return HrCheckHr(hr, IMsgStore_StoreLogoff);
}

/*
 *  IMS_AbortSubmit
 *
 *  Purpose:
 *      Removes the current message from the submission queue.
 *      Since this is not implemented in IMessage on IStorage, we
 *      must do it ourselves.
 *
 *  Arguments:
 *      lpMS        Pointer to the message store.
 *      cbEntryID   the size of the entry ID
 *      lpEntryID   the entry ID of the message to abort
 *      ulFlags     Flags.  Reserved for future use.  Must be zero.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_IN_QUEUE     The message was never successfully
 *                              submitted (and is thus not in the
 *                              outgoing queue).
 *      MAPI_E_UNABLE_TO_ABORT  The underlying messaging system no
 *                              longer allows the submission to be
 *                              cancelled.
 */
STDMETHODIMP IMS_AbortSubmit(PIMS pims, ULONG cbEntryID, LPENTRYID lpEntryID,
    ULONG ulFlags)
{
    HRESULT hr = hrSuccess;
    PIMSG pimsg = NULL;
    ULONG ulObjType;
    BOOL fClearSpooler = FALSE;
    ULONG ulSF;
    PEID peid;

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            AbortSubmit,
            (pims, 
            cbEntryID, 
            lpEntryID, 
            ulFlags));

    IMS_EnterCriticalSection(pims);

    peid = (PEID) lpEntryID;

    /* Note that we don't allow a NULL entryid here, because the root */
    /* folder is not a valid input to AbortSubmit. */

    if (FIsInvalidEID(cbEntryID, peid, pims)
        && !FIsMessage(peid))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    /* unlock the message */
    /* make this store look like the spooler so we can open it if locked */

    if (!OBJ_TestFlag(pims, MSF_SPOOLER))
    {
        OBJ_SetFlag(pims, MSF_SPOOLER);
        fClearSpooler = TRUE;
    }

    hr = pims->lpVtbl->OpenEntry(pims, cbEntryID, lpEntryID,
        NULL, MAPI_MODIFY, &ulObjType, (LPUNKNOWN *) &pimsg);
    if (hr != hrSuccess)
        goto exit;

    /* If we can't get PR_SUBMIT_FLAGS from the message, then either */
    /* the message hasn't been submitted, or something else is broken. */
    /* In any case, we can't abort the submit. */
    /* If the message is locked already by the spooler, then we also */
    /* can't abort the submit. */

    hr = HrGetSingleProp((LPMAPIPROP) pimsg, &pims->lmr, PR_SUBMIT_FLAGS, &ulSF);
    if ((hr != hrSuccess) || (ulSF & SUBMITFLAG_LOCKED))
    {
        hr = ResultFromScode(MAPI_E_UNABLE_TO_ABORT);
        goto exit;
    }

    hr = HrSetFlags(pimsg, UNSET, PR_MESSAGE_FLAGS, MSGFLAG_SUBMIT);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetFlags(pimsg, UNSET, PR_SUBMIT_FLAGS, SUBMITFLAG_LOCKED);
    if (hr != hrSuccess)
        goto exit;

    hr = pimsg->lpVtbl->SaveChanges(pimsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    hr = HrUpdateOutgoingQueue(pims, NULL, (PEID) lpEntryID,
        TABLE_ROW_DELETED);

exit:
    UlRelease(pimsg);

    if (fClearSpooler)
        OBJ_ClearFlag(pims, MSF_SPOOLER);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_AbortSubmit, hr);
    return HrCheckHr(hr, IMsgStore_AbortSubmit);
}

/*
 *  IMS_GetOutgoingQueue
 *
 *  Purpose:
 *      Returns a MAPI Table Object of the queue of messages
 *      waiting to be sent.
 *
 *  Arguments:
 *      pims        Pointer to a Spooler Message Store Object.
 *      ulFlags     Reserved for future use.  Must be zero.
 *      lppTable    Location to return the new table object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_GetOutgoingQueue(PIMS pims, ULONG ulFlags,
    LPMAPITABLE *lppTable)
{
    SCODE sc = S_OK;
    HRESULT hr = hrSuccess;
    LPMAPITABLE ptbl = NULL;
    BOOL fInMutex = FALSE;

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            GetOutgoingQueue,
            (pims, 
            ulFlags, 
            lppTable));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, MSF_SPOOLER))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    /* If the file mutex doesn't yet exist on this process, create it. */

    if (pims->hOGQueueMutex == NULL)
    {
        hr = HrCreateOGQueueMutex(&pims->hOGQueueMutex);
        if (hr != hrSuccess)
            goto exit;
    }

    /* Get the file mutex so that we can use the file (and change it) */
    /* without crossing paths with another process. */

    WaitForSingleObject(pims->hOGQueueMutex, INFINITE);
    fInMutex = TRUE;

    /* Create a new table if there currently is none */
    if (pims->lptblOutgoing == NULL)
    {
        hr = HrNewOutgoingTableData(pims);
        if (hr != hrSuccess)
            goto exit;
    }

    /* open a view on the table */
    hr = pims->lptblOutgoing->lpVtbl->HrGetView(pims->lptblOutgoing,
        NULL, OutgoingViewRelease, (ULONG) pims, &ptbl);
    if (hr != hrSuccess)
        goto exit;

    pims->cOutgoingViews++;

    *lppTable = ptbl;

    Assert(hrSuccess == hr);

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr),
        "Unexpected warning return");

    if (fInMutex)
        ReleaseMutex(pims->hOGQueueMutex);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_GetOutgoingQueue, hr);
    return HrCheckHr(hr, IMsgStore_GetOutgoingQueue);
}

/*
 *  IMS_SetLockState
 *
 *  Purpose:
 *      Allows the spooler to lock a message so that no one else
 *      can modify it while the spooler processes it.
 *
 *  Arguments:
 *      pims        Pointer to the Message Store Object.
 *      lpMessage   The message object to be locked
 *      ulFlags     control flags
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_SetLockState(PIMS pims, LPMESSAGE lpMessage, ULONG ulFlags)
{
    SCODE sc = S_OK;
    HRESULT hr = hrSuccess;
    PIMSG pimsg = (PIMSG) lpMessage;
    ULONG ulSF;
    LPSPropValue pval = NULL;

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            SetLockState,
            (pims, 
            lpMessage, 
            ulFlags));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, MSF_SPOOLER))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    hr = HrGetSingleProp((LPMAPIPROP) pimsg, &pims->lmr, PR_SUBMIT_FLAGS, &ulSF);
    if (hr != hrSuccess)
    {
        if (GetScode(hr) == MAPI_E_NOT_FOUND)
        {
            ULONG ulMF;

            hr = HrGetSingleProp((LPMAPIPROP) pimsg, &pims->lmr, PR_MESSAGE_FLAGS, &ulMF);
            if (hr != hrSuccess)
            {
                if (GetScode(hr) == MAPI_E_NOT_FOUND)
                    hr = ResultFromScode(MAPI_E_CORRUPT_STORE);

                goto exit;
            }

            if (ulMF & MSGFLAG_SUBMIT)
                hr = ResultFromScode(MAPI_E_CORRUPT_STORE);
            else
                hr = ResultFromScode(MAPI_E_NOT_IN_QUEUE);
        }
        goto exit;
    }

    /* set the lock state, if the message is already in the correct state */
    /* just get outta here */

    if (ulFlags & MSG_LOCKED)
    {
        if (!(ulSF & SUBMITFLAG_LOCKED))
            ulSF |= SUBMITFLAG_LOCKED;
        else
            goto exit;
    }
    else
        /* unlock */
    {
        if (ulSF & SUBMITFLAG_LOCKED)
            ulSF &= ~SUBMITFLAG_LOCKED;
        else
            goto exit;
    }

    hr = HrSetSingleProp((LPMAPIPROP) pimsg, &pims->lmr, PR_SUBMIT_FLAGS, &ulSF);
    if (hr != hrSuccess)
        goto exit;

    hr = pimsg->lpVtbl->SaveChanges(pimsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    /* No need to call ChangeTable to update tables because the SaveChanges
     * call above just did that.
     */

exit:
    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_SetLockState, hr);
    return HrCheckHr(hr, IMsgStore_SetLockState);
}

/*
 *  IMS_FinishedMsg
 *
 *  Purpose:
 *      Allows the Spooler to inform the message store that it has
 *      finished processing a message (cancels a previous
 *      MDBLockMsg).
 *
 *  Arguments:
 *      pims        Pointer to a Message Store Object.
 *      ulFlags     Reserved for future use.  Ignored.
 *      lpEntryID   EntryID of message that was locked.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_FinishedMsg(PIMS pims, ULONG ulFlags, ULONG cbEntryID,
    LPENTRYID lpEntryID)
{
    PIMSG pimsg = NULL;         /* opened message */
    PIFLD pifldParent = NULL;   /* parent folder of this message */
    ULONG ulObjectType;
    HRESULT hr = hrSuccess;
    SCODE sc = S_OK;
    PEID peid = (PEID) lpEntryID;


    MS_ValidateParameters(
            pims, 
            IMsgStore,
            FinishedMsg,
            (pims, 
            ulFlags, 
            cbEntryID, 
            lpEntryID));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, MSF_SPOOLER))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    if (FIsInvalidEID(cbEntryID, peid, pims))
    {
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    hr = pims->lpVtbl->OpenEntry(pims, cbEntryID, lpEntryID,
        NULL, MAPI_MODIFY, &ulObjectType, (LPUNKNOWN *) &pimsg);
    if (hr != hrSuccess)
        goto exit;

    Assert(ulObjectType == MAPI_MESSAGE);

    /* update the parent folder */
    hr = HrOpenParent(pims, peid, MAPI_MODIFY, &pifldParent);
    if (hr != hrSuccess)
        goto exit;

    /* unlock the message */
    hr = HrSetFlags(pimsg, UNSET, PR_MESSAGE_FLAGS,
        MSGFLAG_UNSENT | MSGFLAG_SUBMIT);
    if (hr != hrSuccess)
        goto exit;

    /* Mark the message read */
    hr = HrSetFlags(pimsg, SET, PR_MESSAGE_FLAGS, MSGFLAG_READ);
    if (hr != hrSuccess)
        goto exit;

    /* Clear submitflag_locked and save the message */
    hr = HrSetFlags(pimsg, UNSET, PR_SUBMIT_FLAGS, SUBMITFLAG_LOCKED);
    if (hr != hrSuccess)
        goto exit;

    hr = pimsg->lpVtbl->SaveChanges(pimsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->psup->lpVtbl->DoSentMail(pims->psup, 0L, (LPMESSAGE) pimsg);
    if (hr != hrSuccess)
        goto exit;
    pimsg = NULL;

    Assert(pims->lptblOutgoing);

    hr = HrUpdateOutgoingQueue(pims, NULL, (PEID) lpEntryID,
        TABLE_ROW_DELETED);

exit:
    UlRelease(pifldParent);
    UlRelease(pimsg);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_FinishedMsg, hr);
    return HrCheckHr(hr, IMsgStore_FinishedMsg);
}

/*
 *  IMS_NotifyNewMail
 *
 *  Purpose:
 *      Spooler tells us when to tell clients about a new message.
 *      Passed in on the call is the exact notification structure
 *      we need to give the client.
 *
 *      Stubbed for now.
 *
 *  Arguments:
 *      pims        Pointer to the object.
 *      pntf        Pointer to the newmail notification structure.
 *                                      read/write.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP IMS_NotifyNewMail(PIMS pims, LPNOTIFICATION pntf)
{
    HRESULT hr = hrSuccess;
    LPNOTIFKEY lpKey = NULL;
    ULONG ulFlags = 0;
    PEID peidMsg;
    PEID peidFld;
    ULONG cbEIDMsg;
    ULONG cbEIDFld;

    MS_ValidateParameters(
            pims, 
            IMsgStore,
            NotifyNewMail,
            (pims, 
            pntf));

    IMS_EnterCriticalSection(pims);

    if (!OBJ_TestFlag(pims, MSF_SPOOLER))
    {
        hr = ResultFromScode(MAPI_E_NO_SUPPORT);
        goto exit;
    }

    if (!pims->psup)
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    cbEIDMsg = pntf->info.newmail.cbEntryID;
    peidMsg = (PEID) pntf->info.newmail.lpEntryID;

    cbEIDFld = pntf->info.newmail.cbParentID;
    peidFld = (PEID) pntf->info.newmail.lpParentID;

    if (    cbEIDMsg == 0
        ||  FIsInvalidEID(cbEIDMsg, peidMsg, pims)
        ||  !FIsMessage(peidMsg)
        ||  cbEIDFld == 0
        ||  FIsInvalidEID(cbEIDFld, peidFld, pims)
        ||  !FIsFolder(peidFld))
    {
        TraceSz("SMS: Bad entryid given to NotifyNewMail");
        hr = ResultFromScode(MAPI_E_INVALID_ENTRYID);
        goto exit;
    }

    /* Generate the key we use for notifications. First, get the key */
    /* for the folder that the message arrived into. */

    hr = HrGetSMSStandardNotifKey(pims, peidFld, &lpKey);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->psup->lpVtbl->Notify(pims->psup, lpKey, 1, pntf, &ulFlags);
    if (hr != hrSuccess)
        goto exit;
    
    FreeNull(lpKey);
    lpKey = NULL;
    ulFlags = 0;

    /* Now, get the key for the entire store, and send to that key also. */

    hr = HrGetSMSStandardNotifKey(pims, NULL, &lpKey);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->psup->lpVtbl->Notify(pims->psup, lpKey, 1, pntf, &ulFlags);
    if (hr != hrSuccess)
        goto exit;

exit:
    FreeNull(lpKey);

    IMS_LeaveCriticalSection(pims);

    DebugTraceResult(IMS_NotifyNewMail, hr);
    return HrCheckHr(hr, IMsgStore_NotifyNewMail);
}

/* Internal Functions */

BOOL IMS_IsInvalid(PIMS pims)
{
    return (IsBadWritePtr(pims, sizeof(IMS)) || pims->lpVtbl != &vtblIMS);
}

/***************************************************************************
 -  OutgoingViewRelease
 -
 *  Purpose:
 *      Call back function from itable on release of a view
 *      removes the view from the list of open views
 *      releases the table if there are no more open views on it
 *
 *  Arguments:
 *       ulCallerData   pointer to folder object
 *       lptbl      pointer to the table on which this is a view
 *       lpvtView       pointer to the view that was released
 *
 *
 */
STDAPI_(void) OutgoingViewRelease(ULONG ulCallerData, LPTABLEDATA lptbl,
    LPMAPITABLE lpvtView)
{
    PIMS pims;                  /* store who owns this view */
    ULONG ulViewsLeft;          /* number of open views left */

    pims = (PIMS) ulCallerData;

    /* do nothing if the message store is gone */
    if (IMS_IsInvalid(pims))
        return;

    IMS_EnterCriticalSection(pims);

    AssertSz(pims->lptblOutgoing == lptbl,
        "Different table data given to OutgoingViewRelease");

    ulViewsLeft = --(pims->cOutgoingViews);

    /* release the table data if the viewlist is empty */
    if (ulViewsLeft == 0)
    {
        UlRelease(lptbl);
        pims->lptblOutgoing = NULL;
    }

    IMS_LeaveCriticalSection(pims);

    return;
}

/*
 *  HrNewIMS
 *
 *  Purpose:
 *      Allocates and initializes an IMS object (internal
 *      implementation of IMsgStore).
 *
 *  Arguments:
 *      szStorePath         Path name of directory which is the
 *                          "root" of this message store.
 *      szStoreProps        Filename of IMsgStore properties
 *                          docfile in the store root.
 *      pmsp                pointer to the MS provider object.
 *      pmsl                Pointer to the MS logon object given to
 *                          MAPI when this store is created.
 *      prfs                Pointer to a context for accessing
 *                          receive folder settings.
 *      pps                 pointer to our profile section.
 *      psup                Pointer to MAPI Support Object.
 *      fCreate             TRUE if the function should create the docfile
 *                          containing IMS properties (FALSE opens existing).
 *      ppims               Location to return the address of the
 *                          newly created IMS object.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Does AddRef() of support object.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate memory for
 *                                  the object.
 */
HRESULT HrNewIMS(LPTSTR szStorePath, LPTSTR szStoreProps, PMSP pmsp, PMSL pmsl,
    PRFS prfs, LPPROFSECT pps, LPMAPISUP psup, BOOL fCreate, PIMS *ppims)
{
    SCODE sc = S_OK;
    HRESULT hr;
    HRESULT hrStg = hrSuccess;
    LPTSTR szPropFull = NULL;
    PIMS pimsNew = NULL;
    PEID peid = NULL;
    LPMESSAGE lpmsg = NULL;
    BOOL fDoneCreate = FALSE;
    LPMSGSESS pmsgsess = NULL;
    LPSPropValue pvalDLLName = NULL;

    AssertSz(szStorePath, "Bad szStorePath");
    AssertSz(szStoreProps, "Bad szStoreProps");
    AssertSz(pmsl, "Bad pmsl");
    AssertSz(prfs, "Bad prfs");
    AssertSz(ppims, "Bad ppims");

    *ppims = NULL;

    /* Begin by creating or opening the message store's property file. */
    /* This implementation of the sample message store puts its message */
    /* store properties in a file called MSGSTORE.PRP in the root folder */
    /* of the store. If we're opening an existing store, then we'll read */
    /* PR_RECORD_KEY from this file below. If we're creating the file, we */
    /* don't actually use it in this function; however, we still need to */
    /* create the file. */

    hr = HrOpenIMsgSession(&pmsgsess);
    if (hr != hrSuccess)
        goto hr_err;

    hr = HrAppendPath(szStorePath, szStoreProps, &szPropFull);
    if (hr != hrSuccess)
        goto hr_err;
    
    hr = HrOpenIMsg(pmsgsess, szPropFull, &pmsp->lmr, psup, fCreate, FALSE,
        TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto hr_err;

    if (fCreate)
        fDoneCreate = TRUE;

    /* Allocate and fill in the new object. */

    sc = LMAllocZ(&pmsp->lmr, sizeof(IMS), &pimsNew);
    if (sc != S_OK)
        goto sc_err;

    OBJ_Initialize(pimsNew, &vtblIMS, OT_MSGSTORE, pimsNew, &pmsl->cs);

    pimsNew->pmsl = pmsl;
    pimsNew->pmsp = pmsp;
    pimsNew->prfs = prfs;
    pimsNew->psup = psup;
    pimsNew->lmr = pmsl->lmr;
    pimsNew->eidStore.cb = 0L;
    pimsNew->eidStore.lpb = NULL;
    pimsNew->lptblOutgoing = NULL;
    pimsNew->cOutgoingViews = 0L;
    pimsNew->ulOQConn = 0L;
    pimsNew->ulTblConn = 0L;
    pimsNew->pmsgsess = pmsgsess;
    pimsNew->ulFlagsSLT = LOGOFF_ABORT;

    sc = ScAlloc(Cbtszsize(szStorePath), (PPV) &pimsNew->szStorePath);
    if (sc != S_OK)
        goto sc_err;

    lstrcpy(pimsNew->szStorePath, szStorePath);

    pimsNew->szProps = szPropFull;

    /* Fill in the uidResource.
     * This is used as the PR_STORE_RECORD_KEY and
     * as the UID contained in EntryIDs.
     */
    if (fCreate)
    {
        hr = psup->lpVtbl->NewUID(psup, &pimsNew->uidResource);
        if (hr != hrSuccess)
            goto hr_err;
    }
    else
    {
        LPSPropValue pval;

        /* Read out the PR_RECORD_KEY from the store.   */
        /* DO NOT READ THE PR_STORE_RECORD_KEY as that  */
        /* gets wrapped back to pimsNew->uidResource and    */
        /* HAS NOT BEEN FILLED IN YET!                      */

        hr = HrGetOneProp((LPMAPIPROP) lpmsg, PR_RECORD_KEY, &pval);
        if (hr != hrSuccess)
            goto hr_err;

        AssertSz(pval[0].Value.bin.cb == sizeof(MAPIUID),
            "Corrupted data returned from GetProps");

        pimsNew->uidResource = *((LPMAPIUID) pval[0].Value.bin.lpb);

        LMFree(&pmsp->lmr, pval);
    }

    /* Generate the PR_STORE_ENTRYID property in memory. */

    hr = HrConstructEID(&pimsNew->uidResource, &pmsp->lmr,
            pimsNew->szStorePath, &peid);
    if (hr != hrSuccess)
        goto hr_err;

    hr = HrGetOneProp((LPMAPIPROP)pps, PR_PROVIDER_DLL_NAME, &pvalDLLName);
    if (hr != hrSuccess)
        goto hr_err;

    hr = WrapStoreEntryID(0, pvalDLLName->Value.lpszA, CbEID(peid),
            (LPENTRYID)peid, &pimsNew->eidStore.cb,
            (LPENTRYID *) &pimsNew->eidStore.lpb);
    if (hr != hrSuccess)
        goto hr_err;

sc_err:
    if (sc != S_OK)
        hr = ResultFromScode(sc);

hr_err:
    LMFree(&pmsp->lmr, pvalDLLName);
    UlRelease(lpmsg);
    LMFree(&pmsp->lmr, peid);

    if (hr != hrSuccess)
    {
        if (fDoneCreate)
            DeleteFile(szPropFull);

        FreeNull(szPropFull);
        if (pimsNew)
        {
            FreeNull(pimsNew->szStorePath);
            LMFree(&pmsp->lmr, pimsNew->eidStore.lpb);
            LMFree(&pmsp->lmr, pimsNew);
        }

        if (pmsgsess)
            CloseIMsgSession(pmsgsess);
    }
    else
    {
        /* SUCCESS! */
        *ppims = pimsNew;
    }

    DebugTraceResult(HrNewIMS, hr);
    return hr;
}

/*
 *  HrInitIMSProps
 *
 *  Purpose:
 *      Sets the initial (and for read-only properties, the only)
 *      values for the base properties of the Message Store Object:
 *      takes as input parameters the values of those properties
 *      that are specific to this store and calculates (hard-coded)
 *      the values of those properties that are the same for all
 *      stores created by the Microsoft Sample Store Provider.
 *      Also sets attributes.
 *
 *  Arguments:
 *      pims        Internal IMsgStore object instance.
 *      szPswd      Logon Account Password.
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
HRESULT HrInitIMSProps(PIMS pims, LPTSTR szPswd)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL;
    LPSPropValue pval = NULL;
    LPSPropProblemArray pprba = NULL;
    LPSPropTagArray ptaga = NULL;
    LPSPropAttrArray patra = NULL;
    SCODE sc = S_OK;
    LPSPropProblem pProbl = NULL;

#define cInitIMSProps       10
#define grfInitIMSProps     ( PROPATTR_MANDATORY | PROPATTR_READABLE )

    AssertSz(pims, "Bad pims");
    NFAssertSz(pims->psup, "Bad support object");
    AssertSz(szPswd, "Bad szPswd");

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    /* Allocate the property arrays. */
    hr = HrAllocPropArrays(cInitIMSProps, &pval, &ptaga, &patra);
    if (hr != hrSuccess)
        goto exit;

    /* Initialize property value array and all property tags. */

    ptaga->cValues = patra->cValues = cInitIMSProps;

    pval[0].ulPropTag = ptaga->aulPropTag[0] = PR_STORE_ENTRYID;
    pval[0].Value.bin.cb = pims->eidStore.cb;
    pval[0].Value.bin.lpb = pims->eidStore.lpb;
    pval[1].ulPropTag = ptaga->aulPropTag[1] = PR_STORE_RECORD_KEY;
    pval[1].Value.bin.cb = sizeof(pims->uidResource);
    pval[1].Value.bin.lpb = (LPBYTE) &pims->uidResource;
    pval[2].ulPropTag = ptaga->aulPropTag[2] = PR_ENTRYID;
    pval[2].Value.bin.cb = pims->eidStore.cb;
    pval[2].Value.bin.lpb = pims->eidStore.lpb;
    pval[3].ulPropTag = ptaga->aulPropTag[3] = PR_RECORD_KEY;
    pval[3].Value.bin.cb = sizeof(pims->uidResource);
    pval[3].Value.bin.lpb = (LPBYTE) &pims->uidResource;
    pval[4].ulPropTag = ptaga->aulPropTag[4] = PR_DISPLAY_NAME;
    pval[4].Value.LPSZ = pims->szStorePath;
    pval[5].ulPropTag = ptaga->aulPropTag[5] = PR_SMS_PASSWORD;
    pval[5].Value.LPSZ = szPswd;

    /* We don't set support properties that are changed by READONLY */
    /* when the store is open. Those are or'ed in during GetProps. */
    /* See HrWrap_GetProps for details. */

    pval[6].ulPropTag = ptaga->aulPropTag[6] = PR_STORE_SUPPORT_MASK;
    pval[6].Value.ul = SMS_SUPPORTMASK;
        
    pval[7].ulPropTag = ptaga->aulPropTag[7] = PR_OBJECT_TYPE;
    pval[7].Value.l = MAPI_STORE;
    pval[8].ulPropTag = ptaga->aulPropTag[8] = PR_FILENAME_SEQUENCE_NUMBER;
    pval[8].Value.ul = 0x10000000;
    pval[9].ulPropTag = ptaga->aulPropTag[9] = PR_MDB_PROVIDER;
    pval[9].Value.bin.cb = sizeof(MAPIUID);
    pval[9].Value.bin.lpb = (LPBYTE) &uidProvider;

    /* Initialize the property attribute array. */

    patra->aPropAttr[0] = grfInitIMSProps;
    patra->aPropAttr[1] = grfInitIMSProps;
    patra->aPropAttr[2] = grfInitIMSProps;
    patra->aPropAttr[3] = grfInitIMSProps;
    patra->aPropAttr[4] = grfInitIMSProps | PROPATTR_WRITEABLE;
    patra->aPropAttr[5] = grfInitIMSProps;
    patra->aPropAttr[6] = grfInitIMSProps;
    patra->aPropAttr[7] = grfInitIMSProps;
    patra->aPropAttr[8] = grfInitIMSProps;
    patra->aPropAttr[9] = grfInitIMSProps;

    /* Set the property values. */

    hr = lpmsg->lpVtbl->SetProps(lpmsg, cInitIMSProps, pval, &pprba);
    if (hr != hrSuccess) /* || pprba)*/
        goto exit;
    if(pprba)
    {
        for(pProbl = pprba->aProblem; pProbl < pprba->aProblem + pprba->cProblem; ++pProbl)
        {
            if(pProbl->ulPropTag != PR_STORE_SUPPORT_MASK)
                goto exit;
        }
        LMFree(&pims->lmr, pprba);
        pprba = NULL;
    }


    /* Set the property attributes. */

    hr = SetAttribIMsgOnIStg(lpmsg, ptaga, patra, &pprba);
    if (hr != hrSuccess) /* || pprba)*/
        goto exit;
    if(pprba)
    {
        for(pProbl = pprba->aProblem; pProbl < pprba->aProblem + pprba->cProblem; ++pProbl)
        {
            if(pProbl->ulPropTag != PR_STORE_SUPPORT_MASK)
                goto exit;
        }
        LMFree(&pims->lmr, pprba);
        pprba = NULL;
    }



    /* If we succeeded up to this point, commit the properties. */

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

exit:
    AssertSz(hr == hrSuccess || HR_FAILED(hr), "No Warnings expected");

    if (pprba)
    {
        LMFree(&pims->lmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    FreePropArrays(&pval, &ptaga, &patra);

    UlRelease(lpmsg);

    DebugTraceResult(InitIMSProps, hr);
    return hr;
}

/*
 *  GetResourceUID
 *
 *  Purpose:
 *      Returns the one UID that identifies this MAPI resource
 *      (message store).
 *
 *  Arguments:
 *      pims    Internal IMsgStore object instance.
 *      lpuid   Location in which to return the value of the
 *              Resource UID.
 *
 *  Returns:
 *      VOID
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
VOID GetResourceUID(PIMS pims, LPMAPIUID lpuid)
{
    AssertSz(pims, "Bad pims");
    AssertSz(lpuid, "Bad lpuid");

    *lpuid = pims->uidResource;

    return;
}

/*********************************************************
 * FIsInvalidEID
 *
 *  Purpose         check if the peid points to an invalid EID
 *                  Returns TRUE if it is invalid. This routine
 *                  considers EIDs of length 0 invalid.
 *
 *  Parameter
 *      cb          number of bytes believed to be in peid
 *      peid        pointer to the entryid
 *      pims        store in which the object should be. May be NULL,
 *                  in which case, no check of the uid is performed.
 */
BOOL FIsInvalidEID(ULONG cb, PEID peid, PIMS pims)
{
    BOOL fInvalid;

    fInvalid = (cb < CbNewEID(0)
        || cb > CbNewEID(MAX_PATH)
        || IsBadReadPtr(peid, (UINT) cb)
        || IsBadStringPtr(peid->szPath, (UINT) -1)
        || cb != CbEID(peid)
        || peid->bVersion != SMPMS_VERSION);

    /* If the eid still looks good, and we were given the message store */
    /* object, then do one final check of the uid in the eid versus the */
    /* uid of the store. */

    if (!fInvalid && pims)
    {
        MAPIUID uid;

        GetResourceUID(pims, &uid);
        fInvalid = !IsEqualMAPIUID(&uid, &peid->uidResource);
    }

    return fInvalid;
}

/*
 *  HrUniqueFileName
 *
 *  Purpose:
 *      Returns a unique file name base that can be used by other
 *      parts of the store when a file needs to be created.  Gets
 *      the PR_FILENAME_SEQUENCE_NUMBER property out of the message
 *      store object, uses its textized form as the unique name,
 *      increments it, and stores it back in the object.  Sequence
 *      numbers begin at 0x10000000 and increment so that every
 *      file name returned is the same 8-character length.  (See
 *      HrInitIMSProps.)
 *
 *  Arguments:
 *      pims            Message Store Object.
 *      lpulSeqNumber   pointer to sequence number of this file name
 *      lppstrNewName   Location in which to return a pointer to a
 *                      buffer containing the unique file name.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      Increments the PR_FILENAME_SEQUENCE_NUMBER property of the
 *      message store object.
 *
 *  Errors:
 *      All SetProps and SaveChanges errors.  Also:
 *
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the return parameter.
 */
HRESULT HrUniqueFileName(PIMS pims, ULONG *lpulSeqNumber,
    LPTSTR *pszNewName)
{
    HRESULT hr = hrSuccess;
    LPTSTR szFileName = NULL;
    ULONG ulSeq = 0L;
    LPMESSAGE lpmsg = NULL;

    AssertSz(pims, "Bad pims");
    AssertSz(pszNewName, "Bad pszNewName");

    /* Allocate space for the return string */

    hr = HrAlloc((CCH_NAME - CCH_EXT) * sizeof(TCHAR), (PPV) &szFileName);
    if (hr != hrSuccess)
        goto exit;

    /* Get sequence number out of object, increment */
    /* sequence number, and turn it into a string.  */

    hr = HrGetSingleProp((LPMAPIPROP) pims, &pims->lmr,
        PR_FILENAME_SEQUENCE_NUMBER, &ulSeq);
    if (hr != hrSuccess)
        goto exit;

    ulSeq++;

    hr = HrOpenIMSPropsFileRetry(pims->pmsgsess, pims->szProps, &pims->lmr,
        pims->psup, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetOneROProp(lpmsg, &pims->lmr, PR_FILENAME_SEQUENCE_NUMBER, &ulSeq);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, KEEP_OPEN_READWRITE);
    if (hr != hrSuccess)
        goto exit;

    /* If this wsprintf statement changes, fix HrConvertSzToHex below. */

    wsprintf(szFileName, TEXT("%08lx"), ulSeq);

    *pszNewName = szFileName;
    *lpulSeqNumber = ulSeq;

exit:
    UlRelease(lpmsg);

    if (hr != hrSuccess)
        FreeNull(szFileName);

    DebugTraceResult(HrUniqueFileName, hr);
    return hr;
}

/*
 * HrConvertSzToHex
 *
 * Converts the string given into an equivalent number. The string must
 * contain characters in the range 0-9, A-F, or a-f. If the routine finds
 * characters outside these ranges in the string, it will terminate with
 * the error MAPI_E_CALL_FAILED. The string must be at least 8 characters
 * long (a 32-bit number is fully-specified by a 8 hex characters). The
 * routine will use only the first 8 characters in the string, even if the
 * string is longer than 8 characters. Note that only the first 8 characters
 * must be within the proper range. Characters after the first 8 will be
 * ignored.
 *
 * Parameters:
 *  szName: The string to convert.
 *  pulAnswer: A pointer to the location to return the converted answer.
 *
 * Errors:
 *  MAPI_E_CALL_FAILED -- when a character is out of range.
 */
static HRESULT HrConvertSzToHex(LPSTR szName, ULONG *pulAnswer)
{
    HRESULT hr = hrSuccess;
    CHAR *pch;
    CHAR *pchMax;
    ULONG ulAns = 0;
    ULONG ichConv = 0;

    /* String must be at least 8 hex chars long. It should have come from */
    /* the HrUniqueFileName function above, which uses wsprintf to generate */
    /* the string. */

    if (    IsBadStringPtr(szName, (UINT) -1)
        ||  lstrlen(szName) < 8)
    {
        TrapSz("Bad input to function");
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    pch = szName;
    pchMax = szName + lstrlen(szName);

    /* Only convert the first 8 characters, no matter how long the string is. */
    while(pch < pchMax && ichConv < 8)
    {
        ulAns <<= 4;

        if (*pch >= '0' && *pch <= '9')
            ulAns += (*pch - '0');
        else if (*pch >= 'a' && *pch <= 'f')
            ulAns += (*pch - 'a' + 0xA);
        else if (*pch >= 'A' && *pch <= 'F')
            ulAns += (*pch - 'A'+ 0xA);
        else
        {
            TraceSz2("SampleMS: HrConvertSztoHex: char %c(%#x) out of range.\n",
                *pch, *pch);
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            goto exit;
        }

        ++pch;
        ++ichConv;
    }

    *pulAnswer = ulAns;

exit:
    DebugTraceResult(HrConvertSzToHex, hr);
    return hr;
}

/*
 * HrGetSequenceNum
 *
 * This routine takes a message eid and gets the
 * numerical equivalent of the base file name in the entryid. So, if the
 * base name of the message was "00000005.msg", the function would return
 * 0x00000005.
 *
 * Parameters:
 *  pimsg: the message object to update.
 *  pulSequenceNum: a pointer to the location to place the generated number.
 *
 */
static HRESULT HrGetSequenceNum(PEID peid, ULONG *pulSequenceNum)
{
    HRESULT hr;
    LPSTR szBaseName;
    ULONG ulSeqNum;

    szBaseName = SzBaseName(peid);

    hr = HrConvertSzToHex(szBaseName, &ulSeqNum);
    if (hr != hrSuccess)
        goto exit;

    *pulSequenceNum = ulSeqNum;

exit:
    DebugTraceResult(HrGetSequenceNum, hr);
    return hr;
}

/*
 *  IMS_NeuterChildren, IMS_Neuter
 *
 *  Purpose:
 *      Free all memory and resources associated with a logon.  We
 *      cannot, however, remove the critical section:  that must be
 *      done by the caller of this routine.
 *
 *  Arguments:
 *      pims            Pointer to the MS object.
 *
 *  Returns:
 *      None.
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
void IMS_NeuterChildren(POBJ pobj, int iLevel)
{
#ifdef DEBUG
    int i;

    DebugTrace("SMS:   ");
    for (i = 0; i < iLevel; ++i)
        DebugTrace("  ");

    switch (pobj->wType)
    {
    case OT_MSGSTORE:
        DebugTrace("IMsgStore (%s)", ((PIMS) pobj)->szStorePath);
        break;
    case OT_FOLDER:
        DebugTrace("IMAPIFolder");
        break;
    case OT_MESSAGE:
        DebugTrace("IMessage");
        break;
    case OT_ATTACH:
        DebugTrace("IAttach");
        break;
    case OT_STREAM:
        DebugTrace("IStream");
        break;
    }
    DebugTrace(" (@%08lX,cRef=%ld)\n", pobj, pobj->cRef);
#endif

    while (TRUE)
    {
        POBJ pobjChild;

        pobjChild = pobj->pobjHead;

        if (pobjChild == NULL)
            break;

        pobj->pobjHead = pobjChild->pobjNext;
        IMS_NeuterChildren(pobjChild, iLevel + 1);
    }

    if (pobj->wType != OT_MSGSTORE)
    {
        LPFNNEUTER lpfnNeuter;

        lpfnNeuter = rgfnNeuter[pobj->wType];

        if (lpfnNeuter != 0)
            lpfnNeuter(pobj);

        pobj->lpVtbl = 0;
        LMFree(&pobj->pims->lmr, pobj);
    }
}

void IMS_Neuter(PIMS pims)
{
    HRESULT hr;
    ULONG ulFlags;


    if (pims->ulOQConn)
    {
        pims->psup->lpVtbl->Unsubscribe(pims->psup, pims->ulOQConn);
        pims->ulOQConn = 0;
    }

    if (pims->ulTblConn)
    {
        pims->psup->lpVtbl->Unsubscribe(pims->psup, pims->ulTblConn);
        pims->ulTblConn = 0;
    }
        
    OBJ_SetFlag(pims, MSF_BEINGDESTROYED);
    
    ulFlags = pims->ulFlagsSLT;

    hr = pims->psup->lpVtbl->StoreLogoffTransports(pims->psup, &ulFlags);

#ifdef DEBUG
    /* The support object given us during config doesn't support */
    /* StoreLogoffTransports. It isn't an error to get no support */
    /* in that case. */
    if (hr != hrSuccess && GetScode(hr) != MAPI_E_NO_SUPPORT)
        TraceSz1("SMS: IMS_Neuter: StoreLogoffTransports(LOGOFF_ABORT) "
            "returned unexpected error %s", SzDecodeScode(GetScode(hr)));
#endif

    if (pims->cRef != 0 || pims->pobjHead != 0)
    {
        TraceSz("\n---------------------------------------------------------"
            "-------");
        TraceSz("SMS: The following objects were not released before Logoff:");
        IMS_NeuterChildren((POBJ) pims, 0);
        TraceSz("-----------------------------------------------------------"
            "-----\n");
    }

    /* Free MS object's resources */
    FreeNull(pims->szStorePath);
    FreeNull(pims->szProps);
    LMFree(&pims->lmr, pims->eidStore.lpb);
    CloseRFS(pims->prfs);

    if (pims->lptblOutgoing)
    {
        if (pims->cOutgoingViews)
        {
            TraceSz1("Sample MS: IMS_Neuter: Leaked outgoing queue table "
                "(# views left = %08lX)\n", pims->cOutgoingViews);
            pims->cOutgoingViews = 0;
        }

        UlRelease(pims->lptblOutgoing);
    }


    CloseIMsgSession(pims->pmsgsess);
    pims->pmsgsess = NULL;

    /* Make the logon object forget about us */
    if (pims->pmsl)
        pims->pmsl->pims = NULL;
}

/*
 *  HrOpenIMSPropsFileRetry
 *
 *  Purpose:
 *      Open the IMsgStore properties docfile as an IMessage
 *      instance to get/set properties.
 *      This retries up to NUM_RETRIES times on MAPI_E_NO_ACCESS
 *
 *  Arguments:
 *      szFile      The file to open.
 *      plmr        a pointer to the linked memory routines.
 *      psup        a pointer to the MAPI support object.
 *      fModify     TRUE means the caller wants read/write access.
 *                  FALSE means read-only access.
 *      lppmsg      Address of a location in which to return a
 *                  pointer to the newly opened IMessage instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      IMessage on IStorage opening errors.
 */
HRESULT HrOpenIMSPropsFileRetry(LPMSGSESS pmsgsess, LPTSTR szFile, PLMR plmr,
    LPMAPISUP psup, BOOL fModify, LPMESSAGE * lppmsg)
{
    UINT iRetry;                /* number of attempts to open */
    HRESULT hr;

    iRetry = 0;

    while (TRUE)
    {
        hr = HrOpenIMsg(pmsgsess, szFile, plmr, psup, FALSE, fModify, TRUE,
            lppmsg);

        if (GetScode(hr) != MAPI_E_NO_ACCESS || ++iRetry >= NUM_RETRIES)
            break;

        Sleep(500);
    }

    #ifdef DEBUG
    if (iRetry >= NUM_RETRIES)
        TraceSz("HrOpenIMSPropsFileRetry: Failing open. Too many tries.");
    #endif

    DebugTraceResult(HrOpenIMSPropsFileRetry, hr);
    return hr;
}

/*
 * HrGetSMSStandardNotifKey
 *
 * Purpose
 *
 * return the notification key for standard notifications (everything
 * except outgoing queue notifications).
 * memory should be freed with FreeNull
 *
 * In order to call the MAPI registration function, we need to turn
 * an EntryID into a "notification key" (something unique to an
 * object in the store that will remain constant throughout this
 * logon session).  In the case of the Sample Store, we can just
 * use the local file name of the object (folder or message).
 * If the user is interested in notifications about all objects in the
 * store, we use the store's uid for the key.
 *
 * Parameters
 * pims         pointer to the message store object
 * peid         the entryid of the object 
 * lppKey       pointer to the location to return the key
 */
static HRESULT HrGetSMSStandardNotifKey(PIMS pims, PEID peid,
    LPNOTIFKEY * lppKey)
{
    HRESULT hr;
    LPNOTIFKEY lpKey;
    ULONG cb;           /* number of bytes in the key */

    if (peid)
    {
        LPMAPIUID lpuidEID = NULL;
        LPTSTR szPathEID = NULL;
        LPTSTR szFileEID = NULL;

        hr = HrDeconstructEID(peid, &lpuidEID, &szPathEID, &szFileEID);
        if (hr == hrSuccess)
        {
            cb = CbNewNOTIFKEY(Cbtszsize(szFileEID));
            hr = HrAlloc(cb, (PPV) &lpKey);
        }

        if (hr == hrSuccess)
        {
            lstrcpy((LPTSTR) &lpKey->ab, szFileEID);
            lpKey->cb = Cbtszsize(szFileEID);
        }

        FreeNull(lpuidEID);
        FreeNull(szPathEID);
        FreeNull(szFileEID);

        if (hr != hrSuccess)
            goto exit;
    }
    else
    {
        /* The caller is interested in notifications on all objects in the */
        /* store. Generate a key from our uid. */

        cb = CbNewNOTIFKEY(sizeof(MAPIUID));
        hr = HrAlloc(cb, (PPV) &lpKey);
        if (hr != hrSuccess)
            goto exit;

        GetResourceUID(pims, (MAPIUID *) &(lpKey->ab[0]));
        lpKey->cb = sizeof(MAPIUID);
    }

exit:
    if (hr != hrSuccess)
        FreeNull(lpKey);
    else
        *lppKey = lpKey;

    DebugTraceResult(HrGetSMSStandardNotifKey, hr);
    return hr;
}


