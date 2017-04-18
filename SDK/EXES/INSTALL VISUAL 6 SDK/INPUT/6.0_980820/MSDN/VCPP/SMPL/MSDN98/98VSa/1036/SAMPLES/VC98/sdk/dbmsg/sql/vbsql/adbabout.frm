VERSION 2.00
Begin Form fAbout 
   BackColor       =   &H00C0C0C0&
   BorderStyle     =   3  'Fixed Double
   Caption         =   "About ADBPubs 1"
   ForeColor       =   &H00C0C0C0&
   Height          =   2475
   Left            =   1335
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2070
   ScaleWidth      =   6330
   Top             =   1800
   Width           =   6450
   Begin SSPanel panOm 
      AutoSize        =   3  'AutoSize Child To Panel
      BackColor       =   &H00C0C0C0&
      BevelInner      =   2  'Raised
      BevelOuter      =   1  'Inset
      BorderWidth     =   2
      Font3D          =   1  'Raised w/light shading
      ForeColor       =   &H00000000&
      Height          =   1935
      Left            =   60
      TabIndex        =   2
      Top             =   45
      Width           =   6225
      Begin SSPanel Panel3D1 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelWidth      =   0
         BorderWidth     =   0
         Caption         =   "for Microsoft Corporation"
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   255
         Left            =   900
         TabIndex        =   14
         Top             =   630
         Width           =   3945
      End
      Begin PictureBox picFlag 
         BackColor       =   &H00C0C0C0&
         BorderStyle     =   0  'None
         Height          =   555
         Left            =   5310
         ScaleHeight     =   555
         ScaleWidth      =   555
         TabIndex        =   7
         Top             =   240
         Width           =   555
      End
      Begin PictureBox Picture1 
         BackColor       =   &H00FFFFFF&
         Height          =   525
         Left            =   180
         Picture         =   ADBABOUT.FRX:0000
         ScaleHeight     =   495
         ScaleWidth      =   495
         TabIndex        =   6
         Top             =   240
         Width           =   525
      End
      Begin SSPanel Panel3D2 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelWidth      =   0
         BorderWidth     =   0
         Caption         =   "Made by ADB-Arkitektur AB, Sweden 1993"
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   255
         Left            =   900
         TabIndex        =   5
         Top             =   345
         Width           =   3945
      End
      Begin SSPanel Panel3D3 
         AutoSize        =   3  'AutoSize Child To Panel
         BackColor       =   &H00C0C0C0&
         BevelWidth      =   0
         BorderWidth     =   0
         Caption         =   "ADBPubs 1"
         Font3D          =   1  'Raised w/light shading
         ForeColor       =   &H00000000&
         Height          =   255
         Left            =   900
         TabIndex        =   4
         Top             =   105
         Width           =   3945
      End
      Begin SSCommand cmdOk 
         Caption         =   "&Ok"
         Font3D          =   3  'Inset w/light shading
         ForeColor       =   &H00000000&
         Height          =   375
         Left            =   5040
         TabIndex        =   3
         Top             =   1425
         Width           =   1020
      End
      Begin Label Label2 
         Alignment       =   2  'Center
         BackColor       =   &H00000000&
         ForeColor       =   &H00000000&
         Height          =   45
         Left            =   855
         TabIndex        =   13
         Top             =   975
         Width           =   3945
      End
      Begin Label lblCoProcessorInfo 
         BackColor       =   &H00C0C0C0&
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   3135
         TabIndex        =   12
         Top             =   1590
         Width           =   1695
      End
      Begin Label lblModeInfo 
         BackColor       =   &H00C0C0C0&
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   855
         TabIndex        =   11
         Top             =   1125
         Width           =   2280
      End
      Begin Label lblMemoryInfo 
         BackColor       =   &H00C0C0C0&
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   3135
         TabIndex        =   10
         Top             =   1380
         Width           =   1725
      End
      Begin Label Label3 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Math Co-Processor:"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   870
         TabIndex        =   9
         Top             =   1590
         Width           =   1395
      End
      Begin Label Label1 
         AutoSize        =   -1  'True
         BackColor       =   &H00C0C0C0&
         Caption         =   "Memory:"
         FontBold        =   0   'False
         FontItalic      =   0   'False
         FontName        =   "MS Sans Serif"
         FontSize        =   8.25
         FontStrikethru  =   0   'False
         FontUnderline   =   0   'False
         Height          =   195
         Left            =   870
         TabIndex        =   8
         Top             =   1350
         Width           =   600
      End
   End
   Begin SSCommand picFlagOrg 
      Font3D          =   1  'Raised w/light shading
      ForeColor       =   &H00000000&
      Height          =   600
      Index           =   1
      Left            =   150
      Picture         =   ADBABOUT.FRX:0302
      TabIndex        =   1
      Top             =   2160
      Visible         =   0   'False
      Width           =   675
   End
   Begin SSCommand picFlagOrg 
      Font3D          =   1  'Raised w/light shading
      ForeColor       =   &H00000000&
      Height          =   600
      Index           =   2
      Left            =   825
      Picture         =   ADBABOUT.FRX:0604
      TabIndex        =   0
      Top             =   2160
      Visible         =   0   'False
      Width           =   675
   End
   Begin Timer Timer1 
      Interval        =   50
      Left            =   1545
      Top             =   2265
   End
End
Dim FlagNmbr As Integer

Sub cmdOk_Click ()

    Timer1.Enabled = False
    Unload Me

End Sub

Sub Form_Load ()

    Me.Height = 2470
    Me.Width = 6480
    ' Center form
    Left = screen.Width / 2 - Width / 2
    Top = screen.Height / 2 - Height / 2
    
    ' Retrieve current Windows system and memory configuration
    WinFlags = GetWinFlags()
    
    ' Display mode information
    If WinFlags And WF_ENHANCED Then
        lblModeInfo = "386 Enhanced Mode"
    Else
        lblModeInfo = "Standard Mode"
    End If
    
    ' Display math co-processor information
    If WinFlags And WF_80x87 Then
        lblCoProcessorInfo = "Present"
    Else
        lblCoProcessorInfo = "Not Present"
    End If

    ' Scan global heap to get memory information
    temp = GetFreeSpace(0)
    If Sgn(temp) = -1 Then
        FreeSpace = CLng(temp + 1&) Xor &HFFFFFFFF
    Else
        FreeSpace = temp
    End If

    ' Divide by 1024 to display info in KB
    FreeSpace = FreeSpace / 1024
    lblMemoryInfo = Format(FreeSpace, "#,#") + " KB Free"
    
    
    FlagNmbr = 1
    Timer1.Interval = 150
    Timer1.Enabled = True

End Sub

Sub Timer1_Timer ()

    picFlag.Picture = picFlagOrg(FlagNmbr).Picture
    If FlagNmbr = 1 Then
        FlagNmbr = 2
    Else
        FlagNmbr = 1
    End If

End Sub

