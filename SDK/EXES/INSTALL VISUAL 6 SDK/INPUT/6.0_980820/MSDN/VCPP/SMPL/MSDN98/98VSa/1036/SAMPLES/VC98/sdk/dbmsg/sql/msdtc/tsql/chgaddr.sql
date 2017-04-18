Use Pubs
GO

if exists (select * from sysobjects where id = object_id('dbo.change_addr') and sysstat & 0xf = 4)
	drop procedure dbo.change_addr
GO

CREATE PROCEDURE change_addr(@au_id varchar(11), @addr varchar(40), @toserver varchar(12) ) AS

declare @execstr varchar(200)

-- 1. Start a DTC Transaction

BEGIN DISTRIBUTED TRAN

-- 2. Change local author information

update authors set address = @addr where au_id = @au_id 

-- 3. Make a string with the server name, procedure to execute and parameters
select @execstr = @toserver + '.pubs..update_addr ' 

-- 4. Update remote server
--    NOTE THAT THIS SERVERS MUST BE ADDED TO EACH OTHER VIA sp_addserver and sp_addremotelogin

exec @execstr @au_id, @addr

-- 5. Commit the DTC transaction

COMMIT TRAN
GO



