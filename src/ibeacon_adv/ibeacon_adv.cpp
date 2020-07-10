#include "ibeacon_adv/ibeacon_adv.h"

BLEAdvertising *pAdvertising;

uint16_t iBeacon_self_minor = 0;

void iBeacon :: iBeacon_init(){
  BLEDevice::init("");
  pAdvertising = BLEDevice::getAdvertising();
}

void iBeacon :: iBeacon_set(uint16_t major, uint16_t minor, uint16_t interval, String uuid) {
  iBeacon_change_endianess(uuid);
  Serial.println("set uuid: " + uuid);
  Serial.println("set major: " + String(major));
  Serial.println("set minor: " + String(minor));
  iBeacon_self_minor = minor;
  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00); // fake Apple 0x004C LSB (ENDIAN_CHANGE_U16!)
  oBeacon.setProximityUUID(BLEUUID(uuid.c_str()));
  oBeacon.setMajor(major);
  oBeacon.setMinor(minor);
  oBeacon.setSignalPower(0xc5);
  
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x06); // General_Discoverable|BR_EDR_NOT_SUPPORTED 0x04
  
  std::string strServiceData = "";
  
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 
  oAdvertisementData.addData(strServiceData);

  String short_name = "CBR"+(String)minor;
  oScanResponseData.setShortName(short_name.c_str());
  
  pAdvertising->setScanResponseData(oScanResponseData);
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  
  pAdvertising->setMinInterval(interval/0.635); // setMinInterval
  pAdvertising->setMaxInterval(interval/0.635); // setMaxInterval
}

void iBeacon :: iBeacon_change_endianess(String& uuid_str)
{
  char temp[2];
  uint8_t n=0;
  uint8_t k = uuid_str.length()-2;
  
  while(n<uuid_str.length()/2)
  {
    if(uuid_str.c_str()[n] == '-')n++;
    if(uuid_str.c_str()[k+1] == '-')k--;
    
    temp[0] = uuid_str[n];
    temp[1] = uuid_str[n+1];
    
    uuid_str[n] = uuid_str[k];
    uuid_str[n+1] = uuid_str[k+1];      
  
    uuid_str[k] = temp[0];
    uuid_str[k+1] = temp[1];
    
    n+=2;
    k-=2;
  }
}

void iBeacon :: iBeacon_start(){
  pAdvertising->start();
  Serial.println("Advertizing started...");
}

void iBeacon :: iBeacon_stop(){
  pAdvertising->stop();
  Serial.println("Advertizing stop...");
}
  
