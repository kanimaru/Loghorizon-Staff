// Fire.h

#ifndef _FIRE_h
#define _FIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Defines.h"
#include "Effect.h"
#include "Ball.h"

class Effect_Fire : public Effect
{
public:
	void doIt();
private:
	Ball ballSelector = Ball(0, 0, 0, FIRE_ANIMATE_RANGE);

	void restrictBall(Ball* ball);
};

#endif