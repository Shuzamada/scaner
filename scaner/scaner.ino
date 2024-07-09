#include "step_motor.hpp"
#include <Wire.h>
#include <VL53L0X.h>

Step_motor motor;
VL53L0X sensor;
double degree = 0;

double getAvarage()
{
  double res = 0;
  int count = 0;
  while (count < 2)
  {
    double cur = Serial.parseFloat();
    if (cur < 1000)
    {
      res += cur;
      count++;
    }
  }
  return res / count;
}

void setup()
{
  motor.setStep(400*16);
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
  for (int i = 0; i < 400; i+=1)
  {
    degree += motor.ScrollTo(1);
    Serial.print(0.2);
    Serial.print(" ");
    Serial.print(getAvarage());
    //Serial.print(sensor.readRangeSingleMillimeters());
    Serial.print(" ");
    Serial.println(degree * 16);
  }
  
  delay(1000);
}
