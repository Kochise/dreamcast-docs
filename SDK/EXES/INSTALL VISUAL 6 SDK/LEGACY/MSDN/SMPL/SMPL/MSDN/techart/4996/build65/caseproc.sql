/* 
 * InsertArticle using CASE statement
 * SQL Server 6.5 version
 */

CREATE PROCEDURE InsertArticleExt
  (@ArticleID PKID OUT, 
   @ArticleType TypeCode, 
   @AuthorID PKID,  
   @Title StdDescription) 
AS BEGIN 

/* 
 * Evaluate the user-entered @ArticleType, 
 * and select an appropriate pre-defined type code. 
 */
SELECT @ArticleType= 
  CASE 
    WHEN CHARINDEX('TEC', UPPER(@ArticleType)) <> 0 THEN 'Technical Article'
    WHEN CHARINDEX('WH', UPPER(@ArticleType)) <> 0 THEN 'Whitepaper' 
    WHEN CHARINDEX('BA', UPPER(@ArticleType)) <> 0 THEN 'Backgrounder' 
    WHEN CHARINDEX('SP', UPPER(@ArticleType)) <> 0 THEN 'Specification' 
    WHEN CHARINDEX('DO', UPPER(@ArticleType)) <> 0 THEN 'Documentation' 
    ELSE 'Unknown' 
  END 

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
