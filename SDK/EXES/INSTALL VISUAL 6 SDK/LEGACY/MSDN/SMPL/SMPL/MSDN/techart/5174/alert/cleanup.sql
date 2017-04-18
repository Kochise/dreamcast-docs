use msdb
go

sp_droptask CRITICAL_SQL_ERR_NOTIFICATION
go

sp_dropalert CRITICAL_SQL_SEV_17_ERROR
go
