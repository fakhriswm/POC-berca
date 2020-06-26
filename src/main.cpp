#include <Arduino.h>
#include "notif/notif.h"
#include "ble_scanning/ble_scanning.h"
#include "FS_config/FS_config.h"

flash flash;
notif notif;
ble_scanning ble;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  flash.flash_init();
  flash.config_all();
  ble.ble_scan_init();

}

void loop() {
  // put your main code here, to run repeatedly:
  ble.read_ble();
}