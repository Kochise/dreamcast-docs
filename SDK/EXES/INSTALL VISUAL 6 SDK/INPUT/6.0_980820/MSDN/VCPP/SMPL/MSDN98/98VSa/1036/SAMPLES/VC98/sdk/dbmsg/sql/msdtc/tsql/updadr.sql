if exists (select * from sysobjects where id = object_id('dbo.update_addr') and sysstat & 0xf = 4)
	drop procedure dbo.update_addr
GO

CREATE PROCEDURE update_addr(@au_id varchar(11), @addr varchar(40)) AS
	update authors set address = @addr where au_id = @au_id

GO

