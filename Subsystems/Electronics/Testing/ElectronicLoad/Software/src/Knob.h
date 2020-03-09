#ifndef _KNOB_H_
#define _KNOB_H_

#include "Functions.h"
#include "QEI.h"



class Knob
{
    private:
    QEI encoder;

    int lastPulse = 0, currentPosition = 0, current = 0;

    public: 

    Knob(PinName channelA, PinName channelB);

    int8_t getMovement();

    int8_t isPressed();

    int getPosition();

    int getCurrent();

    int8_t reset();

    };

    #endif /* _KNOB_H_ */