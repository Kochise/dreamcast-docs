VERSION 4.00
Begin VB.Form frmTray 
   Caption         =   "MSJ Shell_NotifyIcon Demo"
   ClientHeight    =   1785
   ClientLeft      =   3240
   ClientTop       =   3795
   ClientWidth     =   4245
   Height          =   2220
   Left            =   3180
   LinkTopic       =   "Form1"
   ScaleHeight     =   1785
   ScaleWidth      =   4245
   Top             =   3420
   Width           =   4365
   Begin VB.PictureBox Picture2 
      Height          =   1575
      Left            =   120
      ScaleHeight     =   1515
      ScaleWidth      =   1635
      TabIndex        =   5
      Top             =   120
      Width           =   1695
      Begin VB.CommandButton btnCreate 
         Caption         =   "Create"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   120
         Width           =   1335
      End
      Begin VB.CommandButton btnIcon 
         Caption         =   "New Icon"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   600
         Width           =   1335
      End
      Begin VB.CommandButton btnTip 
         Caption         =   "New Tip"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   1080
         Width           =   1335
      End
   End
   Begin VB.PictureBox Picture1 
      Height          =   1575
      Left            =   1920
      ScaleHeight     =   1515
      ScaleWidth      =   2115
      TabIndex        =   1
      Top             =   120
      Width           =   2175
      Begin VB.PictureBox picIcon 
         Height          =   855
         Left            =   120
         ScaleHeight     =   795
         ScaleWidth      =   915
         TabIndex        =   4
         Top             =   120
         Width           =   975
      End
      Begin VB.CommandButton btnLoad 
         Caption         =   "Load..."
         Height          =   375
         Left            =   1200
         TabIndex        =   3
         Top             =   360
         Width           =   735
      End
      Begin VB.TextBox edtTip 
         Height          =   285
         Left            =   120
         TabIndex        =   2
         Text            =   "Text1"
         Top             =   1080
         Width           =   1815
      End
   End
   Begin MSComDlg.CommonDialog ComDlg 
      Left            =   1560
      Top             =   480
      _Version        =   65536
      _ExtentX        =   847
      _ExtentY        =   847
      _StockProps     =   0
   End
   Begin CbackLib.CallBack CBWnd 
      Height          =   735
      Left            =   1560
      TabIndex        =   0
      Top             =   960
      Width           =   855
      _version        =   65536
      _extentx        =   1508
      _extenty        =   1296
      _stockprops     =   0
   End
End
Attribute VB_Name = "frmTray"
Attribute VB_Creatable = False
Attribute VB_Exposed = False

'====================================================
' When the user clicks on the Create button, do this

Private Sub btnCreate_Click()
    Dim tnd As NOTIFYICONDATA ' The Shell_NotifyIcon data structure

	' Alternate between Create and Delete handling
    If btnCreate.Caption = "Create" Then
		' Fill in tnd with appropriate values
        tnd.szTip = edtTip.Text & Chr$(0)
		' Flags: the message, icon, and tip are valid and should be
		' paid attention to.
        tnd.uFlags = NIF_MESSAGE + NIF_ICON + NIF_TIP
        tnd.uID = 100
        tnd.cbSize = Len(tnd)
		' The window handle of our callback control
        tnd.hwnd = CBWnd.hwnd
		' The message CBWnd will receive when there's an icon event
        tnd.uCallbackMessage = WM_USER + 1
        tnd.hIcon = picIcon.Picture
		' Make the callback window wait for our defined message
        CBWnd.WatchMsg (WM_USER + 1)
		' Add the icon to the taskbar tray
        rc = Shell_NotifyIcon(NIM_ADD, tnd)
		' Flip the button's name
        btnCreate.Caption = "Remove"
    ElseIf btnCreate.Caption = "Remove" Then
		' On remove, we only have to give enough information for Windows
		' to locate the icon, then tell the system to delete it.
        tnd.uID = 100
        tnd.cbSize = Len(tnd)
        tnd.hwnd = CBWnd.hwnd
        tnd.uCallbackMessage = WM_USER + 1
        rc = Shell_NotifyIcon(NIM_DELETE, tnd)
		' Ready to create a new one!
        btnCreate.Caption = "Create"
    End If
End Sub


'=========================================
' btnIcon changes the icon in the tray

Private Sub btnIcon_Click()
    Dim tnd As NOTIFYICONDATA

	' Fill the data structure with necessary information, including
	' the icon we get from the form's picture box
    tnd.uFlags = NIF_ICON
    tnd.uID = 100
    tnd.cbSize = Len(tnd)
    tnd.hwnd = CBWnd.hwnd
    tnd.uCallbackMessage = WM_USER + 1
    tnd.hIcon = picIcon.Picture

	' Call the modify part of the function to change the elements indicated
	' by the uFlags Type member above - in this case, just the icon.
    rc = Shell_NotifyIcon(NIM_MODIFY, tnd)
End Sub


'=========================================
' btnLoad shows the Open common dialog, then retrieves the chosen filename
' and tries to load a picture from it. This can be an icon or an appropriately
' bitmap.

Private Sub btnLoad_Click()
    ComDlg.ShowOpen
    picIcon.Picture = LoadPicture(ComDlg.filename)
End Sub

'=========================================
' btnTip changes the Tip property of the icon, similar to the btnIcon
' changing the icon.

Private Sub btnTip_Click()
    Dim tnd As NOTIFYICONDATA

	' The tip is going to be important
    tnd.uFlags = NIF_TIP
    tnd.uID = 100
    tnd.cbSize = Len(tnd)
    tnd.hwnd = CBWnd.hwnd
    tnd.uCallbackMessage = WM_USER + 1

	' Get the new tip from the onscreen edit box. This has to have a null
	' character appended to it or the tip will appear as a string with as
	' many trailing spaces as there are in the fixed-length string.

    tnd.szTip = edtTip.Text & Chr$(0)

    rc = Shell_NotifyIcon(NIM_MODIFY, tnd)
End Sub

'=========================================
' CBWnd_CallBack is called by the Cback control any time it receives
' a window message specified by a previous WatchMsg call to it. It
' provides the VB programmer the original msg/wParam/lParam intact. (These
' may at times be pointers to values instead of actual values; it is up to
' the programmer to know when this will occur and adjust his code accordingly.

Private Sub CBWnd_CallBack(ByVal msg As Integer, ByVal wParam As Long, ByVal lParam As Long)
	' If the user has pressed the mouse button on the icon, pop up a message box
    If (lParam = WM_LBUTTONDOWN) Then
        MsgBox "You clicked on the tray icon!", vbOKOnly, "Shell_NotifyIcon callback"
    End If
End Sub

'============================================================
' The basic Form_Load - this provides a default icon and string
' for the VB program to set the tray icon.

Private Sub Form_Load()
    edtTip.Text = "Generic tip string."
    picIcon.Picture = Me.Icon
End Sub
