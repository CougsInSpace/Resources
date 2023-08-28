#include <mbed.h>

#include "Configuration.h"
#include "LoadObjects.h"

void controlLoop() {
  // Measure sensors
  outputCurrent = adcOutputCurrent.read() * GAIN_OUTPUT_CURRENT;
  outputVoltage = adcOutputVoltage.read() * GAIN_OUTPUT_VOLTAGE;
  inputCurrent  = adcInputCurrent.read() * GAIN_INPUT_CURRENT;
  inputVoltage  = adcInputVoltage.read() * GAIN_INPUT_VOLTAGE;

  // Adjust DAC
  // TODO allow other modes
  // TODO add feedback from sense resistor
  double current = targetCurrent;

  double shunt = 0.0;
  if (current > 10.0)
    current = 10.0;
  if (current < 0.0)
    current = 0.0;

  if (current > 3.0) {
    bypassShunt100mA = 1;
    bypassShunt1A    = 1;
    shunt            = 0.0145;  //RES_HIGH_SHORT + RES_MED_SHORT + RES_LOW_ON;
  }

  else if (current > 1.0) {
    bypassShunt100mA = 1;
    bypassShunt1A    = 1;
    shunt            = 0.013;  //RES_HIGH_SHORT + RES_MED_SHORT + RES_LOW_ON;
  } else if (current > 0.1) {
    bypassShunt100mA = 0;
    bypassShunt1A    = 1;
    shunt            = RES_HIGH_SHORT + RES_MED_ON + RES_LOW_ON;
  } else {
    bypassShunt100mA = 0;
    bypassShunt1A    = 0;
    shunt            = RES_HIGH_ON + RES_MED_ON + RES_LOW_ON;
  }

  double shuntVoltage = current * shunt;
  shuntVoltage        = shuntVoltage * GAIN_SHUNT;
  dacOutputCurrent.write((float)shuntVoltage);
}

/**
 * @brief Initializes the all of the subclasses of the PMIC
 *
 * @return mbed_error_status_t
 */
mbed_error_status_t initialize() {
  puts("Initialization starting");
  mbed_error_status_t error = MBED_SUCCESS;

  lcd.begin(LCD_CONTRAST);
  lcd.clear();
  lcd.drawstring(0, 0, "Electronic Load");
  lcd.drawstring(0, 1, "Software V0.1.0");
  lcd.display();

  wait_us(1e6);
  puts("Initialization complete");
  return error;
}

/**
 * @brief Executes the main loop of the PMIC
 *
 * @return mbed_error_status_t error code
 */
mbed_error_status_t run() {
  uint32_t now        = HAL_GetTick();
  uint32_t nextRender = now + PERIOD_MS_RENDER;

  int lastKnob = knob.getPulses();

  while (true) {
    now = HAL_GetTick();
    if (now >= nextRender &&
        (nextRender >= PERIOD_MS_RENDER || now <= PERIOD_MS_RENDER)) {
      statusLED  = !statusLED;
      nextRender = now + PERIOD_MS_RENDER;

      menu.render();
      printf("%d %d Target: %f\n", bypassShunt1A.read(),
          bypassShunt100mA.read(), targetCurrent);
    }

    controlLoop();

    int currentKnob = knob.getPulses();
    menu.update(currentKnob - lastKnob);
    lastKnob = currentKnob;
  }
}

/**
 * Program start routine
 * @return error code
 */
int main(void) {
  mbed_error_status_t error = initialize();
  if (error) {
    printf("Failed to initialize: 0x%02X", error);
    return error;
  }
  error = run();
  if (error) {
    printf("Failed to run: 0x%02X", error);
    return error;
  }
  return MBED_SUCCESS;
}
