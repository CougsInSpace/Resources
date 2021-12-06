#ifndef _LOAD_OBJECTS_H_
#define _LOAD_OBJECTS_H_

#include <mbed.h>

#include "LCD.h"
#include "Menu.h"
#include "QEI.h"

extern QEI        knob;
extern ST7565     lcd;
extern DigitalOut statusLED;
extern Menu       menu;

extern AnalogIn adcOutputCurrent;
extern AnalogIn adcOutputVoltage;
extern AnalogIn adcInputCurrent;
extern AnalogIn adcInputVoltage;

extern double outputCurrent;
extern double outputVoltage;
extern double inputCurrent;
extern double inputVoltage;

extern AnalogOut dacOutputCurrent;

extern double targetCurrent;

extern DigitalOut bypassShunt100mA; // 0 to 100 mA
extern DigitalOut bypassShunt1A;    // 0.1 to 1 A
// 10A range cannot be bypassed: 1 to 10 A

#endif /* _LOAD_OBJECTS_H_ */