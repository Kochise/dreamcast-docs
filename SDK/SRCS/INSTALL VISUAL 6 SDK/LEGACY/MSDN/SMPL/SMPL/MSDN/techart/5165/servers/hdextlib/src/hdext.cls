VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CHDExt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'Copyright (C) 1998 Microsoft Corporation
'All rights reserved.
'
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
'EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
'MERCHANTIBILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
'
'Date    - 02/01/98
'Authors - Robert Coleridge, Steve Kirk, Fred Pace, Kevin Marzec, Dale Smith
'
Option Explicit

Private Const OBJNAME = "HDExt"

'=======================================================================
'Synopsis:              Procedure replaces tags with new values.
'Function input:        Message string, tags collection.
'                       the description.
'Function output:       Returns the revised string.
'=======================================================================
Public Function ReplaceTags(ByVal sMsg As String, cTags As Collection) As String
    Dim sTag As String
    Dim sValue As String
    Dim iTagStart As Integer
    Dim iTagEnd As Integer
    Dim n As Integer

    'set up so invalid tag forces exit
    On Error Resume Next

    'walk through list of tags, replacing all found with associated values
    Do While True
        'find start of tag
        iTagStart = InStr(1, sMsg, "<#")
        If iTagStart = 0 Then
            Exit Do
        End If
        
        'find end of tag
        iTagEnd = InStr(iTagStart, sMsg, "#>")
        Debug.Print iTagEnd
        If iTagEnd = 0 Then
            Exit Do
        End If
        
        'extract tag, massage tag, and extract value from collection
        sTag = Mid$(sMsg, iTagStart, iTagEnd - iTagStart + 2)
        sTag = Mid$(sTag, 3, Len(sTag) - 4)
        sValue = cTags.Item(sTag)
        If Err Then
            Exit Do
        End If
        
        'make replacement of tag for value
        sMsg = Left$(sMsg, iTagStart - 1) & sValue & Mid$(sMsg, iTagEnd + 2)
    Loop
    
    'pass back modified resource string
    ReplaceTags = sMsg
    
End Function

'=======================================================================
'Synopsis:              Procedure sends confirmation mail to user.
'Function input:        Profile, user alias, tracking identifier, and
'                       the description.
'Function output:       Returns True if successful
'=======================================================================
Public Function SendConfirmationMail( _
                    ByVal sProfile As String, _
                    ByVal sUserAlias As String, _
                    ByVal lTrackingId As Long, _
                    ByVal sDesc As String) As Boolean
    Dim oSess As MAPI.Session
    Dim oMsg As MAPI.Message
    Dim oRecipTo As MAPI.Recipient
    Dim n As Integer
    Dim Alias As String
    Dim cTags As New Collection

    'we must have a profile to log on
    If Len(sProfile) = 0 Then
        SendConfirmationMail = False
        Exit Function
    End If

    'create session and log on
    Set oSess = CreateObject("MAPI.Session")
    oSess.Logon sProfile
    
    'create message and set up tags
    cTags.Add CLng(lTrackingId), "TRACKINGID"
    cTags.Add sDesc, "DESCRIPTION"
    Set oMsg = oSess.Outbox.Messages.Add
    oMsg.Subject = ReplaceTags(LoadResString(icIDS_CONF_SUBJECT), cTags)
    oMsg.Text = ReplaceTags(LoadResString(icIDS_CONF_MSG), cTags)
    
    ' set up who it's going to
    Set oRecipTo = oMsg.Recipients.Add
    oRecipTo.Name = sUserAlias
    oRecipTo.Type = ActMsgTo
    oRecipTo.Resolve
    
    'send message
    oMsg.Update
    oMsg.Send
    
    'clean up and logoff
    Set oRecipTo = Nothing
    Set oMsg = Nothing
    oSess.Logoff
    Set oSess = Nothing
    
    SendConfirmationMail = True

End Function


