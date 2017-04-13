Attribute VB_Name = "MACHINE"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  MACHINE.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'For use by QueryProperties%() and FetchProperties%() ONLY
Dim dyQueryProperties As Recordset

'For use by QueryAttributes%() and FetchAttributes%() ONLY
Dim dyQueryAttributes As Recordset

Function FetchAttributes%(IDLookup As IDLookupRec, Flush%, DBError%)
'   Fetches another Attribute & Value from the dyQueryAttributes dynaset
'Parameters:
'   IDLookup - Filled in with next attribute and value:
'       .ID      - Recieves the ID of the attribute
'       .StrID   - Recieves the name of the attribute
'       .StrName - Recieves the value of the attribute
'   Flush% - Usually False. If True, the fetch is ended.
'   DBError% - Returns True when DB error occures.
'Return Value:
'   True if another record fetched, else False (no more)

    DBError% = True
    FetchAttributes% = False

    If dyQueryAttributes.EOF Or Flush% Then
        dyQueryAttributes.Close
    Else
        ' Populate the site record from the dyQueryProperties
        ' dynaset and find the next record
        IDLookup.ID& = dyQueryAttributes("ID")
        If IsNull(dyQueryAttributes("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyQueryAttributes("StrID"))
        End If
        If IsNull(dyQueryAttributes("Value")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyQueryAttributes("Value"))
        End If

        On Error Resume Next
        dyQueryAttributes.MoveNext
        If Err > 0 Then Exit Function
        On Error GoTo 0

        FetchAttributes% = True
    End If

    DBError% = False
End Function

Function FetchProperties%(IDLookup As IDLookupRec, Flush%, DBError%)
'   Fetches another Property from the dyQueryProperties dynaset
'Parameters:
'   IDLookup - Filled in with next property name and ID.
'   Flush% - Usually False. If True, the fetch is ended.
'   DBError% - Returns True when DB error occures.
'Return Value:
'   True if another record fetched, else False (no more)

    DBError% = True
    FetchProperties% = False

    If dyQueryProperties.EOF Or Flush% Then
        dyQueryProperties.Close
    Else
        ' Populate the site record from the dyQueryProperties
        ' dynaset and find the next record
        IDLookup.ID& = dyQueryProperties("ID")
        If IsNull(dyQueryProperties("StrID")) Then
            IDLookup.StrID$ = ""
        Else: IDLookup.StrID$ = Trim$(dyQueryProperties("StrID"))
        End If
        If IsNull(dyQueryProperties("StrName")) Then
            IDLookup.StrName$ = ""
        Else: IDLookup.StrName$ = Trim$(dyQueryProperties("StrName"))
        End If

        On Error Resume Next
        dyQueryProperties.MoveNext
        If Err > 0 Then Exit Function
        On Error GoTo 0

        FetchProperties% = True
    End If

    DBError% = False
End Function

Function GetMachine%(db As Database, IDLookup As IDLookupRec)
    Dim Sql$
    Dim dyIDLookup As Recordset

    'Set default return value False (Database error)
    GetMachine% = False

    Sql$ = "SELECT ID, StrID, StrName FROM [MachineID]"

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
    GetMachine% = True
End Function

Function NewMachineDatabase%(db As Database, dbSrce As Database, Attrib As AttributeRec, ErrStr$)
    Dim ix As Index

    'Default return value False (Failed)
    NewMachineDatabase% = False

    On Error GoTo NewMachineDatabaseErr

    dbSrce.Execute "SELECT PropertyID, PropertyNum, AttributeID, Value INTO Attributes IN '" + db.Name + "' FROM Attributes WHERE MachineID = " + CStr(Attrib.MachineID)
    dbSrce.Execute "SELECT DISTINCT ID, StrID, StrName INTO MachineID IN '" + db.Name + "' FROM MachineIDs, Attributes WHERE MachineID = MachineIDs.ID AND MachineID = " + CStr(Attrib.MachineID)
    dbSrce.Execute "SELECT DISTINCT ID, StrID, StrName INTO AttributeIDs IN '" + db.Name + "' FROM AttributeIDs, Attributes WHERE AttributeID = AttributeIDs.ID AND MachineID = " + CStr(Attrib.MachineID)
    dbSrce.Execute "SELECT DISTINCT ID, StrID, StrName INTO PropertyIDs IN '" + db.Name + "' FROM PropertyIDs, Attributes WHERE PropertyID = PropertyIDs.ID AND MachineID = " + CStr(Attrib.MachineID)

    'Set key on Attributes
    Set ix = New Index
    ix.Name = "SortKey"
    ix.Primary = True
    ix.Unique = True
    ix.Fields = "PropertyID;PropertyNum;AttributeID"
    db.TableDefs("Attributes").Indexes.Append ix

    'Set key on MachineID
    Set ix = New Index
    ix.Name = "Key"
    ix.Primary = True
    ix.Unique = True
    ix.Fields = "ID"
    db.TableDefs("MachineID").Indexes.Append ix

    'Set key on PropertyIDs
    Set ix = New Index
    ix.Name = "Key"
    ix.Primary = True
    ix.Unique = True
    ix.Fields = "ID"
    db.TableDefs("PropertyIDs").Indexes.Append ix
    
    'Set key on AttributeIDs
    Set ix = New Index
    ix.Name = "Key"
    ix.Primary = True
    ix.Unique = True
    ix.Fields = "ID"
    db.TableDefs("AttributeIDs").Indexes.Append ix
    
    'Return success
    NewMachineDatabase% = True
    Exit Function

NewMachineDatabaseErr:
    ErrStr$ = Error$
    Exit Function
End Function

Function NewMachineReportWindow%(hConnect&, ByVal FileSpec$, dbSrce As Database, Attrib As AttributeRec, ErrStr$)
    Dim i%, Ret&, TempPath$, TempSpec$, frm As Form
    Dim db As Database, td As TableDef, fd As Field, ix As Index

    'Default return value zero (Failed)
    NewMachineReportWindow% = 0

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
    On Error GoTo NewMachineReportWindowErr
    If FileSpec$ > "" Then
        'File Open: so copy the file the user selected
        ErrStr$ = "Could not create a temporary copy of " + FileSpec$ + ".+"
        FileCopy FileSpec$, TempSpec$
    Else
        'File New: so create a new empty document
        ErrStr$ = "Could not create a temporary file for the new report."
        Kill TempSpec$
        Set db = CreateDatabase(TempSpec$, DB_LANG_GENERAL)

        'Populate it with data from source database
        i% = NewMachineDatabase%(db, dbSrce, Attrib, ErrStr$)
        db.Close
        If Not i% Then GoTo NewMachineReportWindowErr
    End If
    On Error GoTo 0

    'Pass the new document the file name to use
    InitReporthConnect& = hConnect&
    InitReportFileSpec$ = FileSpec$
    InitReportTempSpec$ = TempSpec$
    If InitReportFileSpec$ <= "" Then InitReportNewNumber% = InitReportNewNumber% + 1

    'Create a new document window
    On Error GoTo NewMachineReportWindowErr
    ErrStr$ = "Could not create site report document window."
    Set frm = New frmMachineReport
    Load frm
    On Error GoTo 0

    'Register document window with MDI
    i% = RegisterReportWindow%(frm, ErrStr$)
    If i% <= 0 Then GoTo NewMachineReportWindowErr

    'Show the document window
    frm.Show
    NewMachineReportWindow% = i%
    Exit Function

NewMachineReportWindowErr:
    On Error Resume Next
    If Not frm Is Nothing Then Unload frm
    Kill TempSpec$
    Exit Function
End Function

Function QueryAttributes%(db As Database, Attrib As AttributeRec)
'Queries the Attribute table and creates
'   a dynaset (dyQueryAttributes) used by FetchAttributes()
'Parameters
'   db - The database used for the query
'   Attrib - Not used. All the properties are fetched.
'Return Value:
'   True if no error, else False

    Dim Sql$, Where$

    'Default return value False (Database Error)
    QueryAttributes% = False

    ' Build the SQL statement
    Sql$ = "SELECT DISTINCT PropertyID, PropertyNum, AttributeID, ID, StrID, Value FROM AttributeIDs, Attributes "

    'Build the Where clause
    Where$ = " WHERE AttributeID = ID And PropertyID = " + CStr(Attrib.PropertyID&) + " ORDER BY PropertyID ASC, PropertyNum ASC, AttributeID ASC"

    'Append the where clause onto query string
    Sql$ = Sql$ + Where$

    'Perform the query
    On Error Resume Next
    Set dyQueryAttributes = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    'Every thing is ok
    QueryAttributes% = True
End Function

Function QueryProperties%(db As Database, Attrib As AttributeRec)
'Queries the Attribute table for all properties and creates
'   a dynaset (dyQueryProperties) used by FetchProperties()
'Parameters
'   db - The database used for the query
'   Attrib - Not used. All the properties are fetched.
'Return Value:
'   True if no error, else False

    Dim Sql$, Where$

    'Default return value False (Database Error)
    QueryProperties% = False

    ' Build the SQL statement
    Sql$ = "SELECT DISTINCT ID, StrID, StrName FROM PropertyIDs, Attributes"
    
    'Build the Where clause
    Where$ = " WHERE PropertyID = ID"

    'Append the where clause onto query string
    Sql$ = Sql$ + Where$

    'Perform the query
    On Error Resume Next
    Set dyQueryProperties = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    'Every thing is ok
    QueryProperties% = True
End Function

