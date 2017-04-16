#include <windows.h>
#include <stdio.h>
#include "CryptErr.h"

#ifdef __CPLUSPLUS
extern "C"
	{
#endif

void WhatIsError(BOOL bGLE, DWORD dwError, LPSTR pTitle)
	{
	char Msg[1024];
	BOOL bDisplayError = TRUE;

	if (bGLE != 0)
		{
		dwError = GetLastError();
		}

	switch (dwError)
		{
		default:
			sprintf(Msg, "Unknown error: %ld.", dwError);
			break;
		case 0:
			bDisplayError = FALSE;
			break;
		case ERROR_INVALID_PARAMETER:
			strcpy(Msg, "One of the parameters contains an invalid value. This is most often an illegal pointer.");
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			strcpy(Msg, "The operating system ran out of memory during the operation.");
			break;
		case NTE_BAD_FLAGS:
			strcpy(Msg, "The dwFlags parameter has an illegal value.");
			break;
		case NTE_BAD_KEYSET:
			strcpy(Msg, "The Registry entry for the key container could not be opened and may not exist.");
			break;
		case NTE_BAD_KEYSET_PARAM:
			strcpy(Msg, "The pszContainer or pszProvider parameter is set to an illegal value.");
			break;
		case NTE_BAD_PROV_TYPE:
			strcpy(Msg, "The value of the dwProvType parameter is out of range. All provider types must be from 1 to 999, inclusive.");
			break;
		case NTE_BAD_SIGNATURE:
			strcpy(Msg, "The provider DLL signature did not verify correctly. Either the DLL or the digital signature has been tampered with.");
			break;
		case NTE_EXISTS:
			strcpy(Msg, "The dwFlags parameter is CRYPT_NEWKEYSET, but the key container already exists.");
			break;
		case NTE_KEYSET_ENTRY_BAD:
			strcpy(Msg, "The Registry entry for the pszContainer key container was found (in the HKEY_CURRENT_USER window), but is corrupt. See the section System Administration for details about CryptoAPI's Registry usage.");
			break;
		case NTE_KEYSET_NOT_DEF:
			strcpy(Msg, "No Registry entry exists in the HKEY_CURRENT_USER window for the key container specified by pszContainer.");
			break;
		case NTE_NO_MEMORY:
			strcpy(Msg, "The CSP ran out of memory during the operation.");
			break;
		case NTE_PROV_DLL_NOT_FOUND:
			strcpy(Msg, "The provider DLL file does not exist or is not on the current path.");
			break;
		case NTE_PROV_TYPE_ENTRY_BAD:
			strcpy(Msg, "The Registry entry for the provider type specified by dwProvType is corrupt. This error may relate to either the user default CSP list or the machine default CSP list. See the section System Administration for details about CryptoAPI's Registry usage.");
			break;
		case NTE_PROV_TYPE_NO_MATCH:
			strcpy(Msg, "The provider type specified by dwProvType does not match the provider type found in the Registry. Note that this error can only occur when pszProvider specifies an actual CSP name.");
			break;
		case NTE_PROV_TYPE_NOT_DEF:
			strcpy(Msg, "No Registry entry exists for the provider type specified by dwProvType.");
			break;
		case NTE_PROVIDER_DLL_FAIL:
			strcpy(Msg, "The provider DLL file could not be loaded, and may not exist. If it exists, then the file is not a valid DLL.");
			break;
		case NTE_SIGNATURE_FILE_BAD:
			strcpy(Msg, "An error occurred while loading the DLL file image, prior to verifying its signature.");
			break;
		}

	if (bDisplayError)
		{
		if (pTitle != NULL)
			{
			MessageBox(NULL, Msg, pTitle, 0);
			}
		else
			{
			MessageBox(NULL, Msg, "CryptoAPI Error", 0);
			}
		}

	return;
	}

#ifdef __CPLUSPLUS
	}
#endif
