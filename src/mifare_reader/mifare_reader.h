#ifndef MIFARE_READER_H_
  #define MIFARE_READER_H_

#include <Arduino.h>

#define INTERVAL_ 1000

#define RST_PIN    22          // Configurable, see typical pin layout above
#define SS_PIN     21         // Configurable, see typical pin layout above

class mifare{
  public :
    void mifare_init();
    void mifare_read();
    String read_rfid();
    int readBlock(int blockNumber, byte arrayAddress[]);
};

#endif
