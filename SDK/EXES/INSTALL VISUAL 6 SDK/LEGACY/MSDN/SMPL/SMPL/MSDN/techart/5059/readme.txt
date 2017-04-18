PDHTest Notes:

This sample includes the following files:

PDHFns.c:

Demonstrates the use of the PDH Library Functions

Window.c:

Window handling routines - Main Window, List View, 
Status Window, Window procedures, menu handling 
routines, list view manipulation, etc.

PDHTEST.h:

Header file containing struction definitions, constant 
definitions and function prototypes.

RESOURCE.h:

Header file containing resource ID's

PDHRes.rc:

Resource file containing all resources

Import.txt:

Text file that contains a string (counter name) 
that can be imported.


The program starts by displaying an empty list view control and 
initializing an empty Query.  To add counters to the query, you 
can either import them (from a text file) by choosing the 
Import... options from the File menu.  You can also add 
counters with a dialog box supplied by the PDH Library by 
choosing Browse Counters... from the PDH menu.  Once 
counters have been added, their names will appear in the 
list view control.  To collect (and display) data, you must 
choose the Collect Query Data option from the PDH menu.  
This will gather raw data, format it and display it in 
the list view control.

You can automate data collection by choosing the Start 
option from the Auto menu.  To stop automatic collection 
choose Stop option from the Auto menu.  While this feature 
is enabled, data collection will occur once each second.  
To display statistics (minimum, maximum, average) choose 
Statistics from the Auto menu.  If this option is enabled, 
then raw data will be collected and stored.  Once each 
second, the program will pass this data to the PDH 
library for analysis and the statistical results will 
be displayed.

You can export the counter list to a text file by choosing 
Export... from the File menu.

You can right click on the list view control to more 
quickly locate menu options.