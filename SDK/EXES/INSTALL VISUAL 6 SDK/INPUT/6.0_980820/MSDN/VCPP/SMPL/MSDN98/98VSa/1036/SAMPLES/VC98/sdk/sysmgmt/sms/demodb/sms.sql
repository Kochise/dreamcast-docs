/*
**         SMS.SQL
**
**  Allocate disk space for database devices that will
**  be used for the database and for the log.
**  Make sure that you have VDEVNO 30 and 31 available.
**  If you need to create these devices on another location
**  other than "C:\MSSQL\DATA", edit the PHYSNAME parameter
**  to reflect the new location.
**  Remember that DISK INIT allocates disk space in 2k pages.
**
*/

USE master

/*
**    Check to see if SMSdata_dev and SMSlog_dev
**    devices exists. Then delete them, but first
**    delete the database that may exist on the device.
*/

IF EXISTS ( SELECT name
            FROM sysdevices
            WHERE name IN ('SMSdemo_dev', 'SMSDMlog_dev'))
BEGIN
    DROP DATABASE SMSdemo
    EXEC sp_dropdevice SMSdemo_dev, DELFILE
    EXEC sp_dropdevice SMSDMlog_dev,  DELFILE
END

/*  Create the devices.  */

DISK INIT
  NAME =      'SMSdemo_dev',
  PHYSNAME =  'C:\MSSQL\DATA\SMSDemo.DAT',
  VDEVNO =    30,
  SIZE =      23040

    IF @@error = 0
	BEGIN
	    RAISERROR('Device: SMSdemo_dev created successfully', 10, 1)
	END

DISK INIT
  NAME =      'SMSDMlog_dev',
  PHYSNAME =  'C:\MSSQL\DATA\SMSDMLOG.DAT',
  VDEVNO =    31,
  SIZE =      5120

IF @@error = 0
	BEGIN
	    RAISERROR('Device: SMSDMlog_dev created successfully', 10, 1)
	END
GO


/*
**   This section will create the database.
**
*/

IF EXISTS ( SELECT name
            FROM sysdatabases
            WHERE name = 'SMSdemo' ) -- Checks to see if SMSdemo db exists.
BEGIN
    DROP DATABASE SMSdemo
END

CREATE DATABASE   SMSdemo    -- Creates the SMSdemo database.
  ON		SMSdemo_dev = 45
  LOG ON	SMSDMlog_dev  = 10
  FOR LOAD
GO


/*
**   This section will load the database.
**   It is also depends on the SMSdmp.dat file
**   to be located in \MSSQL\BACKUP\ directory.
**
*/


LOAD DATABASE SMSdemo FROM DISK='C:\MSSQL\BACKUP\SMSdmp.dat'
	WITH STATS = 5

