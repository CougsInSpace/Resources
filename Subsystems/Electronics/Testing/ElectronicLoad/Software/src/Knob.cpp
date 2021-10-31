#include "Knob.h"
#include "QEI.h"

Knob::Knob(PinName channelA, PinName channelB) :
  encoder(channelA, channelB, NC, 24) {}

int8_t Knob::getMovement() {
  int currentPulse = 0;

  currentPulse = encoder.getPulses();

  // finds the amount of movement from previous position
  int delta = currentPulse - lastPulse;
  lastPulse = currentPulse;
  return delta;
}

int8_t Knob::isPressed() {
  return knobPushIn.read() == 0;
}

int Knob::getPosition() {
  int movement = 0;

  movement = getMovement();

  return (currentPosition + movement);
}

int8_t Knob::reset() {
  encoder.reset();
}
