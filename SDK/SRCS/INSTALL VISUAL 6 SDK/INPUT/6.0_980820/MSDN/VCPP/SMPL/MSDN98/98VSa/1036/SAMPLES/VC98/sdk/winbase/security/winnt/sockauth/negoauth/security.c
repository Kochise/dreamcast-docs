/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    security.c

Abstract:

    Handles communication with the SSP package.

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#define SECURITY_WIN32
#include "sspi.h"
#include "issperr.h"
#include "security.h"
#include "collect.h"

static HINSTANCE g_hLib;
static DWORD g_cbMaxToken;
static PSecurityFunctionTable g_pFuncs;

// structure storing the state of the authentication sequence
//
typedef struct _AUTH_SEQ {
    BOOL _fNewConversation;
    CredHandle _hcred;
    BOOL _fHaveCredHandle;
    BOOL _fHaveCtxtHandle;
    struct _SecHandle  _hctxt;
} AUTH_SEQ, *PAUTH_SEQ;

#define SEC_SUCCESS(Status) ((Status) >= 0)

#define PACKAGE_NAME	"negotiate"
#define NT_DLL_NAME		"security.dll"

// Target name for the security package
// De-comment after filling appropriate principal name, here.
//
// #define TOKEN_SOURCE_NAME       "<Domain>\\<User>"


BOOL InitPackage (DWORD *pcbMaxMessage)
/*++

 Routine Description:

    Finds, loads and initializes the security package

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	FARPROC pInit;
	SECURITY_STATUS ss;
	PSecPkgInfo pkgInfo;

	// load and initialize the ntlm ssp
	//
	g_hLib = LoadLibrary (NT_DLL_NAME);
	if (NULL == g_hLib)  {
		fprintf (stderr, "Couldn't load dll: %u\n", GetLastError ());
		return(FALSE);
	}

	pInit = GetProcAddress (g_hLib, SECURITY_ENTRYPOINT);
	if (NULL == pInit)  {
		fprintf (stderr, "Couldn't get sec init routine: %u\n", GetLastError ());
		return(FALSE);
	}

	g_pFuncs = (PSecurityFunctionTable) pInit ();
	if (NULL == g_pFuncs)  {
		fprintf (stderr, "Couldn't init package\n");
		return(FALSE);
	}

	// Query for the package we're interested in
	//
	ss = g_pFuncs->QuerySecurityPackageInfo (PACKAGE_NAME, &pkgInfo);
	if (!SEC_SUCCESS(ss))  {
		fprintf (stderr, "Couldn't query package info for %s, error %u\n",
					PACKAGE_NAME, ss);
		return(FALSE);
	}

	g_cbMaxToken = pkgInfo->cbMaxToken;

	g_pFuncs->FreeContextBuffer (pkgInfo);

	*pcbMaxMessage = g_cbMaxToken;

	return TRUE;
}

BOOL TermPackage ()
{
	FreeLibrary (g_hLib);

	return(TRUE);
}

BOOL GenClientContext (
			DWORD dwKey,
			BYTE *pIn,
			DWORD cbIn,
			BYTE *pOut,
			DWORD *pcbOut,
			BOOL *pfDone)
/*++

 Routine Description:

    Optionally takes an input buffer coming from the server and returns
	a buffer of information to send back to the server.  Also returns
	an indication of whether or not the context is complete.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SECURITY_STATUS	ss;
	TimeStamp		Lifetime;
	SecBufferDesc	OutBuffDesc;
	SecBuffer		OutSecBuff;
	SecBufferDesc	InBuffDesc;
	SecBuffer		InSecBuff;
	ULONG			ContextAttributes;
	PAUTH_SEQ		pAS;

	// Lookup pAS based on Key
	//
	if (!GetEntry (dwKey, (PVOID*) &pAS))
		return(FALSE);

	if (pAS->_fNewConversation)  {
		ss = g_pFuncs->AcquireCredentialsHandle (
							NULL,	// principal
							PACKAGE_NAME,
							SECPKG_CRED_OUTBOUND,
							NULL,	// LOGON id
							NULL,	// auth data
							NULL,	// get key fn
							NULL,	// get key arg
							&pAS->_hcred,
							&Lifetime
							);
		if (SEC_SUCCESS (ss))
			pAS->_fHaveCredHandle = TRUE;
		else {
			fprintf (stderr, "AcquireCreds failed: %u\n", ss);
			return(FALSE);
		}
	}

	// prepare output buffer
	//
	OutBuffDesc.ulVersion = 0;
	OutBuffDesc.cBuffers = 1;
	OutBuffDesc.pBuffers = &OutSecBuff;

	OutSecBuff.cbBuffer = *pcbOut;
	OutSecBuff.BufferType = SECBUFFER_TOKEN;
	OutSecBuff.pvBuffer = pOut;

	// prepare input buffer
	//
	if (!pAS->_fNewConversation)  {
		InBuffDesc.ulVersion = 0;
		InBuffDesc.cBuffers = 1;
		InBuffDesc.pBuffers = &InSecBuff;

		InSecBuff.cbBuffer = cbIn;
		InSecBuff.BufferType = SECBUFFER_TOKEN;
		InSecBuff.pvBuffer = pIn;
	}

	ss = g_pFuncs->InitializeSecurityContext (
						&pAS->_hcred,
						pAS->_fNewConversation ? NULL : &pAS->_hctxt,
						TOKEN_SOURCE_NAME,
						0,	// context requirements
						0,	// reserved1
						SECURITY_NATIVE_DREP,
						pAS->_fNewConversation ? NULL : &InBuffDesc,
						0,	// reserved2
						&pAS->_hctxt,
						&OutBuffDesc,
						&ContextAttributes,
						&Lifetime
						);
	if (!SEC_SUCCESS (ss))  {
		fprintf (stderr, "init context failed: %u\n", ss);
		return FALSE;
	}

	pAS->_fHaveCtxtHandle = TRUE;

	// Complete token -- if applicable
	//
	if ((SEC_I_COMPLETE_NEEDED == ss) || (SEC_I_COMPLETE_AND_CONTINUE == ss))  {
		if (g_pFuncs->CompleteAuthToken) {
			ss = g_pFuncs->CompleteAuthToken (&pAS->_hctxt, &OutBuffDesc);
			if (!SEC_SUCCESS(ss))  {
				fprintf (stderr, "complete failed: %u\n", ss);
				return FALSE;
			}
		}
		else {
			fprintf (stderr, "Complete not supported.\n");
			return FALSE;
		}
	}

	*pcbOut = OutSecBuff.cbBuffer;

	if (pAS->_fNewConversation)
		pAS->_fNewConversation = FALSE;

	*pfDone = !((SEC_I_CONTINUE_NEEDED == ss) ||
				(SEC_I_COMPLETE_AND_CONTINUE == ss));

	return TRUE;
}

BOOL GenServerContext (
			DWORD dwKey,
			BYTE *pIn,
			DWORD cbIn,
			BYTE *pOut,
			DWORD *pcbOut,
			BOOL *pfDone)
/*++

 Routine Description:

    Takes an input buffer coming from the client and returns a buffer
	to be sent to the client.  Also returns an indication of whether or
	not the context is complete.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SECURITY_STATUS	ss;
	TimeStamp		Lifetime;
	SecBufferDesc	OutBuffDesc;
	SecBuffer		OutSecBuff;
	SecBufferDesc	InBuffDesc;
	SecBuffer		InSecBuff;
	ULONG			ContextAttributes;
	PAUTH_SEQ		pAS;

	// Lookup pAS based on Key
	//
	if (!GetEntry (dwKey, (PVOID*) &pAS))
		return(FALSE);

	if (pAS->_fNewConversation)  {
		ss = g_pFuncs->AcquireCredentialsHandle (
							NULL,	// principal
							PACKAGE_NAME,
							SECPKG_CRED_INBOUND,
							NULL,	// LOGON id
							NULL,	// auth data
							NULL,	// get key fn
							NULL,	// get key arg
							&pAS->_hcred,
							&Lifetime
							);
		if (SEC_SUCCESS (ss))
			pAS->_fHaveCredHandle = TRUE;
		else {
			fprintf (stderr, "AcquireCreds failed: %u\n", ss);
			return(FALSE);
		}
	}

	// prepare output buffer
	//
	OutBuffDesc.ulVersion = 0;
	OutBuffDesc.cBuffers = 1;
	OutBuffDesc.pBuffers = &OutSecBuff;

	OutSecBuff.cbBuffer = *pcbOut;
	OutSecBuff.BufferType = SECBUFFER_TOKEN;
	OutSecBuff.pvBuffer = pOut;

	// prepare input buffer
	//
	InBuffDesc.ulVersion = 0;
	InBuffDesc.cBuffers = 1;
	InBuffDesc.pBuffers = &InSecBuff;

	InSecBuff.cbBuffer = cbIn;
	InSecBuff.BufferType = SECBUFFER_TOKEN;
	InSecBuff.pvBuffer = pIn;

	ss = g_pFuncs->AcceptSecurityContext (
						&pAS->_hcred,
						pAS->_fNewConversation ? NULL : &pAS->_hctxt,
						&InBuffDesc,
						0,	// context requirements
						SECURITY_NATIVE_DREP,
						&pAS->_hctxt,
						&OutBuffDesc,
						&ContextAttributes,
						&Lifetime
						);
	if (!SEC_SUCCESS (ss))  {
		fprintf (stderr, "init context failed: %u\n", ss);
		return FALSE;
	}

	pAS->_fHaveCtxtHandle = TRUE;

	// Complete token -- if applicable
	//
	if ((SEC_I_COMPLETE_NEEDED == ss) || (SEC_I_COMPLETE_AND_CONTINUE == ss))  {
		if (g_pFuncs->CompleteAuthToken) {
			ss = g_pFuncs->CompleteAuthToken (&pAS->_hctxt, &OutBuffDesc);
			if (!SEC_SUCCESS(ss))  {
				fprintf (stderr, "complete failed: %u\n", ss);
				return FALSE;
			}
		}
		else {
			fprintf (stderr, "Complete not supported.\n");
			return FALSE;
		}
	}

	*pcbOut = OutSecBuff.cbBuffer;

	if (pAS->_fNewConversation)
		pAS->_fNewConversation = FALSE;

	*pfDone = !((SEC_I_CONTINUE_NEEDED == ss) ||
				(SEC_I_COMPLETE_AND_CONTINUE == ss));

	return TRUE;
}

BOOL ImpersonateContext (DWORD dwKey)
/*++

 Routine Description:

    Impersonates the client whose context is associated with the
	supplied key.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SECURITY_STATUS	ss;
	PAUTH_SEQ		pAS;

	// Lookup pAS based on Key
	//
	if (!GetEntry (dwKey, (PVOID*) &pAS))
		return(FALSE);

	ss = g_pFuncs->ImpersonateSecurityContext (&pAS->_hctxt);
	if (!SEC_SUCCESS(ss)) {
		fprintf (stderr, "Impersonate failed: %u\n", ss);
		return(FALSE);
	}

	return(TRUE);
}

BOOL RevertContext (DWORD dwKey)
/*++

 Routine Description:

    Reverts to the original server context.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SECURITY_STATUS ss;
	PAUTH_SEQ		pAS;

	// Lookup pAS based on Key
	//
	if (!GetEntry (dwKey, (PVOID*) &pAS))
		return(FALSE);

	ss = g_pFuncs->RevertSecurityContext (&pAS->_hctxt);
	if (!SEC_SUCCESS(ss)) {
		fprintf (stderr, "Revert failed: %u\n", ss);
		return(FALSE);
	}

	return(TRUE);
}

BOOL InitSession (DWORD dwKey)
/*++

 Routine Description:

    Initializes the context associated with a key and adds it to the
	collection.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	PAUTH_SEQ pAS;

	pAS = (PAUTH_SEQ) malloc (sizeof (AUTH_SEQ));
	if (NULL == pAS)
		return(FALSE);

	pAS->_fNewConversation = TRUE;
	pAS->_fHaveCredHandle = FALSE;
	pAS->_fHaveCtxtHandle = FALSE;
		
	if (!AddEntry (dwKey, (PVOID)pAS))  {
		free (pAS);
		return(FALSE);
	}

	return(TRUE);
}

BOOL TermSession (DWORD dwKey)
/*++

 Routine Description:

    Releases the resources associated with a key and removes it from
	the collection.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	PAUTH_SEQ pAS;

	if (!DeleteEntry (dwKey, (LPVOID*)&pAS))	
		return(FALSE);

	if (pAS->_fHaveCtxtHandle)
		g_pFuncs->DeleteSecurityContext (&pAS->_hctxt);

	if (pAS->_fHaveCredHandle)
		g_pFuncs->FreeCredentialHandle (&pAS->_hcred);

	free (pAS);
	
	return(TRUE);
}	
