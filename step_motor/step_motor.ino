#include "step_motor.hpp"
 
Step_motor motor; 
double degree = 0;

void setup()
{
  motor.setStep(12800);
  Serial.begin(9600);
}
 
void loop()
{
  for (int i = 0; i < 800; i+=1)
  {
    degree += motor.ScrollTo(16);
    Serial.println(degree);
  }
  
  delay(5000);
}
