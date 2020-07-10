#include "mqtt_manager/mqtt_manager.h"

#include <ArduinoJson.h>
#include <WiFi.h>
#include "serial_parser/serial_parser.h"
#include "device_code/device_code.h"
#include "wifi_manager/wifi_manager.h"
#include "serial_debug/serial_debug.h"

#define MQTT_CHECK_INTERVAL 10000
#define TOKEN_LENGTH 6
#define PUBS_TOPIC  dev_code.dev_type() + "rs/" + dev_code.get_deviceNumber()
#define HB_TOPIC    dev_code.dev_type() + "hb"
#define DATA_TOPIC  dev_code.dev_type() + "rc/" + dev_code.get_deviceNumber()
#define HEAD_TOPIC  dev_code.dev_type() + dev_code.get_deviceNumber()
#define SUBS_TOPIC  dev_code.dev_type() + dev_code. get_deviceNumber() //+ "/#"

WiFiClient espClient;
PubSubClient client(espClient);
extern dev_code dev_code;
extern wifi_manager wifi_manager;

String backend_server = "";
String backend_username = "";
String backend_passwrd = "";
String subs_topic = SUBS_TOPIC;
String pubs_topic = PUBS_TOPIC;
String hb_topic = HB_TOPIC;
uint16_t backend_port = 0;
extern boolean net_state;

unsigned long previous = 0;
unsigned long previous_mill = 0;
unsigned long connection_last_millis = 0;

void mqtt :: mqtt_publish(String topic, String payload){
  client.publish(topic.c_str(),payload.c_str());
  DEBUG_PRINTLN("publish data :" + topic + " " + payload);
}

void mqtt_callback(char* topic, byte* payload, unsigned int len){
  extern mqtt mqtt;
  String topic_s = topic;
      
  String payload_s = (char*)payload;
  payload_s = payload_s.substring(0,len);

  String pub = PUBS_TOPIC;
  DEBUG_PRINTLN(payload_s);
 
  if(topic_s.substring(0,9) == HEAD_TOPIC){
    String uuid = parse_string(payload_s, '|', 0);
    String major = parse_string(payload_s, '|', 1);
    String minor = parse_string(payload_s, '|', 2);
    RS232_SEND_APP(uuid+"|"+major+"|"+minor);
  }  
}

void mqtt :: mqtt_init(){
  DEBUG_PRINT("connecting to: ");
  DEBUG_PRINT(backend_server);
  DEBUG_PRINT(backend_port);
  DEBUG_PRINTLN(backend_username);
  client.setServer(backend_server.c_str(), backend_port);
  client.setCallback(mqtt_callback);
}

void mqtt :: mqtt_reconnect(){
  if (!client.connected()){
    // if(!wifi_manager.wifi_status()){
    //   if(millis() - connection_last_millis >= 10000){
    //     wifi_manager.disconnect_wifi();
    //     wifi_manager.setup_wifi_sta();
    //   }
    //   else{
    //     connection_last_millis = millis();
    //   }
    // }
    DEBUG_PRINT("Attempting MQTT connection...");
    // Attempt to connect
    const char* set_username = NULL;
    const char* set_password = NULL;
    String dev_id = (String)dev_code.get_deviceNumber();
    
    if(backend_username != "" && backend_passwrd != ""){
      set_username = backend_username.c_str();
      set_password = backend_passwrd.c_str();
      }
    if (client.connect(dev_id.c_str(), set_username, set_password)) {
      DEBUG_PRINTLN("connected");
      // Subscribe
      DEBUG_PRINTLN("subs topic: " + subs_topic);
      client.subscribe(subs_topic.c_str());
    } 
    else {
      DEBUG_PRINT("failed, rc=");
      DEBUG_PRINT(client.state());
      DEBUG_PRINTLN(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void mqtt :: mqtt_loop(){
    unsigned long current_millis = millis();
    if(current_millis - previous_mill >= MQTT_CHECK_INTERVAL){
        if(!client.loop()){
            net_state = false;
            mqtt_reconnect();
        }
        previous_mill = current_millis;
        DEBUG_PRINTLN("MQTT check: " + (String)client.loop());
    }
}

void mqtt :: handle_newbeacon(String value){
  uint16_t major = parse_string(value,',',0).toInt();
  uint16_t minor = parse_string(value,',',1).toInt();
  String raw_uuid = parse_string(value,',',2);
  String uuid = "";
  // iBeacon_stop();
  // aes_encrypt(raw_uuid,uuid);
  // iBeacon_set(major,minor,1000,uuid);
  // iBeacon_start();
}

void mqtt :: append_beacon(String lastdigit_uuid, uint16_t major, uint16_t minor){
  DynamicJsonDocument json_doc(70);
  json_doc["type"] = "beacon";
  json_doc["uid"] = lastdigit_uuid;
  json_doc["major"] = major;
  json_doc["minor"] = minor;
  String pub_data;
  serializeJson(json_doc,pub_data);
  mqtt_publish(pubs_topic,pub_data);
}

void mqtt :: append_mifare(String uid){
  String payload = "";
  DynamicJsonDocument json_doc(50);
  json_doc["type"] = "mifare";
  json_doc["uid"] = uid;
  String pub_data;
  serializeJson(json_doc,pub_data);
  mqtt_publish(pubs_topic,pub_data);
}
void mqtt :: send_hb(){
  unsigned long current = millis();
  if(current - previous >= 5000){
    previous = current;
    mqtt_publish(hb_topic,(String)dev_code.get_deviceNumber());
  }
}


