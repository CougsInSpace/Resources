#include "Functions.h"

 AnalogIn  currentIn(ADC_INPUT_CURRENT);
 AnalogIn  currentOut(ADC_OUTPUT_CURRENT);
 AnalogIn  voltageIn(ADC_INPUT_VOLTAGE);
 AnalogIn  voltageOut(ADC_OUTPUT_VOLTAGE);
 AnalogOut currentSet(DAC_OUTPUT_CURRENT_SET);

 Serial serial(USBTX, USBRX);

 DigitalOut bypassShunt100mA(SENSE_RANGE_HIGH); // 0 to 100 mA
 DigitalOut bypassShunt1A(SENSE_RANGE_MED);     // 0.1 to 1 A
// 10A range cannot be bypassed: 1 to 10 A

 DigitalIn knobPushIn(ENCODER_SW);
 DigitalIn knobChannelA(KNOB_CHANNEL_A);
 DigitalIn knobChannelB(KNOB_CHANNEL_B);

 AnalogIn buttonPushIn(UI_BUTTON1);

 ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_A0, LCD_RST_N, LCD_CS1_N);

/**
 * @brief Set the current
 * Bypasses the proper shunt resistors
 * Constrains current to proper range of 0.0Ω to 10.0Ω
 *
 * @param current in amps
 */
void setCurrent(double current) {
  double shunt = 0.0;
  if (current > 10.0)
    current = 10.0;
  if (current < 0.0)
    current = 0.0;

  if (current > 1.0) {
    bypassShunt100mA = 1;
    bypassShunt1A    = 1;
    shunt            = RES_HIGH_SHORT + RES_MED_SHORT + RES_LOW_ON;
  } else if (current > 0.1) {
    bypassShunt100mA = 1;
    bypassShunt1A    = 0;
    shunt            = RES_HIGH_SHORT + RES_MED_ON + RES_LOW_ON;
  } else {
    bypassShunt100mA = 0;
    bypassShunt1A    = 0;
    shunt            = RES_HIGH_ON + RES_MED_ON + RES_LOW_ON;
  }

  double shuntVoltage = current * shunt;
  shuntVoltage        = shuntVoltage * GAIN_SHUNT;
  currentSet.write((float)shuntVoltage);
}

/**
 * @brief Get the output current
 *
 * @return double current in amps
 */
double getOutputCurrent() {
  return currentOut.read() * GAIN_OUTPUT_CURRENT;
}

/**
 * @brief Get the output voltage
 *
 * @return double voltage in volts
 */
double getOutputVoltage() {
  return voltageOut.read() * GAIN_OUTPUT_VOLTAGE;
}

/**
 * @brief Get the input current
 *
 * @return double current in amps
 */
double getCurrentCurrent() {
  return currentIn.read() * GAIN_INPUT_CURRENT;
}

/**
 * @brief Get the input voltage
 *
 * @return double voltage in volts
 */
double getInputVoltage() {
  return voltageIn.read() * GAIN_INPUT_VOLTAGE;
}

int getInputButton(){
  return buttonPushIn.read();
}


/* The LCD Screen has 4 lines high and 25 characters wide.*/

/* Create LCD Screen code

while(true)
if button (pressed) button menu screen displayed
menu.button (pressed)
else if (knob moved)
menu.knob (moved)
else do nothing*/

/**
 * @brief Run all display functions under one name for main display
 * 
 * @return double display main screen
 */
void mainDisplay(double selectedDigit)
{
  lcdInputCurrentDisplayed(selectedDigit);
  lcdOutputCurrentDisplayed();
  lcdInputVoltageDisplayed();
  lcdOutputVoltageDisplayed();
  lcdFunction(selectedDigit);
}

/**
 * @brief Display input current on LCD
 * 
 * @return input current displayed on the the lcd main screen
 */
double lcdInputCurrentDisplayed(double selectedDigit){
  int  charSelect = 0, currentCurrent = 0, highlightedDigit = 0;
  char buf[20];

  currentCurrent = getCurrentCurrent();

  sprintf(buf, "Input Current: %4.d", currentCurrent);

    lcd.drawstring(1, 1, buf); // Drawstring and then draw the highlighted Character afterwards
    highlightedDigit = currentCurrent * (int)pow(10, selectedDigit) % 10; // Used in drawchar, variable represents the number that is highlighted
    charSelect = 15 + highlightedDigit; // Highlighted Digit value plus 
    lcd.drawchar(charSelect, 1, highlightedDigit, true); //I need a pointer for the 
    return MBED_SUCCESS;

    //My math is wrong here, keep working -- FIXING
    //Must select the proper digit to highlight -- WORKING ON IT NOW
    //-- Potentially (x % selectedDigit);
    //Read what digit it is -- WORK IN PROGRESS
    //invert said digit -- WORK IN PROGRESS
}

/**
 * @brief Display output current on LCD
 * 
 * @return ouput current displayed on the lcd main screen
 */
double lcdOutputCurrentDisplayed()
{
  int x = 0;
  char output_current[20];

  x = getOutputCurrent();

  sprintf(output_current, "Output Current: %d", x);

  lcd.drawstring(1, 2, output_current);
  return MBED_SUCCESS;
}

/**
 * @brief Display input voltage
 * 
 * @return double input voltage displayed on the lcd main screen
 */
double lcdInputVoltageDisplayed()
{
      int x = 0;
  char input_voltage[20];

  x = getInputVoltage();

  sprintf(input_voltage, "Input Voltage: %d", x);

    lcd.drawstring(1, 3, input_voltage);
    return MBED_SUCCESS;
}

/**
 * @brief Display ouput voltage
 * 
 * @return double output voltage displayed on the lcd main screen
 */
double lcdOutputVoltageDisplayed()
{
      int x = 0;
  char output_voltage[20];

  x = getOutputVoltage();

  sprintf(output_voltage, "Output Voltage: %d", x);

    lcd.drawstring(1, 2, output_voltage);
    return MBED_SUCCESS;
}

/**
 * @brief Run the display of the lcd
 * 
 * @return proper menu displayed
 */
void lcdFunction(double selectedDigit){
  int x = 0;
  if (getInputButton() == 1)
  {
    lcdButtonMenu();
    x = 0;
  }
  else
  {
    x = 1;
  }
    while(x == 1){
    mainDisplay(selectedDigit);
  }
}

void init()
{
 setCurrent(0);
}