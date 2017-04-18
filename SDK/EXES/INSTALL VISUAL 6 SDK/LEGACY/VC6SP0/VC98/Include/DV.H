#ifndef _DV_H_
#define _DV_H_


#define DV_SMCHN                0x0000e000
#define DV_AUDIOMODE    0x00000f00
#define DV_AUDIO5060    0x00200000
#define DV_AUDIOSMP             0x38000000
#define DV_AUDIOQU              0x07000000
#define DV_NTSC525_60   0
#define DV_PAL625_50    1

#define DV_SD           0x00
#define DV_HD           0x01
#define DV_SL           0x02


#define SIZE_DVINFO     0x20    



typedef struct tag_DVINFO{
	//for 1st 5/6 DIF seq.
	DWORD dwDVAAuxSrc;
	DWORD dwDVAAuxCtl;
	//for 2nd  5/6 DIF seq.
	DWORD dwDVAAuxSrc1;
	DWORD dwDVAAuxCtl1;
	//for video information
	DWORD dwDVVAuxSrc;
	DWORD dwDVVAuxCtl;
	DWORD dwDVReserved[2];

} DVINFO, *PDVINFO;

typedef struct Tag_DVAudInfo
{
	BYTE    bAudStyle[2];           
	//LSB 6 bits for starting DIF sequence number
	//MSB 2 bits: 0 for mon. 1: stereo in one 5/6 DIF sequences, 2: stereo audio in both 5/6 DIF sequences
	//example: 0x00: mon, audio in first 5/6 DIF sequence
	//                 0x05: mon, audio in 2nd 5 DIF sequence
	//                 0x15: stereo, audio only in 2nd 5 DIF sequence
	//                 0x10: stereo, audio only in 1st 5/6 DIF sequence
	//                 0x20: stereo, left ch in 1st 5/6 DIF sequence, right ch in 2nd 5/6 DIF sequence
	//                 0x26: stereo, rightch in 1st 6 DIF sequence, left ch in 2nd 6 DIF sequence
	BYTE    bAudQu[2];                      //qbits, only support 12, 16,           
		
	BYTE    bNumAudPin;                     //how many pin(language)
	WORD    wAvgSamplesPerPinPerFrm[2];     //samples size for one audio pin in one frame(which has 10 or 12 DIF sequence) 
	WORD    wBlkMode;                       //45 for NTSC, 54 for PAL
	WORD    wDIFMode;                       //5  for NTSC, 6 for PAL
	WORD    wBlkDiv;                        //15  for NTSC, 18 for PAL
} DVAudInfo;
	  
#endif // _DV_H_
