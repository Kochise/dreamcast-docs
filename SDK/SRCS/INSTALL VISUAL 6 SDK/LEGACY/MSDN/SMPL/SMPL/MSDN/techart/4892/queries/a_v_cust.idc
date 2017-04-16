Datasource: JobForum
Template: ViewAvail.htx
DefaultParameters: ListingDate=12/1/95, JobTitle=%%, JobDesc=%%, JobCity=%%, JobState=%%, JobAreaCode=%%, JobZip=%%, JobDesc1=%%, JobDesc2=%%
MaxRecords: 50
SQLStatement:
+SELECT *
+FROM %JobType%
+WHERE ListingDate>=#%ListingDate%# 
+AND JobTitle LIKE '%%%JobTitle%%%' AND JobDesc LIKE '%%%JobDesc%%%' AND JobDesc LIKE '%%%JobDesc1%%%' AND JobDesc LIKE '%%%JobDesc2%%%'
+AND  JobCity LIKE '%JobCity%' AND  JobState LIKE '%JobState%' 
+AND  JobAreacode LIKE '%JobAreaCode%'AND JobZip Like '%JobZip%' AND Filled=%Filled%


