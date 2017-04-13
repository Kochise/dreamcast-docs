VERSION 2.00
Begin Form About_Form 
   BackColor       =   &H00FFFF00&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "About"
   ControlBox      =   0   'False
   ForeColor       =   &H00C0C0C0&
   Height          =   2625
   Left            =   2565
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2220
   ScaleWidth      =   3150
   Top             =   1245
   Width           =   3270
   Begin CommandButton Command1 
      Caption         =   "OK"
      Height          =   375
      Left            =   960
      TabIndex        =   3
      Top             =   1440
      Width           =   1215
   End
   Begin Label Label1 
      BackColor       =   &H00FFFF00&
      Caption         =   "VBSQL Sample Application"
      Height          =   255
      Left            =   384
      TabIndex        =   0
      Top             =   816
      Width           =   2624
   End
   Begin Label Label3 
      Alignment       =   2  'Center
      BackColor       =   &H00FF0000&
      Caption         =   "Microsoft Corporation"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   9.75
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   384
      TabIndex        =   2
      Top             =   272
      Width           =   2528
   End
End

Sub Command1_Click ()

    Unload About_Form

End Sub

