/*****************************************************************************/
/*																			 */
/*	  SCHOOLUI.C -- User interface for School Bus sample program	  		 */
/*																			 */
/*																			 */
/*****************************************************************************/

#include <windows.h>
#include <commctrl.h>
#include <setupx.h>

#define EXPORT __export

#define Not_VxD	  // to get ring-3 dcls
#include <vmm.h>
#define MIDL_PASS  // suppress 32-bit only #pragma pack(push)
#include <configmg.h>

#include "resource.h"

BOOL WINAPI EXPORT StatusDlgProc(HWND, UINT, WPARAM, LPARAM);

///////////////////////////////////////////////////////////////////////////////
// EnumPropPages is the external interface to the Windows Device Installer.
// This is used for reporting the properties of a Telepath device

BOOL WINAPI EXPORT EnumPropPages(LPDEVICE_INFO pdi,
	LPFNADDPROPSHEETPAGE AddPage, LPARAM lParam)
	{	 // EnumPropPages
	PROPSHEETPAGE status; // status property page
	HPROPSHEETPAGE hstatus;

	// Create a property sheet page. The address of the structure gets
	// passed as the lParam in the WM_INITDIALOG message. That's how
	// we communicate the address of the DEVNODE whose properties we're
	// reporting.

	status.dwSize = sizeof(PROPSHEETPAGE);
	status.dwFlags = PSP_USETITLE;
	_asm mov status.hInstance, ds
	status.pszTemplate = MAKEINTRESOURCE(IDD_STATUS);
	status.hIcon = NULL;
	status.pszTitle = "Status";
	status.pfnDlgProc = StatusDlgProc;
	status.lParam = (LPARAM) pdi->dnDevnode;
	status.pfnCallback = NULL;

	hstatus = CreatePropertySheetPage(&status);
	if (!hstatus)
	return TRUE;				// display property sheet even if we fail

	// Call the Device Manager back to add our page to the property sheet

	if (!AddPage(hstatus, lParam))
 		DestroyPropertySheetPage(hstatus);
	return TRUE;
	}							// EnumPropPages

///////////////////////////////////////////////////////////////////////////////
// StatusDlgProc is the dialog procedure for our property page. Its only
// function in this example is to examine the allocated configuration of
// the device and display the assigned Telepathic I/O Channel number

BOOL WINAPI EXPORT StatusDlgProc(HWND hdlg, UINT msg, WPARAM wParam,
	LPARAM lParam)
	{							// StatusDlgProc
	switch (msg)
		{						// process message

	case WM_INITDIALOG:
		{						// WM_INITDIALOG
	
		// These declarations would normally be in a header file that
		// you share between this property page provider and the VxD:
		
		#define ResType_Telepath ((0x10 << 5) | 5)
		
		typedef struct
			{					// telepath resource description
			int allocated;		// allocated channel number
			ULONG requested;	// mask for requested channels
			} TELEPATH_RESOURCE;// telepath resource description
			
		LOG_CONF logconf;
		RES_DES hres;
		DEVNODE devnode = (DEVNODE) ((LPPROPSHEETPAGE) lParam)->lParam;
			
		//Determine which channel got assigned to this device and
		// report it on our property page
			
		if (CM_Get_First_Log_Conf(&logconf, devnode, ALLOC_LOG_CONF) == CR_SUCCESS
			&& CM_Get_Next_Res_Des(&hres, (RES_DES) logconf, ResType_Telepath, NULL, 0) == CR_SUCCESS)
			{					// has telepath channel
			TELEPATH_RESOURCE res;
				
			CM_Get_Res_Des_Data(hres, &res, sizeof(res), 0);
			if (res.allocated >= 0)
				SetDlgItemInt(hdlg, IDC_CHANNEL, res.allocated, FALSE);
			}					// has telepath channel
		}						// WM_INITDIALOG
		
		}						// process message
	return FALSE;
	}							// StatusDlgProc

