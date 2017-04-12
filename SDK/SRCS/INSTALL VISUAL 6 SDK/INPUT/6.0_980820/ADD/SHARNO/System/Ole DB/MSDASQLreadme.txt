---------------------------------------------------------
Microsoft(R) OLE DB Provider for ODBC Readme File
---------------------------------------------------------

(c) Microsoft Corporation, 1998

This document provides late-breaking or other information that supplements the Microsoft OLE DB Provider for ODBC documentation.

Please see the Data Access SDK readme file for additional information about OLE DB.

--------
CONTENTS
--------
1. PRODUCT DESCRIPTION
2. NEW FEATURES
3. TECHNICAL NOTES
4. KNOWN LIMITATIONS


----------------------
1. PRODUCT DESCRIPTION
----------------------
The ODBC Provider delivers rich, high-performance access to any ODBC database. 

---------------
2. NEW FEATURES
---------------
The 2.0 version of this provider contains better handling of long data as well as performance and scaling enhancements. 

------------------
3. TECHNICAL NOTES
------------------
* New Server Name Property
A new property, DBPROP_SERVER_NAME, has been added. This property is a datasource information property, not an initialization property. It returns, upon initialization, the name of the server to which you are connected. In many cases, this will be the same as the DBPROP_INIT_DATASOURCE property. For example, when connecting to an ODBC datasource you might specify a DSN (friendly name), and the server name would tell you the name of the actual server to which you were connected.

* IOpenRowset doesn't quote table names. 
The ODBC provider does not quote table names passed through DBIDs -- for instance, in IOpenRowset. Therefore, when trying to open a table against the ODBC provider that requires quoting the name (for instance, when the table name contains extended characters), the consumer must add the quotes to the table name manually or simply execute SELECT * FROM <quoted table name>.

* Boolean parameters are not converted to "True"/"False".
The OLE DB Specification calls for Booleans converted to string data types to appear as the strings "True" or "False". Using the ODBC provider, if the underlying ODBC driver does not support SQLDescribeParam and the OLE DB consumer does not specify the type of the parameter, the ODBC provider will convert Boolean parameter values to "-1" and "0" when the data type of the parameter is a string. In order to ensure proper conversion against ODBC drivers that do not support describing parameters, the OLE DB consumer should always call SetParameterInfo to specify the types of parameters. 

* Setting DBPROPINITMODE to read-only is advisory for ODBC, not mandatory (and therefore is advisory for the ODBC provider).

-----------------
4. KNOWN LIMITATIONS
-----------------
* Do not use DBPROP_INIT_LOCATION with MSDASQL and a Microsoft Access database. 
When attempting to initialize MSDASQL (the ODBC Provider), if you set the initialization property DBPROP_INIT_LOCATION to a valid value and specify that the DATASOURCE is a Microsoft Access data source, a crash will occur. Do not use the property DBPROP_INIT_LOCATION with MSDASQL and a Microsoft Access data source.



