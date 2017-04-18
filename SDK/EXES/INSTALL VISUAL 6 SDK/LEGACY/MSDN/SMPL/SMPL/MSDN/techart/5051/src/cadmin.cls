VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'CAdmin.cls  - Copyright (C) 1996 Microsoft Corporation
'            - All rights reserved.
'Date        - 2/5/97
'Authors     - Ken Bergmann
'Purpose     - Admin operator class implementation

Option Explicit

' Internal object containment lists
Private m_cBanks    As Collection

' Database objects
Private m_dbMain    As Database
Private m_wsMain    As Workspace

'Used for temporary storage of error information
Private m_lErrNo    As Long
Private m_sErrDesc  As String

'Delete
'Purpose     - Delete data object from system
'Inputs      - (CBank)        Optional oBank
'              (CAccount)     Optional oAccount
'Outputs     - (Boolean) Success
Public Function Delete(Optional oBank As CBank, Optional oAccount As CAccount) As Boolean
Dim cParms     As Collection
Dim iParameters  As Integer
Dim sSQL         As String

On Error GoTo errDelete

' Count number of parameters
If Not (oBank Is Nothing) Then iParameters = iParameters + 1
If Not (oAccount Is Nothing) Then iParameters = iParameters + 1

' Check for invalid number of parameters
If iParameters <> 1 Then
    Delete = False
    On Error GoTo 0
    Err.Raise vbObjectError + 3, Trim$(App.Title), "This function operates on only one object per call.  Optional parameters are mutually exclusive."
    Exit Function
End If

'Deleting a Bank?
If Not (oBank Is Nothing) Then
    ' Only delete if you actually have an object
    If CBool(oBank.PKId) Then
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add oBank.PKId, "[@PKId]"
        If Not ExecBoolean("pcDel_Bank", cParms) Then
            Delete = False
            Exit Function
        End If
        Set cParms = Nothing
    Else   'No PKId
        On Error GoTo 0
        Err.Raise 5, Trim$(App.Title) & ".CAdmin.Delete.Bank", "Object may only be deleted by Primary Key, which was not supplied."
        Exit Function
    End If
    oBank.Term
    Set oBank = Nothing
    FillListBanks
End If

'Deleting an Account?
If Not (oAccount Is Nothing) Then
    ' Only delete if you actually have an object
    If CBool(oAccount.PKId) Then
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add oAccount.PKId, "[@PKId]"
        If Not ExecBoolean("pcDel_Account", cParms) Then
            Delete = False
            Exit Function
        End If
        Set cParms = Nothing
    Else   'No PKId
        On Error GoTo 0
        Err.Raise 5, Trim$(App.Title) & ".CAdmin.Delete.Account", "Object may only be deleted by Primary Key, which was not supplied."
        Exit Function
    End If
    oAccount.Term
    Set oAccount = Nothing
    FillListBanks
End If
Delete = True
Exit Function

errDelete:
    Delete = False
    If Err > vbObjectError Then
        Err.Raise Err, Trim$(App.Title) & ".CAdmin.Delete", Err.Description
    Else
        Err.Raise Err + vbObjectError, Trim$(App.Title) & ".CAdmin.Delete", Err.Description
    End If
    Exit Function
    
End Function

Public Function Transfer(ByVal sSrc As String, ByVal sDst As String, ByVal mnyAmount As Currency) As Boolean
Dim pParm   As Parameter
Dim qryDef  As QueryDef

On Error Resume Next

mnyAmount = Abs(mnyAmount)
m_wsMain.BeginTrans
Set qryDef = m_dbMain.QueryDefs("pcUpd_AccountBalance")
With qryDef
    .Parameters("[@Amount]") = -mnyAmount
    .Parameters("[@Number]") = sSrc
    Err = False
    .Execute dbFailOnError + dbSeeChanges
    If CBool(Err) Then
        m_wsMain.Rollback
        If Errors.Count > 1 Then
            m_lErrNo = Errors(0).Number
            m_sErrDesc = Errors(0).Description
        Else
            m_lErrNo = Err
            m_sErrDesc = Err.Description
        End If
        If Err < vbObjectError Then m_lErrNo = Err + vbObjectError
        On Error GoTo 0
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.Transfer", m_sErrDesc
        Transfer = False
        Exit Function
    End If
    .Parameters("[@Amount]") = mnyAmount
    .Parameters("[@Number]") = sDst
    Err = False
    .Execute dbFailOnError + dbSeeChanges
    If CBool(Err) Then
        m_wsMain.Rollback
        If Errors.Count > 1 Then
            m_lErrNo = Errors(0).Number
            m_sErrDesc = Errors(0).Description
        Else
            m_lErrNo = Err
            m_sErrDesc = Err.Description
        End If
        If Err < vbObjectError Then m_lErrNo = Err + vbObjectError
        On Error GoTo 0
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.Transfer", m_sErrDesc
        Transfer = False
        Exit Function
    End If
End With
m_wsMain.CommitTrans dbForceOSFlush
Set qryDef = Nothing
Transfer = True
End Function

'ExecBoolean
'Purpose     - Execute a JET QueryDef
'Assumtions - The cParms object is a Collection
'Inputs      - (Sting)   sQry
'              (Collection)  cParms
'Outputs     - (Boolean) Success
Public Function ExecBoolean(ByVal sQry As String, cParms As Collection) As Boolean
Dim pParm   As Parameter
Dim qryDef  As QueryDef

On Error Resume Next

m_wsMain.BeginTrans
Set qryDef = m_dbMain.QueryDefs(sQry)
With qryDef
    For Each pParm In .Parameters
        pParm.Value = cParms(pParm.Name)
    Next pParm
    Err = False
    .Execute dbFailOnError + dbSeeChanges
    If CBool(Err) Then
        m_wsMain.Rollback
        If Errors.Count > 1 Then
            m_lErrNo = Errors(0).Number
            m_sErrDesc = Errors(0).Description
        Else
            m_lErrNo = Err
            m_sErrDesc = Err.Description
        End If
        If Err < vbObjectError Then m_lErrNo = Err + vbObjectError
        On Error GoTo 0
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.ExecBoolean", m_sErrDesc
        ExecBoolean = False
        Exit Function
    End If
End With
m_wsMain.CommitTrans dbForceOSFlush
Set qryDef = Nothing
ExecBoolean = True
End Function
'ExecFillArray
'Purpose     - Fill an array based on query result
'Assumptions - The optional parameter is only used for internal calls
'Inputs      - (String)     sQry
'            - (String)     sArray()
'            - (Boolean)    Optional bAddColumnName
'Outputs     - (Boolean)    Success
Public Function ExecFillArray(ByVal sQry As String, sArray() As String, Optional ByVal bAddColumnName As Boolean) As Boolean
Dim iCols       As Integer
Dim iCurCol     As Integer
Dim lCurRow     As Long
Dim rsTemp      As Recordset

On Error Resume Next
rsTemp.Close

On Error GoTo errFillArray
Set rsTemp = m_dbMain.OpenRecordset(sQry, dbOpenSnapshot)
If Not (rsTemp.BOF And rsTemp.EOF) Then
    rsTemp.MoveLast 0
    iCols = rsTemp.Fields.Count - 1
    lCurRow = rsTemp.RecordCount - 1
    If bAddColumnName Then
        ReDim sArray(iCols, lCurRow + 1) As String
    Else
        ReDim sArray(iCols, lCurRow) As String
    End If
    lCurRow = 0
    rsTemp.MoveFirst
    Do Until rsTemp.EOF
        For iCurCol = 0 To iCols
            If IsNull(rsTemp(iCurCol)) Then
                sArray(iCurCol, lCurRow) = ""
            Else
                sArray(iCurCol, lCurRow) = Trim$(CStr(rsTemp(iCurCol)))
            End If
            If bAddColumnName Then sArray(iCurCol, 1) = rsTemp(iCurCol).Name
        Next iCurCol
        lCurRow = lCurRow + 1
        rsTemp.MoveNext
    Loop
    ExecFillArray = True
End If
rsTemp.Close
Exit Function

errFillArray:
    ExecFillArray = False
    m_sErrDesc = Err.Description
    If Errors.Count > 1 Then
        m_lErrNo = Errors(0).Number
        m_sErrDesc = Errors(0).Description
    Else
        m_lErrNo = Err
        m_sErrDesc = Err.Description
    End If
    If Err < vbObjectError Then m_lErrNo = m_lErrNo + vbObjectError
    Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.ExecFillArray", m_sErrDesc
    Exit Function

End Function

'FillCollection
'Purpose     - Fill a collection based on query result
'Inputs      - (String)     sQry
'            - (Collection) cTemp
'Outputs     - (Boolean)    Success
Public Function FillCollection(ByVal sQry As String, cTemp As Collection) As Boolean
Dim iCurCol     As Integer
Dim sTmp()      As String

On Error GoTo errFillCollection

Set cTemp = Nothing
Set cTemp = New Collection

If ExecFillArray(sQry, sTmp(), True) Then
    For iCurCol = LBound(sTmp, 1) To UBound(sTmp, 1)
        cTemp.Add sTmp(iCurCol, 0), sTmp(iCurCol, 1)
    Next iCurCol
    FillCollection = True
Else
    FillCollection = False
End If
Exit Function

errFillCollection:
    FillCollection = False
    If Err > vbObjectError Then
        m_lErrNo = Err
    Else
        m_lErrNo = Err + vbObjectError
    End If
    Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.FillCollection", Err.Description
    Exit Function

End Function

'FillListBanks
'Purpose     - Fill Banks list
'Assumptions - The CAdmin object has been initialized
Public Sub FillListBanks()
Dim oBank       As CBank
Dim iIndex      As Integer
Dim sSQL        As String
Dim sTemp()     As String

On Error Resume Next

sSQL = "SELECT PKId, Name AS [Bank Name], Code AS [Bank Code], Address1 AS [Address Line 1], Address2 AS [Address Line 2], City AS [City Name] FROM tbBank"
Err = False
If ExecFillArray(sSQL, sTemp()) Then
    If CBool(Err) Then
        ' Save error number, source, and description and raise error.
        m_lErrNo = Err
        m_sErrDesc = Err.Description
        If Err < vbObjectError Then m_lErrNo = m_lErrNo + vbObjectError
        On Error GoTo 0
        Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.FillListBanks", m_sErrDesc
        Exit Sub
    End If
End If
'Reset the Bank List
If Not (m_cBanks Is Nothing) Then
    For Each oBank In m_cBanks
        oBank.Term
    Next oBank
    Set oBank = Nothing
    Set m_cBanks = Nothing
End If
Set m_cBanks = New Collection

For iIndex = LBound(sTemp, 2) To UBound(sTemp, 2)
    ' add new CBank to collection
    Set oBank = New CBank
    Set oBank.Admin = Me
    oBank.PKId = CLng(sTemp(0, iIndex))
    m_cBanks.Add oBank, "Id=" & Trim$(CStr(oBank.PKId))
    Set oBank = Nothing
Next iIndex
For Each oBank In m_cBanks
    oBank.Refresh
Next oBank
End Sub

'Init
'Purpose     - Open database and prepare server
'Inputs      - (String)     sDataSource
'Outputs     - (Boolean)    Success
Public Function Init(ByVal sDataSource As String) As Boolean
On Error GoTo errInit
Term

Err = False
Init = True
Set m_wsMain = DBEngine.Workspaces(0)
Set m_dbMain = m_wsMain.OpenDatabase(sDataSource, False, False)
If CBool(Err) Then
    Err.Raise Err.Number + vbObjectError, Trim$(App.Title) & "Could not open database.", Err.Description
    Init = False
End If
Exit Function

errInit:
    Init = False
    If Err > vbObjectError Then
        Err.Raise Err.Number, Trim$(App.Title) & ".CAdmin.Init", Err.Description
    Else
        Err.Raise Err.Number + vbObjectError, Trim$(App.Title) & ".CAdmin.Init", Err.Description
    End If
    Exit Function
End Function

'Insert
'Purpose     - Insert data object into system
'Inputs      - (CBank)        Optional oBank
'              (CAccount)     Optional oAccount
'Outputs     - (Boolean) Success
Public Function Insert(Optional oBank As CBank, Optional oAccount As CAccount) As Boolean
Dim cParms          As Collection
Dim iParameters     As Integer
Dim sQry            As String

On Error GoTo errInsert

' count number of parameters
If Not (oBank Is Nothing) Then iParameters = iParameters + 1
If Not (oAccount Is Nothing) Then iParameters = iParameters + 1

If iParameters <> 1 Then
    Insert = False
    On Error GoTo 0
    Err.Raise vbObjectError + 3, Trim$(App.Title), "This function operates on only one object per call.  Optional parameters are mutually exclusive."
    Exit Function
End If

'Inserting a Bank?
If Not (oBank Is Nothing) Then
    ' validate oBank object
    With oBank
        If Not CBool(Len(.Code)) Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Bank", "A required field has not been filled in - Code"
            Exit Function
        End If
        
        If Not CBool(.TypeId) Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Bank", "A required field has not been filled in - TypeId"
            Exit Function
        End If
        
        If Not CBool(Len(.Name)) Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Bank", "A required field has not been filled in - Name"
            Exit Function
        End If
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add Trim$(Left$(.Address1, 60)), "[@Address1]"
        cParms.Add Trim$(Left$(.Address2, 60)), "[@Address2]"
        cParms.Add Trim$(Left$(.City, 15)), "[@City]"
        cParms.Add Trim$(Left$(.Code, 16)), "[@Code]"
        cParms.Add Trim$(Left$(.Name, 80)), "[@Name]"
        cParms.Add .TypeId, "[@BankTypeId]"
    End With
    If Not ExecBoolean("pcIns_Bank", cParms) Then
        Insert = False
        Exit Function
    End If
    Set cParms = Nothing
    oBank.Term
    Set oBank = Nothing
    FillListBanks
End If

'Inserting an Account?
If Not (oAccount Is Nothing) Then
    ' validate oAccount object
    With oAccount
        If .Bank Is Nothing Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Account", "A required field has not been filled in - bank"
            Exit Function
        Else
            If Not CBool(.Bank.PKId) Then
                Insert = False
                On Error GoTo 0
                Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Account", "A required field has not been filled in - Bank"
                Exit Function
            End If
        End If
        If Not CBool(.TypeId) Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Account", "A required field has not been filled in - TypeId"
            Exit Function
        End If
        If Not CBool(Len(.Number)) Then
            Insert = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Insert.Account", "A required field has not been filled in - Name"
            Exit Function
        End If
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add .Bank.PKId, "[@BankId]"
        cParms.Add .TypeId, "[@AccountTypeId]"
        cParms.Add Trim$(Left$(.Number, 80)), "[@Number]"
    End With
    If Not ExecBoolean("pcIns_Account", cParms) Then
        Insert = False
        Exit Function
    End If
    Set cParms = Nothing
    oAccount.Term
    Set oAccount = Nothing
    FillListBanks
End If

Insert = True
Exit Function

errInsert:
    Insert = False
    m_lErrNo = Err
    If Err < vbObjectError Then m_lErrNo = m_lErrNo + vbObjectError
    Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.Insert", Err.Description
    Exit Function
    
End Function

'Term
'Purpose     - Terminate an object, release all object references
Public Sub Term()
On Error Resume Next
Set m_cBanks = Nothing
m_dbMain.Close
Set m_dbMain = Nothing
Set m_wsMain = Nothing
End Sub

'Update
'Purpose     - Update data object
'Inputs      - (CBank)        Optional oBank
'              (CAccount)     Optional oAccount
'Outputs     - (Boolean) Success
Public Function Update(Optional oBank As CBank, Optional oAccount As CAccount) As Boolean
Dim cParms       As Collection
Dim iParameters  As Integer
Dim sQry         As String

On Error GoTo errUpdate

If Not (oBank Is Nothing) Then iParameters = iParameters + 1
If Not (oAccount Is Nothing) Then iParameters = iParameters + 1

If iParameters <> 1 Then
    Update = False
    On Error GoTo 0
    Err.Raise vbObjectError + 3, Trim$(App.Title), "This function operates on only one object per call.  Optional parameters are mutually exclusive."
    Exit Function
End If

'Updating a Bank?
If Not (oBank Is Nothing) Then
    ' validate oBank object
    With oBank
        If Not CBool(.PKId) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Bank", "A required field has not been filled in - PKId"
            Exit Function
        End If
        If Not CBool(Len(.Code)) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Bank", "A required field has not been filled in - Code"
            Exit Function
        End If
        If Not CBool(Len(.Name)) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Bank", "A required field has not been filled in - Name"
            Exit Function
        End If
        If Not CBool(.TypeId) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Bank", "A required field has not been filled in - TypeId"
            Exit Function
        End If
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add .PKId, "[@PKId]"
        cParms.Add Trim$(Left$(.Address1, 60)), "[@Address1]"
        cParms.Add Trim$(Left$(.Address2, 60)), "[@Address2]"
        cParms.Add Trim$(Left$(.City, 15)), "[@City]"
        cParms.Add Trim$(Left$(.Code, 16)), "[@Code]"
        cParms.Add Trim$(Left$(.Name, 80)), "[@Name]"
        cParms.Add .TypeId, "[@BankTypeId]"
    End With
    If Not ExecBoolean("pcUpd_Bank", cParms) Then
        Update = False
        Exit Function
    End If
    Set cParms = Nothing
    oBank.Term
End If

'Updating an Account?
If Not (oAccount Is Nothing) Then
    ' validate oAccount object
    With oAccount
        If .Bank Is Nothing Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Account", "A required field has not been filled in - Bank"
            Exit Function
        Else
            If Not CBool(.Bank.PKId) Then
                Update = False
                On Error GoTo 0
                Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Account", "A required field has not been filled in - Bank"
                Exit Function
            End If
        End If
        If Not CBool(.PKId) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Account", "A required field has not been filled in - PKId"
            Exit Function
        End If
        If Not CBool(.TypeId) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Account", "A required field has not been filled in - TypeId"
            Exit Function
        End If
        If Not CBool(Len(.Number)) Then
            Update = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.Update.Account", "A required field has not been filled in - Name"
            Exit Function
        End If
        ' Create Collection with parameter information
        Set cParms = New Collection
        cParms.Add .PKId, "[@PKId]"
        cParms.Add .Bank.PKId, "[@BankId]"
        cParms.Add .TypeId, "[@AccountTypeId]"
        cParms.Add Trim$(Left$(.Number, 80)), "[@Number]"
    End With
    If Not ExecBoolean("pcUpd_Account", cParms) Then
        Update = False
        Exit Function
    End If
    Set cParms = Nothing
    oAccount.Term
    Set oAccount = Nothing
    FillListBanks
End If

Update = True
Exit Function

errUpdate:
    Update = False
    m_lErrNo = Err
    If Err < vbObjectError Then m_lErrNo = m_lErrNo + vbObjectError
    Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.Update", Err.Description
    Exit Function
    
End Function

Public Property Get Banks() As Collection
If m_cBanks Is Nothing Then Set m_cBanks = New Collection
Set Banks = m_cBanks
End Property

Private Sub Class_Terminate()
On Error Resume Next
Term
End Sub


Public Function InsertVarObj(Optional vBank, Optional vAccount) As Boolean
Dim oAccount As CAccount
Dim oBank As CBank
Dim iParameters As Integer

On Error GoTo errInsertVarObj

' count number of parameters
If Not (IsMissing(vBank)) Then iParameters = iParameters + 1
If Not (IsMissing(vAccount)) Then iParameters = iParameters + 1

If iParameters <> 1 Then
    InsertVarObj = False
    On Error GoTo 0
    Err.Raise vbObjectError + 3, Trim$(App.Title), "This function operates on only one object per call.  Optional parameters are mutually exclusive."
    Exit Function
End If

'Inserting a Bank?
If Not (IsMissing(vBank)) Then
    ' apply vBank properties to oBank for insert
    Set oBank = New CBank
    With oBank
        .Address1 = vBank.Address1
        .Address2 = vBank.Address2
        .City = vBank.City
        .Code = vBank.Code
        .Name = vBank.Name
        .TypeId = vBank.TypeId
    End With
    InsertVarObj = Insert(oBank)
    Set oBank = Nothing
End If

'Inserting an Account?
If Not (IsMissing(vAccount)) Then
    ' apply vAccount properties to oAccount for insert
    With vAccount
        If Not CBool(.Bank.PKId) Then
                InsertVarObj = False
                On Error GoTo 0
                Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.InsertVarObj.Account", "A required field has not been filled in - Bank"
                Exit Function
        End If
        If Not CBool(.TypeId) Then
            InsertVarObj = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.InsertVarObj.Account", "A required field has not been filled in - TypeId"
            Exit Function
        End If
        If Not CBool(Len(.Number)) Then
            InsertVarObj = False
            On Error GoTo 0
            Err.Raise 4 + vbObjectError, Trim$(App.Title) & ".CAdmin.InsertVarObj.Account", "A required field has not been filled in - Name"
            Exit Function
        End If
        Set oAccount = New CAccount
        For Each oBank In m_cBanks
            If oBank.PKId = .Bank.PKId Then
                Set oAccount.Bank = oBank
                Exit For
            End If
        Next
        Set oBank = Nothing
        oAccount.TypeId = .TypeId
        oAccount.Number = .Number
        InsertVarObj = Insert(, oAccount)
        Set oAccount = Nothing
    End With
End If

Exit Function

errInsertVarObj:
    Resume
    InsertVarObj = False
    m_lErrNo = Err
    If Err < vbObjectError Then m_lErrNo = m_lErrNo + vbObjectError
    Err.Raise m_lErrNo, Trim$(App.Title) & ".CAdmin.InsertVarObj", Err.Description
    Exit Function

End Function
