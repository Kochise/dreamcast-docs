#ifndef __CENCRYPT__
#define __CENCRYPT__
#include <windows.h>
#include <stdio.h>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#include <wincrypt.h>

#ifdef USE_BLOCK_CIPHER
    // defines for RC2 block cipher
    #define ENCRYPT_ALGORITHM	CALG_RC2
    #define ENCRYPT_BLOCK_SIZE	8
#else
    // defines for RC4 stream cipher
    #define ENCRYPT_ALGORITHM	CALG_RC4
    #define ENCRYPT_BLOCK_SIZE	1
#endif

#define MY_MAX_PASSWORD_SIZE 64

class CEncrypt
	{
	private:
		HCRYPTKEY GetKeyFromHashedPassword(
					HCRYPTPROV hProv,
					LPSTR pPassword);

	protected:
		// class data
		BOOL m_bInitialized;
		HCRYPTPROV m_hCryptProvider;
		DWORD m_dwLastError;
		ALG_ID m_Algoritm_ID;

		// Encrption session data
		HCRYPTKEY m_hKey;
		HCRYPTHASH m_hHash;

		// Worker functions
		int OpenSrcAndDstFiles(
				LPSTR pInputFile, 
				FILE ** hSource, 
				LPSTR pOutputFile, 
				FILE ** hDestination);
		int ProcessSrcAndDstFiles(
				HCRYPTKEY hKey, 
				BOOL bEncrypt, 
				FILE ** hSource, 
				FILE ** hDestination);
		int CloseSrcAndDstFiles(
				FILE ** hSource,
				FILE ** hDestination);
		HCRYPTKEY GetKeyBlobFromFile(
					FILE * hSource);
		int PutKeyBlobToFile(
				FILE * hDestination,
				HCRYPTKEY hKey);


	public:
		// enumerations
		enum
			{
			ENCRYPT_SUCCESS = 0,
			ENCRYPT_NOTINITIALIZED,
			ENCRYPT_RESOURCEERROR,
			ENCRYPT_CRYPTAPIERROR,
			ENCRYPT_MISMATCHEDSIGNATURES,
			ENCRYPT_CANNOTOPENINPUTFILE,
			ENCRYPT_CANNOTOPENOUTPUTFILE,
			};
		// Constructor[s] and Destructor
		CEncrypt(
			LPSTR pCryptContainer = NULL,
			LPSTR pCryptProvider = MS_DEF_PROV,
			DWORD dwProviderType = PROV_RSA_FULL,
			DWORD dwFlags = 0);
		~CEncrypt();

		// User Initialization & Destruction
		int AddUser();
		int RemoveUser();

		// Encryption member functions
		DWORD RequiredBufferSize(
				DWORD dwBufferSize);
		int EncryptBuffer(
				LPSTR pBuffer,
				DWORD dwSize,
				LPSTR pPassword);
		int DecryptBuffer(
				LPSTR pBuffer,
				DWORD dwSize,
				LPSTR pPassword);
		int EncryptFile(
				LPSTR pInputFile,
				LPSTR pOutputFile,
				LPSTR pPassword);
		int DecryptFile(
				LPSTR pInputFile,
				LPSTR pOutputFile,
				LPSTR pPassword);
		int SignFile(
				PCHAR szSourceFile,
				PCHAR szSignatureFile,
				PCHAR szDescription);
		int VerifyFile(
				PCHAR szSourceFile,
				PCHAR szSignatureFile,
				PCHAR szDescription);
		int ImportKeyBlob(LPSTR pBlobFile);
		int ExportKeyBlob(LPSTR pBlobFile);

		// Information functions
		BOOL Statistics();

		// Worker functions
		DWORD IsFailure();
		DWORD LastError();
	};

#endif // #ifndef __CENCRYPT__
