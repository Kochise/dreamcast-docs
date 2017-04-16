/* 
 * Sample data
 * SQL Server 6.5 version
 */

/* 
 * Load Author Table
 */
SET IDENTITY_INSERT Author ON 
INSERT INTO Author (AuthorID, Name) VALUES (1, 'Stan Peterson')
INSERT INTO Author (AuthorID, Name) VALUES (2, 'James K. Hamill')
INSERT INTO Author (AuthorID, Name) VALUES (3, 'Freida Post')
INSERT INTO Author (AuthorID, Name) VALUES (4, 'Helen Trammell') 
SET IDENTITY_INSERT Author OFF 

/* 
 * Load Editor Table 
 */
SET IDENTITY_INSERT Editor ON 
INSERT INTO Editor (EditorID, Name) VALUES (1, 'Tina Brockwell')
INSERT INTO Editor (EditorID, Name) VALUES (2, 'Mindy H. Cameron')
INSERT INTO Editor (EditorID, Name) VALUES (3, 'Steve Landers')
INSERT INTO Editor (EditorID, Name) VALUES (4, 'Mark Cromwell') 
SET IDENTITY_INSERT Editor OFF 

/* 
 * Load Sample Article
 */
SET IDENTITY_INSERT Article ON 
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (1, 'Technical Article', 1, 'Converting from MS Cardfile to SQL Server')
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (2, 'Technical Article', 3, 'Using Distributed Transactions in SQL Server 6.5') 
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (3, 'Backgrounder', 2, 'Overview of Microsoft Internet Technologies') 
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (4, 'Specification', 3, 'Microsoft Distributed Leaflet API') 
SET IDENTITY_INSERT Article OFF 

/* 
 * Load Sample Matter
 */
SET IDENTITY_INSERT Matter ON 
INSERT INTO Matter (MatterID, MatterType, Description, ArticleID, EditorID) VALUES (1, 'Editorial Review', 'Edit Preliminary Draft', 1, 3)
INSERT INTO Matter (MatterID, MatterType, Description, ArticleID, EditorID) VALUES (2, 'Editorial Review', 'Final Edit', 2, 4) 
SET IDENTITY_INSERT Matter OFF 


/* 
 * Load Nodes Table.
 */
SET IDENTITY_INSERT Node ON 
INSERT INTO Node (NodeID, NodeType, ParentNode, Description) VALUES (1, 'Top Level Node', NULL, 'Top Level - Publication #1')
INSERT INTO Node (NodeID, NodeType, ParentNode, Description) VALUES (2, 'Technical Articles', 1, 'Technical Articles') 
SET IDENTITY_INSERT Node OFF 


/* 
 * Load Publications Table.
 */
SET IDENTITY_INSERT Publication ON 
INSERT INTO Publication (PublicationID, PublicationType, TopLevelNode, Description) VALUES (1, 'World Wide Web Site', 1, 'Sample World Wide Web Site') 
SET IDENTITY_INSERT Publication OFF

/* 
 * Load ArticlePub Table
 */
SET IDENTITY_INSERT ArticlePub ON 
INSERT INTO ArticlePub (ArticlePubID, ArticleID, NodeID) VALUES (1, 2, 2)  
SET IDENTITY_INSERT ArticlePub OFF 
