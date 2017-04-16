Datasource: JobForum
Template: W_ListID.htx
DefaultParameters:
SQLStatement:
+SELECT *
+FROM `Wanted Date Match`
+WHERE ContactName='%ContactName%' AND 
+Company='%Company%' AND
+JobTypeID=%JobTypeID% AND  
+JobClass='%JobClass%' AND 
+JobDesc='%JobDesc%' AND  
+SpecialSkills='%SpecialSkills%' AND
+YearsExp='%YearsExp%' AND  
+Education='%Education%' AND
+Location='%Location%'




