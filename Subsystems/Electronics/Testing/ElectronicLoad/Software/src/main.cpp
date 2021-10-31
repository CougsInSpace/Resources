#include "Functions.h"

void init(); // Sets current = 0

int main(void) {
  while(true){
 

  Fan niceFan(FAN_PWM, FAN_TACH);

 
 Menu niceMenu(ADC_OUTPUT_VOLTAGE, ADC_OUTPUT_CURRENT, ADC_INPUT_VOLTAGE, ADC_INPUT_CURRENT);
 

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