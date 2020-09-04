#include "wifi_manager.h"
#include "serial_debug/serial_debug.h"
#include "webserver_handle/webserver_handle.h"
#include "ibeacon_adv/ibeacon_adv.h"
#include "device_code/device_code.h"

webserver webserver;
extern iBeacon ibeacon;
extern wifi_manager wifi_manager;

String sta_ssid = "";
String sta_passwrd = "";

String ap_ssid = "";
String ap_passwrd = "";

wifi_sta_state_t wifi_sta_state = WIFI_STA_DISCONNECTED;

void wifi_manager :: setup_wifi_ap(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); 
  
  dev_code dev_code;
  String ap_ssid = "TR-" + String(dev_code.get_deviceNumber()); //overwrite ap_ssid
  
  WiFi.softAP(ap_ssid.c_str(),ap_passwrd.c_str());
  DEBUG_PRINT("AP mode on ");
  DEBUG_PRINTLN(WiFi.softAPIP());
  delay(1000); 
}

void wifi_manager :: setup_wifi_sta(){
  WiFi.disconnect();
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINTLN(sta_ssid);
  WiFi.begin(sta_ssid.c_str(), sta_passwrd.c_str());
}

boolean wifi_manager :: wifi_status(){
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }
  else{
    return true;
  }
}

void wifi_manager :: wifi_init(boolean enable_ap){
  if(enable_ap){
    setup_wifi_ap();
    webserver.webserver_start();
  }
  setup_wifi_sta();
  WiFi.onEvent(wifi_event);
}

void wifi_event(WiFiEvent_t event, WiFiEventInfo_t info)
{
  char buff[50];

  switch (event)
  {
    case SYSTEM_EVENT_STA_DISCONNECTED :
    {
      if(wifi_sta_state == WIFI_STA_CONNECTED){
        DEBUG_PRINTLN("wifi event : STA Disconnected");
        wifi_sta_state = WIFI_STA_DISCONNECTED;
      }
    }break;

    case SYSTEM_EVENT_STA_CONNECTED :
    {
      DEBUG_PRINTLN("wifi event : STA Connected");
    }break;

    case SYSTEM_EVENT_STA_GOT_IP :
    {
      sprintf(buff, "wifi event : STA Got IP %s", ip4addr_ntoa(&(info.got_ip.ip_info.ip)));
      DEBUG_PRINTLN(buff);
      wifi_sta_state = WIFI_STA_CONNECTED;
    }break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED :
    {
      Serial.println("AP connected");
      //ibeacon.iBeacon_stop();
      //webserver.webserver_start();
    }break;

    case SYSTEM_EVENT_AP_STADISCONNECTED :
    {
      Serial.println("AP Disconnected");
      //ibeacon.iBeacon_start();
    }break;
  }
}