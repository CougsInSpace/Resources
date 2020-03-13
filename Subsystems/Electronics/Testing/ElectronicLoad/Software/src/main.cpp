#include "Functions.h"

void init();
void lcdFunction(int selectedDigit);

int main(void)
{
  int selectedDigit = 0, timesPressed = 0, currentCurrent = 0;
  Knob niceKnob = Knob(KNOB_CHANNEL_A, KNOB_CHANNEL_B);
  ST7565 lcd = ST7565(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N, LCD_A0);

  currentCurrent = getCurrentCurrent();

  if (niceKnob.isPressed() == 1)
  {
    timesPressed++;
  }
  else
  {
    int determineHDValue(int selectedDigit, int timesPressed);
    void highlightDigit(int selectedDigit, int currentCurrent, ST7565 lcd);
  }
  

}

int determineHDValue(int selectedDigit, int timesPressed)
{
  if (selectedDigit >= 5)
  {
    selectedDigit = selectedDigit + timesPressed;
  }

  selectedDigit = selectedDigit + timesPressed;
  return selectedDigit;
}


void highlightDigit(int selectedDigit, int currentCurrent, ST7565 lcd){
int hdValue = 0, xCoordLocation = 0;

xCoordLocation = selectedDigit + 16;
hdValue = (currentCurrent / pow(10, selectedDigit)); // Probably doesn't reveal the actual digit's value

lcd.drawchar(xCoordLocation, 1, hdValue, true);
}