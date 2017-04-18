/*=============================================================================
  =============================================================================*/
  
  
/*=============================================================================
  =============================================================================*/
  
#include <shinobi.h>
#include "ginsu.h"

/*=============================================================================
  =============================================================================*/

void main(void)
{
    char        firstExe    [1000];
    char        firstDir    [1000]  = "\\";
    int         firstGDDA           = 2;
    void*       bigbuf256k  = NULL;
    GS_APP_ID   appGinsu    = NULL;

    
    /* -- Clear DDS to work with old binaries -- */
    #define SYD_DDS_FLAG_ADR  (0x8c0080fc)
    #define SYD_DDS_FLAG_CLEAR (0x20)

    //void syDdsClearDDSFlag( void )
    {
        *(Uint8 *)SYD_DDS_FLAG_ADR = SYD_DDS_FLAG_CLEAR;
    }
        
//njSetBorderColor (0x00000000);
    
    gsInit();
    
//njSetBorderColor( 0x00000000 ) ;
  switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
        
//njInitVertexBuffer(10000, 0, 100000, 0, 0);
//njInitPrint(NULL,0,0) ;
//njSetBackColor(0x00803808, 0x00803010, 0x00800040);
    
            bigbuf256k = malloc(GS_INI_BUFFER_SIZE);
            gsIniOpen (bigbuf256k);
    
                /* -- get GINSU app for basic configuration info -- */
                appGinsu = gsFindApp ("GINSU");
                if (appGinsu)
                {
                    /* -- setup default program information -- */
                    {
                        const char* kvalue = gsGetKeyValue(appGinsu, "Ginsu.DefaultApp");
                        if (kvalue)
                        {
                            GS_APP_ID app = gsFindApp(kvalue);
                            if (app)
                            {
                                const char* exename = gsGetKeyValue(app, "Ginsu.Command");
                                if (exename)
                                {
                                    const char* dirptr = gsGetKeyValue(app, "Ginsu.Path");
                                    gsSetDefaultExecutable (exename, dirptr);
                                }
                            }
                        }
                    }
                    
                    /* -- setup transfer program information -- */
                    {
                        const char* kvalue  = gsGetKeyValue (appGinsu, "Ginsu.XferExecutable");
                        if (kvalue)
                        {
                            gsSetXFerExecutable (kvalue);
                        }
                    }
                    
                    /* -- extract first program information -- */
                    {
                        const char* kvalue = gsGetKeyValue(appGinsu, "Ginsu.FirstApp");
                        if (kvalue)
                        {
                            GS_APP_ID app = gsFindApp(kvalue);
                            if (app)
                            {
                                const char* exename = gsGetKeyValue(app, "Ginsu.Command");
                                if (exename)
                                {
                                    strcpy (firstExe, exename);
                                }
                                
                                /* -- the working directory -- */
                                {   /* -- try to read actual working dir -- */
                                    const char* dirptr = gsGetKeyValue (app, "Ginsu.Path");
                                    if (dirptr)
                                    {
                                        strcpy (firstDir  , dirptr);
                                    }
                                }
                
                                /* -- the gdda offset -- */
                                {   /* -- try to read actual working dir -- */
                                    const char* numptr = gsGetKeyValue (app, "Ginsu.FirstGDDA");
                                    if (numptr)
                                    {
                                        firstGDDA = atoi(numptr);
                                    }
                                }
                            }
                        }
                    }
                }
    
            gsIniClose();




//{
//    int i;
//    NJS_PERIPHERAL* padinfo;
//    for (i=0; i<60; i++)
//    {
//    njPrintSize(8);
//    njPrintColor(0xffffffff);
//    njPrintC(NJM_LOCATION(20,10), "Initializing...");
//    padinfo = njGetPeripheral(NJD_PORT_A0);
//    
//    njWaitVSync();
//    }
//    
//}    
//
//njExitPrint();

	    sbExitSystem();

    gsSetFirstGDDA  (firstGDDA);
    gsSetBasePath   (firstDir);
    gsExitTo        (firstExe,firstDir,firstGDDA);
} 
