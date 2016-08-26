// Ball.h

#ifndef _BALL_h
#define _BALL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Ball
{
public:
	int16_t x, y, z;

	Ball(int16_t x, int16_t y, int16_t z, int16_t radius);
	boolean isIn(int16_t x, int16_t y, int16_t z);
	int16_t dist(int16_t x, int16_t y, int16_t z);
	
	void debug();
private:
	int16_t _radius2, _radius;
};

#endif

