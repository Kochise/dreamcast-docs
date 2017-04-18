Rem Globals

Rem These handle the SQL Server connection

Global DBLIB_VERSION$
Global PrimaryWindowTitle$
Global SqlConn%
Global ServerName$
Global LoginID$
Global Password$
Global DatabaseName$
Global SQLStatus%
Global DefServer$
Global DefLogin$
Global Const LoginTimeout% = 30
Global Const QueryTimeout% = 60

Rem Additional needed for updates in browse mode
Global SqlUpdConn%

