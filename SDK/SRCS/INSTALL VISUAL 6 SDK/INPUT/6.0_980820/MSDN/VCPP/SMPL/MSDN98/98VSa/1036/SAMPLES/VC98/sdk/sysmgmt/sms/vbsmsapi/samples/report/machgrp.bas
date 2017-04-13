Attribute VB_Name = "MACHGRP"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MACHGRP.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

Type IDLookupRec
    ID As Long
    StrID As String
    StrName As String
End Type

Type AttributeRec
    MachineGroupID As Long
    MachineID As Long
    PropertyID As Long
    PropertyNum As Integer
    AttributeID As Long
    Value As String
End Type

'For use by frmMachineGrpReport ONLY
Global InitMachineGroupID$
Global InitMachineGroupProperties$()
Global InitMachineGroupPropertyCount%
Global InitMachineGroupIsFiltered%

'For use by QueryMachineGroups%() and FetchMachineGroups%() ONLY
Dim dyQueryMachineGroups As Recordset

'For use by QueryMachines%() and FetchMachines%() ONLY
Dim dyQueryMachines As Recordset

Function AddAttribute&(db As Database, Attrib$, AttributeName$)
    Dim IDLookup As IDLookupRec, Count%

    ' Default return value zero (Failed)
    AddAttribute& = 0

    IDLookup.StrID$ = Attrib$
    IDLookup.StrName$ = AttributeName$
    Count% = FindAttributeID%(db, "AttributeIDs", IDLookup)
    If Count% = 0 Then
        IDLookup.ID& = GetUniqueID&()
        If InsertAttributeID&(db, "AttributeIDs", IDLookup) = 1 Then AddAttribute& = IDLookup.ID&
    ElseIf Count% = 1 Then
        AddAttribute& = IDLookup.ID&
    End If
End Function

Function AddMachine&(db As Database, Machine$, MachineName$)
    Dim IDLookup As IDLookupRec, Count%

    ' Default return value zero (Failed)
    AddMachine& = 0

    IDLookup.StrID$ = Machine$
    IDLookup.StrName$ = MachineName$
    Count% = FindMachineID%(db, "MachineIDs", IDLookup)
    If Count% = 0 Then
        IDLookup.ID& = GetUniqueID&()
        If InsertMachineID&(db, "MachineIDs", IDLookup) = 1 Then AddMachine& = IDLookup.ID&
    ElseIf Count% = 1 Then
        AddMachine& = IDLookup.ID&
    End If
End Function

Function AddMachineGroup&(db As Database, Group$, GroupName$)
    Dim IDLookup As IDLookupRec, Count%

    ' Default return value zero (Failed)
    AddMachineGroup& = 0

    IDLookup.StrID$ = Group$
    IDLookup.StrName$ = GroupName$
    Count% = FindMachineGroupID%(db, "MachineGroupID", IDLookup)
    If Count% = 0 Then
        IDLookup.ID& = GetUniqueID&()
        If InsertMachineGroupID&(db, "MachineGroupID", IDLookup) = 1 Then AddMachineGroup& = IDLookup.ID&
    ElseIf Count% = 1 Then
        AddMachineGroup& = IDLookup.ID&
    End If
End Function

Function AddProperty&(db As Database, Property$, PropertyName$)
    Dim IDLookup As IDLookupRec, Count%

    ' Default return value zero (Failed)
    AddProperty& = 0

    IDLookup.StrID$ = Property$
    IDLookup.StrName$ = PropertyName$
    Count% = FindPropertyID%(db, "PropertyIDs", IDLookup)
    If Count% = 0 Then
        IDLookup.ID& = GetUniqueID&()
        If InsertPropertyID&(db, "PropertyIDs", IDLookup) = 1 Then AddProperty& = IDLookup.ID&
    ElseIf Count% = 1 Then
        AddProperty& = IDLookup.ID&
    End If
End Function

Function FetchMachineGroups%(IDLookup As IDLookupRec, Flush%, DBError%)
'   Fetches another Machine Group from the dyQueryMachineGroups dynaset
'Parameters:
'   IDLookup - Filled in with next machine name and ID.
'   Flush% - Usually False. If True, the fetch is ended.
'   DBError% - Returns True when DB error occures.
'Return Value:
'   True if another record fetched, else False (no more)

    DBError% = True
    FetchMachineGroups% = False

    If dyQueryMachineGroups.EOF Or Flush% Then
        dyQueryMachineGroups.Close
    Else
        ' Populate the site record from the dyQueryMachineGroups
        ' dynaset and find the next record
        IDLookup.ID& = dyQueryMachineGroups("ID")
        If IsNull(dyQueryMachineGroups("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyQueryMachineGroups("StrID"))
        End If
        If IsNull(dyQueryMachineGroups("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyQueryMachineGroups("StrName"))
        End If

        On Error Resume Next
        dyQueryMachineGroups.MoveNext
        If Err > 0 Then Exit Function
        On Error GoTo 0

        FetchMachineGroups% = True
    End If

    DBError% = False
End Function

Function FetchMachines%(IDLookup As IDLookupRec, Flush%, DBError%)
'   Fetches another Machine from the dyQueryMachines dynaset
'Parameters:
'   IDLookup - Filled in with next machine name and ID.
'   Flush% - Usually False. If True, the fetch is ended.
'   DBError% - Returns True when DB error occures.
'Return Value:
'   True if another record fetched, else False (no more)

    DBError% = True
    FetchMachines% = False

    If dyQueryMachines.EOF Or Flush% Then
        dyQueryMachines.Close
    Else
        ' Populate the site record from the dyQueryMachines
        ' dynaset and find the next record
        IDLookup.ID& = dyQueryMachines("ID")
        If IsNull(dyQueryMachines("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyQueryMachines("StrID"))
        End If
        If IsNull(dyQueryMachines("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyQueryMachines("StrName"))
        End If

        On Error Resume Next
        dyQueryMachines.MoveNext
        If Err > 0 Then Exit Function
        On Error GoTo 0

        FetchMachines% = True
    End If

    DBError% = False
End Function

Function FindAttributeID%(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef, dyIDLookup As Recordset

    'Set default return value -1 (Database error)
    FindAttributeID% = -1

    'Build query
    Set qy = db.QueryDefs("FindAttributeID")
    qy![INPUT StrID] = IDLookup.StrID$

    'Perform query
    On Error Resume Next
    Set dyIDLookup = qy.OpenRecordset(dbOpenDynaset, dbReadOnly)
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    ' Populate the site record
    If Not dyIDLookup.EOF Then
        IDLookup.ID& = dyIDLookup("ID")
        If IsNull(dyIDLookup("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyIDLookup("StrID"))
        End If
        If IsNull(dyIDLookup("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyIDLookup("StrName"))
        End If
    End If

    ' Return the record count
    FindAttributeID% = dyIDLookup.RecordCount
End Function

Function FindMachineGroupID%(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef, dyIDLookup As Recordset

    'Set default return value -1 (Database error)
    FindMachineGroupID% = -1

    'Build query
    Set qy = db.QueryDefs("FindMachineGroupID")
    qy![INPUT StrID] = IDLookup.StrID$

    'Perform query
    On Error Resume Next
    Set dyIDLookup = qy.OpenRecordset(dbOpenDynaset, dbReadOnly)
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    ' Populate the site record
    If Not dyIDLookup.EOF Then
        IDLookup.ID& = dyIDLookup("ID")
        If IsNull(dyIDLookup("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyIDLookup("StrID"))
        End If
        If IsNull(dyIDLookup("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyIDLookup("StrName"))
        End If
    End If

    ' Return the record count
    FindMachineGroupID% = dyIDLookup.RecordCount
End Function

Function FindMachineID%(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef, dyIDLookup As Recordset

    'Set default return value -1 (Database error)
    FindMachineID% = -1

    'Build query
    Set qy = db.QueryDefs("FindMachineID")
    qy![INPUT StrID] = IDLookup.StrID$

    'Perform query
    On Error Resume Next
    Set dyIDLookup = qy.OpenRecordset(dbOpenDynaset, dbReadOnly)
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    ' Populate the site record
    If Not dyIDLookup.EOF Then
        IDLookup.ID& = dyIDLookup("ID")
        If IsNull(dyIDLookup("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyIDLookup("StrID"))
        End If
        If IsNull(dyIDLookup("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyIDLookup("StrName"))
        End If
    End If

    ' Return the record count
    FindMachineID% = dyIDLookup.RecordCount
End Function

Function FindPropertyID%(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef, dyIDLookup As Recordset

    'Set default return value -1 (Database error)
    FindPropertyID% = -1

    'Build query
    Set qy = db.QueryDefs("FindPropertyID")
    qy![INPUT StrID] = IDLookup.StrID$

    'Perform query
    On Error Resume Next
    Set dyIDLookup = qy.OpenRecordset(dbOpenDynaset, dbReadOnly)
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    ' Populate the site record
    If Not dyIDLookup.EOF Then
        IDLookup.ID& = dyIDLookup("ID")
        If IsNull(dyIDLookup("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyIDLookup("StrID"))
        End If
        If IsNull(dyIDLookup("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyIDLookup("StrName"))
        End If
    End If

    ' Return the record count
    FindPropertyID% = dyIDLookup.RecordCount
End Function

Function GetMachineGroup%(db As Database, IDLookup As IDLookupRec)
    Dim Sql$
    Dim dyIDLookup As Recordset

    'Set default return value False (Database error)
    GetMachineGroup% = False

    Sql$ = "SELECT ID, StrID, StrName FROM [MachineGroupID]"

    ' If an error occurs exit the function
    On Error Resume Next
    Set dyIDLookup = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    ' Populate the site record
    If Not dyIDLookup.EOF Then
        IDLookup.ID& = dyIDLookup("ID")
        If IsNull(dyIDLookup("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyIDLookup("StrID"))
        End If
        If IsNull(dyIDLookup("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyIDLookup("StrName"))
        End If
    End If

    ' Return the record count
    GetMachineGroup% = True
End Function

Function GetUniqueID&()
    Static UniqueID&

    UniqueID& = UniqueID& + 1
    GetUniqueID& = UniqueID&
End Function

Function InsertAttribute&(db As Database, Attrib As AttributeRec)
'   Inserts the attribute record into the given data base
'Parameters
'   db     - The database used for the query
'   Attrib - The attribute record
'Return Value:
'   The number of records inserted

    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertAttribute& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertAttribute")
    qy![INPUT MachineID] = Attrib.MachineID&
    qy![INPUT PropertyID] = Attrib.PropertyID&
    qy![INPUT PropertyNum] = Attrib.PropertyNum%
    qy![INPUT AttributeID] = Attrib.AttributeID&
    qy![INPUT Value] = Attrib.Value$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertAttribute& = 1
End Function

Function InsertAttributeID&(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertAttributeID& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertAttributeID")
    qy![INPUT ID] = IDLookup.ID&
    qy![INPUT StrID] = IDLookup.StrID$
    qy![INPUT StrName] = IDLookup.StrName$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertAttributeID& = 1
End Function

Function InsertMachineGroupID&(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertMachineGroupID& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertMachineGroupID")
    qy![INPUT ID] = IDLookup.ID&
    qy![INPUT StrID] = IDLookup.StrID$
    qy![INPUT StrName] = IDLookup.StrName$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertMachineGroupID& = 1
End Function

Function InsertMachineID&(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertMachineID& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertMachineID")
    qy![INPUT ID] = IDLookup.ID&
    qy![INPUT StrID] = IDLookup.StrID$
    qy![INPUT StrName] = IDLookup.StrName$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertMachineID& = 1
End Function

Function InsertPropertyID&(db As Database, TableName$, IDLookup As IDLookupRec)
    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertPropertyID& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertPropertyID")
    qy![INPUT ID] = IDLookup.ID&
    qy![INPUT StrID] = IDLookup.StrID$
    qy![INPUT StrName] = IDLookup.StrName$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertPropertyID& = 1
End Function

Function MakeNiceForCrystalReports$(ByVal s$)
    Dim nPos%

    If Len(s$) > 32 Then
        'Maybe a path environment variable. Add spaces after semicolons
        nPos% = InStr(s$, ";")
        Do While nPos% > 0
            s$ = left$(s$, nPos%) + " " + Mid$(s$, nPos% + 1)
            nPos% = InStr(nPos% + 1, s$, ";")
        Loop
    End If
    MakeNiceForCrystalReports$ = s$
End Function

Function NewMachineGrpDatabase%(db As Database, ErrStr$)
    Dim td As TableDef, qy As QueryDef, fd As Field, ix As Index

    'Default return value False (Failed)
    NewMachineGrpDatabase% = False

    On Error GoTo NewMachineGrpDatabaseErr

    Set td = New TableDef
    td.Name = "MachineGroupID"

        'Fields
        Set fd = New Field
        fd.Name = "ID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrID"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrName"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Index
        Set ix = New Index
        ix.Name = "Key"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "ID"
        td.Indexes.Append ix

    db.TableDefs.Append td

    Set td = New TableDef
    td.Name = "MachineIDs"

        'Fields
        Set fd = New Field
        fd.Name = "ID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrID"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrName"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Index
        Set ix = New Index
        ix.Name = "Key"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "ID"
        td.Indexes.Append ix

    db.TableDefs.Append td

    Set td = New TableDef
    td.Name = "PropertyIDs"

        'Fields
        Set fd = New Field
        fd.Name = "ID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrID"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrName"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Index
        Set ix = New Index
        ix.Name = "Key"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "ID"
        td.Indexes.Append ix

    db.TableDefs.Append td

    Set td = New TableDef
    td.Name = "AttributeIDs"

        'Fields
        Set fd = New Field
        fd.Name = "ID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrID"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "StrName"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Index
        Set ix = New Index
        ix.Name = "Key"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "ID"
        td.Indexes.Append ix

    db.TableDefs.Append td

    Set td = New TableDef
    td.Name = "Attributes"

        'Fields
        Set fd = New Field
        fd.Name = "MachineID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "PropertyID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "PropertyNum"
        fd.Type = DB_INTEGER
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "AttributeID"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Value"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Index
        Set ix = New Index
        ix.Name = "SortKey"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "MachineID;PropertyID;PropertyNum;AttributeID"
        td.Indexes.Append ix

    db.TableDefs.Append td

    'Make QueryDefs for common insert queries and selects
    Set qy = db.CreateQueryDef("InsertAttribute", "PARAMETERS [INPUT MachineID] Long, [INPUT PropertyID] Long, [INPUT PropertyNum] Short, [INPUT AttributeID] Long, [INPUT Value] Text; INSERT INTO [Attributes] (MachineID, PropertyID, PropertyNum, AttributeID, [Value]) SELECT [INPUT MachineID] As MachineID, [INPUT PropertyID] As PropertyID, [INPUT PropertyNum] As PropertyNum, [INPUT AttributeID] As AttributeID, '|[INPUT Value]|' As [Value]")

    Set qy = db.CreateQueryDef("InsertMachineGroupID", "PARAMETERS [INPUT ID] Long, [INPUT StrID] Text, [INPUT StrName] Text; INSERT INTO MachineGroupID (ID, StrID, StrName) SELECT [INPUT ID] As ID, '|[INPUT StrID]|' As StrID, '|[INPUT StrName]|' As StrName")
    Set qy = db.CreateQueryDef("InsertMachineID", "PARAMETERS [INPUT ID] Long, [INPUT StrID] Text, [INPUT StrName] Text; INSERT INTO MachineIDs (ID, StrID, StrName) SELECT [INPUT ID] As ID, '|[INPUT StrID]|' As StrID, '|[INPUT StrName]|' As StrName")
    Set qy = db.CreateQueryDef("InsertPropertyID", "PARAMETERS [INPUT ID] Long, [INPUT StrID] Text, [INPUT StrName] Text; INSERT INTO PropertyIDs (ID, StrID, StrName) SELECT [INPUT ID] As ID, '|[INPUT StrID]|' As StrID, '|[INPUT StrName]|' As StrName")
    Set qy = db.CreateQueryDef("InsertAttributeID", "PARAMETERS [INPUT ID] Long, [INPUT StrID] Text, [INPUT StrName] Text; INSERT INTO AttributeIDs (ID, StrID, StrName) SELECT [INPUT ID] As ID, '|[INPUT StrID]|' As StrID, '|[INPUT StrName]|' As StrName")

    Set qy = db.CreateQueryDef("FindMachineGroupID", "PARAMETERS [INPUT StrID] Text; SELECT ID, StrID, StrName FROM MachineGroupID WHERE StrID = '|[INPUT StrID]|'")
    Set qy = db.CreateQueryDef("FindMachineID", "PARAMETERS [INPUT StrID] Text; SELECT ID, StrID, StrName FROM MachineIDs WHERE StrID = '|[INPUT StrID]|'")
    Set qy = db.CreateQueryDef("FindPropertyID", "PARAMETERS [INPUT StrID] Text; SELECT ID, StrID, StrName FROM PropertyIDs WHERE StrID = '|[INPUT StrID]|'")
    Set qy = db.CreateQueryDef("FindAttributeID", "PARAMETERS [INPUT StrID] Text; SELECT ID, StrID, StrName FROM AttributeIDs WHERE StrID = '|[INPUT StrID]|'")

    'Return success
    NewMachineGrpDatabase% = True
    Exit Function

NewMachineGrpDatabaseErr:
    ErrStr$ = Error$
    Exit Function
End Function

Function NewMachineGrpReportWindow%(hConnect&, ByVal FileSpec$, ErrStr$)
    Dim i%, Ret&, TempPath$, TempSpec$, frm As Form, MachineGroupID$
    Dim db As Database, td As TableDef, fd As Field, ix As Index
    Dim Resp%

    'Default return value zero (Failed)
    NewMachineGrpReportWindow% = 0

    'Allocate space for returned string
    TempSpec$ = String$(256, 0)

    'Get a temp file name
    TempPath$ = Environ$("TEMP")
    Ret& = GetTempFileName(TempPath$, "MDB", 0, TempSpec$)
    ErrStr$ = "Could not get a temporary file name for the new report."
    If (Ret& = 0) Then Exit Function

    'Clean up return string of null terminator
    i% = InStr(TempSpec$, Chr$(0))
    If i% = 0 Then i% = Len(TempSpec$) + 1
    TempSpec$ = left$(TempSpec$, i% - 1)

    'Create a temporary document file
    On Error GoTo NewMachineGrpReportWindowErr
    If FileSpec$ > "" Then
        'File Open: so copy the file the user selected
        ErrStr$ = "Could not create a temporary copy of " + FileSpec$ + ".+"
        FileCopy FileSpec$, TempSpec$
        Resp% = True
    Else
        'File New: so create a new empty document HERE
        ErrStr$ = "Could not create a temporary file for the new report."
        Kill TempSpec$
        Set db = CreateDatabase(TempSpec$, DB_LANG_GENERAL)
        i% = NewMachineGrpDatabase%(db, ErrStr$)
        db.Close
        If Not i% Then GoTo NewMachineGrpReportWindowErr

        'Let the user pick the machine groups
        Resp% = PickMachineGroups%(hConnect&, db, MachineGroupID$)
        If Resp% Then
            Resp% = PickProperties%(hConnect&, MachineGroupID$, InitMachineGroupIsFiltered%, InitMachineGroupProperties$(), InitMachineGroupPropertyCount%)
        End If
    End If
    On Error GoTo 0

    If Resp% Then
        'Pass the new document the file name to use
        InitMachineGroupID$ = MachineGroupID$
        InitReporthConnect& = hConnect&
        InitReportFileSpec$ = FileSpec$
        InitReportTempSpec$ = TempSpec$
        If InitReportFileSpec$ <= "" Then InitReportNewNumber% = InitReportNewNumber% + 1

        'Create a new document window
        On Error GoTo NewMachineGrpReportWindowErr
        ErrStr$ = "Could not create site report document window."
        Set frm = New frmMachineGrpReport
        Load frm
        On Error GoTo 0

        'Register document window with MDI
        i% = RegisterReportWindow%(frm, ErrStr$)
        If i% <= 0 Then GoTo NewMachineGrpReportWindowErr

        'Show the document window
        frm.Show
        NewMachineGrpReportWindow% = i%
    Else
        'User canceled
        Kill TempSpec$
        NewMachineGrpReportWindow% = -1
    End If

    Exit Function

NewMachineGrpReportWindowErr:
    On Error Resume Next
    If Not frm Is Nothing Then Unload frm
    Kill TempSpec$
    Exit Function
End Function

Function QueryMachineGroups%(db As Database, Attrib As AttributeRec)
'   Queries the Attribute table for all machine groups and creates
'   a dynaset (dyQueryMachineGroups) used by FetchMachineGroups()
'Parameters
'   db - The database used for the query
'   Attrib - Not used.  All machine groups are fetched.
'Return Value:
'   True if no error, else False

    Dim Sql$, Where$

    'Default return value False (Database Error)
    QueryMachineGroups% = False

    ' Build the SQL statement
    Sql$ = "SELECT DISTINCT ID, StrID, StrName FROM MachineGroupIDs, Attributes"
    
    'Build the Where clause
    Where$ = " WHERE MachineGroupID = ID"

    'Append the where clause onto query string
    Sql$ = Sql$ + Where$

    'Perform the query
    On Error Resume Next
    Set dyQueryMachineGroups = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    'Every thing is ok
    QueryMachineGroups% = True
End Function

Function QueryMachines%(db As Database, Attrib As AttributeRec)
'   Queries the Attribute table and creates
'   a dynaset (dyQueryMachines) used by FetchMachines()
'Parameters
'   db - The database used for the query
'   Attrib - The machines to fetch are indicated by the following fields
'       MachineGroupID& - Specifies the Machine Group
'Return Value:
'   True if no error, else False

    Dim Sql$, Where$

    'Default return value False (Database Error)
    QueryMachines% = False

    ' Build the SQL statement
    Sql$ = "SELECT DISTINCT ID, StrID, StrName FROM MachineIDs, Attributes"
    
    'Build the Where clause
    Where$ = " WHERE MachineID = ID"

    'Append the where clause onto query string
    Sql$ = Sql$ + Where$

    'Perform the query
    On Error Resume Next
    Set dyQueryMachines = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    'Every thing is ok
    QueryMachines% = True
End Function

