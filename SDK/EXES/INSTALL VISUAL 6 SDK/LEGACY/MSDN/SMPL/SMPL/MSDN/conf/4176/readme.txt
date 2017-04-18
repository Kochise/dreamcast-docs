
This group of files is intended to provide information on how to design and develop 
client/server applications in Microsoft Access 2.0. This content was developed for 
the Tech*Ed class AC302: "Creating Client/Server Applications with Microsoft Access" 

Included in this information set is:

	NWINDCS.MDB	This is the original NWIND orders form completely rebuilt and 
			optimized for the client/server environment.

	NWINDUP.MDB	This is the original NWIND.MDB database only modified to run
			against a SQL Server based, NorthWind data set. The main point
			to notice here is the technique used to alias tables and 
			fields by replacing a table with an aliasing query.

	NWINDCS.SQL	This is a complete SQL dump of all tables, indexes, and stored
			procedures that completely recreate the functionality of the 
			original NWIND.MDB database integrity including cascades. This
			is all in SQL Server Transact SQL.

In order to be able to run NWINDUP.MDB, or NWINDCS.MDB, you need to create and 
populate your server database. If you need more detailed help on the steps involved 
in migrating to SQL Server, please refer to the Migrating Microsoft Access Tables 
to Database Servers section in the "Creating Client/Server Applications with 
Microsoft Access".
		
A high level summary of steps involved in migrating from a file server to a 
client/server environment include:
	* Create the server database.
	* Establish your ODBC data source using the ODBC Administrator. The Data Source 
	  Name must be "NWIND".
	* Export each table to the server database, using the Export choice of Microsoft 
	  Access 2.0's File menu. The required files for NWINDCS.MDB are Orders, Order 
	  Details, Customers, and Products. Be sure to add a timestamp field to the end 
	  of the Order Details table.
	* Add the indexes and data integrity constraints to the server tables. Use the 
	  Transact SQL in NWINDCS.SQL included in this zip file. 
	* Re-attach to the server tables using the Microsoft Access attach facility from 
	  within the database.

There are many features of the NWINDCS.MDB orders application to take note of as you 
browse this application. A few of these include:
	* Data management takes place in 2 ways: through recordset management and through SQL 
	  Passthrough. You change the mode by checking or un-checking the SQL Passthrough box
	  on the orders form.
	* Field validation is checked before sending the update to SQL Server. If a field is 
	  not valid, the failing field is turned red, and control is returned to that field.
	* Lots of enabling and disabling of fields and buttons depending on the current 
	  mode of the application.
	* Both bound (orders subform) and unbound (orders master) forms are employed in order to
	  provide both ease of development, and batching of transactions to the server
	* Relocation of screen objects at runtime to provide both ease of development and 
	  high re-use of screen real estate at runtime.
	* Replacing of combo boxes for finding customers with more intelligent search logic.
	  Similar logic for product lookup on description.
	* Use of both local and remote (server based) data for optimal responsiveness and 
	  performance.

We hope you find these applications informative and helpful in your client/server development.
Access Marketing.
4/4/94
