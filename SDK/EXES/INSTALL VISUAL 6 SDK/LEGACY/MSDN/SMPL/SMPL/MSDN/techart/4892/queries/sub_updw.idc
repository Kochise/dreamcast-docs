Datasource: JobForum
Template: Sub_UpdW.htx
SQLStatement:
+UPDATE JobWanted
+SET ContactName='%ContactName%', Company='%Company%', 
+Address='%Address%', City='%City%', State='%State%',
+Zip='%Zip%', Country='%Country%', Phone='%Phone%', FAX='%FAX%', 
+Email='%Email%', ContactMethodID=%ContactMethodID%, 
+JobTypeID=%JobTypeID%, JobClass='%JobClass%', 
+Location='%Location%', JobDesc='%JobDesc%', 
+SpecialSkills='%SpecialSkills%', YearsExp='%YearsExp%', 
+Education='%Education%', Website='%Website%', MSCert='%MSCert%',Available='%Available%'
+WHERE WantedID=%WantedID%





