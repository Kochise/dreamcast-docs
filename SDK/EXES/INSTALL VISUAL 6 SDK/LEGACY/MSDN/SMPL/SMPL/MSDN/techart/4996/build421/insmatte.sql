/* 
 * InsertMatter 
 * SQL Server 4.21 version
 */

CREATE PROCEDURE InsertMatter 
  (@MatterID PKID OUT, 
   @MatterType TypeCode, 
   @Description StdDescription, 
   @ArticleID PKID, 
   @EditorID PKID) 
AS BEGIN 

DECLARE @MatID     PKID 
DECLARE @rc        int 

EXECUTE @rc = GetNextPKID 
   @PKIDName = 'MatterID', 
   @PKIDValue = @MatID OUT 

IF @rc = -1 GOTO ERROR_EXIT 

INSERT INTO Matter  
  (MatterID, 
   MatterType, 
   Description, 
   ArticleID, 
   EditorID) 
VALUES 
  (@MatID, 
   @MatterType, 
   @Description, 
   @ArticleID, 
   @EditorID)

IF @@rowcount <> 1 GOTO ERROR_EXIT 

SUCCESS:
  SELECT @MatterID = @MatID 
  RETURN 0

ERROR_EXIT:
  /* Raise an error message. */
  RETURN -1


END 
