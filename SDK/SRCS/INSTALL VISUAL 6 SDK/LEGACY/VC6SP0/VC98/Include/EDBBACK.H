/*
 *	EDBBACK.H
 *
 *	Microsoft Exchange Information Store
 *	Copyright (C) 1992-1995, Microsoft Corporation
 *	
 *	Contains declarations of additional definitions and interfaces
 *	for the Exchange Online backup Server APIs.
 */

#ifndef	_MDBBACK_
#define	_MDBBACK_

//
//	Useful types.
//

typedef	DWORD ERR;

typedef	LONG HRESULT;

#ifndef	EDBBACK_BUILD
#define	EDBBACK_API	__declspec(dllimport) _stdcall
#else
#define	EDBBACK_API
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#define	BACKUP_WITH_UUID

HRESULT
EDBBACK_API
HrBackupRegisterW(
    UUID *puuidService,
    WCHAR * wszEndpointAnnotation
    );
HRESULT
EDBBACK_API
HrBackupRegisterA(
    UUID *puuidService,
    char * szEndpointAnnotation
    );

#ifdef	UNICODE
#define	HrBackupRegister HrBackupRegisterW
#else
#define	HrBackupRegister HrBackupRegisterA
#endif

HRESULT
EDBBACK_API
HrBackupUnregister(
    );

ERR
EDBBACK_API
ErrRestoreRegisterW(
	WCHAR * wszEndpointAnnotation,
	WCHAR * wszRestoreDll,
	char * szPerformRestore,
	char * szQueryDatabaseLocations
	);

ERR
EDBBACK_API
ErrRestoreRegisterA(
	char * szEndpointAnnotation,
	char * szRestoreDll,
	char * szPerformRestore,
	char * szQueryDatabaseLocations
	);

#ifdef	UNICODE
#define	ErrRestoreRegister ErrRestoreRegisterW
#else
#define	ErrRestoreRegister ErrRestoreRegisterA
#endif

ERR
EDBBACK_API
ErrRestoreUnregisterW(
	WCHAR * szEndpointAnnotation
	);

ERR
EDBBACK_API
ErrRestoreUnregisterA(
	char * szEndpointAnnotation
	);

#ifdef	UNICODE
#define	ErrRestoreUnregister ErrRestoreUnregisterW
#else
#define	ErrRestoreUnregister ErrRestoreUnregisterA
#endif

ERR
EDBBACK_API
ErrRecoverAfterRestoreW(
	WCHAR * szParametersRoot,
	WCHAR * wszAnnotation
	);

ERR
EDBBACK_API
ErrRecoverAfterRestoreA(
	char * szParametersRoot,
	char * szAnnotation
	);

#ifdef	UNICODE
#define	ErrRecoverAfterRestore ErrRecoverAfterRestoreW
#else
#define	ErrRecoverAfterRestore ErrRecoverAfterRestoreA
#endif



#ifdef	__cplusplus
}
#endif

#endif	// _MDBBACK_
