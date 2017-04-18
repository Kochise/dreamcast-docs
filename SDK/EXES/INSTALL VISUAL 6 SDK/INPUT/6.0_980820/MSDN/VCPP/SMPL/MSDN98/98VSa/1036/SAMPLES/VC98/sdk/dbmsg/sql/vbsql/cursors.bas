Rem Global Definitions

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
Global Const LoginTimout% = 30
Global Const QueryTimeout% = 60
Rem Globals for cursor operations

Global CursorHandle%
Global RowStatus&()
Global OpenTran%
Global CursorColName$(255)
Global CursorColLen&(255)
Global NumRowsInCursor%
Global NumRowsInKeyset&
Global ScrollOpt%
Global NumCols%
Global CursorSliderValue%           'To tell if we are scrolling up or down
Global OutputData(20) As String     'Storage for up to 21 rows

