/** This script updates a table and calls an extended 			**/
/** procedure which retrieves rows from the same table.			**/
/** Its purpose is to show how two connections can work with 		**/
/** the same rows, without blocking each other. This is possible	**/
/** because the connection opened by the extended stored 		**/
/** procedure xp_gettable is bound to the connection from which the 	**/
/** procedure is called from.						**/
  
sp_addextendedproc 'xp_gettable', 'xp_odbc.dll'
go

begin transaction
update pubs..authors
	set phone =phone
exec xp_gettable 'pubs..authors'
commit transaction
go

sp_dropextendedproc 'xp_gettable'
go

dbcc xp_odbc(free)
go