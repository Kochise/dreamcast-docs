/* 
 * InsertArticle 
 * SQL Server 4.21 version
 */

CREATE PROCEDURE InsertArticle
  (@ArticleID PKID OUT, 
   @ArticleType TypeCode, 
   @AuthorID PKID, 
   @Title StdDescription) 
AS BEGIN 

DECLARE @ArtID     PKID 
DECLARE @rc        int 

EXECUTE @rc = GetNextPKID  
   @PKIDName = 'ArticleID', 
   @PKIDValue = @ArtID OUT 

IF @rc = -1 GOTO ERROR_EXIT 


INSERT INTO Article 
  (ArticleID, 
   ArticleType, 
   AuthorID, 
   Title) 
VALUES 
  (@ArtID, 
   @ArticleType, 
   @AuthorID, 
   @Title)

IF @@rowcount <> 1 GOTO ERROR_EXIT 

SUCCESS:
  SELECT @ArticleID = @ArtID 
  RETURN 0

ERROR_EXIT:
  /* Raise an error message. */
  RETURN -1


END 
