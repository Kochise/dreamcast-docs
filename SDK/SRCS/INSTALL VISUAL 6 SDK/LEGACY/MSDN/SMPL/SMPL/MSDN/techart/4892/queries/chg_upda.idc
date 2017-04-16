Datasource: JobForum
Template: Chg_UpdA.htx
SQLStatement:
+UPDATE JobAvailable
+SET ContactName='%ContactName%', Company='%Company%', 
+Address='%Address%', City='%City%', State='%State%',
+Zip='%Zip%', Country='%Country%', Phone='%Phone%', FAX='%FAX%', 
+Email='%Email%', ContactMethodID=%ContactMethodID%, JobCity='%JobCity%', 
+JobState='%JobState%', JobAreaCode='%JobAreaCode%', JobZip='%JobZip%', 
+JobTypeID=%JobTypeID%, JobTitle='%JobTitle%', JobDesc='%JobDesc%', 
+SpecialSkills='%SpecialSkills%', YearsExp='%YearsExp%', EducReq='%EducReq%', 
+Website='%Website%', CertReq='%CertReq%', MSCert='%MSCert%'
+WHERE AvailID=%AvailID%





