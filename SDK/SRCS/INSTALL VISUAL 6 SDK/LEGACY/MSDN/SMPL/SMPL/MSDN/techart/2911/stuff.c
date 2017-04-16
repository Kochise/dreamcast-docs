    hwndToolbar = CreateToolbarEx(hwndDlg, TBSTYLE_TOOLTIPS | WS_CHILD | CCS_NORESIZE | CCS_NODIVIDER, // | WS_CLIPSIBLINGS,
        IDC_TOOLBAR, 12, HINST_COMMCTRL, IDB_VIEW_SMALL_COLOR, atbButtons,
        ARRAYSIZE(atbButtons), 0, 0, 0, 0, sizeof(TBBUTTON));

	if (hwndToolbar) {
		::SetWindowPos(hwndToolbar, NULL,
					   rcToolbar.left, rcToolbar.top,
					   rcToolbar.right - rcToolbar.left,
					   rcToolbar.bottom - rcToolbar.top,
					   SWP_NOACTIVATE | SWP_NOZORDER | SWP_SHOWWINDOW);
