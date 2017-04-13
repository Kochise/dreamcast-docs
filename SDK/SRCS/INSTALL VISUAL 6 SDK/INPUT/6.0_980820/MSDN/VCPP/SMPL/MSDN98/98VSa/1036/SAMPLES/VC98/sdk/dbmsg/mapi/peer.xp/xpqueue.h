/*
 -  X P Q U E U E . H
 -
 *  Purpose:
 *      Background transmit queue definitions for Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/* Structures used to build a adrlist from a recipient table. */

/* This is a lot like a ADRLIST except we keep track of the size of
the contained ADRLIST for resizing purposes. */

typedef struct _myadrlist
{
    ULONG cMaxEntries;
    LPADRLIST lpAdrList;
} MYADRLIST, *LPMYADRLIST;

/* Prototype of callback function which can be invoked as part of
operation of the HrBuildAdrList() function. */

typedef HRESULT (*LPMYCALLBACK) (LPXPL lpxpl,
    LPSPropValue lpPropArray,
    LPMESSAGE lpMessage,
    ULONG ulRecipType,
    LPTSTR lpszEmailAddress,
    BOOL FAR * lpfSent);

/* Build one or two ADRLISTs for use by send/receive logic */

HRESULT HrBuildAdrList (LPXPL lpxpl,
    LPSPropValue lpPropArray,
    LPMESSAGE lpMessage,
    LPMAPITABLE lpTable,
    BOOL fSetResponsibility,
    LPMYCALLBACK lpfnCallBack,
    LPMYADRLIST FAR * lppMyAdrListGood,
    LPMYADRLIST FAR * lppMyAdrListBad);

/* Send a single message from inside a restriction. */

HRESULT HrSendOneMessage (LPXPL lpxpl,
    LPSPropValue lpPropArray,
    LPMESSAGE lpMessage,
    ULONG ulRecipType,
    LPTSTR lpszEmailAddress,
    BOOL FAR * lpfSent);

/* Free a MYADRLIST structure */

void FreeMyAdrList (LPXPL lpxpl, LPMYADRLIST lpMyAdrList);
