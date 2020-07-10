#include "wifi_manager.h"
#include <WiFi.h>
#include "serial_debug/serial_debug.h"

String sta_ssid = "";
String sta_passwrd = "";

String ap_ssid = "";
String ap_passwrd = "";

void wifi_manager :: setup_wifi_ap(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); 
  WiFi.softAP(ap_ssid.c_str(),ap_passwrd.c_str());
  DEBUG_PRINT("AP mode on ");
  DEBUG_PRINTLN(WiFi.softAPIP());
  delay(1000); 
}

void wifi_manager :: setup_wifi_sta(){
  disconnect_wifi();
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(sta_ssid);
  WiFi.begin(sta_ssid.c_str(), sta_passwrd.c_str());
  uint8_t retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    DEBUG_PRINT(".");
    retry++;
    if (retry>=50)
    {
      setup_wifi_sta();
    }
  }
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINTLN("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());
}

boolean wifi_manager :: wifi_status(){
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }
  else{
    return true;
  }
}

void wifi_manager :: disconnect_wifi(){
  WiFi.disconnect();
}
