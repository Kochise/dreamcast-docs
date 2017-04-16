// EdkUtCpp.h-------------------------------------------------------------------
// Declares a class that supplies a list of id's and strings which can 
// be found by ID.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EDKUTCPP_H_
#define _EDKUTCPP_H_

// -----------------------------------------------------------------------------
// Use this structure to create your list.
// -----------------------------------------------------------------------------

typedef struct _IDList
{
    ULONG   ulID;
    LPSTR   pszValue;
} IDList, *PIDList;

// -----------------------------------------------------------------------------

class CIDList
{
public:    
    // CONSTRUCTOR: Use ARRAY_CNT( IDListArray) to pass nCnt.
    CIDList( 
        PIDList pIDList,    // Pointer to array of IDList.
        UINT nCnt);         // Number of items in the list.

    // Find an ID in the pIDList and return it's string.
    const LPSTR Find(   // Returns the string found or a not found message string.
        ULONG ulID);    // ID to search for.

protected:    
    PIDList m_pIDList;        // Contains a ptr to the ID List array.
    UINT    m_nCnt;           // Number of items in the array.
    char    m_chNotFound[30]; // Will contain the last id not found message. The 
                              // largest value will be "(ID: 0x012345678 not found)".
};

// -----------------------------------------------------------------------------

#endif //_EDKUTCPP_H_
