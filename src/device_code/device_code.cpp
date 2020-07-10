#include "device_code/device_code.h"

String dev_code :: get_mac_address(bool delimited){
  uint8_t baseMac[6];
  // Get MAC address for WiFi station
  //esp_read_mac(baseMac, ESP_MAC_WIFI_SOFTAP);
  esp_efuse_mac_get_default(baseMac); //default is wifi sta mac
  char baseMacChr[18] = {0};

  if(delimited)
    sprintf(baseMacChr, "%02x:%02x:%02x:%02x:%02x:%02x", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
  else
    sprintf(baseMacChr, "%02x%02x%02x%02x%02x%02x", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);

  return String(baseMacChr);
}

String dev_code :: dev_id()
{
  return get_mac_address(false).substring(6);
}

String dev_code :: dev_type()
{
  return "gate/";
}

uint16_t dev_code :: get_deviceNumber(){
  uint8_t baseMac[6];
  // Get MAC address for WiFi station
  //esp_read_mac(baseMac, ESP_MAC_WIFI_SOFTAP);
  esp_efuse_mac_get_default(baseMac); //default is wifi sta mac
  return (baseMac[4]<<8)|baseMac[5];
}
