#ifndef _KNOB_H_
#define _KNOB_H_

#include "Functions.h"
#include "QEI.h"

class Knob: private NonCopyable<Knob> {
private:
  QEI encoder;

  int lastPulse = 0, currentPosition = 0, current = 0.1;

public:
  Knob(PinName channelA, PinName channelB);

  int8_t getMovement();

  int8_t isPressed();

  int getPosition();

  int8_t reset();

  // modify current
  void modCurrent();
  
};

#endif /* _KNOB_H_ */