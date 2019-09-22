#include <mbed.h>
/* Dates: 
09/08/2019 - Set up repositories and libraries
09/15/2019 - wrote description, outlined variables, outline pins
*/
AnalogIn currentIn(INPUT_CURRENT); //ADC
AnalogIn currentOut(OUTPUT_CURRENT); //ADC
AnalogIn voltageIn(INPUT_VOLTAGE); //ADC
AnalogIn voltageOut(OUTPUT_VOLTAGE); //ADC
AnalogOut currentSet(OUTPUT_CURRENT_SET); //DAC

Serial serial(USBTX, USBRX); //UART1 & 2

DigitalOut senseLo(SENSE_RANGE_LOW);
DigitalOut senseMid(SENSE_RANGE_MED);


/* 
* Description: To write a program that can run the Electronic Load hardware.
* All variables including but not limited to: A variable knob, Lcd screen, four connectors.
*
* Connectors are: 
* Current Conductor - (takes current and sends current back to itself), 
* Input Current Connector - Same as Current Sensor (connects to power transistor via current),
* UART Connector - accepts signal through microcontroller - !peripheral to the microcontroller!
* Fan - is thermally connected to power transistor and is controlled by microcontroller via PWM.
* Voltage Sense Connector - accepts two sources of voltage into itself.
*
* Will need at least three outputs to turn on and off the three shunt resistors.
*/
/* Encoder has 2 random pins and buttons have random pins */

int main(void) {
  currentIn.read(); //ADC
  currentOut.read(); //DAC
  voltageIn.read(); //ADC
  voltageOut.read(); //ADC
  currentSet.write(); //DAC
  
  senseLo.write(); 
  senseMid.write(); 



// cc = 0.0; // Current Conductor
// icc = 0.0; // Input Current Connector
// uart = 0.0; // UART Connector
// fan = 0.0; // Thermally connected fan for cooling
// vsc = 0.0; // Voltage Sense Connector
// 
// sr1 = 0.0; // Shunt Resistor 1
// sr2 = 0.0; // Shunt Resistor 2
// sr3 = 0.0; // Shunt Resistor 3
  return MBED_SUCCESS;
}
