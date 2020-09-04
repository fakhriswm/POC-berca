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
        void notif_idle();

        void timer_init(void (*f)(), uint32_t interval);
	      void timer_start(void (*f)(),uint32_t interval);
	      void timer_pause();
	      void timer_resume();

        uint32_t timer_interval;
        typedef void (*callback_function)(); //create function pointer type
	      callback_function callback_func;

      private:
        hw_timer_t * timer = NULL;
};


#endif