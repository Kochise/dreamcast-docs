Sub ExitApplication ()

Rem
Rem Exit SQL, then exit the application.
Rem

   SqlExit
   SqlWinExit
   End

End Sub

Sub InitializeApplication ()

Rem
Rem Initialize the connection to SQL Server
Rem
    SqlConn = 0
    DBLIB_VERSION$ = SqlInit$()
End Sub

