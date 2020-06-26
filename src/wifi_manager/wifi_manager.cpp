#include "wifi_manager.h"
#include <WiFi.h>

String sta_ssid = "";
String sta_passwrd = "";

String ap_ssid = "";
String ap_passwrd = "";

void wifi_manager :: setup_wifi_ap(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); 
  WiFi.softAP(ap_ssid.c_str(),ap_passwrd.c_str());
  Serial.print("AP mode on ");
  Serial.println(WiFi.softAPIP());
  delay(1000); 
}

void wifi_manager :: setup_wifi_sta(){
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.println(sta_ssid);

  WiFi.begin(sta_ssid.c_str(), sta_passwrd.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

boolean wifi_manager :: wifi_status(){
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }
  else{
    return true;
  }
}
