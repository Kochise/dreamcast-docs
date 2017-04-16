/****************************************************************************
 *
 *  Copyright (C) 1996 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dmdfm.h
 *  Content:    DetachFromMedium include file
 *
 ****************************************************************************/
#ifndef __DMDFM_INCLUDED__
#define __DMDFM_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 *      IDirectMemory
 *
 ****************************************************************************/

#define DMDFM_IFREMOVABLE       0x00000001
#define DMDFM_IFFIXED           0x00000002
#define DMDFM_IFNETWORK         0x00000004
#define DMDFM_IFCDROM           0x00000008
#define DMDFM_IFRAMDISK         0x00000010
#define DMDFM_ALWAYS            0x0000001F
#define DMDFM_IFMASK            0x0000001F //// ;Internal

#define DMDFM_CODEPAGES         0x00000100
#define DMDFM_ROPAGES           0x00000200
#define DMDFM_RWPAGES           0x00000400
#define DMDFM_RESPAGES          0x00000800
#define DMDFM_OTHERPAGES        0x00001000
#define DMDFM_ALLPAGES          0x00001F00
#define DMDFM_MASKPAGES         0x00001F00 //// ;Internal

#define DMDFM_VALID             0x00000F1F //// ;Internal

STDMETHODIMP DetachFromMedium(HINSTANCE hinst, DWORD fl);

/****************************************************************************
 *
 *  Return Codes
 *
 ****************************************************************************/

/*
 *  The operation completed successfully.
 */
#define DM_OK                           S_OK

/*
 *  The operation had no effect.
 */
#define DM_NOEFFECT                     S_FALSE

/*
 * An invalid parameter was passed to the returning function,
 * or the object was not in a state that admitted the function
 * to be called.
 */
#define DMERR_INVALIDPARAM              E_INVALIDARG

/*
 * An undetermined error occurred inside the DirectMemory subsystem
 */
#define DMERR_GENERIC                   E_FAIL

/*
 *  The DirectMemory subsystem couldn't allocate sufficient memory
 *  to complete the caller's request.
 */
#define DMERR_OUTOFMEMORY               E_OUTOFMEMORY

/*
 * The function called is not supported at this time
 */
#define DMERR_UNSUPPORTED               E_NOTIMPL

#ifdef __cplusplus
};
#endif

#endif  /* __DMDFM_INCLUDED__ */
