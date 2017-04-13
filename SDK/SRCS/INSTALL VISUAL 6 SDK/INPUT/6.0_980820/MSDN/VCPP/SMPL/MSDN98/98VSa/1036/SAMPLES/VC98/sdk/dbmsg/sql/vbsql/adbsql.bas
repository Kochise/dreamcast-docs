
Function Logon% (pServer$, pLoginId$, pPassword$, pWorkSta$, pAppName$)
'
' Open connection to SQL Server. Returns channel number
' to use in further communication with SQL Server through
' this channel.
'
' This function can be called one or several times from
' each form.

    Logon% = SqlOpenConnection(pServer$, pLoginId$, pPassword$, pWorkSta$, pAppName$)

End Function

Function SQLComm% (pChannel%, pCmd$)
'
' Generalized function to send SQL statements to SQL
' Server. If global variable ShowSql is set to True,
' the SQL statement is shown in a messagebox before
' it is sent to SQL Server

Dim Res%

    If ShowSql Then
        MsgBox pCmd$
    End If
    Do
        Res% = SqlCancel(pChannel%)
        If Res% <> SUCCEED% Then
            Exit Do
        End If
        Res% = SQLCmd(pChannel%, pCmd$)
        If Res% <> SUCCEED% Then
            Exit Do
        End If
        Res% = SqlExec(pChannel%)
        If Res% <> SUCCEED% Then
            Exit Do
        End If
        Res% = SqlResults%(pChannel%)
        If Res% <> SUCCEED% Then
            Exit Do
        End If
    Loop Until True
    SQLComm% = Res%

End Function

