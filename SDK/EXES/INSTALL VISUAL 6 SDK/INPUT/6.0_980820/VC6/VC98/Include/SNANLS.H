#ifdef __cplusplus
extern "C"
{
#endif

#if !defined __SNANLS_INC__

#define __SNANLS_INC__

/* ********************* Constants ******************** */

#define	CP_37		37		/* EBCDIC Lower English	*/

#define	CP_273		273		
#define	CP_277		277		
#define	CP_278		278	
#define	CP_280		280	
#define	CP_284		284	
#define	CP_285		285	


#define	CP_290		290		/* EBCDIC Katakana	*/

#define	CP_297		297
#define CP_423		423
#define CP_500		500
#define CP_875		875	

#define	CP_930		930		/* EBCDIC Katakana + Kanji	*/
#define	CP_931		931		/* EBCDIC Lower English + Kanji	*/
#define	CP_932		932 	/* Japanese	*/

#define	CP_933		933		/* EBCDIC Korean	*/

#define CP_935		935		/* EBCDIC Simplified Chinese */
#define CP_936		936		/* Chinese */
#define	CP_937		937		/* EBCDIC Traditional Chinese	*/

#define	CP_939		939		/* EBCDIC Extended Lower English + Kanji	*/
#define	CP_949		949		/* Korean	*/
#define	CP_950		950		/* Taiwanese	*/
#define	CP_1027	    1027	/* EBCDIC Extended Lower English	*/


#define SNA_UNICODE   1  /* Result of Conversion is Unicode */
#define SNA_MULTIBYTE 2  /* Result of Conversion is MultiByte */

/* ********************* Functions ******************** */

/* ***************************************************************** */
/*		Initialization Routine : Local Machine						 */
/*			CodePage : The CodePage which we need to support         */
/*			return   : 1 if CodePage Translations are Supported      */
/*                     0 otherwise									 */
/* ***************************************************************** */

int WINAPI SnaNlsInit(UINT CodePage);

/* ***************************************************************** */
/*																	 */
/* Translation Routine												 */
/*																	 */
/*		Input														 */
/*																	 */
/*			lpSrcStr   : Input, Source String						 */
/*																	 */
/*			lpDestStr  : Output, Translated String			         */
/*							maybe NULL if out_length is 0			 */
/*																	 */
/*			inCodePage : CodePage of incoming string				 */
/*							ignored if input is in unicode			 */
/*																	 */
/*			outCodePage: CodePage of translated string.				 */
/*							ignored if output is in unicode			 */
/*																	 */
/*			in_length  : Length of input string				         */
/*							in characters if input is multibyte      */
/*							in wide chars if input is unicode        */
/*																	 */
/*          out_length : Length of output string					 */
/*							in characters if output is multibyte     */
/*							in wide chars if output is unicode       */
/*																	 */
/*			in_type    : SNA_UNICODE - Unicode Input				 */
/*						 SNA_MULTIBYTE - MultiByte Input			 */
/*																	 */
/*			out_type   : SNA_UNICODE - Unicode Output				 */
/*						 SNA_MULTIBYTE - MultiByte Output			 */
/*																	 */
/*			Options    : Multiple usage								 */
/*							Trnsdt Options							 */
/*							Default Character for Translation (NLS)  */
/*																	 */
/*		Output														 */
/*																	 */
/*			return val : 0 - Failure								 */
/*							Use GetLastError to retrieve error		 */
/*						 Else										 */
/*							Num of chars(wide) written to lpDestStr  */
/*																	 */
/*			lpDestStr  : Translated String							 */
/*																	 */
/* 			Options    : Required buffer length if call failed		 */
/*																	 */
/*			Errors	   : (Retrieved by using GetLastError)           */
/*																	 */
/*						  ERROR_NOT_SUPPORTED						 */
/*							Possible Reasons:		  				 */
/*								NLS is not available		 		 */
/*								Input & Output are not of same type	 */
/*																	 */
/*						 ERROR_BUFFER_OVERFLOW						 */
/*							Possible Reasons:						 */
/*								Output buffer is too small           */
/*																	 */
/*						 ERROR_INVALID_PARAMETER					 */
/*							Possible Reasons:						 */
/*								in_type or out_type is faulty        */
/*																	 */
/*						 ERROR_INVALID_DATA							 */
/*							Possible Reasons:						 */
/*								input data has a lead byte at end    */
/*																	 */
/*						 ERROR_OUTOFMEMORY							 */
/*							Possible Reasons:						 */
/*								malloc failed			             */
/*																	 */
/*																	 */
/* ***************************************************************** */

int WINAPI SnaNlsMapString (LPCTSTR lpSrcStr, LPTSTR lpDestStr,
					 UINT inCodePage, UINT outCodePage,
					 int in_length,   int out_length, 
					 UINT in_type, UINT out_type,  WORD * Options);



#endif

#ifdef __cplusplus
}
#endif