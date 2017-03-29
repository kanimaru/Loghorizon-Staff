// Light.h

#ifndef _LIGHT_h
#define _LIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Physics.h"
#include "Effect.h"
#include "Hardware.h"

class Light : public Trigger
{
public:
	void init();
	void onTrigger();
private:
	AngleDef lightY;
	ImpulsDef lightImpulsY;
	Effect* oldMode = nullptr;
	boolean entered = 0;
};

extern Light light;

#endif

