// ColorChanger.h

#ifndef _COLORCHANGER_h
#define _COLORCHANGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Effect.h"

class Effect_ColorChanger : public Effect
{
public:
	Effect_ColorChanger(uint16_t r, uint16_t g, uint16_t b);
	void doIt();
	void onTap();
private: 
	uint16_t r;
	uint16_t g;
	uint16_t b;
	boolean enabled;
};

#endif

