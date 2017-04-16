CREATE PROCEDURE AuthorSummary 
AS BEGIN 

SELECT AuthorID, 
       COUNT(*) 
FROM   Article 
GROUP BY ArticleType 

END
