#include <Arduino.h>
#include "notif/notif.h"
#include "ble_scanning/ble_scanning.h"
#include "FS_config/FS_config.h"
#include "wifi_manager/wifi_manager.h"
#include "webserver_handle/webserver_handle.h"
#include "serial_debug/serial_debug.h"

notif notif;
ble_scanning ble;
flash flash;
wifi_manager wifi_manager;
webserver webserver;

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
  delay(1000);
  notif.notif_init();
  flash.flash_init();
  flash.config_all();
  wifi_manager.setup_wifi_ap();
  webserver.webserver_start();
  ble.ble_scan_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  ble.read_ble();
  ble.check_beacon();
}