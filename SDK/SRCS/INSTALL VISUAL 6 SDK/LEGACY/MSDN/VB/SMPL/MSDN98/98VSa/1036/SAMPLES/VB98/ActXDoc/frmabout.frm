VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "À propos de FirstDoc"
   ClientHeight    =   3555
   ClientLeft      =   1320
   ClientTop       =   2100
   ClientWidth     =   5730
   ClipControls    =   0   'False
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2453.724
   ScaleMode       =   0  'User
   ScaleWidth      =   5380.766
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox picIcon 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      ClipControls    =   0   'False
      Height          =   540
      Left            =   240
      Picture         =   "frmAbout.frx":0000
      ScaleHeight     =   337.12
      ScaleMode       =   0  'User
      ScaleWidth      =   337.12
      TabIndex        =   1
      Top             =   240
      Width           =   540
   End
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   345
      Left            =   4245
      TabIndex        =   0
      Top             =   2625
      Width           =   1260
   End
   Begin VB.CommandButton cmdSysInfo 
      Caption         =   "&Infos système..."
      Height          =   345
      Left            =   4260
      TabIndex        =   2
      Top             =   3075
      Width           =   1245
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00808080&
      BorderStyle     =   6  'Inside Solid
      Index           =   1
      X1              =   84.515
      X2              =   5309.398
      Y1              =   1687.583
      Y2              =   1687.583
   End
   Begin VB.Label lblDescription 
      Caption         =   "Document ActiveX"
      ForeColor       =   &H00000000&
      Height          =   1170
      Left            =   1050
      TabIndex        =   3
      Top             =   1125
      Width           =   3885
   End
   Begin VB.Label lblTitle 
      Caption         =   "Document ActiveX FirstDoc"
      ForeColor       =   &H00000000&
      Height          =   480
      Left            =   1050
      TabIndex        =   4
      Top             =   240
      Width           =   3885
   End
   Begin VB.Line Line1 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   0
      X1              =   98.6
      X2              =   5309.398
      Y1              =   1697.936
      Y2              =   1697.936
   End
   Begin VB.Label lblVersion 
      Caption         =   "Version 1.0"
      Height          =   225
      Left            =   1050
      TabIndex        =   5
      Top             =   780
      Width           =   3885
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Options de sécurité de la clé de la base de registres.
Const READ_CONTROL = &H20000
Const KEY_QUERY_VALUE = &H1
Const KEY_SET_VALUE = &H2
Const KEY_CREATE_SUB_KEY = &H4
Const KEY_ENUMERATE_SUB_KEYS = &H8
Const KEY_NOTIFY = &H10
Const KEY_CREATE_LINK = &H20
Const KEY_ALL_ACCESS = KEY_QUERY_VALUE + KEY_SET_VALUE + _
                       KEY_CREATE_SUB_KEY + KEY_ENUMERATE_SUB_KEYS + _
                       KEY_NOTIFY + KEY_CREATE_LINK + READ_CONTROL
                     
' Types RACINE de la clé de la base de registes.
Const HKEY_LOCAL_MACHINE = &H80000002
Const ERROR_SUCCESS = 0
Const REG_SZ = 1                         ' Chaîne se terminant par un caractère nul Unicode.
Const REG_DWORD = 4                      ' Nombre 32 bits.

Const gREGKEYSYSINFOLOC = "SOFTWARE\Microsoft\Shared Tools Location"
Const gREGVALSYSINFOLOC = "MSINFO"
Const gREGKEYSYSINFO = "SOFTWARE\Microsoft\Shared Tools\MSINFO"
Const gREGVALSYSINFO = "PATH"

Private Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByVal lpData As String, ByRef lpcbData As Long) As Long
Private Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long


Private Sub cmdSysInfo_Click()
  Call StartSysInfo
End Sub

Private Sub cmdOK_Click()
  Unload Me
End Sub

Private Sub Form_Load()
  Me.Caption = "À propos de " & App.Title
  lblVersion.Caption = "Version " & App.Major & "." & App.Minor & "." & App.Revision
  lblTitle.Caption = App.Title
End Sub

Public Sub StartSysInfo()
  On Error GoTo SysInfoErr

  Dim rc As Long
  Dim SysInfoPath As String
  
  ' Essaie d'obtenir des informations système pour le chemin et/ou le nom du programme à partir de la base de registres.
  If GetKeyValue(HKEY_LOCAL_MACHINE, gREGKEYSYSINFO, gREGVALSYSINFO, SysInfoPath) Then
  ' Essaie d'obtenir uniquement des informations système pour le chemin du programme à partir de la base de registres du système.
  ElseIf GetKeyValue(HKEY_LOCAL_MACHINE, gREGKEYSYSINFOLOC, gREGVALSYSINFOLOC, SysInfoPath) Then
      ' Valide l'existence de la version du fichier 32 bits.
      If (Dir(SysInfoPath & "\MSINFO32.EXE") <> "") Then
          SysInfoPath = SysInfoPath & "\MSINFO32.EXE"
          
      ' Erreur - Fichier introuvable...
      Else
          GoTo SysInfoErr
      End If
  ' Erreur - Entrée de la base de registres introuvable...
  Else
      GoTo SysInfoErr
  End If
  
  Call Shell(SysInfoPath, vbNormalFocus)
  
  Exit Sub
SysInfoErr:
  MsgBox "Information système introuvable en ce moment", vbOKOnly
End Sub

Public Function GetKeyValue(KeyRoot As Long, KeyName As String, SubKeyRef As String, ByRef KeyVal As String) As Boolean
  Dim i As Long          ' Compteur de boucle.
  Dim rc As Long         ' Code de retour.
  Dim hKey As Long       ' Gestion vers la clé de la base de registres ouverte.
  Dim hDepth As Long
  Dim KeyValType As Long ' Type de données d'une clé de la base de registres.
  Dim tmpVal As String   ' Stockage temporaire pour une valeur de la clé de la base de registres.
  Dim KeyValSize As Long ' Taille de la variable de la clé de la base de registres.

  '------------------------------------------------------------
  ' Ouvre la clé de la base de registres sous la racine clé {HKEY_LOCAL_MACHINE...}
  '------------------------------------------------------------
  rc = RegOpenKeyEx(KeyRoot, KeyName, 0, KEY_ALL_ACCESS, hKey) ' Ouvre la clé de la base de registres.
  
  If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' Gère l'erreur...
  
  tmpVal = String$(1024, 0)                               ' Alloue de l'espace à la variable.
  KeyValSize = 1024                                       ' Marque la taille de la variable.
  
  '------------------------------------------------------------
  ' Extrait la valeur de la clé de la base de registres...
  '------------------------------------------------------------
  rc = RegQueryValueEx(hKey, SubKeyRef, 0, _
                       KeyValType, tmpVal, KeyValSize)    ' Obtient/Crée la valeur de la clé.
                      
  If (rc <> ERROR_SUCCESS) Then GoTo GetKeyError          ' Gère les erreurs.
  
  If (Asc(Mid(tmpVal, KeyValSize, 1)) = 0) Then ' Win95 ajoute une chaîne se terminant par un caractère null...
      tmpVal = Left(tmpVal, KeyValSize - 1) ' Null a été trouvé, l'extrait de la chaîne
  Else ' WinNT n'ajoute PAS de chaîne se terminant par un carctère null...
      tmpVal = Left(tmpVal, KeyValSize) ' Null introuvable, extrait uniquement la chaîne
  End If
  '------------------------------------------------------------
  ' Détermine le type de valeur de la clé pour la conversion...
  '------------------------------------------------------------
  Select Case KeyValType   ' Recherche les types de données...
  Case REG_SZ              ' Type de données de la clé de la base de registres de la chaîne
      KeyVal = tmpVal      ' Copie la valeur de la chaîne
  Case REG_DWORD           ' Type de données de la clé de la base de registres de mots doubles
      For i = Len(tmpVal) To 1 Step -1 ' Convertit chaque bit
          KeyVal = KeyVal + Hex(Asc(Mid(tmpVal, i, 1)))   ' Construit la valeur caractère par caractère
      Next
      KeyVal = Format$("&h" + KeyVal) ' Convertit le mot double en chaîne
  End Select
  
  GetKeyValue = True       ' Renvoie une opération réussie
  rc = RegCloseKey(hKey)   ' Ferme la clé de la base de registres
  Exit Function            ' Quitte la fonction
  
GetKeyError:               ' Efface après qu'une erreur se soit produite...
  KeyVal = ""              ' Définit la valeur de retour avec une chaîne vide
  GetKeyValue = False      ' Renvoie un échec
  rc = RegCloseKey(hKey)   ' Ferme la clé de la base de registres
End Function
