sp_addextendedproc 'xp_proclist', 'xp.dll'
go
sp_addextendedproc 'xp_disklist', 'xp.dll'
go
sp_addextendedproc 'xp_diskfree', 'xp.dll'
go
sp_addextendedproc 'xp_scan_xbase', 'xp.dll'
go
sp_addextendedproc 'xp_echo', 'xp.dll'
go
sp_addextendedproc 'xp_trace', 'xp.dll'
go
grant exec on xp_proclist to public
go
grant exec on xp_disklist to public
go
grant exec on xp_diskfree to public
go
grant exec on xp_scan_xbase to public
go
grant exec on xp_echo to public
go
grant exec on xp_trace to public
go
