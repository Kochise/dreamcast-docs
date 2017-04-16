/* 
 * Sample data load
 * SQL Server 4.21
 */

/* 
 * Load Author Table
 */
INSERT INTO Author (AuthorID, Name) VALUES (1, 'Stan Peterson')
INSERT INTO Author (AuthorID, Name) VALUES (2, 'James K. Hamill')
INSERT INTO Author (AuthorID, Name) VALUES (3, 'Freida Post')
INSERT INTO Author (AuthorID, Name) VALUES (4, 'Helen Trammell')

/* 
 * Load Editor Table 
 */
INSERT INTO Editor (EditorID, Name) VALUES (1, 'Tina Brockwell')
INSERT INTO Editor (EditorID, Name) VALUES (2, 'Mindy H. Cameron')
INSERT INTO Editor (EditorID, Name) VALUES (3, 'Steve Landers')
INSERT INTO Editor (EditorID, Name) VALUES (4, 'Mark Cromwell')

/* 
 * Load Sample Article
 */
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (1, 'Technical Article', 1, 'Converting from MS Cardfile to SQL Server')
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (2, 'Technical Article', 3, 'Using Distributed Transactions in SQL Server 6.5')
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (3, 'Backgrounder', 2, 'Overview of Microsoft Internet Technologies') 
INSERT INTO Article (ArticleID, ArticleType, AuthorID, Title) VALUES (4, 'Specification', 3, 'Microsoft Distributed Leaflet API') 

/* 
 * Load Sample Matter
 */
INSERT INTO Matter (MatterID, MatterType, Description, ArticleID, EditorID) VALUES (1, 'Editorial Review', 'Edit Preliminary Draft', 1, 3)
INSERT INTO Matter (MatterID, MatterType, Description, ArticleID, EditorID) VALUES (2, 'Editorial Review', 'Final Edit', 2, 4)


/* 
 * Load Nodes Table.
 */
INSERT INTO Node (NodeID, NodeType, ParentNode, Description) VALUES (1, 'Top Level Node', NULL, 'Top Level - Publication #1')
INSERT INTO Node (NodeID, NodeType, ParentNode, Description) VALUES (2, 'Technical Articles', 1, 'Technical Articles')


/* 
 * Load Publications Table.
 */
INSERT INTO Publication (PublicationID, PublicationType, TopLevelNode, Description) VALUES (1, 'World Wide Web Site', 1, 'Sample World Wide Web Site')

/* 
 * Load ArticlePub Table
 */
INSERT INTO ArticlePub (ArticlePubID, ArticleID, NodeID) VALUES (1, 2, 2) 


/* 
 * Load PKIdentifier Table 
 * Sequencing must take into account values already used by other 
 * INSERT statements in this script. 
 */
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('ArticleID', 3)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('AuthorID', 5)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('MatterID', 3)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('EditorID', 5)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('PublicationID', 2)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('NodeID', 3)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('ArticlePubID', 2)
INSERT INTO PKIdentifier(PKIDName, PKIDValue) VALUES ('LinkID', 1)
