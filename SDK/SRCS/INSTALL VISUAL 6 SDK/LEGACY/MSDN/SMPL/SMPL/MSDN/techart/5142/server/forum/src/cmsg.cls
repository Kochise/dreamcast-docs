VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CMessagePvt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum enumMessageType
    [Private Message] = 0
    [Broadcast Message] = 1
    [Package Message] = 2
End Enum

Private m_etType    As enumMessageType
Private m_lDstId    As Long
Private m_lSrcId    As Long
Private m_sMessage  As String

Public Property Get DestinationId() As Long
On Error Resume Next
DestinationId = m_lDstId
End Property

Public Property Let DestinationId(ByVal lDestinationIdIn As Long)
On Error Resume Next
m_lDstId = lDestinationIdIn
End Property

Public Property Get Message() As String
On Error Resume Next
Message = m_sMessage
End Property

Public Property Let Message(ByVal sMessageIn As String)
On Error Resume Next
m_sMessage = Trim$(sMessageIn)
End Property

Public Property Get MessageType() As enumMessageType
On Error Resume Next
MessageType = m_etType
End Property

Public Property Let MessageType(ByVal etTypeIn As enumMessageType)
On Error Resume Next
m_etType = etTypeIn
End Property

Public Property Get SourceId() As Long
On Error Resume Next
SourceId = m_lSrcId
End Property

Public Property Let SourceId(ByVal lSourceIdIn As Long)
On Error Resume Next
m_lSrcId = lSourceIdIn
End Property

Private Sub Class_Initialize()
On Error Resume Next
m_etType = [Broadcast Message]
End Sub
