/* 
 * GetNextPKID 
 * SQL Server 4.21 only
 */

CREATE PROCEDURE GetNextPKID 
  (@PKIDName varchar(64), 
   @PKIDValue PKID OUT) 

AS BEGIN 

DECLARE @PKID    PKID 
DECLARE @rows    int 

SELECT @rows = 0 

/* Lock record so that multiple users cannot 
 * retrieve the same ID value.
 */

BEGIN TRAN 
  SELECT @PKID = PKIDValue 
  FROM PKIdentifier 
  HOLDLOCK 
  WHERE PKIDName = @PKIDName 
    
  SELECT @rows = @@Rowcount 
  IF @rows = 1 
  BEGIN 
    UPDATE PKIdentifier 
    SET PKIDValue = @PKID + 1 
    WHERE PKIDName = @PKIDName 
    SELECT @PKIDValue = @PKID 
  END 
COMMIT TRAN 

IF @rows <> 1 
BEGIN 
  /* Raise an error message. */
  RETURN -1 
END 

IF @rows = 1 RETURN 0 

END 
