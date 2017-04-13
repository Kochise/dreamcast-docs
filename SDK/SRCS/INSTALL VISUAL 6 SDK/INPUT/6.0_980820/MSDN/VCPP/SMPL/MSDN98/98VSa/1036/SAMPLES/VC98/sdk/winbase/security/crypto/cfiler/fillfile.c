
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// FILLFILE.C

#include "cfiler.h"

extern HANDLE   			ghDrvThread;
extern HWND 	 	 		ghwndDrv;

/********************************************************************************\
* FillFile()
*
* in parameters
* lpCInfo - instance data for drive child
* hwnd - HWND specified by caller
*
* purpose:
* Fills the file listbox with strings constructed from the contents of the 
* directory that is highlighted in the directory listbox.
* This is accomplished by building a file string table with hidden and displayed
* string pairs. The hidden strings are the full pathnames as they exist on the
* disk. The displayed strings are specially formatted strings containing file
* and directory names to be displayed in the owner-draw listbox. The listbox
* knows how to appropriately draw these file and directory names because the
* strings have some special characters at the beginning. Once the string table
* has been constructed, a function called TableSend is called, which generates
* LB_ADDSTRING messages to the listbox, one for each displayed string in the
* table.
*
* returns:
* TRUE if successful
* FALSE if unsuccessful
\********************************************************************************/

BOOL FillFile(LPCINFO lpCInfo, HWND hwnd) {
	BOOL				bHasSignature = FALSE;
    BOOL				fNextFile = TRUE;
	BOOL				fSearchFlag = TRUE;
	DWORD				dwLastError = ERROR_SUCCESS;
	HANDLE				hFindFile;
	HANDLE				hFileRead;
	INT					i;
	TCHAR				szDecryptedName[PATH_SIZE];
	TCHAR				szFileName[PATH_SIZE];
	TCHAR				szFind[PATH_SIZE];
	TCHAR               szFiles[PATH_SIZE];
	TCHAR				szBuf[PATH_SIZE];
	WIN32_FIND_DATA		FindFileData;
	LONG				lIndex;
	TABLE				sigtable;

    if (!lpCInfo) {
    	ErrorMsg(TEXT("FillFile: lpCInfo is NULL."));
    	return FALSE;
    }
    
    if( WaitForSingleObject(lpCInfo->hFileMutex, MUTEX_TIMEOUT) 
                									== WAIT_TIMEOUT) {
    	ErrorMsg(TEXT("FillFile: File LB Mutex Timeout."));
    	return 0;
    }
		     	
	TableFree(lpCInfo->FileTable);

	lpCInfo->FileTable = TableNew();
		       	
	if (!lpCInfo->FileTable) {
		ErrorMsg(TEXT("MM_FILLFILE: TableNew failed."));
		return 0;
	}
		       	            
	SendMessage(lpCInfo->hFileLB, LB_RESETCONTENT, (WPARAM)NULL, (LPARAM)NULL);

    // Put the full pathname of the directory into szFind
    // by accessing the directory string table.
                
    lIndex = SendMessage( lpCInfo->hDirLB, LB_GETCARETINDEX,
              (WPARAM)NULL, (LPARAM)NULL );
                          
	if (!TableGetHidden(lpCInfo->DirTable, lIndex, szFind)) {
		ErrorMsg(TEXT("FillFile: TableGetHidden failed."));
		return 0;
	}
           
	// if szFind has a '\' append a * otherwise append '\*'

	if (szFind[lstrlen(szFind) - 1] == TEXT('\\')) 
		szFind[lstrlen(szFind) - 1] = TEXT('\0');
  				
	lstrcpy(szFiles, szFind);
				
	lstrcat(szFind, TEXT("\\*"));
				
	if ((hFindFile = FindFirstFile(szFind, &FindFileData)) 
															== INVALID_HANDLE_VALUE) {
		ReleaseMutex(lpCInfo->hFileMutex);
		ErrorMsg(TEXT("FillFile: FindFirstFile failed."));
		ReleaseMutex(lpCInfo->hFileMutex);
		return 0;
	}
			
	sigtable = TableNew();
	
	if (!sigtable) {
		ErrorMsg(TEXT("FillFile: TableNew failed."));
		return 0;
	}
	
	BuildSigTable(sigtable);
	
	// Loop through, calling FindNextFiles until no more files are left.
					
	for (i = 0; fNextFile || dwLastError != ERROR_NO_MORE_FILES; i++) {
		lstrcpy(szFileName, szFiles);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, FindFileData.cFileName);
		bHasSignature = FALSE;
						
		// If szFileName is not a directory, check if it has a signature.
					
		if (!CFilerIsDirectory(szFileName))
			HasSignature(szFileName, sigtable, &bHasSignature);
					
		if (IsEncrypted(szFileName)) {
			BOOL fIsValidEncryptedFile = TRUE;
					
			if (!CFilerIsDirectory(szFileName)) {
				if (!GetDecryptedFileName(hwnd, szFileName, szDecryptedName, &hFileRead)) {
					fIsValidEncryptedFile = FALSE;
					lstrcpy(szBuf, TEXT("\0"));
				}
				CloseHandle(hFileRead);
			}
			else
				GetDecryptedDirName(hwnd, szFileName, szDecryptedName, 0, &hFileRead);

			if (fIsValidEncryptedFile) {
				if (!bHasSignature) 
				// '|' indicates to the the owner-draw listbox
				// an encrypted file or directory
				// This is not unwholesome since '|' is not a legal
				// character for a file or directory identifier.
					lstrcpy(szBuf, TEXT("|")); 
				else if (bHasSignature) 
				// '>' indicates an encrypted file that has been signed.
				// This is not unwholesome since '>' is not a legal character
				// for a file or directory identifier.
					lstrcpy(szBuf, TEXT(">")); 
			}				
		
			lstrcat(szBuf, szDecryptedName);
						
			// add to string table.

			if (IsLegalToAdd(FindFileData.cFileName)) {
				 if (!TableAdd(lpCInfo->FileTable, FindFileData.cFileName, szBuf)) {
					ErrorMsg(TEXT("FillFile: TableAdd failed."));
					return FALSE;
				}
			}				
		}
		else {
		// Not encrypted
				
			if (CFilerIsDirectory(szFileName)) {
							
				// For directories, enclose the directory name with brackets 
				// before inserting into string table.
							
				lstrcpy(szBuf, TEXT("["));
				lstrcat(szBuf, FindFileData.cFileName);
				lstrcat(szBuf, TEXT("]"));
							
				// Add directory name to string table.

				if (IsLegalToAdd(FindFileData.cFileName)) {
					if (!TableAdd(lpCInfo->FileTable, szBuf, szBuf)) {
						ErrorMsg(TEXT("FillFile: TableAdd failed."));
						return FALSE;
					}
				}
			}
			else if (!CFilerIsDirectory(szFileName)) {

			// Not a directory and not encrypted

				if (!bHasSignature)
					lstrcpy(szBuf, FindFileData.cFileName);
				else if (bHasSignature) {
				// ';' indicates a signed file. This is
				// not unwholesome since ';' is not a legal
				// character for a filename.
					lstrcpy(szBuf, TEXT(";"));
					lstrcat(szBuf, FindFileData.cFileName);
				}							
				// Add filename to string table.
							
				if (IsLegalToAdd(FindFileData.cFileName)) {
				 	if (!TableAdd(lpCInfo->FileTable, FindFileData.cFileName, szBuf)) {
						ErrorMsg(TEXT("FillFile: TableAdd failed."));
						return FALSE;
					}
				}
			}
		}
			
		fNextFile = FindNextFile(hFindFile, &FindFileData);

		dwLastError = GetLastError();
	}
				
	// sort the file string table on its displayed members
	// using the same string compare routine
	// that the owner-draw listbox uses.
				
	if (!TableSort(lpCInfo->FileTable, CFilerlstrcmp)) {
		ErrorMsg(TEXT("FillFile: selection failed."));
		return 0;
	}
			
	// send all of the displayed members of the file string table
	// to the owner-draw listbox.
	// It does not matter in what order they are sent since the
	// owner-draw listbox will sort them anyway.

	if (GetSize(lpCInfo->FileTable) && !TableSend(lpCInfo->FileTable, lpCInfo->hFileLB)) {
		ErrorMsg(TEXT("FillFile: TableSend failed."));
		return 0;
	}
			
	//
	//  Set selection to first file.
	//
	if (GetSize(lpCInfo->FileTable)) {
		if(SendMessage(lpCInfo->hFileLB, LB_SETSEL, (WPARAM)TRUE, (LPARAM)0) == LB_ERR) {
			ErrorMsg(TEXT("FillFile:  Listbox selection failure."));
			ReleaseMutex( lpCInfo->hFileMutex );
			return 0;
		}
	}

	if (!SetWindowText(lpCInfo->hTextWnd, lpCInfo->CaptionBarText)) {
		ErrorMsg(TEXT("FillFile: SetWindowText failed."));
		return FALSE;
	}

	TableFree(sigtable);

	ReleaseMutex( lpCInfo->hFileMutex );

	FindClose(hFindFile);

	return TRUE;
}

/************************************************************************\
* BuildSigTable()
*
* input:
* sigtable - pointer to an empty string table
*
* purpose:
* Builds a string table with displayed fields containing
* the filenames of all the files in the \sig directory on the
* same drive as the system directory.
*
* returns
* TRUE if successful
* FALSE if unsuccessful
\************************************************************************/

BOOL BuildSigTable(TABLE sigtable)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;
	TCHAR szFiles[PATH_SIZE];
	TCHAR szFileName[PATH_SIZE];
	TCHAR szSystemDirectory[PATH_SIZE];
	TCHAR szSigDir[PATH_SIZE];

	// [system directory drive]:\sig -> szSigDir

	GetSystemDirectory(szSystemDirectory, PATH_SIZE * sizeof(*szSystemDirectory));
	szSigDir[0] = szSystemDirectory[0];
	szSigDir[1] = TEXT('\0');
	lstrcat(szSigDir, TEXT(":\\sig"));
	lstrcpy(szFiles, szSigDir);
	lstrcat(szFiles, TEXT("\\*"));

	hFindFile = FindFirstFile(szFiles, &FindFileData);

	if (hFindFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	// insert all the signature filenames into the table sigtable.
	
	do {
		lstrcpy(szFileName, szSigDir);
		lstrcat(szFileName, TEXT("\\"));
		lstrcat(szFileName, FindFileData.cFileName);
				
		TableInsert(sigtable, TEXT("NULL"), szFileName, 0);
	} while (FindNextFile(hFindFile, &FindFileData) 
					|| GetLastError() != ERROR_NO_MORE_FILES);

	FindClose(hFindFile);
}	

/*************************************************************************************\
* GetLBText()
*
* Gets the text of the currently selected (careted) item in the given
*   listbox.
*
* Returns:  Index of selected item if successful, -1 on failure
\*************************************************************************************/

LONG GetLBText(HWND hActiveLB, PTCHAR szItemBuff)
{
    LONG    lIndex;

    //
    // Retrieve selected (careted) item.
    //
    lIndex = SendMessage( hActiveLB, LB_GETCARETINDEX,
                          (WPARAM)NULL, (LPARAM)NULL );

    if( SendMessage( hActiveLB, LB_GETTEXT, (WPARAM)lIndex,
                     (LPARAM)szItemBuff) == LB_ERR ){
        ErrorMsg(TEXT("LBN_DBLCLK: Text retrieval failure."));
        return(-1);
    }

    return( lIndex );
}

/*************************************************************************************\
* UpdateFileLB()
*
* Updates the file listbox of the drive child given by sending an MM_FILLFILE
*   message to it.
*
*  input:   hwnd    -   Handle of drive child to update file listbox of.
\*************************************************************************************/

VOID UpdateFileLB(HWND hwnd)
{
    LPCINFO lpCInfo;

    lpCInfo = (LPCINFO)GetWindowLong(hwnd, GWL_USERDATA);

	SendMessage(hwnd, WM_COMMAND, (WPARAM)MM_FILLFILE, (LPARAM)0);
}

/*************************************************************************************\
* RunListBoxItem()
*
*  input:   lpCInfo   -   pointer to Drv child's LPCINFO structure
*  			cmd	  -   integer specifying what action to perform on
*						  the file corresponding to the selected 
*						  file listbox text.
*
* purpose:
* 1. Obtains the full pathname of the selected directory or file
* in the file listbox.
* 2. Depending on whether a directory or file has been selected and
* depending on cmd, the appropriate action is taken:
* - CFILEREncryptFile()
* - EncryptDir()
* - CFILERDecryptFile()
* - DecryptDir()
* - SignFile()
* - VerifyFile()
*
* Returns TRUE if successful, FALSE if unsuccessful.
* If a user tries to sign a directory, RunListBoxItem returns FALSE.			
\*************************************************************************************/

BOOL RunListBoxItem(LPCINFO lpCInfo, int cmd)
{
    LONG		lIndex;
	TCHAR		szBuf[PATH_SIZE];
    TCHAR		szFileName[PATH_SIZE];
	TCHAR		szBuf2[PATH_SIZE];
	
    if (!lpCInfo) {
    	ErrorMsg(TEXT("RunListBoxItem: lpCInfo is NULL."));
    	return FALSE;
    }
    
    // get index of selected item in Directory listbox.
    
    lIndex = SendMessage( lpCInfo->hDirLB, LB_GETCARETINDEX,
                          (WPARAM)NULL, (LPARAM)NULL );
                          
	// obtain full pathname of directory corresponding to selected text in
	// directory listbox by accessing the string table for the directory listbox.
	
	if (!TableGetHidden(lpCInfo->DirTable, lIndex, szFileName)) {
		ErrorMsg(TEXT("RunListBoxItem: TableGetHidden failed."));
		return FALSE;
	}
   
   	// append a '\\' to the end of the full pathname if one isn't already there.
   	
   	if (szFileName[lstrlen(szFileName) - 1] != TEXT('\\')) {
   		if (!lstrcat(szFileName, TEXT("\\"))) {
			ErrorMsg(TEXT("RunListBoxItem: lstrcat failed."));
			return FALSE;
		}
  	}  

    //
    // Retrieve selected (careted) item.
    //

    // get index of selected item in the file listbox.
    
    lIndex = GetLBText(lpCInfo->hFileLB, szBuf);

    if (lIndex == LB_ERR) {
		ErrorMsg(TEXT("RunListBoxItem: GetLBText failed."));
        return FALSE;
	}
    
    // get the full pathname of the file corresponding to the selected text
    // in the file listbox by accessing the string table for the 
    // file listbox.
        
   	if (!TableGetHidden(lpCInfo->FileTable, lIndex, szBuf)) {
		ErrorMsg(TEXT("RunListBoxItem: TableGetHidden failed."));
		return FALSE;
	}
	
	if (WaitForSingleObject(ghDrvThread, INFINITE) == WAIT_FAILED) {
		ErrorMsg(TEXT("RunListBoxItem: WaitForSingleObject failed."));
		return FALSE;
	}

	if (lpCInfo->hDirThread 
		&& WaitForSingleObject(lpCInfo->hDirThread, INFINITE) == WAIT_FAILED) {
		ErrorMsg(TEXT("RunListBoxItem: WaitForSingleObject failed."));
		return FALSE;
	}
	
	lstrcpy(szBuf2, szBuf);
	SimplifyFileName(szBuf2, szBuf);
	lstrcat(szFileName, szBuf);
	
	// if szFileName is not encrypted and the user wants to encrypt/decrypt
	if (!IsEncrypted(szFileName) && cmd == ENCRYPT_DECRYPT) {
		// if szFileName is a directory
		if (CFilerIsDirectory(szFileName)) {
			// encrypt the directory
			if (!EncryptDir(ghwndDrv, szFileName, lpCInfo)) {
				ErrorMsg(TEXT("RunListBoxItem: EncryptDir failed."));
				return FALSE;
			}
		}		
		// not a directory
		else {
			// encrypt the file
			if	(!CFILEREncryptFile(ghwndDrv, szFileName)) {
				ErrorMsg(TEXT("RunListBoxItem: CFILEREncryptFile failed."));
				return FALSE;
			}
		}
		UpdateFileLB(ghwndDrv);
    }
	else if (cmd == ENCRYPT_DECRYPT) {
		// if szFileName is a directory
		if (CFilerIsDirectory(szFileName)) {
			// decrypt the directory.
			if (!DecryptDir(ghwndDrv, szFileName, lpCInfo)) {
				ErrorMsg(TEXT("RunListBoxItme: DecryptDir failed."));
				return FALSE;
			}
		}
		else {		
			// not a directory
			if (!CFILERDecryptFile(ghwndDrv, szFileName)) {
	 			ErrorMsg(TEXT("RunListBoxItem: CFILERDecryptFile failed."));
	 			return FALSE;
			}
		}
		UpdateFileLB(ghwndDrv);
	}
	else if (cmd == SIGN) {
		// sign file if szFileName is not a directory
		if (!CFilerIsDirectory(szFileName) && !SignFile(ghwndDrv, szFileName)) {
	 		ErrorMsg(TEXT("RunListBoxItem: SignFile failed."));
	 		return FALSE;
		}
		UpdateFileLB(ghwndDrv);
	}
	else if (cmd == VERIFY) {
		// verify file is szFileName is not a directory.
		if (!CFilerIsDirectory(szFileName) && !VerifyFile(ghwndDrv, szFileName)) {
	 		ErrorMsg(TEXT("RunListBoxItem: VerifyFile failed."));
	 		return FALSE;
		}
		UpdateFileLB(ghwndDrv);
	}

    return TRUE;
}

/*************************************************************************************\
* CFilerIsDirectory()
*
* input - szDirName: In Parameter: Buffer containing full pathname of directory
*
* Purpose: returns TRUE if szDiretory is a directory or a hidden directory,
* FALSE otherwise or if error. 
\*************************************************************************************/

BOOL CFilerIsDirectory(LPTSTR szDirName) {
	DWORD dwFileAttributes;

	if (!szDirName) {
		ErrorMsg(TEXT("CFilerIsDirectory: szDirName is NULL."));
		return FALSE;
	}
	
	dwFileAttributes = GetFileAttributes(szDirName);

	if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;

	if (dwFileAttributes == (FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN))
		return TRUE;

	return FALSE;
}

/*************************************************************************************\
* SeparatePathName()
*
* First parameter (in parameter): szFileName - full path name to be separated
*
* Second parameter (out parameter): szDir - buffer to hold full pathname of directory
*
* Third parameter (out parameter): szFile - buffer to hold filename (not full pathname)
*
* Example: C:\directory\[foo] -> C:\directory + [foo]
\*************************************************************************************/

BOOL SeparatePathName(LPTSTR szFileName, LPTSTR szDir, LPTSTR szFile) {
	INT		i, j, nLen, nFileOffset;

	if (!szFileName) {
		ErrorMsg(TEXT("SeparatePathName: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szDir) {
		ErrorMsg(TEXT("SeparatePathName: szDir is NULL."));
		return FALSE;
	}
	
	if (!szFile) {
		ErrorMsg(TEXT("SeparatePathName: szFile is NULL."));
		return FALSE;
	}
	
	lstrcpy(szDir, TEXT("\0"));
	lstrcpy(szFile, TEXT("\0"));
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 1] == TEXT('\\'))
		for (i = nLen - 1; szFileName[i] != TEXT('\\') && i; i--);
	else
		for (i = nLen; szFileName[i] != TEXT('\\') && i; i--);
	
	nFileOffset = i + 1;
    
    for (i = 0; i < nFileOffset - 1; i++)
    	szDir[i] = szFileName[i];
    szDir[i] = TEXT('\0');
    
    for (j = 0, i++; i < lstrlen(szFileName); i++, j++)
        szFile[j] = szFileName[i];
    szFile[j] = TEXT('\0');  
    
	return TRUE;
}

/*************************************************************************************\
* SeparatePathName2()
*
* First parameter (in parameter): szFileName - full path name to be separated
*
* Second parameter (out parameter): szDir - buffer to hold full pathname of directory
*
* Third parameter (out parameter): szFile - buffer to hold filename (not full pathname)
*
* brackets are stripped from the filename before the filename is inserted into szFile.
*
* C:\directory\[foo] -> C:\directory + foo
\*************************************************************************************/

BOOL SeparatePathName2(LPTSTR szFileName, LPTSTR szDir, LPTSTR szFile) {
	INT		i, j, nLen, nFileOffset;

	if (!szFileName) {
		ErrorMsg(TEXT("SeparatePathName2: szFileName is NULL."));
		return FALSE;
	}
	
	if (!szDir) {
		ErrorMsg(TEXT("SeparatePathName2: szDir is NULL."));
		return FALSE;
	}
	
	if (!szFile) {
		ErrorMsg(TEXT("SeparatePathName2: szFile is NULL."));
		return FALSE;
	}
	
	lstrcpy(szDir, TEXT("\0"));
	lstrcpy(szFile, TEXT("\0"));
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 1] == TEXT('\\'))
		for (i = nLen - 1; szFileName[i] != TEXT('\\') && i; i--);
	else
		for (i = nLen; szFileName[i] != TEXT('\\') && i; i--);
		
	nFileOffset = i + 1;
    
    for (i = 0; i < nFileOffset - 1; i++)
    	szDir[i] = szFileName[i];
    szDir[i] = TEXT('\0');
    
    for (j = 0, i++; i < lstrlen(szFileName); ) {
    	if (szFileName[i] == TEXT('[') || szFileName[i] == TEXT(']'))
			i++;
    	else {
    		szFile[j] = szFileName[i];
    		i++;
			j++;
		}
	}

    szFile[j] = TEXT('\0');  
    
	return TRUE;
}

/*************************************************************************************\
* IsEncrypted()
* 
* input:
*
* szFileName - In parameter: buffer containing filename
*
* If szFileName has a .CRP extension, IsEncrypted() returns TRUE, FALSE otherwise
* or if failure.
\*************************************************************************************/

BOOL IsEncrypted(LPTSTR szFileName) {
	INT nLen;

	if (!szFileName) {
		ErrorMsg(TEXT("IsEncrypted: szFileName is NULL."));
		return FALSE;
	}
	
	nLen = lstrlen(szFileName);

	if (szFileName[nLen - 4] == TEXT('.') &&
  		szFileName[nLen - 3] == TEXT('C') &&
		szFileName[nLen - 2] == TEXT('R') &&
		szFileName[nLen - 1] == TEXT('P'))
		return TRUE;

	return FALSE;
}

/*************************************************************************************\
* IsLegalToAdd()
*
* input
* in parameters
* szFileName - buffer containing filename (not full pathname) of file in question
*
* purpose
* determines whether szFileName is a file or directory that should be added to
* the file listbox string table.
*
* returns
* TRUE if szFileName is legal
* FALSE otherwise
\*************************************************************************************/

BOOL IsLegalToAdd(LPTSTR szFileName)
{
	if (lstrcmp(szFileName, TEXT(".."))
	 && lstrcmp(szFileName, TEXT("."))
	 && lstrcmp(szFileName, TEXT("dirinfo")))
	 	return TRUE;
	
	return FALSE;
}
