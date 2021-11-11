#include "Display.h"

/**
 * @brief outputs a menu to the lcd displays that allows the user to view
 * important values and allows user to change the current and power values
 *
 * @param pinOutputVoltage pin name for output voltage sensor
 * @param pinOutputCurrent pin name for
 * @param pinInputVoltage pin name for auxiliary voltage sensor
 * @param pinInputCurrent pin name for
 */
Display::Display(PinName pinOutputVoltage, PinName pinOutputCurrent,PinName pinInputVoltage, PinName pinInputCurrent) :
  outputVoltage(pinOutputVoltage), outputCurrent(pinOutputCurrent), inputVoltage(pinInputVoltage), inputCurrent(pinInputCurrent) {
  int modifyChoice = 0;

  Knob niceKnob(KNOB_A, KNOB_B); // Initializing the niceKnob Knob class
  DigitalOut status(LED1); // initialize led

  while (true) {
    if(niceKnob.isPressed()){
      if(modifyChoice == 2){
        modifyChoice = 0;
      }
      else {
        modifyChoice++;
      }
    }

    //DRAW SELECT DOT ON the line to modify and modify that thing
    if(modifyChoice == 0){
      //choice to mod current
      printf("Modify Choice: 1");
      drawDisplay();
      niceKnob.reset();
      setCurrent((niceKnob.getMovement()*.1));
    }

    if(modifyChoice == 1){
      //choice to mod power
      printf("Modify Choice: 2");
      drawDisplay();
      niceKnob.reset();
      setCurrentWP(niceKnob.getMovement()*.1);
    }

    if(modifyChoice == 2){
      //choice to mod resistance
      printf("Modify Choice: 3");
      drawDisplay();
      niceKnob.reset();
      setCurrentWR(niceKnob.getMovement() % 4);
    }
    
    status = !status;
    wait_us(500e3);
  }
}

/**
 * @brief calculates the power using voltage and current 
 * @return double power
 */
double Display::calculatePower(double voltage, double current) {
  double power = 0.0;

  // calculates the power by multiplying the voltage and the current
  power = getOutputVoltage() * getOutputCurrent();

  return power;
}

/**
 * @brief calculates the resistance using voltage and current
 * @return double resistance
 */
double Display::calculateResistance() {
  double resistance = 0.0;

  // calculates the power by multiplying the voltage and the current
  resistance = getOutputVoltage() / getOutputCurrent();

  return resistance;
}

/**
 * @brief calculates the efficiency using input power and output power 
 * @return double efficiency
 */
double Display::calculateEfficiency() {
  double efficiency = 0.0;

  // calculate the efficiency by dividing the output power by the input power;
  efficiency = calculatePower(getOutputVoltage(), getOutputCurrent()) / calculatePower(getInputVoltage(), getCurrentCurrent());

  return efficiency;
}

void Display::drawDisplay(){
    printf("   AC Voltage: %.4f\r\n", getOutputVoltage());
    printf("1. AC Current: %.4f\r\n", getOutputCurrent());
    printf("2. AC Power: %.4f\r\n", calculatePower(getOutputVoltage(), getOutputCurrent()));
    printf("   Aux Voltage: %.4f\r\n", getInputVoltage());
    printf("3. Aux Current: %.4f\r\n", getCurrentCurrent());
    printf("   Aux Power: %.4f\r\n", calculatePower(getInputVoltage(), getCurrentCurrent()));
}
