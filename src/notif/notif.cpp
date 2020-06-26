#include "notif/notif.h"

boolean state = false;

void notif :: notif_init(){
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(BUZZER,OUTPUT);
}

void notif :: notif_beep(uint8_t counter, uint16_t longbeep){
  for(uint8_t i=1; i<=counter; i++){
    LED_ON(LED0);
    BUZZER_ON();
    delay(longbeep);
    LED_OFF(LED0);
    BUZZER_OFF();
    delay(longbeep);
  }  
}

void notif :: notif_powerup(){
  notif_beep(2,100);
}

void notif :: notif_accessgrant(){
  notif_beep(1,100);
}

void notif :: notif_accessreject(){
  notif_beep(2,500);
}
void notif :: notif_network_connected(){
  state = !state; 
  digitalWrite(LED1,state);
}
void notif :: notif_network_notconnected(){
  digitalWrite(LED1,false);
}
