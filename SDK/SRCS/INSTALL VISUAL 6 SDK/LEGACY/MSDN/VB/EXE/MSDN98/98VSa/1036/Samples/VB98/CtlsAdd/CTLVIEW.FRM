VERSION 5.00
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmCtlView 
   BackColor       =   &H8000000C&
   Caption         =   "Exemple Visionneuse de contrôles"
   ClientHeight    =   6795
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   9480
   LinkTopic       =   "Form1"
   ScaleHeight     =   453
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   632
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog dlgFind 
      Left            =   7800
      Top             =   480
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSDataListLib.DataList lstControls 
      Height          =   9030
      Left            =   0
      TabIndex        =   1
      Top             =   420
      Width           =   2595
      _ExtentX        =   4577
      _ExtentY        =   15928
      _Version        =   393216
   End
   Begin VB.Label lblInfo 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BorderStyle     =   1  'Fixed Single
      Caption         =   $"CtlView.frx":0000
      ForeColor       =   &H8000000D&
      Height          =   420
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   10635
      WordWrap        =   -1  'True
   End
End
Attribute VB_Name = "frmCtlView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim rsControls As New ADODB.Recordset
Dim cnControls As New ADODB.Connection
Dim oControl As Object

Private Sub Form_Load()
    On Error GoTo FindErr
    Dim strQ As String ' Chaîne pour la requête
    strQ = "Provider=Microsoft.Jet.OLEDB.3.51;Data source=" & App.Path & "\controls.mdb"
    cnControls.Open strQ
    rsControls.Open "select * from controls order by description", cnControls, adOpenKeyset, adLockOptimistic
    lstControls.ListField = "Description"
    Set lstControls.RowSource = rsControls
    Exit Sub
FindErr:
    ' Si la base de données est introuvable, utilise la fonction FindDB pour la trouver.
    If Err.Number = -2147467259 Then
    cnControls.Open "Provider=Microsoft.Jet.OLEDB.3.51;Data source=" & FindDB("controls.mdb")
    Resume Next
    End If
    Exit Sub
End Sub
Private Function FindDB(dbName As String) As String
    On Error GoTo ErrHandler

    ' Configure le contrôle cmdDialog si la base de données est introuvable.
    With dlgFind
        .DialogTitle = "Impossible de trouver : " & dbName
        .Filter = "(*.MDB)|*.mdb"
        .CancelError = True   ' Provoque une erreur si l'utilisateur clique sur Annuler.
        .ShowOpen
    End With
    ' Teste le chaîne pour s'assurer qu'il s'agit de la base de données recherchée.
    Do While Right(Trim(dlgFind.FileName), Len(dbName)) <> dbName
       MsgBox "Nom de fichier différent de " & dbName
       dlgFind.ShowOpen
    Loop
    
    FindDB = dlgFind.FileName ' Renvoie le chemin d'accès complet.
    Exit Function
ErrHandler:
    If Err = 32755 Then
      Unload Me
    End If

End Function

Private Sub Form_Resize()
  lblInfo.Width = ScaleWidth
  lstControls.Move 0, lblInfo.Height, lstControls.Width, ScaleHeight - lblInfo.Height
End Sub

Private Sub lstControls_Click()
  Dim vControlLicense As Variant
  Dim vControlType As Variant
  Dim vPropertyName As Variant
  Dim vPropertyValue As Variant
  Dim vControlWidth As Variant
  Dim vControlHeight As Variant
  Dim sError As String
  
  If Not oControl Is Nothing Then
    Controls.Remove oControl
    Set oControl = Nothing
  End If
  
  rsControls.MoveFirst
  Do
    If rsControls.EOF Then Exit Do
    If rsControls.Fields("Description") = lstControls.BoundText Then
      Exit Do
    End If
    rsControls.MoveNext
  Loop
  
  vPropertyName = rsControls.Fields("Nom de la propriété")
  vPropertyValue = rsControls.Fields("Valeur de la propriété")
  vControlLicense = rsControls.Fields("Licence du contrôle")
  vControlType = rsControls.Fields("Type de contrôle")
  vControlWidth = rsControls.Fields("Largeur du contrôle")
  vControlHeight = rsControls.Fields("Hauteur du contrôle")
  
  On Error GoTo CantFindControl
  
  If (Not IsNull(vControlLicense)) Then
    sError = "Impossible d'ajouter la licence"
    Licenses.Add vControlType, vControlLicense
  End If
  
  sError = "Impossible de créer la licence du contrôle"
  Set oControl = Controls.Add(vControlType, "MyControl")
  
  If (Not IsNull(vControlLicense)) Then
    sError = "Impossible de supprimer la licence"
    Licenses.Remove vControlType
  End If
  
  If (Not IsNull(vControlWidth)) Then
    sError = "Impossible de définir la propriété Width"
    oControl.Width = vControlWidth
  End If
  
  If (Not IsNull(vControlHeight)) Then
    sError = "Impossible de définir la propriété Height"
    oControl.Height = vControlHeight
  End If
  
  sError = "Impossible de définir la propriété Left"
  oControl.Left = lstControls.Width + ((ScaleWidth - lstControls.Width) - oControl.Width) / 2
  
  sError = "Impossible de définir la propriété Top"
  oControl.Top = lblInfo.Height + ((ScaleHeight - lblInfo.Height) - oControl.Height) / 2
  
  sError = "Impossible de définir la propriété Visible"
  oControl.Visible = True
  
  If (Not IsNull(vPropertyName)) Then
    sError = "Impossible de définir la propriété '" & vPropertyName & "'"
    If (Left$(vControlType, 3) = "VB.") Then
      CallByName oControl, vPropertyName, VbLet, vPropertyValue
    Else
      CallByName oControl.object, vPropertyName, VbLet, vPropertyValue
    End If
  End If
    
  Exit Sub
  
CantFindControl:
  MsgBox "Erreur lors de l'ajout du contrôle '" & vControlType & "', " & sError & ", " & Err.Description
End Sub

