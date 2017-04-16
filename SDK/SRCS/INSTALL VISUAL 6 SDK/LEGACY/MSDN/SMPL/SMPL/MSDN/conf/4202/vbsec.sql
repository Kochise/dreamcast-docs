/* VBSEC.SQL */

/* this procedure looks at the user_id of the current connection   */
/* and returns a list of stored procedures in the current database */
/* that the user has permission to execute                         */

/* This procedure can be used by a client application to retrieve  */
/* information to determin whether or not client functionality     */
/* should be enabled/disabled.                                     */

/* Craig Goren 01/08/95              */
/* Internet: cgoren@claritycnslt.com */
/* CIS:      72773.1062              */
 

IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('sp_security'))
begin
     DROP procedure sp_security
     print "Old procedure dropped."
end
GO

create procedure sp_security AS
begin

	/* if sa/dbo, the return everything */

	if USER_ID() = 1
	begin
	        select 
	                o.name 
	        from
	                sysobjects o
	        where
	                o.type = 'P'   /* only get SPs */
	        order by
	                o.name 
                
	        return 0               /* we're done! */
	end



	/* begin "normal" user case */

	/* find everything you or your alias owns */
	select
	        o.name 
	from 
	        sysobjects o,
	        sysusers u
	where
	            o.uid = u.uid       /* find what you own */
	        and o.type = 'P'        /* only get SPs */
	        and o.uid = user_id()   /* current user */

	UNION

	/* find everything you or your alias has been */
     /* explicitly granted execute privliges on    */

	select 
	        o.name 
	from 
	        sysprotects p,
	        sysusers u,
	        sysobjects o

	where 
        
	            p.uid = u.uid        /* join users to protect by user id */
	        and p.id = o.id          /* join by object ID */
	        and action=224           /* execute */
	        and protecttype=205      /* grant */
	        and p.uid = user_id()    /* current user */

	UNION

	/* find everything you or your alias' group has been explicitly granted execute privliges on */

	select 
	        o.name 
	from 
	        sysprotects p,
	        sysusers u,
	        sysobjects o

	where 
        
	            u.gid = p.uid       /* join users to protect groupid->userid */
	        and p.id = o.id         /* join by object ID */
	        and action=224          /* execute */
	        and protecttype=205     /* grant */
	        and u.uid = user_id()   /* current user */

	UNION

	/* find everything the PUBLIC group has been */
     /* explicitly granted execute privliges on   */

	select 
	        o.name 
	from 
	        sysprotects p,
	        sysobjects o

	where 
        
	            p.uid = 0        /* PUBLIC has reserved gid =0 */
	        and p.id = o.id      /* join by object ID */
	        and action=224       /* execute */
	        and protecttype=205  /* grant */

	order by
	        o.name
end
go

print "New procedure added."
go

/* Grant execute privliges to public group.  */

GRANT EXECUTE ON sp_security TO PUBLIC
go 

print "Execute privliges granted to PUBLIC."
go
