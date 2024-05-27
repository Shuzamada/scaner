#ifndef STEP_MOTOR_HPP
#define STEP_MOTOR_HPP

#include "Arduino.h"

class Step_motor
{
public:
  Step_motor();
  void setStep(const uint32_t& new_step);
  void setDelay(const uint16_t& new_delay);
  void ScrollTo(const uint16_t& degree) const;
  void ScrollToFullRound() const;
private:
  uint8_t PUL = 4;
  uint8_t DIR = 3;
  uint8_t ENA = 2;
  uint32_t step = 12800;
  uint16_t delay_time = 0;
};

#endif
