//
// Copyright (C) Microsoft Corporation, 1997.  All rights reserved.
//

// TSSQSEC.h : main header file for the TSSQSEC DLL
//

#ifndef TSSQSEC_H
#define TSSQSEC_H

#ifdef __cplusplus
extern "C"
{
#endif

SCODE WINAPI Login(HANDLE *phUser, LPCTSTR UserName, LPCTSTR Password);
SCODE WINAPI IsPermitted(HANDLE hUser, long Channel, long TuningSpace, DATE Time, DATE *StopTime);
SCODE WINAPI Logout(HANDLE hUser);

#ifdef __cplusplus
}
#endif

#endif // TSSQSEC_H
