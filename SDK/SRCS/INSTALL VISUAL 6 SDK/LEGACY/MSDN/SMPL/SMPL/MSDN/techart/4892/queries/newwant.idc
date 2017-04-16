Datasource: JobForum
Template: NewWant.htx
DefaultParameters: 
RequiredParameters: ContactName
SQLStatement:
+INSERT INTO JobWanted (ContactName, Company, Address, City, State
+, Zip, Country, Phone, FAX, Email, ContactMethodID, JobTypeID
+, JobClass, JobDesc, Location, SpecialSkills, YearsExp, Education, Website, MSCert, Password) 
+VALUES ('%ContactName%', '%Company%', '%Address%', '%City%'
+, '%State%', '%Zip%', '%Country%', '%Phone%', '%FAX%', '%Email%'
+, %ContactMethodID%, %JobTypeID%,'%JobClass%', '%JobDesc%', +'%Location%', '%SpecialSkills%', +'%YearsExp%', '%Education%', +'%Website%', '%MSCert%', '%Password%');

