Datasource: JobForum
Template: ViewWant.htx
DefaultParameters: ListingDate=12/1/95, JobDesc=%%, JobDesc1=%%, JobDesc2=%%
MaxRecords: 50
SQLStatement:
+SELECT *
+FROM %JobType%
+WHERE ListingDate>=#%ListingDate%# 
+AND JobClass LIKE '%%%JobClass%%%' AND JobDesc LIKE '%%%JobDesc%%%' 
+AND JobDesc LIKE '%%%JobDesc1%%%' AND JobDesc LIKE '%%%JobDesc2%%%'
+AND (Available=%Available%)


