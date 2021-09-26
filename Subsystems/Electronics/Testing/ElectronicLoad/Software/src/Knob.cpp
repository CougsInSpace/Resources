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

double Knob::getCurrent() {
  current = (current + 0);
  return current;
}

int8_t Knob::reset() {
  encoder.reset();
}

double Knob::modCurrent(){
  // raw tells the amount of movement from the knob
  int raw = 0;
  while(true){
    raw += this->getMovement();

    // changes the current based on the movement from the knob
    current = (raw * 0.1);
  }
}