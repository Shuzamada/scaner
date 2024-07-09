#include <Stepper.h>
#include <Wire.h>
#include <VL53L0X.h>
#define MOSFET 12

const int stepsPerRevolution = 2038;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
VL53L0X sensor;

void liftGoTo(int h)
{
  while (true)
  {
    int cur_h = sensor.readRangeSingleMillimeters();
    if (cur_h < h)
    {
      digitalWrite(MOSFET, HIGH);
      myStepper.step(stepsPerRevolution/5);
    }
    else if (cur_h > h)
    {
      digitalWrite(MOSFET, HIGH);
      myStepper.step(-stepsPerRevolution/13);
    }
    else if (cur_h == h)
    {
      Serial.print("get");
      Serial.println(cur_h);
      return;
    }
    digitalWrite(MOSFET, LOW);
    Serial.println(cur_h);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(MOSFET, OUTPUT);
  digitalWrite(MOSFET, LOW);
  myStepper.setSpeed(20);
   myStepper.step(-stepsPerRevolution);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.setMeasurementTimingBudget(50000);
  liftGoTo(100);
  liftGoTo(60);
  liftGoTo(75);
  liftGoTo(50);
}

void loop()
{

  
  digitalWrite(MOSFET, HIGH);
  myStepper.step(stepsPerRevolution/13);
  delay(300);
  myStepper.step(-stepsPerRevolution/13);
  Serial.println(sensor.readRangeSingleMillimeters());

  digitalWrite(MOSFET, LOW);
  delay(300);
}
