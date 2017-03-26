'Selfboot Inducer v4 by burnerO 061804
'Modified by [big_fury]SiZiOUS 17 nov 06
' How to compile : Use BCX compiler

Global hInstance As HINSTANCE

'Configuration
Global useJoliet As Boolean 'joliet is enabled ?
Global useRock As Boolean 'Rock ridge is enabled ?
Global temporaryDir As String 'directory for temporary ISO and/or CDI
Global insertLogo As Boolean 'user wanna insert a logo in the IP.BIN ?

'===========================================================================================
' PROGRAM ENTRY POINT
'===========================================================================================

Const IDM_ABOUT = 1

Function WinMain()	
	Local Wc As WNDCLASS
	Local Msg As MSG
	Local hMenu As HWND
	
	'Go to the CONFIGURATION SECTION (at the bottom) to see what's it
	LoadConfiguration()
	
	'this's a global variable for the whole program
	hInstance = hInst
	
	'init the window
	Wc.style = CS_HREDRAW Or CS_VREDRAW
	Wc.lpfnWndProc = WndProc 'the events handler for Selfboot Inducer
	Wc.cbClsExtra = 0
	Wc.cbWndExtra = 0
	Wc.hInstance = hInst
	Wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(1100))
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW)
	Wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1)
	Wc.lpszMenuName = NULL
	Wc.lpszClassName = "Sbi"
	RegisterClass(&Wc)
	
	FormLoad(hInst)
	
	'Set the hints for buttons
	ToolTip_SetToolTip(Button4, "Extract selected SBI packages.")
	ToolTip_SetToolTip(Button5, "Generates a Padus DiscJuggler v4.0 image.")
	ToolTip_SetToolTip(Button6, "Generates a Nero Burning Rom image.")
	ToolTip_SetToolTip(Button8, "Burn a DreamInducer CD-ROM now with embedded CDRecord.")
	ToolTip_SetToolTip(Button9, "Reset DreamInducer compilation.")
	ToolTip_SetToolTip(btnConfig, "Configure Selfboot Inducer.")
	
	'add a "About" item to the system menu
	hMenu = GetSystemMenu(Form1, FALSE)
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL)
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, "&About...")
	
	'this is the main loop for Selfboot Inducer
	While GetMessage(&Msg, NULL, 0, 0)
	 If Not IsWindow(GetActiveWindow()) Or _
	  Not IsDialogMessage(GetActiveWindow(), &Msg) Then
	  TranslateMessage(&Msg)
	  DispatchMessage(&Msg)
	 End If
	Wend
	
	Function = Msg.wParam
End Function

'===========================================================================================
' EVENTS HANDLER
'===========================================================================================

Callback Function WndProc()

Select Case Msg
'===========================================================================================
CASE WM_SYSCOMMAND
'===========================================================================================
	If LOWORD(wParam) = IDM_ABOUT Then
		DialogBox(hInstance, MAKEINTRESOURCE(500), Form1, AboutBox) 'show the aboutbox
	End If
'===========================================================================================
Case WM_COMMAND
'===========================================================================================
If Cbctl = ID_btnConfig Then
	DialogBox (hInstance, MAKEINTRESOURCE(400), Form1, ConfigBox) 'ConfigBox procedure in the "Configuration Section"
End If
'===========================================================================================
If Cbctl = ID_Button1 And Trim$(List$) <> "" Then
Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbx"
Rename Temp$, Left$(Temp$, Len(Temp$) - 4) & ".sbi"
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 SendMessage(List1, LB_DELETESTRING, 0, "")
 Temp$ = FindNext$
Wend
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 If Lcase$(Right$(Temp$, 3)) = "sbi" Then
  Temp$ = "[+] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 If Lcase$(Right$(Temp$, 3)) = "sbx" Then
  Temp$ = "[_] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 Temp$ = FindNext$
Wend
End If
'===========================================================================================
If Cbctl = ID_Button2 And Trim$(List$) <> "" Then
Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbi"
Rename Temp$, Left$(Temp$, Len(Temp$) - 4) & ".sbx"
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 SendMessage(List1, LB_DELETESTRING, 0, "")
 Temp$ = FindNext$
Wend
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 If Lcase$(Right$(Temp$, 3)) = "sbi" Then
  Temp$ = "[+] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 If Lcase$(Right$(Temp$, 3)) = "sbx" Then
  Temp$ = "[_] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 Temp$ = FindNext$
Wend
End If
'===========================================================================================
If Cbctl = ID_Button3 Then
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 SendMessage(List1, LB_DELETESTRING, 0, "")
 Temp$ = FindNext$
Wend
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 If Lcase$(Right$(Temp$, 3)) = "sbi" Then
  Temp$ = "[+] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 If Lcase$(Right$(Temp$, 3)) = "sbx" Then
  Temp$ = "[_] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
  List$ = ""
 End If
 Temp$ = FindNext$
Wend
Open "Tools\Inducer.sbi" For Binary As Fp1
 Seek Fp1, Lof("Tools\Inducer.sbi") - 8192
 Get$ Fp1, Temp$, 8192
 Temp$ = Rtrim$(Temp$)
Close Fp1
SetText(Edit1, Temp$)
End If
'===========================================================================================
If Cbctl = ID_Button4 Then
Temp$ = GetText$(Combo1)
If Temp$ = "" Or Temp$ = "Multi Menu" Then
 TextColor(WHITE)
 Print "Extracting: ";
 TextColor(LIGHT_GRAY)
 ? "Inducer.sbi"
 Temp$ = "Tools\Unzip.exe -o -qq Tools\Inducer.sbi"
 ShellWait(Temp$)
 Temp$ = FindFirst$("Sbi\*.sbi")
 While Temp$ <> ""
  TextColor(WHITE)
  Print "Extracting: ";
  TextColor(LIGHT_GRAY)
  Print Temp$
  Temp$ = "Tools\Unzip.exe -o -qq Sbi\" & Temp$
  ShellWait(Temp$)
  Temp$ = FindNext$
 Wend
 Temp$ = FindFirst$("Sbi\*.sbt")
 While Temp$ <> ""
  TextColor(WHITE)
  Print "Extracting: ";
  TextColor(LIGHT_GRAY)
  ? Temp$
  Temp$ = "Tools\Unzip.exe -o -qq Sbi\" & Temp$
  ShellWait(Temp$)
  Temp$ = FindNext$
 Wend
 If Exist("Inducer\Emus") Then
  Temp$ = FindFirst$("Inducer\Emus\*.dxl")
  Count = 0
  While Temp$ <> ""
   Dxl$[Count] = "Inducer\Emus\" & Temp$
   Incr Count
   Temp$ = FindNext$
  Wend
  Qsort Dxl$, Count
  Incr Count
  If Exist("Inducer\Themes\Emus.dxl") Then Kill "Inducer\Themes\Emus.dxl"
  Open "Inducer\Themes\Emus.dxl" For Output As Fp1
   Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
   Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
   Chr$(34), "/cd/Themes/Emus.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
   Count = 0
   While Dxl$[Count] <> ""
    Open Dxl$[Count] For Input As Fp2
     While Not Eof(Fp2)
      Line Input Fp2, Temp$
      Fprint Fp1, Temp$
     Wend
    Close Fp2
    Dxl$[Count] = ""
    Incr Count
   Wend
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Exit to Menu", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), "Exit to the main menu", Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Exit.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Mainmenu.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
   Fprint Fp1, "</LIST>"
  Close Fp1
  Temp$ = FindFirst$("Inducer\Emus\*.dxl")
  While Temp$ <> ""
   Kill "Inducer\Emus\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Apps") Then
  Temp$ = FindFirst$("Inducer\Apps\*.dxl")
  Count = 0
  While Temp$ <> ""
   Dxl$[Count] = "Inducer\Apps\" & Temp$
   Incr Count
   Temp$ = FindNext$
  Wend
  Qsort Dxl$, Count
  Incr Count
  If Exist("Inducer\Themes\Apps.dxl") Then Kill "Inducer\Themes\Apps.dxl"
  Open "Inducer\Themes\Apps.dxl" For Output As Fp1
   Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
   Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
   Chr$(34), "/cd/Themes/Apps.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
   Count = 0
   While Dxl$[Count] <> ""
    Open Dxl$[Count] For Input As Fp2
     While Not Eof(Fp2)
      Line Input Fp2, Temp$
      Fprint Fp1, Temp$
     Wend
    Close Fp2
    Dxl$[Count] = ""
    Incr Count
   Wend
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Exit to Menu", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), "Exit to the main menu", Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Exit.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Mainmenu.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
   Fprint Fp1, "</LIST>"
  Close Fp1
  Temp$ = FindFirst$("Inducer\Apps\*.dxl")
  While Temp$ <> ""
   Kill "Inducer\Apps\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Games") Then
  Temp$ = FindFirst$("Inducer\Games\*.dxl")
  Count = 0
  While Temp$ <> ""
   Dxl$[Count] = "Inducer\Games\" & Temp$
   Incr Count
   Temp$ = FindNext$
  Wend
  Qsort Dxl$, Count
  Incr Count
  If Exist("Inducer\Themes\Games.dxl") Then Kill "Inducer\Themes\Games.dxl"
  Open "Inducer\Themes\Games.dxl" For Output As Fp1
   Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
   Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
   Chr$(34), "/cd/Themes/Games.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
   Count = 0
   While Dxl$[Count] <> ""
    Open Dxl$[Count] For Input As Fp2
     While Not Eof(Fp2)
      Line Input Fp2, Temp$
      Fprint Fp1, Temp$
     Wend
    Close Fp2
    Dxl$[Count] = ""
    Incr Count
   Wend
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Exit to Menu", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), "Exit to the main menu", Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Exit.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Mainmenu.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
   Fprint Fp1, "</LIST>"
  Close Fp1
  Temp$ = FindFirst$("Inducer\Games\*.dxl")
  While Temp$ <> ""
   Kill "Inducer\Games\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Demos") Then
  Temp$ = FindFirst$("Inducer\Demos\*.dxl")
  Count = 0
  While Temp$ <> ""
   Dxl$[Count] = "Inducer\Demos\" & Temp$
   Incr Count
   Temp$ = FindNext$
  Wend
  Qsort Dxl$, Count
  Incr Count
  If Exist("Inducer\Themes\Demos.dxl") Then Kill "Inducer\Themes\Demos.dxl"
  Open "Inducer\Themes\Demos.dxl" For Output As Fp1
   Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
   Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
   Chr$(34), "/cd/Themes/Demos.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
   Count = 0
   While Dxl$[Count] <> ""
    Open Dxl$[Count] For Input As Fp2
     While Not Eof(Fp2)
      Line Input Fp2, Temp$
      Fprint Fp1, Temp$
     Wend
    Close Fp2
    Dxl$[Count] = ""
    Incr Count
   Wend
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Exit to Menu", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), "Exit to the main menu", Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Exit.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Mainmenu.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
   Fprint Fp1, "</LIST>"
  Close Fp1
  Temp$ = FindFirst$("Inducer\Demos\*.dxl")
  While Temp$ <> ""
   Kill "Inducer\Demos\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 Count = 0
 If Exist("Inducer\Emus") Then Incr Count
 If Exist("Inducer\Apps") Then Incr Count
 If Exist("Inducer\Games") Then Incr Count
 If Exist("Inducer\Demos") Then Incr Count
 Open "Inducer\Mainmenu.dxl" For Output As Fp1
  Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
  Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
  Chr$(34), "/cd/Themes/Mainmenu.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
  If Exist("Inducer\Emus") Then
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Emus", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Emus.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Themes/Emus.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
  End If
  If Exist("Inducer\Apps") Then
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Apps", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Apps.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Themes/Apps.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
  End If
  If Exist("Inducer\Games") Then
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Games", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Games.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Themes/Games.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
  End If
  If Exist("Inducer\Demos") Then
   Fprint Fp1, "  <LINK"
   Fprint Fp1, "    TITLE=", Chr$(34), "Demos", Chr$(34)
   Fprint Fp1, "    DESCRIPTION=", Chr$(34), Chr$(34)
   Fprint Fp1, "    SCREENSHOT=", Chr$(34), "/cd/Themes/Demos.png", Chr$(34)
   Fprint Fp1, "    TARGET=", Chr$(34), "/cd/Themes/Demos.dxl", Chr$(34)
   Fprint Fp1, "    PREROLL=", Chr$(34), "/cd/Themes/Loading.dxi", Chr$(34), "/>"
  End If
  Fprint Fp1, "</LIST>"
 Close Fp1
 TextColor(LIGHT_GREEN)
 Print Crlf$, "Extraction complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
'===========================================================================================
If Temp$ = "Single Menu" Then
 TextColor(WHITE)
 Print "Extracting: ";
 TextColor(LIGHT_GRAY)
 ? "Inducer.sbi"
 Temp$ = "Tools\Unzip.exe -o -qq Tools\Inducer.sbi"
 ShellWait(Temp$)
 Temp$ = FindFirst$("Sbi\*.sbi")
 While Temp$ <> ""
  TextColor(WHITE)
  Print "Extracting: ";
  TextColor(LIGHT_GRAY)
  Print Temp$
  Temp$ = "Tools\Unzip.exe -o -qq Sbi\" & Temp$
  ShellWait(Temp$)
  Temp$ = FindNext$
 Wend
 Temp$ = FindFirst$("Sbi\*.sbt")
 While Temp$ <> ""
  TextColor(WHITE)
  Print "Extracting: ";
  TextColor(LIGHT_GRAY)
  Print Temp$
  Temp$ = "Tools\Unzip.exe -o -qq Sbi\" & Temp$
  ShellWait(Temp$)
  Temp$ = FindNext$
 Wend
 If Exist("Inducer\Emus") Then
  Temp$ = FindFirst$("Inducer\Emus\*.dxl")
  While Temp$ <> ""
   Copyfile "Inducer\Emus\" & Temp$, "Inducer\" & Temp$
   Kill "Inducer\Emus\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Apps") Then
  Temp$ = FindFirst$("Inducer\Apps\*.dxl")
  While Temp$ <> ""
   Copyfile "Inducer\Apps\" & Temp$, "Inducer\" & Temp$
   Kill "Inducer\Apps\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Games") Then
  Temp$ = FindFirst$("Inducer\Games\*.dxl")
  While Temp$ <> ""
   Copyfile "Inducer\Games\" & Temp$, "Inducer\" & Temp$
   Kill "Inducer\Games\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Demos") Then
  Temp$ = FindFirst$("Inducer\Demos\*.dxl")
  While Temp$ <> ""
   Copyfile "Inducer\Demos\" & Temp$, "Inducer\" & Temp$
   Kill "Inducer\Demos\" & Temp$
   Temp$ = FindNext$
  Wend
 End If
 If Exist("Inducer\Mainmenu.dxl") Then Kill "Inducer\Mainmenu.dxl"
 Temp$ = FindFirst$("Inducer\Themes\*.dxl")
 While Temp$ <> ""
  Kill "Inducer\Themes\" & Temp$
  Temp$ = FindNext$
 Wend
 Count = 0
 Temp$ = FindFirst$("Inducer\*.dxl")
 While Temp$ <> ""
  Dxl$[Count] = "Inducer\" & Temp$
  Incr Count
  Temp$ = FindNext$
 Wend
 Qsort Dxl$, Count
 Open "Inducer\Mainmenu.dxl" For Output As Fp1
  Fprint Fp1, "<?xml version='1.0' encoding='UTF-8'?>"
  Fprint Fp1, "<LIST ENTRIES='", Mid$(Str$(Count), 2, Len(Str$(Count))-1), "' THEME=",  _
  Chr$(34), "/cd/Themes/Mainmenu.dxt", Chr$(34), " MODE=", Chr$(34), "RGB565", Chr$(34), ">"
  Count = 0
  While Dxl$[Count] <> ""
   Open Dxl$[Count] For Input As Fp2
    While Not Eof(Fp2)
     Line Input Fp2, Temp$
     Fprint Fp1, Temp$
    Wend
   Close Fp2
   Dxl$[Count] = ""
   Incr Count
  Wend
  Fprint Fp1, "</LIST>"
 Close Fp1
 Temp$ = FindFirst$("Inducer\*.dxl")
 While Temp$ <> ""
  Temp$ = "Inducer\" & Temp$
  If Temp$ <> "Inducer\Mainmenu.dxl" Then Kill Temp$
  Temp$ = FindNext$
 Wend
 TextColor(LIGHT_GREEN)
 Print Crlf$, "Extraction complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
'===========================================================================================
If Temp$ = "Sbi2boot" And Trim$(List$) = "" Then
 Msgbox "Select a file from the right.", "Slow down!", MB_ICONWARNING
End If
If Temp$ = "Sbi2boot" And Trim$(List$) <> "" Then
Count = Msgbox("The Inducer dir will be deleted." , "Warning!", MB_YESNO + MB_ICONWARNING)
If Count = IDYES Then
 If Exist("Inducer") Then
  Chdir Appexepath$ & "Inducer"
  While Curdir$ & "\" <> Appexepath$
   Chdir Appexepath$ & "Inducer"
   While Len(Curdir$) <> Count
    Count = Len(Curdir$)
    Temp$ = FindFirst$("*.*")
    While Temp$ <> ""
     If Getattr(Temp$) = 48 Then Setattr(Temp$, 16)
     If Getattr(Temp$) = 16 And Temp$ <> "." And Temp$ <> ".." Then Chdir Temp$
     Temp$ = FindNext$
    Wend
   Wend
   Temp$ = FindFirst$("*.*")
   While Temp$ <> ""
    If Getattr(Temp$) <> 16 And Temp$ <> "." And Temp$ <> ".." Then
     TextColor(WHITE)
	 Print "Removing: ";
	 TextColor(LIGHT_GRAY)
	 Print Temp$
     Setattr(Temp$, 32)
     Kill Temp$
    End If
    Temp$ = FindNext$
   Wend
   Count = Len(Curdir$) - 1
   While Mid$(Curdir$, Count, 1) <> "\"
    Decr Count
   Wend
   Chdir Left$(Curdir$, Count - 1)
   Temp$ = FindFirst$("*.*")
   While Temp$ <> ""
    If Getattr(Temp$) = 16 And Temp$ <> "." And Temp$ <> ".." Then Rmdir Temp$
    Temp$ = FindNext$
   Wend
  Wend
 End If
 If Left$(List$, 3) = "[+]" Then
  Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbi"
 End If
 If Left$(List$, 3) = "[_]" Then
  Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbx"
 End If
 TextColor(WHITE) 
 Print Crlf$, "Extracting: ";
 TextColor(LIGHT_GRAY)
 Print Mid$(Temp$, 5, Len(Temp$) - 5), "i", Crlf$
 Temp$ = "Tools\Unzip.exe -o -qq " & Temp$
 ShellWait(Temp$)
 Temp$ = "Tools\Unzip.exe -o -qq Tools\Inducer.sbi Inducer\Ip.bin"
 ShellWait(Temp$)
 If Exist("Inducer\Emus") Then
  Temp$ = "Inducer\Emus\" & FindFirst$("Inducer\Emus\*.dxl")
  Open Temp$ For Input As Fp1
   While Not Eof(Fp1)
    Line Input Fp1, Temp$
    Temp$ = Left$(Temp$, Len(Temp$) - 1)
    Temp$ = Replace$(Temp$, "/", "\")
    Temp$ = Trim$(Temp$)
    If Right$(Temp$, 3) = "png" Or Right$(Temp$, 3) = "PNG" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 17, Len(Temp$) - 16)
     Kill Temp$
     Count = Len(Temp$) - 1
     While Mid$(Temp$, Count, 1) <> "\"
      Decr Count
     Wend
     Rmdir Left$(Temp$, Count - 1)
    End If
    If Right$(Temp$, 3) = "bin" Or Right$(Temp$, 3) = "BIN" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 13, Len(Temp$) - 12)
     Temp$ = "Tools\Scramble.exe " & Temp & " Inducer\1st_read.bin"
     ShellWait(Temp$)
     Temp$ = Mid$(Temp$, 20, Len(Temp$) - 40)
     Kill Temp$
    End If
   Wend
  Close Fp1
  Temp$ = "Inducer\Emus\" & FindFirst$("Inducer\Emus\*.dxl")
  Kill Temp$
  Temp$ = FindFirst$("Inducer\*.*")
  While Temp$ <> ""
   Temp$ = FindNext$
  Wend
  Rmdir "Inducer\Emus"
 End If
 If Exist("Inducer\Apps") Then
  Temp$ = "Inducer\Apps\" & FindFirst$("Inducer\Apps\*.dxl")
  Open Temp$ For Input As Fp1
   While Not Eof(Fp1)
    Line Input Fp1, Temp$
    Temp$ = Left$(Temp$, Len(Temp$) - 1)
    Temp$ = Replace$(Temp$, "/", "\")
    Temp$ = Trim$(Temp$)
    If Right$(Temp$, 3) = "png" Or Right$(Temp$, 3) = "PNG" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 17, Len(Temp$) - 16)
     Kill Temp$
     Count = Len(Temp$) - 1
     While Mid$(Temp$, Count, 1) <> "\"
      Decr Count
     Wend
     Rmdir Left$(Temp$, Count - 1)
    End If
    If Right$(Temp$, 3) = "bin" Or Right$(Temp$, 3) = "BIN" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 13, Len(Temp$) - 12)
     Temp$ = "Tools\Scramble.exe " & Temp & " Inducer\1st_read.bin"
     ShellWait(Temp$)
     Temp$ = Mid$(Temp$, 20, Len(Temp$) - 40)
     Kill Temp$
    End If
   Wend
  Close Fp1
  Temp$ = "Inducer\Apps\" & FindFirst$("Inducer\Apps\*.dxl")
  Kill Temp$
  Temp$ = FindFirst$("Inducer\*.*")
  While Temp$ <> ""
   Temp$ = FindNext$
  Wend
  Rmdir "Inducer\Apps"
 End If
 If Exist("Inducer\Games") Then
  Temp$ = "Inducer\Games\" & FindFirst$("Inducer\Games\*.dxl")
  Open Temp$ For Input As Fp1
   While Not Eof(Fp1)
    Line Input Fp1, Temp$
    Temp$ = Left$(Temp$, Len(Temp$) - 1)
    Temp$ = Replace$(Temp$, "/", "\")
    Temp$ = Trim$(Temp$)
    If Right$(Temp$, 3) = "png" Or Right$(Temp$, 3) = "PNG" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 17, Len(Temp$) - 16)
     Kill Temp$
     Count = Len(Temp$) - 1
     While Mid$(Temp$, Count, 1) <> "\"
      Decr Count
     Wend
     Rmdir Left$(Temp$, Count - 1)
    End If
    If Right$(Temp$, 3) = "bin" Or Right$(Temp$, 3) = "BIN" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 13, Len(Temp$) - 12)
     Temp$ = "Tools\Scramble.exe " & Temp & " Inducer\1st_read.bin"
     ShellWait(Temp$)
     Temp$ = Mid$(Temp$, 20, Len(Temp$) - 40)
     Kill Temp$
    End If
   Wend
  Close Fp1
  Temp$ = "Inducer\Games\" & FindFirst$("Inducer\Games\*.dxl")
  Kill Temp$
  Temp$ = FindFirst$("Inducer\*.*")
  While Temp$ <> ""
   Temp$ = FindNext$
  Wend
  Rmdir "Inducer\Games"
 End If
 If Exist("Inducer\Demos") Then
  Temp$ = "Inducer\Demos\" & FindFirst$("Inducer\Demos\*.dxl")
  Open Temp$ For Input As Fp1
   While Not Eof(Fp1)
    Line Input Fp1, Temp$
    Temp$ = Left$(Temp$, Len(Temp$) - 1)
    Temp$ = Replace$(Temp$, "/", "\")
    Temp$ = Trim$(Temp$)
    If Right$(Temp$, 3) = "png" Or Right$(Temp$, 3) = "PNG" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 17, Len(Temp$) - 16)
     Kill Temp$
     Count = Len(Temp$) - 1
     While Mid$(Temp$, Count, 1) <> "\"
      Decr Count
     Wend
     Rmdir Left$(Temp$, Count - 1)
    End If
    If Right$(Temp$, 3) = "bin" Or Right$(Temp$, 3) = "BIN" Then
     Temp$ = "Inducer\" & Mid$(Temp$, 13, Len(Temp$) - 12)
     Temp$ = "Tools\Scramble.exe " & Temp & " Inducer\1st_read.bin"
     ShellWait(Temp$)
     Temp$ = Mid$(Temp$, 20, Len(Temp$) - 40)
     Kill Temp$
    End If
   Wend
  Close Fp1
  Temp$ = "Inducer\Demos\" & FindFirst$("Inducer\Demos\*.dxl")
  Kill Temp$
  Temp$ = FindFirst$("Inducer\*.*")
  While Temp$ <> ""
   Temp$ = FindNext$
  Wend
  Rmdir "Inducer\Demos"
 End If
 TextColor(LIGHT_GREEN)
 Print "Extraction complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
End If
End If
'===========================================================================================
If Cbctl = ID_Button5 Then 'DiscJuggler original button
	ChangeImagePropertiesTitleLabel("DiscJuggler Image")
	ResetAllVisibilityState() 'we don't know where the user was before clicking this button
	ChangeImagePropertiesVisibilityState(True, False) 'show image properties panel
End If
'===========================================================================================
If Cbctl = ID_IP_Back_Btn Then 'hide the ImageProperties panel and return to main screen
	ChangeImagePropertiesVisibilityState(False, False)
	ChangePackagesListVisibilityState(True)
End If
'===========================================================================================
If Cbctl = ID_IP_DJ_Generate_Btn Then 'DiscJugglerCDI v4.0 Generation started

	Local TargetFileName As String
	Local SelfbootPath As String
	Local Options As String
	Local DataISO As String
	
	SelfbootPath = GetApplicationPath() 'Get Selfboot Inducer application path
	TargetFileName = GETFILENAME$("Save your DiscJuggler image to...", "DiscJuggler Image (*.cdi)|*.cdi|All files(*.*)|*.*", 1, _
		Form1, OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST) 'BC has a bug with the flags, you MUST patch BC.EXE before compiling this code !
	If Len(TargetFileName) = 0 Then Exit Function 'Cancel button pushed
	TargetFileName = CorrectTargetFileName(TargetFileName, ".cdi") 'to be sure that us filename has the required extension (here CDI)
	SetCurrentDirectory(SelfbootPath) 'When GETFILENAME$'s called, the current directory is changed so we need to reset it
	'TargetFileName contains the destination filename
	
	Print "Generating DiscJuggler Image...", Crlf$
	
	'Test for the IP.BIN
	If Not Exist("Inducer\IP.BIN") Then
		TextColor(LIGHT_RED)
		Print "IP.BIN was not found. Please insert it in the Inducer directory !", Crlf$
		TextColor(LIGHT_GRAY)
		Exit Function
	End If
	
	'Insert IPLOGO.MR inside IP.BIN if the user want it.
	If insertLogo Then
		If InsertLogoInIPBIN("Tools\Iplogo.mr", "Inducer\IP.BIN") Then
			TextColor(LIGHT_GREEN)
			Print "Iplogo.mr inserted.", Crlf$
			TextColor(LIGHT_GRAY)
		Else
			TextColor(LIGHT_RED)
			Print "Iplogo.mr insertion failed !", Crlf$
			TextColor(LIGHT_GRAY)
		End If
	End If
	
	'options
	Options = ""
	if useJoliet Then Options = "-J"
	if useRock Then Options = Options & " -R"
	
	DataISO = CHR$(34) & temporaryDir & "data.iso" & CHR$(34) 'temp data track
	
	'generate the data track
	Temp$ = "Tools\mkisofs.exe -C 0,11702 -V " & CHR$(34) & GetText(IP_Label_Edit) & CHR$(34) & " -G Inducer\ip.bin " & Options & " -l -o " & DataISO & " Inducer"
	ShellWait(Temp$)
 
	'if data track ok
	If Exist(temporaryDir & "data.iso") Then
		Print Crlf$
		Temp$ = "Tools\cdi4dc.exe " & DataISO & " " & CHR$(34) & TargetFileName & CHR$(34) 'generate the final CDI
		ShellWait(Temp$)
		
		Kill (temporaryDir & "data.iso")

		'Success !
		TextColor(LIGHT_GREEN)
		Print Crlf$, "DiscJuggler image successfully created. Burn it now !", Crlf$
		TextColor(LIGHT_GRAY)
		
		'Return at the main screen
		ChangeImagePropertiesVisibilityState(False, False)
		ChangePackagesListVisibilityState(True)
	Else
		TextColor(LIGHT_RED)
		Print Crlf$, "Error when creating the DiscJuggler image !", Crlf$
		TextColor(LIGHT_GRAY)
	End If
	
End If
'===========================================================================================
If Cbctl = ID_Button6 Then 'Nero original button
	ChangeImagePropertiesTitleLabel("Nero Burning Rom Image")
	ResetAllVisibilityState() 'we don't know where the user was before clicking this button
	ChangeImagePropertiesVisibilityState(True, True)
End If
'===========================================================================================
If Cbctl = ID_IP_NRG_Generate_Btn Then 'Nero Image creation

	Local TargetFileName As String
	Local SelfbootPath As String
	Local TaoSwitch As String
	Local Tao As Boolean
	Local Options As String
	Local DataISO As String
	Local TempCDI As String
	
	SelfbootPath = GetApplicationPath() 'Get Selfboot Inducer application path
	TargetFileName = GETFILENAME$("Save your Nero image to...", "Nero Burning Rom Image (*.nrg)|*.nrg|All files(*.*)|*.*", 1, _
	Form1, OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST) 'BC has a bug with the flags, you MUST patch BC.EXE before compiling this code !
	If Len(TargetFileName) = 0 Then Exit Function 'Cancel button pushed
	TargetFileName = CorrectTargetFileName(TargetFileName, ".nrg") 'to be sure that us filename has the required extension (here CDI)
	SetCurrentDirectory(SelfbootPath) 'When GETFILENAME$'s called, the current directory is changed so we need to reset it
	'TargetFileName contains the destination filename

	If (IsDlgButtonChecked(Form1, ID_IP_Nero_DAO_RB) = BST_CHECKED) Then 'Is the DAO button checked ?
		TaoSwitch = "" 'yes
		Print "Generating Nero Burning Rom DAO Image...", Crlf$	
		Tao = False 'marche mal sur les string alors on fait ça
	Else
		TaoSwitch = " -t" 'no
		Print "Generating Nero Burning Rom TAO Image...", Crlf$	
		Tao = True
	End If
	
	'Test for the IP.BIN
	If Not Exist("Inducer\IP.BIN") Then
		TextColor(LIGHT_RED)
		Print "IP.BIN was not found. Please insert it in the Inducer directory !", Crlf$
		TextColor(LIGHT_GRAY)
		Exit Function
	End If
	
	'Insert IPLOGO.MR inside IP.BIN if the user want it.
	If insertLogo Then
		If InsertLogoInIPBIN("Tools\Iplogo.mr", "Inducer\IP.BIN") Then
			TextColor(LIGHT_GREEN)
			Print "Iplogo.mr inserted.", Crlf$
			TextColor(LIGHT_GRAY)
		Else
			TextColor(LIGHT_RED)
			Print "Iplogo.mr insertion failed !", Crlf$
			TextColor(LIGHT_GRAY)
		End If
	End If
	
	'options
	Options = ""
	if useJoliet Then Options = "-J"
	if useRock Then Options = Options & " -R"
	
	'temp files
	DataISO = CHR$(34) & temporaryDir & "data.iso" & CHR$(34)
	TempCDI = CHR$(34) & temporaryDir & "temp.cdi" & CHR$(34)
	
	Temp$ = "Tools\mkisofs.exe -C 0,11702 -V " & CHR$(34) & GetText(IP_Label_Edit) & CHR$(34) & " -G Inducer\ip.bin " & Options & " -l -o " & DataISO & " Inducer"
	ShellWait(Temp$)
	
	If Exist(temporaryDir & "data.iso") Then
		Print Crlf$
		Temp$ = "Tools\cdi4dc.exe " & DataISO & " " & TempCDI 'generate temp CDI
		ShellWait(Temp$)
		
		Kill (temporaryDir & "data.iso")
		
		Print Crlf$
		
		'convert to Nero Image
		Temp$ = "Tools\cdi2nero.exe " & TempCDI & " " & CHR$(34) & TargetFileName & CHR$(34) & TaoSwitch 'SiZ! : CDI2NERO doesn't accept CDI v4.0 images. I can't use CDI4DC
		ShellWait(Temp$)
		
		Kill(temporaryDir & "temp.cdi") 'delete temp CDI
		
		If Tao Then
			TextColor(LIGHT_GREEN)
			Print Crlf$, "Nero Burning Rom TAO image successfully created. Burn it now !", Crlf$
			TextColor(LIGHT_GRAY)
		Else
			TextColor(LIGHT_GREEN)
			Print Crlf$, "Nero Burning Rom DAO image successfully created. Burn it now !", Crlf$
			TextColor(LIGHT_GRAY)
		End If
			
		'Return at the main screen
		ChangeImagePropertiesVisibilityState(False, False)
		ChangePackagesListVisibilityState(True)
	Else
		TextColor(LIGHT_RED)
		Print Crlf$, "Error when creating the DiscJuggler image !", Crlf$
		TextColor(LIGHT_GRAY)
	End If
	
End If
'===========================================================================================
If Cbctl = ID_Button8 Then 'CDRecord panel
	ResetAllVisibilityState()
	ChangeCDRecordVisibilityState(True)
	
 'Show the selfboot inducer tutorial
 Open "Tools\Inducer.sbi" For Binary As Fp1
  Seek Fp1, Lof("Tools\Inducer.sbi") - 8192
  Get$ Fp1, Temp$, 8192
  Temp$ = Rtrim$(Temp$)
 Close Fp1
 SetText(Edit1, Temp$)
End If
'===========================================================================================
If Cbctl = ID_Button9 Then
Count = Msgbox("The Inducer will be cleaned." , "Warning!", MB_YESNO + MB_ICONWARNING)
If Count = IDYES Then
 If Exist("Inducer") Then
  Chdir Appexepath$ & "Inducer"
  While Curdir$ & "\" <> Appexepath$
   Chdir Appexepath$ & "Inducer"
   While Len(Curdir$) <> Count
    Count = Len(Curdir$)
    Temp$ = FindFirst$("*.*")
    While Temp$ <> ""
     If Getattr(Temp$) = 48 Then Setattr(Temp$, 16)
     If Getattr(Temp$) = 16 And Temp$ <> "." And Temp$ <> ".." Then Chdir Temp$
     Temp$ = FindNext$
    Wend
   Wend
   Temp$ = FindFirst$("*.*")
   While Temp$ <> ""
    If Getattr(Temp$) <> 16 And Temp$ <> "." And Temp$ <> ".." Then
	 TextColor(WHITE)
     Print "Removing: ";
	 TextColor(LIGHT_GRAY)
	 Print Temp$
     Setattr(Temp$, 32)
     Kill Temp$
    End If
    Temp$ = FindNext$
   Wend
   Count = Len(Curdir$) - 1
   While Mid$(Curdir$, Count, 1) <> "\"
    Decr Count
   Wend
   Chdir Left$(Curdir$, Count - 1)
   Temp$ = FindFirst$("*.*")
   While Temp$ <> ""
    If Getattr(Temp$) = 16 And Temp$ <> "." And Temp$ <> ".." Then Rmdir Temp$
    Temp$ = FindNext$
   Wend
  Wend
 End If
 TextColor(WHITE)
 Print Crlf$, "Extracting: ";
 TextColor(LIGHT_GRAY)
 Print "Inducer.sbi", Crlf$
 Temp$ = "Tools\Unzip.exe -o -qq Tools\Inducer.sbi"
 ShellWait(Temp$)
 TextColor(LIGHT_GREEN)
 Print "Directory restored.", Crlf$
 TextColor(LIGHT_GRAY)
End If
End If
'===========================================================================================
If Cbctl = ID_Button10 Then
 Temp$ = "Tools\Cdrecord.exe -scanbus"
 ShellWait(Temp$)
End If
'===========================================================================================
If Cbctl = ID_Button11 Then
If GetText$(Edit3) <> "x,x,x" Then
 Temp$ = "Tools\Cdrecord.exe -v -dev=" & GetText$(Edit3) & " -multi -audio speed=" & _
 GetText$(Edit4) & " Tools\Audio.raw"
 ShellWait(Temp$)
 TextColor(LIGHT_GREEN)
 Print Crlf$, "Burn complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
End If
'===========================================================================================
If Cbctl = ID_Button12 Then
 Temp$ = "Tools\Cdrecord.exe -dev=" & GetText$(Edit3) & " -msinfo > " & chr(34) & _
 Appexepath$ & "Tools\Msinfo.ini" & chr(34)
 Open "Tools\Msinfo.bat" For Output As Fp1
  Fprint Fp1, Temp$
 Close Fp1
 Temp$ = "Tools\Msinfo.bat"
 ShellWait(Temp$)
 Kill "Tools\Msinfo.bat"
 TextColor(LIGHT_GREEN)
 Print Crlf$, "Msinfo complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
'===========================================================================================
If Cbctl = ID_Button13 Then
If GetText$(Edit5) = "GOATSE" Then
 Print " /     \             \            /    \"
 Print "I       I             \          I      I"
 Print "I       `.             I         I       :"
 Print "`        I             I        \I       I"
 Print " \       I /       /  \\\   --__ \\       :"
 Print "  \      \/   _--~~          ~--__I \     I"
 Print "   \      \_-~                    ~-_\    I"
 Print "    \_     \        _.--------.______\I   I"
 Print "      \     \______// _ ___ _ (_(__>  \   I"
 Print "       \   .  C ___)  ______ (_(____>  I  /"
 Print "       /\ I   C ____)/      \ (_____>  I_/"
 Print "      / /\I   C_____)       I  (___>   /  \"
 Print "     I   (   _C_____)\______/  // _/ /     \"
 Print "     I    \  I__   \\_________// (__/       I"
 Print "    I \    \____)   `----   --'             I"
 Print "    I  \_          ___\       /_          _/ I"
 Print "   I              /    I     I  \            I"
 Print "   I             I    /       \  \           I"
 Print "   I          / /    I         I  \           I"
 Print "   I         / /      \__/\___/    I          I"
 Print "  I         / /        I    I       I         I"
 Print "  I          I         I    I       I         I" & Crlf$
 SetText(Form1, "Goatse Inducer")
Else
 If Exist("Tools\Msinfo.ini") Then
  Open "Tools\Msinfo.ini" For Input As Fp1
   Line Input Fp1, List$
   List$ = Trim$(List$)
  Close Fp1
 End If
 If List$ <> "" And Exist("Inducer\Ip.bin") Then
  If Exist("Tools\Iplogo.mr") Then
   Open "Inducer\Ip.bin" For Binary As Fp1
    Seek Fp1, 14368
    Temp$ = Repeat$(8192, Chr$(0))
    Put$ Fp1, Temp$, 8192
    Seek Fp1, 14368
    Open "Tools\Iplogo.mr" For Binary As Fp2
     Get$ Fp2, Temp$, Lof("Tools\Iplogo.mr")
    Close Fp2
    Put$ Fp1, Temp$, Lof("Tools\Iplogo.mr")
   Close Fp1
  Print "Iplogo.bin inserted.", Crlf$
  End If
  Temp$ = "Tools\Mkisofs.exe -C " & List$ & " -V " & _
  GetText$(Edit5) & " -R -l -o data.iso INDUCER"
  List$ = ""
  ShellWait(Temp$)
  If Exist("data.iso") Then
   Open "Inducer\Ip.bin" For Binary As Fp1
    Get$ Fp1, Temp$, 32768
   Close Fp1
   Open "data.iso" For Binary As Fp1
    Seek Fp1, 0
    Put$ Fp1, Temp$, 32768
   Close Fp1
  End If
  Print Crlf$, "Iso created.", Crlf$
 End If
End If
End If
'===========================================================================================
If Cbctl = ID_Button14 Then
If GetText$(Edit3) <> "x,x,x" Then
 Temp$ = "Tools\Cdrecord.exe -v -eject -dev=" & GetText$(Edit3) & _
 " -xa1 speed=" & GetText$(Edit6) & " data.iso"
 ShellWait(Temp$)
 TextColor(LIGHT_GREEN)
 Print Crlf$, "Burn complete.", Crlf$
 TextColor(LIGHT_GRAY)
End If
End If
'===========================================================================================
If Cbctl = ID_Button15 Then 'CDRecord button back
 ChangeCDRecordVisibilityState(False)
 ChangePackagesListVisibilityState(True)
End If
'===========================================================================================
Case WM_DESTROY
'===========================================================================================
'DestroyThemedButton()

Temp$ = FindFirst$("Sbi\*.sbx")
While Temp$ <> ""
 Temp$ = "Sbi\" & Temp$
 Rename Temp$, Left$(Temp$, Len(Temp$) - 4) & ".sbi"
 Temp$ = FindNext$
Wend
If Exist("Tools\Cdrecord.ini") Then Kill "Tools\Cdrecord.ini"
Open "Tools\Cdrecord.ini" For Output As Fp1
 Temp$ = GetText$(Edit3)
 Fprint Fp1, Temp$
 Temp$ = GetText$(Edit4)
 Fprint Fp1, Temp$
 Temp$ = GetText$(Edit6)
 Fprint Fp1, Temp$
Close Fp1
PostQuitMessage(0)
'===========================================================================================
End Select
End Function

Callback Function ListBox_WndProc
Dim RAW cSel
Select Case CBMSG
'===========================================================================================
CASE WM_LBUTTONUP
'===========================================================================================
cSel = SendMessage(CBHWND, LB_GETCURSEL, 0, 0)
List$ = Space$(255)
SendMessage (CBHWND, LB_GETTEXT, cSel, List$)
'===========================================================================================
If Left$(List$, 3) = "[+]" Then
 EnableWindow(Button1, FALSE)
Else
 EnableWindow(Button1, TRUE)
End If
If Left$(List$, 3) = "[_]" Then
 EnableWindow(Button2, FALSE)
Else
 EnableWindow(Button2, TRUE)
End If
Temp$ = ""
If Left$(List$, 3) = "[+]" Then Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbi"
If Left$(List$, 3) = "[_]" Then Temp$ = "Sbi\" & Right$(List$, Len(List$) - 4) & ".sbx"
If Temp$ <> "" Then
 Open Temp$ For Binary As Fp1
  Seek Fp1, Lof(Temp$) - 8194
  Get$ Fp1, List$, 1
  If Asc(List$) = 0 Then
   Seek Fp1, Lof(Temp$) - 8193
   Get$ Fp1, List$, 1
   If Asc(List$) = 32 Then
    Seek Fp1, Lof(Temp$) - 8192
    Get$ Fp1, Temp$, 8192
    Temp$ = Rtrim$(Temp$)
    SetText(Edit1, Temp$)
   End If
  Else
   Temp$ = "No description available."
   SetText(Edit1, Temp$)
  End If
 Close Fp1
End If
'===========================================================================================
List$ = Space$(255)
SendMessage (CBHWND, LB_GETTEXT, cSel, List$)
End Select
Function = CallWindowProc(GetProp(CBHWND, "LBCB"), _
hWnd, Msg, wParam, lParam)
End Function

Sub FormLoad(hInst As HANDLE)
'===========================================================================================
Global Dxl$[1000]
Global Temp$ * 32768
Global List$
Global Count

Print "Selfboot Inducer v4 by burnerO 061804", Crlf$
TextColor(LIGHT_RED) 'red !
Print "CDI4DC Stage III : Ultimate Power(tm) starring [big_fury]SiZiOUS (19 nov 06)" 'SiZ! modification (14 nov 06)
Print "This is *NOT* an official version.", Crlf$
TextColor(LIGHT_GRAY) 'normal
If Not Exist("Tools\cdi4dc.exe") Then
 Msgbox "CDI4DC.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
'SiZ! modif (14 nov 06)
'If Not Exist("Tools\Bin2boot.exe") Then
' Msgbox "BIN2BOOT.EXE missing.", "Oops!"
' End
'End If
If Not Exist("Tools\cdi2nero.exe") Then
 MsgBox "CDI2NERO.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
'SiZ! modif (14 nov 06)
'If Not Exist("Tools\Cdi2tao.exe") Then
' Msgbox "CDI2TAO.EXE missing.", "Oops!"
' End
'End If
If Not Exist("Tools\Cdrecord.exe") Then
 Msgbox "CDRECORD.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
If Not Exist("Tools\Cygwin1.dll") Then
 MsgBox "CYGWIN1.DLL missing.", "Oops!", MB_ICONERROR
 End
End If
If Not Exist("Tools\Inducer.sbi") Then
 MsgBox "INDUCER.SBI missing.", "Oops!", MB_ICONERROR
 End
End If
If Not Exist("Tools\Mkisofs.exe") Then
 MsgBox "MKISOFS.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
If Not Exist("Tools\Scramble.exe") Then
 MsgBox "SCRAMBLE.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
If Not Exist("Tools\Unzip.exe") Then
 MsgBox "UNZIP.EXE missing.", "Oops!", MB_ICONERROR
 End
End If
If Exist("Tools\Cdrecord.ini") Then
 Open "Tools\Cdrecord.ini" For Input As Fp1
 Count = 0
 While Not Eof (Fp1)
  Line Input Fp1, Temp$
  Dxl$[Count] = Temp$
  Incr Count
 Wend
 Close Fp1
Else
 Dxl$[0] = "x,x,x"
 Dxl$[1] = "1"
 Dxl$[2] = "1"
End If
Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
 Temp$ = "Sbi\" & Temp$
 Setattr(Temp$, 32)
 If Right$(Temp$, 8) = ".sbi.zip" Then Rename Temp$, Left$(Temp$, Len(Temp$) - 4)
 If Right$(Temp$, 8) = ".sbt.zip" Then Rename Temp$, Left$(Temp$, Len(Temp$) - 4)
 Temp$ = FindNext$
Wend

Open "Tools\Inducer.sbi" For Binary As Fp1
	Seek Fp1, Lof("Tools\Inducer.sbi") - 8192
	Get$ Fp1, Temp$, 8192
	Temp$ = Rtrim$(Temp$)
Close Fp1

'===========================================================================================
Global Form1 AS HANDLE
Form1 = CreateWindow("Sbi", "Selfboot Inducer [CDI4DC Stage III : Ultimate Power]", DS_MODALFRAME Or WS_POPUP _
Or WS_CAPTION Or WS_SYSMENU Or WS_MINIMIZEBOX, _
0, 0, 436, 274, NULL, NULL, hInst, NULL)
'===========================================================================================
Global Group1 AS HANDLE
Group1 = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_GROUP Or WS_VISIBLE, _
2, 2, 259, 190, Form1, NULL, hInst, NULL)
SendMessage(Group1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group2 AS HANDLE
Group2 = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_VISIBLE Or WS_GROUP, _
267, 2, 162, 190, Form1, NULL, hInst, NULL)
'===========================================================================================
Global Group3 AS HANDLE
Group3 = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_GROUP Or WS_VISIBLE, _
2, 197, 159, 56, Form1, NULL, hInst, NULL)
SendMessage(Group3, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group4 AS HANDLE
Group4 = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_GROUP Or WS_VISIBLE, _
162, 197, 158, 56, Form1, NULL, hInst, NULL)
SendMessage(Group4, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global gConfig AS HANDLE
gConfig = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_GROUP Or WS_VISIBLE, _
322, 197, 52, 56, Form1, NULL, hInst, NULL)
SendMessage(gConfig, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group5 AS HANDLE
Group5 = CreateWindowEx(0, "static", "", _
SS_SUNKEN Or WS_CHILD Or WS_GROUP Or WS_VISIBLE, _
378, 197, 50, 56, Form1, NULL, hInst, NULL)
SendMessage(Group5, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))


'===========================================================================================
'===========================================================================================
Global Group6 AS HANDLE
Const ID_Group6 = 128
Group6 = CreateWindowEx(0, "button", "Determine Scanbus", _
WS_CHILD Or BS_GROUPBOX Or WS_VISIBLE, _
267, 0, 161, 42, Form1, ID_Group6, hInst, NULL)
SendMessage(Group6, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group7 AS HANDLE
Const ID_Group7 = 129
Group7 = CreateWindowEx(0, "button", "Burn First Session", _
WS_CHILD Or BS_GROUPBOX Or WS_VISIBLE, _
267, 49, 161, 42, Form1, ID_Group7, hInst, NULL)
SendMessage(Group7, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group8 AS HANDLE
Const ID_Group8 = 130
Group8 = CreateWindowEx(0, "button", "Make Iso", _
WS_CHILD Or BS_GROUPBOX Or WS_VISIBLE, _
267, 98, 161, 42, Form1, ID_Group8, hInst, NULL)
SendMessage(Group8, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Group9 AS HANDLE
Const ID_Group9 = 131
Group9 = CreateWindowEx(0, "button", "Burn Second Session", _
WS_CHILD Or BS_GROUPBOX Or WS_VISIBLE, _
267, 147, 161, 42, Form1, ID_Group9, hInst, NULL)
SendMessage(Group9, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button1 AS HANDLE
Const ID_Button1 = 101
Button1 = CreateWindow("button", "Select", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
272, 162, 45, 22, Form1, ID_Button1, hInst, NULL)
SendMessage(Button1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button2 AS HANDLE
Const ID_Button2 = 102
Button2 = CreateWindow("button", "Deselect", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
325, 162, 58, 22, Form1, ID_Button2, hInst, NULL)
SendMessage(Button2, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button3 AS HANDLE
Const ID_Button3 = 103
Button3 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
398, 162, 25, 22, Form1, ID_Button3, hInst, NULL)
SendMessage(Button3, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button4 AS HANDLE
Const ID_Button4 = 104
Button4 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
114, 200, 40, 40, Form1, ID_Button4, hInst, NULL)
SendMessage(Button4, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button5 AS HANDLE
Const ID_Button5 = 105
Button5 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
170, 200, 40, 40, Form1, ID_Button5, hInst, NULL)
SendMessage(Button5, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button6 AS HANDLE
Const ID_Button6 = 106
Button6 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
221, 200, 40, 40, Form1, ID_Button6, hInst, NULL)
SendMessage(Button6, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
'Global Button7 AS HANDLE
'Const ID_Button7 = 107
'Button7 = CreateWindow("button", "", _
'WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
'274, 200, 40, 40, Form1, ID_Button7, hInst, NULL)
'SendMessage(Button7, WM_SETFONT, _
'GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button8 AS HANDLE
Const ID_Button8 = 108
Button8 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
272, 200, 40, 40, Form1, ID_Button8, hInst, NULL)
SendMessage(Button8, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global btnConfig As HANDLE
Const ID_btnConfig = 300
btnConfig = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
329, 200, 40, 40, Form1, ID_btnConfig, hInst, NULL)
SendMessage(btnConfig, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
ApplyIconToButton(hInst, Form1, btnConfig, 1109)
'===========================================================================================
Global Button9 AS HANDLE
Const ID_Button9 = 109
Button9 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
383, 200, 40, 40, Form1, ID_Button9, hInst, NULL)
SendMessage(Button9, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button10 AS HANDLE
Const ID_Button10 = 110
Button10 = CreateWindow("button", "Scanbus", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
272, 15, 60, 22, Form1, ID_Button10, hInst, NULL)
SendMessage(Button10, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button11 AS HANDLE
Const ID_Button11 = 111
Button11 = CreateWindow("button", "Burn", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
272, 64, 36, 22, Form1, ID_Button11, hInst, NULL)
SendMessage(Button11, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button12 AS HANDLE
Const ID_Button12 = 112
Button12 = CreateWindow("button", "Msinfo", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
368, 64, 48, 22, Form1, ID_Button12, hInst, NULL)
SendMessage(Button12, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button13 AS HANDLE
Const ID_Button13 = 113
Button13 = CreateWindow("button", "Make Iso", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
272, 113, 60, 22, Form1, ID_Button13, hInst, NULL)
SendMessage(Button13, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button14 AS HANDLE
Const ID_Button14 = 114
Button14 = CreateWindow("button", "Burn", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
272, 162, 36, 22, Form1, ID_Button14, hInst, NULL)
SendMessage(Button14, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Button15 AS HANDLE
Const ID_Button15 = 115
Button15 = CreateWindow("button", "", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
398, 162, 25, 22, Form1, ID_Button15, hInst, NULL)
SendMessage(Button15, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Combo1 AS HANDLE
Const ID_Combo1 = 116
Combo1 = CreateWindow("ComboBox", "", _
WS_CHILD Or WS_VISIBLE Or LBS_STANDARD Or _
CBS_DROPDOWN Or WS_VSCROLL Or WS_TABSTOP, _
7, 217, 96, 100, Form1, ID_Combo1, hInst, NULL)
SendMessage(Combo1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
SendMessage(Combo1, CB_ADDSTRING, 0, "Multi Menu")
SendMessage(Combo1, CB_ADDSTRING, 0, "Single Menu")
SendMessage(Combo1, CB_ADDSTRING, 0, "Sbi2boot")
SendMessage(Combo1, CB_SETCURSEL, 0, 0) 'SiZ! modification (12 nov 06)
'===========================================================================================
Global Edit1 AS HANDLE
Const ID_Edit1 = 117
Edit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", Temp$, _
WS_CHILD Or WS_VISIBLE Or WS_VSCROLL Or ES_MULTILINE,  _
7, 7, 249, 177, Form1, ID_Edit1, hInst, NULL)
SendMessage(Edit1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Edit2 AS HANDLE
Const ID_Edit2 = 118
Edit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", NULL, _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or WS_VSCROLL Or ES_MULTILINE, _
272, 7, 151, 147, Form1, ID_Edit2, hInst, NULL)
SendMessage(Edit2, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
EnableWindow(Edit2, FALSE)
'===========================================================================================
Global Edit3 AS HANDLE
Const ID_Edit3 = 119
Edit3 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", Dxl$[0], _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or ES_AUTOHSCROLL, _
339, 15, 36, 21, Form1, ID_Edit3, hInst, NULL)
SendMessage(Edit3, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Edit4 AS HANDLE
Const ID_Edit4 = 120
Edit4 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", Dxl$[1], _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or ES_AUTOHSCROLL, _
330, 64, 20, 21, Form1, ID_Edit4, hInst, NULL)
SendMessage(Edit4, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Edit5 AS HANDLE
Const ID_Edit5 = 121
Edit5 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "INDUCER", _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or ES_AUTOHSCROLL, _
339, 113, 77, 21, Form1, ID_Edit5, hInst, NULL)
SendMessage(Edit5, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Edit6 AS HANDLE
Const ID_Edit6 = 122
Edit6 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", Dxl$[2], _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or ES_AUTOHSCROLL, _
330, 162, 20, 21, Form1, ID_Edit6, hInst, NULL)
SendMessage(Edit6, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
'===========================================================================================
'Global hIcon1 AS HICON
'hIcon1 = LoadIcon(hInst, MAKEINTRESOURCE(1101))
'SendMessage(Button3, BM_SETIMAGE, IMAGE_ICON, hIcon1)
ApplyIconToButton(hInst, Form1, Button3, 1101)
'===========================================================================================
'Global hIcon2 AS HICON
'hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(1102))
'SendMessage(Button4, BM_SETIMAGE, IMAGE_ICON, hIcon2)
ApplyIconToButton(hInst, Form1, Button4, 1102)
'===========================================================================================
'Global hIcon3 AS HICON
'hIcon3 = LoadIcon(hInst, MAKEINTRESOURCE(1103))
'SendMessage(Button5, BM_SETIMAGE, IMAGE_ICON, hIcon3)
ApplyIconToButton(hInst, Form1, Button5, 1103)
'===========================================================================================
'Global hIcon4 AS HICON
'hIcon4 = LoadIcon(hInst, MAKEINTRESOURCE(1104))
'SendMessage(Button6, BM_SETIMAGE, IMAGE_ICON, hIcon4)
ApplyIconToButton(hInst, Form1, Button6, 1104)
'===========================================================================================
'Global hIcon5 AS HICON
'hIcon5 = LoadIcon(hInst, MAKEINTRESOURCE(1105))
'SendMessage(Button7, BM_SETIMAGE, IMAGE_ICON, hIcon5)
'===========================================================================================
'Global hIcon6 AS HICON
'hIcon6 = LoadIcon(hInst, MAKEINTRESOURCE(1106))
'SendMessage(Button8, BM_SETIMAGE, IMAGE_ICON, hIcon6)
ApplyIconToButton(hInst, Form1, Button8, 1106)
'===========================================================================================
'Global hIcon7 AS HICON
'hIcon7 = LoadIcon(hInst, MAKEINTRESOURCE(1107))
'SendMessage(Button9, BM_SETIMAGE, IMAGE_ICON, hIcon7)
ApplyIconToButton(hInst, Form1, Button9, 1107)
'===========================================================================================
'Global hIcon8 AS HICON
'hIcon8 = LoadIcon(hInst, MAKEINTRESOURCE(1108))
'SendMessage(Button15, BM_SETIMAGE, IMAGE_ICON, hIcon8)
ApplyIconToButton(hInst, Form1, Button15, 1108)
'===========================================================================================
Global List1 AS HANDLE
Const ID_List1 = 132
List1 = CreateWindow("listbox", NULL, _
WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or _
LBS_DISABLENOSCROLL Or WS_VSCROLL, _
274, 9, 147, 150, Form1, ID_List1, hInst, NULL)
SendMessage(List1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0))
SetProp(List1, "LBCB", (HANDLE) SubclassWindow(List1, ListBox_WndProc))
'===========================================================================================
Global Text1 AS HANDLE
Const ID_Text1 = 133
Text1 = CreateWindow("static", "Select Menu Type:", _
WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
6, 200, 90, 13, Form1, ID_Text1, hInst, NULL)
SendMessage(Text1, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Text2 AS HANDLE
Const ID_Text2 = 134
Text2 = CreateWindow("static", "at", _
WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
314, 68, 9, 14, Form1, ID_Text2, hInst, NULL)
SendMessage(Text2, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Text3 AS HANDLE
Const ID_Text3 = 135
Text3 = CreateWindow("static", "x", _
WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
356, 66, 6, 14, Form1, ID_Text3, hInst, NULL)
SendMessage(Text3, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Text4 AS HANDLE
Const ID_Text4 = 136
Text4 = CreateWindow("static", "at", _
WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
314, 166, 9, 14, Form1, ID_Text4, hInst, NULL)
SendMessage(Text4, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(FALSE, 0))
'===========================================================================================
Global Text5 AS HANDLE
Const ID_Text5 = 137
Text5 = CreateWindow("static", "x", _
WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
356, 164, 6, 14, Form1, ID_Text5, hInst, NULL)
SendMessage(Text5, WM_SETFONT, _
GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(FALSE, 0))
'===========================================================================================
CreateImagePropertiesControlPanel(hInst)
'===========================================================================================
ChangeCDRecordVisibilityState(False)

'EnableWindow(Button5, false)

Temp$ = FindFirst$("Sbi\*.*")
While Temp$ <> ""
If Lcase$(Right$(Temp$, 3)) = "sbi" Then
  Temp$ = "[+] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
 End If
 If Lcase$(Right$(Temp$, 3)) = "sbx" Then
  Temp$ = "[_] " & Left$(Temp$, Len(Temp$) - 4)
  SendMessage(List1, LB_ADDSTRING, 0, Temp$)
 End If
Temp$ = FindNext$
Wend
Dxl$[0] = ""
Dxl$[1] = ""
Dxl$[2] = ""
'===========================================================================================
Center(Form1)
Show(Form1)
End Sub

'===========================================================================================
' CONFIGURATION SECTION
'===========================================================================================

'Contains the configuration dialog section

Const ID_dlg_bOK = 401
Const ID_dlg_bCancel = 402
Const ID_dlg_cbxJoliet = 404
Const ID_dlg_cbxRock = 405
Const ID_dlg_cbxIPBIN = 406
Const ID_dlg_eTempDir = 408
Const ID_dlg_bBrowse = 409

Global hCbxJoliet As HANDLE
Global hCbxRock As HANDLE
Global hCbxIPBIN As HANDLE
Global hEdTempDir As HANDLE

'-------------------------------------------------------------------------------------------

'Default configuration if the Tools\config.ini isn't found
Sub ApplyDefaultConfiguration()
	useJoliet = True
	useRock = True
	temporaryDir = GetCorrectPath(GetApplicationPath())
	insertLogo = True
End Sub

'-------------------------------------------------------------------------------------------

'Get the new configuration from the dialog and apply it to the variables
Sub ApplyConfiguration(hDlg As HANDLE)
	useJoliet = (IsDlgButtonChecked(hDlg, ID_dlg_cbxJoliet) == BST_CHECKED)
	useRock = (IsDlgButtonChecked(hDlg, ID_dlg_cbxRock) == BST_CHECKED)
	insertLogo = (IsDlgButtonChecked(hDlg, ID_dlg_cbxIPBIN) == BST_CHECKED)
	temporaryDir = GetCorrectPath(GetText(hEdTempDir))
End Sub

'-------------------------------------------------------------------------------------------

'Save the config to the Tools\config.ini file
Sub SaveConfiguration()
	Open "Tools\config.ini" For Output As F
		If (useJoliet) Then Fprint F, "True" Else Fprint F, "False"
		If (useRock) Then Fprint F, "True" Else Fprint F, "False"
		Fprint F, temporaryDir
		If (insertLogo) Then Fprint F, "True" Else Fprint F, "False"
	Close F
End Sub

'-------------------------------------------------------------------------------------------

'Load the config from the Tools\Config.ini file
Sub LoadConfiguration()
	Dim Buffer$ 'très mal géré les strings en BCX... langage de merde ! impossible de faire un "=" (normal c'est pas géré nativement par le C!)
	Dim TrueStr$
	
	TrueStr$ = "True" 'obligé de faire ça pour comparer des strings...

	'not exists
	If Not Exist("Tools\config.ini") Then
		ApplyDefaultConfiguration() 'apply default config...
		SaveConfiguration() '...and save it
		Exit Sub
	End If
	
	Open "Tools\config.ini" For Input As F
		LINE INPUT F, Buffer$
		'useJoliet = (Buffer$ is TrueStr$) ... dla merde... j'peux pas comparer direct avec "True"...
		'encore plus dla merde... je peux pas faire cette ligne là je dois faire un If...
		If Buffer$ = TrueStr$ Then useJoliet = True Else useJoliet = False
		
		LINE INPUT F, Buffer
		'useRock = (Buffer$ is TrueStr$)
		If Buffer$ = TrueStr$ Then useRock = True Else useRock = False
		
		LINE INPUT F, Buffer$
		temporaryDir = GetCorrectPath(Buffer$)
		
		LINE INPUT F, Buffer$
		'insertLogo = (Buffer$ is TrueStr$)
		If Buffer$ = TrueStr$ Then insertLogo = True Else insertLogo = False
	Close F
	
	'Print "useJoliet : " & useJoliet
	'Print "useRock : " & useRock
	'Print "insertLogo : " & insertLogo
End Sub

'-------------------------------------------------------------------------------------------

'Init the dialog with standard font and create the tool tip, etc...
Sub InitDialogControls(hWndDialog As HWND)
	' retrive controls
	ApplyFont(GetDlgItem(hWndDialog, ID_dlg_bOK))
	ApplyFont(GetDlgItem(hWndDialog, ID_dlg_bCancel))
	ApplyFont(GetDlgItem(hWndDialog, 403))
	hCbxJoliet = GetDlgItem(hWndDialog, ID_dlg_cbxJoliet); ApplyFont(hCbxJoliet)
	hCbxRock = GetDlgItem(hWndDialog, ID_dlg_cbxRock); ApplyFont(hCbxRock)
	
	hCbxIPBIN = GetDlgItem(hWndDialog, ID_dlg_cbxIPBIN); ApplyFont(hCbxIPBIN)
	ToolTip_SetToolTip(hCbxIPBIN, "Insert the " & Chr$(34) & "Tools\iplogo.mr" & Chr$(34) & " in the IP.BIN.")
	
	ApplyFont(GetDlgItem(hWndDialog, 407))
	hEdTempDir = GetDlgItem(hWndDialog, ID_dlg_eTempDir); ApplyFont(hEdTempDir); 
	ToolTip_SetToolTip(hEdTempDir, "All temporary files'll be placed in this directory.")
	
	ApplyFont(GetDlgItem(hWndDialog, 410))
End Sub

'-------------------------------------------------------------------------------------------

'Show the configuration in the dialog
Sub InitConfigurationStateDialog(hDlg As HANDLE)
	If useJoliet Then CheckDlgButton(hDlg, ID_dlg_cbxJoliet, BST_CHECKED)
	If useRock Then CheckDlgButton(hDlg, ID_dlg_cbxRock, BST_CHECKED)
	If insertLogo Then CheckDlgButton(hDlg, ID_dlg_cbxIPBIN, BST_CHECKED)
	SetText(hEdTempDir, temporaryDir)
End Sub

'-------------------------------------------------------------------------------------------

'Configuration Box Handler
Function ConfigBox _
  (hWnd As HWND, Msg As UINT, wParam As WPARAM, lParam As LPARAM) _
  As LRESULT CALLBACK
  
  Select Case Msg

    Case WM_INITDIALOG
		InitDialogControls(hWnd) 'build the dialog
		InitConfigurationStateDialog(hWnd) 'load the configuration from the variables
		
	    Center (hWnd)

    Case WM_COMMAND
		If CBCTL = ID_dlg_bOK Then      'clicked the okay button
		
			If Not Exist(GetText(hEdTempDir)) Then
				MsgBox "NO"
			Else
				ApplyConfiguration(hWnd) 'apply the new config...
				SaveConfiguration() '...and save it
				EndDialog (hWnd, 0) 'close dialog
			End If
			
	    End If

	    If CBCTL = ID_dlg_bCancel Then      'clicked the cancel button
	      EndDialog (hWnd, 0)
	    End If
		
		If CBCTL = ID_dlg_bBrowse Then
			Local tempdir As String
			tempdir = SelectDirectory("Select the new temp directory")
			If Len(tempdir) > 0 Then SetText(hEdTempDir, tempdir)
		End If
		
    Case WM_CLOSE
	    EndDialog (hWnd, 0)
  End Select
  
  Function = 0
End Function

'===========================================================================================
' ABOUT SECTION
'===========================================================================================

Const ID_dlg_about_bOK = 501
Const ID_dlg_about_bSiZ = 502

'About Box Handler
Function AboutBox _
  (hWnd As HWND, Msg As UINT, wParam As WPARAM, lParam As LPARAM) _
  As LRESULT CALLBACK
  
  Select Case Msg

    Case WM_INITDIALOG		
	    Center (hWnd)

    Case WM_COMMAND
		If CBCTL = ID_dlg_about_bOK Then     
			EndDialog (hWnd, 0)
	    End If
		
		If CBCTL = ID_dlg_about_bSiZ Then
			ShellExecute(hWnd, "open", "http://sbibuilder.shorturl.com/", "", "", SW_SHOWNORMAL)
		End If
		
    Case WM_CLOSE
	    EndDialog (hWnd, 0)
  End Select
  
  Function = 0
End Function

'===========================================================================================
' SELFBOOT INDUCER TOOLS SECTION
'===========================================================================================

'Insert a MR file inside a IP.BIN
Function InsertLogoInIPBIN(MRLogo As String, IPBIN As String) As Boolean
	Dim Result As Boolean
	Result = False
	If Exist(IPBIN) And Exist(MRLogo) Then
		Open IPBIN For Binary As Fp1
			Seek Fp1, 14368
			Temp$ = Repeat$(8192, Chr$(0))
			Put$ Fp1, Temp$, 8192
			Seek Fp1, 14368
			Open "Tools\Iplogo.mr" For Binary As Fp2
				Get$ Fp2, Temp$, Lof(MRLogo)
			Close Fp2
			Put$ Fp1, Temp$, Lof(MRLogo)
		Close Fp1
		Result = True
	End If
	Function = Result
End Function

'-------------------------------------------------------------------------------------------

Sub CreateImagePropertiesControlPanel(hInst As HINSTANCE)	
	' --- Create the "Label" edit
	Global IP_Label_Edit AS HANDLE
	Const ID_IP_Label_Edit = 200
	IP_Label_Edit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "INDUCER", _
					WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or ES_AUTOHSCROLL, _
					272, 52, 144, 21, Form1, ID_IP_Label_Edit, hInst, NULL)
	ApplyFont(IP_Label_Edit)
	
	' -- Create the "Generate" button
	Global IP_DJ_Generate_Btn AS HANDLE
	Const ID_IP_DJ_Generate_Btn = 201
	IP_DJ_Generate_Btn = 	CreateWindow("button", "&Generate...", _
							WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
							288, 88, 112, 24, Form1, ID_IP_DJ_Generate_Btn, hInst, NULL)
	ApplyFont(IP_DJ_Generate_Btn)
	
	' -- Create the "Enter the CD label" label (lol !)
	Global IP_EnterCDLabel_Text AS HANDLE
	Const ID_IP_EnterCDLabel_Text = 202
	IP_EnterCDLabel_Text = 	CreateWindow("static", "Please enter the CD label :", _
							WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
							272, 35, 144, 16, Form1, ID_IP_EnterCDLabel_Text, hInst, NULL)
	ApplyFont(IP_EnterCDLabel_Text)
	
	' -- Create the "<Image Type Title> creation" label
	Global IP_ImageTypeTitle_Text AS HANDLE
	Const ID_IP_ImageTypeTitle_Text = 203
	IP_ImageTypeTitle_Text = 	CreateWindow("static", "Image Type Label", _
								WS_CHILD Or WS_VISIBLE Or SS_LEFT, _
								272, 12, 144, 16, Form1, ID_IP_ImageTypeTitle_Text, hInst, NULL)
	ApplyFont(IP_ImageTypeTitle_Text)
	
	' -- Return button
	Global IP_Back_Btn AS HANDLE
	Const ID_IP_Back_Btn = 204
	IP_Back_Btn = 	CreateWindow("button", "", _
					WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_ICON, _
					398, 162, 25, 22, Form1, ID_IP_Back_Btn, hInst, NULL)
	ApplyFont(IP_Back_Btn)
	ApplyIconToButton(hInst, Form1, IP_Back_Btn, 1108)
	
	' -- Nero Group (DAO / TAO)
	Global IP_NeroGroup As HANDLE
	Const ID_IP_NeroGroup = 205
	IP_NeroGroup = 	CreateWindowEx(0, "button", "Image type :", _
					WS_CHILD Or BS_GROUPBOX Or WS_VISIBLE, _
					272, 76, 144, 42, Form1, ID_IP_NeroGroup, hInst, NULL)
	ApplyFont(IP_NeroGroup)
	
	' -- Nero DAO RadioButton
	Global IP_Nero_DAO_RB As HANDLE
	Const ID_IP_Nero_DAO_RB = 206
	IP_Nero_DAO_RB = 	CreateWindow("button", "DAO", WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_AUTORADIOBUTTON, _
						280, 90, 50, 24, Form1, ID_IP_Nero_DAO_RB, hInst, NULL);
	ApplyFont(IP_Nero_DAO_RB)
	CheckDlgButton(Form1, ID_IP_Nero_DAO_RB, BST_CHECKED)
	
	' -- Nero TAO RadioButton
	Global IP_Nero_TAO_RB As HANDLE
	Const ID_IP_Nero_TAO_RB = 207
	IP_Nero_TAO_RB = 	CreateWindow("button", "TAO", WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_AUTORADIOBUTTON, _
						340, 90, 50, 24, Form1, ID_IP_Nero_TAO_RB, hInst, NULL);
	ApplyFont(IP_Nero_TAO_RB)
	
	' -- Create the NERO "Generate" button
	Global IP_NRG_Generate_Btn AS HANDLE
	Const ID_IP_NRG_Generate_Btn = 208
	IP_NRG_Generate_Btn = 	CreateWindow("button", "&Generate...", _
							WS_CHILD Or WS_TABSTOP Or WS_VISIBLE Or BS_PUSHBUTTON, _
							288, 125, 108, 24, Form1, ID_IP_NRG_Generate_Btn, hInst, NULL)
	ApplyFont(IP_NRG_Generate_Btn)
	
	'Hide all created components
	ChangeImagePropertiesVisibilityState(False, False)
	Show(Group2) 'group2 is used in the main screen
End Sub

'-------------------------------------------------------------------------------------------

Sub ChangeImagePropertiesTitleLabel(Title As String)
	SetText(IP_ImageTypeTitle_Text, Title)
End Sub

'-------------------------------------------------------------------------------------------

Sub ChangeImagePropertiesVisibilityState(State As Boolean, IsNero As Boolean)	
	If (State) Then
		Show(Group2); 'main frame
		Show(IP_Label_Edit); Show(IP_EnterCDLabel_Text); 
		Show(IP_ImageTypeTitle_Text);
		Show(IP_Back_Btn); 'Show(hIcon8);
		
		If (IsNero) Then
			Show(IP_NeroGroup); Show(IP_Nero_DAO_RB); 
			Show(IP_Nero_TAO_RB); Show(IP_NRG_Generate_Btn);
		Else
			Show(IP_DJ_Generate_Btn);
		End If
	Else
		Hide(Group2);
		Hide(IP_Label_Edit); Hide(IP_DJ_Generate_Btn);
		Hide(IP_EnterCDLabel_Text); Hide(IP_ImageTypeTitle_Text);
		Hide(IP_Back_Btn); 'Hide(hIcon8); 
		Hide(IP_NeroGroup); 
		Hide(IP_Nero_DAO_RB); Hide(IP_Nero_TAO_RB); Hide(IP_NRG_Generate_Btn);
	End If
End Sub

'-------------------------------------------------------------------------------------------

Sub ChangeCDRecordVisibilityState(State As Boolean)
	If (State) Then 'Show controls
		Show(Button10);	Show(Button11);	Show(Button12);
		Show(Button13);	Show(Button14);	Show(Button15);
		Show(Edit3); Show(Edit4); Show(Edit5); 
		Show(Edit6); Show(Group6); Show(Group7);
		Show(Group8); Show(Group9);	'Show(hIcon8);
		Show(Text2); Show(Text3); Show(Text4);
		Show(Text5);
	Else 'Hide controls
		Hide(Button10);	Hide(Button11);	Hide(Button12);
		Hide(Button13);	Hide(Button14);	Hide(Button15);
		Hide(Edit3); Hide(Edit4); Hide(Edit5); 
		Hide(Edit6); Hide(Group6); Hide(Group7);
		Hide(Group8); Hide(Group9);	'Hide(hIcon8);
		Hide(Text2); Hide(Text3); Hide(Text4);
		Hide(Text5);
	End If
End Sub

'-------------------------------------------------------------------------------------------

'Show or hide the Package ListBox. True = Show, False = Hide
Sub ChangePackagesListVisibilityState(State As Boolean)	
	If (State) Then 'Show Selfboot Inducer controls
		Show(Button1); Show(Button2); Show(Button3);
		Show(Edit2); Show(List1); Show(Group2);
		'Show(hIcon1);
	Else 'Hide controls
		Hide(Button1); Hide(Button2); Hide(Button3);
		Hide(Edit2); Hide(List1); Hide(Group2);
		'Hide(hIcon1);
	End If
End Sub

'-------------------------------------------------------------------------------------------

Sub ResetAllVisibilityState()
	ChangeImagePropertiesVisibilityState(False, False) 'when the first is false the second isn't used but i can't define default values...
	ChangeCDRecordVisibilityState(False)
	ChangePackagesListVisibilityState(False)
End Sub

'===========================================================================================
' GENERAL UTILITIES SECTION
'===========================================================================================

'-------------------------------------------------------------------------------------------

'Browse for folder
Function SelectDirectory(Caption As String) As String
    Local bi As BROWSEINFO
    Local pidlRoot As LPITEMIDLIST
	Local pidlChosen As LPITEMIDLIST
    Local pszBuffer As String
    Local szChosenFolder As String
	szChosenFolder = "\\"
    'Local retval As Integer
    Local hwndf As HWND
	hwndf = NULL
    Local dwFlags As DWORD
    dwFlags	= BIF_RETURNONLYFSDIRS
	Local sz_buf As String
	
    SHGetSpecialFolderLocation(hwndf, CSIDL_DESKTOP, &pidlRoot)

    'memset(&bi, 0, sizeof(BROWSEINFO))
    bi.hwndOwner = hwndf
    bi.pidlRoot = pidlRoot
    bi.pszDisplayName = pszBuffer
    bi.lpszTitle = Caption
    bi.ulFlags = dwFlags

    'retval = 0
	pidlChosen = SHBrowseForFolder(&bi)
    If (pidlChosen <> NULL) Then
 
        If (dwFlags & BIF_BROWSEFORCOMPUTER) Then
            strncat(szChosenFolder, pszBuffer, MAX_PATH - 2)
            'retval = 1
        Else 
			If (SHGetPathFromIDList(pidlChosen, pszBuffer)) Then
	        
	            strncpy(szChosenFolder, pszBuffer, MAX_PATH)
	            'retval = 1
	        End If
		End If
		
    Else
        szChosenFolder = CHR$(0)
	End If

    strncpy(sz_buf, szChosenFolder, MAX_PATH)
    Function = sz_buf
End Function

'-------------------------------------------------------------------------------------------

'correct the path
Function GetCorrectPath(Path As String) As String
	Local i As Integer
	Local LastCharWasSeparator As Boolean
	Local Result As String
	Local PathStr As String
	
	Result = ""
	LastCharWasSeparator = False
	
	PathStr = Path & "\"
	
	For i = 0 to Len(PathStr)
		If MID$(PathStr, i, 1) = "\" Then
			If Not LastCharWasSeparator Then
				Result = Result & MID$(PathStr, i, 1)
				LastCharWasSeparator = True
			End If
		Else
			LastCharWasSeparator = False
			Result = Result & MID$(PathStr, i, 1)
		End If
	Next
	
	Function = Result
End Function

'-------------------------------------------------------------------------------------------

'Apply default font to control
Sub ApplyFont(ToControlHwnd As HWND)
	SendMessage(ToControlHwnd, WM_SETFONT, GetStockObject(DEFAULT_GUI_FONT), _
		MAKELPARAM(FALSE, 0))
End Sub

'-------------------------------------------------------------------------------------------

'get text from a control
Function GetText$(hWnd AS HWND)
	Count = GetWindowTextLength(hWnd)
	GetWindowText(hWnd, Temp$, Count + 1)
	Function = Temp$
End Function

'-------------------------------------------------------------------------------------------

'run a proggy and wait for the end
Function ShellWait(cmd$)
	Dim si As STARTUPINFO
	Dim pi As PROCESS_INFORMATION
	Dim ssi%
	Dim retval%
	ssi% = sizeof(STARTUPINFO)
	ZeroMemory(&si, ssi%)
	si.cb = ssi%
	CreateProcess(NULL, cmd$, 0, 0, 1, 32, 0, NULL, &si, &pi)
	retval% = WaitForSingleObject(pi.hProcess, -1)
	Call GetExitCodeProcess(pi.hProcess, &retval)
	Call CloseHandle(pi.hThread)
	Call CloseHandle(pi.hProcess)
	Function = retval%
End Function

'-------------------------------------------------------------------------------------------

'create a hint object
Function ToolTip_Create(hWnd As HWND) As HWND
	Global hWnd_ToolTip As HWND
	If hWnd_ToolTip = NULL Then
	If hWnd = NULL Then hWnd = GetActiveWindow()
	If hWnd = NULL Then Exit Function
	InitCommonControls()
	hWnd_ToolTip = CreateWindowEx(0, "tooltips_class32", "", TTS_ALWAYSTIP Or 64, _
	0, 0, 0, 0, hWnd, 0, (HWND)GetWindowLong(hWnd,GWL_HINSTANCE), 0)
	End If
	Function = hWnd_ToolTip
End Function

'-------------------------------------------------------------------------------------------

'Assign a hint to a control
Function ToolTip_SetToolTip(hWnd As HWND, Text$)
	Local ti As TOOLINFO
	If ToolTip_Create(GetParent(hWnd)) = 0 Then Exit Function
	ti.cbSize = SIZEOF(ti)
	ti.uFlags = TTF_SUBCLASS Or TTF_IDISHWND
	ti.hwnd = GetParent(hWnd)
	ti.uId = (UINT)hWnd
	If SendMessage(hWnd_ToolTip, TTM_GETTOOLINFO, 0, &ti) Then
	SendMessage(hWnd_ToolTip, TTM_DELTOOL, 0, &ti)
	End If
	ti.cbSize = SIZEOF(ti)
	ti.uFlags = TTF_SUBCLASS Or TTF_IDISHWND
	ti.hwnd = GetParent(hWnd)
	ti.uId = (UINT)hWnd
	ti.lpszText = Text$
	Function = SendMessage(hWnd_ToolTip,TTM_ADDTOOL,0,&ti)
End Function

'-------------------------------------------------------------------------------------------

'Change text from a control
Sub SetText(hWnd As HWND, Temp$)
	SendMessage(hWnd, WM_SETTEXT, 0, Temp$)
End Sub

'-------------------------------------------------------------------------------------------

CONST BLACK 		=	0
CONST DARK_BLUE 	=	1
CONST DARK_GREEN 	=	2
CONST DARK_CYAN 	=	3
CONST DARK_RED 		=	4
CONST DARK_MAGENTA 	=	5
CONST BROWN 		=	6
CONST LIGHT_GRAY	=	7
CONST DARK_GRAY 	=	8
CONST LIGHT_BLUE 	=	9
CONST LIGHT_GREEN 	=	10
CONST LIGHT_CYAN 	=	11
CONST LIGHT_RED 	=	12
CONST LIGHT_MAGENTA =	13
CONST YELLOW 		=	14
CONST WHITE 		=	15

'set the console text color
Sub TextColor(Color As Integer)
	Local bkgnd As Integer
	bkgnd = 0 'black (not really used here)
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), Color + (bkgnd << 4))
End Sub

'-------------------------------------------------------------------------------------------

'Extract the Selfboot Inducer filename from the full application exename
'Function GetApplicationFileName() As String
'	Function = ExtractFileName(GetFullApplicationExeName())
'End Function

'-------------------------------------------------------------------------------------------

'Extract the Selfboot Inducer path from the full application exename
Function GetApplicationPath() As String
	Function = ExtractFilePath(GetFullApplicationExeName())
End Function

'-------------------------------------------------------------------------------------------

'return the Selfboot Inducer full path + exename
Function GetFullApplicationExeName() As String
	Local hModule As HANDLE
	Local ExeName As String
  
	hModule = GetModuleHandle(NULL)
	GetModuleFileName(hModule, ExeName, 256)
	
	Function = ExeName
End Function

'-------------------------------------------------------------------------------------------

'Extract directory from a full path. example : f:\yeah\anti\flag.cool return f:\yeah\anti\
Function ExtractFilePath(FullFileName As String) As String
	Local AppPath As String
	AppPath = MID$(FullFileName, 1, INSTRREV(FullFileName, "\"))
	Function = AppPath
End Function

'-------------------------------------------------------------------------------------------

'Extract filename from a full path. example : f:\yeah\anti\flag.cool return flag.cool
Function ExtractFileName(FullFileName As String) As String
	Local Position As Integer
	Position = INSTRREV(FullFileName, "\")
	Function = MID$(FullFileName, Position + 1, Len(FullFileName) - Position)
End Function

'-------------------------------------------------------------------------------------------

'Checks if the FileName has the "Extension" extension. Please include the dot (.).
Function CorrectTargetFileName(FullFileName As String, Extension As String) As String
	Local SingleName As String
	
	'Print Position & " " & FullFileName
	
	SingleName = LCASE$(ExtractFileName(FullFileName)) 'Extract the filename from FullFileName
	Extension = LCASE$(Extension)
		
	If InStr(SingleName, Extension) = 0 Then 
		Function = FullFileName & Extension 'Add the extension. dont forget the DOT in the function CALL !
	Else
		Function = FullFileName
	End If
End Function

'-------------------------------------------------------------------------------------------

' GRAPHICAL BUTTONS MANAGING SECTION

Const BITMAP_RESOURCE_MASK_VALUE = 20000 'each mask has a resource ID equals at 20000 + ImageID

'Apply Icon on Windows 95/98/ME/NT/2K or bitmap and his mask (XP only and maybe Vista) to a button.
Sub ApplyIconToButton(hAppliInst As HINSTANCE, hParentForm As HANDLE, hButton As HANDLE, ImageID As Integer)
	If Not IsWindowsXP() Then
		SendMessage(hButton, BM_SETIMAGE, IMAGE_ICON, LoadIcon(hAppliInst, MAKEINTRESOURCE(ImageID))) 'burnerO old style
		Exit Sub
	End If
	
	'New style : XP buttons with Icons (if you don't like it, you can delete the MANIFEST line from the resource file (sbinducr.rc)
	'and delete the above code, but don't forget to remove the IsWindowsXP() function too)
	
	'Create the ImageList : ImageList is a windows object allowing you to manage graphical resources (such icons, bitmap...).
	Local m_ImageList As HIMAGELIST 'here it's the ImageList
	Local Button_ImageList As BUTTON_IMAGELIST 'A Button_ImageList is a structure to associate an ImageList to a object.
	
	m_ImageList = ImageList_Create(32, 32, ILC_COLOR32 Or ILC_MASK, 0, 1) 'Create the image list
	
	'Add the ImageID and the associated mask
	ImageList_Add(m_ImageList, LoadBitmap(hAppliInst, MAKEINTRESOURCE(ImageID)), _
		LoadBitmap(hAppliInst, MAKEINTRESOURCE(ImageID + BITMAP_RESOURCE_MASK_VALUE)))
	
	'Parameters for the ImageList
	Button_ImageList.himl = m_ImageList 'associate the imagelist to the Button_ImageList
	Button_ImageList.uAlign = BUTTON_IMAGELIST_ALIGN_CENTER 'center icon
	Button_ImageList.margin.top = 1
	Button_ImageList.margin.bottom = 1
	Button_ImageList.margin.left = 1
	Button_ImageList.margin.right = 1

	Button_SetImageList(hButton, &Button_ImageList) 'set the Button_ImageList object to the button
		
	'Resize the button
	Local sizeBtn As SIZE 'struct to get the ideal size of a button
	Local rectBtn As RECT
	
	Button_GetIdealSize(hButton, &sizeBtn)
	rectBtn = GetWindowPos(hButton) 'Get the current left and top position of the button
	SetWindowPos(hButton, hParentForm, rectBtn.left, rectBtn.top, sizeBtn.cx, sizeBtn.cy, _
		SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE)
End Sub

'-------------------------------------------------------------------------------------------

'Destroy the ImageList associated to a button
Sub DestroyThemedButton(hButton As HANDLE)
	Local himl As PBUTTON_IMAGELIST
	If Button_GetImageList(hButton, himl) Then ImageList_Destroy(himl)
End Sub

'-------------------------------------------------------------------------------------------

'Retrive the RECT of a windowed control
Function GetWindowPos(hControl As HANDLE) As RECT
	Local hGlobal As HGLOBAL
	Local lpWndPlacement As PWINDOWPLACEMENT
	Local Result As RECT
	
	'Reservation de mémoire.
	hGlobal = GlobalAlloc(GHND, SizeOf(WINDOWPLACEMENT))
	lpWndPlacement = GlobalLock(hGlobal)
	
	'Initialisation de la structure.
	lpWndPlacement->length = SizeOf(WINDOWPLACEMENT)
	
	'Appel de la fonction.
	GetWindowPlacement(hControl, lpWndPlacement)
	
	'Copie de la valeur de retour
	Result.left = lpWndPlacement->rcNormalPosition.left
	Result.top = lpWndPlacement->rcNormalPosition.top
	Result.right = lpWndPlacement->rcNormalPosition.right
	Result.bottom = lpWndPlacement->rcNormalPosition.bottom
		
	'Destruction de notre buffer
	If (hGlobal) Then GlobalFree(hGlobal)
	
	Function = Result
End Function

'-------------------------------------------------------------------------------------------------------

'Is the host Windows >= XP ? (in order to apply the theme because on Windows 98 at 2000 it's buggy)
Function IsWindowsXP() As Boolean
	Local hGlobal As HGLOBAL
	Local POSInfo As POSVERSIONINFO
	Local IsXP As Boolean
	
	hGlobal = GlobalAlloc(GHND, SizeOf(OSVERSIONINFO))
	POSInfo = GlobalLock(hGlobal)
	
	POSInfo->dwOSVersionInfoSize = SizeOf(OSVERSIONINFO)
	GetVersionExA(POSInfo)
	
	IsXP = False
	If (POSInfo->dwPlatformId = 2) Then If POSInfo->dwMajorVersion = 5 Then If POSInfo->dwMinorVersion > 0 Then IsXP = True
		
	If (hGlobal) Then GlobalFree(hGlobal)
	
	Function = IsXP
End Function

'===========================================================================================