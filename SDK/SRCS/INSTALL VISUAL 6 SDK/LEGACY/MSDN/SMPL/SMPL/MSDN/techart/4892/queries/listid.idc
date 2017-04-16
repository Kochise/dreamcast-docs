Datasource: JobForum
Template: ListID.htx
DefaultParameters:
SQLStatement:
+SELECT *
+FROM `Available Date Match`
+WHERE ContactName='%ContactName%'AND 
+Company='%Company%'AND
+JobTypeID=%JobTypeID% AND  
+JobTitle='%JobTitle%' AND 
+JobDesc='%JobDesc%' AND  
+JobCity='%JobCity%' 
+AND JobState='%JobState%' AND  JobAreaCode='%JobAreaCode%'
+AND  JobZip='%JobZip%'




