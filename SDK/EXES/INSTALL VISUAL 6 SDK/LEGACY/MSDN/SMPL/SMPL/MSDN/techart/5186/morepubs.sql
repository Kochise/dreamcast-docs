/* Microsoft SQL Server - Scripting							*/
/* Database: pubs										*/
/*												*/
/* The following script creates the Microsoft SQL Server login and 	*/
/* objects referenced by MYBTRV32.DLL and ODBCAPP.EXe in the pubs 	*/
/* pubs database.  The script adds the 'pubsuser' account and creates 	*/
/* the stored procedures and tables referenced by the applications	*/
/* mentioned above.									*/
/*												*/ 
/* Creation Date 12/12/96 1:23:27 PM 						*/


use master
go

/************************************************************************
	CREATE THE 'pubsuser' MICROSOFT SQL SERVER LOGIN
*************************************************************************/
sp_addlogin pubsuser, pubsuser, pubs
go



/************************************************************************
	Create the tables referenced by MYBTRV32.DLL
*************************************************************************/
use pubs
go

/****** Object:  Table dbo.TitlePublisher    Script Date: 2/7/97 1:24:36 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.TitlePublisher') and sysstat & 0xf = 3)
	drop table dbo.TitlePublisher
GO

/****** Object:  Table dbo.bsales    Script Date: 2/7/97 1:24:36 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.bsales') and sysstat & 0xf = 3)
	drop table dbo.bsales
GO

/****** Object:  Table dbo.TitlePublisher    Script Date: 2/7/97 1:24:36 PM ******/
CREATE TABLE dbo.TitlePublisher (
	title_id varchar (6) NOT NULL ,
	title varchar (80) NOT NULL ,
	type char (12) NOT NULL ,
	pub_id char (4) NULL ,
	price money NULL ,
	advance money NULL ,
	royalty int NULL ,
	ytd_sales int NULL ,
	pub_name varchar (40) NULL ,
	city varchar (20) NULL ,
	state char (2) NULL ,
	country varchar (30) NULL 
)
GO
GRANT REFERENCES, SELECT, INSERT, DELETE, UPDATE ON TITLEPUBLISHER TO pubsuser
go
PRINT 'Table TitlePublisher Created'
GO
INSERT TitlePublisher
 SELECT T.title_id, T.title, T.type, P.pub_id, T.price, T.advance, T.royalty, T.ytd_sales, P.pub_name, P.city, P.state, P.country 
 FROM titles T, publishers P
 WHERE T.pub_id = P.pub_id
GO
PRINT 'Table TitlePublisher Populated'
GO



/****** Object:  Table dbo.bsales    Script Date: 2/7/97 1:24:37 PM ******/
CREATE TABLE dbo.bsales (
	stor_id char (4) NOT NULL ,
	title_id varchar (6) NOT NULL ,
	ordnum varchar (20) NOT NULL ,
	qty smallint NOT NULL ,
	payterms varchar (12) NULL 
)
GO
GRANT REFERENCES, SELECT, INSERT, DELETE, UPDATE ON BSALES TO pubsuser
go
PRINT 'Table bsales Created'
GO
INSERT bsales
SELECT stor_id, title_id, ordnum, qty, payterms FROM sales
GO
PRINT 'Table bsales Populated'
GO



/************************************************************************
	Create the stored procedures referenced by ODBCAPP.EXE
*************************************************************************/
use pubs
go


/****** Object:  Stored Procedure dbo.GetSales    Script Date: 12/12/96 1:23:29 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.GetSales') and sysstat & 0xf = 4)
	drop procedure dbo.GetSales
GO

/****** Object:  Stored Procedure dbo.GetTPByPubID    Script Date: 12/12/96 1:23:29 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.GetTPByPubID') and sysstat & 0xf = 4)
	drop procedure dbo.GetTPByPubID
GO

/****** Object:  Stored Procedure dbo.GetTPByTitleId    Script Date: 12/12/96 1:23:29 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.GetTPByTitleId') and sysstat & 0xf = 4)
	drop procedure dbo.GetTPByTitleId
GO

/****** Object:  Stored Procedure dbo.UpdtTitlesByPubID    Script Date: 12/12/96 1:23:29 PM ******/
if exists (select * from sysobjects where id = object_id('dbo.UpdtTitlesByPubID') and sysstat & 0xf = 4)
	drop procedure dbo.UpdtTitlesByPubID
GO

/****** Object:  Stored Procedure dbo.GetSales    Script Date: 12/12/96 1:23:30 PM ******/
CREATE PROCEDURE GetSales @titleid char(6) AS
  SELECT TITLE_ID, QTY FROM SALES WHERE TITLE_ID = @titleid 
GO
GRANT EXECUTE ON dbo.GetSales to pubsuser
GO
PRINT 'Stored Procedure GetSales Created'
GO


/****** Object:  Stored Procedure dbo.GetTPByPubID    Script Date: 12/12/96 1:23:30 PM ******/
CREATE PROCEDURE GetTPByPubID @PubID char(4) AS
	SELECT T.TITLE_ID, T.TITLE, T.TYPE, T.PUB_ID, T.PRICE, T.ADVANCE, T.ROYALTY, T.YTD_SALES, P.PUB_NAME, 
		P.CITY, P.STATE, P.COUNTRY FROM TITLES T, PUBLISHERS P WHERE T.PUB_ID = P.PUB_ID AND T.PUB_ID = @PubID
GO
GRANT EXECUTE ON dbo.GetTPByPubID to pubsuser
GO
PRINT 'Stored Procedure GetTPByPubID Created'
GO

/****** Object:  Stored Procedure dbo.GetTPByTitleId    Script Date: 12/12/96 1:23:30 PM ******/
CREATE PROCEDURE GetTPByTitleId @titleid char(6) AS
	SELECT T.TITLE_ID, T.TITLE, T.TYPE, T.PUB_ID, T.PRICE, T.ADVANCE, T.ROYALTY, T.YTD_SALES, P.PUB_NAME, 
		P.CITY, P.STATE, P.COUNTRY FROM TITLES T, PUBLISHERS P WHERE T.TITLE_ID = @titleid AND T.PUB_ID = P.PUB_ID
GO
GRANT EXECUTE ON dbo.GetTPByTitleID to pubsuser
GO
PRINT 'Stored Procedure GetTPByTitleID Created'
GO

/****** Object:  Stored Procedure dbo.UpdtTitlesByPubID    Script Date: 12/12/96 1:23:30 PM ******/
CREATE PROCEDURE UpdtTitlesByPubID @PubID char(4) AS
	UPDATE TITLES SET YTD_SALES = YTD_SALES + (SELECT SUM(QTY) FROM SALES WHERE TITLES.TITLE_ID = SALES.TITLE_ID) 
		WHERE PUB_ID = @PubID
GO
GRANT EXECUTE ON dbo.UpdtTitlesByPubID to pubsuser
GO
PRINT 'Stored Procedure UpdtTitlesByPubID Created'
GO

