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

void SensorGrid3::begin(const uint16_t& baudRate = 9600)
{
  baudRate_ = baudRate;
  mySerial3.begin(baudRate_);
  delay(100);
  mySerial2.begin(baudRate_);
  delay(100);
  mySerial1.begin(baudRate_);
}

uint16_t SensorGrid3::readFirst()
{
  mySerial1.begin(baudRate_);
  String str_data = "";
  uint16_t int_data = 0;
  while (true)
  {
    if (mySerial1.available())
    {
      char c = mySerial1.read();
      if (c != '\n')
      {
        str_data = str_data + String(c);
      }
      if (c == '\n')
      {
        int_data = str_data.toInt();
        if (int_data != 0)
        {
          return int_data;
        }
        int_data = 0;
        str_data = "";
      }
    }
  }
}