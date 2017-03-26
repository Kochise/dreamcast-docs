/* Example program */

#include <stdio.h>
#include <kos.h>

int startButtonPressed(void)
{
    cont_cond_t controller;

    cont_get_cond(maple_addr(0, 0), &controller);

    return !(controller.buttons & CONT_START);
}

int main()
{
    int           bytesRead = 0;
    int           i;
    unsigned char data[1024];

    if (!modem_init())
    {
       printf("modem_init failed!\n");
       return 1;
    }

    modem_set_mode(MODEM_MODE_DIRECT, MODEM_SPEED_V34_AUTO);

    printf("Waiting for a connection\n");
    while (modem_is_connecting())
    {
          if (startButtonPressed())
          {
             printf("Connection aborted\n");
             return 1;
          }
    }

    if (!modem_is_connected())
    {
       printf("Connection failed\n");
       return 1;
    }

    printf("Connected at %dbps\n", modem_get_connection_rate());

    while (!startButtonPressed())
    {
          if (modem_has_data())
          {
             bytesRead = modem_read_data(data, 256);
             if (bytesRead > 0)
             {
                for (i=0; i<bytesRead; i++)
                    printf("%c", data[i]);
             }
          }
    }

    printf("Disconnecting..\n");
    modem_disconnect();

    return 0;
}
