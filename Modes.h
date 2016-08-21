// Locking.h

#ifndef _LOCKING_h
#define _LOCKING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void setupModes();
void doModes();

#endif

