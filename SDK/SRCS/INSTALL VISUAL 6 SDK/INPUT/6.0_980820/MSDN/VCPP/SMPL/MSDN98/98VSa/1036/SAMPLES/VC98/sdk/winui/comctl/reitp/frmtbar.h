/*
 *		frmtbar.h
 *
 *		Declarations for a richedit format bar
 *
 */

// Control IDs for the comboboxes. Returned to the user on selections
#define	TBI_Name			21761
#define	TBI_Size			21762
#define	TBI_Color			21763

#define cxBulletIndent	(1440 / 4)

BOOL FInitFormatBarClass(HINSTANCE hinst);
HWND HwndCreateFormatBar(HWND hwndParent, WORD wID, HDC hdc);

#define	FORMATBARCLASSNAME	"REFormatBar"

