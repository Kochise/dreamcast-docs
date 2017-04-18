VERSION 5.00
Begin VB.Form frmBilling 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Shipping / Billing Information"
   ClientHeight    =   6195
   ClientLeft      =   2130
   ClientTop       =   1170
   ClientWidth     =   8280
   Icon            =   "Billing_information.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6195
   ScaleWidth      =   8280
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox txtCardNumber 
      Height          =   285
      Left            =   1560
      TabIndex        =   14
      Top             =   5130
      Width           =   3135
   End
   Begin VB.TextBox txtCompany 
      Height          =   285
      Left            =   1560
      TabIndex        =   2
      Top             =   960
      Width           =   2655
   End
   Begin VB.ComboBox cboExpirationYear 
      Height          =   315
      Left            =   7200
      TabIndex        =   16
      Top             =   5130
      Width           =   975
   End
   Begin VB.ComboBox cboExpirationMonth 
      Height          =   315
      Left            =   6240
      TabIndex        =   15
      Top             =   5130
      Width           =   855
   End
   Begin VB.TextBox txtCardHolder 
      Height          =   285
      Left            =   4680
      TabIndex        =   13
      Top             =   4650
      Width           =   3495
   End
   Begin VB.ComboBox cboCardType 
      Height          =   315
      Left            =   1560
      TabIndex        =   12
      Top             =   4650
      Width           =   1695
   End
   Begin VB.TextBox txtComments 
      Height          =   615
      Left            =   1560
      TabIndex        =   11
      Top             =   3240
      Width           =   5295
   End
   Begin VB.TextBox txtPhone 
      Height          =   285
      Left            =   1560
      TabIndex        =   10
      Top             =   2760
      Width           =   1920
   End
   Begin VB.TextBox txtCountry 
      Height          =   285
      Left            =   4800
      TabIndex        =   9
      Top             =   2400
      Width           =   1695
   End
   Begin VB.TextBox txtEmail 
      Height          =   285
      Left            =   5280
      TabIndex        =   3
      Top             =   960
      Width           =   2295
   End
   Begin VB.TextBox txtLastName 
      Height          =   285
      Left            =   5280
      TabIndex        =   1
      Top             =   600
      Width           =   2295
   End
   Begin VB.TextBox txtAddress2 
      Height          =   285
      Left            =   1560
      TabIndex        =   5
      Top             =   1665
      Width           =   2670
   End
   Begin VB.TextBox txtAddress1 
      Height          =   285
      Left            =   1560
      TabIndex        =   4
      Top             =   1380
      Width           =   2670
   End
   Begin VB.TextBox txtState 
      Height          =   285
      Left            =   1560
      TabIndex        =   8
      Top             =   2400
      Width           =   1920
   End
   Begin VB.TextBox txtZip 
      Height          =   285
      Left            =   4800
      TabIndex        =   7
      Top             =   2040
      Width           =   1680
   End
   Begin VB.TextBox txtCity 
      Height          =   285
      Left            =   1560
      TabIndex        =   6
      Top             =   2040
      Width           =   1935
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7065
      TabIndex        =   18
      Top             =   5715
      Width           =   1125
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   5865
      TabIndex        =   17
      Top             =   5715
      Width           =   1125
   End
   Begin VB.TextBox txtFirstName 
      Height          =   285
      Left            =   1560
      TabIndex        =   0
      Top             =   600
      Width           =   2655
   End
   Begin VB.Line lneBorder 
      BorderColor     =   &H00FFFFFF&
      Index           =   1
      X1              =   105
      X2              =   8190
      Y1              =   4110
      Y2              =   4110
   End
   Begin VB.Line lneBorder 
      BorderColor     =   &H00808080&
      Index           =   0
      X1              =   105
      X2              =   8190
      Y1              =   4095
      Y2              =   4095
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Card Number:"
      Height          =   255
      Index           =   16
      Left            =   300
      TabIndex        =   35
      Top             =   5160
      Width           =   1185
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Company:"
      Height          =   255
      Index           =   1
      Left            =   180
      TabIndex        =   34
      Top             =   990
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Expiration Date:"
      Height          =   255
      Index           =   15
      Left            =   4965
      TabIndex        =   33
      Top             =   5175
      Width           =   1185
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Name on Card:"
      Height          =   255
      Index           =   14
      Left            =   3420
      TabIndex        =   32
      Top             =   4680
      Width           =   1185
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Card Type:"
      Height          =   255
      Index           =   13
      Left            =   180
      TabIndex        =   31
      Top             =   4680
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Comments:"
      Height          =   255
      Index           =   12
      Left            =   180
      TabIndex        =   30
      Top             =   3255
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Day Phone:"
      Height          =   255
      Index           =   11
      Left            =   180
      TabIndex        =   29
      Top             =   2775
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Country:"
      Height          =   255
      Index           =   10
      Left            =   3450
      TabIndex        =   28
      Top             =   2430
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "State/Province:"
      Height          =   255
      Index           =   9
      Left            =   180
      TabIndex        =   27
      Top             =   2415
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Zip Code:"
      Height          =   255
      Index           =   8
      Left            =   3810
      TabIndex        =   26
      Top             =   2070
      Width           =   945
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "City:"
      Height          =   255
      Index           =   7
      Left            =   180
      TabIndex        =   25
      Top             =   2055
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Address:"
      Height          =   255
      Index           =   6
      Left            =   180
      TabIndex        =   24
      Top             =   1410
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Email:"
      Height          =   255
      Index           =   5
      Left            =   3915
      TabIndex        =   23
      Top             =   1005
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "First Name:"
      Height          =   255
      Index           =   4
      Left            =   180
      TabIndex        =   22
      Top             =   630
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      BackStyle       =   0  'Transparent
      Caption         =   "Credit Card Information:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   21
      Top             =   4290
      Width           =   2085
   End
   Begin VB.Label lblBilling 
      Alignment       =   1  'Right Justify
      Caption         =   "Last Name:"
      Height          =   255
      Index           =   2
      Left            =   3900
      TabIndex        =   20
      Top             =   645
      Width           =   1305
   End
   Begin VB.Label lblBilling 
      BackStyle       =   0  'Transparent
      Caption         =   "Shipping / Billing Address:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   19
      Top             =   120
      Width           =   2925
   End
   Begin VB.Label lblBilling 
      BackStyle       =   0  'Transparent
      Caption         =   "Shipping / Billing Address:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00808080&
      Height          =   255
      Index           =   18
      Left            =   135
      TabIndex        =   37
      Top             =   135
      Width           =   2925
   End
   Begin VB.Label lblBilling 
      BackStyle       =   0  'Transparent
      Caption         =   "Credit Card Information:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00808080&
      Height          =   255
      Index           =   17
      Left            =   135
      TabIndex        =   36
      Top             =   4305
      Width           =   2085
   End
End
Attribute VB_Name = "frmBilling"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdCancel_Click()
    '---- Unload the form
    Unload Me
End Sub

'--------------------------------------------------------------------------
'<Purpose> The user has clicked ok.  Process the order.
'--------------------------------------------------------------------------
Private Sub cmdOK_Click()
    '---- Shipping Information
    Dim FirstName       As String
    Dim LastName        As String
    Dim Company         As String
    Dim Email           As String
    Dim Address1        As String
    Dim Address2        As String
    Dim City            As String
    Dim State           As String
    Dim Zip             As String
    Dim Country         As String
    Dim Phone           As String
    Dim Comments        As String
    '---- Billing Information
    Dim CardType        As String
    Dim CardHolder      As String
    Dim CardNumber      As String
    Dim ExpirationMonth As String
    Dim ExpirationYear  As String
    '---- Boolean for checking function return values
    Dim ReturnValue     As Boolean
    '---- String to display reason for failure to the user
    Dim Reason          As String

    '---- Get information from the form

    '---- Shipping information
    FirstName = txtFirstName
    LastName = txtLastName
    Company = txtCompany
    Email = txtEmail
    Address1 = txtAddress1
    Address2 = txtAddress2
    City = txtCity
    State = txtState
    Zip = txtZip
    Country = txtCountry
    Phone = txtPhone
    Comments = txtComments

    '---- Credit Card Information
    CardType = cboCardType.List(cboCardType.ListIndex)
    CardHolder = txtCardHolder
    CardNumber = txtCardNumber
    ExpirationMonth = cboExpirationMonth.List(cboExpirationMonth.ListIndex)
    ExpirationYear = cboExpirationYear.List(cboExpirationYear.ListIndex)

    '---- Validate the shipping information
    ReturnValue = ValidateShippingInformation(FirstName, LastName, Company, Email, Address1, Address2, City, State, Zip, Country, Phone, Comments)

    If ReturnValue Then

      '---- Make sure they gave us a name and number
      If (Trim(CardHolder) = "") Or (Trim(CardNumber) = "") Then
        MsgBox "You must provide the credit card holders name and the card number.", vbOKOnly + vbInformation
        Exit Sub
      End If
      
      '---- Bill the customers credit card
      ReturnValue = BillCreditCard(CardType, CardHolder, CardNumber, ExpirationMonth, ExpirationYear)

      If ReturnValue Then
        
        '---- Let the user know their order was placed.
        MsgBox "Your order has been successfully processed.", vbOKOnly + vbInformation
        
        '---- Unload we're done
        Unload Me
      Else

        '---- Find out why the credit card processing failed
        Reason = GetCreditCardProcessingFailure()
        If (Reason = "") Then
            Reason = "We were unable to process your credit card transaction."
        Else
            Reason = "Your credit card transaction could not be processed for the following reason: " & Reason & "."
        End If
        
        MsgBox Reason, vbOKOnly + vbInformation
      End If

    Else

      '---- Find out why the validation failed
      Reason = GetShippingValidationFailure()
      If (Reason = "") Then
        Reason = "We were unable to validate your shipping information.  Make sure that you provide your name, address and phone number."
      Else
        Reason = "Your shipping information could not be processed for the following reason: " & Reason & ". Make sure that you provide your name, address and phone number."
      End If

      '---- Let the user know why the credit card transaction failed
      MsgBox Reason, vbOKOnly + vbInformation
    End If
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim ReturnValue As Boolean
    
    '---- Shutdown the application
    ReturnValue = ShutdownApplication()
    
End Sub
