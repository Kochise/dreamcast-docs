/*
** LibS3MPlay Example Player (C) Josh PH3NOM Pearson 2011
*/

#include <kos.h>
#include "libs3mplay/libs3mplay.h"

int check_cont() {
		
		int ret=0;
    	
        maple_device_t *cont;
	    cont_state_t *state;		
        cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

		if(cont)
		{
			state = (cont_state_t *)maple_dev_status(cont);
			if (!state)
				ret = 0;
			if (state->buttons & CONT_Y) {
                ret = 1;               
			}
			if (state->buttons & CONT_START) {
                ret = 2;
            }
		}
		
		return ret;
		
}

int main()
{
    printf("LibS3MPlay Example (C) PH3NOM 2011\n");
    int stat;
    
    stat = s3m_play("/cd/sample.s3m");
    
    if( stat != S3M_SUCCESS )
    {
        switch (stat)
        {
            case S3M_ERROR_IO:
                 printf("Unabled to open s3m file\n");
                 return -1;
            case S3M_ERROR_MEM:
                 printf("s3m file exceeds available SRAM\n");
                 return -1;
        }
    }

	while(1) {
       int input = check_cont();
       int exit=0;
       switch (input) {
              case 0:
                   break;
              case 1:
               	   printf("LibS3M: restarting\r\n");
                   s3m_stop();
                   s3m_play("/cd/sample.s3m");
                   break;
              case 2:
                   exit++;
                   break;
              default:
                   break;     
       }
       if(exit)
           break;
       thd_sleep(50);
	}
	
    s3m_stop();
    
    printf("LibS3MPlay Example Exiting\n");
    
    return 0;
    
}

