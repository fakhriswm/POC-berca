#ifndef SERIAL_DEBUG_H_
#define SERIAL_DEBUG_H_

#include <Arduino.h>

#ifdef DEBUG_ENABLE
#define DEBUG_PRINTLN(str)	Serial2.println(str)
#else
#define DEBUG_PRINTLN(str)	{}
#endif

#ifdef DEBUG_ENABLE
#define DEBUG_PRINT(str)	Serial2.print(str)
#else
#define DEBUG_PRINT(str)	{}
#endif

#define RS232_SEND_BEACON(str)     Serial2.print("$"+str+"\n")
#define RS232_SEND_MIFARE(str)     Serial2.print("#"+str+"\n")

#endif