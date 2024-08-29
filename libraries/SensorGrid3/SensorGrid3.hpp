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
    uint16_t readSecond();
    uint16_t readThird();
  private:
    SensorGrid3() = delete;
    SensorGrid3(const SensorGrid3& other) = delete;
    SensorGrid3(SensorGrid3&& other) = delete;
    SensorGrid3& operator=(const SensorGrid3& other) = delete;
    SensorGrid3& operator=(SensorGrid3&& other) = delete;
    uint16_t baudRate_ = 9600;
    NeoSWSerial mySerial1;
    NeoSWSerial mySerial2;
    NeoSWSerial mySerial3;
}; 

#endif
