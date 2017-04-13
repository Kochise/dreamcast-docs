Option Explicit

Function AlterAuthors (pChannel As Integer)
'
' This routine alters the Authors table with
' a TIMESTAMP column. Then it sends a 'dummy' update
' statement so that every row in the table
' gets a value in the TIMESTAMP column.

Dim lCmd$, lRetValue As Integer, lInfoText As String, Res%

    lRetValue = False
    lInfoText = mdiMA.panInfo.Caption
    mdiMA.panInfo.Caption = " Altering the authors table with a TIMESTAMP column."
    lCmd$ = "alter table authors add timestamp timestamp NULL "
    Res% = SQLComm%(pChannel, lCmd$)
    If Res% = SUCCEED% Then
        mdiMA.panInfo.Caption = " Every row in the authors table is now being updated."
        lCmd$ = "update authors set au_fname = au_fname"
        Res% = SQLComm%(pChannel, lCmd$)
        If Res% = SUCCEED% Then lRetValue = True
    End If
    mdiMA.panInfo.Caption = lInfoText
    AlterAuthors = lRetValue

End Function

Function AskifAlter ()
'
' This routine asks if the user wants to
' alter the Authors table with a TIMESTAMP
' column.

Dim lMsg$, Res%, lRetValue As Integer

    lMsg$ = "This sample application needs a column with "
    lMsg$ = lMsg$ + " the name TIMESTAMP and the datatype "
    lMsg$ = lMsg$ + " TIMESTAMP in the authors table." + NEWLINE$
    lMsg$ = lMsg$ + NEWLINE$ + "The reason is that this application "
    lMsg$ = lMsg$ + "uses Browse Mode and Optimistic Concurrency "
    lMsg$ = lMsg$ + "Control." + NEWLINE$ + NEWLINE$
    lMsg$ = lMsg$ + "There is no TIMESTAMP column in your authors "
    lMsg$ = lMsg$ + "table at this moment!" + NEWLINE$ + NEWLINE$
    lMsg$ = lMsg$ + "If you click on the OK button the application "
    lMsg$ = lMsg$ + "will create the column for you. If you click "
    lMsg$ = lMsg$ + "on the cancel button you won't be able to run "
    lMsg$ = lMsg$ + "this sample until the column is there."
    Beep
    Res% = MsgBox(lMsg$, 17, "Alter table authors")
    If Res% = IDOK Then
        lRetValue = True
    Else
        lRetValue = False
    End If
    AskifAlter = lRetValue

End Function

Function CheckifTimestamp (pChannel As Integer)
'
' This routine checks if there is a TIMESTAMP column
' for the table Authors.

Dim lCmd$, lRetValue As Integer, Res%

    lRetValue = False
    lCmd$ = "select count(*) from sysobjects so, syscolumns "
    lCmd$ = lCmd$ + "sc where so.id = sc.id "
    lCmd$ = lCmd$ + "and so.name = 'authors' "
    lCmd$ = lCmd$ + "and sc.name = 'timestamp' "
    lCmd$ = lCmd$ + "and sc.type = 37"
    Res% = SQLComm%(pChannel, lCmd$)
    If Res% = SUCCEED% Then
        Res% = SQLNextRow(pChannel)
        If Res% = REGROW Then
            If Val(SQLData(pChannel, 1)) > 0 Then
                lRetValue = True
            End If
        End If
    End If
    CheckifTimestamp = lRetValue

End Function

Function EmptyQualString ()
'
' This routine lets the user know that some condition
' for using Concurrency Control with Browse Mode is
' not fullfilled.

Dim lRetValue As String

    lRetValue = "The qual string is empty, which is not acceptable."
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "There are three mandatory preconditions for using "
    lRetValue = lRetValue + "Concurrency Control with Browse Mode."
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "1 - You must have a unique index."
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "2 - You must have a column named TIMESTAMP with the "
    lRetValue = lRetValue + " datatype TIMESTAMP in the specific table."
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "3 - You must add 'FOR BROWSE' to your SQL select statement "
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "Check to see if the unique index on the authors table "
    lRetValue = lRetValue + "has been dropped. That might be the problem."
    lRetValue = lRetValue + NEWLINE$ + NEWLINE$
    lRetValue = lRetValue + "This operation will not go through to SQL Server."
    EmptyQualString = lRetValue
    
End Function

