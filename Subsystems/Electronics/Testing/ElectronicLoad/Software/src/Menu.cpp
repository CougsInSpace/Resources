#include "Menu.h"

Menu::Menu(){
    while(true){
        int  selectedDigit = 0;

        //char displayCurrent[20], displayPower[20], displayResistance[20]; 

        Knob niceKnob(KNOB_A, KNOB_B); // Initializing the niceKnob Knob class
        ST7565 lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N, LCD_A0); // Initializing the LCD screen

        // retrives the current from the knob
        setCurrent(niceKnob.getCurrent());
        // sets the power to calculated power value
        setPower(calculatePower());
        // sets the resistance to calculated resistance value
        setResistance(calculateResistance());

        // need to figure out where to get the voltage
        // also need to add in a option to change the power and current using the knob to traverse the screen for options.

        // now since we have the values we now can print to the display
        lcdDisplayCurrent();
        lcdDisplayPower();
        lcdDisplayResistance();
    }
}

/**
 * @brief returns the private variable current
 *
 * @return double current returned
 */
double Menu::getCurrent(){
    return current;
}

/**
 * @brief returns the private variable voltage
 *
 * @return double voltage returned
 */
double Menu::getVoltage(){
    return voltage;
}

/**
 * @brief returns the private variable power
 *
 * @return double power returned
 */
double Menu::getPower(){
    return power;
}

/**
 * @brief returns the private variable resistance
 *
 * @return double resistance returned
 */
double Menu::getResistance(){
    return resistance;
}

/**
 * @brief sets the private data to new current
 */
void Menu::setCurrent(double newCurrent){
    current = newCurrent;
}

/**
 * @brief sets the private data to new voltage
 */
void Menu::setVoltage(double newVoltage){
    voltage = newVoltage;
}

/**
 * @brief sets the private data to new power
 */
void Menu::setPower(double newPower){
    power = newPower;
}
  
  /**
 * @brief sets the private data to new resistance
 */
void Menu::setResistance(double newResistance){
    resistance = newResistance;
}

/**
 * @brief returns the the calculated value for power
 *
 * @return double power returned
 */
double Menu::calculatePower(){
    double power = 0;

    // calculates the power by multiplying the voltage and the current
    power = getVoltage() * getCurrent();

    return power;
}

/**
 * @brief returns the the calculated value for resistance
 *
 * @return double resistance returned
 */
double Menu::calculateResistance(){
    double resistance = 0;

    // calculates the power by multiplying the voltage and the current
    resistance = getVoltage() / getCurrent();

    return resistance;
}

/**
 * @brief Display current
 */
void Menu::lcdDisplayCurrent(){
    char currentDisplay[20];

    sprintf(currentDisplay, "I: %d", getCurrent());

    lcd.drawstring(0, 1, currentDisplay);
}

/**
 * @brief Display power
 */
void Menu::lcdDisplayPower(){
    char powerDisplay[20];

    sprintf(powerDisplay, "P: %d", getPower());

    lcd.drawstring(0, 2, powerDisplay);
}

/**
 * @brief Display resistance
 */
void Menu::lcdDisplayResistance(){
    char resistanceDisplay[20];

    sprintf(resistanceDisplay, "R: %d", getResistance());

    lcd.drawstring(0, 3, resistanceDisplay);
}