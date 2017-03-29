// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define LED_TYPE unint8_t

typedef uint16_t led_t;

class LED
{
public:
	int16_t _x, _y, _z;	
	led_t r, g, b;
	boolean update;

	void setPosition(int16_t _x, int16_t _y, int16_t _z);
	void setRGB(led_t r, led_t g, led_t b);
};

#endif

