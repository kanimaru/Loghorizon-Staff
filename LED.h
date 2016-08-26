// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LED
{
public:
	uint8_t channel;
	int16_t x, y, z;
	uint16_t r, g, b;
	boolean update;

	void initDef(uint8_t channel, int16_t x, int16_t y, int16_t z);
	void setRGB(uint16_t r, uint16_t g, uint16_t b);
};

#endif
