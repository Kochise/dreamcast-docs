VERSION 5.00
Begin VB.Form dlg_Order 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Order"
   ClientHeight    =   5160
   ClientLeft      =   390
   ClientTop       =   1980
   ClientWidth     =   5265
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Dlg_orde.frx":0000
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5160
   ScaleWidth      =   5265
   Begin VB.PictureBox Frame3D1 
      BackColor       =   &H00C0C0C0&
      Height          =   1575
      Left            =   120
      ScaleHeight     =   1515
      ScaleWidth      =   4875
      TabIndex        =   10
      Top             =   840
      Width           =   4935
      Begin VB.ComboBox lst_Customer_Name 
         BackColor       =   &H00FFFFFF&
         Height          =   315
         Left            =   120
         TabIndex        =   16
         Top             =   420
         Width           =   2655
      End
      Begin VB.TextBox txt_Customer_Id 
         Height          =   285
         Left            =   2880
         TabIndex        =   15
         Top             =   420
         Width           =   1815
      End
      Begin VB.TextBox txt_customer_address 
         BackColor       =   &H00C0C0C0&
         Height          =   285
         Left            =   120
         TabIndex        =   11
         Top             =   1080
         Width           =   4575
      End
      Begin VB.Label Label3 
         BackStyle       =   0  'Transparent
         Caption         =   "Name"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   180
         Width           =   1335
      End
      Begin VB.Label Label4 
         BackStyle       =   0  'Transparent
         Caption         =   "Customer Id"
         Height          =   255
         Left            =   2880
         TabIndex        =   13
         Top             =   180
         Width           =   1335
      End
      Begin VB.Label Label5 
         BackStyle       =   0  'Transparent
         Caption         =   "Address"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   840
         Width           =   1335
      End
   End
   Begin VB.CommandButton btn_cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2880
      TabIndex        =   7
      Top             =   4560
      Width           =   975
   End
   Begin VB.CommandButton btn_ok 
      Caption         =   "&Ok"
      Height          =   375
      Left            =   3960
      TabIndex        =   9
      Top             =   4560
      Width           =   975
   End
   Begin VB.TextBox txt_sum 
      BackColor       =   &H00C0C0C0&
      Height          =   285
      Left            =   240
      TabIndex        =   3
      Top             =   4680
      Width           =   1575
   End
   Begin VB.TextBox txt_order_id 
      Height          =   285
      Left            =   240
      TabIndex        =   1
      Top             =   300
      Width           =   1815
   End
   Begin VB.PictureBox Frame3D2 
      BackColor       =   &H00C0C0C0&
      DrawStyle       =   5  'Transparent
      Height          =   1815
      Left            =   120
      ScaleHeight     =   1755
      ScaleWidth      =   4875
      TabIndex        =   0
      Top             =   2520
      Width           =   4935
      Begin VB.ListBox lst_order_rows 
         BackColor       =   &H00C0C0C0&
         Height          =   645
         Left            =   120
         TabIndex        =   5
         Top             =   120
         Width           =   4695
      End
      Begin VB.CommandButton btn_new 
         Caption         =   "&New"
         Height          =   375
         Left            =   3840
         TabIndex        =   6
         Top             =   1320
         Width           =   975
      End
      Begin VB.CommandButton btn_remove 
         Caption         =   "&Remove"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2760
         TabIndex        =   8
         Top             =   1320
         Width           =   975
      End
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "Sum"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   4440
      Width           =   975
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Order Id"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   60
      Width           =   1335
   End
End
Attribute VB_Name = "dlg_Order"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"3237F8CC025E"
'##ModelId=3237F8CB0307
Dim Active_Order As New Order
'##ModelId=3237F8CB030A
Dim Active_Customer As New Customer
'##ModelId=3237F8CB03AE
Dim My_Customers As New Customers

'##ModelId=3237F8CC025F
Private Sub Update_Form()
    'Present the order id
    txt_order_id.Text = Active_Order.OrderId
    'Present the customer information in the dialog
    txt_Customer_Id.Text = Active_Customer.CustomerId
    lst_Customer_Name.Text = Active_Customer.Name
    txt_customer_address.Text = Active_Customer.Address
End Sub


'##ModelId=3237F8CC028A
Private Sub btn_cancel_Click()
    'Ignore the new order and clode the form.
    Unload Me
End Sub

'##ModelId=3237F8CC028B
Private Sub btn_new_Click()
    Dim New_Row As New OrderRow
    'Edit the new row.
    If New_Row.Create() Then
        'Ok clicked!
        'Add the new row to the active order
        Active_Order.AddOrderRow New_Row
        'Add the new row to the dialog
        lst_order_rows.AddItem New_Row.Quantity & " units of " & New_Row.Article.Name & " @ " & Format(New_Row.Article.Price, "$#.#0")
        'Calculate and present the total order sum.
        txt_sum.Text = Format(Active_Order.Sum(), "$#.#0")
    End If
End Sub

'##ModelId=3237F8CC028C
Private Sub btn_ok_Click()
    'Register the new order and update the database
    Active_Order.Register
    Unload Me
End Sub



'##ModelId=3237F8CC028D
Private Sub Form_Load()
   'check if the customers are loded from the customer db
    If My_Customers.Count = 0 Then
        'Grab all the articles
        My_Customers.Fetch
    End If
    Update_Customer_List
    Update_Form
End Sub

'##ModelId=3237F8CC028E
Private Sub lst_Customer_Name_Click()
    Set Active_Customer = My_Customers.Item(lst_Customer_Name.ListIndex + 1)
    Update_Form
End Sub

'##ModelId=3237F8CC028F
Private Sub lst_Customer_Name_KeyPress(KeyAscii As Integer)
    'Trap RETURN
    If KeyAscii = 13 Then
        Dim Customer_Id As Integer
        'Restore the customer from the database
        My_Customers.Fetch Name:=CStr(lst_Customer_Name.Text)
        Set Active_Customer = My_Customers.Item
        'Accociate this customer to the active order.
        Set Active_Order.Purchaser = Active_Customer
        'Update customer list
        Update_Customer_List
        'Update form
        Update_Form
    End If
End Sub


'##ModelId=3237F8CC0291
Private Sub txt_customer_id_KeyPress(KeyAscii As Integer)
    'Trap RETURN
    If KeyAscii = 13 Then
        Dim Active_Customer As Customer
        Dim Customer_Id As Integer
        'Restore the customer from the database
        My_Customers.Fetch Id:=txt_Customer_Id.Text
        Set Active_Customer = My_Customers.Item
        'Accociate this customer to the active order.
        Set Active_Order.Purchaser = Active_Customer
        'Update customer list
        Update_Customer_List
        'Present the customer information in the dialog
        Update_Form
    End If
End Sub



'##ModelId=3237F8CC02C7
Private Sub Update_Customer_List()
    'Remove all old customer names
    lst_Customer_Name.Clear
    'Iterate over the customers
    My_Customers.MoveFirst
    Do
        'Grab the customer name and move on
        lst_Customer_Name.AddItem My_Customers.Item.Name
        My_Customers.MoveNext
    Loop Until My_Customers.Last
    'Select the first customer in list
    lst_Customer_Name.ListIndex = 0
End Sub
