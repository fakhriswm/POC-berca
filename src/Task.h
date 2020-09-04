#include "main.h"

void IRAM_ATTR onTimer(){
  connectivity_check_timer++;
  DEBUG_PRINTLN(connectivity_check_timer);
  if(wifi_sta_state == WIFI_STA_DISCONNECTED){
    connection_timeout++;
    if(connection_timeout % RECONNECT_INTERVAL == 0){
      time_to_reconnect = true;
    }
    if(connection_timeout >= 180){
      DEBUG_PRINTLN("ESP32 reboot, failed to connect wifi");
      ESP.restart();
    }
  }
  else{
    connection_timeout = 0;
    time_to_reconnect = false;
  }
}

void task_connectivity(void *pvParameters)  // This is a task.
{
  (void) pvParameters; 
  DEBUG_PRINTLN("task_connectivity");
  for (;;)
  {
    if(time_to_reconnect){
      DEBUG_PRINTLN("reconnect wifi");
			periph.timer_pause();
      wifi_manager.setup_wifi_sta();
      time_to_reconnect = false;
      periph.timer_resume();
    }
    if(connectivity_check_timer >= CONNECTIVITY_CHECK_INTERVAL){
      if(wifi_sta_state == WIFI_STA_CONNECTED && !mqtt.mqtt_loop()){
        mqtt.mqtt_reconnect();
      }
      else if(wifi_sta_state == WIFI_STA_CONNECTED && mqtt.mqtt_loop()){
        DEBUG_PRINTLN("connectivity ok");
      }
      DEBUG_PRINTLN("wifi state :" + String(wifi_sta_state));
      DEBUG_PRINTLN("mqtt state : " + String(mqtt.mqtt_loop()));
      DEBUG_PRINTLN("wifi RSSI : " + String(WiFi.RSSI()));
      connectivity_check_timer = 0;
    }
    mqtt.mqtt_loop();
    vTaskDelay(1000/portTICK_RATE_MS); // one tick delay (15ms) in between reads for stability
  }
}

void task_scanning(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;)
  {
    ble.read_ble();
    ble.check_beacon();
    mifare.mifare_read();
    vTaskDelay(10/portTICK_RATE_MS); // one tick delay (15ms) in between reads for stability
  }
}

