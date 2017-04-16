VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "StringBag"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' ------------------------------------------------------
' Utilise un PropertyBag pour stocker, extraire, rendre
' continues ou discontinues les données...
' ------------------------------------------------------
Private m_pbProperties As PropertyBag

' ------------------------------------------------
' Ajoute un élément à notre stockage...
' ------------------------------------------------
Public Sub Add(strKey As String, strValue As String)
    'Stocker la valeur
    m_pbProperties.WriteProperty strKey, strValue
End Sub

' ------------------------------------------------
' Extrait un élément du stockage...
'
'  [in] strKey : Clé de l'élément extrait
' ------------------------------------------------
Public Function Retrieve(strKey As String) As Variant
    Retrieve = m_pbProperties.ReadProperty(strKey)
End Function

Private Sub Class_Initialize()
    ' Initialise le PropertyBag
    Set m_pbProperties = New PropertyBag
End Sub

' ------------------------------------------------
' Prend le contenu du stockage de classe et le sérialiser en chaîne
'
' ------------------------------------------------
Public Function Serialize() As String
    ' Vide le contenu du PropertyBag dans une chaîne
    Serialize = m_pbProperties.Contents
End Function


' ------------------------------------------------
' Prend le contenu de la chaîne continue et
' le développe en propriétés, etc.
'  [in] strString : Contenu à placer dans le PropertyBag
' ------------------------------------------------
Public Sub DeSerialize(ByVal strString As String)
Dim byteArr() As Byte
    
    ' Place la chaîne dans un tableau d'octets afin que .Contents accepte l'affectation
    byteArr = strString
    
    m_pbProperties.Contents = byteArr
End Sub

' ------------------------------------------------
' Prend le contenu de notre chaîne continue et
' le développe en propriétés, etc.
'
'  [in] objMQ    : File de message pour laquelle est réalisée la continuité
'  [in] strLabel : Étiquette du message
'
'  [11/12/97, IvoSa] Created
' ------------------------------------------------
Public Sub serilizeToQueue(ByVal objMQ As MSMQQueue, Optional ByVal strLabel As String = "")
    sendMessageToQueue objMQ, strLabel, Me.Serialize
End Sub

' ------------------------------------------------
' Prend le contenu de la chaîne continue et
' le développe en propriétés, etc.
'
'  [in] objMQ     : File de message pour laquelle est réalisée la continuité
'  [in] strLablel : Étiquette du message
'
'  [11/12/97, IvoSa] Created
' ------------------------------------------------
Public Sub deserilizeFromQueue(ByVal objMessage As MSMQMessage)
        Me.DeSerialize CStr(objMessage.Body)
End Sub



Private Sub Warning(strMsg As String)
    MsgBox strMsg
End Sub
