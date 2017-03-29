// Hypnotic.h

#ifndef _HYPNOTIC_h
#define _HYPNOTIC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"

class Effect_Hypnotic : public Effect
{
public:
	void doIt();
private:
	double sinX = 0.01;
};

#endif

