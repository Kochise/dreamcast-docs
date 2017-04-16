set quoted_identifier on
GO

use master
GO

if exists (select * from sysdatabases where name = 'AddrBookDB')
	drop database AddrBookDB
GO

create database AddrBookDb on default = 1
GO

use AddrBookDB
GO


/****** Object:  User 'adcdemo' ******/
if not exists (select * from master..syslogins where name = 'adcdemo')
	EXEC sp_addlogin 'adcdemo', 'adcdemo', 'AddrBookDB'
GO
EXEC sp_adduser 'adcdemo'
GO

/****** Object:  Table dbo.Employee ******/
if exists (select * from sysobjects where id = object_id('dbo.Employee') and sysstat & 0xf = 3)
	drop table "dbo"."Employee"
GO

/****** Object:  Table dbo.Employee  ******/

CREATE TABLE dbo.Employee (
	ID int IDENTITY (1010, 10) NOT NULL ,
	FirstName varchar (30) NOT NULL ,
	LastName varchar (30) NOT NULL ,
	Name varchar (60) NULL,
	Title varchar (20) NULL,
	Type varchar (20) NULL,
	Email varchar (20) NULL,
	ManagerEmail varchar (20) NULL,
	Building varchar (30) NULL,
	Room varchar (20) NULL,
	Phone varchar (20) NULL,
	CONSTRAINT PK___1__10 PRIMARY KEY  CLUSTERED 
	(
		ID
	)
)
GO

GRANT  REFERENCES ,  SELECT ,  INSERT ,  DELETE ,  UPDATE  ON "Employee"  TO "public"
GO

-- Populate the table with sample data

insert Employee values ('Amy' ,'Anderson' ,'Anderson, Amy' ,'Purchase Manager' ,'full-time' ,'amya' ,'jamesa' ,'6' ,'2021' ,'555-7132')
go

insert Employee values ('Karen' ,'Berge' ,'Berge, Karen' ,'Program Manager' ,'full-time' ,'karenb' ,'jamesa' ,'4' ,'1020' ,'555-7233')
go

insert Employee values ('Jan' ,'Trabandt' ,'Trabandt, Jan' ,'Program Manager' ,'full-time' ,'jantr' ,'michaelc' ,'5' ,'2214' ,'555-3743')
go

insert Employee values ('Viki' ,'Parrott' ,'Parrott, Viki' ,'Sales Manager' ,'full-time' ,'vikip' ,'amyan' ,'1' ,'1205' ,'555-5327')
go

insert Employee values ('Bill' ,'Sornsin' ,'Sornsin, Bill' ,'Account Executive' ,'full-time' ,'billso' ,'darlener' ,'3' ,'2003' ,'555-2757')
go

insert Employee values ('Rich' ,'Andrews' ,'Andrews, Rich' ,'Sales Representative' ,'full-time' ,'richand' ,'josel' ,'6' ,'1023' ,'555-2701')
go

insert Employee values ('Max' ,'Benson' ,'Benson, Max' ,'Account Executive' ,'full-time' ,'maxb' ,'kimy' ,'4' ,'1586' ,'555-2715')
go

insert Employee values ('Barbara' ,'Hoffman' ,'Hoffman, Barbara' ,'District Sales Manager' ,'full-time' ,'barbh' ,'lauraj' ,'5' ,'2295' ,'555-2711')
go

insert Employee values ('Laura' ,'Jennings' ,'Jennings, Laura' ,'Regional Sales Director' ,'full-time' ,'lauraj' ,'bobm' ,'1' ,'2106' ,'555-2712')
go

insert Employee values ('Beverly' ,'Jones' ,'Jones, Beverly' ,'Marketing Manager' ,'full-time' ,'beverlyj' ,'lauraj' ,'3' ,'1242' ,'555-2705')
go

insert Employee values ('Brent' ,'Jones' ,'Jones, Brent' ,'Senior Accountant' ,'full-time' ,'brentk' ,'jamesa' ,'6' ,'2178' ,'555-2708')
go

insert Employee values ('April' ,'LaMonte' ,'LaMonte, April' ,'Sales Representative' ,'full-time' ,'aprilla' ,'josel' ,'4' ,'1814' ,'555-2702')
go

insert Employee values ('Jose' ,'Lugo' ,'Lugo, Jose' ,'Sales Manager' ,'full-time' ,'josel' ,'barbh' ,'5' ,'1250' ,'555-2707')
go

insert Employee values ('Steve' ,'Masters' ,'Masters, Steve' ,'Program Manager' ,'full-time' ,'stevemas' ,'michaelc' ,'1' ,'2086' ,'555-2709')
go

insert Employee values ('Thom' ,'McCann' ,'McCann, Thom' ,'Sales Representative' ,'full-time' ,'thommc' ,'josel' ,'3' ,'2122' ,'555-2704')
go

insert Employee values ('Nina' ,'Roberts' ,'Roberts, Nina' ,'Account Executive' ,'full-time' ,'ninaro' ,'kimy' ,'6' ,'1158' ,'555-2710')
go

insert Employee values ('Sharon' ,'Swanson' ,'Swanson, Sharon' ,'Sales Representative' ,'full-time' ,'sharons' ,'josel' ,'4' ,'1194' ,'555-2706')
go

insert Employee values ('Stephen' ,'Thomas' ,'Thomas, Stephen' ,'Account Executive' ,'full-time' ,'thomas' ,'kimy' ,'5' ,'2230' ,'555-2713')
go

insert Employee values ('Kevin' ,'Yim' ,'Yim, Kevin' ,'Account Executive' ,'full-time' ,'keviny' ,'kimy' ,'1' ,'2266' ,'555-2714')
go

insert Employee values ('Kim' ,'Yoshida' ,'Yoshida, Kim' ,'Account Manager' ,'full-time' ,'kimy' ,'barbh' ,'3' ,'1102' ,'555-2703')
go


-- Run a stored procedure to verify the creation of the table and metadata

sp_help employee
go

-- Do a simple select statement to verify the population of the database table
-- Should return 20 rows of data

select LastName, FirstName, Email from employee
go

-- Grant read and write permissions to public for the employee table (updates)

grant all on employee to public
go
