// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    dde.c

    This module handles all the DDE support not provided by wrapper.c

*/

#include "stocksrv.h"
#include <stdlib.h>

//
// string names for our own service, topics and items
//

#define SZ_SERVICENAME  "StockSrv"
#define SZ_PRICES       "Prices"
#define SZ_BREAD        "Bread"
#define SZ_MILK         "Milk"
#define SZ_MSFT         "MSFT"

//
// DDE variables
//

BOOL bMilkActive = TRUE;            // TRUE if we supply item info
BOOL bBreadActive = TRUE;           // and FALSE if not. Controlled
BOOL bMSFTActive = TRUE;            // by menu items.


static DWORD dwDDEInst = 0;         // DDE Instance value

static DWORD dwBreadPrice = 250;    // current price
static DWORD dwMilkPrice = 450;
static DWORD dwMSFTPrice = 7000;

static PDDEITEMINFO pBreadInfo;     // Need these for advise requests
static PDDEITEMINFO pMilkInfo;
static PDDEITEMINFO pMSFTInfo;

//
// Format lists
//

WORD MyFormats[] = {
    CF_TEXT,
    NULL};

//
// Local functions
//

HDDEDATA BreadRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA MilkRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA MSFTRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem);


//
// Startup our DDE services
//

void SetupDDE(HINSTANCE hInstance)
{
    //
    // Do the basic initialization
    //

    InitializeDDE(hInstance,
                  SZ_SERVICENAME,
                  &dwDDEInst, 
                  NULL,
                  CBF_FAIL_EXECUTES);

    //
    // Add each system/item pair we support
    //

    AddDDEItem(SZDDESYS_TOPIC, 
               SZDDESYS_ITEM_HELP,
               MyFormats,
               SysHelpRequest,
               NULL);

    //
    // Add each topic/item pair we support
    // Save the return value for making advise requests later
    //

    pBreadInfo = AddDDEItem(SZ_PRICES,
                            SZ_BREAD,
                            MyFormats,
                            BreadRequest,
                            NULL);

    pMilkInfo = AddDDEItem(SZ_PRICES,
                           SZ_MILK,
                           MyFormats,
                           MilkRequest,
                           NULL);

    pMSFTInfo = AddDDEItem(SZ_PRICES,
                           SZ_MSFT,
                           MyFormats,
                           MSFTRequest,
                           NULL);

}

//
// Function to update our DDE Info database every time we 
// get a timer message.  This simulates the data arriving from
// an outside source
//

void UpdateDDEInfo()
{
    if (bMSFTActive) {
        dwMSFTPrice += 132L;
        if (dwMSFTPrice > 10000L) {
            dwMSFTPrice /= 2L;
            Status("Microsoft stock split announced!");
        }
        Status("MSFT: %lu.%lu", dwMSFTPrice/100, dwMSFTPrice%100);
        PostDDEAdvise(pMSFTInfo);
    }
    if (bBreadActive) {
        dwBreadPrice = 250 + (DWORD) (rand() % 100);
        Status("Bread: %lu.%lu", dwBreadPrice/100, dwBreadPrice%100);
        PostDDEAdvise(pBreadInfo);
    }
    if (bMilkActive) {
        dwMilkPrice = 450 + (DWORD) (rand() % 150);
        Status("Milk: %lu.%lu", dwMilkPrice/100, dwMilkPrice%100);
        PostDDEAdvise(pMilkInfo);
    }
}

//
// Return a string in CF_TEXT format
//

HDDEDATA MakeCFText(UINT wFmt, LPSTR lpszStr, HSZ hszItem)
{
    if (wFmt != CF_TEXT) return NULL;

    return DdeCreateDataHandle(dwDDEInst,
                               lpszStr,
                               lstrlen(lpszStr)+1,
                               0,
                               hszItem,
                               CF_TEXT,
                               NULL);
}

//        
// Return data on a topic
//

HDDEDATA BreadRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    char sz[40];
    
    wsprintf(sz, "%ld.%ld", dwBreadPrice / 100L, dwBreadPrice % 100L);
    return MakeCFText(wFmt, sz, hszItem);
}

HDDEDATA MilkRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    char sz[40];
    
    wsprintf(sz, "%ld.%ld", dwMilkPrice / 100L, dwMilkPrice % 100L);
    return MakeCFText(wFmt, sz, hszItem);
}

HDDEDATA MSFTRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    char sz[40];
    
    wsprintf(sz, "%ld.%ld", dwMSFTPrice / 100L, dwMSFTPrice % 100L);
    return MakeCFText(wFmt, sz, hszItem);
}

//
// Return the Help info
//

HDDEDATA SysHelpRequest(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    static char sz[] = "DDE Help for the Stock Price Service.\r\n\t"
        "Request or advise on 'Stocks!<item>' to get the price.\r\n\t";
        "Items are:  Bread, Milk, MSFT.";

    return MakeCFText(wFmt, sz, hszItem);
}

//
// Copy the current state to the clipboard
//

void CopyDDEInfo(HWND hWnd)
{
    HANDLE hMem;
    LPSTR p;


    //
    // Copy the current price info to the clipboard
    // in CF_TEXT format with tabs between the items
    //

    if (OpenClipboard(hWnd)) {

        //
        // Allocate a chunk of global memory big enough
        // for the string we want to pass
        //

        hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, 1024);
        if (hMem) {

            //
            // lock it and get a pointer to it
            //

            p = GlobalLock(hMem);
            if (p) {

                //
                // Empty any existing Clipboard contents
                //

                EmptyClipboard();

                //
                // format the memory buffer with our info.  Use
                // tabs to delimit the items since Excel and others
                // handle this well
                //

                wsprintf(p, 
                         "MSFT\t%lu.%lu\tBread\t%lu.%lu\tMilk\t%lu.%lu",
                         dwMSFTPrice / 100, dwMSFTPrice % 100,
                         dwBreadPrice / 100, dwBreadPrice % 100,
                         dwMilkPrice / 100, dwMilkPrice % 100);

                //
                // Unlock the memory
                //

                GlobalUnlock(hMem);

                //
                // Send the memory block handle to the clipboard
                //

                SetClipboardData(CF_TEXT, hMem);

            } else {

                //
                // Free it up if we couldn't lock it
                // (Just being tidy)

                GlobalFree(hMem);
            }
        }

        CloseClipboard();
    }
}

//
// Respond to a user request to change the active state of an item
//

void ChangeActiveItemStatus(WPARAM wParam)
{
    switch (wParam) {
    case IDM_BREAD:
        bBreadActive = ! bBreadActive;
        if (bBreadActive) {
            pBreadInfo = AddDDEItem(SZ_PRICES,
                                    SZ_BREAD,
                                    MyFormats,
                                    BreadRequest,
                                    NULL);
            Status("Bread item added");
        } else {
            RemoveDDEItem(SZ_PRICES,
                          SZ_BREAD);
            pBreadInfo = NULL;
            Status("Bread item removed");
        }
        break;

    case IDM_MILK:
        bMilkActive = ! bMilkActive;
        if (bMilkActive) {
            pMilkInfo = AddDDEItem(SZ_PRICES,
                                    SZ_MILK,
                                    MyFormats,
                                    MilkRequest,
                                    NULL);
            Status("Milk item added");
        } else {
            RemoveDDEItem(SZ_PRICES,
                          SZ_MILK);
            pMilkInfo = NULL;
            Status("Milk item removed");
        }
        break;

    case IDM_MSFT:
        bMSFTActive = ! bMSFTActive;
        if (bMSFTActive) {
            pMSFTInfo = AddDDEItem(SZ_PRICES,
                                    SZ_MSFT,
                                    MyFormats,
                                    MSFTRequest,
                                    NULL);
            Status("MSFT item added");
        } else {
            RemoveDDEItem(SZ_PRICES,
                          SZ_MSFT);
            pMSFTInfo = NULL;
            Status("MSFT item removed");
        }
        break;

    default:
        break;
    }

    //
    // Just for fun, if there are no active items we blow
    // away the topic too.  This helps test the auto disconnect
    // code that deals with topic removal.
    //

    if (!bBreadActive && !bMilkActive && !bMSFTActive) {
        RemoveDDETopic(SZ_PRICES);
        Status("Prices topic removed");
    }

}
