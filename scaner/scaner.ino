#include "step_motor.hpp"

#include <AccelStepper.h>

#include <Wire.h>
#include <Stepper.h>
#include <VL53L0X.h>

#define MOSFET 12

Step_motor motor;
VL53L0X sensor;
double degree = 0;
int lower_h = 78;
int h = lower_h;

const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

AccelStepper acc_motor;

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

void spin(int h)
{
  for (int i = 0; i < 400; i+=1)
  {
    Serial.print(h - lower_h + 0.2);
    Serial.print(" ");
    Serial.print(getAvarage());
    //Serial.print(sensor.readRangeSingleMillimeters());
    Serial.print(" ");
    Serial.println(degree * 16);
    degree += motor.ScrollTo(1);
  }
}

void setup()
{
  acc_motor.setMaxSpeed(200000.0);
  acc_motor.setAcceleration(10000.0);
  //motor.setStep(400*16);
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
  if (acc_motor.distanceToGo() == 0)
  {
    acc_motor.setCurrentPosition(0);
    acc_motor.moveTo(6400*4);
    h += 2;
    liftGoTo(h);
  }
  acc_motor.run();
  if (acc_motor.distanceToGo()% (64) == 0)
  {
  degree+=0.9;
  Serial.print(h - lower_h);
  Serial.print(" ");
  Serial.print(getAvarage());
  //Serial.print(1); 
  Serial.print(" ");
  Serial.println(degree); 
  }

}
