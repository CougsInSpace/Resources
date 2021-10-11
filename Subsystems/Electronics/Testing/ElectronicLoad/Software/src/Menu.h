#ifndef _Menu_H_
#define _Menu_H_

#include "Functions.h"
#include <mbed.h>

class Menu : private NonCopyable<Menu> {
private:
  double current, voltage;
  double power, resistance;

public:
  Menu();


  double getCurrent();
  double getVoltage();
  double getPower();
  double getResistance();

  void setCurrent(double newCurrent);
  void setVoltage(double newVoltage);
  void setPower(double newPower);
  void setResistance(double newResistance);

  double calculatePower();
  double calculateResistance();

  void lcdDisplayCurrent();
  void lcdDisplayPower();
  void lcdDisplayResistance();

};

#endif