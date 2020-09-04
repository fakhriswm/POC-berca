//on branch poc2
#include "main.h"
#include "task.h"

void task_create(){
#ifdef WIFI_VERSION
  xTaskCreatePinnedToCore(
    task_connectivity
    ,  "task_connectivity"   // A name just for humans
    ,  10000  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);
#endif

  xTaskCreatePinnedToCore(
    task_scanning
    ,  "task_scanning"
    ,  10000  // Stack size
    ,  NULL
    ,  3  // Priority
    ,  NULL 
    ,  0);
}

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
  DEBUG_PRINTLN("device number :" + (String)dev_code.get_deviceNumber());
  delay(1000);
  
  periph.init();
  periph.notif_powerup();
  
  flash.flash_init();
  flash.config_all();

  ble.ble_scan_init();
  mifare.mifare_init();

  if(!idle_mode){
    ibeacon.iBeacon_init();
    ibeacon.iBeacon_set(IBEACON_MAJOR,IBEACON_MINOR,BROADCAST_INTERVAL,BEACON_UUID);
    ibeacon.iBeacon_start();
    wifi_manager.wifi_init(false);
    DEBUG_PRINTLN("enable advertising");

    mqtt.mqtt_init();
    mqtt.mqtt_reconnect();

    periph.timer_init(onTimer,TIMER_INTERVAL);
    task_create();
  }
  else{
    wifi_manager.wifi_init(true);
    DEBUG_PRINTLN("disable advertising");
  }
    
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(idle_mode){
    mifare.mifare_read();
    periph.notif_idle();
    delay(1000);
  }
}//