#ifndef SENSORGRID3_HPP
#define SENSORGRID3_HPP

#include "Arduino.h"
#include <NeoSWSerial.h>

class SensorGrid3
{ 
  public:
    SensorGrid3(const uint8_t& rxPin1 = 5, const uint8_t& txPin1 = 13,
                const uint8_t& rxPin2 = 6, const uint8_t& txPin2 = 13,
                const uint8_t& rxPin3 = 7, const uint8_t& txPin3 = 13);
    void begin(const uint16_t& baudRate = 9600);
    uint16_t readFirst();
  private:
    uint16_t baudRate_ = 9600;
    NeoSWSerial mySerial1;
    NeoSWSerial mySerial2;
    NeoSWSerial mySerial3;
}; 

#endif
