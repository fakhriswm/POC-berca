#include "FS_config/FS_config.h"
#include "mqtt_manager/mqtt_manager.h"
#include "wifi_manager/wifi_manager.h"
#include "ble_scanning/ble_scanning.h"
#include "mifare_reader/mifare_reader.h"

String json = "";
const char* json_value = "";
DynamicJsonDocument doc(300);

extern String sta_ssid;
extern String sta_passwrd;
extern String ap_ssid;
extern String ap_passwrd;
extern String backend_server;
extern String backend_username;
extern String backend_passwrd;
extern uint16_t backend_port;
extern float proximity;
extern int ble_timeout;
extern uint8_t detect_counter;
extern String master_key;

bool flash :: flash_init(){
  if(SPIFFS.begin(true)){
    return true;
  }
  else{
    return false;
  }
}

String open_spiff(String file_name){
  json = "";
  File file = SPIFFS.open(file_name);

  if(!file){
    Serial.println("Failed to open file for reading");
    return "";
  }
  Serial.println("File Content:");
 
  while(file.available()){
    json += (char)file.read();
  }
  file.close();
  delay(100);
  return json;
}

void flash :: write_spiff(String file_name, String json){
  File file = SPIFFS.open(file_name, FILE_WRITE);
 
    if(!file){
        Serial.println("There was an error opening the file for writing");
        return;
    }
 
    if(file.print(json)){
        Serial.println("File was written");
    } else {
        Serial.println("File write failed");
    }
 
    file.close();
}

void flash :: set_sta(const char* ssid, const char* passwrd){
  sta_ssid = ssid;
  sta_passwrd = passwrd;
  String raw_json = open_spiff(CONF_STA_FILE);
  deserializeJson(doc,raw_json);
  doc["sta_ssid"] = sta_ssid;
  doc["sta_passwrd"] = sta_passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_STA_FILE,raw_json);
}

void flash :: set_ap(const char* ssid, const char* passwrd){
  ap_ssid = ssid;
  ap_passwrd = passwrd;
  String raw_json = open_spiff(CONF_AP_FILE);
  deserializeJson(doc,raw_json);
  doc["ap_ssid"] = ssid;
  doc["ap_passwrd"] = passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_AP_FILE,raw_json);
}

void flash :: set_backend(const char* backend_server, const char* username, const char* passwrd, uint16_t port){
  backend_server = backend_server;
  backend_username = username;
  backend_passwrd = passwrd;
  backend_port = port;
  String raw_json = open_spiff(CONF_BACKEND_FILE);
  deserializeJson(doc,raw_json);
  doc["backend_server"] = backend_server;
  doc["backend_user"] = username;
  doc["backend_passwrd"] = passwrd;
  doc["backend_port"] = backend_port;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_BACKEND_FILE,raw_json);
}

void flash :: set_scanning(double distance,int timeout, uint8_t counter, String key){
  proximity = distance;
  ble_timeout = timeout;
  detect_counter = counter;
  String raw_json = open_spiff(CONF_BLE_FILE);
  deserializeJson(doc,raw_json);
  doc["proximity"] = proximity;
  doc["ble_timeout"] = ble_timeout;
  doc["detect_counter"] = detect_counter;
  doc["master_key"] = master_key;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_BLE_FILE,raw_json);
}

void flash :: read_sta_conf(){
  String raw_json = open_spiff(CONF_STA_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["sta_ssid"];
  sta_ssid = json_value;
  json_value = doc["sta_passwrd"];
  sta_passwrd = json_value;
}

void flash ::  read_ap_conf(){
  String raw_json = open_spiff(CONF_AP_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["ap_ssid"];
  ap_ssid = json_value;
  json_value = doc["ap_passwrd"];
  ap_passwrd = json_value;
}

void flash :: read_backend_conf(){
  String raw_json = open_spiff(CONF_BACKEND_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["backend_server"];
  backend_server = json_value;
  json_value = doc["backend_user"];
  backend_username = json_value;
  json_value = doc["backend_passwrd"];
  backend_passwrd = json_value;
  backend_port = doc["backend_port"];
}

void flash :: read_scanning_conf(){
  String raw_json = open_spiff(CONF_BLE_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  proximity = doc["proximity"];
  ble_timeout = doc["ble_timeout"];
  detect_counter = doc["detect_counter"];
  json_value = doc["master_key"];
  master_key = json_value;
}

void flash :: config_all(){
  read_backend_conf();
  read_sta_conf(); 
  read_ap_conf(); 
  read_scanning_conf();
}
