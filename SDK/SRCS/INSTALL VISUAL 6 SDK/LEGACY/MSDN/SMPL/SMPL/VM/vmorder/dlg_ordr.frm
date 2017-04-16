VERSION 5.00
Begin VB.Form dlg_OrderRow 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Order Row"
   ClientHeight    =   4305
   ClientLeft      =   1320
   ClientTop       =   1575
   ClientWidth     =   4305
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4305
   ScaleWidth      =   4305
   Begin VB.CommandButton btn_cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   3660
      Width           =   1095
   End
   Begin VB.CommandButton btn_ok 
      Caption         =   "Ok"
      Height          =   375
      Left            =   3000
      TabIndex        =   4
      Top             =   3660
      Width           =   1095
   End
   Begin VB.TextBox txt_quantity 
      Height          =   285
      Left            =   240
      TabIndex        =   1
      Top             =   3660
      Width           =   1215
   End
   Begin VB.PictureBox Frame3D1 
      BackColor       =   &H00C0C0C0&
      Height          =   3195
      Left            =   120
      ScaleHeight     =   3135
      ScaleWidth      =   4035
      TabIndex        =   11
      Top             =   120
      Width           =   4095
      Begin VB.TextBox txt_article_id 
         Height          =   285
         Left            =   120
         TabIndex        =   14
         Top             =   300
         Width           =   1815
      End
      Begin VB.ComboBox lst_article 
         BackColor       =   &H00FFFFFF&
         Height          =   300
         Left            =   120
         TabIndex        =   12
         Top             =   960
         Width           =   2775
      End
      Begin VB.Label Label4 
         BackStyle       =   0  'Transparent
         Caption         =   "Article Id"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   60
         Width           =   1695
      End
      Begin VB.Label Label6 
         BackStyle       =   0  'Transparent
         Caption         =   "Price"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   2580
         Width           =   1695
      End
      Begin VB.Label txt_price 
         BorderStyle     =   1  'Fixed Single
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   2820
         Width           =   1815
      End
      Begin VB.Label Label5 
         BackStyle       =   0  'Transparent
         Caption         =   "Description"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   1980
         Width           =   1695
      End
      Begin VB.Label txt_description 
         BorderStyle     =   1  'Fixed Single
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   2220
         Width           =   3735
      End
      Begin VB.Label Label3 
         BackStyle       =   0  'Transparent
         Caption         =   "Article Name"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   720
         Width           =   1695
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "In Stock"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   1380
         Width           =   1935
      End
      Begin VB.Label txt_stock 
         BorderStyle     =   1  'Fixed Single
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   1620
         Width           =   1215
      End
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "Quantity"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   3420
      Width           =   2055
   End
End
Attribute VB_Name = "dlg_OrderRow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CC02C8"
'Actual object will be passed by the Edit operation
'##ModelId=3237F8CC00DD
Private My_Orderrow As OrderRow
'The set of accessable articles
'##ModelId=3237F8CC0110
Private My_Articles As New Articles


'##ModelId=3237F8CC02C9
Public Sub Edit(The_Orderrow As OrderRow)
    'Pass the object to edit to a local variable
    Set My_Orderrow = The_Orderrow
    'Edit it
    Me.Show 1
    'Grab the result
    Set The_Orderrow = My_Orderrow
    'Close the dialog
    Unload Me
End Sub


'##ModelId=3237F8CC02CB
Private Sub btn_cancel_Click()
    'pass the cancel user command as a zero quantity
    My_Orderrow.Quantity = 0
    Me.Hide
End Sub

'##ModelId=3237F8CC02F8
Private Sub btn_ok_Click()
    On Error GoTo dlg_order_row__ok_click_err
    My_Orderrow.Quantity = CVar(txt_quantity.Text)
    Set My_Orderrow.Article = My_Articles.Item(lst_article.ListIndex + 1)
    Me.Hide
    Exit Sub
dlg_order_row__ok_click_err:
    Resume dlg_order_row__ok_click_end
dlg_order_row__ok_click_end:
    My_Orderrow.Quantity = 0
End Sub

'##ModelId=3237F8CC02F9
Private Sub Form_Load()
    Dim temp As Article
    Dim index
    'check if the articles are loded from the article db
    If My_Articles.Count = 0 Then
        'Grab all the articles
        My_Articles.Fetch
    End If
    Update_Form
End Sub

'##ModelId=3237F8CC02FA
Private Sub lst_article_Click()
    txt_article_id.Text = My_Articles.Item(lst_article.ListIndex + 1).ArticleId
    txt_stock.Caption = My_Articles.Item(lst_article.ListIndex + 1).Quantity
    txt_description.Caption = My_Articles.Item(lst_article.ListIndex + 1).Description
    txt_price.Caption = Format(My_Articles.Item(lst_article.ListIndex + 1).Price, "$#.#0")
End Sub


'##ModelId=3237F8CC02FB
Private Sub Update_Form()
    'clear the list box
    lst_article.Clear
    'Move the articles into the dialog.
    'Item is indexed 1..Count
    For index = 1 To My_Articles.Count
        lst_article.AddItem My_Articles.Item(index).Name
    Next
    If lst_article.ListCount > 0 Then
        lst_article.ListIndex = 0
    End If
End Sub


'##ModelId=3237F8CC02FC
Private Sub lst_article_KeyPress(KeyAscii As Integer)
    'Trap RETURN
    If KeyAscii = 13 Then
        'Grab all the articles
        My_Articles.Fetch Name:=lst_article.Text
        Update_Form
    End If
End Sub

'##ModelId=3237F8CC02FE
Private Sub txt_article_id_KeyPress(KeyAscii As Integer)
    'Trap RETURN
    If KeyAscii = 13 Then
        'Grab all the articles
        My_Articles.Fetch Id:=txt_article_id.Text
        Update_Form
    End If
End Sub


