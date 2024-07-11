//#include "step_motor.hpp"
//#include <AccelStepper.h>
//Step_motor motor; 
//double degree = 0;
//
//void setup()
//{
//  motor.setStep(12800);
//  //Serial.begin(9600);
//}
// 
//void loop()
//{
//  for (int i = 0; i < 800; i+=1)
//  {
//    degree += motor.ScrollTo(160000);
//    //Serial.println(degree);
//  }
//  
//  delay(5000);
//}

// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(1000000);
  stepper.setAcceleration(200000);
  stepper.moveTo(400);
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
      stepper.currentPosition() = 100;

    stepper.run();
}
