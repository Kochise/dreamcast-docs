// --addrlkup.h-----------------------------------------------------------------
// 
//  Header file for address mapping functions.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_ADDRLKUP_H)
#define _ADDRLKUP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//$--HrFindExchangeGlobalAddressList-------------------------------------------------
// Returns the entry ID of the global address list container in the address
// book.
// -----------------------------------------------------------------------------
HRESULT HrFindExchangeGlobalAddressList( // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,        // address book pointer
    OUT ULONG *lpcbeid,             // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);         // pointer to entry ID pointer

//$--HrGWResolveAddress--------------------------------------------------------
// Returns the entry ID for the recipient identified by a given address.
// -----------------------------------------------------------------------------
HRESULT HrGWResolveAddressW(       // RETURNS: return code
    IN LPABCONT lpGalABCont,        // pointer to GAL container
    IN LPCWSTR lpszAddress,         // pointer to proxy address
    OUT BOOL *lpfMapiRecip,         // MAPI recipient
    OUT ULONG *lpcbEntryID,         // count of bytes in entry ID
    OUT LPENTRYID *lppEntryID);     // pointer to entry ID

HRESULT HrGWResolveAddressA(       // RETURNS: return code
    IN LPABCONT lpGalABCont,        // pointer to GAL container
    IN LPCSTR lpszAddress,          // pointer to proxy address
    OUT BOOL *lpfMapiRecip,         // MAPI recipient
    OUT ULONG *lpcbEntryID,         // count of bytes in entry ID
    OUT LPENTRYID *lppEntryID);     // pointer to entry ID

#ifdef UNICODE
#define HrGWResolveAddress HrGWResolveAddressW
#else
#define HrGWResolveAddress HrGWResolveAddressA
#endif

//$--HrGWResolveProxy----------------------------------------------------------
// Returns the address of a specified type for the recipient identified by
// a given entry ID.
// -----------------------------------------------------------------------------
HRESULT HrGWResolveProxyW(         // RETURNS: return code
    IN  LPADRBOOK   lpAdrBook,      // pointer to address book
    IN  ULONG       cbeid,          // count of bytes in the entry ID
    IN  LPENTRYID   lpeid,          // pointer to the entry ID
    IN  LPCWSTR     lpszAddrType,   // pointer to the address type
    OUT BOOL *      lpfMapiRecip,   // MAPI recipient
    OUT LPWSTR *    lppszAddress);  // pointer to the address pointer

HRESULT HrGWResolveProxyA(         // RETURNS: return code
    IN  LPADRBOOK   lpAdrBook,      // pointer to address book
    IN  ULONG       cbeid,          // count of bytes in the entry ID
    IN  LPENTRYID   lpeid,          // pointer to the entry ID
    IN  LPCSTR      lpszAddrType,   // pointer to the address type
    OUT BOOL *      lpfMapiRecip,   // MAPI recipient
    OUT LPSTR *     lppszAddress);  // pointer to the address pointer

#ifdef UNICODE
#define HrGWResolveProxy   HrGWResolveProxyW
#else
#define HrGWResolveProxy   HrGWResolveProxyA
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _ADDRLKUP_H */
