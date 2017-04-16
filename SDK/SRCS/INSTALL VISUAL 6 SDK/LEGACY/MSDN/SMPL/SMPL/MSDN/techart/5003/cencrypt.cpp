#include "CEncrypt.h"
#include <stdio.h>



//*******************************************************************************
// temporary
//*******************************************************************************
#include "CryptErr.h"



//*******************************************************************************
// Constructor[s] and Destructor
//*******************************************************************************
CEncrypt::CEncrypt(LPSTR pCryptContainer, LPSTR pCryptProvider, DWORD dwProviderType, DWORD dwFlags)
	{
	BOOL bResult;

	// set last error flag to success value
	m_dwLastError = 0L;

	// set initialization flag
	m_bInitialized = TRUE;

	// get specified context provider
	bResult = ::CryptAcquireContext(
			&this->m_hCryptProvider,
			pCryptContainer,
			pCryptProvider,
			dwProviderType, 
			dwFlags);

	// if cannot do so then error
	if (!bResult)
		{
		this->m_dwLastError = GetLastError();
		this->m_bInitialized = FALSE;
		WhatIsError(TRUE, 0, "CryptAcquireContext Error");
		}
	}

CEncrypt::~CEncrypt()
	{
	// release context provider if one acquired earlier
	if (m_bInitialized)
		{
		::CryptReleaseContext(this->m_hCryptProvider, 0);
		}
	}



//*******************************************************************************
// User Initialization & Destruction
//*******************************************************************************
int CEncrypt::AddUser()
	{
    HCRYPTPROV hProv;
    HCRYPTKEY hKey;
    CHAR szUserName[100];
    DWORD dwUserNameLen = 100;
	int iReturnCode = ENCRYPT_SUCCESS;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

    // Attempt to acquire a handle to the default key container.
    if (!::CryptAcquireContext(
			&hProv,
			NULL,
			MS_DEF_PROV,
			PROV_RSA_FULL,
			0))
		{
		// Some sort of error occured.

		// Create default key container.
		if(!::CryptAcquireContext(
				&hProv,
				NULL,
				MS_DEF_PROV,
				PROV_RSA_FULL,
				CRYPT_NEWKEYSET))
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error Creating key container");
			return(ENCRYPT_CRYPTAPIERROR);
			}

		// Get name of default key container.
		if(!::CryptGetProvParam(
				hProv,
				PP_CONTAINER,
				(BYTE *)szUserName,
				&dwUserNameLen,
				0))
			{
			// Error getting key container name.
			szUserName[0] = 0;
			}
		}

    // Attempt to get handle to signature key.
    if(!::CryptGetUserKey(hProv, AT_SIGNATURE, &hKey))
		{
		if(GetLastError() == NTE_NO_KEY)
			{
			// Create signature key pair.
			if(!::CryptGenKey(hProv,AT_SIGNATURE,0,&hKey))
				{
				this->m_dwLastError = GetLastError();
				WhatIsError(TRUE, 0, "CryptGenKey Error");
				return(ENCRYPT_CRYPTAPIERROR);
				}
			else
				{
				::CryptDestroyKey(hKey);
				}
			}
		else
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "CryptGetUserKey Error");
			return(ENCRYPT_CRYPTAPIERROR);
			}
		}

    // Attempt to get handle to exchange key.
    if(!::CryptGetUserKey(hProv,AT_KEYEXCHANGE,&hKey))
		{
		if(GetLastError()==NTE_NO_KEY)
			{
			// Create key exchange key pair.
			if(!::CryptGenKey(hProv,AT_KEYEXCHANGE,0,&hKey))
				{
				this->m_dwLastError = GetLastError();
				WhatIsError(TRUE, 0, "CryptGenKey Error");
				return(ENCRYPT_CRYPTAPIERROR);
				}
			else
				{
				::CryptDestroyKey(hKey);
				}
			}
		else
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "CryptGetUserKey Error");
			return(ENCRYPT_CRYPTAPIERROR);
			}
		}

    ::CryptReleaseContext(hProv,0);

	return(iReturnCode);
	}

BOOL CEncrypt::RemoveUser()
	{
    HCRYPTPROV hProv;
	int iReturnCode = ENCRYPT_SUCCESS;

    // Attempt to delete key set
    if (!::CryptAcquireContext(
			&hProv,
			NULL,
			MS_DEF_PROV,
			PROV_RSA_FULL,
			CRYPT_DELETEKEYSET))
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error deleting key set");
			iReturnCode = ENCRYPT_CRYPTAPIERROR;
			}

	return(iReturnCode);
	}

//*******************************************************************************
// Encryption & decryption member functions
//*******************************************************************************
DWORD CEncrypt::RequiredBufferSize(DWORD dwBufferSize)
	{
	DWORD dwBufferLen = 0;

	return(dwBufferLen);
	}

int CEncrypt::EncryptBuffer(LPSTR pBuffer, DWORD dwSize, LPSTR pPassword)
	{
	int iReturnCode = ENCRYPT_SUCCESS;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	return(iReturnCode);
	}

int CEncrypt::DecryptBuffer(LPSTR pBuffer, DWORD dwSize, LPSTR pPassword)
	{
	int iReturnCode = ENCRYPT_SUCCESS;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	return(iReturnCode);
	}

int CEncrypt::EncryptFile(LPSTR pInputFile, LPSTR pOutputFile, LPSTR pPassword)
	{
	int iReturnCode = ENCRYPT_SUCCESS;
	FILE *hSource      = NULL;
	FILE *hDestination = NULL;
	HCRYPTKEY hKey     = 0;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	// set last error flag to success value
	this->m_dwLastError = 0L;

	// Open source and destination files
	if (this->OpenSrcAndDstFiles(pInputFile, &hSource, pOutputFile, &hDestination) == ENCRYPT_SUCCESS)
		{
		// see if password was supplied
		if (pPassword == NULL)
			{
			// Create a random session key.
			::CryptGenKey(this->m_hCryptProvider, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey);

			// export key to file
			this->PutKeyBlobToFile(hDestination, hKey);
			}
		else
			{
			// Derive a session key from the hashed password
			hKey = this->GetKeyFromHashedPassword(this->m_hCryptProvider, pPassword);
			}

		// encrypt source file into destionation file
		ProcessSrcAndDstFiles(hKey, FALSE, &hSource, &hDestination);
		}

	// Close files.
	CloseSrcAndDstFiles(&hSource, &hDestination);

	// Destroy session key.
	::CryptDestroyKey(hKey);

	return(iReturnCode);
	}

int CEncrypt::DecryptFile(LPSTR pInputFile, LPSTR pOutputFile, LPSTR pPassword)
	{
	int iReturnCode = ENCRYPT_SUCCESS;
	FILE *hSource      = NULL;
	FILE *hDestination = NULL;
    HCRYPTKEY hKey = 0;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	// set last error flag to success value
	this->m_dwLastError = 0L;

	// Open source and destination files
	if (this->OpenSrcAndDstFiles(pInputFile, &hSource, pOutputFile, &hDestination) == ENCRYPT_SUCCESS)
		{
		// see if password was supplied
		if(pPassword == NULL)
			{
			// Decrypt the file with the saved session key.
			hKey = this->GetKeyBlobFromFile(hSource);
			}
		else
			{
			// Decrypt the file with a session key derived from a password.
			hKey = this->GetKeyFromHashedPassword(this->m_hCryptProvider, pPassword);
			}

		// decrypt source file into destionation file
		ProcessSrcAndDstFiles(hKey, FALSE, &hSource, &hDestination);
		}

    // Close files.
	CloseSrcAndDstFiles(&hSource, &hDestination);

    // Destroy session key.
	::CryptDestroyKey(hKey);

	return(iReturnCode);
	}

	
	
//*******************************************************************************
// Key & Password member functions
//*******************************************************************************
HCRYPTKEY CEncrypt::GetKeyFromHashedPassword(HCRYPTPROV hProv, LPSTR pPassword)
	{
	HCRYPTKEY hKey = (HCRYPTKEY)NULL;
	HCRYPTKEY hHash;

	// Create a hash object.
	if (::CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
		{
		// Hash in the password data.
		if (::CryptHashData(hHash, (PBYTE)pPassword, strlen(pPassword), 0))
			{
			// Derive a session key from the hash object.
			if (!::CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey))
				{
				hKey = (HCRYPTKEY)NULL;
				}
			}
		}

	// Destroy the hash object.
	::CryptDestroyHash(hHash);

	// return hashed key
	return(hKey);
	}



int CEncrypt::ImportKeyBlob(LPSTR pBlobFile)
	{
	int iReturnCode = ENCRYPT_SUCCESS;
	FILE * hFile;

	hFile = fopen(pBlobFile, "rb");
	this->GetKeyBlobFromFile(hFile);
	fclose(hFile);

	return(iReturnCode);
	}

int CEncrypt::ExportKeyBlob(LPSTR pBlobFile)
	{
	int iReturnCode = ENCRYPT_SUCCESS;
	FILE * hFile;
	HCRYPTKEY hKey;

	hFile = fopen(pBlobFile, "wb");
	this->PutKeyBlobToFile(hFile, hKey);
	fclose(hFile);

	return(iReturnCode);
	}

//*******************************************************************************
// Information functions
//*******************************************************************************
BOOL CEncrypt::Statistics()
	{
    BYTE *ptr = NULL;
    DWORD i;
    ALG_ID aiAlgid;
    DWORD dwBits;
    DWORD dwNameLen;
    CHAR szName[100];	      // Often allocated dynamically.
    BYTE pbData[1000];	      // Often allocated dynamically.
    DWORD dwDataLen;
    DWORD dwFlags;
    CHAR *pszAlgType = NULL;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(FALSE);
		}

    // Enumerate the supported algorithms.
    for (i=0; ; i++)
		{
		// Set the CRYPT_FIRST flag the first time through the loop.
		if (i == 0)
			{
			dwFlags = CRYPT_FIRST;
			}
		else
			{
			dwFlags = 0;
			}

		// Retrieve information about an algorithm.
		dwDataLen = 1000;
		if (!::CryptGetProvParam(this->m_hCryptProvider, PP_ENUMALGS, pbData, &dwDataLen, 0))
			{
			if (GetLastError() == ERROR_NO_MORE_ITEMS)
				{
				// Exit the loop.
				break;
				}
			else
				{
				this->m_dwLastError = GetLastError();
				WhatIsError(TRUE, 0, "Reading Algorithm Error");
				return(FALSE);
				}
			}

		// Extract algorithm information from 'pbData' buffer.
		ptr = pbData;
		aiAlgid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		dwNameLen = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		strncpy((LPSTR)szName, (LPSTR)ptr, dwNameLen);

		// Determine algorithm type.
		switch (GET_ALG_CLASS(aiAlgid))
			{
			case ALG_CLASS_DATA_ENCRYPT:
				pszAlgType = "Encrypt  ";
				break;
			case ALG_CLASS_HASH:
				pszAlgType = "Hash     ";
				break;
			case ALG_CLASS_KEY_EXCHANGE:
				pszAlgType = "Exchange ";
				break;
			case ALG_CLASS_SIGNATURE:
				pszAlgType = "Signature";
				break;
			default:
				pszAlgType = "Unknown  ";
				break;
			}

		// Print information about algorithm.
		printf("Name:%-14s Type:%s  Bits:%-4d Algid:%8.8xh\n",
			szName, pszAlgType, dwBits, aiAlgid);
		}

	return(TRUE);
	}



//*******************************************************************************
// Signature member functions
//*******************************************************************************
int CEncrypt::SignFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription)
	{
	FILE *hSourceFile	 = NULL;
	FILE *hSignatureFile = NULL;

	HCRYPTHASH hHash = 0;

	PBYTE pbSignature = NULL;
	DWORD dwSignatureLen;

	PBYTE pbBuffer    = NULL;
	DWORD dwBufferLen;
	DWORD dwCount;

	int iReturnCode = ENCRYPT_SUCCESS;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	//
	// Hash source file.
	//

	// Determine number of bytes to hash at once.
	dwBufferLen = 1000;

	// Allocate memory for 'pbBuffer'.
	pbBuffer = new BYTE [dwBufferLen + 1];
	if (pbBuffer == NULL)
		{
		this->m_dwLastError = ERROR_OUTOFMEMORY;
		WhatIsError(FALSE, this->m_dwLastError, "Error Out of Memory");
		goto error;
		}

	// Open source file.
	if ((hSourceFile = fopen(szSourceFile,"rb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening source file");
		iReturnCode = ENCRYPT_CANNOTOPENINPUTFILE;
		goto error;
		}

	// Create a hash object.
	if (!::CryptCreateHash(this->m_hCryptProvider, CALG_MD5, 0, 0, &hHash))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptCreateHash Error");
		goto error;
		}

	// Hash source file.
	do
		{
		// Read up to 'dwBufferLen' bytes from source file.
		dwCount = fread(pbBuffer, 1, dwBufferLen, hSourceFile);
		if (ferror(hSourceFile))
			{
			iReturnCode = ENCRYPT_RESOURCEERROR;
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error reading Plaintext");
			goto error;
			}

		// Add data to hash object.
		if (!::CryptHashData(hHash, pbBuffer, dwCount, 0))
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "CryptHashData Error");
			goto error;
			}
		} while(!feof(hSourceFile));

	// Close source file.
	fclose(hSourceFile);
	hSourceFile = 0;

	// Free 'pbBuffer' memory.
	delete [] pbBuffer;
	pbBuffer = NULL;


	//
	// Sign hash object.
	//

	// Determine size of signature.
	dwCount = 0;
	if (!::CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSignatureLen))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptSignHash Error");
		goto error;
		}

	// Allocate memory for 'pbSignature'.
	pbSignature = new BYTE [dwSignatureLen + 1];
	if (pbSignature == NULL)
		{
		this->m_dwLastError = ERROR_OUTOFMEMORY;
		WhatIsError(FALSE, this->m_dwLastError, "Error Out of Memory");
		goto error;
		}

	// Sign hash object (with signature key).
	if (!::CryptSignHash(hHash, AT_SIGNATURE, szDescription, 0, pbSignature, &dwSignatureLen))\
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptSignHash Error");
		goto error;
		}


	//
	// Write signature to signature file.
	//

	// Open signature file.
	if ((hSignatureFile = fopen(szSignatureFile,"wb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening signature file");
		iReturnCode = ENCRYPT_CANNOTOPENOUTPUTFILE;
		goto error;
		}

	// Write signature to signature file.
	fwrite(pbSignature, 1, dwSignatureLen, hSignatureFile);
	if (ferror(hSignatureFile))
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error writing signature");
		goto error;
		}

	// Close signature file.
	fclose(hSignatureFile);
	hSignatureFile = 0;

	// Free 'pbSignature' memory.
	delete [] pbSignature;
	pbSignature = NULL;


	// Destroy hash object.
	::CryptDestroyHash(hHash);
	hHash = 0;

	return (iReturnCode);

error:

	//
	// Do cleanup
	//

	// Close files.
	if (hSourceFile)
		fclose(hSourceFile);
	if (hSignatureFile)
		fclose(hSignatureFile);

	// Free memory.
	if (pbSignature)
		delete [] pbSignature;
	if (pbBuffer)
		delete [] pbBuffer;

	// Release crypto handles.
	if (hHash)
		::CryptDestroyHash(hHash);

	return (iReturnCode);
	}

int CEncrypt::VerifyFile(PCHAR szSourceFile, PCHAR szSignatureFile, PCHAR szDescription)
	{
	FILE *hSourceFile	 = NULL;
	FILE *hSignatureFile = NULL;

	HCRYPTHASH hHash = 0;
	HCRYPTKEY hSigPublicKey = 0;

	PBYTE pbSignature = NULL;
	DWORD dwSignatureLen;

	PBYTE pbBuffer = NULL;
	DWORD dwBufferLen;
	DWORD dwCount;

	int iReturnCode = ENCRYPT_SUCCESS;

	// return error if not initialized
	if (!m_bInitialized)
		{
		return(ENCRYPT_NOTINITIALIZED);
		}

	//
	// Hash source file.
	//

	// Determine number of bytes to hash at once.
	dwBufferLen = 1000;

	// Allocate memory for 'pbBuffer'.
	pbBuffer = new BYTE [dwBufferLen + 1];
	if (pbBuffer == NULL)
		{
		this->m_dwLastError = ERROR_OUTOFMEMORY;
		WhatIsError(FALSE, this->m_dwLastError, "Error Out of Memory");
		goto error;
		}

	// Open source file.
	if ((hSourceFile = fopen(szSourceFile,"rb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening source file");
		iReturnCode = ENCRYPT_CANNOTOPENINPUTFILE;
		goto error;
		}

	// Create a hash object.
	if (!::CryptCreateHash(this->m_hCryptProvider, CALG_MD5, 0, 0, &hHash))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptCreateHash Error");
		goto error;
		}

	// Hash source file.
	do
		{
		// Read up to 'dwBufferLen' bytes from source file.
		dwCount = fread(pbBuffer, 1, dwBufferLen, hSourceFile);
		if (ferror(hSourceFile))
			{
			iReturnCode = ENCRYPT_RESOURCEERROR;
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error reading Plaintext");
			goto error;
			}

		// Add data to hash object.
		if (!::CryptHashData(hHash, pbBuffer, dwCount, 0))
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "CryptHashData Error");
			goto error;
			}
		} while (!feof(hSourceFile));

	// Close source file.
	fclose(hSourceFile);
	hSourceFile = 0;

	// Free 'pbBuffer' memory.
	delete [] pbBuffer;
	pbBuffer = NULL;


	//
	// Read in signature file.
	//

	// Determine size of signature.
	dwSignatureLen = 0;
	if (!::CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSignatureLen))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptSignHash Error");
		goto error;
		}

	// Allocate memory for 'pbSignature'.
	pbSignature = new BYTE [dwSignatureLen + 1];
	if (pbSignature == NULL)
		{
		this->m_dwLastError = ERROR_OUTOFMEMORY;
		WhatIsError(FALSE, this->m_dwLastError, "Error Out of Memory");
		goto error;
		}

	// Open signature file.
	if ((hSignatureFile = fopen(szSignatureFile,"rb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening signature file");
		iReturnCode = ENCRYPT_CANNOTOPENINPUTFILE;
		goto error;
		}

	// Read signature data.
	dwCount = fread(pbSignature, 1, dwSignatureLen, hSignatureFile);
	if (ferror(hSignatureFile))
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error reading signature");
		goto error;
		}

	// Close signature file.
	fclose(hSignatureFile);
	hSignatureFile = 0;


	//
	// Verify signature.
	//

	// Get handle to signature key.
	if (!::CryptGetUserKey(this->m_hCryptProvider, AT_SIGNATURE, &hSigPublicKey))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptGetUserKey Error");
		goto error;
		}

	// Verify signature.
	if (!::CryptVerifySignature(hHash, pbSignature, dwSignatureLen, hSigPublicKey, szDescription, 0))
		{
		if (GetLastError() == NTE_BAD_SIGNATURE)
			{
			iReturnCode = ENCRYPT_MISMATCHEDSIGNATURES;
			}
		else
			{
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "CryptVerifySignature Error");
		}
		goto error;
		}

	// Release signature key.
	::CryptDestroyKey(hSigPublicKey);
	hSigPublicKey = 0;

	// Free 'pbSignature' memory.
	delete [] pbSignature;
	pbSignature = NULL;

	// Destroy hash object.
	::CryptDestroyHash(hHash);
	hHash = 0;

	return (iReturnCode);

error:

	//
	// Do cleanup
	//

	// Close files.
	if (hSourceFile)
		fclose(hSourceFile);
	if (hSignatureFile)
		fclose(hSignatureFile);

	// Free memory.
	if (pbSignature)
		delete [] pbSignature;
	if (pbBuffer)
		delete pbBuffer;

	// Release crypto handles.
	if (hHash)
		::CryptDestroyHash(hHash);
	if (hSigPublicKey)
		::CryptDestroyKey(hSigPublicKey);

	return (iReturnCode);
	}

//
// Worker member functions
//
DWORD CEncrypt::IsFailure()
	{
	return(this->m_dwLastError);
	}

DWORD CEncrypt::LastError()
	{
	return(this->m_dwLastError);
	}

int CEncrypt::OpenSrcAndDstFiles(LPSTR pInputFile, FILE ** hSource, LPSTR pOutputFile, FILE ** hDestination)
	{
	if((*hSource = fopen(pInputFile,"rb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening source file");
		return(ENCRYPT_CANNOTOPENINPUTFILE);
	    }

    // Open destination file.
    if((*hDestination = fopen(pOutputFile,"wb")) == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error opening destination file");
		return(ENCRYPT_CANNOTOPENOUTPUTFILE);
		}

	return(ENCRYPT_SUCCESS);
	}

int CEncrypt::ProcessSrcAndDstFiles(HCRYPTKEY hKey, BOOL bEncrypt, FILE ** hSource, FILE ** hDestination)
	{
	PBYTE pbBuffer = NULL;
	DWORD dwBlockLen;
	DWORD dwBufferLen;
	DWORD dwCount;
	int iReturnCode = ENCRYPT_SUCCESS;
	BOOL bLastBlock = FALSE;

	// Determine number of bytes to encrypt at a time. This must be a multiple
	// of ENCRYPT_BLOCK_SIZE.
	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

	// Determine the block size. If a block cipher is used this must have
	// room for an extra block.
	if(ENCRYPT_BLOCK_SIZE > 1)
		{
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
		}
	else
		{
		dwBufferLen = dwBlockLen;
		}

	// Allocate memory.
	pbBuffer = new BYTE [dwBufferLen + 1];
	if (pbBuffer == NULL)
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = ERROR_OUTOFMEMORY;
		WhatIsError(FALSE, this->m_dwLastError, "Error Out of Memory");
		goto done;
		}

	// Encrypt source file and write to Source file.
	do
		{
		// Read up to 'dwBlockLen' bytes from source file.
		dwCount = fread(pbBuffer, 1, dwBlockLen, *hSource);
		if(ferror(*hSource))
			{
			iReturnCode = ENCRYPT_RESOURCEERROR;
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error reading Plaintext");
			goto done;
			}

		// set signal if last block of data
		bLastBlock = (feof(*hSource) ? TRUE : FALSE);

		// encrypt if request, else decrypt
		if (bEncrypt)
			{
			// Encrypt data
			if(!::CryptEncrypt(hKey, 0, bLastBlock, 0, pbBuffer, &dwCount, dwBufferLen))
				{
				iReturnCode = ENCRYPT_CRYPTAPIERROR;
				this->m_dwLastError = GetLastError();
				WhatIsError(TRUE, 0, "CryptEncrypt Error");
				goto done;
				}
			}
		else
			{
			// Decrypt data
			if(!::CryptDecrypt(hKey, 0, bLastBlock, 0, pbBuffer, &dwCount))
				{
				iReturnCode = ENCRYPT_CRYPTAPIERROR;
				this->m_dwLastError = GetLastError();
				WhatIsError(TRUE, 0, "CryptDecrypt Error");
				goto done;
				}
			}

		// Write data to destination file.
		fwrite(pbBuffer, 1, dwCount, *hDestination);
		if(ferror(*hDestination))
			{
			iReturnCode = ENCRYPT_RESOURCEERROR;
			this->m_dwLastError = GetLastError();
			WhatIsError(TRUE, 0, "Error writing Ciphertext");
			goto done;
			}
		} while(!feof(*hSource));

done:
	// free resources
	if(pbBuffer)
		delete [] pbBuffer;

	return(iReturnCode);
	}

int CEncrypt::CloseSrcAndDstFiles(FILE ** hSource, FILE ** hDestination)
	{
    // Close files.
    if(*hSource)
		{
		fclose(*hSource);
		}
	*hSource = (FILE *)NULL;
    if(*hDestination)
		{
		fclose(*hDestination);
		}
	*hDestination = (FILE *)NULL;

	return(ENCRYPT_SUCCESS);
	}

HCRYPTKEY CEncrypt::GetKeyBlobFromFile(FILE * hSource)
	{
    PBYTE pbKeyBlob = NULL;
    DWORD dwKeyBlobLen;
	HCRYPTKEY hKey = (HCRYPTKEY)NULL;

	// Read key blob length from source file and allocate memory.
	fread(&dwKeyBlobLen, sizeof(DWORD), 1, hSource);
	if(ferror(hSource) || feof(hSource))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error reading file header");
		goto done;
		}
	pbKeyBlob = new BYTE [dwKeyBlobLen + 1];
	if (pbKeyBlob == NULL)
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error Out of memory or improperly formatted source file!");
		goto done;
		}

	// Read key blob from source file.
	fread(pbKeyBlob, 1, dwKeyBlobLen, hSource);
	if(ferror(hSource) || feof(hSource))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error reading file header");
		goto done;
		}

	// Import key blob into CSP.
	if(!::CryptImportKey(this->m_hCryptProvider, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey))
		{
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptImportKey Error");
		goto done;
		}

done:
    // Free memory.
    if(pbKeyBlob)
		delete [] pbKeyBlob;

	return(hKey);
	}

int CEncrypt::PutKeyBlobToFile(FILE * hDestination, HCRYPTKEY hKey)
	{
	HCRYPTKEY hXchgKey = 0;
	PBYTE pbKeyBlob = NULL;
	DWORD dwKeyBlobLen;
	int iReturnCode = ENCRYPT_SUCCESS;

	// Get handle to key exchange public key.
	if(!::CryptGetUserKey(this->m_hCryptProvider, AT_KEYEXCHANGE, &hXchgKey))
		{
		iReturnCode = ENCRYPT_CRYPTAPIERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptGetUserKey Error");
		goto done;
		}

	// Determine size of the key blob and allocate memory.
	if(!::CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen))
		{
		iReturnCode = ENCRYPT_CRYPTAPIERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error computing blob length");
		goto done;
		}
	pbKeyBlob = new BYTE [dwKeyBlobLen + 1];
	if (pbKeyBlob == NULL)
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error out of memory");
		goto done;
		}

	// Export session key into a simple key blob.
	if(!::CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen))
		{
		iReturnCode = ENCRYPT_CRYPTAPIERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "CryptExportKey Error");
		goto done;
		}


	// Write size of key blob to destination file.
	fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);
	if(ferror(hDestination))
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error writing header");
		goto done;
		}

	// Write key blob to destination file.
	fwrite(pbKeyBlob, 1, dwKeyBlobLen, hDestination);
	if(ferror(hDestination))
		{
		iReturnCode = ENCRYPT_RESOURCEERROR;
		this->m_dwLastError = GetLastError();
		WhatIsError(TRUE, 0, "Error writing header");
		goto done;
		}

done:
	// Release key exchange key handle.
	::CryptDestroyKey(hXchgKey);

    // Free memory.
    if(pbKeyBlob)
		delete [] pbKeyBlob;

	return(iReturnCode);
	}

