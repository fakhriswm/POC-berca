#ifndef IBEACON_ADV_H_
  #define IBEACON_ADV_H_

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEBeacon.h>

class iBeacon{
  public :
    void iBeacon_init();
    void iBeacon_set(uint16_t major, uint16_t minor, uint16_t interval, String uuid);
    void iBeacon_start();
    void iBeacon_stop();
    void iBeacon_change_endianess(String& uuid_str);
};

#endif