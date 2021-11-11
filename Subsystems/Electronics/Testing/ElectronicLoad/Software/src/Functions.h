#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Knob.h"
#include "LCD.h"
#include "LCDfont.h"
#include "PinNames.h"
#include "QEI.h"
#include "Menu.h"
#include "fan.h"
#include <mbed.h>

#define RES_HIGH_SHORT (0.00082)
#define RES_HIGH_ON (0.510)
#define RES_MED_SHORT (0.00082)
#define RES_MED_ON (0.05)
#define RES_LOW_ON (0.005)
#define GAIN_SHUNT (48.0 / 3.1)
#define GAIN_OUTPUT_CURRENT ((3.1 / 50.0) / 0.005)
#define GAIN_OUTPUT_VOLTAGE (3.1 / (10.0/(10.0 + 30.0)))
#define GAIN_INPUT_CURRENT ((3.1 / 50.0) / 0.005)
#define GAIN_INPUT_VOLTAGE (3.1 / (10.0/(10.0 + 30.0)))

extern AnalogIn  currentIn;
extern AnalogIn  currentOut;
extern AnalogIn  voltageIn;
extern AnalogIn  voltageOut;
extern AnalogOut currentSet;

extern BufferedSerial serial;

extern DigitalOut bypassShunt100mA; // 0 to 100 mA
extern DigitalOut bypassShunt1A;    // 0.1 to 1 A
// 10A range cannot be bypassed: 1 to 10 A

extern DigitalIn knobPushIn;
extern DigitalIn knobChannelA;
extern DigitalIn knobChannelB;

extern AnalogIn buttonPushIn;

//extern ST7565 lcd;

/**
 * @brief Set the Current in amps
 *
 * @param current in amps
 */
void setCurrent(double current);

/**
 * @brief Set the resistance and thus the current
 * Bypasses the proper shunt resistors
 * Constrains current to proper range of 0.0Ω to 10.0Ω
 *
 * @param current through going throught the 4 different resistance setting in amps
 */
void setCurrentWR(double resistance);

/**
 * @brief Set the resistance and thus the current
 * Bypasses the proper shunt resistors
 * Constrains current to proper range of 0.0Ω to 10.0Ω
 *
 * @param current through going throught the 4 different resistance setting in amps
 */
void setCurrentWP(double power);

/**
 * @brief Get the output current
 *
 * @return double current in amps
 */
double getOutputCurrent();

/**
 * @brief Get the output voltage
 *
 * @return double voltage in volts
 */
double getOutputVoltage();

/**
 * @brief Get the input current
 *
 * @return double current in amps
 */
double getCurrentCurrent();

/**
 * @brief Get the input voltage
 *
 * @return double voltage in volts
 */
double getInputVoltage();

/**
 * @brief
 *
 * @return int
 */
int main(void);

int getInputButton();

/**
 * @brief Run all display functions under one name for main display
 *
 * @return double display main screen
 */
//void mainDisplay(double selectedDigit);

/**
 * @brief Display input current on LCD
 *
 * @return input current displayed on the the lcd main screen
 */
//double lcdInputCurrentDisplayed(double selectedDigit);

/**
 * @brief Display output current on LCD
 *
 * @return ouput current displayed on the lcd main screen
 */
//double lcdOutputCurrentDisplayed();

/**
 * @brief Display input voltage
 *
 * @return double input voltage displayed on the lcd main screen
 */
//double lcdInputVoltageDisplayed();

/**
 * @brief Display ouput voltage
 *
 * @return double output voltage displayed on the lcd main screen
 */
//double lcdOutputVoltageDisplayed();

/**
 * @brief Run the main for if the button is pressed
 *
 * @return double display button menu
 */
//double lcdButtonMenu();

/**
 * @brief Run the display of the lcd
 *
 * @return proper menu displayed
 */
//void lcdFunction(double selectedDigit);

/**
 * @brief  Sets current to zero
 *
 */
void init();

#endif /* _FUNCTIONS_H_ */