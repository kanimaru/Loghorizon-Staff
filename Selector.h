// Selector.h

#ifndef _SELECTOR_h
#define _SELECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Hardware.h"

class Selector
{
public:
	LED* leds[LED_AMOUNT];
	uint8_t ledCount;

	void setX(int16_t x);
	void setY(int16_t y);
	void setZ(int16_t z);

	int16_t getX();
	int16_t getY();
	int16_t getZ();
	
	void setRGB(uint16_t r, uint16_t g, uint16_t b);
	void move(int16_t _x, int16_t _y, int16_t _z);
	void setPosition(int16_t _x, int16_t _y, int16_t _z);

	virtual boolean isIn(int16_t x, int16_t y, int16_t z) = 0;
protected:
	virtual void _collect();
	int16_t _x, _y, _z;
};

#endif