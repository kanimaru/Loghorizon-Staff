// Fire.h

#ifndef _FIRE_h
#define _FIRE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void setupFire();
void doFire();

#endif

