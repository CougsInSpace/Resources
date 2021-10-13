#ifndef _Menu_H_
#define _Menu_H_

#include "Functions.h"
#include <mbed.h>

class Menu : private NonCopyable<Menu> {
private:
    AnalogIn outputVoltage;
    AnalogIn outputCurrent;
    AnalogIn inputVoltage;
    AnalogIn inputCurrent;

public:
  Menu(PinName pinOutputVoltage, PinName pinOutputCurrent, PinName pinInputVoltage, PinName pinInputCurrent);

  void updateDisplay();

  // getters
  double getOutputCurrent();
  double getOutputVoltage();
  double getInputCurrent();
  double getInputVoltage();

  // calculations
  double calculatePower(double voltage, double current);
  double calculateResistance();
  double calculateEfficiency();

  // display
  void draw(int x, int line, double data, char dataType[20]);

};

#endif