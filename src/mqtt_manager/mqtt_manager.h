#ifndef MQTT_MANAGER_H_
  #define MQTT_MANAGER_H_

#include <Arduino.h>
#include <PubSubClient.h>

void mqtt_callback(char* topic, byte* payload, unsigned int len);

class mqtt{
  public :
    void mqtt_init();
    void mqtt_publish(String topic, String payload);
    void handle_newbeacon(String value);
    void mqtt_reconnect();
    boolean mqtt_loop();
    void append_beacon(String lastdigit_uuid, uint16_t major, uint16_t minor);
    void append_mifare(String uid);
    void send_hb();
};

#endif
