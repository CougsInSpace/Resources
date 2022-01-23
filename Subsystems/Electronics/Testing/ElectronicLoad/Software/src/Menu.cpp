#include "Menu.h"

#include "LoadObjects.h"

Menu::Menu() {}

void Menu::update(int knobMovement) {
  switch (currentPage) {
    case Page::VALUES: {
      // If cursor is not selected, move cursor
      // if cursor is selected, adjust value
      targetCurrent += 0.001 * knobMovement;
      if (targetCurrent > 10.0)
        targetCurrent = 10.0;
      if (targetCurrent < 0.0)
        targetCurrent = 0.0;

    } break;
  }
}

void Menu::render() {
  lcd.clear();
  switch (currentPage) {
    case Page::VALUES: {
      lcd.drawstring(8, 0, "I: ");
      lcd.drawstring(8, 1, "P: ");
      lcd.drawstring(8, 2, "R: ");
      lcd.drawstring(8, 3, "V: ");
      lcd.drawstring(56, 0, "I: ");
      lcd.drawstring(56, 1, "P: ");
      lcd.drawstring(56, 2, "E: ");
      double outputPower      = outputCurrent * outputVoltage;
      double inputPower       = inputCurrent * inputVoltage;
      double outputResistance = outputVoltage / outputCurrent;
      double efficiency       = outputCurrent * inputCurrent * 100.0;
      drawNumber(16, 0, "%5.2f", outputCurrent);
      drawNumber(16, 1, "%5.2f", outputPower);
      drawNumber(16, 2, "%5.2f", outputResistance);
      drawNumber(16, 3, "%5.2f", outputVoltage);
      drawNumber(72, 0, "%5.4f", inputCurrent);
      drawNumber(72, 1, "%5.2f", inputPower);
      drawNumber(72, 2, "%5.2f", efficiency);
      // TODO cursor
    } break;
  }
  lcd.display();
}

void Menu::drawNumber(
    const int x, const int line, const char * format, const double data) {
  char buf[20];
  sprintf(buf, format, data);
  lcd.drawstring(x, line, buf);
}
