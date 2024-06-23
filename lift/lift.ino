 
#include <Stepper.h>

const int stepsPerRevolution = 2038;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {

}

void loop() {

  myStepper.setSpeed(10);
  myStepper.step(-stepsPerRevolution/360);
  delay(100);


}
