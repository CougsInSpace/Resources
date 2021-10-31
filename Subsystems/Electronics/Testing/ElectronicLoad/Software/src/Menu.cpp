#include "Menu.h"

/**
 * @brief outputs a menu to the lcd displays that allows the user to view
 * important values and allows user to change the current and power values
 *
 * @param pinOutputVoltage pin name for output voltage sensor
 * @param pinOutputCurrent pin name for
 * @param pinInputVoltage pin name for auxiliary voltage sensor
 * @param pinInputCurrent pin name for
 */
Menu::Menu(PinName pinOutputVoltage, PinName pinOutputCurrent,
    PinName pinInputVoltage, PinName pinInputCurrent) :
  outputVoltage(pinOutputVoltage), outputCurrent(pinOutputCurrent), inputVoltage(pinInputVoltage), inputCurrent(pinInputCurrent) {
     int modifyChoice = 0;
  while (true) {
    // will probably need to change niceknob a little to actually work properly
    // with this program
    Knob niceKnob(KNOB_A, KNOB_B); // Initializing the niceKnob Knob class

    ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N,
        LCD_A0); // Initializing the LCD screen
        
        if(niceKnob.isPressed()){
          if(modifyChoice = 2){
            modifyChoice = 0;
          }
          else {
            modifyChoice++;
          }
        }

        //DRAW SELECT DOT ON the line to modify and modify that thing
         if(modifyChoice == 0){
           //choice to mod current
        this->drawSelectDot(0);
         niceKnob.reset();
         setCurrent((niceKnob.getMovement()*.1));
          }

          if(modifyChoice == 1){
            //choice to mod power
        this->drawSelectDot(1);
         niceKnob.reset();
         setCurrentWP(niceKnob.getMovement()*.1);
          }

          if(modifyChoice == 2){
            //choice to mod resistance
        this->drawSelectDot(2);
         niceKnob.reset();
         setCurrentWR(niceKnob.getMovement() % 4);
          }



    // update the display with new values
    updateDisplay();
  }
}

/**
 * @brief Calls all functions to display to  lcd
 */
void Menu::updateDisplay() {
  // first section of the display
  draw(8, 0, getOutputCurrent(), "%5.2fI");
  draw(8, 1, calculatePower(getOutputVoltage(), getOutputCurrent()), "%5.2fW");
  draw(8, 2, calculateResistance(), "%5.2fR");
  // second section of the display
  draw(40, 0, getInputCurrent(), "%5.2fI");
  draw(40, 1, calculatePower(getInputVoltage(), getInputCurrent()), "%5.2fW");
  draw(40, 2, calculateEfficiency(), "%5.2f%");
  
}

/**
 * @brief returns the private variable current
 *
 * @return double current returned
 */
double Menu::getOutputCurrent() {
  return outputCurrent.read() * GAIN_OUTPUT_CURRENT;
}

/**
 * @brief returns the private variable voltage
 *
 * @return double voltage returned
 */
double Menu::getOutputVoltage() {
  return outputVoltage.read_voltage() * GAIN_OUTPUT_VOLTAGE;
}

/**
 * @brief returns the private variable resistance
 *
 * @return double resistance returned
 */
double Menu::getInputCurrent() {
  return inputCurrent.read() * GAIN_INPUT_CURRENT;
}

/**
 * @brief returns the private variable Inputvoltage
 *
 * @return double voltage returned
 */
double Menu::getInputVoltage() {
  return inputVoltage.read() * GAIN_INPUT_VOLTAGE;
}


/**
 * @brief calculates the power using voltage and current 
 * @return double power
 */
double Menu::calculatePower(double voltage, double current) {
  double power = 0.0;

  // calculates the power by multiplying the voltage and the current
  power = getOutputVoltage() * getOutputCurrent();

  return power;
}

/**
 * @brief calculates the resistance using voltage and current
 * @return double resistance
 */
double Menu::calculateResistance() {
  double resistance = 0.0;

  // calculates the power by multiplying the voltage and the current
  resistance = getOutputVoltage() / getOutputCurrent();

  return resistance;
}

/**
 * @brief calculates the efficiency using input power and output power 
 * @return double efficiency
 */
double Menu::calculateEfficiency() {
  double efficiency = 0.0;

  // calculate the efficiency by dividing the output power by the input power;
  efficiency = calculatePower(getOutputVoltage(), getOutputCurrent()) / calculatePower(getInputVoltage(), getInputCurrent());

  return efficiency;
}

/**
 * @brief Display current
 * @param int x and int line for placement in the board, double data, and char DataType
 */
void Menu::draw(int x, int line, double data, char dataType[5]) {
  char display[20];

  sprintf(display, dataType, data);

  lcd.drawstring(x, line, display);
}

void Menu::drawSelectDot(int line){
  lcd.fillcircle(0, line, 3, 1);
}

