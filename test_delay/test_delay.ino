#include <AccelStepper.h>
#include <Wire.h>
#include <VL53L0X.h>

AccelStepper stepper; 
VL53L0X sensor;
double degree = 0;
void setup()
{  
    stepper.setMaxSpeed(2000.0);
    stepper.setAcceleration(1000.0);
    Serial.begin(9600);
    Serial.begin(9600);
    Wire.begin();
    sensor.setTimeout(500);
    if (!sensor.init())
    {
      Serial.println("Failed to detect and initialize sensor!");
      //while (1) {}
    }
    sensor.setMeasurementTimingBudget(1000);
}

void loop()
{
    
    if (stepper.distanceToGo() == 0)
    {
      stepper.setCurrentPosition(0);
      stepper.moveTo(6400*4);
      delay(3000);
    }
    stepper.run();
    //Serial.print(stepper.distanceToGo());
    //Serial.print(" ");
    if (stepper.distanceToGo()% (64) == 0)
    {
    //Serial.print(stepper.distanceToGo());
    degree+=0.9;
    Serial.print(0.2);
    Serial.print(" ");
    Serial.print(sensor.readRangeSingleMillimeters());   
    Serial.print(" ");
    //Serial.println((stepper.distanceToGo() * 400 / (6400*4)) * 0.9);
    Serial.println(degree);
    
    }
    //stepper.stop();
}
