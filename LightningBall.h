// LightningBall.h

#ifndef _LIGHTNINGBALL_h
#define _LIGHTNINGBALL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"
#include "Cube.h"

class Effect_LightningBall : public Effect
{
public:
	Effect_LightningBall();
	void doIt();
private:
	Cube* sel;
	
};

#endif

