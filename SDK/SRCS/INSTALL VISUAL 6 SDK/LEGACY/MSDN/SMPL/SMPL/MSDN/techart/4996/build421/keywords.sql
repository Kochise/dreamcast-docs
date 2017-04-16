/* 
 * Keywords 
 * Table and stored procedure which violate keyword 
 * and reserved words in version 6.0 and 6.5. 
 */

CREATE TABLE CheckUpgrade 

  /* keywords */

  (identitycol   int NOT NULL, 
   constraint    int, 
   floppy        varchar(24), 

  /* reserved words */

   cascaded      bit, 
   deferred      tinyint, 
   retaindays    smallint) 
go 


CREATE PROCEDURE TestCheckUpgrade 
AS BEGIN 

  CREATE TABLE #temp1 

  /* keywords */

   (identitycol   int NOT NULL, 
    constraint    int, 
    floppy        varchar(24), 

  /* reserved words */

   cascaded      bit, 
   deferred      tinyint, 
   retaindays    smallint) 

  DROP TABLE #temp1 

END 
