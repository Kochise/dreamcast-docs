Datasource: JobForum
Template: UpdAvail.htx
DefaultParameters:
MaxRecords: 50
SQLStatement:
+SELECT *
+FROM JobAvailable
+WHERE AvailID=%AvailID% and Password='%Password%'





