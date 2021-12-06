#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define PERIOD_MS_RENDER 200

#define LCD_CONTRAST 0x18

#define KNOB_TICKS 24

#define RES_HIGH_SHORT (0.00082)
#define RES_HIGH_ON (0.510)
#define RES_MED_SHORT (0.00082)
#define RES_MED_ON (0.05)
#define RES_LOW_ON (0.005)
#define GAIN_SHUNT (48.0 / 3.1)
#define GAIN_OUTPUT_CURRENT ((3.1 / 50.0) / 0.005)
#define GAIN_OUTPUT_VOLTAGE (3.1 / (10.0 / (10.0 + 30.0)))
#define GAIN_INPUT_CURRENT ((3.1 / 50.0) / 0.005)
#define GAIN_INPUT_VOLTAGE (3.1 / (10.0 / (10.0 + 30.0)))

#endif /* _CONFIGURATION_H_ */