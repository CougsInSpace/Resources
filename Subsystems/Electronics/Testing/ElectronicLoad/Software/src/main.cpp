#include <mbed.h>

#define HIGH_SHORT (0.0008)
#define HIGH_ON (0.5)
#define MED_SHORT (0.0008)
#define MED_ON (0.05)
#define LOW_ON (0.005)
#define GAIN (48 / 3.3)

/* Dates:
09/08/2019 - Set up repositories and libraries
09/15/2019 - wrote description, outlined variables, outline pins
*/
AnalogIn  currentIn(INPUT_CURRENT);       // ADC
AnalogIn  currentOut(OUTPUT_CURRENT);     // ADC
AnalogIn  voltageIn(INPUT_VOLTAGE);       // ADC
AnalogIn  voltageOut(OUTPUT_VOLTAGE);     // ADC
AnalogOut currentSet(OUTPUT_CURRENT_SET); // DAC

Serial serial(USBTX, USBRX); // UART1 & 2

DigitalOut senseHigh(SENSE_RANGE_LOW); // 0.5 OHM 100 mA = .005W
DigitalOut senseMid(SENSE_RANGE_MED);  // 50 mOHM 1 A = 0.05W
// Shunt-High is 5mOHM and 100 A = 0.5W

/*
 * Description: To write a program that can run the Electronic Load hardware.
 * All variables including but not limited to: A variable knob, Lcd screen, four
 * connectors.
 *
 * Connectors are:
 * Current Conductor - (takes current and sends current back to itself),
 * Input Current Connector - Same as Current Sensor (connects to power
 * transistor via current), UART Connector - accepts signal through
 * microcontroller - !peripheral to the microcontroller! Fan - is thermally
 * connected to power transistor and is controlled by microcontroller via PWM.
 * Voltage Sense Connector - accepts two sources of voltage into itself.
 *
 * Will need at least three outputs to turn on and off the three shunt
 * resistors.
 */
/* Encoder has 2 random pins and buttons have random pins */

void setCurrent(double current) {
  double shunt = 0.0;
  if (current > 1.0) {
    senseHigh = 1;
    senseMid  = 1;
    shunt     = HIGH_SHORT + MED_SHORT + LOW_ON;
  } else if (current > 0.1) {
    senseHigh = 1;
    senseMid  = 0;
    shunt     = HIGH_SHORT + MED_ON + LOW_ON;
  } else {
    senseHigh = 0;
    senseMid  = 0;
    shunt     = HIGH_ON + MED_ON + LOW_ON;
  }

  double voltage = current * shunt;
  voltage        = voltage * GAIN;
  currentSet     = voltage;
}

int main(void) {
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
