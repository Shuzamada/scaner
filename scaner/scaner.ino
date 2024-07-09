#include "step_motor.hpp"
#include <Wire.h>
#include <Stepper.h>
#include <VL53L0X.h>

#define MOSFET 12

Step_motor motor;
VL53L0X sensor;
double degree = 0;
int lower_h = 85;
int h = lower_h;

const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

double getAvarage()
{
  double res = 0;
  int count = 0;
  while (count < 1)
  {
    double cur = Serial.parseFloat();
    if (cur < 200)
    {
      res += cur;
      count++;
    }
    else
    {
      return 0;
    }
  }
  return res / count;
}

void liftGoTo(int h)
{
  int count = 0;
  while (true)
  {
    int cur_h = sensor.readRangeSingleMillimeters();
    if (cur_h < h)
    {
      digitalWrite(MOSFET, HIGH);
      myStepper.step(stepsPerRevolution/100);
      count = 0;
    }
    else if (cur_h > h)
    {
      digitalWrite(MOSFET, HIGH);
      myStepper.step(-stepsPerRevolution/100);
      count = 0;
    }
    else if (cur_h == h)
    {
      count++;
      if (count == 3)
      {
        return;
      }
    }
    digitalWrite(MOSFET, LOW);
  }
}

void setup()
{
  motor.setStep(400*16);
  Serial.begin(9600);
  Wire.begin();
  pinMode(MOSFET, OUTPUT);
  digitalWrite(MOSFET, LOW);
  myStepper.setSpeed(20);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(50000);
  liftGoTo(h);
}
 
void loop()
{
  delay(100);
  for (int i = 0; i < 400; i+=1)
  {
    degree += motor.ScrollTo(1);
    Serial.print(h - lower_h + 0.2);
    Serial.print(" ");
    Serial.print(getAvarage());
    //Serial.print(sensor.readRangeSingleMillimeters());
    Serial.print(" ");
    Serial.println(degree * 16);
  }
  h += 2;
  liftGoTo(h);
}
