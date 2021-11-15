#include "Menu.h"

ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N, LCD_A0);      // Initializing the LCD screen
Knob niceKnob(KNOB_A, KNOB_B); // Initializing the niceKnob Knob class

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

    
    lcd.begin(0x18);
    lcd.clear_display();
    lcd.clear();

    while (true) {

        
        if(niceKnob.isPressed()){
          if(modifyChoice == 2){
            modifyChoice = 0;
          }
          else {
            modifyChoice++;
          }
            modifyChoice = 0;
        }

        // DRAW SELECT DOT ON the line to modify and modify that thing
        if(modifyChoice == 0){
            // choice to mod current
            drawSelectDot(0, 0);
            //niceKnob.reset();
            setCurrent((niceKnob.getMovement()*.1));
        }

        if(modifyChoice == 1){
            // choice to mod power
            drawSelectDot(0, 1);
            //niceKnob.reset();
            setCurrentWP(niceKnob.getMovement()*.1);
        }

        if(modifyChoice == 2){
            // choice to mod resistance
            drawSelectDot(0, 2);
            //niceKnob.reset();
            setCurrentWR(niceKnob.getMovement() % 4);
        }

        
        updateDisplay();
        //lcd.drawstring(0,0,"Hellow");
        lcd.display();

        modifyChoice++;
        wait_us(500e3);
  }
}

/**
 * @brief Calls all functions to display to  lcd
 */
void Menu::updateDisplay() {
    lcd.drawstring(8,0,"I: ");
    lcd.drawstring(8,1,"P: ");
    lcd.drawstring(8,2,"R: ");
    lcd.drawstring(8,3,"V: ");
    lcd.drawstring(56,0,"I: ");
    lcd.drawstring(56,1,"P: ");
    lcd.drawstring(56,2,"E: ");
    // first section of the display
    draw(16, 0, getOutputCurrent(), "%5.2f");
    draw(16, 1, calculatePower(getOutputVoltage(), getOutputCurrent()), "%5.2f");
    draw(16, 2, calculateResistance(), "%5.2f");
    draw(16, 3, getOutputVoltage(), "%5.2f");
    // second section of the display
    draw(72, 0, getCurrentCurrent(), "%5.2f");
    draw(72, 1, calculatePower(getInputVoltage(), getCurrentCurrent()), "%5.2f");
    draw(72, 2, calculateEfficiency(), "%5.2f");
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
  efficiency = calculatePower(getOutputVoltage(), getOutputCurrent()) / calculatePower(getInputVoltage(), getCurrentCurrent());

  return efficiency;
}

/**
 * @brief Display current
 * @param int x and int line for placement in the board, double data, and char DataType
 */
void Menu::draw(int x, int line, double data, char dataType[10]) {
    char buff[20];
    sprintf(buff, dataType, data);
    lcd.drawstring(x, line, buff);
    lcd.display();
}

void Menu::drawSelectDot(int x, int line){
    lcd.drawstring(x,line,"*");
}

