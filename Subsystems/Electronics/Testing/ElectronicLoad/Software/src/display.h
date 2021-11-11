#ifndef _Display_H_
#define _Display_H_

#include "Functions.h"
#include <mbed.h>




class Display : private NonCopyable<Display> {
private:
    AnalogIn outputVoltage;
    AnalogIn outputCurrent;
    AnalogIn inputVoltage;
    AnalogIn inputCurrent;

public:
  Display(PinName pinOutputVoltage, PinName pinOutputCurrent, PinName pinInputVoltage, PinName pinInputCurrent);

  // calculations
  double calculatePower(double voltage, double current);
  double calculateResistance();
  double calculateEfficiency();


  // display
  void drawDisplay();

};

#endif