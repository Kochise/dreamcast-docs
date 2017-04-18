VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "VisDataClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Description = "Outils du Gestionnaire de données"
'>>>>>>>>>>>>>>>>>>>>>>>>
'>>>>>>>>>>>>>>>>>>>>>>>>

Public VBInstance As VBIDE.VBE

Implements IDTExtensibility

'---------------------------------------------------
' Cette méthode peut être appelée depuis un outil
' externe de lancement ou depuis l'interface VB.
'---------------------------------------------------
Private Sub IDTExtensibility_OnConnection(ByVal VBInst As Object, ByVal ConnectMode As vbext_ConnectMode, ByVal AddInInst As VBIDE.AddIn, custom() As Variant)
  On Error GoTo LVDErr
    
  Dim rc As Long
  Set gVDClass = Me
  ' Ceci définit le descripteur de l'instance VB
  ' utilisé par la feuille DataFormDesigner.
  Set VBInstance = VBInst
  frmMDI.mnuUDataFormDesigner.Visible = True
  frmMDI.WindowState = vbNormal
  frmMDI.SetFocus
  
  Exit Sub
    
LVDErr:
  MsgBox Err.Description
End Sub

Private Sub IDTExtensibility_OnDisconnection(ByVal RemoveMode As vbext_DisconnectMode, custom() As Variant)
  On Error Resume Next
  Unload frmMDI
End Sub

Private Sub IDTExtensibility_OnStartupComplete(custom() As Variant)
'
End Sub

Private Sub IDTExtensibility_OnAddInsUpdate(custom() As Variant)
'
End Sub

'---------------------------------------------------
' Cette méthode peut être appelée à partir d'une
' application VB au moyen d'Automation lorsque:
'Dim x As Object
'Set x = CreateObject("VisData.VisDataClass")
'x.VDOpenDatabase "c:\vb\biblio.mdb", "", False
'---------------------------------------------------
Sub VDOpenDatabase(sDatabaseName As String, sConnect As String, bReadOnly As Integer)
  On Error GoTo RVDErr
    
  frmMDI.mnuUDataFormDesigner.Visible = False
  
  gnReadOnly = bReadOnly
  If Len(sConnect) = 0 Then
    ' Doit être un fichier MDB de Microsoft Access.
    gsDataType = gsMSACCESS
    gsDBName = sDatabaseName
    OpenLocalDB True
  ElseIf UCase(Left(sConnect, 5)) = gsSQLDB Then
    ' Doit être une base de données ODBC.
    gsDataType = gsSQLDB
    ' Définit les autres variables pour la base ODBC.
    GetODBCConnectParts sConnect
    gsDBName = sDatabaseName
    SendKeys "%FOO{Enter}"
  Else
    ' Doit être une base de données ISAM locale.
    gsDataType = sConnect
    gsDBName = sDatabaseName
    OpenLocalDB True
  End If
  
  Exit Sub
    
RVDErr:
  MsgBox Err.Description
End Sub

'---------------------------------------------------
' Cette méthode ferme simplement le Gestionnaire de données à partir du client.
'---------------------------------------------------
Sub VDClose()
  Unload frmMDI
End Sub

