/* 
 * InsertMatter 
 * SQL Server 6.5 version
 */

CREATE PROCEDURE InsertMatter 
  (@MatterID PKID OUT, 
   @MatterType TypeCode, 
   @Description StdDescription, 
   @ArticleID PKID, 
   @EditorID PKID) 
AS BEGIN 

INSERT INTO Matter  
  (MatterType, 
   Description, 
   ArticleID, 
   EditorID) 
VALUES 
  (@MatterType, 
   @Description, 
   @ArticleID, 
   @EditorID)

IF @@rowcount <> 1 GOTO ERROR_EXIT 

SUCCESS:
  SELECT @MatterID = @@IDENTITY 
  RETURN 0

ERROR_EXIT:
  /* Raise an error message. */
  RETURN -1


END 
