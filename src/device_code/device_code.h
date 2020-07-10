#ifndef DEVICE_CODE_H_
  #define DEVICE_CODE_H_

#include <Arduino.h>

class dev_code{
  public :
    String get_mac_address(bool delimited);
    String dev_id();
    String dev_type();
    uint16_t get_deviceNumber();
};

#endif
