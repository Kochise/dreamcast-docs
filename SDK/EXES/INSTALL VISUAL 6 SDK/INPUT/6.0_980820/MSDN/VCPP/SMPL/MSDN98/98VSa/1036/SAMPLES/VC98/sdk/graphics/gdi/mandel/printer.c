/******************************Module*Header*******************************\
* Module Name: printer.c
*
* Contains functions for enermerating printers
*
* Created: 16-Apr-1992 11:19:00
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* Before printing the bInitPrinter is called for enumerating printers
* and doing the setup for printing
*
* When Mandelbrot Dream exits, bCleanupPrinter is called to free up
* memory
*
* Dependencies:
*
*   (#defines)
*   (#includes)
*
\**************************************************************************/
#include <windows.h>
#include <winspool.h>
#include <drivinit.h>
#include "julia.h"
#include "printer.h"

//
// Globals for printing
//
PPRINTER_INFO_1     gpPrinters       = NULL;
PSZ                *gpszPrinterNames = NULL;
PSZ                *gpszDeviceNames  = NULL;

extern HMENU  hPrinterMenu;
extern INT    giNPrinters;
extern HWND   ghwndMain;

BOOL bInitPrinter(HWND);
BOOL bCleanupPrinter(VOID);


/******************************Public*Routine******************************\
*
* bInitPrinter
*
* Effects: Enumerating printers...
*
* Warnings: Globals alert!!
*
\**************************************************************************/

BOOL bInitPrinter(HWND hwnd) {
    BOOL        bSuccess;
    DWORD       cbPrinters;
    DWORD       cbNeeded, cReturned, j;
    int         i;


    bSuccess = TRUE;
    cbPrinters = 4096L;
    
    if (!(gpPrinters = (PPRINTER_INFO_1)LocalAlloc((LMEM_FIXED | LMEM_ZEROINIT),
                                                  cbPrinters)))
    {
        OutputDebugString( "InitPrint: LocalAlloc for gpPrinters failed.");
        return (FALSE);
    }

    if (!EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 1, (LPBYTE)gpPrinters,
                      cbPrinters, &cbNeeded, &cReturned))
    {
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) 
        {
            LocalFree((LOCALHANDLE)gpPrinters);
            gpPrinters = (PPRINTER_INFO_1)LocalAlloc((LMEM_FIXED | LMEM_ZEROINIT),
                                               cbNeeded);
            cbPrinters = cbNeeded;

            if (!EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL, 1, (LPBYTE)gpPrinters,
                              cbPrinters, &cbNeeded, &cReturned))
            {
                MessageBox(ghwndMain, 
					       GetStringRes (IDS_ERR_CANT_ENUM_PRINTERS),
					       NULL, MB_OK);
                return (FALSE);
            }

        } 
        else 
        {
            MessageBox(ghwndMain, 
				       GetStringRes (IDS_ERR_CANT_ENUM_PRINTERS),
					   NULL, MB_OK);
            return (FALSE);
        }
    }

    // allocate some memory.

    gpszPrinterNames = (PSZ *)LocalAlloc((LMEM_FIXED | LMEM_ZEROINIT),
                                        cReturned * (DWORD)sizeof(PSZ));

    gpszDeviceNames = (PSZ *)LocalAlloc((LMEM_FIXED | LMEM_ZEROINIT),
                                        cReturned * (DWORD)sizeof(PSZ));

    if (giNPrinters != 0) {
        for (i = 0; i < giNPrinters; i++) {
            RemoveMenu(hPrinterMenu, 3, MF_BYPOSITION);
        }
        giNPrinters = 0;
    }

    // insert each printer name into the menu.

    j = giNPrinters = cReturned;
    for (i = 0; i < (INT) cReturned; i++)
    {
        // insert into menu from bottom up.

        j--;        
        InsertMenu(hPrinterMenu, 4, MF_BYCOMMAND | MF_STRING,
                   MM_PRINTER + i, (LPSTR)gpPrinters[j].pName);

        // save a list of printer names, so we can associate them
        // with their menu indices later.

        gpszPrinterNames[i] = gpPrinters[j].pName;
        gpszDeviceNames[i] = gpPrinters[j].pDescription;
    }
#if 0
    //
    // Use this if this is called in the MDI child instead
    //
    DrawMenuBar(GetParent(GetParent(hwnd)));
#endif
    //
    // Use this instead if this is called in InitializeApp
    //
    DrawMenuBar(hwnd);
    return (bSuccess);
}




/******************************Public*Routine******************************\
*
* bCleanupPrinter
*
* Effects:  Local freeing
*
* Warnings: globals!!!
*
\**************************************************************************/

BOOL bCleanupPrinter(VOID)
{
    if (gpPrinters != NULL)
        LocalFree((LOCALHANDLE)gpPrinters);
    if (gpszPrinterNames != NULL)
        LocalFree((LOCALHANDLE)gpszPrinterNames);
    if (gpszDeviceNames  != NULL)
        LocalFree((LOCALHANDLE)gpszDeviceNames);

    return TRUE;
}
