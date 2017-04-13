' Sample script for sequencing an installation from outside MSI - test code only, hardwired paths
' Requires AutoApi.DLL to be self-registered (use REGSVR32 AutoApi.DLL)
Sub SingleStep()
   Dim Engine As Object, ActionView As Object
   Dim Sequence As Integer, Action As String, Condition As String
   Dim Test As Integer, Result As Integer
   Dim ExitAction As String, ErrorAction As String, CancelAction As String
   Set MsiAuto = CreateObject("Msi.ApiAutomation")
   MsiAuto.UILevel = 5 'Full UI (no enums yet)
   MsiAuto.EnableLog "warped", "C:\temp\step.log"
   Set Engine = MsiAuto.OpenPackage("C:\msi\testdb\testdb.msi")
'  Engine.Property("SOURCEDIR") = "C:\msi\testdb"  ' needed if source location different than database
   Set Database = Engine.Database
   Set ActionView = Database.OpenView("SELECT Action,Condition,Sequence FROM InstallSequence ORDER BY Sequence")
   ActionView.Execute
   Do
      Set Record = ActionView.Fetch
      If Record Is Nothing Then Exit Do
      Sequence = Record.IntegerData(3)
      Action = Record.StringData(1)
      Condition = Record.StringData(2)
      If Sequence <= 0 Then
         Debug.Print Sequence; " Action = "; Action; "  (exit dialog)"
         If (Sequence = -1) Then ExitAction = Action
         If (Sequence = -2) Then CancelActon = Action
         If (Sequence = -3) Then ErrorAction = Action
      Else
         Test = Engine.EvaluateCondition(Condition)
         Debug.Print Sequence; " Action = "; Action; "  Condition:"; Test;
         If Test = iecError Then Debug.Print "Invalid Expression"; Condition
         If Test <> iecFalse Then
            Result = Engine.DoAction(Action)
            Debug.Print "  Result: "; Result
            If Result <> iesSuccess And Result <> iesNoAction Then Exit Do
         Else
            Debug.Print "(not called)"
         End If
      End If
   Loop
   If Result = iesSuccess Then Engine.DoAction (ExitAction)
   If Result = iesFailure Then Engine.DoAction (ErrorAction)
   If Result = iesUserExit Then Engine.DoAction (CancelAction)
   Debug.Print "Sequence completed"
End Sub
