#include "ble_scanning/ble_scanning.h"
#include "notif/notif.h"

extern notif notif;

typedef struct BLE{
    int major;
    int minor;
    int rss;
    int counter;
    unsigned long time;
    bool flag_detect;
  }BLE_t;

BLE_t b[NUMBEROFBEACON];

char rawData[26];
char uuid[16];
uint8_t i = 0;
float proximity = 0;
int ble_timeout = 0; //in millisecond
uint8_t detect_counter = 0;

extern uint16_t iBeacon_self_minor;


void ble_scanning :: ble_scan_init(){
  Serial2.begin(115200);
  delay(100);
}

void ble_scanning :: read_ble(){
  if(Serial2.available()){
  char in=Serial2.read();
  if(in=='B'){
   rawData[0]=in;
   uint8_t sum = 0;
   String uuidf = "";
   char uuid_lastdigit[10];
   
   for(i=1;i<=26;i++)
   {
    rawData[i]=Serial2.read();
    if(i>=2 && i<=24)sum+=rawData[i];
   }
   delay(10);
   if(rawData[0] == 'B' && rawData[1] == 'T' && rawData[26]=='\n' && sum==rawData[25] && sum!=0){
    for(i=0;i<=15;i++)
    {
        uuid[i]=rawData[i+2];
        uuidf+=uuid[i];
    }
    sprintf(uuid_lastdigit,"%02x%02x",rawData[16],rawData[17]);
            
    uint16_t cardMajor=rawData[18];
    cardMajor=(cardMajor<<8) + rawData[19];

    uint16_t cardMinor=rawData[20];
    cardMinor=(cardMinor<<8) + rawData[21];
    Serial.print((String)cardMinor+",");
    int rssi = rawData[22];
    rssi = ~rssi;
    rssi = rssi+B01;
    rssi = rssi & 0xff;
    rssi = ~rssi;

    double rss = rssi;
    double distance = calculateDistance(rss);
    Serial.println((String)distance+","+(String)rssi);
    if(distance <= proximity /*&& cardMinor != iBeacon_self_minor*/){
      for(int k=0; k<NUMBEROFBEACON; k++){
               if(cardMinor == b[k].minor){
                b[k].time = millis();
                b[k].rss = rssi;
                b[k].counter += 1;
                Serial.print("Existing :"); Serial.print(b[k].minor); Serial.print("-"); Serial.print(b[k].counter); Serial.print("-"); Serial.println(b[k].time);
                if(b[k].counter == detect_counter && b[k].flag_detect == false){
                      b[k].flag_detect = true;
                      b[k].time = millis();
                      Serial.println("access grant!");
                      notif.notif_accessgrant();
                   }
                return;
              }
            }
      for(int j=0; j<NUMBEROFBEACON; j++){
              if(b[j].minor == NULL){
                b[j].major = cardMajor;
                b[j].minor = cardMinor;
                b[j].time = millis();
                b[j].rss = rssi;
                b[j].counter = 1;
                b[j].flag_detect = false;
                Serial.print("append success ->"); Serial.println(b[j].minor);
                return;
            }
          }
        }   
      }
    }
  }
}

double ble_scanning :: calculateDistance(double rssi) {
    float txPower = -59.0;
    if (rssi == 0) {
        return -1.0; // if we cannot determine distance, return -1.
    }
    double ratio = rssi * 1.0 / txPower;

    if (ratio < 1.0) {
        return pow(ratio, 10);
    } 
    else {
        double accuracy = (0.89976) * pow(ratio, 7.7095) + 0.111;
        return accuracy;
    }
}

void ble_scanning :: check_beacon(){
  unsigned long current_millis = millis();
    for(int j=0; j<NUMBEROFBEACON; j++){
     if(current_millis-b[j].time>ble_timeout && b[j].minor!=NULL){
        Serial.print(b[j].minor); Serial.print("-"); Serial.println("out");
        b[j].major = 0;
        b[j].minor = 0;
        b[j].rss = 0;
        b[j].time = 0;
        b[j].counter = 0;
        b[j].flag_detect = false;
     }
     else if( b[j].minor!=NULL){
        Serial.print(b[j].minor); Serial.print(" inrange with rssi = "); Serial.println(b[j].rss);
     }
    }
}
