#include "Fan.h"

/**
 * @brief Construct a new Fan:: Fan object
 *
 * @param pinPwm Pin name for the fan PWM
 * @param pinTach Pin name for the fan Tachometer
 */
Fan::Fan(PinName pinPwm, PinName pinTach) : pwm(pinPwm) {
  pwm.period(1.0 / 25e3);
  pwm.write(1.0f);
}
