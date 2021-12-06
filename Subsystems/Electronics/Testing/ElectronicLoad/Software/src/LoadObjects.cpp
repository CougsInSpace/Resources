#include "LoadObjects.h"

#include "Configuration.h"

QEI        knob(KNOB_A, KNOB_B, NC, KNOB_TICKS, QEI::X4_ENCODING);
ST7565     lcd(LCD_MOSI, LCD_SCK, LCD_CS1_N, LCD_RST_N, LCD_A0);
DigitalOut statusLED(LED1);

Menu menu;

AnalogIn adcOutputCurrent(ADC_OUTPUT_CURRENT);
AnalogIn adcOutputVoltage(ADC_OUTPUT_VOLTAGE);
AnalogIn adcInputCurrent(ADC_INPUT_CURRENT);
AnalogIn adcInputVoltage(ADC_INPUT_VOLTAGE);

double outputCurrent = 0.0;
double outputVoltage = 0.0;
double inputCurrent  = 0.0;
double inputVoltage  = 0.0;

AnalogOut dacOutputCurrent(DAC_OUTPUT_CURRENT_SET);

double targetCurrent = 0.0;

DigitalOut bypassShunt100mA(FET_2);
DigitalOut bypassShunt1A(FET_1);
