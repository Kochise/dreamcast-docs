VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MyDataSource"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Sub Class_GetDataMember(DataMember As String, Data As Object)
    ' Déclare une instance de la classe MyObject
    Dim MyOSP As New MyOSPObject
    
    ' Vérifie que le DataMember est valide
    If DataMember = "" Then
        Err.Raise (E_FAIL)
    End If
    
    ' Définit la propriété FilePath
    MyOSP.FilePath = DataMember
    
    ' Appelle la méthode LoadData pour remplir la classe
    MyOSP.LoadData
    
    ' Définit les données de MyDataSource à partir des données de MyOSPObject
    Set Data = MyOSP
End Sub


