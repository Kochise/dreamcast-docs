Datasource: JobForum
Template: ViewAvail.htx
RequiredParameters: ListingDate
SQLStatement:
+SELECT *
+FROM %JobType%
+WHERE ListingDate>=#%ListingDate%# 


