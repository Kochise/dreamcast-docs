Attribute VB_Name = "InitSchedule"
Option Explicit
'The Exchange version of SP732EN.OLB must be installed.
'The version shipped with Windows 95 is broken
Global SPlusApplication As SPL.Application
Global scdSchedule As SPL.Schedule
'Arrays of names
Global QuickSearch$
Global FieldNames$(1 To 30) 'Field name for random item
Global TableNames$(0 To 7) 'Table Names
Global SFieldNames$(0 To 10) 'Schedule Field Names
Global STableNames$(0 To 8) 'Schedule Table Names

Sub SchedulePlus_Init()
Set SPlusApplication = CreateObject("Schedule+.Application")
If SPlusApplication.LoggedOn = False Then
    SPlusApplication.Logon
End If
Set scdSchedule = SPlusApplication.ScheduleLogged
End Sub
Function NameToTable(AnItem As Item, ByVal NameIs$) As Object
'We trim automatically if needed
'This keeps calling code simpler
If InStr(NameIs$, ":") > 1 Then
    NameIs$ = Left(NameIs$, InStr(NameIs$, ":") - 1)
End If
    Select Case NameIs$
        'Tables
        Case "Projects"
            Set NameToTable = AnItem.Projects
       Case "Contacts"
            Set NameToTable = AnItem.Contacts
       Case "Roles"
            Set NameToTable = AnItem.Roles
       Case "AccessControls"
            Set NameToTable = AnItem.AccessControls
       Case "AlarmsToRing"
            Set NameToTable = AnItem.AlarmsToRIng
       Case "Attendees"
            Set NameToTable = AnItem.Attendees
       Case "Exceptions"
            Set NameToTable = AnItem.Exceptions
       Case "DeletedItems"
            Set NameToTable = AnItem.DeletedItems
       Case "SingleTasks", "Tasks", "RecurringTasks", _
             "SingleEvents", "Events", "RecurringEvents", _
              "SingleAppointments", "Appointments", "RecurringAppointments"
              Set NameToTable = Nothing
            MsgBox NameIs$ & " cannot be accessed except on the Schedule object.", 32, "ERROR"

       Case Else 'Schedule specific items are omitted
            MsgBox "Unable to retrieve " & NameIs$ & ".", 32, "ERROR"
    End Select
End Function
Sub SetPropertyValue(ByVal NameIs$, AnItem As Object)
'We CANNOT use "As Item", because of SetProperties method :-(
Dim ValueIs As Variant
Dim OldValue As Variant
On Error GoTo NoWriteProperty
OldValue = AnItem.GetProperty((NameIs$))
If IsError(OldValue) Then OldValue = "{new}"
ValueIs = InputBox("New Value for " & NameIs$ & " is", "Simplified Input", OldValue)
If Len(ValueIs) = 0 Then Exit Sub 'No value
Select Case NameIs$
Case "CreatorName"
    AnItem.SetProperties CreatorName:=ValueIs
Case "Text"
    AnItem.SetProperties Text:=ValueIs
Case "Start"
    AnItem.SetProperties Start:=ValueIs
Case "End"
    AnItem.SetProperties End:=ValueIs
Case "AccessActual"
    AnItem.SetProperties AccessActual:=ValueIs
Case "ChangeNumber"
    AnItem.SetProperties ChangeNumber:=ValueIs
Case "LastModified"
    AnItem.SetProperties LastModified:=ValueIs
Case "BusyType"
    AnItem.SetProperties BusyType:=ValueIs
Case "AlarmAmountOriginal"
    AnItem.SetProperties AlarmAmountOriginal:=ValueIs
Case "AlarmTypeUnitOriginal"
    AnItem.SetProperties AlarmTypeUnitOriginal:=ValueIs
Case "AlarmTypeUnit"
    AnItem.SetProperties AlarmTypeUnit:=ValueIs
Case "AlarmAmount"
    AnItem.SetProperties AlarmAmount:=ValueIs
Case "Notify"
    AnItem.SetProperties Notify:=ValueIs
Case "Ring"
    AnItem.SetProperties Ring:=ValueIs
Case "Goal"
    AnItem.SetProperties Goal:=ValueIs
End Select
'Make sure file is updated
AnItem.Flush
Exit_SetPropertiesValue:
Exit Sub

NoWriteProperty:
'Some of the above WILL ERROR -- done on purpose. :-)
MsgBox "Cannot change " & NameIs$ & ". " & Err.Description, 16, "Fail to set Property Value"
Resume Exit_SetPropertiesValue
End Sub

Sub DefineFields()
Dim I As Integer
SFieldNames$(0) = "ScheduleID"
SFieldNames$(1) = "Name"
'Next demonstrates that the password cannot be read
SFieldNames$(2) = "Password"
SFieldNames$(3) = "DayStartsAt"
SFieldNames$(4) = "DayEndsAt"
SFieldNames$(5) = "LastCleanUp"
SFieldNames$(6) = "DefaultHomePhone1"
SFieldNames$(7) = "Ranges"
SFieldNames$(8) = "SoundDefault"
SFieldNames$(9) = "SoundLevel"
' Next field is to demonstrate that data items are NOT returned
'not an Property object
SFieldNames$(10) = "Visible" 'This always exists

FieldNames$(1) = "CreatorName"
FieldNames$(2) = "Text"
FieldNames$(3) = "Start"
FieldNames$(4) = "End"
FieldNames$(5) = "AccessActual"
FieldNames$(6) = "ChangeNumber"
FieldNames$(7) = "LastModified"
FieldNames$(8) = "BusyType"
FieldNames$(9) = "AlarmAmountOriginal"
FieldNames$(10) = "AlarmTypeUnitOriginal"
FieldNames$(11) = "AlarmTypeUnit"
FieldNames$(12) = "AlarmAmount"
FieldNames$(13) = "Notify"
FieldNames$(14) = "Exceptions"
FieldNames$(15) = "Attendees"
FieldNames$(16) = "Contacts"
FieldNames$(17) = "AccessControls"
FieldNames$(18) = "AlarmsToRing"
FieldNames$(19) = "SingleAppointments"
FieldNames$(20) = "RecurringAppointments"
FieldNames$(21) = "Appointments"
FieldNames$(22) = "SingleTasks"
FieldNames$(23) = "RecurringTasks"
FieldNames$(24) = "Tasks"
FieldNames$(25) = "SingleEvents"
FieldNames$(26) = "RecurringEvents"
FieldNames$(27) = "Events"
FieldNames$(28) = "DeletedItems"
FieldNames$(29) = "Projects"
FieldNames$(30) = "Roles"

STableNames$(0) = "Events"
STableNames$(1) = "Tasks"
STableNames$(2) = "Appointments"
STableNames$(3) = "SingleAppointments"
STableNames$(4) = "RecurringAppointments"
STableNames$(5) = "SingleEvents"
STableNames$(6) = "RecurringEvents"
STableNames$(7) = "SingleTasks"
STableNames$(8) = "RecurringTasks"

TableNames$(0) = "Contacts"
TableNames$(1) = "AccessControls"
TableNames$(2) = "AlarmsToRing"
TableNames$(3) = "DeletedItems"
TableNames$(4) = "Projects"
TableNames$(5) = "Roles"
TableNames$(6) = "Attendees"
TableNames$(7) = "Exceptions"
QuickSearch$ = "|"
For I = LBound(TableNames$) To UBound(TableNames$)
    QuickSearch$ = QuickSearch$ + TableNames$(I) + "|"
Next I
For I = LBound(STableNames$) To UBound(STableNames$)
    QuickSearch$ = QuickSearch$ + STableNames$(I) + "|"
Next I
End Sub

Function NewKey$() 'Simple counter supplies unique IDs
Static counter As Long
counter = counter + 1
NewKey$ = Format(counter, "0")
End Function
