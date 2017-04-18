/*
 *  Middleware Library
 *  Copyright (c) 1998,1999 SEGA
 *  
 *		TrueMotion
 *
 *  Module  : Library Header File
 *  File    : TM_MW.H
 *  Create  : 1998-03-10
 *  Modify  : 
 *  Note    :
 */

#ifndef	_TM_MW_H_
#define	_TM_MW_H_

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/

typedef	struct tm_Tag{
	int nothing_in_here_yet;
}MWS_PLY_CPRM_TM;

#ifdef	__cplusplus
extern	"C"	{
#endif	/*	__cplusplu		*/
/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

/*	Initialize TrueMotion Library		*/
void	mwPlyInitTM(void);

/*	Finish using TrueMotion Library		*/
void	mwPlyFinishTM(void);

/*	Create MWPLY handle for TrueMotione	*/
MWPLY	mwPlyCreateTM(MWS_PLY_CPRM_TM *cprm);

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_TM_MW_H_	*/
