/********************************************************************
 * pack.h
 *
 * Description
 *   CVibrationPack class.
 ********************************************************************/

#ifndef __PACK_H        // Prevent multiple inclusions
#define __PACK_H

/********************************************************************
 * Includes
 ********************************************************************/
#include <mapledev.h>
#include <vib.h>

/********************************************************************
 * class CVibrationPack
 *
 * Description
 *   Holds information for each vibration pack plugged in at last
 *   scan.
 ********************************************************************/
class CVibrationPack
{
    public:
        // Constructor/Destructor
                        CVibrationPack(LPCMAPLEDEVICEINSTANCE pMDI);
        virtual        ~CVibrationPack(void);

        // Validation functions
        BOOL            IsOkay(void);
        VARIANT_BOOL    IsPlugged(void);

        // Member data
        IVib           *_pVib;          // Vibration device 
        short           _nSources;      // Number of sources in pack
        short           _nSimSources;   // Number of simultaneous sources
                                        // Vibration pack source data
        VIB_INFO        _aVibInfo[VIB_MAX_SOURCES];
                                        // Autostop times for vib pack sources
        BYTE           _aAutoStop[VIB_MAX_SOURCES];
};

#endif // __PACK_H
