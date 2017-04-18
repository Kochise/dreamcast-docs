VERSION 4.00
Begin VB.Form frmNetGet 
   Caption         =   "NetGet"
   ClientHeight    =   4020
   ClientLeft      =   3840
   ClientTop       =   2055
   ClientWidth     =   8385
   Height          =   4425
   Icon            =   "FNetGet.frx":0000
   Left            =   3780
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   4020
   ScaleWidth      =   8385
   Top             =   1710
   Width           =   8505
   Begin VB.DirListBox dirMain 
      Height          =   2055
      Left            =   2640
      TabIndex        =   12
      Top             =   1080
      Visible         =   0   'False
      Width           =   2040
   End
   Begin VB.DriveListBox drvMain 
      Height          =   315
      Left            =   240
      TabIndex        =   11
      Top             =   1080
      Visible         =   0   'False
      Width           =   2295
   End
   Begin VB.ListBox lstFiles 
      Height          =   2205
      Left            =   4800
      Sorted          =   -1  'True
      TabIndex        =   10
      Top             =   1080
      Width           =   2040
   End
   Begin VB.ListBox lstImages 
      Height          =   2205
      Left            =   2640
      Sorted          =   -1  'True
      TabIndex        =   8
      Top             =   1080
      Width           =   2040
   End
   Begin VB.ListBox lstReferences 
      Height          =   2205
      Left            =   240
      Sorted          =   -1  'True
      TabIndex        =   7
      Top             =   1080
      Width           =   2295
   End
   Begin VB.TextBox txtRawHTML 
      Height          =   735
      Left            =   7200
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   4
      Top             =   1200
      Visible         =   0   'False
      Width           =   555
   End
   Begin VB.CommandButton btExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   6960
      TabIndex        =   2
      Top             =   120
      Width           =   1000
   End
   Begin VB.CommandButton btSaveFile 
      Caption         =   "&Save File"
      Height          =   375
      Left            =   5820
      TabIndex        =   1
      Top             =   120
      Width           =   1000
   End
   Begin VB.CommandButton btGetURL 
      Caption         =   "Read &URL"
      Height          =   375
      Left            =   4740
      TabIndex        =   0
      Top             =   120
      Width           =   1000
   End
   Begin VB.TextBox txtUrl 
      Height          =   375
      Left            =   660
      TabIndex        =   3
      Text            =   "http://www.microsoft.com"
      Top             =   120
      Width           =   3915
   End
   Begin ComctlLib.StatusBar sbrMain 
      Align           =   2  'Align Bottom
      Height          =   495
      Left            =   0
      TabIndex        =   9
      Top             =   3525
      Width           =   8385
      _Version        =   65536
      _ExtentX        =   14790
      _ExtentY        =   873
      _StockProps     =   68
      AlignSet        =   -1  'True
      SimpleText      =   ""
      i1              =   "FNetGet.frx":0442
   End
   Begin ComctlLib.TabStrip tabViews 
      Height          =   2775
      Left            =   120
      TabIndex        =   6
      Top             =   600
      Width           =   7995
      _Version        =   65536
      _ExtentX        =   14102
      _ExtentY        =   4895
      _StockProps     =   68
      ImageList       =   ""
      NumTabs         =   3
      i1              =   "FNetGet.frx":0577
      i2              =   "FNetGet.frx":06EA
      i3              =   "FNetGet.frx":0841
   End
   Begin VB.Label lblURL 
      Caption         =   "URL :"
      Height          =   195
      Left            =   180
      TabIndex        =   5
      Top             =   180
      Width           =   435
   End
End
Attribute VB_Name = "frmNetGet"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Declare Function SendMessageFind Lib "user32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Integer, ByVal lParam As String) As Long

Private Const LB_ERR = (-1)
Private Const LB_FINDSTRING = &H18F
Private Const icSpacer = 120    ' 120 twips spacer between controls
Private Const scBlankStr = ""

Dim objNetGet       As New CNetGet
Dim colReferences   As New Collection
Dim colImages       As New Collection
Dim vReference      As Variant
Dim sHost           As String
Dim sUrl            As String

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btExit_Click
' Purpose    : click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Terminates instance of CNetGet and frees collections
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btExit_Click()
objNetGet.Term
Set objNetGet = Nothing
Set frmNetGet = Nothing
Unload Me
End
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btGetURL_Click
' Purpose    : click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Reads URL and parses references and images from the html page
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btGetURL_Click()
Dim iEndPos As Integer
iEndPos = InStr(8, txtURL, "/")
If CBool(iEndPos) Then
    sHost = Mid$(txtURL, 1, iEndPos - 1)
Else
    sHost = Mid$(txtURL, 1, Len(txtURL))
End If
sUrl = txtURL
Set colReferences = Nothing
Set colImages = Nothing
If Len(txtURL) Then
    If objNetGet.ReadUrl(txtURL) Then
        If objNetGet.ParseHTML("A HREF=""", colReferences, """>?#") Then AddReferences
        If objNetGet.ParseHTML("SRC=""", colImages) Then AddImages
        AddRawHTML
    Else
        MsgBox "Error: " & objNetGet.GetLastError
    End If
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : btSaveFile_Click
' Purpose    : click event for button
' Parameters : NA
' Return val : NA
' Algorithm  : Saves files specified in lstFiles listbox control
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub btSaveFile_Click()
Dim sOutFileName As String
sOutFileName = dirMain
If Not Right$(dirMain, 1) = "\" Then sOutFileName = sOutFileName & "\"
Do While CBool(lstFiles.ListCount)
    lstFiles.ListIndex = 0
    objNetGet.ReadUrl lstFiles.List(0), sOutFileName & FileNameURL(lstFiles.List(0))
    lstFiles.RemoveItem (0)
Loop
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : drvMain_Change
' Purpose    : change event for drive control
' Parameters : NA
' Return val : NA
' Algorithm  : sets the dir control path to the drive
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub drvMain_Change()
dirMain.Path = drvMain.Drive    ' When drive changes, set directory path.
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Form_Load
' Purpose    : form load event
' Parameters : NA
' Return val : NA
' Algorithm  : Initializes object, centers form, then sets the status window property
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Load()
objNetGet.Init
CenterForm Me
objNetGet.SetStatusWindow = sbrMain.Panels(1)
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : Form_Resize
' Purpose    : resize event of form
' Parameters : NA
' Return val : NA
' Algorithm  : calculates new sizes for controls on form
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub Form_Resize()
On Error Resume Next
tabViews.Move icSpacer, 600, Me.ScaleWidth - 2 * icSpacer, Me.ScaleHeight - 1200
lstReferences.Move icSpacer * 2, lstReferences.Top, (Me.ScaleWidth - 6 * icSpacer) / 3, tabViews.Height - 500
lstImages.Move (lstReferences.Width + 3 * icSpacer), lstImages.Top, lstReferences.Width, lstReferences.Height
lstFiles.Move ((lstReferences.Width * 2) + 4 * icSpacer), lstFiles.Top, lstReferences.Width, lstReferences.Height
txtURL.Move txtURL.Left, txtURL.Top, Me.ScaleWidth - 8 * icSpacer - lblURL.Width - 3 * btGetURL.Width
txtRawHTML.Move lstReferences.Left, lstReferences.Top, lstReferences.Width * 3 + 2 * icSpacer, lstReferences.Height
drvMain.Move icSpacer * 2, lstReferences.Top, (Me.ScaleWidth - 6 * icSpacer) / 3
dirMain.Move (lstReferences.Width + 3 * icSpacer), lstImages.Top, lstReferences.Width, lstReferences.Height
btGetURL.Move txtURL.Left + txtURL.Width + icSpacer
btSaveFile.Move btGetURL.Left + btGetURL.Width + icSpacer
btExit.Move btSaveFile.Left + btSaveFile.Width + icSpacer
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : lstFiles_DBlClick
' Purpose    : double click event of listbox control
' Parameters : NA
' Return val : NA
' Algorithm  : removes item from the lstFiles listbox control
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub lstFiles_DBlClick()
    lstFiles.RemoveItem (lstFiles.ListIndex)
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : lstImages_DBlClick
' Purpose    : double click event of listbox control
' Parameters : NA
' Return val : NA
' Algorithm  : adds file to listbox after adjusting for relative or absolute URL
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub lstImages_DBlClick()
Dim sImage As String
Dim sUrlPath As String
sImage = lstImages.List(lstImages.ListIndex)
If InStr(1, sImage, "http://") Then
    AddFile sImage
Else
    If CBool(Left$(sImage, 1) = "/") Then
        AddFile sHost & sImage
    Else
        If CBool(InStr(1, sUrl, ".htm")) Then
            sUrlPath = FilePathURL(sUrl)
        Else
            sUrlPath = sUrl
        End If
        If CBool(Right$(sUrlPath, 1) = "/") Then
            AddFile sUrlPath & sImage
        Else
            AddFile sUrlPath & "/" & sImage
        End If
    End If
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : lstReferences_DblClick
' Purpose    : double click event of listbox control
' Parameters : NA
' Return val : NA
' Algorithm  : places reference in textbox  after checking for absolute or relative URL
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub lstReferences_DblClick()
Dim sRef As String
Dim sUrlPath As String
sRef = lstReferences.List(lstReferences.ListIndex)
If InStr(1, sRef, "http://") Then
    txtURL = sRef
Else
    If CBool(Left$(sRef, 1) = "/") Then
        txtURL = sHost & sRef
    Else
        If CBool(InStr(1, sUrl, ".htm")) Then
            sUrlPath = FilePathURL(sUrl)
        Else
            sUrlPath = sUrl
        End If
        If CBool(Right$(sUrl, 1) = "/") Then
            txtURL = sUrl & sRef
        Else
            txtURL = sUrl & "/" & sRef
        End If
    End If
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : tabViews_Click
' Purpose    : click event of tabstrip control
' Parameters : NA
' Return val : NA
' Algorithm  : toggles between view of listbox and textbox controls
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub tabViews_Click()
Select Case tabViews.SelectedItem.Index
    Case 1:
        txtRawHTML.Visible = False
        lstReferences.Visible = True
        lstImages.Visible = True
        lstFiles.Visible = True
        drvMain.Visible = False
        dirMain.Visible = False
    Case 2:
        txtRawHTML.Visible = True
        lstReferences.Visible = False
        lstImages.Visible = False
        lstFiles.Visible = False
        drvMain.Visible = False
        dirMain.Visible = False
    Case 3:
        txtRawHTML.Visible = False
        lstReferences.Visible = False
        lstImages.Visible = False
        lstFiles.Visible = False
        drvMain.Visible = True
        dirMain.Visible = True
End Select
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : AddFile
' Purpose    : Adds files to listbox control
' Parameters : string to add
' Return val : NA
' Algorithm  : If item already added the index is set to that item, else item is added
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub AddFile(ByVal sFile As String)
Dim lRetVal As Long
lRetVal = SendMessageFind(lstFiles.hWnd, LB_FINDSTRING, 0, (sFile))
If lRetVal = LB_ERR Then
    lstFiles.AddItem sFile
Else
    lstFiles.ListIndex = lRetVal
End If
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : CenterForm
' Purpose    : Used for centering form on screen
' Parameters : the form you would like to center
' Return val : NA
' Algorithm  : moves the form to center of screen after calculating position
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub CenterForm(theForm As Form)
Dim iLeft   As Integer
Dim iTop    As Integer
iLeft = (Screen.Width - theForm.Width) / 2
iTop = (Screen.Height - theForm.Height) / 2
If (iLeft < 0) Then iLeft = 0
If (iTop < 0) Then iTop = 0
theForm.Move iLeft, iTop
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : FileNameURL
' Purpose    : Returns the 8.3 file name after stripping off the path
' Parameters : URL
' Return val : filename
' Algorithm  : returns piece of string from last whack until end
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function FileNameURL(ByVal sFPath As String) As String
Dim iLastSlash  As Integer
Dim i           As Integer
On Error Resume Next
iLastSlash = 0
Do
    i = InStr(iLastSlash + 1, sFPath, "/")
    If (i <> 0) Then
        iLastSlash = i
    End If
Loop While (i <> 0)
FileNameURL = Right(RTrim(sFPath), Len(RTrim(sFPath)) - iLastSlash)
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : FilePathURL
' Purpose    : Returns the path to a file after stripping off the 8.3 file name
' Parameters : URL
' Return val : path
' Algorithm  : returns piece of string from eginning of string to last whack
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function FilePathURL(ByVal sFPath As String) As String
Dim iLastSlash  As Integer
Dim i           As Integer
On Error Resume Next
sFPath = Trim$(sFPath)
iLastSlash = 0
Do
    i = InStr(iLastSlash + 1, sFPath, "/")
    If (i <> 0) Then
        iLastSlash = i
    End If
Loop While (i <> 0)
FilePathURL = Left$(sFPath, iLastSlash)
End Function

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : AddImages
' Purpose    : Adds images to list box from the colImages collection
' Parameters : NA
' Return val : NA
' Algorithm  : Iterates through the collection and adds items to the listbox
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub AddImages()
lstImages.Clear
For Each vReference In colImages
    lstImages.AddItem vReference
Next vReference
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : AddRawHTML
' Purpose    : Copies portion objNetGet buffer to a textbox control
' Parameters : NA
' Return val : NA
' Algorithm  : Copies the object's HTML buffer to a textbox control
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub AddRawHTML()
txtRawHTML = scBlankStr
' buffer is truncated if it is longer than 60000 bytes.
txtRawHTML = Mid$(objNetGet.GetRawHTML, 1, 60000)
End Sub

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Name       : AddReferences
' Purpose    : Adds references to list box from the colReferences collection
' Parameters : NA
' Return val : NA
' Algorithm  : Iterates through the collection add adds items to the listbox
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub AddReferences()
lstReferences.Clear
For Each vReference In colReferences
    lstReferences.AddItem vReference
Next vReference
End Sub
