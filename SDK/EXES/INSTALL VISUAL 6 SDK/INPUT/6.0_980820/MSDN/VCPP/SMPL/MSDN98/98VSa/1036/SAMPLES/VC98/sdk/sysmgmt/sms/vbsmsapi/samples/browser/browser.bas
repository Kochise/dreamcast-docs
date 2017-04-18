Attribute VB_Name = "basBROWSER"
Option Explicit

'Horizontal tab character (Can't have string constants)
'This is initialized in InitBrowser()
Dim HT$

'Size of one pixel in Twips (Set in Browser Form Load)
Global X_PIX_SIZE%
Global Y_PIX_SIZE%

'Here are a few extra BASETYPE for my convenience
'This is initialized in InitBrowser()
Global T_ROOTOBJECT As BASETYPE
Global T_SCALAR As BASETYPE

'Data structure for an entry in the Outline control
Type OutlineEntryData
    Type As BASETYPE
    Tag As Long
    Handle As Long
    RetrieveData As Integer
End Type

'Collection of OutlineEntryData structures.
'This is intialized in InitOutlineEntries()
Dim OutlineEntryDataArray() As OutlineEntryData
Const OUTLINE_ENTRY_ALLOC = 64  'How to allocated each time we run out

Function AddOutlineEntry&(sType As BASETYPE, lTag&, lHandle&, bRetrieveData%)
    Dim NewEntryIndex%
    
    'Initially an invalid value
    NewEntryIndex% = -1

    If OutlineEntryDataArray(0).Handle& <= 0 Then
        'Need to make more room
        OutlineEntryDataArray(0).Handle& = UBound(OutlineEntryDataArray) + 1
        ReDim Preserve OutlineEntryDataArray(0 To UBound(OutlineEntryDataArray) + OUTLINE_ENTRY_ALLOC)
        For NewEntryIndex% = OutlineEntryDataArray(0).Handle& To UBound(OutlineEntryDataArray) - 1
            OutlineEntryDataArray(NewEntryIndex%).Handle& = NewEntryIndex% + 1
        Next NewEntryIndex%
        OutlineEntryDataArray(NewEntryIndex%).Handle& = 0
    End If

    'Allocate an entry
    NewEntryIndex% = OutlineEntryDataArray(0).Handle&
    OutlineEntryDataArray(0).Handle& = OutlineEntryDataArray(NewEntryIndex%).Handle&

    'Copy the info into the new entry
    OutlineEntryDataArray(NewEntryIndex%).Type = sType
    OutlineEntryDataArray(NewEntryIndex%).Tag = lTag&
    OutlineEntryDataArray(NewEntryIndex%).Handle = lHandle&
    OutlineEntryDataArray(NewEntryIndex%).RetrieveData% = bRetrieveData%

    'Return handle to new entry
    AddOutlineEntry& = NewEntryIndex%
End Function

Sub FreeOutlineEntry(ByVal Handle&)
    Dim index%

    index% = ValidateOutlineEntryHandle%(Handle&)
    If index% > 0 Then
        OutlineEntryDataArray(index%).Handle& = OutlineEntryDataArray(0).Handle&
        OutlineEntryDataArray(0).Handle& = index%
    End If
End Sub

Sub GetOutlineEntry(ByVal Handle&, Entry As OutlineEntryData)
    Dim index%

    index% = ValidateOutlineEntryHandle%(Handle&)
    If index% > 0 Then
        Entry = OutlineEntryDataArray(index%)
    End If
End Sub

Function InitBrowser%()
    'Default return value is True
    InitBrowser = True

    'Horizontal tab character
    HT$ = Chr$(9)

    'Init the OutlineEntryData collection
    InitOutlineEntrys

    'Init Visual Basic SMS_API stuff
    T_ROOTOBJECT.enum = &HFFFFFFFE
    T_SCALAR.enum = &HFFFFFFFF
    If Not Init_SMSAPI() Then InitBrowser% = False
End Function

Sub InitOutlineEntrys()
    ReDim OutlineEntryDataArray(0 To 0)
    OutlineEntryDataArray(0).Handle& = 0
End Sub

Sub Main()
    'Initialize the application
    If InitBrowser() = True Then
        On Error Resume Next
        frmBrowser.Show
        On Error GoTo 0
    End If
End Sub

Sub SetOutlineEntry(ByVal Handle&, Entry As OutlineEntryData)
    Dim index%

    index% = ValidateOutlineEntryHandle%(Handle&)
    If index% > 0 Then
        OutlineEntryDataArray(index%) = Entry
    End If
End Sub

Function ValidateOutlineEntryHandle%(Handle&)
    Dim index%, i%

    'Default is an error
    ValidateOutlineEntryHandle% = 0
    
    index% = CInt(Handle&)
    
    'Debugging Stuff
    If index% <= 0 Or index% > UBound(OutlineEntryDataArray) Then
        MsgBox "Entry data index out of bounds!"
        Exit Function
    End If
    
    i% = CInt(OutlineEntryDataArray(0).Handle&)
    Do While i% <> 0
        If i% = index% Then
            MsgBox "Entry data index is invalid!"
            Exit Function
        Else: i% = CInt(OutlineEntryDataArray(i%).Handle&)
        End If
    Loop
    'End Debugging stuff

    ValidateOutlineEntryHandle% = index%
End Function

