Datasource: JobForum
Template: NewAvail.htx
DefaultParameters: 
RequiredParameters: ContactName, JobTitle
SQLStatement:
+INSERT INTO JobAvailable (ContactName, Company, Address, City, State,
+Zip, Country, Phone, FAX, Email, ContactMethodID, JobCity, JobState, JobAreaCode, 
+JobZip, JobTypeID, JobTitle, JobDesc, SpecialSkills, YearsExp, EducReq, Website, 
+CertReq, MSCert, Password) 
+VALUES ('%ContactName%', '%Company%', '%Address%', '%City%'
+,'%State%', '%Zip%', '%Country%', '%Phone%', '%FAX%', '%Email%'
+,%ContactMethodID%, '%JobCity%' , '%JobState%' , '%JobAreaCode%' 
+,'%JobZip%', %JobTypeID%, '%JobTitle%', '%JobDesc%', '%SpecialSkills%'
+,'%YearsExp%', '%EducReq%', '%Website%', '%CertReq%', '%MSCert%', '%Password%');

