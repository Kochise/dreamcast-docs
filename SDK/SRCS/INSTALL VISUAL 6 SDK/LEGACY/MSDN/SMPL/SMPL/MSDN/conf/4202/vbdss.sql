/* DSS.SQL */

use pubs
go 


/* ------------------------ */
/* create users             */
/* ------------------------ */

/* add logins to server */
sp_addlogin dss_manager, dss_manager, pubs
go
sp_addlogin dss_rep, dss_rep, pubs
go
sp_addlogin dss_programmer, dss_programmer, pubs
go

/* add groups to database */
sp_addgroup dss_managers
go
sp_addgroup dss_reps
go
sp_addgroup dss_programmers
go

/* add users to database and groups */
sp_adduser dss_manager, dss_manager, dss_managers
go
sp_adduser dss_rep, dss_rep, dss_reps
go
sp_adduser dss_programmer, dss_programmer, dss_programmers
go

/* ------------------------ */
/* create dss objects       */
/* ------------------------ */


/* dss table */
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('dss'))
     DROP table dss
go

create table dss (
	month smallint not null,
	year smallint not null,
	state char(2) null,
	title varchar(80) not null,
	qty smallint not null,
	dol money
	)
	
go

/* refresh dss stored procedure  */

IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('sp_dss_refresh'))
     DROP procedure sp_dss_refresh 
go


create procedure sp_dss_refresh as
begin

	/* begin this transaction */
	begin tran 

	/*delete old data */
	print "Deleting DSS..."
	delete from dss
	/* check for error */
	if @@error <> 0 
	begin
		print "Error deleting DSS.  Rolling back."
		rollback tran
		return
	end


	/* insert new data */
	print "Inserting into DSS..."
	insert into dss
	select 
		month=datepart(month, date),
		year=datepart(year, date),
		state, 
		title, 
		qty=sum(qty),
		dol=sum(qty*price)
	from 
		titles t,
		sales s,
		stores o
	where
		t.title_id=s.title_id and
		s.stor_id=o.stor_id
	group by 
		datepart(month, date),
		datepart(year, date),
		title,
		state
	/* check for error */
	if @@error <> 0
	begin
		Print "Error inserting.  Rolling back."
		rollback tran
		return
	end

	/* commit transaction */
	commit tran
	print "Done."

end
go


/* --------------------------------- */
/* create end-user stored procedures */
/* --------------------------------- */


IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('sp_dss_detail'))
     DROP procedure sp_dss_detail
GO

/* shows detail for all states or a specific state (year,month,title,state) */
create procedure sp_dss_detail 
@state varchar(2)
AS
begin
	waitfor delay '00:00:10'  /* wait a while, so things don't happen so fast */
     
     select @state = ltrim(@state) + '%'
     select 
		year,   
		month,
		title,                                                                            
		state, 
		qty,    
		dol                       
     	from 
		dss
	where 
		state like @state

end
GO



IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('sp_dss_sum'))
     DROP procedure sp_dss_sum
GO

/* shows sales summarrized by state (year,month,title) */
create procedure sp_dss_sum  
AS
begin
	waitfor delay '00:00:10'  /* wait a while, so things don't happen so fast */
     
     	select 
		year,   
		month,
		title,    
		qty=sum(qty),    
		dol=sum(dol)                       
     	from 
		dss
     	group by
		year,   
		month,
		title
end	
go

IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('sp_dss_states'))
     DROP procedure sp_dss_states
GO

/* shows list of states for selection */
create procedure sp_dss_states
AS
begin
	waitfor delay '00:00:10'  /* wait a while, so things don't happen so fast */
     
     	select 
		state
     	from 
		dss
     	group by
		state
	order by
		state
end	
go


/* ------------------------ */
/* create permissions       */
/* ------------------------ */

/* dss_managers have access to both         */
/* dss_reps only have access to sp_dss reps */
/* dss_sales as access to nothing           */

GRANT EXECUTE ON sp_dss_detail TO dss_managers		/* managers have state level */
go
GRANT EXECUTE ON sp_dss_sum TO dss_reps, dss_managers		/* all have */ 
go
GRANT EXECUTE ON sp_dss_states TO dss_reps, dss_managers		/* all have */
go

/* ------------------------------------------------------ */
/* Refresh the DSS table.                                 */
/* This would be run at regular intervals (e.g. nightly). */
/* ------------------------------------------------------ */

exec sp_dss_refresh
