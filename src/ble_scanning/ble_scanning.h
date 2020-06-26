#ifndef BLE_SCANNING_H_
  #define BLE_SCANNING_H_

#include <Arduino.h>

#define NUMBEROFBEACON 50
class ble_scanning {
 public :
  void ble_scan_init();
  void read_ble();
  double calculateDistance(double rssi);
  void check_beacon();
};

#endif