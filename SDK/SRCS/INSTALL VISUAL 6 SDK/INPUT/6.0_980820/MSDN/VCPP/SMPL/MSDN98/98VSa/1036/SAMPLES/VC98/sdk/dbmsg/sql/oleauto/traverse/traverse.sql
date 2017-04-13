/** This samples shows how to use the traversal syntax for object hierarchies
*** 
**/

declare @hr int, @pobj int
declare @source varchar(30), @desc varchar (200)

/* create a new SQLOLE object */
exec @hr = sp_OACreate "SQLOLE.SQLServer", @pobj out
if @hr <> 0
	goto Err

/* open a connection to the local database */
exec @hr = sp_OAMethod @pobj, 'Connect("", "sa")'
if @hr <> 0
	goto Err

/* get all keys from other tables that reference the Authors table from Pubs database, including all candidate tables */
/* the query result is returned as one string                                                                         */
exec @hr = sp_OAMethod @pobj, 'Databases("pubs").Tables("authors").EnumReferencingKeys(IncludeAllCandidates := FALSE).GetRangeString'
if @hr <> 0
	goto Err

/* get the number of columns returned by the above query result */
exec @hr = sp_OAGetProperty @pobj, 'Databases("pubs").Tables("authors").EnumReferencingKeys(IncludeAllCandidates := FALSE).Columns'
if @hr <> 0
	goto Err

goto Done

Err:	
	Print '## ERROR ##'
	exec sp_OAGetErrorInfo null, @source OUT, @desc OUT
	select hr =  convert (binary(4), @hr), source = @source, description = @desc
	goto Done

Done:
	exec sp_OADestroy @pobj

go