#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
    stepper.setMaxSpeed(2000.0);
    stepper.setAcceleration(1000.0);
    Serial.begin(9600);
    stepper.moveTo(400*4);
}

void loop()
{
    
    if (stepper.distanceToGo() == 0)
    {
      stepper.moveTo(800*4);
      delay(3000);
    }
    stepper.run();
    Serial.println(stepper.distanceToGo());
    delay(10);
    //stepper.stop();
}
