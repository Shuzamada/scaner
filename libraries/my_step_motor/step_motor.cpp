#include "step_motor.hpp"
#include "Arduino.h"

// 1 STEP == 0.9 DEGREE

Step_motor::Step_motor(const uint8_t& PUL = 2,
                       const uint8_t& DIR = 3,
                       const uint8_t& ENA = 4)
{
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void Step_motor::setDirection(const bool& new_direction)
{
  direction = new_direction;
}

void Step_motor::setDelay(const uint16_t& new_delay)
{
  delay_time = new_delay;
}
void Step_motor::setStep(const uint32_t& new_step)
{
  step = new_step;
}

double Step_motor::ScrollTo(const uint16_t& steps) const
{
  for (int i=0; i < steps; i++)
  {
    digitalWrite(DIR, direction);
    digitalWrite(ENA, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(delay_time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(delay_time);
  }
  return 0.9 * steps * 400 / step;
}

void Step_motor::ScrollToFullRound() const
{
  ScrollTo(step);
}