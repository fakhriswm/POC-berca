#ifndef SERIAL_DEBUG_H_
    #define SERIAL_DEBUG_H_

#include <Arduino.h>

    #ifdef DEBUG_ENABLE
        #define DEBUG_PRINTLN(str)	Serial.println(str)
    #else
        #define DEBUG_PRINTLN(str)	{}
    #endif

    #ifdef DEBUG_ENABLE
        #define DEBUG_PRINT(str)	Serial.print(str)
    #else
        #define DEBUG_PRINT(str)	{}
    #endif

    #define RS232_SEND_BEACON(str)  Serial.print("#"+str+"\n")
    #define RS232_SEND_MIFARE(str)  Serial.print("$"+str+"\n")
    #define RS232_SEND_APP(str)  Serial.print("!"+str+"\n")

    #endif /* LIB_SERIAL_LOG_SERIAL_LOG_H_ */



