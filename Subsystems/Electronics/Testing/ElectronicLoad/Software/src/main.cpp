#include <mbed.h>

<<<<<<< Updated upstream
=======
#define RES_HIGH_SHORT (0.0008)
#define RES_HIGH_ON (0.5)
#define RES_MED_SHORT (0.0008)
#define RES_MED_ON (0.05)
#define RES_LOW_ON (0.005)
#define GAIN_SHUNT (48.0 / 5.0)
#define GAIN_OUTPUT_CURRENT ((5.0 / 50.0) / 0.005)
#define GAIN_OUTPUT_VOLTAGE (5.0)
#define GAIN_INPUT_CURRENT ((5.0 / 50.0) / 0.005)
#define GAIN_INPUT_VOLTAGE (5.0)

AnalogIn  currentIn(ADC_INPUT_CURRENT);
AnalogIn  currentOut(ADC_OUTPUT_CURRENT);
AnalogIn  voltageIn(ADC_INPUT_VOLTAGE);
AnalogIn  voltageOut(ADC_OUTPUT_VOLTAGE);
AnalogOut currentSet(DAC_OUTPUT_CURRENT_SET);

Serial serial(USBTX, USBRX);

DigitalOut bypassShunt100mA(SENSE_RANGE_HIGH); // 0 to 100 mA
DigitalOut bypassShunt1A(SENSE_RANGE_MED);     // 0.1 to 1 A
// 10A range cannot be bypassed: 1 to 10 A

DigitalIn knobPushIn(Encoder_SW);

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

double knobPushIn(){
  return Encoder_SW.read()
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
double getInputCurrent() {
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
>>>>>>> Stashed changes

int main(void) {

  return MBED_SUCCESS;
}
