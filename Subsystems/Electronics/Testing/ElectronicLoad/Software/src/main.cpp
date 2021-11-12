// #include "Functions.h"

// void init(); // Sets current = 0

// int main(void) {
//   while(true){
//     Fan niceFan(FAN_PWM, FAN_TACH);
//     Menu niceMenu(ADC_OUTPUT_VOLTAGE, ADC_OUTPUT_CURRENT, ADC_INPUT_VOLTAGE,
//     ADC_INPUT_CURRENT);
//   }
// }

// #include "Fan.h"
// #include "Functions.h"
// #include "LCD.h"
// #include "QEI.h"
// #include "display.h"

#include "C12832/C12832.h"

#include <mbed.h>

// extern AnalogIn  voltageOut;
// extern AnalogIn currentOut;
// extern AnalogIn voltageIn;
// extern AnalogIn currentIn;

// AnalogIn  voltageOut(ADC_OUTPUT_VOLTAGE);
// AnalogIn  currentOut(ADC_OUTPUT_CURRENT);
// AnalogIn  voltageIn(ADC_INPUT_VOLTAGE);
// AnalogIn  currentIn(ADC_INPUT_CURRENT);

int main(void) {
  C12832 lcd(LCD_MOSI, LCD_SCK, LCD_RST_N, LCD_A0, LCD_CS1_N);
  lcd.set_contrast(0x18);
  lcd.line(0, 0, 127, 32,1);
  lcd.line(127, 0, 0, 32,1);
  lcd.character(0, 0, 'F');
  lcd.copy_to_lcd();

  // ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N,
  //       LCD_A0); // Initializing the LCD screen
  DigitalOut status(LED1);
  // QEI niceKnob(KNOB_A, KNOB_B, NC, 24, QEI::X4_ENCODING);
  // Fan niceFan(FAN_PWM, FAN_TACH);

  // float outputVoltage, inputCurrent, outputPower, inputVoltage;

  // Display niceDisplay(ADC_OUTPUT_VOLTAGE, ADC_OUTPUT_CURRENT,
  // ADC_INPUT_VOLTAGE, ADC_INPUT_CURRENT);

  // lcd.begin(0x18);
  // lcd.display();
  // wait_us(1e6);
  // lcd.clear();
  // lcd.drawstring(1, 1, "Hello World!");
  // lcd.display();

  // BufferedSerial serial(USBTX, USBRX, 9600);

  while (true) {
    //   outputVoltage = voltageOut.read() * GAIN_OUTPUT_VOLTAGE;
    //   inputVoltage = voltageIn.read() * GAIN_INPUT_VOLTAGE;
    //   inputCurrent = currentIn.read() * GAIN_INPUT_CURRENT;

    //   //outputPower = outputVoltage * outputCurrent;
    //   printf("Knob: %d\r\n", niceKnob.getPulses());
    //   printf("AC Voltage: %.4f\r\n", outputVoltage);
    //   printf("Aux Voltage: %.4f\r\n", inputVoltage);
    //   printf("Aux Current: %.4f\r\n", inputCurrent);
    //   printf("Aux Current data: %.4f\r\n", currentIn.read());
    //   printf("AC Power: %.4f\r\n", outputPower);

    //   // char buf[128];
    //   // int  pulses = niceKnob.getPulses();
    //   // int n = snprintf(buf, 128, "Knob: %d\r\n", pulses);
    //   // serial.write(buf, n);

    status = !status;
    wait_us(500e3);
  }
}

// /**
//  * @brief Takes in selectedDigit and timesPressed to determine
//  * which digit is supposed to be highlighted. This is achieved
//  * by verifying if the digit has gone through the whole integer
//  * or not
//  *
//  * @param selectedDigit
//  * @param timesPressed
//  * @return int
//  */
// int determineHDValue(int selectedDigit, int timesPressed) {
//   if (selectedDigit >= 3) {
//     selectedDigit = selectedDigit +
//                     timesPressed; // Determines current value of
//                     selectedDigit
//   } else {
//     selectedDigit = 0; // Resets selectedDigit
//   }
//   return selectedDigit;
// }

// /**
//  * @brief Takes in selectedDigit, currentCurrent, and lcd to change
//  * the selected digit to be a negative image or in this case the
//  * method used to highlight this digit
//  *
//  * @param selectedDigit
//  * @param currentCurrent
//  * @param lcd
//  */
// void highlightDigit(int selectedDigit, int currentCurrent, ST7565 lcd) {
//   int hdValue = 0, xCoordLocation = 0;

//   xCoordLocation = selectedDigit + 16;
//   hdValue        = (currentCurrent %
//              (10 * (int)pow(
//                        10, selectedDigit))); // Reveals the value of the
//                        digit
//                                              // in the selectedDigit's
//                                              location

//   lcd.drawchar(xCoordLocation, 1, hdValue, true);
// }