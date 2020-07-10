#include "peripheral/peripheral.h"

#define LED0       25
#define LED1       26
#define BUZZER     27
#define LEDPIN     2
#define BUTTONPIN  0    

#define LED_ON(LED)    digitalWrite(LED, HIGH)
#define LED_OFF(LED)   digitalWrite(LED, LOW)

#define  BUZZER_ON()   digitalWrite(BUZZER, HIGH)
#define  BUZZER_OFF()  digitalWrite(BUZZER, LOW)

int ledState = HIGH;         
int buttonState;             
int lastButtonState = LOW;   

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 2000; 

boolean state = false;

void periph :: init(){
    pinMode(BUTTONPIN, INPUT);
    pinMode(LED0,OUTPUT);
    pinMode(LED1,OUTPUT);
    pinMode(BUZZER,OUTPUT);
}

void periph :: button_read(){
    int reading = digitalRead(BUTTONPIN);
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == HIGH) {
            state = !state;
            Serial.println("state : " + (String)state);
        }
    }
  }
  lastButtonState = reading;
}

void periph :: notif_beep(uint8_t counter, uint16_t longbeep){
  for(uint8_t i=1; i<=counter; i++){
    LED_ON(LED0);
    BUZZER_ON();
    delay(longbeep);
    LED_OFF(LED0);
    BUZZER_OFF();
    delay(longbeep);
  }  
}

void periph :: notif_powerup(){
  notif_beep(2,100);
}

void periph :: notif_accessgrant(){
  notif_beep(1,100);
}

void periph :: notif_accessreject(){
  notif_beep(2,500);
}
void periph :: notif_network_connected(){
  state = !state; 
  digitalWrite(LED1,state);
}
void periph :: notif_network_notconnected(){
  digitalWrite(LED1,false);
}