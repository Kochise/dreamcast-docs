#ifndef __UNI_H__
#define __UNI_H__

//
// Universe Constant
//
const double G_G = -6.67e-11 ;
const double G_SECS_PER_TICK = 86400 ;
const double G_WIDTH = 10e8 ;
const double G_HEIGHT = 10e8 ;
const UINT G_TIME = 100 ;


class CUniverse {
public:
// Functions
	static BOOL DoUniDialog() ;
	static BOOL DoTimeDialog() ;
	static void Save(CArchive& ar );

//Members
public:
	static double G ;
	static double SECS_PER_TICK ;
	static double WIDTH ;
	static double HEIGHT ;
	static UINT TIME ;
};


#endif //__UNI_H__
