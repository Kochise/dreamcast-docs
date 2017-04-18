/* 
 * Sample "Content" Database Build Scripts
 * SQL Server 6.5 version 
 */
 
 
 exec sp_addtype PKID, "int", "NOT NULL"
go
 
 exec sp_addtype StdDescription, "varchar(128)", "NULL"
go
 
 exec sp_addtype TypeCode, "varchar(48)", "NOT NULL"
go
 

CREATE TABLE Author
  (AuthorID  PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   Name      StdDescription NULL)
go
 
 
CREATE TABLE Article
  (ArticleID    PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   ArticleType  TypeCode,
   AuthorID     PKID FOREIGN KEY (AuthorID) REFERENCES Author(AuthorID),
   Title        StdDescription NULL)
go

 
CREATE INDEX XIF2Article
  ON Article (AuthorID)
go
 
 
CREATE TABLE Node
  (NodeID      PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   NodeType    TypeCode,
   ParentNode  PKID NULL FOREIGN KEY (ParentNode) REFERENCES Node(NodeID),
   Description StdDescription NULL)
go
 
CREATE INDEX XIF21Node
   ON Node (ParentNode)
go
  

CREATE TABLE ArticlePub
  (ArticlePubID  PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   ArticleID     PKID FOREIGN KEY (ArticleID) REFERENCES Article(ArticleID),
   NodeID        PKID FOREIGN KEY (NodeID) REFERENCES Node(NodeID))
go
 
 
CREATE INDEX XIF22ArticlePub
  ON ArticlePub (NodeID)
go
 
CREATE INDEX XIF23ArticlePub
  ON ArticlePub (ArticleID)
go
 
 
CREATE TABLE Editor
  (EditorID   PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   Name       StdDescription NULL)
go
 
 
CREATE TABLE Link
  (LinkID            PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   LinkSourceID      PKID FOREIGN KEY (LinkSourceID) REFERENCES ArticlePub(ArticlePubID),
   LinkTargetID      PKID FOREIGN KEY (LinkSourceID) REFERENCES ArticlePub(ArticlePubID),
   LinkSourceMethod  StdDescription NULL,
   LinkTargetMethod  StdDescription NULL)
go
 

CREATE INDEX XIF24Link
   ON Link (LinkTargetID)
go
 
CREATE INDEX XIF25Link
  ON Link (LinkSourceID)
go
 
CREATE TABLE Matter
  (MatterID     PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   MatterType   TypeCode,
   ArticleID    PKID FOREIGN KEY (ArticleID) REFERENCES Article(ArticleID),
   Description  StdDescription NULL,
   EditorID     PKID FOREIGN KEY (EditorID) REFERENCES Editor(EditorID))
go
 

CREATE INDEX XIF5Matter
  ON Matter (ArticleID)
go
 
CREATE INDEX XIF6Matter
  ON Matter (EditorID)
go
 

CREATE TABLE Publication
  (PublicationID     PKID IDENTITY(1,1) PRIMARY KEY CLUSTERED,
   PublicationType   TypeCode,
   TopLevelNode      PKID FOREIGN KEY(TopLevelNode) REFERENCES Node(NodeID),
   Description       StdDescription NULL)
go
 
CREATE INDEX XIF20Publication
  ON Publication (TopLevelNode)
go
 
