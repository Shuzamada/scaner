#include <AccelStepper.h>

AccelStepper acc_motor1(AccelStepper::FULL4WIRE,2,3,4);
AccelStepper acc_motor2(AccelStepper::FULL4WIRE,5,6,7);

long dist = 6400*4;

void setup()
{
  acc_motor1.setMaxSpeed(20000.0);
  acc_motor1.setAcceleration(10000.0);
  acc_motor2.setMaxSpeed(20000.0);
  acc_motor2.setAcceleration(10000.0);
  acc_motor2.moveTo(-dist);
}

void loop()
{
  if (acc_motor1.distanceToGo() == 0)
  {
    acc_motor1.setCurrentPosition(0);
    //acc_motor1.moveTo(dist);
    acc_motor2.moveTo(-dist);
    //delay(500);
  }
  if (acc_motor2.distanceToGo() == 0)
  {
    acc_motor2.setCurrentPosition(0);
    acc_motor1.moveTo(-dist);
  }
  acc_motor1.run();
  acc_motor2.run();
}
