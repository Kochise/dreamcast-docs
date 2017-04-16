Datasource: JobForum
Template: UpdWant.htx
DefaultParameters:
MaxRecords: 50
SQLStatement:
+SELECT *
+FROM JobWanted
+WHERE WantedID=%WantedID% and Password='%Password%'





