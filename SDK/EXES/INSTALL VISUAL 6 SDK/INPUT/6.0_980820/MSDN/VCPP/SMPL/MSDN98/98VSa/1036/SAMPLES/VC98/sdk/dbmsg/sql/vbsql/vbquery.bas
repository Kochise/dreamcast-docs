Rem These handle the SQL Server connection for this application

' Declare SqlConn as Integer in VBWin, Long in VBDOS
Global SqlConn As Integer

Global DBLIB_VERSION$
Global PrimaryWindowTitle$
Global ServerName$
Global LoginID$
Global Password$
Global DatabaseName$
Global SQLStatus%
Global Const LoginTimeout% = 30
Global Const QueryTimeout% = 60

