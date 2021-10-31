#include "Functions.h"

void init(); // Sets current = 0

int main(void) {
  while(true){
  int  selectedDigit = 0, timesPressed = 0, currentCurrent = 0;
  double currentPower = 0.0; // this is calculating the power
  double currentVoltage = 0.0; // this stores voltage for calculation

  Knob niceKnob(KNOB_A, KNOB_B); // Initializing the niceKnob Knob class
  ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N,
      LCD_A0); // Initializing the LCD screen

  void lcdFunction(int selectedDigit); // Runs the LCD screen

  currentCurrent =
      getCurrentCurrent(); // Currently set value for electronic current

  /*
  if (niceKnob.isPressed() == 1) {
    timesPressed++; // Counts amount of times that the button has been pressed
  } else {
    int determineHDValue(
        int selectedDigit, int timesPressed); // Calls digit selection function
    void highlightDigit(int selectedDigit, int currentCurrent,
        ST7565 lcd); // Calls digit highlighting function
  }
  */

  // mods the current based off of knob movement
  niceKnob.modCurrent();
  // prints the current to the lcd display
  lcd.drawchar(0,0, getOutputCurrent());

  // get the output voltage from the board and displays to the lcd
  lcdOutputVoltageDisplayed();

  // calculates the power by multiplying the voltage and current
  currentVoltage = getOutputVoltage();
  currentPower = currentVoltage * getOutputCurrent();
  // prints power to the lcd display
  lcd.drawchar(0,2, currentPower);

  }

}

/**
 * @brief Takes in selectedDigit and timesPressed to determine
 * which digit is supposed to be highlighted. This is achieved
 * by verifying if the digit has gone through the whole integer
 * or not
 *
 * @param selectedDigit
 * @param timesPressed
 * @return int
 */
int determineHDValue(int selectedDigit, int timesPressed) {
  if (selectedDigit >= 3) {
    selectedDigit = selectedDigit +
                    timesPressed; // Determines current value of selectedDigit
  } else {
    selectedDigit = 0; // Resets selectedDigit
  }
  return selectedDigit;
}

/**
 * @brief Takes in selectedDigit, currentCurrent, and lcd to change
 * the selected digit to be a negative image or in this case the
 * method used to highlight this digit
 *
 * @param selectedDigit
 * @param currentCurrent
 * @param lcd
 */
void highlightDigit(int selectedDigit, int currentCurrent, ST7565 lcd) {
  int hdValue = 0, xCoordLocation = 0;

  xCoordLocation = selectedDigit + 16;
  hdValue        = (currentCurrent %
             (10 * (int)pow(
                       10, selectedDigit))); // Reveals the value of the digit
                                             // in the selectedDigit's location

  lcd.drawchar(xCoordLocation, 1, hdValue, true);
}