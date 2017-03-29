// Effect.h

#ifndef _EFFECT_h
#define _EFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Effect
{
public:
	virtual void doIt() = 0;
	virtual void onTap() {};
	virtual void onDoubleTap() {};
};

#endif

