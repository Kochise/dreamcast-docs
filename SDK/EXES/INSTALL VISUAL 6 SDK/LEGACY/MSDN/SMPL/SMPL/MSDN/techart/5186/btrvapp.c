/*************************************************************************
**
**  Copyright 1997 Microsoft Corporation All Rights Reserved
**
*************************************************************************/
/***************************************************************************

   BTRIEVE APP.C
     This is the starting point progra for the Migrating Btrieve Applications 
	 to SQL Server discussion.  The program is a simple data entry and reoprting 
	 application that maintains information about book titles, the publishers 
	 that own these titles, and sales information for each title.  
	 
	 If the program is linked with BTRV32.dll it accesses the Sales.btr and 
	 Titlepub.btr btrieve files.  If the program is linked with MYBTRV32.dll 
	 it accesses the SQL Server BSALES and TitlePublisher tables.
   
****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <btrapi.h>
#include <btrconst.h>

/***************************************************************************
   Constants
****************************************************************************/
#define EXIT_WITH_ERROR		    1
#define TRUE					1
#define FALSE					0
#define VERSION_OFFSET			0
#define REVISION_OFFSET			2
#define PLATFORM_ID_OFFSET		4

#define NON_MATCH				999
#define B_BEGIN_CONCUR_TRAN		1019
/***************************************************************************
   Structure Type Definitions
****************************************************************************/

  // titlepub record structure
  struct
   {
	char	TitleID[ 7 ];	//string
	char	Title[ 81 ];	//string
	char	Type[ 13 ];		//string
	char	PubID[ 5 ];		//string
	float	Price;			//money
	float	Advance;		//money
	int		Royalty;		//integer
	int		YTD_Sales;		//integer
	char	PubName[ 41 ];	//string
	char	City[ 21 ];		//string
	char	State[ 3 ];		//string
	char	Country[ 31 ];	//string
   } tpRec;


  // sales record structure
  struct
   {
	char	StorID[ 5 ];	//string
    char	TitleID[ 7 ];	//string
	char	OrdNum[ 21 ];	//string
	int		Qty;			//integer
	char	PayTerms[ 13 ];	//string
   } salesRec;

/***************************************************************************
   Function Prototypes
****************************************************************************/

int BtrFileOpen(BTI_BYTE posBlock[128], char file[]);
BTI_SINT GetTitlePub(BTI_BYTE tpPB[128], BTI_WORD op, BTI_WORD keyNum, BTI_BYTE keyBuf[ 255 ]);
BTI_SINT GetSales(BTI_BYTE salesPB[128], BTI_WORD op, BTI_BYTE keyBuf[ 255 ], int print);
BTI_SINT YTDSales(BTI_BYTE tpPB[128], BTI_BYTE salesPB[128]);
BTI_SINT AddTitlePub(BTI_BYTE tpPB[128]);
BTI_SINT AddSales(BTI_BYTE salesPB[128]);
BTI_SINT PubYTDSales(BTI_BYTE tpPB[128], BTI_BYTE salesPB[128]);

/***************************************************************************
   Main
****************************************************************************/
int main( void )
{
   BTI_BYTE dataBuf[ 1000 ];	// Btrieve data buffer needed for BTRV funcation calls
   BTI_SINT status;				// BTRV return code status
   BTI_WORD dataLen;			// dataBuf length
   BTI_BYTE keyBuf[1000 ];		// key buffer used for BTRV function calls
   BTI_WORD keyNum = 0;			// Key number used for searches
   BTI_BYTE tpPB[ 128 ];		// Position block used for TitlePublisher interface
   BTI_BYTE salesPB[ 128 ];		// Position block used for Sales interface
   int quitnow = 1;
   char RageOn[]="999";			

   

   /* Initialize variables */
   unsigned char fileOpen = FALSE;
   unsigned char btrieveLoaded = FALSE;

   BTI_BYTE  clientID[ 16 ] = { 0,0,0,0,0,0,0,0,0,0,0,0,'M','T',0,1 }; 

   dataLen = sizeof( dataBuf );

   /************************************************************************
      GET THE BTRIEVE VERSION. 
    
   *************************************************************************/
   
   status = BTRVID( B_VERSION, tpPB, &dataBuf, &dataLen, keyBuf,
               keyNum, clientID );
   if ( status == B_NO_ERROR )
      btrieveLoaded = TRUE;
   else
   {
      if ( status != B_RECORD_MANAGER_INACTIVE )
         btrieveLoaded = TRUE;
   }

   /* RELEASE RESOURCES FOR clientID IN NON-DOS ENVIRONMENTS. */
   status = BTRVID( B_STOP, tpPB, &dataBuf, &dataLen, keyBuf,
               keyNum, clientID );

 
   // Open TitlePublishers and Sales Btrieve files

   BtrFileOpen(tpPB,  "titlepub.btr" );
   BtrFileOpen(salesPB,  "sales.btr" ); 

   // Present operation options until user quits 
	while (quitnow > 0 && quitnow <5)
	{
		printf("\n\nENTER DESIRED OPERATION:");
		printf("\n\t1 - SEARCH FOR A TITLE, IT'S SALES INFO, AND DISPLAY IT'S YTD SALES");
		printf("\n\t2 - INSERT TITLE/PUBLISHERS INFO ");
		printf("\n\t3 - INSERT SALES INFO ");
		printf("\n\t4 - UPDATE YTD_SALES FOR EACH TITLE OWNED BY A SPECIFIC PUBLISHER ");
		printf("\n\t0 - QUIT\n"); 
		printf("CHOICE: ");
		gets(RageOn);

		switch((quitnow=atoi(RageOn)))
		{
	  
			case 0:  //quit
			break;

			case 1:  //title sales search
				YTDSales(tpPB, salesPB);
			break;

			case 2:  //title/publisher insert
				AddTitlePub(tpPB);
			break;

			case 3:  //sales insert
				AddSales(salesPB);
			break;

			case 4:  //update YTD_SALES for each title owned by a specific publisher
			{
				PubYTDSales(tpPB, salesPB);
			break;
			}

			default: //shouldn't go here
				printf("\nInvalid choice - Please choose an option from 0 - 4\n\n");
				quitnow = 1;
			break;


		} //switch
   } //while
	
	// Close interface with Btrieve
	if ( btrieveLoaded )
	{
      dataLen = 0;
      status = BTRV( B_STOP, tpPB, dataBuf, &dataLen, keyBuf, keyNum );
      printf( "Btrieve STOP status = %d\n", status );
      if ( status != B_NO_ERROR )
         status = EXIT_WITH_ERROR;
	}

   return( (int)status );
}

/*************************************************************************************
	BtrFileOpen
/*************************************************************************************/

int BtrFileOpen (BTI_BYTE posBlock[128], char file[])
{
   BTI_BYTE dataBuf[ 255 ];
   BTI_SINT status;
   BTI_WORD dataLen;
   BTI_BYTE keyBuf[ 255 ];
   BTI_WORD keyNum = 0;
   
   
   keyNum = 0;
   dataLen = 0;
     
   // open the file
   strcpy( (BTI_CHAR *)keyBuf, file );
   status = BTRV( B_OPEN, posBlock, dataBuf, &dataLen, keyBuf, keyNum );
   printf( "Btrieve %s B_OPEN status = %d\n", file, status );
   
    
	return((int) status);
}


/*************************************************************************************
	GetTitlePub
*************************************************************************************/
BTI_SINT GetTitlePub(BTI_BYTE tpPB[128], BTI_WORD op, BTI_WORD keyNum, BTI_BYTE keyBuf[ 255 ])
{
	BTI_SINT tpStat;
	BTI_WORD dataLen;
	int ok=0;
   
   /* GET TITLE/PUBLISHERS RECORD WITH op */
	memset( &tpRec, 0, sizeof(tpRec) );
	dataLen = sizeof(tpRec);
	tpStat = BTRV( op, tpPB, &tpRec, &dataLen, keyBuf, keyNum );
	if (tpStat != B_NO_ERROR)
		return tpStat;
	
	switch(keyNum)
	{
		case 0:  // Search on keynum 0  - TitleID; Verify match between PubId fetched and keyBuf 
			if (!strcmp(tpRec.TitleID, keyBuf))
				ok=1;
		break;

		case 3: // Search on keynum 3 - PubID; Verify match between TitleId fetched and keyBuf 
			if (!strcmp(tpRec.PubID, keyBuf))
				ok=1;
		break;

		default:
		break;
	}

	if (ok) // Print the record if it was found
	{
		printf( "\nTitle/Publishers Record is: \n TITLE ID: \t%s\n TITLE: \t%s\n TYPE: \t\t%s\n PUB ID: \t%s\n", tpRec.TitleID, tpRec.Title, tpRec.Type, tpRec.PubID);
		printf(" PUB NAME: \t%s\n PUB CITY: \t%s\n PUB STATE: \t%s\n PUB COUNTRY: \t%s\n", tpRec.PubName, tpRec.City, tpRec.State, tpRec.Country);	
		printf(" PRICE: \t%.2f\n ADVANCE \t%.2f\n ROYALTY: \t%i\n YTD_SALES \t%i\n\n",  tpRec.Price, tpRec.Advance, tpRec.Royalty, tpRec.YTD_Sales);	
	}
	else
		return B_END_OF_FILE;	

	return B_NO_ERROR;
}



/*************************************************************************************
	GetSales
*************************************************************************************/
BTI_SINT GetSales(BTI_BYTE salesPB[128], BTI_WORD op, BTI_BYTE keyBuf[ 255 ], int print)
{
	BTI_SINT salesStat;
	BTI_WORD dataLen;
	char TitleID[7];
	
   
   /* Get TITLE/PUBLISHER with OPERATION*/
	strcpy(TitleID, keyBuf);
	memset( &salesRec, 0, sizeof(salesRec) );
	dataLen = sizeof(salesRec);

	// Fetch SALEs record based on TitleID
	salesStat = BTRV( op, salesPB, &salesRec, &dataLen, keyBuf, 1 );
	if (salesStat != B_NO_ERROR)
		return salesStat;

	// Print if desired record found
	if (!strcmp(salesRec.TitleID, TitleID)){
		if (print)
			printf( "\n TITLE ID: %s\t QTY: %i",  salesRec.TitleID, salesRec.Qty);
	}
	else
		return NON_MATCH;

	return B_NO_ERROR;

}

/*************************************************************************************
	YTDSales
*************************************************************************************/
BTI_SINT YTDSales(BTI_BYTE tpPB[128], BTI_BYTE salesPB[128])
{
	BTI_SINT tpStat, salesStat;
	char	choice[100];
	char	sVal[100];
	int		salesQty=0;


	// Get the TitleID to gather year to date sales on
	printf("\n\nENTER THE 6 CHAR TITLE ID: ");
    gets(choice);
	strcpy(sVal, choice);
    printf("\n\n");

	// Fetch TitlePublisher record 
	tpStat=GetTitlePub(tpPB, B_GET_EQUAL, 0, sVal);
	if (tpStat != B_NO_ERROR){
		printf( "\nBtrieve TitlePublishers fetch status = %d\n", tpStat );
		return tpStat;
	}

	// Fetch all of the Sales records for this TitleId and total sales
	if (tpStat == B_NO_ERROR)
	{
		salesStat=GetSales( salesPB, B_GET_EQUAL, sVal, 1);
		if (salesStat != B_NO_ERROR && salesStat!=NON_MATCH){
			printf( "\nBtrieve Sales fetch status = %d\n", salesStat );
			return salesStat;
		}
		while (salesStat == B_NO_ERROR)
		{
			salesQty = salesQty + salesRec.Qty;
			salesStat=GetSales( salesPB, B_GET_NEXT, sVal, 1);
			if (salesStat!= B_NO_ERROR && salesStat!=NON_MATCH){
				printf( "\nBtrieve Sales fetch status = %d\n", salesStat );
				return salesStat;
			}
		}
		salesQty = salesQty + tpRec.YTD_Sales;
		printf("\n\n YTD SALES for %s = %i\n\n", tpRec.TitleID, salesQty);
	}

	return B_NO_ERROR;
}

/*************************************************************************************
	AddTitlePub
*************************************************************************************/
BTI_SINT AddTitlePub(BTI_BYTE tpPB[128])
{
	BTI_SINT tpStat;
	BTI_WORD dataLen;
	char choice[100];
	char cont[2]="Y";

	while (!strcmp(cont, "Y") || !strcmp(cont, "y"))
	{
		memset( &tpRec, 0, sizeof(tpRec) );
		memset( &choice, 0, sizeof(choice) );

		printf("\n\nENTER TITLE AND PUBLISHER INFO (* denotes optional info):\n");
		printf("TITLE ID [6 CHAR MAX]: ");
		gets(tpRec.TitleID);

		printf("\nTITLE [80 char max]: ");
		gets(tpRec.Title);	  

		printf("\nTYPE [12 char max]: ");
		gets(tpRec.Type);

		printf("\n* PRICE [9999.99 format]: ");
		gets(choice);
		tpRec.Price = (float) atof(choice); 

		printf("\n* ADVANCE [9999.99 format]: ");
		gets(choice);
		tpRec.Advance = (float) atof(choice);

		printf("\n* ROYALTY [9999 format]: ");
		gets(choice);
		tpRec.Royalty = atoi(choice);	  

		printf("\n* YTD_SALES [9999 format char max]: ");
		gets(choice);
		tpRec.YTD_Sales = atoi(choice);

		printf("\nPUB ID [4 char max]: ");
		gets(tpRec.PubID);

		printf("\n* PUB NAME [30 char max]: ");
		gets(tpRec.PubName);

		printf("\n* PUB CITY [20 char max]: ");
		gets(tpRec.City);

		printf("\n* PUB STATE [2 char max]: ");
		gets(tpRec.State);

		printf("\n* PUB COUNTRY [2 char max]: ");
		gets(tpRec.Country);

		// Insert the new TitlePublisher record within a transaction
		dataLen = sizeof(tpRec);
		tpStat = BTRV(B_BEGIN_CONCUR_TRAN, tpPB, 0, 0, 0, 0); // Begin Transaction

		tpStat = BTRV(B_INSERT, tpPB, &tpRec, &dataLen, tpRec.TitleID, 0 );  // Insert the record
		if (tpStat != B_NO_ERROR){  // Error returned abort the transaction
			printf( "\nBtrieve TitlePublishers UPDATE status = %d\n", tpStat ); 
			tpStat = BTRV(B_ABORT_TRAN, tpPB, 0, 0, 0, 0);
			return B_UNRECOVERABLE_ERROR;
		}

		tpStat = BTRV(B_END_TRAN, tpPB, 0, 0, 0, 0); // Insert successful end transaction
		
		printf("\n\nContinue adding Title/Publisher Info [Y/N]:");
		gets(cont);
		if ((strcmp(cont,"Y")) && (strcmp(cont,"N"))  && (strcmp(cont,"y")) && (strcmp(cont,"n")))
			strcpy(cont, "N");
	 }


	return B_NO_ERROR;
}


/*************************************************************************************
	AddSales
*************************************************************************************/
BTI_SINT AddSales(BTI_BYTE salesPB[128])
{
	BTI_SINT	salesStat;
	BTI_WORD	dataLen;
	char		choice[100];
	char		cont[2]="Y";


	while (!strcmp(cont, "Y")  || !strcmp(cont, "y"))
	{
		memset( &salesRec, 0, sizeof(tpRec) );
		memset( &choice, 0, sizeof(choice) );

		printf("\n\nENTER SALE INFO:\n");
		printf("STORE ID [4 CHAR]: ");
		gets(salesRec.StorID);

		printf("\nTitle ID [6 char ]: ");
		gets(salesRec.TitleID);	  

		printf("\nORDER NUMBER [20 char max]: ");
		gets(salesRec.OrdNum);	  

		printf("\nQUANTITY [99999 format]: ");
		gets(choice);
		salesRec.Qty = atoi(choice);

		printf("\nPAY TERMS  [13 char max]: ");
		gets(salesRec.PayTerms);	
		
		// Insert the new Sales record within a transaction
		dataLen = sizeof(salesRec);
		salesStat = BTRV(B_BEGIN_CONCUR_TRAN, salesPB, 0, 0, 0, 0);  // Begin Transaction

		salesStat = BTRV(B_INSERT, salesPB, &salesRec, &dataLen, salesRec.TitleID, 0 ); // Insert the record
		if (salesStat != B_NO_ERROR){		// Error returned abort the transaction
			printf( "\nBtrieve TitlePublishers UPDATE status = %d\n", salesStat );
			salesStat = BTRV(B_ABORT_TRAN, salesPB, 0, 0, 0, 0);
			return B_UNRECOVERABLE_ERROR;
		}

		salesStat = BTRV(B_END_TRAN, salesPB, 0, 0, 0, 0);  // Insert successful end transaction 


		printf("\n\nContinue adding Sales Info [Y/N]:");
		gets(cont);
		if ((strcmp(cont,"Y")) && (strcmp(cont,"N")) && (strcmp(cont,"y")) && (strcmp(cont,"n")))
			strcpy(cont, "N");
	}
	

	return B_NO_ERROR;
}

/*************************************************************************************
	PubYTDSales
*************************************************************************************/
BTI_SINT PubYTDSales(BTI_BYTE tpPB[128], BTI_BYTE salesPB[128])
{
	BTI_SINT tpStat, salesStat;
	BTI_WORD dataLen;
	char	choice[100];
	char	sVal[100];
	char	TitleID[7];
	int		salesQty=0;

	// Get PubId for Publisher for which we will be gathering year to date sales totals
	printf("\n\nENTER THE 4 CHAR PUB ID: ");
    gets(choice);
	strcpy(sVal, choice);
    printf("\n\n");

	// Begin Transaction
	tpStat = BTRV(B_BEGIN_CONCUR_TRAN, tpPB, 0, 0, 0, 0);
	
	//Get the first TITLEPUBLISHER associated with entered PUBID
	tpStat=GetTitlePub(tpPB, B_GET_EQUAL, 3, sVal);
	if (tpStat != B_NO_ERROR){
		printf( "\nBtrieve TitlePublishers B_GET_EQUAL status = %d\n", tpStat );
		tpStat = BTRV(B_ABORT_TRAN, tpPB, 0, 0, 0, 0);
		return B_UNRECOVERABLE_ERROR;
	}

	// Process the sales records for this PubID
	while (tpStat != B_END_OF_FILE && tpStat != B_UNRECOVERABLE_ERROR)
	{
		//Get the first SALES record, if one exists, for the TITLEID
		strcpy(TitleID, tpRec.TitleID);
		salesStat=GetSales( salesPB, B_GET_EQUAL, TitleID, 0);
		if (salesStat!= B_NO_ERROR && salesStat!=NON_MATCH && salesStat != B_KEY_VALUE_NOT_FOUND){
			printf( "\nBtrieve Sales GET_EQUAL fetch status = %d\n", salesStat );
			tpStat = BTRV(B_ABORT_TRAN, tpPB, 0, 0, 0, 0);
			return salesStat;
		}
		while (salesStat == B_NO_ERROR)  //Get remaining SALES records for the TITLEID
		{
			salesQty = salesQty + salesRec.Qty;
			salesStat=GetSales( salesPB, B_GET_NEXT, TitleID, 0);
			if (salesStat!= B_NO_ERROR && salesStat!=NON_MATCH){
				printf( "\nBtrieve Sales GET_NEXT fetch status = %d\n", salesStat );
				tpStat = BTRV(B_ABORT_TRAN, tpPB, 0, 0, 0, 0);
				return salesStat;
			}
		}
	
		tpRec.YTD_Sales = tpRec.YTD_Sales + salesQty;
		dataLen = sizeof(tpRec);

		//Update with -1 key value because key for the record is not to be changed
		tpStat = BTRV(B_UPDATE, tpPB, &tpRec, &dataLen, TitleID, -1 );
		if (tpStat != B_NO_ERROR){  // Error abort transaction
			printf( "\nBtrieve TitlePublishers UPDATE status = %d\n", tpStat );
			tpStat = BTRV(B_ABORT_TRAN, tpPB, 0, 0, 0, 0);
			return B_UNRECOVERABLE_ERROR;
		}
		
		// Print update ytd sales for this PubId
		printf("\n %s RECENT SALES = %i  UPDATED YTD SALES = %i\n\n\n", tpRec.TitleID, salesQty, tpRec.YTD_Sales);
		salesQty=0;
		tpStat=GetTitlePub(tpPB, B_GET_NEXT, 3, sVal);
	}

	tpStat = BTRV(B_END_TRAN, tpPB, 0, 0, 0, 0);
	return B_NO_ERROR;
}

