Attribute VB_Name = "Enumarate"
Option Explicit
Public MyDb As Database
Public FieldName As String, FieldType As String
Public TableName As String, DataName As String
Public DBLen As Integer

Public Sub listTable(TbName As String)
Dim td As TableDef, fld As Field
Dim Type2Str(13) As String, TmpAttrib As String, TmpFld As String

TmpAttrib = ""
If Len(TbName) = 0 Then VBDBForm.listtb.Clear Else VBDBForm.listfld.Clear
For Each td In MyDb.TableDefs
  If (td.Attributes And dbSystemObject) <> 0 Then TmpAttrib = " *System"
  If (td.Attributes And dbAttachedTable) <> 0 Then TmpAttrib = " *Attached"
  If (td.Attributes And dbAttachedODBC) <> 0 Then TmpAttrib = " *Attached ODBC"
  If Len(TbName) = 0 Then VBDBForm.listtb.AddItem td.Name & TmpAttrib

  'Map Fields for each TableDef
  TmpAttrib = ""
  If Len(TbName) > 0 And td.Name = TbName Then
    For Each fld In td.Fields
       Type2Str(8) = "Data/Time  "
       Type2Str(10) = "Text       "
       Type2Str(12) = "Memo       "
       Type2Str(1) = "Yes/No     "
       Type2Str(3) = "Integer    "
       Type2Str(4) = "Long       "
       Type2Str(5) = "Currency   "
       Type2Str(6) = "Single     "
       Type2Str(7) = "Double     "
       Type2Str(2) = "Byte       "
       Type2Str(11) = "Long Binary"
    
       Type2Str(0) = "Unknown    "
       TmpFld = fld.Name
       VBDBForm.listfld.AddItem TmpFld & "   " & Type2Str(fld.Type)        '    TmpAttrib
    Next fld
  End If
Next td
End Sub

Sub ComputeRPS(ReadOnly As Boolean, Iterations As Integer, _
 DataName As String, TableName As String, _
 FieldName As String, FieldType As String, connect As String)
 VBDBForm.TxtDAO.Text = Format(0, "0.####")
 VBDBForm.TxtRDO.Text = Format(0, "0.####")
 VBDBForm.TxtODBC.Text = Format(0, "0.####")
 DoEvents
 Dim i As Integer, StartTime As Double
 Dim CountRec As Long

 VBDBForm.LabMsg.Caption = VBDBForm.labdao.Caption & ":"
 DoEvents
 StartTime = Timer
 CountRec = 0
 For i = 1 To Iterations
 ' DAO
 VBDBForm.LabCount.Caption = i
 DoEvents
 CountRec = CountRec + ReadWrite.DBRead(DataName, ReadOnly, FieldName, _
                FieldType, connect, 0)
 VBDBForm.TxtDAO.Text = Format(CountRec / (Timer - StartTime), "0.####")

 DoEvents
Next

VBDBForm.LabMsg.Caption = VBDBForm.labrdo.Caption & ":"
DoEvents
StartTime = Timer
CountRec = 0
For i = 1 To Iterations
' RDO
VBDBForm.LabCount.Caption = i
DoEvents
CountRec = CountRec + ReadWrite.DBRead(DataName, ReadOnly, FieldName, FieldType, connect, 1)
VBDBForm.TxtRDO.Text = Format(CountRec / (Timer - StartTime), "0.####")

DoEvents
Next

VBDBForm.LabMsg.Caption = VBDBForm.labodbc.Caption & ":"
DoEvents
StartTime = Timer
CountRec = 0
For i = 1 To Iterations
  ' ODBC
  VBDBForm.LabCount.Caption = i
  DoEvents
  CountRec = CountRec + ReadWrite.DBRead(DataName, ReadOnly, FieldName, FieldType, connect, 2)
  VBDBForm.TxtODBC.Text = Format(CountRec / (Timer - StartTime), "0.####")
  DoEvents
Next

VBDBForm.LabMsg.Caption = ""
VBDBForm.LabCount.Caption = ""
End Sub



