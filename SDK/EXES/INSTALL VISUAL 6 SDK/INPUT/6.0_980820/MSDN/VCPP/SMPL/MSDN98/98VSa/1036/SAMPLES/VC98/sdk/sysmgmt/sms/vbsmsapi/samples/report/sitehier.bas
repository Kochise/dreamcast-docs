Attribute VB_Name = "SITEHIER"
Option Explicit

'//****************************************************************************
'//
'//  Copyright (c) 1995, Microsoft Corporation
'//
'//  File:  SITEHIER.BAS
'//
'//  History:
'//
'//      Gary Fuehrer, SEA   5/9/95      Created.
'//
'//****************************************************************************

'These need to be the same as outline control picture types
'  (see SITEHIER.FRM in global declarations section)
Global Const SITEHIERTYPE_ROOT = MSOUTLINE_PICTURE_CLOSED
Global Const SITEHIERTYPE_SITE = MSOUTLINE_PICTURE_OPEN
Global Const SITEHIERTYPE_DOMAIN = MSOUTLINE_PICTURE_LEAF

Type SiteRec
    ItemNum As Long
    Parent As String
    Code As String
    Type As Integer
    TypeName As String
    Depth As Integer
    Name As String
End Type

'For use by QuerySite%() and FetchSite%() ONLY
Dim dyQuerySite As Recordset

Function FetchSite%(Site As SiteRec, Flush%, DBError%)
'   Fetches another site record from the dyQuerySite dynaset
'Parameters:
'   Site   - Filled in with next site record.
'   Flush% - Usually False. If True, the fetch is ended.
'   DBError% - Returns True when DB error occures.
'Return Value:
'   True if another record fetched, else False (no more)

    DBError% = True
    FetchSite% = False

    If dyQuerySite.EOF Or Flush% Then
        dyQuerySite.Close
    Else
        ' Populate the site record from the dyQuerySite
        ' dynaset and find the next record
        Site.ItemNum& = dyQuerySite("ItemNum")
        If IsNull(dyQuerySite("Parent")) Then
            Site.Parent$ = ""
        Else: Site.Parent$ = Trim$(dyQuerySite("Parent"))
        End If
        If IsNull(dyQuerySite("Code")) Then
            Site.Code$ = ""
        Else: Site.Code$ = Trim$(dyQuerySite("Code"))
        End If
        Site.Type% = dyQuerySite("Type")
        Site.TypeName$ = Trim$(dyQuerySite("TypeName"))
        Site.Depth% = dyQuerySite("Depth")
        Site.Name$ = Trim$(dyQuerySite("Name"))

        On Error Resume Next
        dyQuerySite.MoveNext
        If Err > 0 Then Exit Function
        On Error GoTo 0

        FetchSite% = True
    End If

    DBError% = False
End Function

Function FindSite%(db As Database, Site As SiteRec)
'   Finds a specific site given the ItemNum
'Parameters
'   db - The database variable
'   Site - The following members are used to identify the site
'       ItemNum&
'Return Value:
'   Count of number of records found
'   Site - Filled with one of those found

    Dim Sql$
    Dim dySite As Recordset

    'Set default return value -1 (Database error)
    FindSite% = -1

    Sql$ = "SELECT ItemNum, Parent, Code, Type, TypeName, Depth, Name FROM [Site Hierarchy]"
    Sql$ = Sql$ + " WHERE ItemNum = " + CStr(Site.ItemNum&)

    ' If an error occurs exit the function
    On Error Resume Next
    Set dySite = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    ' Populate the site record
    If Not dySite.EOF Then
        Site.ItemNum& = dySite("ItemNum")
        If IsNull(dySite("Parent")) Then
            Site.Parent$ = ""
        Else: Site.Parent$ = Trim$(dySite("Parent"))
        End If
        If IsNull(dySite("Code")) Then
            Site.Code$ = ""
        Else: Site.Code$ = Trim$(dySite("Code"))
        End If
        Site.Type% = dySite("Type")
        Site.TypeName$ = Trim$(dySite("TypeName"))
        Site.Depth% = dySite("Depth")
        Site.Name$ = Trim$(dySite("Name"))
    End If

    ' Return the record count
    FindSite% = dySite.RecordCount
End Function

Function InsertSite&(db As Database, Site As SiteRec)
'   Inserts the Site record into the given data base
'Parameters
'   db    - The database used for the query
'   Site  - The Site record
'Return Value:
'   The number of records inserted

    Dim qy As QueryDef

    ' Default return value False (Failed)
    InsertSite& = -1

    ' Build the insert statement
    Set qy = db.QueryDefs("InsertSite")
    qy![INPUT ItemNum] = Site.ItemNum&
    qy![INPUT Parent] = Site.Parent$
    qy![INPUT Code] = Site.Code$
    qy![INPUT Type] = Site.Type%
    qy![INPUT TypeName] = Site.TypeName$
    qy![INPUT Depth] = Site.Depth%
    qy![INPUT Name] = Site.Name$

    'Try to insert the record
    On Error Resume Next
    qy.Execute
    If Err > 0 Then Exit Function
    qy.Close
    On Error GoTo 0

    'Return insert count
    InsertSite& = 1
End Function

Function NewSiteHierarchyDatabase%(db As Database, ErrStr$)
    Dim td As TableDef, qy As QueryDef, fd As Field, ix As Index

    'Default return value False (Failed)
    NewSiteHierarchyDatabase% = False

    On Error GoTo NewMachineDatabaseErr
    
    Set td = New TableDef
    td.Name = "Site Hierarchy"

        'Fields
        Set fd = New Field
        fd.Name = "ItemNum"
        fd.Type = DB_LONG
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Parent"
        fd.Type = DB_TEXT
        fd.Size = 4
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Code"
        fd.Type = DB_TEXT
        fd.Size = 4
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Type"
        fd.Type = DB_INTEGER
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "TypeName"
        fd.Type = DB_TEXT
        fd.Size = 16
        fd.AllowZeroLength = True
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Depth"
        fd.Type = DB_INTEGER
        td.Fields.Append fd

        Set fd = New Field
        fd.Name = "Name"
        fd.Type = DB_TEXT
        fd.Size = 255
        fd.AllowZeroLength = True
        td.Fields.Append fd

        'Indexes
        Set ix = New Index
        ix.Name = "SortKey"
        ix.Primary = True
        ix.Unique = True
        ix.Fields = "ItemNum"
        td.Indexes.Append ix

    db.TableDefs.Append td

    'Make QueryDefs for common insert queries and selects
    Set qy = db.CreateQueryDef("InsertSite", "PARAMETERS [INPUT ItemNum] Long, [INPUT Parent] Text, [INPUT Code] Text, [INPUT Type] Short, [INPUT TypeName] Text, [INPUT Depth] Short, [INPUT Name] Text; INSERT INTO [Site Hierarchy] (ItemNum, Parent, Code, Type, TypeName, Depth, Name) SELECT [INPUT ItemNum] As ItemNum, '|[INPUT Parent]|' As Parent, '|[INPUT Code]|' As Code, [INPUT Type] As Type, '|[INPUT TypeName]|' As TypeName, [INPUT Depth] As Depth, '|[INPUT Name]|' As Name")

    'Return success
    NewSiteHierarchyDatabase% = True
    Exit Function

NewMachineDatabaseErr:
    ErrStr$ = Error$
    Exit Function
End Function

Function NewSiteHierarchyReportWindow%(hConnect&, ByVal FileSpec$, ErrStr$)
    Dim i%, Ret&, TempPath$, TempSpec$, frm As Form
    Dim db As Database, td As TableDef, fd As Field, ix As Index

    'Default return value zero (Failed)
    NewSiteHierarchyReportWindow% = 0

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
    On Error GoTo NewSiteHierarchyReportWindowErr
    If FileSpec$ > "" Then
        'File Open: so copy the file the user selected
        ErrStr$ = "Could not create a temporary copy of " + FileSpec$ + ".+"
        FileCopy FileSpec$, TempSpec$
    Else
        'File New: so create a new empty document
        ErrStr$ = "Could not create a temporary file for the new report."
        Kill TempSpec$
        Set db = CreateDatabase(TempSpec$, DB_LANG_GENERAL)
        i% = NewSiteHierarchyDatabase%(db, ErrStr$)
        db.Close
        If Not i% Then GoTo NewSiteHierarchyReportWindowErr
    End If
    On Error GoTo 0

    'Pass the new document the file name to use
    InitReporthConnect& = hConnect&
    InitReportFileSpec$ = FileSpec$
    InitReportTempSpec$ = TempSpec$
    If InitReportFileSpec$ <= "" Then InitReportNewNumber% = InitReportNewNumber% + 1

    'Create a new document window
    On Error GoTo NewSiteHierarchyReportWindowErr
    ErrStr$ = "Could not create site report document window."
    Set frm = New frmSiteHierarchyReport
    Load frm
    On Error GoTo 0

    'Register document window with MDI
    
    i% = RegisterReportWindow%(frm, ErrStr$)
    If i% <= 0 Then GoTo NewSiteHierarchyReportWindowErr

    'Show the document window
    frm.Show
    NewSiteHierarchyReportWindow% = i%
    Exit Function

NewSiteHierarchyReportWindowErr:
    On Error Resume Next
    If Not frm Is Nothing Then Unload frm
    If Not db Is Nothing Then db.Close
    Kill TempSpec$
    Exit Function
End Function

Function QuerySite%(db As Database, Site As SiteRec)
'   Queries the Site Hierarchy table and creates
'   a dynaset (dyQuerySite) used by FetchSite()
'   ordered by path
'Parameters
'   db - The database used for the query
'   Site - The following are used in the where clause
'       .Parent$ - Specifies the parent site code
'       .Code$   - Specifies the item (wildcard if enpty)
'Return Value:
'   True if no error, else False

    Dim Sql$, Where$

    'Default return value False (Database Error)
    QuerySite% = False

    ' Build the SQL statement
    Sql$ = "SELECT ItemNum, Parent, Code, Type, TypeName, Depth, Name FROM [Site Hierarchy]"

    'Build the Where clause
    Where$ = ""

    'Specify the parent
    If Site.Parent$ > "" Then
        Where$ = " WHERE Parent = '" + Site.Parent$ + "'"
    Else: Where$ = " WHERE Depth = 0"
    End If

    'Optionally specify the item (Site or Domain)
    If Site.Code$ > "" Then
        If Where$ > "" Then
            Where$ = Where$ + " AND "
        Else: Where$ = " WHERE "
        End If
        Where$ = Where$ + "Code = '" + Site.Code$ + "'"
    End If

    'Append the where clause onto query string
    Sql$ = Sql$ + Where$

    'Perform the query
    On Error Resume Next
    Set dyQuerySite = db.OpenRecordset(Sql$, dbOpenDynaset)
    If Err > 0 Then Exit Function
    On Error GoTo 0

    'Every thing is ok
    QuerySite% = True
End Function

