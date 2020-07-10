#ifndef PERIPHERAL_H_
  #define PERIPHERAL_H_

#include <Arduino.h>

class periph{
    public :
        void init();
        void button_read();
        void notif_beep(uint8_t counter, uint16_t longbeep);
        void notif_cardpresent();
        void notif_accessgrant();
        void notif_accessreject();
        void notif_powerup();
        void notif_network_connected();
        void notif_network_notconnected();
};

#endif