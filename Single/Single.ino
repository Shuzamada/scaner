/* This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>


VL53L0X sensor;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(200000);
}

void loop()
{
  Serial.print(sensor.readRangeSingleMillimeters());
  Serial.print(" ");
  Serial.print(2);
  Serial.print(" ");
  Serial.println(3);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
}
