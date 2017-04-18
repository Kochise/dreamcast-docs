Datasource: JobForum
Template: ViewWant.htx
DefaultParameters: ListingDate=12/1/95
RequiredParameters: 
SQLStatement:
+SELECT *
+FROM %JobType%
+WHERE ListingDate>=#%ListingDate%# 


