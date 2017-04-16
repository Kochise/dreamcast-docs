/* 
 * Sample database build scripts
 * SQL Server 4.21
 */
 
 exec sp_addtype PKID, "int", "NOT NULL"
go
 
 exec sp_addtype StdDescription, "varchar(128)", "NULL"
go
 
 exec sp_addtype TypeCode, "varchar(48)", "NOT NULL"
go
 
 CREATE TABLE Article
       (ArticleID                PKID,
        ArticleType              TypeCode,
        AuthorID                 PKID,
        Title                    StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKArticle
   ON Article
 (
        ArticleID
 )
go
 
 CREATE INDEX XIF2Article
   ON Article
 (
        AuthorID
 )
go
 
 exec sp_primarykey Article,
     ArticleID
go
 
 CREATE TABLE ArticlePub
       (ArticlePubID             PKID,
        ArticleID                PKID,
        NodeID                   PKID
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKArticlePub
   ON ArticlePub
 (
        ArticlePubID
 )
go
 
 CREATE INDEX XIF22ArticlePub
   ON ArticlePub
 (
        NodeID
 )
go
 
 CREATE INDEX XIF23ArticlePub
   ON ArticlePub
 (
        ArticleID
 )
go
 
 exec sp_primarykey ArticlePub,
     ArticlePubID
go
 
 CREATE TABLE Author
       (AuthorID                 PKID,
        Name                     StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKAuthor
   ON Author
 (
        AuthorID
 )
go
 
 exec sp_primarykey Author,
     AuthorID
go
 
 CREATE TABLE Editor
       (EditorID                 PKID,
        Name                     StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKEditor
   ON Editor
 (
        EditorID
 )
go
 
 exec sp_primarykey Editor,
     EditorID
go
 
 CREATE TABLE Link
       (LinkID                   PKID,
        LinkSourceID             PKID,
        LinkTargetID             PKID,
        LinkSourceMethod         StdDescription,
        LinkTargetMethod         StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKLink
   ON Link
 (
        LinkID
 )
go
 
 CREATE INDEX XIF24Link
   ON Link
 (
        LinkTargetID
 )
go
 
 CREATE INDEX XIF25Link
   ON Link
 (
        LinkSourceID
 )
go
 
 exec sp_primarykey Link,
     LinkID
go
 
 CREATE TABLE Matter
       (MatterID                 PKID,
        MatterType               TypeCode,
        ArticleID                PKID,
        Description              StdDescription,
        EditorID                 PKID
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKMatter
   ON Matter
 (
        MatterID
 )
go
 
 CREATE INDEX XIF5Matter
   ON Matter
 (
        ArticleID
 )
go
 
 CREATE INDEX XIF6Matter
   ON Matter
 (
        EditorID
 )
go
 
 exec sp_primarykey Matter,
     MatterID
go
 
 CREATE TABLE Node
       (NodeID                   PKID,
        NodeType                 TypeCode,
        ParentNode               PKID NULL,
        Description              StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKNode
   ON Node
 (
        NodeID
 )
go
 
 CREATE INDEX XIF21Node
   ON Node
 (
        ParentNode
 )
go
 
 exec sp_primarykey Node,
     NodeID
go
 
 CREATE TABLE PKIdentifier
       (PKIDName                 varchar(64) NOT NULL,
        PKIDValue                PKID
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKIdentifier
   ON PKIdentifier
 (
        PKIDName
 )
go
 
 exec sp_primarykey PKIdentifier,
     PKIDName
go
 
 CREATE TABLE Publication
       (PublicationID            PKID,
        PublicationType          TypeCode,
        TopLevelNode             PKID,
        Description              StdDescription
 )
go
 
 CREATE UNIQUE CLUSTERED INDEX XPKPublication
   ON Publication
 (
        PublicationID
 )
go
 
 CREATE INDEX XIF20Publication
   ON Publication
 (
        TopLevelNode
 )
go
 
 exec sp_primarykey Publication,
     PublicationID
go
 
 exec sp_foreignkey Article, Author,
     AuthorID
go
 
 exec sp_foreignkey ArticlePub, Article,
     ArticleID
go
 
 exec sp_foreignkey ArticlePub, Node,
     NodeID
go
 
 exec sp_foreignkey Link, ArticlePub,
     LinkSourceID
go
 
 exec sp_foreignkey Link, ArticlePub,
     LinkTargetID
go
 
 exec sp_foreignkey Matter, Editor,
     EditorID
go
 
 exec sp_foreignkey Matter, Article,
     ArticleID
go
 
 exec sp_foreignkey Node, Node,
     ParentNode
go
 
 exec sp_foreignkey Publication, Node,
     TopLevelNode
go
 
 create trigger tD_Article on Article for DELETE as
/* ERwin Builtin Mon Aug 05 10:42:28 1996 */
/* DELETE trigger on Article */
begin
  declare  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Mon Aug 05 10:42:28 1996 */
    /* Article R/23 ArticlePub ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,ArticlePub
      where
        /*  %JoinFKPK(ArticlePub,deleted," = "," and") */
        ArticlePub.ArticleID = deleted.ArticleID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Article" because "ArticlePub" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:28 1996 */
    /* Article R/5 Matter ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Matter
      where
        /*  %JoinFKPK(Matter,deleted," = "," and") */
        Matter.ArticleID = deleted.ArticleID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Article" because "Matter" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:28 1996 */
    return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_Article on Article for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:28 1996 */
/* INSERT trigger on Article */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:28 1996 */
  /* Author R/2 Article ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(AuthorID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Author
        where
          /* %JoinFKPK(inserted,Author) */
          inserted.AuthorID = Author.AuthorID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Article" because "Author" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Article on Article for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Article */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insArticleID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/23 ArticlePub ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(ArticleID)
  begin
    if exists (
      select * from deleted,ArticlePub
      where
        /*  %JoinFKPK(ArticlePub,deleted," = "," and") */
        ArticlePub.ArticleID = deleted.ArticleID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Article" because "ArticlePub" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/5 Matter ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(ArticleID)
  begin
    if exists (
      select * from deleted,Matter
      where
        /*  %JoinFKPK(Matter,deleted," = "," and") */
        Matter.ArticleID = deleted.ArticleID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Article" because "Matter" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Author R/2 Article ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(AuthorID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Author
        where
          /* %JoinFKPK(inserted,Author) */
          inserted.AuthorID = Author.AuthorID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Article" because "Author" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tD_ArticlePub on ArticlePub for DELETE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* DELETE trigger on ArticlePub */
begin
  declare  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* ArticlePub R/25 Link ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Link
      where
        /*  %JoinFKPK(Link,deleted," = "," and") */
        Link.LinkSourceID = deleted.ArticlePubID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "ArticlePub" because "Link" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* ArticlePub R/24 Link ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Link
      where
        /*  %JoinFKPK(Link,deleted," = "," and") */
        Link.LinkTargetID = deleted.ArticlePubID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "ArticlePub" because "Link" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_ArticlePub on ArticlePub for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* INSERT trigger on ArticlePub */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/23 ArticlePub ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(ArticleID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Article
        where
          /* %JoinFKPK(inserted,Article) */
          inserted.ArticleID = Article.ArticleID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "ArticlePub" because "Article" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/22 ArticlePub ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(NodeID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Node
        where
          /* %JoinFKPK(inserted,Node) */
          inserted.NodeID = Node.NodeID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "ArticlePub" because "Node" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_ArticlePub on ArticlePub for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on ArticlePub */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insArticlePubID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/25 Link ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(ArticlePubID)
  begin
    if exists (
      select * from deleted,Link
      where
        /*  %JoinFKPK(Link,deleted," = "," and") */
        Link.LinkSourceID = deleted.ArticlePubID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "ArticlePub" because "Link" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/24 Link ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(ArticlePubID)
  begin
    if exists (
      select * from deleted,Link
      where
        /*  %JoinFKPK(Link,deleted," = "," and") */
        Link.LinkTargetID = deleted.ArticlePubID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "ArticlePub" because "Link" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/23 ArticlePub ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(ArticleID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Article
        where
          /* %JoinFKPK(inserted,Article) */
          inserted.ArticleID = Article.ArticleID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "ArticlePub" because "Article" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/22 ArticlePub ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(NodeID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Node
        where
          /* %JoinFKPK(inserted,Node) */
          inserted.NodeID = Node.NodeID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "ArticlePub" because "Node" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tD_Author on Author for DELETE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* DELETE trigger on Author */
begin
  declare  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* Author R/2 Article ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Article
      where
        /*  %JoinFKPK(Article,deleted," = "," and") */
        Article.AuthorID = deleted.AuthorID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Author" because "Article" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Author on Author for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Author */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insAuthorID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Author R/2 Article ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(AuthorID)
  begin
    if exists (
      select * from deleted,Article
      where
        /*  %JoinFKPK(Article,deleted," = "," and") */
        Article.AuthorID = deleted.AuthorID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Author" because "Article" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tD_Editor on Editor for DELETE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* DELETE trigger on Editor */
begin
  declare  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* Editor R/6 Matter ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Matter
      where
        /*  %JoinFKPK(Matter,deleted," = "," and") */
        Matter.EditorID = deleted.EditorID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Editor" because "Matter" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Editor on Editor for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Editor */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insEditorID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Editor R/6 Matter ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(EditorID)
  begin
    if exists (
      select * from deleted,Matter
      where
        /*  %JoinFKPK(Matter,deleted," = "," and") */
        Matter.EditorID = deleted.EditorID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Editor" because "Matter" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_Link on Link for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* INSERT trigger on Link */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/25 Link ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(LinkSourceID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,ArticlePub
        where
          /* %JoinFKPK(inserted,ArticlePub) */
          inserted.LinkSourceID = ArticlePub.ArticlePubID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Link" because "ArticlePub" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/24 Link ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(LinkTargetID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,ArticlePub
        where
          /* %JoinFKPK(inserted,ArticlePub) */
          inserted.LinkTargetID = ArticlePub.ArticlePubID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Link" because "ArticlePub" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Link on Link for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Link */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insLinkID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/25 Link ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(LinkSourceID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,ArticlePub
        where
          /* %JoinFKPK(inserted,ArticlePub) */
          inserted.LinkSourceID = ArticlePub.ArticlePubID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Link" because "ArticlePub" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* ArticlePub R/24 Link ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(LinkTargetID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,ArticlePub
        where
          /* %JoinFKPK(inserted,ArticlePub) */
          inserted.LinkTargetID = ArticlePub.ArticlePubID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Link" because "ArticlePub" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_Matter on Matter for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* INSERT trigger on Matter */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Editor R/6 Matter ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(EditorID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Editor
        where
          /* %JoinFKPK(inserted,Editor) */
          inserted.EditorID = Editor.EditorID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Matter" because "Editor" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/5 Matter ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(ArticleID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Article
        where
          /* %JoinFKPK(inserted,Article) */
          inserted.ArticleID = Article.ArticleID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Matter" because "Article" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Matter on Matter for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Matter */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insMatterID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Editor R/6 Matter ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(EditorID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Editor
        where
          /* %JoinFKPK(inserted,Editor) */
          inserted.EditorID = Editor.EditorID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Matter" because "Editor" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Article R/5 Matter ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(ArticleID)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Article
        where
          /* %JoinFKPK(inserted,Article) */
          inserted.ArticleID = Article.ArticleID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Matter" because "Article" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tD_Node on Node for DELETE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* DELETE trigger on Node */
begin
  declare  @errno   int,
           @errmsg  varchar(255)
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* Node R/22 ArticlePub ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,ArticlePub
      where
        /*  %JoinFKPK(ArticlePub,deleted," = "," and") */
        ArticlePub.NodeID = deleted.NodeID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Node" because "ArticlePub" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* Node R/21 Node ON PARENT DELETE SET NULL */
    update Node
      set
        /* %SetFK(Node,NULL) */
        Node.ParentNode = NULL
      from Node,deleted
      where
        /* %JoinFKPK(Node,deleted," = "," and") */
        Node.ParentNode = deleted.NodeID
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    /* Node R/20 Publication ON PARENT DELETE RESTRICT */
    if exists (
      select * from deleted,Publication
      where
        /*  %JoinFKPK(Publication,deleted," = "," and") */
        Publication.TopLevelNode = deleted.NodeID
    )
    begin
      select @errno  = 30001,
             @errmsg = 'Cannot DELETE "Node" because "Publication" exists.'
      goto error
    end
    /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
    return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_Node on Node for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* INSERT trigger on Node */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/21 Node ON CHILD INSERT SET NULL */
  if
    /* %ChildFK(" or",update) */
    update(ParentNode)
  begin
    update Node
      set
        /* %SetFK(Node,NULL) */
        Node.ParentNode = NULL
      from Node,inserted
      where
        /* %JoinPKPK(Node,inserted," = "," and") */
        Node.NodeID = inserted.NodeID and
        not exists (
          select * from Node
          where
            /* %JoinFKPK(inserted,Node," = "," and") */
            inserted.ParentNode = Node.NodeID
        )
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Node on Node for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Node */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insNodeID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/22 ArticlePub ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(NodeID)
  begin
    if exists (
      select * from deleted,ArticlePub
      where
        /*  %JoinFKPK(ArticlePub,deleted," = "," and") */
        ArticlePub.NodeID = deleted.NodeID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Node" because "ArticlePub" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/21 Node ON PARENT UPDATE SET NULL */
  if
    /* %ParentPK(" or",update) */
    update(NodeID)
  begin
    update Node
      set
        /* %SetFK(Node,NULL) */
        Node.ParentNode = NULL
      from Node,deleted
      where
        /* %JoinFKPK(Node,deleted," = "," and") */
        Node.ParentNode = deleted.NodeID
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/20 Publication ON PARENT UPDATE RESTRICT */
  if
    /* %ParentPK(" or",update) */
    update(NodeID)
  begin
    if exists (
      select * from deleted,Publication
      where
        /*  %JoinFKPK(Publication,deleted," = "," and") */
        Publication.TopLevelNode = deleted.NodeID
    )
    begin
      select @errno  = 30005,
             @errmsg = 'Cannot UPDATE "Node" because "Publication" exists.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/21 Node ON CHILD UPDATE SET NULL */
  if
    /* %ChildFK(" or",update) */
    update(ParentNode)
  begin
    update Node
      set
        /* %SetFK(Node,NULL) */
        Node.ParentNode = NULL
      from Node,inserted
      where
        /* %JoinPKPK(Node,inserted," = "," and") */
        Node.NodeID = inserted.NodeID and 
        not exists (
          select * from Node
          where
            /* %JoinFKPK(inserted,Node," = "," and") */
            inserted.ParentNode = Node.NodeID
        )
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tI_Publication on Publication for INSERT as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* INSERT trigger on Publication */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/20 Publication ON CHILD INSERT RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(TopLevelNode)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Node
        where
          /* %JoinFKPK(inserted,Node) */
          inserted.TopLevelNode = Node.NodeID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30002,
             @errmsg = 'Cannot INSERT "Publication" because "Node" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

create trigger tU_Publication on Publication for UPDATE as
/* ERwin Builtin Mon Aug 05 10:42:29 1996 */
/* UPDATE trigger on Publication */
begin
  declare  @numrows int,
           @nullcnt int,
           @validcnt int,
           @insPublicationID PKID,
           @errno   int,
           @errmsg  varchar(255)

  select @numrows = @@rowcount
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  /* Node R/20 Publication ON CHILD UPDATE RESTRICT */
  if
    /* %ChildFK(" or",update) */
    update(TopLevelNode)
  begin
    select @nullcnt = 0
    select @validcnt = count(*)
      from inserted,Node
        where
          /* %JoinFKPK(inserted,Node) */
          inserted.TopLevelNode = Node.NodeID
    /* %NotnullFK(inserted," is null","select @nullcnt = count(*) from inserted where"," and") */
    
    if @validcnt + @nullcnt != @numrows
    begin
      select @errno  = 30007,
             @errmsg = 'Cannot UPDATE "Publication" because "Node" does not exist.'
      goto error
    end
  end
  /* ERwin Builtin Mon Aug 05 10:42:29 1996 */
  return
error:
    raiserror @errno @errmsg
    rollback transaction
end
go

