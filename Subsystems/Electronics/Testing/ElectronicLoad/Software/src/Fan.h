#ifndef _FAN_H_
#define _FAN_H_

#include "Functions.h"
#include <mbed.h>

class Fan : private NonCopyable<Fan> {
private:
  PwmOut pwm;

public:
  Fan(PinName pinPwm, PinName pinTach);
};

#endif