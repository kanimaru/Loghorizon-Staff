// Hardware.h
#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PCA9685_LED.h"
#include "LED.h"
#include "ADXL345.h"
#include "Defines.h"

class Hardware
{
public:
	void init();
	void turnOffLEDs();
	void doAccel();
	void doLEDs();
	void doTime();
	void doCheckInactivity();

	void disableInactive();
	void enableInactive();

	ADXL345 adxl = ADXL345();
	PCA9685_LED chips[PCA_AMOUNT] = { 0x40, 0x41, 0x42, 0x44, 0x60};
	LED* leds[LED_AMOUNT];

	// accerlated Values
	int8_t _x;
	int8_t _y;
	int8_t _z;

	// Timer
	unsigned long ms;
	unsigned long last;
	uint8_t diff;

	boolean inactive;

private:
	int _pos;
	int _flatX[SMOOTHNESS];
	int _flatY[SMOOTHNESS];
	int _flatZ[SMOOTHNESS];

	int8_t _xOffset = -0;
	int8_t _yOffset = 0;
	int8_t _zOffset = -0;

	void selfCheck();
	void turnOff();
	void turnOn();

	boolean _inactivityEnabled = true;
	boolean _inactivity = false;
	uint16_t _inactiveCounter = 0;

};

extern Hardware hardware;

#endif

