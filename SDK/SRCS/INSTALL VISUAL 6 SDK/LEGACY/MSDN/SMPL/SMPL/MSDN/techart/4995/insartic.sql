/* 
 * InsertArticle 
 * SQL Server 6.5 version
 */

CREATE PROCEDURE InsertArticle
  (@ArticleID PKID OUT, 
   @ArticleType TypeCode, 
   @AuthorID PKID,  
   @Title StdDescription) 
AS BEGIN 

INSERT INTO Article 
  (ArticleType, 
   AuthorID, 
   Title) 
VALUES 
  (@ArticleType, 
   @AuthorID, 
   @Title)

IF @@rowcount <> 1 GOTO ERROR_EXIT 

SUCCESS:
  SELECT @ArticleID = @@IDENTITY 
  RETURN 0

ERROR_EXIT:
  /* Raise an error message. */
  RETURN -1


END 
