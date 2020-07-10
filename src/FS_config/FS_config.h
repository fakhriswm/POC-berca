#ifndef FS_CONFIG_H_
  #define FS_CONFIG_H_

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define CONF_STA_FILE "/conf_sta.json"
#define CONF_AP_FILE "/conf_ap.json"
#define CONF_BACKEND_FILE "/conf_mqtt.json"
#define CONF_BLE_FILE "/conf_scanning.json"

class flash{
  public :
    bool flash_init();
    void write_spiff(String file_name, String json);
    void set_sta(const char* ssid, const char* passwrd);
    void set_ap(const char* ssid, const char* passwrd);
    void set_backend(const char* backend_server, const char* username, const char* passwrd, uint16_t port);
    void set_scanning(double distance,int timeout, uint8_t counter, String key);
    void read_sta_conf();
    void read_ap_conf();
    void read_backend_conf();
    void read_scanning_conf();
    void config_all();
};

#endif