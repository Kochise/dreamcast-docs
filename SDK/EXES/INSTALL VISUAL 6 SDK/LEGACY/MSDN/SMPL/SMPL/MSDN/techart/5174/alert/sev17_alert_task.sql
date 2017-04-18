exec msdb..sp_addtask 'CRITICAL_SQL_ERR_NOTIFICATION', 
	@subsystem = 'CmdExec', 
	@databasename = 'master', 
	@enabled = 1, 
	@freqtype = 2, 
	@activestartdate = 970101, @activeenddate = 99991231, 
	@activestarttimeofday = 0, @activeendtimeofday = 235959, 
	@loghistcompletionlevel = 2, 
	@emailcompletionlevel = 0, 
@command = 'NET SEND rudedog "CRITICAL SQL SERVER SEVERITY 17 ERROR ENCOUNTERED ON PRODSQL" ' 
go

exec msdb..sp_addalert @name = 'CRITICAL_SQL_SEV_17_ERROR',
	@message_id=0,
	@severity = 17,
	@delay_between_responses = 10, 
	@task_name = 'CRITICAL_SQL_ERR_NOTIFICATION'
go
