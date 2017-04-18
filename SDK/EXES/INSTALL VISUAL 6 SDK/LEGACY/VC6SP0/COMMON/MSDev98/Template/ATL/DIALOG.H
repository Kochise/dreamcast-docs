// [!HeaderName] : Declaration of the [!ClassName]
[!crlf]

[!if=(FileExists, "FALSE")]
#ifndef __[!UpperShortName]_H_
#define __[!UpperShortName]_H_
[!crlf]
#include "resource.h"       // main symbols
#include <atlhost.h>
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "<atlhost.h>")]
[!endif]
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

class [!ClassName] : 
	public CAxDialogImpl<[!ClassName]>
{
public:
	[!ClassName]()
	{
	}
[!crlf]
	~[!ClassName]()
	{
	}
[!crlf]
	enum { IDD = IDD_[!UpperShortName] };
[!crlf]
BEGIN_MSG_MAP([!ClassName])
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
[!crlf]
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 1;  // Let the system set the focus
	}
[!crlf]
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
[!crlf]
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif //__[!UpperShortName]_H_
[!endif]
