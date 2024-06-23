#ifndef STEP_MOTOR_HPP
#define STEP_MOTOR_HPP

// 1 STEP == 0.9 DEGREE


#include "Arduino.h"

class Step_motor
{
public:
  Step_motor(const uint8_t& PUL = 2,
             const uint8_t& DIR = 3,
             const uint8_t& ENA = 4);
  void setDirection(const bool& new_direction);
  void setStep(const uint32_t& new_step);
  void setDelay(const uint16_t& new_delay);
  double ScrollTo(const uint16_t& steps) const;
  void ScrollToFullRound() const;
private:
  uint8_t PUL = 4;
  uint8_t DIR = 3;
  uint8_t ENA = 2;
  bool direction = 0;
  uint32_t step = 400;
  uint16_t delay_time = 200000000;
};

#endif
