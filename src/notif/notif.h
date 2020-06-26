#ifndef NOTIF_H_
  #define NOTIF_H_

#include <Arduino.h>

#define LED0       25
#define LED1       26
#define BUZZER     27

#define LED_ON(LED)    digitalWrite(LED, HIGH)
#define LED_OFF(LED)   digitalWrite(LED, LOW)

#define  BUZZER_ON()   digitalWrite(BUZZER, HIGH)
#define  BUZZER_OFF()  digitalWrite(BUZZER, LOW)

class notif{
  public :
    void notif_init();
    void notif_beep(uint8_t counter, uint16_t longbeep);
    void notif_cardpresent();
    void notif_accessgrant();
    void notif_accessreject();
    void notif_powerup();
    void notif_network_connected();
    void notif_network_notconnected();
};
    
#endif
