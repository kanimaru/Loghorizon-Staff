// PCA9685_LED.h

#ifndef _PCA9685_LED_h
#define _PCA9685_LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PCA9685.h"

class PCA9685_LED : public PCA9685
{
public:
	PCA9685_LED(uint8_t address);
	void update();
	LED leds[5];
};


#endif

