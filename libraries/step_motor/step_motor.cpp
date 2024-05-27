#include "step_motor.hpp"
#include "Arduino.h"

Step_motor::Step_motor()
{
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}

void Step_motor::setDelay(const uint16_t& new_delay)
{
  delay_time = new_delay;
}
void Step_motor::setStep(const uint32_t& new_step)
{
  step = new_step;
}
void Step_motor::ScrollTo(const uint16_t& degree) const
{
  for (int i=0; i < (step * degree / 360) + 1; i++)
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(delay);
    digitalWrite(PUL,LOW);
    delayMicroseconds(delay);
  }
}
void Step_motor::ScrollToFullRound() const
{
  ScrollTo(360);
}