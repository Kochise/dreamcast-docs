Datasource: JobForum
Template: A_U_Srch.htx
DefaultParameters: ListingDate=12/1/95, JobTitle=%%, JobDesc=%%, JobCity=%%, JobState=%%, JobAreaCode=%%, JobZip=%%, ContactName=%%, Company=%%
MaxRecords: 50
SQLStatement:
+SELECT *
+FROM %JobType%
+WHERE ListingDate>=#%ListingDate%# 
+AND JobTitle LIKE '%%%JobTitle%%%' AND JobDesc LIKE '%%%JobDesc%%%' 
+AND  JobCity LIKE '%JobCity%' AND  JobState LIKE '%JobState%' 
+AND  JobAreacode LIKE '%JobAreaCode%'AND JobZip Like '%JobZip%' 
+AND Filled=%Filled% AND ContactName LIKE '%ContactName%' AND Company LIKE '%Company%'


