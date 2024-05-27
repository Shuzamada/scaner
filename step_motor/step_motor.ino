#include "step_motor.hpp"

  Step_motor motor; 

void setup()
{

}
 
void loop()
{
  for (int i = 0; i < 360; i++)
  {
    motor.ScrollTo(1);
    //delay(200);
  }
  delay(10000);
}
