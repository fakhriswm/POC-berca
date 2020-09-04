#ifndef SRC_MAIN_H_
    #define SRC_MAIN_H_


#include <Arduino.h>
#include <WiFi.h>
#include "ble_scanning/ble_scanning.h"
#include "FS_config/FS_config.h"
#include "wifi_manager/wifi_manager.h"
#include "mifare_reader/mifare_reader.h"
#include "peripheral/peripheral.h"
#include "mqtt_manager/mqtt_manager.h"
#include "device_code/device_code.h"
#include "serial_debug/serial_debug.h"
#include "ibeacon_adv/ibeacon_adv.h"

#define DEBUG_ENABLE
#define BEACON_UUID "cb10023f-a318-3394-4199-a8730c7c1aec" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)
#define BROADCAST_INTERVAL 500
#define IBEACON_MAJOR 555
#define CONNECTIVITY_CHECK_INTERVAL 10
#define IBEACON_MINOR dev_code.get_deviceNumber()
#define RECONNECT_INTERVAL 15
#define TIMER_INTERVAL 1000000 

boolean net_state = false;
boolean time_to_reconnect = false;

unsigned long last = 0;
volatile int connectivity_check_timer = 0;
uint16_t retry_connect_wifi = 0;
volatile int connection_timeout = 0;
boolean idle_mode;

mqtt mqtt;
periph periph;
ble_scanning ble;
flash flash;
mifare mifare;
wifi_manager wifi_manager;

dev_code dev_code;
iBeacon ibeacon;

extern wifi_sta_state_t wifi_sta_state;

void task_connectivity(void *pvParameters);
void task_scanning(void *pvParameters);

#endif