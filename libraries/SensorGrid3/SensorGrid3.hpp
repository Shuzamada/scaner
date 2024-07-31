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
  private:
    NeoSWSerial mySerial1;
    NeoSWSerial mySerial2;
    NeoSWSerial mySerial3;
}; 

#endif
