#include <Arduino.h>
#include "ble_scanning/ble_scanning.h"
#include "FS_config/FS_config.h"
#include "wifi_manager/wifi_manager.h"
#include "webserver_handle/webserver_handle.h"
#include "mifare_reader/mifare_reader.h"
#include "peripheral/peripheral.h"
#include "mqtt_manager/mqtt_manager.h"
#include "device_code/device_code.h"
#include "serial_debug/serial_debug.h"
#include "ibeacon_adv/ibeacon_adv.h"

//FreeRTOS
#if CONFIG_FREERTOS_UNICORE
  #define ARDUINO_RUNNING_CORE 0
#else
  #define ARDUINO_RUNNING_CORE 1
#endif

#define BEACON_UUID "cb10023f-a318-3394-4199-a8730c7c1aec" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
#define BROADCAST_INTERVAL 1000
#define IBEACON_MAJOR 555
#define IBEACON_MINOR dev_code.get_deviceNumber()

boolean net_state = false;

mqtt mqtt;
periph periph;
ble_scanning ble;
flash flash;
mifare mifare;
wifi_manager wifi_manager;
webserver webserver;
dev_code dev_code;
iBeacon ibeacon;

void task_connectivity(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  Serial.println("setup task connectivity");
  
  for (;;)
  {
    net_state = true;
    mqtt.mqtt_loop();
    vTaskDelay(100); // one tick delay (15ms) in between reads for stability
  }
}

void task_scanning(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  ble.ble_scan_init();
  mifare.mifare_init();

  for (;;)
  {
    ble.read_ble();
    ble.check_beacon();
    mifare.mifare_read();
    vTaskDelay(100); // one tick delay (15ms) in between reads for stability
  }
}

void RTOS_initialization(){
#ifdef WIFI_VERSION
  xTaskCreatePinnedToCore(
    task_connectivity
    ,  "task_connectivity"   // A name just for humans
    ,  20000  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  1);
#endif

  xTaskCreatePinnedToCore(
    task_scanning
    ,  "task_scanning"
    ,  5000  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  DEBUG_PRINTLN("device number :" + (String)dev_code.get_deviceNumber());
  delay(1000);
  periph.init();
  periph.notif_powerup();
  flash.flash_init();
  flash.config_all();
  wifi_manager.setup_wifi_ap();
  webserver.webserver_start();
  wifi_manager.setup_wifi_sta();    
  ibeacon.iBeacon_init();
  ibeacon.iBeacon_set(IBEACON_MAJOR,IBEACON_MINOR,BROADCAST_INTERVAL,BEACON_UUID);
  ibeacon.iBeacon_start();
  
  mqtt.mqtt_init();
  mqtt.mqtt_reconnect();

  RTOS_initialization();


}

void loop() {
  // put your main code here, to run repeatedly:
}