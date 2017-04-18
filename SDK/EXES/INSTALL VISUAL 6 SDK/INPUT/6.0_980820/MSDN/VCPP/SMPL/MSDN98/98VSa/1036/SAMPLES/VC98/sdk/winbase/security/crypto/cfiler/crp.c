
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// CRP.C
#include "cfiler.h"

HCRYPTPROV					hMe;
ALG_ID						AlgidEncrypt;
ALG_ID						AlgidSign;
TCHAR						sPass[BUF_SIZE];
TCHAR						szPassName[BUF_SIZE];

extern HANDLE	 			ghModule; 
extern HMENU				ghMenu;                                                                   		 		

/************************************************************************\
* EnterPass()
*
* Dialog procedure for the "PASSWORD" dialog box.
*
* Stores the password entered by the user into 
* the global buffer sPass
\************************************************************************/

WINAPI EnterPass(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam)  {
	TCHAR szMessage[BUF_SIZE];
	
	switch(wMsgID) {
		case WM_INITDIALOG:
			lstrcpy(szMessage, TEXT("Enter password: "));
			lstrcat(szMessage, szPassName);
			SetDlgItemText(hDlg, IDC_PASSTEXT, szMessage);
			SetDlgItemText(hDlg, IDC_EDIT1, TEXT("\0"));
			SetDlgItemText(hDlg, IDC_EDIT2, TEXT("\0"));

			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				TCHAR szVerify[BUF_SIZE];
				
				case IDOK:
					if (!GetDlgItemText(hDlg, IDC_EDIT1, sPass, BUF_SIZE)) {
	                	if (MessageBox(hDlg, TEXT("No password entered."), NULL, MB_OK) == IDOK) {
							EndDialog(hDlg, FALSE);
							return FALSE;
						}
					}
	                				
					SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
					
					if (!GetDlgItemText(hDlg, IDC_EDIT2, szVerify, BUF_SIZE)) {
						MessageBox(hDlg, TEXT("No password entered."), NULL, MB_OK);
						EndDialog(hDlg, FALSE);
						return FALSE;
					}
					
					if (lstrcmp(sPass, szVerify)) {
						MessageBox(hDlg, TEXT("Could not verify password."), NULL, MB_OK);
						EndDialog(hDlg, FALSE);
						return FALSE;
					}

					EndDialog(hDlg, TRUE);					
					
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, -1);
					return -1;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}	

/************************************************************************\
* CryptDlgProc()
*
* Dialog procedure for all dialog boxes of the
* application besides "PASSWORD", "ENCRYPTION_ALGORITHM,"
* and "HASH_ALGORITHM."
\************************************************************************/

LRESULT WINAPI CryptDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDOK:
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* EncryptDlgProc()
*
* Dialog procedure for "ENCRYPTION_ALGORITHM" dialog box.
\************************************************************************/

LRESULT WINAPI EncryptDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			if (AlgidEncrypt == CALG_RC4)
				CheckRadioButton(hDlg, IDC_RC2, IDC_RC4, IDC_RC4);
			else
				CheckRadioButton(hDlg, IDC_RC2, IDC_RC4, IDC_RC2);
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDC_RC2:
					AlgidEncrypt = CALG_RC2;
					return TRUE;

				case IDC_RC4:
					AlgidEncrypt = CALG_RC4;
					return TRUE;
			
				case IDOK:
					if (!AlgidEncrypt)
						AlgidEncrypt = CALG_RC2;
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* HashDlgProc()
*
* Dialog procedure for "HASH_ALGORITHM" dialog box
\************************************************************************/

LRESULT WINAPI HashDlgProc(HWND hDlg, UINT wMsgID, UINT wParam, LPARAM lParam) {
	switch(wMsgID) {
		case WM_INITDIALOG:
			if (AlgidSign == CALG_SHA)
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_SHA);
			else if (AlgidSign == CALG_MD5)
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_MD5);
			else
				CheckRadioButton(hDlg, IDC_MD4, IDC_SHA, IDC_MD4);
			return FALSE;
			
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDC_MD4:
					AlgidSign = CALG_MD4;
					return TRUE;

				case IDC_MD5:
					AlgidSign = CALG_MD5;
					return TRUE;

				case IDC_SHA:
					AlgidSign = CALG_SHA;
					return TRUE;

				case IDOK:
					EndDialog(hDlg, TRUE);
					return TRUE;
					
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				default:
					return FALSE;
			}
			break;
	}
	return FALSE;
}

/************************************************************************\
* GetPass()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Creates a dialog box prompting the user to enter a password.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetPass(HWND hWnd) {
	INT bRet = 0;

	do {
		if (bRet == -1)
			break;

		// Prompt the user to enter a password.

		bRet = DialogBox(ghModule, TEXT("PASSWORD"), hWnd, EnterPass);
	} while (!bRet || !lstrcmp(sPass, TEXT("\0")) || !lstrcmp(sPass, TEXT("")));

	AlgidEncrypt = 0;
	
	return TRUE;
}

/************************************************************************\
* GetfnKey()
*
* purpose:
* Retrieves fnKey from the registry.
* fnKey is used to encrypt and decrypt filenames.
* If fnKey does not exist in the registry, GetfnKey creates it.
*
* returns
* a valid key if successful
* 0 if unsuccessful.
\************************************************************************/

HCRYPTKEY GetfnKey(HWND hWnd) {
	BYTE 		pbFileKeyBlob[BUF_SIZE];
	DWORD 		dwFileBlobLen = BUF_SIZE;
	LONG		lRv;
	HKEY		hKey;
	DWORD		dwType;
	DWORD		dwSize;
	DWORD		dwDisposition;
	HCRYPTKEY	phEncryptPubKey;
	HCRYPTKEY	hfnKey;

	if (!GetEncryptPublicKey(hWnd, &phEncryptPubKey)) {
		ErrorMsg(TEXT("GetfnKey: GetEncryptPublicKey failed."));
		return (HCRYPTKEY)0;
	}

#ifdef WIN95

	lRv = RegOpenKeyEx(HKEY_CURRENT_USER, 
			 		   TEXT("SOFTWARE\\Microsoft\\Cryptfiler.ini"), 
					   0, 
					   KEY_ALL_ACCESS,
					   &hKey);

#else

	lRv = RegOpenKeyEx(HKEY_CURRENT_USER, 
			 		   TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\IniFileMapping\\Cryptfiler.ini"), 
					   0, 
					   KEY_ALL_ACCESS,
					   &hKey);
#endif

	if (lRv != ERROR_SUCCESS) {

		// not in registry; we must create.

#ifdef WIN95

		lRv = RegCreateKeyEx(HKEY_CURRENT_USER, 
				 			 TEXT("SOFTWARE\\Microsoft\\Cryptfiler.ini"), 
							 0, 
							 NULL, 
							 REG_OPTION_NON_VOLATILE,
							 KEY_ALL_ACCESS,
							 NULL,
							 &hKey,
							 &dwDisposition);
#else
		lRv = RegCreateKeyEx(HKEY_CURRENT_USER, 
				 			 TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\IniFileMapping\\Cryptfiler.ini"), 
							 0, 
							 NULL, 
							 REG_OPTION_NON_VOLATILE,
							 KEY_ALL_ACCESS,
							 NULL,
							 &hKey,
							 &dwDisposition);
#endif
	
		if (lRv != ERROR_SUCCESS) {
			ErrorMsg(TEXT("GetfnKey: RegCreateKeyEx failed."));
			return (HCRYPTKEY)0;
		}

		if (RCRYPT_FAILED(CryptGenKey(hMe, CALG_RC4, CRYPT_EXPORTABLE, &hfnKey))) {
			ErrorMsg(TEXT("GetfnKey: CryptGenKey failed."));
			return (HCRYPTKEY)0;
		} 
		
		//Export the key so that it can be stored in the registry.
		
		if (RCRYPT_FAILED(CryptExportKey(hfnKey, 
						  phEncryptPubKey, 
						  SIMPLEBLOB, 
						  0, 
						  pbFileKeyBlob, 
						  &dwFileBlobLen))) {
			ErrorMsg(TEXT("GetfnKey: CryptExportKey failed."));
			return (HCRYPTKEY)0;
		}

		// Store the key blob in the registry.
		
		if (RegSetValueEx(hKey,
						  TEXT("fnKey"),
						  0,
						  REG_BINARY,
						  pbFileKeyBlob,
						  dwFileBlobLen * sizeof(*pbFileKeyBlob)) != ERROR_SUCCESS) {
					
			ErrorMsg(TEXT("GetfnKey: RegSetValueEx failed."));
			return (HCRYPTKEY)0;
		}
	}	
	else {
		// in registry. We must extract.
		
		dwType = 0;
		dwFileBlobLen = 0;
		dwSize = BUF_SIZE;

		if (RegQueryValueEx(hKey, 
							TEXT("fnKey"),
							NULL, 
							&dwType, 
							pbFileKeyBlob, 
							&dwSize) != ERROR_SUCCESS)
		{
			MessageBox(hWnd, TEXT("GetfnKey: RegQueryValueEx failed querrying pbFileKeyBlob."), NULL, MB_OK);
			return (HCRYPTKEY)0;
		};

		// Read the key blob from the disk into a Buf.
		
		if (!dwSize || (dwSize > BUF_SIZE)) {
			ErrorMsg(TEXT("GetfnKey: dwSize is not in acceptable range."));
			return FALSE;
		}
		
		// Import the key whose blob is contained in the Buf pbDecryptBlob

		dwFileBlobLen = dwSize;

		if (RCRYPT_FAILED(CryptImportKey(hMe, 
						  pbFileKeyBlob, 
						  dwFileBlobLen, 
						  0, 
						  0,
						  &hfnKey))) {

			MessageBox(hWnd, TEXT("GetfnKey: CryptImportKey failed"), NULL, MB_OK);
			return (HCRYPTKEY)0;
		}
	}

	return hfnKey;
}

/************************************************************************\
* Logon()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Creates a dialog box which says "Performing context acquisition."
* Calls CryptAcquireContext.
* Destroys the dialog box
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL Logon(HWND hWnd) {
	HWND			hwndDlg;
	TCHAR			pszName[64];

	pszName[0] = TEXT('\0');
	hwndDlg = CreateDialog(ghModule, TEXT("ACQUIRE_CONTEXT"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		ErrorMsg(TEXT("Logon: CreateDialog failed."));
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptAcquireContext(&hMe, pszName, MS_DEF_PROV, PROV_RSA_FULL, 0))) {
		if (RCRYPT_FAILED(CryptAcquireContext(&hMe, 
						  pszName, 
						  TEXT(MS_DEF_PROV), 
						  PROV_RSA_FULL, 
						  CRYPT_NEWKEYSET))) {
			EndDialog(hwndDlg, FALSE);
			MessageBox(hWnd, TEXT("Logon: CryptAcquireContext failed."), NULL, MB_OK);
			return FALSE;
		}
	}

	EndDialog(hwndDlg, FALSE);
	return TRUE;

return FALSE;
}

/************************************************************************\
* Logoff()
*
* input:
* hWnd - HWND of caller
*
* purpose:
* Calls CryptReleaseContext.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL Logoff(HWND hWnd) 
{
	if (hMe) {
		if (RCRYPT_FAILED(CryptReleaseContext(hMe, 0))) {
        	ErrorMsg(TEXT("Logoff: CryptReleaseContext failed."));
        	return FALSE;
    	}
	}
	else {
		ErrorMsg(TEXT("Logoff: hMe is NULL."));
		return FALSE;
	}

	return TRUE;
}

/************************************************************************\
* GetEncryptPublicKey()
*
* input:
* hWnd - HWND specified by caller
* phEncryptPubKey - address to store key
*
* purpose: calls CryptGetUserKey to obtain the AT_KEYEXCHANGE public
* key.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetEncryptPublicKey(HWND hWnd, HCRYPTKEY *phEncryptPubKey) {
	if (!phEncryptPubKey) {
		ErrorMsg(TEXT("GetEncryptPubKey: phEncryptPubKey is NULL."));
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptGetUserKey(hMe, AT_KEYEXCHANGE, phEncryptPubKey))) {
		if (RCRYPT_FAILED(CryptGenKey(hMe, AT_KEYEXCHANGE, 0, phEncryptPubKey))) {
			ErrorMsg(TEXT("GetEncryptPublicKey: CryptGenKey failed."));
			return TRUE;
		}
	}	
	
	return TRUE;
}

/************************************************************************\
* GetSignaturePublicKey()
*
* input:
* hWnd - HWND specified by caller
* phSignaturePubKey - address to store key
*
* purpose: calls CryptGetUserKey to obtain the AT_SIGNATURE public
* key.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSignaturePublicKey(HWND hWnd, HCRYPTKEY *phSignaturePubKey) {
	if (!phSignaturePubKey) {
		ErrorMsg(TEXT("GetSignaturePublicKey: phSignaturePubKey is NULL."));
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptGetUserKey(hMe, AT_SIGNATURE, phSignaturePubKey))) {
		if (RCRYPT_FAILED(CryptGenKey(hMe, AT_SIGNATURE, 0, phSignaturePubKey))) {
			ErrorMsg(TEXT("GetSignaturePublicKey: CryptGenKey failed."));
			return FALSE;
		}
	}
	
	return TRUE;
}

/************************************************************************\
* MakeHashDirectory()
*
* purpose: 
* Creates the directory \sig on the same drive as the 
* system directory as a hidden directory if
* it doesn't exist and checks the menu item ID_HIDE.
* If it does exist and it is hidden it checks the menu item ID_HIDE.
* If it does exist and it is not hidden it sets the menu item ID_HIDE
* to be unchecked.
*
* returns: 
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL MakeHashDirectory(VOID) {
	DWORD dwFileAttributes;
	TCHAR szSigDir[PATH_SIZE];
	
	GetSigDir(szSigDir);
	
	// Does this directory exist?
	
	if (GetFileAttributes(szSigDir) == 0xFFFFFFFF) {
		// Create the directory
		if (!CreateDirectory(szSigDir, NULL)) {
			ErrorMsg(TEXT("MakeHashDirectory: CreateDirectory failed."));
			return FALSE;
		}
		// Make the directory hidden
		if (!SetFileAttributes(szSigDir, FILE_ATTRIBUTE_HIDDEN)) {
			ErrorMsg(TEXT("Another process is using the \\sig directory."));
			return FALSE;
		}
	}

	dwFileAttributes = GetFileAttributes(szSigDir);

	// Toggle the "Hide Signatures" menu item appropriately.
	
	if (dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
      	CheckMenuItem(ghMenu, ID_HIDE, MF_CHECKED);
    else
    	CheckMenuItem(ghMenu, ID_HIDE, MF_UNCHECKED);
    	 		
    return TRUE;
}

/************************************************************************\
* DeleteHashDirectory()
*
* purpose: 
* Deletes the directory \sig on the same drive as the system directory
* if the \sig directory is empty. This function is called when the
* application terminates.
*
* returns: 
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL DeleteHashDirectory(VOID) {
	TCHAR szSigDir[PATH_SIZE];
	TCHAR szFiles[PATH_SIZE];
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;
	
	GetSigDir(szSigDir);

	lstrcpy(szFiles, szSigDir);
	lstrcat(szFiles, TEXT("\\*"));
	
	// Does this directory exist?
	
	if (GetFileAttributes(szSigDir) == 0xFFFFFFFF) {
		return TRUE;
	}

	hFindFile = FindFirstFile(szFiles, &FindFileData);

	FindNextFile(hFindFile, &FindFileData);

	if (!FindNextFile(hFindFile, &FindFileData)) {
		FindClose(hFindFile);
		SetFileAttributes(szSigDir, FILE_ATTRIBUTE_NORMAL);
		if (!RemoveDirectory(szSigDir)) {
			ErrorMsg(TEXT("DeleteHashDirectory: RemoveDirectory failed."));
			return FALSE;
		}
	}
	else    	 		
    	FindClose(hFindFile);
    
    return TRUE;
}

/************************************************************************\
* HideSignatures()
*
* purpose:
* Hides the directory \sig and its contents
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL HideSignatures(VOID) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;
	TCHAR szFiles[PATH_SIZE];
	TCHAR szFileName[PATH_SIZE];
	TCHAR szSigDir[PATH_SIZE];

	GetSigDir(szSigDir);
	lstrcpy(szFiles, szSigDir);
	lstrcat(szFiles, TEXT("\\*"));

	// hide the directory.
	
	if (!SetFileAttributes(szSigDir, FILE_ATTRIBUTE_HIDDEN)) {
		ErrorMsg(TEXT("Another process is using the \\sig directory."));
		return FALSE;
	}
	
	hFindFile = FindFirstFile(szFiles, &FindFileData);

	if (hFindFile == INVALID_HANDLE_VALUE) {
		SetFileAttributes(szSigDir, FILE_ATTRIBUTE_NORMAL);
		return FALSE;
	}

	// Hide all the signature files.
	
	do {
		lstrcpy(szFileName, szSigDir);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, FindFileData.cFileName);
				
		if (!CFilerIsDirectory(szFileName)) {
			if (!SetFileAttributes(szFileName, FILE_ATTRIBUTE_HIDDEN)) {
				SetFileAttributes(szSigDir, FILE_ATTRIBUTE_NORMAL);
				FindClose(hFindFile);
				ErrorMsg(TEXT("Another process is using a signature file."));
				return FALSE;
			}
		}
	} while (FindNextFile(hFindFile, &FindFileData) 
					|| GetLastError() != ERROR_NO_MORE_FILES);

	FindClose(hFindFile);

	return TRUE;
}	

/************************************************************************\
* ShowSignatures()
*
* purpose:
* "unhides" the directory \sig and its contents
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL ShowSignatures(VOID) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;
	TCHAR szFiles[PATH_SIZE];
	TCHAR szFileName[PATH_SIZE];
	TCHAR szSigDir[PATH_SIZE];

	GetSigDir(szSigDir);
	lstrcpy(szFiles, szSigDir);
	lstrcat(szFiles, TEXT("\\*"));

	// unhide the directory
	
	if (!SetFileAttributes(szSigDir, FILE_ATTRIBUTE_NORMAL)) {
		ErrorMsg(TEXT("Another process is using the \\sig directory."));
		return FALSE;
	}
	
	hFindFile = FindFirstFile(szFiles, &FindFileData);

	if (hFindFile == INVALID_HANDLE_VALUE) {
		SetFileAttributes(szSigDir, FILE_ATTRIBUTE_HIDDEN);
		return FALSE;
	}

	// unhide all the signature files.
	
	do {
		lstrcpy(szFileName, szSigDir);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, FindFileData.cFileName);
				
		if (!CFilerIsDirectory(szFileName)) {
			if (!SetFileAttributes(szFileName, FILE_ATTRIBUTE_NORMAL)) {
				SetFileAttributes(szSigDir, FILE_ATTRIBUTE_HIDDEN);
				FindClose(hFindFile);
				ErrorMsg(TEXT("Another process is using a signature file."));
				return FALSE;
			}
		}
	} while (FindNextFile(hFindFile, &FindFileData) 
					|| GetLastError() != ERROR_NO_MORE_FILES);

	FindClose(hFindFile);

	return TRUE;
}	

/************************************************************************\
* c2r64()
*
* input:
* i - integer value to be converted to a radix64 character
* c - address where character is to be stored
*
* purpose:
* converts an integer between 0 and 63 to a character.
* 0-25 -> A-Z
* 26 - 51 -> a-z
* 52 - 61 -> 0-9
* 62 -> +
* 63 -> _
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL c2r64(INT i, LPTSTR c) {
	if (!c) {
		ErrorMsg(TEXT("c2r64: c is NULL."));
		return FALSE;
	}
	
	if (0 <= i && i <= 25)
		*c = TEXT('A') + i;
	else if (26 <= i && i <= 51)
		*c = TEXT('a') + i - 26;
	else if (52 <= i && i <= 61)
		*c = TEXT('0') + i - 52;
	else if (i == 62)
		*c = TEXT('+');
	else if (i == 63)
		*c = TEXT('_');
	else {
		ErrorMsg(TEXT("c2r64: c is not between 0 and 63."));
		return FALSE;
	}
	return TRUE;
}

/************************************************************************\
* SHAtoRadix64 takes as input a SHA_SIZE-byte hash of the full 
* pathname of a file. It produces a 27-byte "Radix64" 
* representation of the hash, where each byte in the
* "Radix64" representation is between 0 and 2^6.
* It pretends that the SHZ_SIZE + 1st input byte is NULL.
\************************************************************************/

BOOL SHAtoRadix64(LPBYTE pbPathHash, LPTSTR szFileName) {
	INT i, j;
	TCHAR c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	
	if (!pbPathHash) {
		ErrorMsg(TEXT("SHAtoRadix64: pbPathHash is NULL."));
		return FALSE;
	}

	if (!szFileName) {
		ErrorMsg(TEXT("SHAtoRadix64: szFileName is NULL."));
		return FALSE;
	}
	
	for (i = 0, j = 0; i < 18 && j < 24; i += 3, j += 4) {
		c1 = c1 | (((pbPathHash[i + 0] >> 7) & 1) << 5);
		c1 = c1 | (((pbPathHash[i + 0] >> 6) & 1) << 4);
		c1 = c1 | (((pbPathHash[i + 0] >> 5) & 1) << 3);
		c1 = c1 | (((pbPathHash[i + 0] >> 4) & 1) << 2);
		c1 = c1 | (((pbPathHash[i + 0] >> 3) & 1) << 1);
		c1 = c1 | (((pbPathHash[i + 0] >> 2) & 1) << 0);
	
		c2 = c2 | (((pbPathHash[i + 0] >> 1) & 1) << 5);
		c2 = c2 | (((pbPathHash[i + 0] >> 0) & 1) << 4);
		c2 = c2 | (((pbPathHash[i + 1] >> 7) & 1) << 3);
		c2 = c2 | (((pbPathHash[i + 1] >> 6) & 1) << 2);
		c2 = c2 | (((pbPathHash[i + 1] >> 5) & 1) << 1);
		c2 = c2 | (((pbPathHash[i + 1] >> 4) & 1) << 0);

		c3 = c3 | (((pbPathHash[i + 1] >> 3) & 1) << 5);
		c3 = c3 | (((pbPathHash[i + 1] >> 2) & 1) << 4);
		c3 = c3 | (((pbPathHash[i + 1] >> 1) & 1) << 3);
		c3 = c3 | (((pbPathHash[i + 1] >> 0) & 1) << 2);
		c3 = c3 | (((pbPathHash[i + 2] >> 7) & 1) << 1);
		c3 = c3 | (((pbPathHash[i + 2] >> 6) & 1) << 0);

		c4 = c4 | (((pbPathHash[i + 2] >> 5) & 1) << 5);
		c4 = c4 | (((pbPathHash[i + 2] >> 4) & 1) << 4);
		c4 = c4 | (((pbPathHash[i + 2] >> 3) & 1) << 3);
		c4 = c4 | (((pbPathHash[i + 2] >> 2) & 1) << 2);
		c4 = c4 | (((pbPathHash[i + 2] >> 1) & 1) << 1);
		c4 = c4 | (((pbPathHash[i + 2] >> 0) & 1) << 0);

		c2r64(c1, &(szFileName[j + 0]));
		c2r64(c2, &(szFileName[j + 1]));
		c2r64(c3, &(szFileName[j + 2]));
		c2r64(c4, &(szFileName[j + 3]));

		c1 = 0; c2 = 0; c3 = 0; c4 = 0;
	}
	
	c1 = c1 | (((pbPathHash[18] >> 7) & 1) << 5);
	c1 = c1 | (((pbPathHash[18] >> 6) & 1) << 4);
	c1 = c1 | (((pbPathHash[18] >> 5) & 1) << 3);
	c1 = c1 | (((pbPathHash[18] >> 4) & 1) << 2);
	c1 = c1 | (((pbPathHash[18] >> 3) & 1) << 1);
	c1 = c1 | (((pbPathHash[18] >> 2) & 1) << 0);
		
	c2 = c2 | (((pbPathHash[18] >> 1) & 1) << 5);
	c2 = c2 | (((pbPathHash[18] >> 0) & 1) << 4);
	c2 = c2 | (((pbPathHash[19] >> 7) & 1) << 3);
	c2 = c2 | (((pbPathHash[19] >> 6) & 1) << 2);
	c2 = c2 | (((pbPathHash[19] >> 5) & 1) << 1);
	c2 = c2 | (((pbPathHash[19] >> 4) & 1) << 0);

	c3 = c3 | (((pbPathHash[19] >> 3) & 1) << 5);
	c3 = c3 | (((pbPathHash[19] >> 2) & 1) << 4);
	c3 = c3 | (((pbPathHash[19] >> 1) & 1) << 3);
	c3 = c3 | (((pbPathHash[19] >> 0) & 1) << 2);
	c3 = c3 | (((0              >> 7) & 1) << 1);
	c3 = c3 | (((0              >> 6) & 1) << 0);

	c2r64(c1, &(szFileName[24]));
	c2r64(c2, &(szFileName[25]));
	c2r64(c3, &(szFileName[26]));

	szFileName[27] = TEXT('\0');

	return TRUE;
}

/************************************************************************\
* Exit1 and Exit2 close handles, etc. for CFILEREncryptFile,
* CFILERDecryptFile, SignFile, and VerifyFile.
\************************************************************************/

void Exit1(HWND hWnd, LPTSTR message, HANDLE hFile1, HANDLE hFile2) {
	CloseHandle(hFile1);
	CloseHandle(hFile2);
	MessageBox(hWnd, message, NULL, MB_OK);
	return;
}

void Exit2(HWND hWnd, LPTSTR message, HWND hwndDlg, HANDLE hFile1, HANDLE hFile2) {
	CloseHandle(hFile1);
	CloseHandle(hFile2);
	EndDialog(hwndDlg, FALSE);
	MessageBox(hWnd, message, NULL, MB_OK);
	return;
}


/************************************************************************\
* CFILEREncryptFile()
*
* input:
* hWnd - HWND specified by caller
* szFileName - buffer containing full pathname of file to encrypt
*
* Opens a file to encrypt and saves the file in
* encrypted form in the same path as the plaintext file.
* It is saved as a hidden file with a random filename. Its filename is
* encrypted with fnKey and is stored in the header of the file.
* Deletes the plaintext file.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL CFILEREncryptFile(HWND hWnd, LPTSTR szFileName) {
	TCHAR					szEncryptedFileName[PATH_SIZE];	
	TCHAR					szFileName2[PATH_SIZE];
	TCHAR					szRandomName[PATH_SIZE];
	TCHAR					szDirBuf[PATH_SIZE];
	BYTE					pEncryptBuf[2 * BUF_SIZE];
	DWORD					dwNumBytesRead = BUF_SIZE;
	DWORD					dwNumBytesWritten;
	DWORD					dwEncryptLen = BUF_SIZE;
	HWND					hwndDlg;
	HCRYPTKEY				hFileKey;
	HCRYPTKEY				phEncryptPubKey;
	HCRYPTKEY				hfnKey;
	BYTE 					pbFileKeyBlob[BUF_SIZE];
	DWORD 					dwFileBlobLen = BUF_SIZE;
	HANDLE					hFileRead = INVALID_HANDLE_VALUE;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTHASH				hHash;
	DWORD					dwBufLen = HEADER_SIZE * sizeof(TCHAR);
	DWORD					dwDataLen = HEADER_SIZE * sizeof(TCHAR);

	if (!szFileName) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}
	
	SeparatePathName2(szFileName, szDirBuf, szEncryptedFileName);
	
	GetEncryptPublicKey(hWnd, &phEncryptPubKey);
	GenRandomName(szRandomName);
	
	// Generate a key to encrypt this file only if the user
	// selected the password option

	if (!AlgidEncrypt) {
		if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_MD4, 0, 0, &hHash))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptCreateHash failed."), NULL, MB_OK);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)sPass, lstrlen(sPass), 0))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptHashData failed."), NULL, MB_OK);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptDeriveKey(hMe, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hFileKey))) {
			MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptDeriveKey failed."), NULL, MB_OK);
			return FALSE;
		}
	
		CryptDestroyHash(hHash);
	}
	// Generate a key to encrypt this file only (not derived from password).
	else if (RCRYPT_FAILED(CryptGenKey(hMe, AlgidEncrypt, CRYPT_EXPORTABLE, &hFileKey))) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptGenKey failed."), NULL, MB_OK);
		return FALSE;
	} 

	dwFileBlobLen = MAXBLOBLEN;

	//Export the key so that it can be stored on the disk.

	if (RCRYPT_FAILED(CryptExportKey(hFileKey, 
					  phEncryptPubKey, 
					  SIMPLEBLOB, 
					  0, 
					  pbFileKeyBlob, 
					  &dwFileBlobLen))) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CryptExportKey failed."), NULL, MB_OK);
		return FALSE;
	}

   	if (!AlgidEncrypt)
   		dwFileBlobLen = 0;
   		
   	// Open a file to encrypt
	
	hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("CFILEREncryptFile: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}
	      
	lstrcpy(szFileName2, szDirBuf);
	lstrcat(szFileName2, TEXT("\\"));
	lstrcat(szFileName2, szRandomName); 
	
	// Create a hidden .CRP file with a random filename.
	
	hFileWrite = CreateFile(szFileName2, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							0, 
							CREATE_NEW, 
							FILE_ATTRIBUTE_HIDDEN, 
							0);
	
	if (hFileWrite == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("Cannot write to media."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	
	}
	
	// Tell the user that the program is busy encrypting data
	hwndDlg = CreateDialog(ghModule, TEXT("ENCRYPTING"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: CreateDialog failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}
	
	if (RCRYPT_FAILED(CryptEncrypt(hfnKey, 0, TRUE, 0, (LPBYTE)szEncryptedFileName, &dwDataLen, dwBufLen))) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: CryptEncrypt failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}	

	// Write the original file's encrypted name to disk.
	
	if (RCRYPT_FAILED(WriteFile(hFileWrite, 
				      szEncryptedFileName, 
				      HEADER_SIZE * sizeof(*szEncryptedFileName), 
				      &dwNumBytesWritten, 
				      0))) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Write the key blob length to disk.	
	
	if (!WriteFile(hFileWrite, &dwFileBlobLen, sizeof(dwFileBlobLen), &dwNumBytesWritten, 0)) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Write the key blob to disk.
	
	if (dwFileBlobLen && !WriteFile(hFileWrite, 
									pbFileKeyBlob, 
									dwFileBlobLen, 
									&dwNumBytesWritten, 
									0)) {
		Exit2(hWnd, TEXT("CFILEREncryptFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// Encrypt the file by reading small amounts
	// of data from the disk, encrypting those Bufs, and saving the
	// encrypted Bufs to disk. The loop terminates as soon as there is
	// not enough data left on the disk to read a full Buf.

	for ( ; ; ) {

		if (!ReadFile(hFileRead, pEncryptBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: ReadFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
		
		if (dwNumBytesRead != BUF_SIZE)
			break;
			
		if (RCRYPT_FAILED(CryptEncrypt(hFileKey, 0, FALSE, 0, pEncryptBuf, &dwEncryptLen, BUF_SIZE))) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: CryptEncrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pEncryptBuf, dwEncryptLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILEREncryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		dwEncryptLen = BUF_SIZE;
	}

	// Encrypt the last block of data.

	if (0 < dwNumBytesRead && dwNumBytesRead < BUF_SIZE) {
		dwEncryptLen = dwNumBytesRead;

		if (RCRYPT_FAILED(CryptEncrypt(hFileKey, 0, TRUE, 0, pEncryptBuf, &dwEncryptLen, BUF_SIZE))) {
			Exit2(hWnd, TEXT("CryptEncrypt failed."), hwndDlg, hFileRead, hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pEncryptBuf, dwEncryptLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, TEXT("WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
	}

	if (RCRYPT_FAILED(CryptDestroyKey(hFileKey))) {
		Exit2(hWnd, TEXT("CryptDestroyKey failed."), hwndDlg, hFileRead,hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	CloseHandle(hFileRead);
	
	if (!DeleteFile(szFileName)) {
		EndDialog(hwndDlg, FALSE);
		MessageBox(hWnd, TEXT("File cannot be deleted: It is either in use by another process, or it is a system file."), NULL, MB_OK);
		CloseHandle(hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}
	
	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileWrite);
	SetFileAttributes(szFileName2, FILE_ATTRIBUTE_HIDDEN);
	
	return TRUE;
}

/************************************************************************\
* CFILERDecryptFile()
*
* input:
* hWnd - HWND specified by caller
* szFileName - buffer containing full pathname of file to decrypt.
*
* purpose:
* decrypts the file specified by szFileName and stores the file in
* the same directory. Deletes the encrypted file.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL CFILERDecryptFile(HWND hWnd, LPTSTR szFileName)
{
	TCHAR					szFileName2[PATH_SIZE];
	TCHAR					szDecryptedFileName[PATH_SIZE];
	TCHAR					szFile[PATH_SIZE];
	BYTE					pDecryptBuf[2 * BUF_SIZE];
	DWORD					dwNumBytesRead;
	DWORD					dwNumBytesWritten;
	DWORD					dwDecryptDataLen = BUF_SIZE;
	HCRYPTKEY				hFileKey;
	HCRYPTKEY				phEncryptPubKey;
	BYTE 					pbDecryptBlob[BUF_SIZE];
	DWORD 					dwDecryptBlobLen;			
	HWND					hwndDlg;
	HANDLE					hFileRead;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTHASH				hHash;
	DWORD					dwDataLen = HEADER_SIZE * sizeof(TCHAR);
//	BYTE					pHashData[BUF_SIZE];
	DWORD					HashDataLen;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	GetEncryptPublicKey(hWnd, &phEncryptPubKey);
	
	GetDecryptedFileName(hWnd, 
						 szFileName, 
						 szDecryptedFileName, 
						 &hFileRead);

	// Read the key blob length from the disk.	
	
	if (!ReadFile(hFileRead, &dwDecryptBlobLen, sizeof(dwDecryptBlobLen), &dwNumBytesRead, 0)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: ReadFile failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	}

	// Read the key blob from the disk into a Buf.
	
	if (dwDecryptBlobLen && !ReadFile(hFileRead, 
									  pbDecryptBlob, 
									  dwDecryptBlobLen, 
									  &dwNumBytesRead, 
									  0)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: ReadFile failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	} 

	// Import the key whose blob is contained in the Buf pbDecryptBlob
	
	if (dwDecryptBlobLen && !CryptImportKey(hMe, 
											pbDecryptBlob, 
											dwDecryptBlobLen, 
											0, 
											0, 
											&hFileKey)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptImportKey failed."), NULL, MB_OK);
		CloseHandle(hFileRead);
		return FALSE;
	}

	SeparatePathName(szFileName, szFileName2, szFile);
	
	lstrcat(szFileName2, TEXT("\\"));
	lstrcat(szFileName2, szDecryptedFileName);
	
	// Generate a key to decrypt this file if the user
	// selected the password option

	if (!dwDecryptBlobLen) {
		lstrcpy(szPassName, szFileName2);
			
		if (!GetPass(hWnd)) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: GetPass failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		lstrcpy(szPassName, TEXT("\0"));
		
		if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_MD4, 0, 0, &hHash))) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptCreateHash failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)sPass, lstrlen(sPass), 0))) {
			MessageBox(hWnd, TEXT("DecrypttFile: CryptHashData failed."), NULL, MB_OK);
			return FALSE;
		}

		HashDataLen = BUF_SIZE;

		if (RCRYPT_FAILED(CryptDeriveKey(hMe, CALG_RC2, hHash, CRYPT_EXPORTABLE, &hFileKey))) {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CryptDeriveKey failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}

		CryptDestroyHash(hHash);
		
		dwDecryptBlobLen = 0;
	}
	
	// Recreate the plaintext file
	
	hFileWrite = CreateFile(szFileName2, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							0, 
							CREATE_ALWAYS, 
							FILE_ATTRIBUTE_NORMAL, 
							0);

	if (hFileWrite == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILENAME_EXCED_RANGE) {
			TCHAR szEmergencyName[PATH_SIZE];
			TCHAR szEmergencyRandomName[PATH_SIZE];
			TCHAR szDir1[PATH_SIZE];
			TCHAR szFile1[PATH_SIZE];
			SeparatePathName(szFileName, szDir1, szFile1);
			GenRandomName2(szEmergencyRandomName);
			lstrcpy(szEmergencyName, szDir1);
			lstrcat(szEmergencyName, TEXT("\\recovered"));
			lstrcat(szEmergencyName, szEmergencyRandomName);
			hFileWrite = CreateFile(szEmergencyName, GENERIC_READ | GENERIC_WRITE,
										0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if (hFileWrite == INVALID_HANDLE_VALUE) {
				ErrorMsg(TEXT("Could not recover file."));
				return FALSE;
			}
		}
		else {
			MessageBox(hWnd, TEXT("CFILERDecryptFile: CreateFile failed."), NULL, MB_OK);
			CloseHandle(hFileRead);
			return FALSE;
		}
	}
	
	// Create a dialog box to inform the user that the program is busy decrypting data.

	hwndDlg = CreateDialog(ghModule, TEXT("DECRYPTING"), hWnd, CryptDlgProc);

	if (!hwndDlg) {
		Exit2(hWnd, TEXT("CFILERDecryptFile: CreateDialog failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// The following for loop decrypts the data in units of BUF_SIZE
	// at a time and stores the decrypted data into the file hFileWrite.
	// The loop terminates when fewer than BUF_SIZE have been read.

	for ( ; ; ) {
		if (!ReadFile(hFileRead, pDecryptBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: ReadFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (dwNumBytesRead != BUF_SIZE)
			break;
		
		if (RCRYPT_FAILED(CryptDecrypt(hFileKey, 0, FALSE, 0, pDecryptBuf, &dwDecryptDataLen))) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: CryptDecrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pDecryptBuf, dwDecryptDataLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		dwDecryptDataLen = BUF_SIZE;
	}

	// Decrypt the final block of data.
	
	if (0 < dwNumBytesRead && dwNumBytesRead < BUF_SIZE) {
		dwDecryptDataLen = dwNumBytesRead;
		
		if (RCRYPT_FAILED(CryptDecrypt(hFileKey, 0, TRUE, 0, pDecryptBuf, &dwDecryptDataLen))) {

			MessageBox(hWnd, TEXT("GetfnKey: CryptImportKey failed"), NULL, MB_OK);
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: CryptDecrypt failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}

		if (!WriteFile(hFileWrite, pDecryptBuf, dwDecryptDataLen, &dwNumBytesWritten, 0)) {
			Exit2(hWnd, 
					TEXT("CFILERDecryptFile: WriteFile failed."),
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
	}

	if (!CryptDestroyKey(hFileKey)) {
		Exit2(hWnd, 
				TEXT("CFILERDecryptFile: CryptDestroyKey failed."),
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileRead);
	CloseHandle(hFileWrite);
	
	if (!DeleteFile(szFileName)) {
		MessageBox(hWnd, TEXT("CFILERDecryptFile: DeleteFile failed."), NULL, MB_OK);
		DeleteFile(szFileName2);
	}
	
	return TRUE;
}

/************************************************************************\
* SignFile:
* Opens a file, creates a hash value of the file,
* signs that hash value, and stores the result to disk.
\************************************************************************/

BOOL SignFile(HWND hWnd, LPTSTR szFileName) {
	TCHAR 					szFilter1[] = TEXT("Signature Files (*.SGN)\0*.SGN\0");
	TCHAR 					szFilter2[] = TEXT("All Files (*.*)\0*.*\0");
	TCHAR					szFile[PATH_SIZE] = TEXT("\0");
	TCHAR					szFile2[PATH_SIZE] = TEXT("\0");
	TCHAR					szFileTitle[PATH_SIZE];
	TCHAR					szFileName2[PATH_SIZE];
	DWORD					dwNumBytesRead = BUF_SIZE;
	DWORD					dwNumBytesWritten;
	HWND					hwndDlg;
	HANDLE					hFileRead = INVALID_HANDLE_VALUE;
	HANDLE					hFileWrite = INVALID_HANDLE_VALUE;
	HCRYPTKEY				phSignaturePubKey;
	HCRYPTHASH				hHash;
	BYTE					pSignBuf[BUF_SIZE];
	BYTE					pbHash[BUF_SIZE];
	DWORD					dwHashLen;

	GetSignaturePublicKey(hWnd, &phSignaturePubKey);
	
	if (!szFileName) {
		MessageBox(hWnd, TEXT("SignFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	lstrcpy(szFile, TEXT(""));
	lstrcpy(szFileTitle, TEXT(""));
	
	// Open plaintext file
	
	hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("SignFile: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}

	// hash the full pathname of the file. This will be the name of
	// the signature file.
	
	if (!GetSigFileName(szFileName, szFileName2)) {
		MessageBox(hWnd, TEXT("SignFile: GetSigFileName failed."), NULL, MB_OK);
		return FALSE;
	}

	// Create signature file.
	
	if (GetFileAttributes(szFileName2) == 0xFFFFFFFF) {
		
		hFileWrite = CreateFile(szFileName2, 
								GENERIC_READ | GENERIC_WRITE, 
								0, 
								0, 
								CREATE_NEW, 
								FILE_ATTRIBUTE_HIDDEN, 
								0);
				
		if (hFileWrite == INVALID_HANDLE_VALUE) {
			Exit1(hWnd, TEXT("SignFile: CreateFile failed."), hFileRead, hFileWrite);
			return FALSE;
		} 
	}
	else {
		if (MessageBox(hWnd, 
					   TEXT("Delete signature?"), 
					   TEXT("Signature file already exists."), 
					   MB_OKCANCEL) == IDOK) {

			DeleteFile(szFileName2);

			hFileWrite = CreateFile(szFileName2,
									GENERIC_READ | GENERIC_WRITE,
									0,
									0,
									CREATE_NEW,
									FILE_ATTRIBUTE_HIDDEN,
									0);
		
			if (hFileWrite == INVALID_HANDLE_VALUE) {
				Exit1(hWnd, TEXT("SignFile: CreateFile failed."), hFileRead, hFileWrite);
				return FALSE;
			}
		}
		else {
			CloseHandle(hFileRead);
			
			return FALSE;
		}
	}
	
	// Create a dialog box to inform the user that the program is hashing data.
	
	hwndDlg = CreateDialog(ghModule, TEXT("SIGNING"), hWnd, CryptDlgProc);
	
	if (RCRYPT_FAILED(CryptCreateHash(hMe, AlgidSign, 0, 0, &hHash))) {
		Exit2(hWnd, TEXT("SignFile: CryptCreateHash failed."), hwndDlg, hFileRead, hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	// The following for loop hashes the file in BUF_SIZE Bufs at a time.
	
	for (dwNumBytesRead = BUF_SIZE ; dwNumBytesRead == BUF_SIZE; ) {
		if (!ReadFile(hFileRead, pSignBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, 
					TEXT("SignFile: ReadFile failed."), 
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
		else if (RCRYPT_FAILED(CryptHashData(hHash, pSignBuf, dwNumBytesRead, 0))) {
			Exit2(hWnd, 
					TEXT("SignFile: CryptHashData failed."), 
					hwndDlg, 
					hFileRead, 
					hFileWrite);
			DeleteFile(szFileName2);
			return FALSE;
		}
	}

	dwHashLen = BUF_SIZE;

	if (RCRYPT_FAILED(CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbHash, &dwHashLen)))
	{

		MessageBox(hWnd, TEXT("SignFile: CryptSignHash failed"), NULL, MB_OK);

		Exit2(hWnd, 
				TEXT("SignFile: CryptSignHash failed."), 
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	} 

	// Write ALG_ID to disk
	
	if (!WriteFile(hFileWrite, &AlgidSign, sizeof(ALG_ID), &dwNumBytesWritten, 0)) {
		Exit2(hWnd, TEXT("SignFile: WriteFile failed."), hwndDlg, hFileRead, hFileWrite);
		return FALSE;
	}
	
	// Write hash to disk.
	
	if (!WriteFile(hFileWrite, pbHash, dwHashLen, &dwNumBytesWritten, 0)) {
		Exit2(hWnd, 
				TEXT("SignFile: WriteFile failed."), 
				hwndDlg, 
				hFileRead, 
				hFileWrite);
		DeleteFile(szFileName2);
		return FALSE;
	}

	CryptDestroyHash(hHash);
	EndDialog(hwndDlg, FALSE);
	CloseHandle(hFileRead);
	CloseHandle(hFileWrite);
	
	return TRUE;
}

/************************************************************************\
* VerifyFile
* Opens a signature file and the original file.
* Hashes the original file and tries to verify
* the hash.
\************************************************************************/

BOOL VerifyFile(HWND hWnd, LPTSTR szFileName) {
	TCHAR 					szFilter1[] = TEXT("Signature Files (*.SGN)\0*.SGN\0");
	TCHAR 					szFilter2[] = TEXT("All Files (*.*)\0*.*\0");
	TCHAR					szFile[PATH_SIZE] = TEXT("\0");
	TCHAR					szFile2[PATH_SIZE] = TEXT("\0");
	TCHAR					szFileTitle[PATH_SIZE];
	TCHAR					szFileName2[PATH_SIZE];
	DWORD					dwNumBytesRead;
	DWORD					dwNumBytesRead2;
	HWND					hwndDlg;
	HANDLE					hFileOrig = INVALID_HANDLE_VALUE;
	HANDLE					hFileSig = INVALID_HANDLE_VALUE;
	BYTE					pbSig[BUF_SIZE];
	BYTE					pVerifyBuf[BUF_SIZE];
	DWORD					dwSigLen;
	HCRYPTHASH				hHash;
	HCRYPTKEY				phSignaturePubKey;
	ALG_ID 					DiskAlgid;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("VerifyFile: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	GetSignaturePublicKey(hWnd, &phSignaturePubKey);
	
	// hash the full pathname of the file to determine the signature file
	// to open.
	
	if (!GetSigFileName(szFileName, szFileName2)) {
		MessageBox(hWnd, TEXT("VerifyFile: GetSigFileName failed."), NULL, MB_OK);
		return FALSE;
	}

	lstrcpy(szFile, TEXT(""));
	lstrcpy(szFileTitle, TEXT(""));

	// Open the plaintext file to hash it.
	
	hFileOrig = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hFileOrig == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("VerifyFile: CreateFile failed."), NULL, MB_OK);
		CloseHandle(hFileOrig);
		return FALSE;
	}

	// Automatically open the signature file if it 
	// exists in the same directory as the file to be verified.
	// Otherwise, prompt the user to browse the directory tree 
	// for the signature file.
	
	if (GetFileAttributes(szFileName2) != 0xFFFFFFFF) {
		
		hFileSig = CreateFile(szFileName2, 
							  GENERIC_READ, 
							  0, 
							  0, 
							  OPEN_EXISTING, 
							  FILE_ATTRIBUTE_READONLY, 
							  0);
		
		if (hFileSig == INVALID_HANDLE_VALUE) {
			Exit1(hWnd, TEXT("VerifyFile: CreateFile failed."), hFileOrig, hFileSig);
			return FALSE;
		} 
	}
	else {
		Exit1(hWnd, TEXT("Signature file does not exist."), hFileOrig, hFileSig);
		return FALSE;
	} 
	
	// Create a dialog box to tell the user that the program is busy hashing data.

	hwndDlg = CreateDialog(ghModule, TEXT("VERIFYING"), hWnd, CryptDlgProc);
	
	// Read the ALG_ID
	
	if (!ReadFile(hFileSig, &DiskAlgid, sizeof(ALG_ID), &dwNumBytesRead2, 0)) {
		Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}
	
	// Read the hash
	
	if (!ReadFile(hFileSig, pbSig, BUF_SIZE, &dwSigLen, 0)) {
		Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptCreateHash(hMe, DiskAlgid, 0, 0, &hHash))) {
		Exit2(hWnd, TEXT("VerifyFile: CryptCreateHash failed."), hwndDlg, hFileOrig, hFileSig);
		return FALSE;
	}

	// hash the file in BUF_SIZE chunks
	
	for (dwNumBytesRead = BUF_SIZE; dwNumBytesRead == BUF_SIZE; ) {
		if (!ReadFile(hFileOrig, pVerifyBuf, BUF_SIZE, &dwNumBytesRead, 0)) {
			Exit2(hWnd, TEXT("VerifyFile: ReadFile failed."), hwndDlg, hFileOrig, hFileSig);
			return FALSE;
		}
		if (RCRYPT_FAILED(CryptHashData(hHash, pVerifyBuf, dwNumBytesRead, 0))) {
			Exit2(hWnd, 
					TEXT("VerifyFile: CryptHashData failed."), 
					hwndDlg, 
					hFileOrig, 
					hFileSig);
			return FALSE;
		}
	}


	if (RCRYPT_FAILED(CryptVerifySignature(hHash, pbSig, dwSigLen, phSignaturePubKey, 0, 0))) {
		EndDialog(hwndDlg, FALSE);
		MessageBox(hWnd, 
				   TEXT("Could not verify signature."), 
				   TEXT("Result"), 
				   MB_OK | MB_ICONINFORMATION);
		CloseHandle(hFileOrig);
		CloseHandle(hFileSig);
		return TRUE;
	}

	if (RCRYPT_FAILED(CryptDestroyHash(hHash))) {
		Exit2(hWnd, 
				TEXT("Could not destroy hash."), 
				hwndDlg, 
				hFileOrig, 
				hFileSig);
		return FALSE;
	}
	
	EndDialog(hwndDlg, FALSE);
	
	MessageBox(hWnd, 
			   TEXT("Signature verified."), 
			   TEXT("Result"), 
			   MB_OK | MB_ICONINFORMATION);
	CloseHandle(hFileOrig);
	CloseHandle(hFileSig);
	
	return TRUE;
}

/************************************************************************\
* EncryptDir()
*
* in parameters
* hWnd - HWND specified by caller
* szDirName - full path of directory to encrypt
* lpCInfo - instance data for drive child
*
* purpose: 
* Encrypts szDirName and recursively encrypts all of its
* subdirectories. Confirmation is needed for each subdirectory.
* A random directory name is generated, and szDirName is
* renamed and given hidden attributes.
* dirinfo contains the fnKey-encrypted directory name.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL EncryptDir(HWND hWnd, LPTSTR szDirName, LPCINFO lpCInfo) {
	TCHAR				szDirInfo[PATH_SIZE];
	TCHAR				szFileName[PATH_SIZE];
	TCHAR				szEncryptedDirName[PATH_SIZE];
	TCHAR				szRandom[PATH_SIZE];
	TCHAR				szRandomName[PATH_SIZE];
	TCHAR				szDir[PATH_SIZE];
	TCHAR				szFile[PATH_SIZE];
	TCHAR				szMessage[PATH_SIZE];
	TCHAR				szOldDir[PATH_SIZE];
	TCHAR				Buf[PATH_SIZE];
	TCHAR				szDirName2[PATH_SIZE];
	LPTSTR				lpszDirName2;
	HANDLE 				hFileDirInfo;
	HANDLE				hFindFile;
	WIN32_FIND_DATA		FindFileData;
	BOOL				fNextFile;
	DWORD				dwLastError;
	DWORD				dwDataLen = BUF_SIZE;
	DWORD				dwNumBytesWritten;
	LONG				lIndex;
	LONG				lCount;
	HCRYPTKEY			hfnKey;
		
	if (!szDirName) {
		MessageBox(hWnd, TEXT("EncryptDir: szDirName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	if (!lpCInfo) {
		MessageBox(hWnd, TEXT("EncryptDir: lpCInfo is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("EncryptDir: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}

	SeparatePathName2(szDirName, szDir, szEncryptedDirName);
		
	lstrcpy(szMessage, TEXT("\0"));
	wsprintf(szMessage, TEXT("Encrypt the directory %s?\n"), szDirName);

	// ask for confirmation about encrypting the directory
	
	if (MessageBox(hWnd, szMessage, 
				TEXT("Confirmation needed."), MB_OKCANCEL) == IDCANCEL)
		return FALSE;

	lstrcpy(szFileName, szDir);
	lstrcat(szFileName, TEXT("\\"));
	lstrcat(szFileName, szEncryptedDirName);

	if (!szDirName) {
		MessageBox(hWnd, TEXT("EncryptDir: szDirName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	GenRandomName(szRandom);
	
	lstrcpy(szRandomName, szDir);
	lstrcat(szRandomName, TEXT("\\"));
	lstrcat(szRandomName, szRandom);
	lstrcpy(szDirInfo, szFileName);
	lstrcat(szDirInfo, TEXT("\\dirinfo"));

	// Create a file called "dirinfo" in directory about to encrypted.
	// This will contain the original directory name encrypted with fnKey.
	
	hFileDirInfo = CreateFile(szDirInfo, 
							  GENERIC_READ | GENERIC_WRITE, 
							  0, 
							  0, 
							  CREATE_ALWAYS, 
							  FILE_ATTRIBUTE_HIDDEN, 
							  0);
	
	if (hFileDirInfo == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("EncryptDir: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	
	}
		
	// Encrypt the directory name with fnKey.
	
	if (RCRYPT_FAILED(CryptEncrypt(hfnKey, 
					  0, 
					  TRUE, 
					  0, 
					  (LPBYTE)szEncryptedDirName, 
					  &dwDataLen, 
					  HEADER_SIZE * sizeof(*szEncryptedDirName)))) {
		MessageBox(hWnd, TEXT("EncryptDir: CryptEncrypt failed."), NULL, MB_OK);
		CloseHandle(hFileDirInfo);
		return FALSE;
	}	

	// Write the original directory's encrypted name to disk.
	
	if (!WriteFile(hFileDirInfo, 
				   szEncryptedDirName, 
				   HEADER_SIZE * sizeof(*szEncryptedDirName), 
				   &dwNumBytesWritten, 
				   0)) {
		MessageBox(hWnd, TEXT("EncryptDir: WriteFile failed."), NULL, MB_OK);
		CloseHandle(hFileDirInfo);
		return FALSE;
	}
	
	CloseHandle(hFileDirInfo);
	
	SeparatePathName2(szDirName, szDir, szFile);
	
	lstrcpy(szDirName, szDir);
	lstrcat(szDirName, TEXT("\\"));
	lstrcat(szDirName, szFile);
	lstrcpy(szOldDir, szDirName);
	lstrcat(szDirName, TEXT("\\*"));

	if ((hFindFile = FindFirstFile(szDirName, &FindFileData)) 
										== INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("EncryptDir: FindFirstFile failed."), NULL, MB_OK);
		return FALSE;
	}

	// Loop through, calling FindNextFiles until no more files are left.
					
	do {
	
		lstrcpy(szFileName, szDir);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, szFile);
		lstrcat(szFileName, TEXT("\\"));			
		lstrcat(szFileName, FindFileData.cFileName);
		
		// is szFileName encrypted and not .., ., or dirinfo?
		if (!IsEncrypted(szFileName)
		   && lstrcmp(FindFileData.cFileName, TEXT("."))
		   && lstrcmp(FindFileData.cFileName, TEXT(".."))
		   && lstrcmp(FindFileData.cFileName, TEXT("dirinfo"))) {	
			// Is szFileName a directory?
			if (CFilerIsDirectory(szFileName)) {
				// Encrypt the directory szFileName.
				if (!EncryptDir(hWnd, szFileName, lpCInfo)) {
					MessageBox(hWnd, TEXT("EncryptDir: EncryptDir failed."), NULL, MB_OK);
					return FALSE;
				}
			}
			// encrypt the file szFileName.
			else if (!CFILEREncryptFile(hWnd, szFileName)) {
				MessageBox(hWnd, TEXT("EncryptDir: CFILEREncryptFile failed."), NULL, MB_OK);
				return FALSE;
			}
		}
		
		fNextFile = FindNextFile(hFindFile, &FindFileData);

		dwLastError = GetLastError();

	} while (fNextFile || dwLastError != ERROR_NO_MORE_FILES);
					
	FindClose(hFindFile);
	
	lpszDirName2 = szDirName2;
	
	// Collapse the selected directory.

	lIndex = GetLBText(lpCInfo->hDirLB, Buf);
	lCount = GetDirDepth(Buf, &lpszDirName2);
	CollapseDir(lpCInfo, lIndex, lCount);
	
	// rename the directory with a random name.
#ifdef UNICODE
	if (_wrename((const wchar_t *)szOldDir, (const wchar_t *)szRandomName)) {
#else
	if (rename(szOldDir, szRandomName)) {
#endif
		MessageBox(hWnd, TEXT("Another process is using this directory."), NULL, MB_OK);
		return FALSE;
	}
		
	// hide the directory.

	SetFileAttributes(szRandomName, FILE_ATTRIBUTE_HIDDEN);
	
	return TRUE;
}

/************************************************************************\
* GenRandomName()
*
* out parameters
* szRandomName - buffer to receive random filename
*
* purpose:
* Uses the random number generator to generate a random filename with
* a .CRP extension.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GenRandomName(LPTSTR szRandomName) {
	INT i;

	if (!szRandomName) {
		ErrorMsg(TEXT("GenRandomName: szRandomName is NULL."));
		return FALSE;
	}
	
	for (i = 0; i < RANDOM_NAME_LENGTH; i++)
		szRandomName[i] = rand() % 26 + TEXT('a');
	szRandomName[i] = TEXT('\0');

	lstrcat(szRandomName, TEXT(".CRP\0"));

	return TRUE;
}

/************************************************************************\
* GenRandomName2()
*
* out parameters
* szRandomName - buffer to receive random filename
*
* purpose:
* Uses the random number generator to generate a random filename without
* a .CRP extension.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GenRandomName2(LPTSTR szRandomName) {
	INT i;

	if (!szRandomName) {
		ErrorMsg(TEXT("GenRandomName: szRandomName is NULL."));
		return FALSE;
	}
	
	for (i = 0; i < RANDOM_NAME_LENGTH; i++)
		szRandomName[i] = rand() % 26 + TEXT('a');
	szRandomName[i] = TEXT('\0');

	return TRUE;
}

/************************************************************************\
* GetSigFileName()
*
* input
* in parameters:
* szFileName - full path of filename
* out parameters:
* szOutName - buffer containing name of signature file.
*
* purpose:
* obtains the name of the signature file that corresponds to szFileName.
* by hashing it and converting it to ascii.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSigFileName(LPTSTR szFileName, LPTSTR szOutName) {
	HCRYPTHASH hHash;
	BYTE pbHash[BUF_SIZE];
	DWORD dwHashLen;
	TCHAR szFileBuf[PATH_SIZE];
	TCHAR szSigDir[PATH_SIZE];

	if (!szFileName) {	
		ErrorMsg(TEXT("GetSigFileName: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szOutName) {
		ErrorMsg(TEXT("GetSigFileName: szOutName is NULL."));
		return FALSE;
	}
	
 	GetSigDir(szSigDir);
	
	// Hash szFileName.
	
	if (RCRYPT_FAILED(CryptCreateHash(hMe, CALG_SHA, 0, 0, &hHash))) {
		ErrorMsg(TEXT("GetSigFileName: CryptCreateHash failed."));
		return FALSE;
	}

	if (RCRYPT_FAILED(CryptHashData(hHash, (LPBYTE)szFileName, lstrlen(szFileName) * sizeof(*szFileName), 0))) {
		ErrorMsg(TEXT("GetSigFileName: CryptHashData failed."));
		return FALSE;
	}

	dwHashLen = SHA_SIZE;
	
	if (RCRYPT_FAILED(CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))) {
		ErrorMsg(TEXT("GetSigFileName: CryptFinishHash failed."));
		return FALSE;
	}
	
	// Convert the hash to ascii
	
	if (!SHAtoRadix64(pbHash, szFileBuf)) {
		ErrorMsg(TEXT("DrvWndProc: FILLFILE: SHAtoRadix64 failed."));
		return 0;
	}
							
	lstrcpy(szOutName, szSigDir);
	lstrcat(szOutName, TEXT("\\"));
	lstrcat(szOutName, szFileBuf);

	CryptDestroyHash(hHash);
}

/************************************************************************\
* HasSignature()
*
* in parameters
* szFileName - full path of filename in question
* sigtable - pointer to a string table with displayed fields containing
* the filenames of all the files in the \sig directory, which is located
* on the same drive as the system directory.
*
* out parameters
* bHasSignature - flag specifying whether szFileName has a signature
*
* purpose:
* determines whether \sig\szFileName has a signature by calling
* GetSigFileName.
*
* returns
* TRUE if such a file exists
* FALSE otherwise or if unsuccessful
\************************************************************************/

BOOL HasSignature(LPTSTR szFileName, TABLE sigtable, BOOL *bHasSignature) {
	TCHAR szFileName2[PATH_SIZE];
	
	if (!szFileName) {	
		ErrorMsg(TEXT("HasSignature: szFileName is NULL."));
		return FALSE;
	}
	
	if (!bHasSignature) {
		ErrorMsg(TEXT("HasSignature: bHasSignature is NULL."));
		return FALSE;
	}
	
	if (!GetSigFileName(szFileName, szFileName2)) {
		ErrorMsg(TEXT("HasSignature: GetSigFileName failed."));
		return FALSE;
	}

	// Does this file exist?
	
	if (TableFind(sigtable, szFileName2))
		*bHasSignature = TRUE;
	else
		*bHasSignature = FALSE;
}
				
/************************************************************************\
* GetDecryptedFileName()
*
* in parameters
* hWnd - HWND specified by caller
* szFileName - full path of file
* 
* out parameters
* szDecryptedFileName - buffer to hold full decrypted path
* hFileRead - pointer to file handle
*
* purpose:
* reads HEADER_SIZE bytes from szFileName, decrypts it with fnKey, and
* stores the result on szDecryptedFileName, the decrypted file name.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetDecryptedFileName(HWND hWnd, 
						  LPTSTR szFileName, 
						  LPTSTR szDecryptedFileName, 
						  HANDLE *hFileRead) {
	DWORD dwDataLen = HEADER_SIZE * sizeof(TCHAR);
	DWORD dwNumBytesRead;
	TCHAR szDir[PATH_SIZE];
	HCRYPTKEY hfnKey;

	if (!szFileName) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: szFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	if (!szDecryptedFileName) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: szDecryptedFileName is NULL."), NULL, MB_OK);
		return FALSE;
	}

	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}

	// Open encrypted file.
	
	*hFileRead = CreateFile(szFileName, 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   GetFileAttributes(szFileName),
						   0);

	if (*hFileRead == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: CreateFile failed."), NULL, MB_OK);
		return FALSE;
	}
	
	// Read the encrypted filename from the disk.
						
	if (!ReadFile(*hFileRead, 
			 	  szDecryptedFileName, 
			 	  HEADER_SIZE * sizeof(*szDecryptedFileName), 
			 	  &dwNumBytesRead, 
			 	  0))
		return FALSE;
						
	if (dwNumBytesRead != HEADER_SIZE * sizeof(*szDecryptedFileName)) {
		SeparatePathName2(szFileName, szDir, szDecryptedFileName);
		return FALSE;
	}

	// Decrypt the filename.
						
	CryptDecrypt(hfnKey, 0, TRUE, 0, (LPBYTE)szDecryptedFileName, &dwDataLen);

	return TRUE;
}

/************************************************************************\
* GetDecryptedDirName()
*
* in parameters
* hWnd - HWND specified by caller
* szDirectoryName - full path of directory
* bDeldirinfo - flag: TRUE means caller wants dirinfo to be deleted
*
* out parameters
* szDecryptedDirName - buffer to hold full decrypted pathname of
* szDirName
* hFileRead - pointer to file handle
*
* purpose:
* reads HEADER_SIZE bytes from file dirinfo in directory szDirectoryName,
* decrypts it with fnKey, and stores the result in szDecryptedDirName,
* a buffer to hold the decrypted directory name.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetDecryptedDirName(HWND hWnd, 
						   LPTSTR szDirectoryName, 
						   LPTSTR szDecryptedDirName, 
						   BOOL bDeldirinfo,
						   HANDLE *hFileRead) {
	DWORD dwDataLen = HEADER_SIZE * sizeof(TCHAR);
	DWORD dwNumBytesRead;
	TCHAR szDir[PATH_SIZE];
	TCHAR szBuf[PATH_SIZE];
	HCRYPTKEY hfnKey;

	hfnKey = GetfnKey(hWnd);
	
	if (!hfnKey) {
		MessageBox(hWnd, TEXT("GetDecryptedFileName: GetfnKey failed."), NULL, MB_OK);
		return FALSE;
	}

	if (!szDirectoryName) {
		MessageBox(hWnd, TEXT("GetDecryptedDirName: szDirectoryName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	if (!szDecryptedDirName) {
		MessageBox(hWnd, TEXT("GetDecryptedDirNAme: szDecryptedDirName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	lstrcpy(szDir, szDirectoryName);

	if (szDir[lstrlen(szDir) - 1] != TEXT('\\'))
		lstrcat(szDir, TEXT("\\"));

	lstrcat(szDir, TEXT("dirinfo"));

	// open dirinfo in szDirectoryName.
	
	*hFileRead = CreateFile(szDir,
						   	GENERIC_READ,
						   	0,
						   	0,
						   	OPEN_EXISTING,
						   	GetFileAttributes(szDir),
						   	0);

	if (*hFileRead == INVALID_HANDLE_VALUE)
		return FALSE;

	// Read the encrypted filename from the disk.
	
	if (!ReadFile(*hFileRead,
			 	  szDecryptedDirName,
			 	  HEADER_SIZE * sizeof(*szDecryptedDirName),
			 	  &dwNumBytesRead,
			 	  0))
		return FALSE;

	CloseHandle(*hFileRead);

	// Decrypt the directoryname.
	
	CryptDecrypt(hfnKey, 0, TRUE, 0, (LPBYTE)szDecryptedDirName, &dwDataLen);

	// enclose the directory name with brackets.
	
	lstrcpy(szBuf, TEXT("["));
	lstrcat(szBuf, szDecryptedDirName);
	lstrcat(szBuf, TEXT("]"));
	lstrcpy(szDecryptedDirName, szBuf);

	if (bDeldirinfo)
		DeleteFile(szDir);

	return TRUE;
}

/************************************************************************\
* DecryptDir()
*
* in parameters
* hWnd - HWND specified by caller
* szDirName - Full path of directory to be decrypted
* lpCInfo - instance data for drive child
*
* purpose:
* recursively decrypts szDirName and all of its subdirectories.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL DecryptDir(HWND hWnd, LPTSTR szDirName, LPCINFO lpCInfo) {
	INT i, j;
	TCHAR szDir[PATH_SIZE];
	TCHAR szDir2[PATH_SIZE];
	TCHAR szFile[PATH_SIZE];
	TCHAR szBuf2[PATH_SIZE];
	TCHAR Buf[PATH_SIZE];
	TCHAR szDecryptedDirName[PATH_SIZE];
	TCHAR szFileName[PATH_SIZE];
	TCHAR szDirName2[PATH_SIZE];
	LPTSTR lpszDirName2;
	HANDLE hFileRead;
	HANDLE hFindFile;
	WIN32_FIND_DATA FindFileData;
	BOOL fNextFile;
	DWORD dwLastError;
	LONG lIndex, lCount;
	
	if (!szDirName) {
		MessageBox(hWnd, TEXT("DecryptDir: szDirName is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	if (!lpCInfo) {
		MessageBox(hWnd, TEXT("DecryptDir: lpCInfo is NULL."), NULL, MB_OK);
		return FALSE;
	}
	
	GetDecryptedDirName(hWnd, szDirName, szDecryptedDirName, 1, &hFileRead);

	// strip the brackets off szDecryptedDirName.

	if (szDecryptedDirName[0] == TEXT('[')) {
		for (i = 1, j = 0; szDecryptedDirName[i] 
						&& szDecryptedDirName[i] != TEXT(']'); i++, j++)
			szBuf2[j] = szDecryptedDirName[i];
		szBuf2[j] = TEXT('\0');
		lstrcpy(szDecryptedDirName, szBuf2);
	}	

	CloseHandle(hFileRead);

	lpszDirName2 = szDirName2;

	// Collapse the selected directory in the directory listbox.
	
	lIndex = GetLBText(lpCInfo->hDirLB, Buf);
	lCount = GetDirDepth(Buf, &lpszDirName2);
	CollapseDir(lpCInfo, lIndex, lCount);
	
	SeparatePathName2(szDirName, szDir, szFile);
	
	// unhide the directory.
	
	lstrcat(szDir, TEXT("\\"));
	lstrcat(szDir, szDecryptedDirName);
	SetFileAttributes(szDirName, GetFileAttributes(szDirName) ^ FILE_ATTRIBUTE_HIDDEN);
	
	// rename the directory to its original name.

#ifdef UNICODE
	if (_wrename((const wchar_t *)szDirName, (const wchar_t *)szDir)) {
#else
	if (rename(szDirName, szDir)) {
#endif
		MessageBox(hWnd, TEXT("Another process is using this directory."), NULL, MB_OK);
		return FALSE;
	}
	
	lstrcpy(szDir2, szDir);
	lstrcat(szDir2, TEXT("\\*"));
	
	if ((hFindFile = FindFirstFile(szDir2, &FindFileData)) == INVALID_HANDLE_VALUE) {
		MessageBox(hWnd, TEXT("DecryptDir: FindFirstFile failed."), NULL, MB_OK);
		return FALSE;
	}

	// decrypt all the files in the directory, recursing on directories
	
	do {
		lstrcpy(szFileName, szDir);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, FindFileData.cFileName);
		
		// is szFileName encrypted?
		if (IsEncrypted(szFileName)
		   && lstrcmp(FindFileData.cFileName, TEXT("."))
		   && lstrcmp(FindFileData.cFileName, TEXT(".."))) {	
			// is szFileName a directory?
			if (CFilerIsDirectory(szFileName)) {
				// Decrypt the directory szFileName.
				if (!DecryptDir(hWnd, szFileName, lpCInfo)) {
					MessageBox(hWnd, TEXT("DecryptDir: DecryptDir failed."), NULL, MB_OK);
					return FALSE;
				}
			}
			// decrypt the file szFileName.
			else if (!CFILERDecryptFile(hWnd, szFileName)) {
				MessageBox(hWnd, TEXT("DecryptDir: CFILERDecryptFile failed."), NULL, MB_OK);
				return FALSE;
			}
		}
		
		fNextFile = FindNextFile(hFindFile, &FindFileData);

		dwLastError = GetLastError();
		
	} while (fNextFile || dwLastError != ERROR_NO_MORE_FILES);

	FindClose(hFindFile);

	return TRUE;
}

/************************************************************************\
* GetSigDir()
*
* in parameters
* szSigDir - buffer to hold result
*
* purpose: 
* stores in buffer szSigDir the name of the directory containing
* the signatures
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL GetSigDir(LPTSTR szSigDir)
{
	TCHAR szSystemDirectory[PATH_SIZE];

	if (!szSigDir) {
		ErrorMsg(TEXT("GetSigDir: szSigDir is NULL."));
		return FALSE;
	}
		
	// [system directory drive]:\sig -> szSigDir
	
	GetSystemDirectory(szSystemDirectory, PATH_SIZE * sizeof(*szSystemDirectory));
	szSigDir[0] = szSystemDirectory[0];
	szSigDir[1] = TEXT('\0');
	lstrcat(szSigDir, TEXT(":\\sig"));
	
	return TRUE;
}
