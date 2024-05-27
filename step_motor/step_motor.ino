#include "step_motor.hpp"

  Step_motor motor; 

void setup()
{
  motor.setStep(12800);
}
 
void loop()
{
  motor.ScrollTo(12800);
  //delay(200);
  delay(5000);
}
