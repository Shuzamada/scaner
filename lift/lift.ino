#include <Stepper.h>
#include <Wire.h>
#include <VL53L0X.h>
#define MOSFET 12

const int stepsPerRevolution = 2038;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup()
{
  pinMode(MOSFET, OUTPUT);
  //myStepper.step(-stepsPerRevolution);
  myStepper.setSpeed(20);
  Wire.begin();
}

void loop()
{

  
  digitalWrite(MOSFET, HIGH);
  myStepper.step(stepsPerRevolution/26);
  delay(300);
  digitalWrite(MOSFET, LOW);  
  myStepper.step(-stepsPerRevolution/13);
  delay(300);


}
