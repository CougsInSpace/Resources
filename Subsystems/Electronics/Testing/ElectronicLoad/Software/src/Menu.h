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

  // calculations
  double calculatePower(double voltage, double current);
  double calculateResistance();
  double calculateEfficiency();

  // display
  void draw(int x, int line, double data, char dataType[10]);
  void drawSelectDot(int x, int line);

};

#endif