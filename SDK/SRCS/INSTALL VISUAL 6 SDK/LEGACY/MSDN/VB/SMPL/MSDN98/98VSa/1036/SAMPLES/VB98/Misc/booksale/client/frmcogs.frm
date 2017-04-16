VERSION 5.00
Begin VB.Form frmCogs 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   " Options de COGS"
   ClientHeight    =   2625
   ClientLeft      =   705
   ClientTop       =   3975
   ClientWidth     =   7545
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2625
   ScaleWidth      =   7545
   StartUpPosition =   2  'CenterScreen
   WhatsThisHelp   =   -1  'True
   Begin VB.CommandButton Command1 
      Caption         =   "&Enregistrer"
      Default         =   -1  'True
      Height          =   420
      Index           =   0
      Left            =   6210
      TabIndex        =   13
      Top             =   1650
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Aide"
      Height          =   420
      Index           =   1
      Left            =   6210
      TabIndex        =   12
      Top             =   705
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "A&nnuler"
      Height          =   420
      Index           =   2
      Left            =   6210
      TabIndex        =   11
      Top             =   210
      Width           =   1215
   End
   Begin VB.Frame Frame3 
      Caption         =   "Type de papier"
      Height          =   2340
      Left            =   2010
      TabIndex        =   6
      Top             =   120
      Width           =   1395
      Begin VB.OptionButton optPaperGrade 
         Caption         =   "Qualité 2"
         Height          =   285
         Index           =   1
         Left            =   150
         TabIndex        =   10
         Top             =   690
         Width           =   1215
      End
      Begin VB.OptionButton optPaperGrade 
         Caption         =   "Qualité 3"
         Height          =   285
         Index           =   2
         Left            =   150
         TabIndex        =   9
         Top             =   1050
         Width           =   1215
      End
      Begin VB.OptionButton optPaperGrade 
         Caption         =   "Qualité 4"
         Height          =   285
         Index           =   3
         Left            =   150
         TabIndex        =   8
         Top             =   1410
         Width           =   1215
      End
      Begin VB.OptionButton optPaperGrade 
         Caption         =   "Qualité 1"
         Height          =   285
         Index           =   0
         Left            =   150
         TabIndex        =   7
         Top             =   330
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Couleurs de l'image"
      Height          =   1125
      Left            =   105
      TabIndex        =   3
      Top             =   1335
      Width           =   1800
      Begin VB.OptionButton optPicColor 
         Caption         =   "Couleur"
         Height          =   285
         Index           =   1
         Left            =   120
         TabIndex        =   5
         Top             =   690
         Width           =   1500
      End
      Begin VB.OptionButton optPicColor 
         Caption         =   "Noir && blanc"
         Height          =   285
         Index           =   0
         Left            =   120
         TabIndex        =   4
         Top             =   345
         Value           =   -1  'True
         Width           =   1500
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Type de reliure"
      Height          =   1125
      Left            =   105
      TabIndex        =   0
      Top             =   120
      Width           =   1800
      Begin VB.OptionButton optBinding 
         Caption         =   "Couverture papier"
         Height          =   285
         Index           =   1
         Left            =   140
         TabIndex        =   2
         Top             =   600
         Width           =   1575
      End
      Begin VB.OptionButton optBinding 
         Caption         =   "Couverture rigide"
         Height          =   285
         Index           =   0
         Left            =   140
         TabIndex        =   1
         Top             =   300
         Value           =   -1  'True
         Width           =   1575
      End
   End
   Begin VB.Frame FrameConverted 
      BackColor       =   &H00C0C0C0&
      Height          =   2355
      Left            =   3510
      TabIndex        =   14
      Top             =   120
      Width           =   2535
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "+"
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   10
         Left            =   2220
         TabIndex        =   32
         Top             =   1500
         Width           =   90
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   6
         Left            =   1590
         TabIndex        =   31
         Top             =   1920
         Width           =   495
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Coût unitaire"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00800000&
         Height          =   255
         Index           =   9
         Left            =   120
         TabIndex        =   30
         Top             =   1920
         Width           =   1125
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "_________________________"
         ForeColor       =   &H00800000&
         Height          =   225
         Index           =   8
         Left            =   180
         TabIndex        =   29
         Top             =   1650
         Width           =   2250
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   165
         Index           =   5
         Left            =   1590
         TabIndex        =   28
         Top             =   1590
         Width           =   495
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Type de reliure"
         ForeColor       =   &H00800000&
         Height          =   255
         Index           =   7
         Left            =   -750
         TabIndex        =   27
         Top             =   1470
         Width           =   1965
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   4
         Left            =   1560
         TabIndex        =   26
         Top             =   1380
         Width           =   525
      End
      Begin VB.Label lblCost 
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   165
         Index           =   3
         Left            =   1110
         TabIndex        =   25
         Top             =   1050
         Width           =   495
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   165
         Index           =   2
         Left            =   1710
         TabIndex        =   24
         Top             =   900
         Width           =   375
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   1
         Left            =   1680
         TabIndex        =   23
         Top             =   540
         Width           =   405
      End
      Begin VB.Label lblCost 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   0
         Left            =   1530
         TabIndex        =   22
         Top             =   270
         Width           =   555
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "_________________________"
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   6
         Left            =   150
         TabIndex        =   21
         Top             =   1140
         Width           =   2250
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "*"
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   5
         Left            =   2250
         TabIndex        =   20
         Top             =   1110
         Width           =   60
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Pages"
         ForeColor       =   &H00800000&
         Height          =   255
         Index           =   4
         Left            =   240
         TabIndex        =   19
         Top             =   1050
         Width           =   615
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "+"
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   2
         Left            =   2220
         TabIndex        =   17
         Top             =   450
         Width           =   90
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Qualité de papier"
         ForeColor       =   &H00800000&
         Height          =   255
         Index           =   1
         Left            =   -120
         TabIndex        =   16
         Top             =   540
         Width           =   1485
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         BackStyle       =   0  'Transparent
         Caption         =   "Couleurs d'image"
         ForeColor       =   &H00800000&
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   15
         Top             =   270
         Width           =   1245
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         AutoSize        =   -1  'True
         BackStyle       =   0  'Transparent
         Caption         =   "_________________________"
         ForeColor       =   &H00800000&
         Height          =   195
         Index           =   3
         Left            =   150
         TabIndex        =   18
         Top             =   660
         Width           =   2250
      End
   End
End
Attribute VB_Name = "frmCogs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim lRetVal As Long

' Ces variables contiennent les valeurs en cours du COGS sélectionné par l'utilisateur.
Dim cBindingCost As Currency
Dim cPicture As Currency
Dim cPaperGrade As Currency
Dim lngNumPages As Long

Dim strBinding As String
Dim strPicture As String
Dim strPaper As String

Dim acurBindingCost(1) As Currency
Dim acurPictureCost(1) As Currency
Dim acurPaperCost(3) As Currency
Dim acurCogs(5) As Currency

Private Sub optPicColor_Click(Index As Integer)
If Index = 0 Then
  ' Noir & blanc
  strPicture = "NB"
Else
  ' Couleur
  strPicture = "Couleur"
End If
  
acurCogs(0) = acurPictureCost(Index)
lblCost(0).Caption = Format$(acurCogs(0), "#.0000")

CalcUnitCost

End Sub

Private Sub Command1_Click(Index As Integer)
  Dim sHelpString As String
  
  Select Case Index
    Case 0  ' Enregistrer
      frmRevenue.txtRevParm(0).Text = strBinding & ", " & strPicture & ", " & strPaper
      frmRevenue.txtRevParm(0).Tag = lblCost(6).Caption
      Unload Me
      
    Case 1  ' Aide
      sHelpString = "Sélectionnez le type de reliure désiré, le type d'image et la qualité du papier." & vbCrLf & _
                    "Cliquez sur Enregistrer pour enregistrer ces valeurs et retourner dans la feuille des revenus de livre." & vbCrLf & _
                    "Cliquez sur Annuler pour abandonner les valeurs saisies et retourner dans la feuille des revenus de livre."
                    
      lRetVal = MsgBox(prompt:=sHelpString, Title:="Aide COGS", Buttons:=vbInformation)
      
    Case 2  'Fermer
      Unload Me
      
 End Select
      
End Sub
Sub CalcUnitCost()
  Dim curTemp As Currency
    
  curTemp = acurCogs(0) + acurCogs(1)
  lblCost(2).Caption = Format$(curTemp, "#.0000")
  
  curTemp = curTemp * lngNumPages
  lblCost(4).Caption = Format$(curTemp, "#.0000")
  
  curTemp = curTemp + acurCogs(5)
  lblCost(6).Caption = Format$(curTemp, "#.0000")
  
End Sub
Function GetCOGS() As Integer
  Dim fld As Field
  Dim strSQL As String
  Dim rsCOGS As ADODB.Recordset  
  On Error GoTo GetCOGSError
  
  goStatusPanel.Text = "Récupère les numéros de COGS..."
  strSQL = "SELECT * FROM COGS"
           
  Set rsCOGS = gobjServer.GetRsCOGS(strSQL)
  
  acurBindingCost(0) = rsCOGS.Fields("HardCover")
  acurBindingCost(1) = rsCOGS.Fields("PaperBack")
  acurPictureCost(0) = rsCOGS.Fields("BlackWhite")
  acurPictureCost(1) = rsCOGS.Fields("Color")
  acurPaperCost(0) = rsCOGS.Fields("Grade1")
  acurPaperCost(1) = rsCOGS.Fields("Grade2")
  acurPaperCost(2) = rsCOGS.Fields("Grade3")
  acurPaperCost(3) = rsCOGS.Fields("Grade4")

  rsCOGS.Close
  
  GetCOGS = True
  Exit Function
  
GetCOGSError:
  If IsObject(gSn) Then gSn.Close
  GetCOGS = False
    
End Function

Public Function GetBookPages(strTitle As String) As Long
   Dim strSQL As String
   Dim rsBookPages As ADODB.Recordset

Static strOldTitle As String
Static lngPages As Long

On Error GoTo GetBookPagesError

If strTitle <> strOldTitle Then
     frmRevenue.sbrRev.Panels(1).Text = "Recherche du nombre de pages de " & strTitle & "..."
  strSQL = "SELECT Titles.Pages " & _
           "FROM Titles " & _
           "WHERE ((Titles.Title=" & Chr$(34) & Trim$(strTitle) & Chr$(34) & "));"
  
      
  Set rsBookPages = gobjServer.GetBookPages(strSQL)
  
  lngPages = rsBookPages.Fields("Pages")
  strOldTitle = strTitle
  rsBookPages.Close
  
Else
  goStatusPanel.Text = "Utilisation du nombre de pages en mémoire cache."

End If

GetBookPages = lngPages

Exit Function

GetBookPagesError:
  If IsObject(rsBookPages) Then rsBookPages.Close
  GetBookPages = False
  MsgBox Error$ & Str$(Err), vbCritical, "Erreur dans la fonction GetBookPages"

End Function

Private Sub Form_Load()
  Me.Left = (Screen.Width - Me.Width) / 2
  Me.Top = (Screen.Height - Me.Height) / 2
  Me.Show
  DoEvents
  
  lngNumPages = GetBookPages(frmRevenue.cboBooks.Text)
  lRetVal = GetCOGS
  
  lblCost(0).Caption = Format$(acurPictureCost(0), "#.0000")
  acurCogs(0) = acurPictureCost(0)
  
  lblCost(1).Caption = Format$(acurPaperCost(0), "#.0000")
  acurCogs(1) = acurPaperCost(0)
  
  lblCost(3).Caption = Str$(lngNumPages)
  
  lblCost(5).Caption = Format$(acurBindingCost(0), "#.0000")
  acurCogs(5) = acurBindingCost(0)
  
  strBinding = "Rigide"
  strPicture = "NB"
  strPaper = "1"
  CalcUnitCost
  DoEvents
  
End Sub

Private Sub optBinding_Click(Index As Integer)
  If Index = 0 Then
    strBinding = "Rigide"
    
  Else
    strBinding = "Papier"
    
  End If
  
  acurCogs(5) = acurBindingCost(Index)
  lblCost(5).Caption = Format$(acurCogs(5), "#.0000")
  
  If optPaperGrade(0).Value Then
    optPaperGrade_Click (0)
  
  ElseIf optPaperGrade(0).Value Then
    optPaperGrade_Click (1)
    
  ElseIf optPaperGrade(2).Value Then
    optPaperGrade_Click (2)
    
  Else
    optPaperGrade_Click (3)
    
  End If

  CalcUnitCost
  
End Sub

Private Sub optPaperGrade_Click(Index As Integer)
  
  Select Case Index
    Case 0
      strPaper = "1"
      
    Case 1
      strPaper = "2"
      
    Case 2
      strPaper = "3"

    Case 3
      strPaper = "4"
      
  End Select
 
  
  If optBinding(1).Value = True Then
    acurCogs(1) = acurPaperCost(Index) * 0.5
      
  Else
    acurCogs(1) = acurPaperCost(Index)
    
  End If
  
  lblCost(1).Caption = Format$(acurCogs(1), "#.0000")
  CalcUnitCost
  
End Sub


