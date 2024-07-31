#include "SensorGrid3.hpp"
#include "Arduino.h"
#include <NeoSWSerial.h>

SensorGrid3::SensorGrid3(const uint8_t& rxPin1 = 5, const uint8_t& txPin1 = 13,
                         const uint8_t& rxPin2 = 6, const uint8_t& txPin2 = 13,
                         const uint8_t& rxPin3 = 7, const uint8_t& txPin3 = 13):
  mySerial1(rxPin1, txPin1),
  mySerial2(rxPin2, txPin2),
  mySerial3(rxPin3, txPin3)
{
}