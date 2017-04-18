VERSION 5.00
Begin VB.UserControl MyData 
   ClientHeight    =   825
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4740
   DataSourceBehavior=   1  'vbDataSource
   ScaleHeight     =   825
   ScaleWidth      =   4740
   Begin VB.PictureBox Picture1 
      BackColor       =   &H80000005&
      Height          =   495
      Left            =   120
      ScaleHeight     =   435
      ScaleWidth      =   4440
      TabIndex        =   0
      Top             =   120
      Width           =   4500
      Begin VB.CommandButton cmdLast 
         Height          =   375
         Left            =   4080
         Picture         =   "MyData.ctx":0000
         Style           =   1  'Graphical
         TabIndex        =   4
         Top             =   0
         Width           =   300
      End
      Begin VB.CommandButton cmdNext 
         Height          =   375
         Left            =   3720
         Picture         =   "MyData.ctx":0102
         Style           =   1  'Graphical
         TabIndex        =   3
         Top             =   0
         Width           =   300
      End
      Begin VB.CommandButton cmdPrev 
         Height          =   375
         Left            =   360
         Picture         =   "MyData.ctx":0204
         Style           =   1  'Graphical
         TabIndex        =   2
         Top             =   0
         Width           =   300
      End
      Begin VB.CommandButton cmdFirst 
         Height          =   375
         Left            =   0
         Picture         =   "MyData.ctx":0306
         Style           =   1  'Graphical
         TabIndex        =   1
         Top             =   0
         Width           =   300
      End
      Begin VB.Label lblCaption 
         BackStyle       =   0  'Transparent
         Caption         =   "MyData"
         Height          =   375
         Left            =   720
         TabIndex        =   5
         Top             =   0
         Width           =   2295
      End
   End
End
Attribute VB_Name = "MyData"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Enum BOFActionType
    adDoMoveFirst = 0
    adStayBOF = 1
End Enum

Public Enum EOFActionType
    adDoMoveLast = 0
    adStayEOF = 1
    adDoAddNew = 2
End Enum


Private cn As ADODB.Connection
Private WithEvents rs As ADODB.RecordSet
Attribute rs.VB_VarHelpID = -1

' Valeurs de propriétés par défaut :
Const m_def_RecordSource = ""
Const m_def_BOFAction = BOFActionType.adDoMoveFirst
Const m_def_EOFAction = EOFActionType.adDoMoveLast
Const m_def_ConnectionString = ""

' Variables de propriétés :
Private m_RecordSource As String
Private m_BOFAction As BOFActionType
Private m_EOFAction As EOFActionType
Private m_ConnectionString As String

Private Sub cmdFirst_Click()
    If rs Is Nothing Then Exit Sub
    rs.MoveFirst
End Sub

Private Sub cmdLast_Click()
    If rs Is Nothing Then Exit Sub
    rs.MoveLast
End Sub

Private Sub cmdNext_Click()
    If rs Is Nothing Then Exit Sub

    If rs.EOF Then
        Select Case m_EOFAction
            Case EOFActionType.adDoAddNew
                rs.AddNew
            Case EOFActionType.adDoMoveLast
                rs.MoveLast
            Case EOFActionType.adStayEOF
                Exit Sub
            Case Else
                Exit Sub
        End Select
    Else
        rs.MoveNext
    End If
End Sub

Private Sub cmdPrev_Click()
    If rs Is Nothing Then Exit Sub
   
   If rs.BOF Then
       Select Case m_BOFAction
           Case BOFActionType.adDoMoveFirst
               rs.MoveFirst
           Case BOFActionType.adStayBOF
               Exit Sub
           Case Else
               Exit Sub
       End Select
   Else
       rs.MovePrevious
   End If
End Sub

Private Sub UserControl_GetDataMember(DataMember As String, Data As Object)
    Dim conn As String

    On Error GoTo GetDataMemberError
    
    If rs Is Nothing Or cn Is Nothing Then
        
        ' Vérifie que les différentes propriétés ont été définies
        If Trim$(m_ConnectionString) = "" Then
            MsgBox "Propriété ConnectionString non spécifié!", vbInformation, Ambient.DisplayName
            Exit Sub
        End If
         
        If Trim$(m_RecordSource) = "" Then
            MsgBox "Propriété RecordSource non spécifié!", vbInformation, Ambient.DisplayName
            Exit Sub
        End If
            
        If Trim$(m_ConnectionString) <> "" Then
            ' Crée un objet Connection et définit
            ' une connexion.
            Set cn = New ADODB.Connection
            cn.ConnectionString = m_ConnectionString
            cn.Open
         
            ' Crée un objet RecordSet.
            Set rs = New ADODB.RecordSet
            rs.Open m_RecordSource, cn, adOpenKeyset, adLockPessimistic
            rs.MoveFirst
         Else
            Set cn = Nothing
            Set rs = Nothing
         End If
    End If
    
    Set Data = rs
    
    Exit Sub
    
GetDataMemberError:

    MsgBox "Erreur: " & CStr(Err.Number) & vbCrLf & vbCrLf & Err.Description, vbOKOnly, Ambient.DisplayName
    Exit Sub
End Sub

Private Sub UserControl_InitProperties()
    m_RecordSource = m_def_RecordSource
    m_BOFAction = m_def_BOFAction
    m_EOFAction = m_def_EOFAction
    lblCaption.Caption = Ambient.DisplayName
    m_ConnectionString = m_def_ConnectionString
    Set UserControl.Font = Ambient.Font
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    ' Charge des valeurs de propriétés à partir du stockage
    lblCaption.Caption = PropBag.ReadProperty("Caption", Ambient.DisplayName)
    m_RecordSource = PropBag.ReadProperty("RecordSource", m_def_RecordSource)
    m_BOFAction = PropBag.ReadProperty("BOFAction", m_def_BOFAction)
    m_EOFAction = PropBag.ReadProperty("EOFAction", m_def_EOFAction)
    m_ConnectionString = PropBag.ReadProperty("ConnectionString", m_def_ConnectionString)
End Sub

Private Sub UserControl_Resize()
    Picture1.Move 0, 0, Width, Height
    cmdFirst.Move 0, 0, cmdFirst.Width, _
        Height - 60
    cmdPrev.Move cmdFirst.Left + _
        cmdFirst.Width, 0, _
        cmdPrev.Width, Height - 60
    cmdLast.Move (Width - cmdLast.Width) _
        - 60, 0, cmdLast.Width, Height - 60
    cmdNext.Move cmdLast.Left - _
        cmdNext.Width, 0, cmdNext.Width, _
        Height - 60
         
    lblCaption.Height = TextHeight("A")
    lblCaption.Move cmdPrev.Left + _
        cmdPrev.Width, ((Height - 60) _
        / 2) - (lblCaption.Height / 2), _
        cmdNext.Left - (cmdPrev.Left _
        + cmdPrev.Width)
End Sub
Public Property Get Caption() As String
    Caption = lblCaption.Caption
End Property

Public Property Let Caption(ByVal New_Caption As String)
   lblCaption.Caption = New_Caption
   PropertyChanged "Caption"
End Property
' lecture seule
Public Property Get RecordSet() As ADODB.RecordSet
   Set RecordSet = rs
End Property

Public Property Get RecordSource() As String
    RecordSource = m_RecordSource
End Property

Public Property Let RecordSource(ByVal New_RecordSource As String)
    m_RecordSource = New_RecordSource
    PropertyChanged "RecordSource"
End Property

Public Property Get BOFAction() As BOFActionType
    BOFAction = m_BOFAction
End Property

Public Property Let BOFAction(ByVal New_BOFAction As BOFActionType)
    m_BOFAction = New_BOFAction
    PropertyChanged "BOFAction"
End Property

Public Property Get EOFAction() As EOFActionType
    EOFAction = m_EOFAction
End Property

Public Property Let EOFAction(ByVal New_EOFAction As EOFActionType)
    m_EOFAction = New_EOFAction
    PropertyChanged "EOF Action"
End Property

Public Property Get ConnectionString() As String
    ConnectionString = m_ConnectionString
End Property

Public Property Let ConnectionString(ByVal New_ConnectionString As String)
    m_ConnectionString = New_ConnectionString
    PropertyChanged "ConnectionString"
End Property


Private Sub UserControl_Terminate()
    On Error Resume Next
    
    If Not rs Is Nothing Then
        rs.Close
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        cn.Close
        Set cn = Nothing
    End If
    
    Err.Clear
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    ' Écrit les valeurs de propriétés dans le stockage
    Call PropBag.WriteProperty("Caption", lblCaption.Caption, Ambient.DisplayName)
    Call PropBag.WriteProperty("RecordSource", m_RecordSource, m_def_RecordSource)
    Call PropBag.WriteProperty("BOFAction", m_BOFAction, m_def_BOFAction)
    Call PropBag.WriteProperty("EOFAction", m_EOFAction, m_def_EOFAction)
    Call PropBag.WriteProperty("ConnectionString", m_ConnectionString, m_def_ConnectionString)
End Sub
