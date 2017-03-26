/****************************************************************************/
/*!
\par Project:  libads
\par Module:   PSS audio plugin
\file          ads.h
\par Purpose:  ADS (Audio Data Stream) player API 
\par Platform: WIN32 DreamCast
\author        L@ Cible (la.cible@free.fr)
\date          Created on 24/04/2003 (DD/MM/YY)
\date          Updated on 25/04/2003 (DD/MM/YY)
*/
/****************************************************************************/

#ifndef ADS_OUT_H
#define ADS_OUT_H

/*
 * ads data format
 */
#define ADS_FORMAT_PCM_BIG		 0
#define ADS_FORMAT_PCM_LITTLE	 1
#define ADS_FORMAT_ADPCM		16


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

int  ADS_Open  (unsigned char * _adsHeader);
void ADS_Close ();
void ADS_Write (unsigned char * data, int size);

#ifdef    __cplusplus
}
#endif /* __cplusplus */


#endif //ADS_OUT_H