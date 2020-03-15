#include "Knob.h"
#include "QEI.h"

Knob::Knob(PinName channelA, PinName channelB) :
  encoder(channelA, channelB, NC, 24) {}

int8_t Knob::getMovement() {
  int currentPulse = 0;

  currentPulse = encoder.getPulses();

  if (lastPulse != currentPulse) {
    return (currentPulse - lastPulse);
  } else {
    return 0;
  }
}

int8_t Knob::isPressed() {
  return knobPushIn.read() == 0;
}

int Knob::getPosition() {
  int movement = 0;

  movement = getMovement();

  return (currentPosition + movement);
}

int Knob::getCurrent() {
  current = (current + 0);
  return current;
}

int8_t Knob::reset() {
  encoder.reset();
}