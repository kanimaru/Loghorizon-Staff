// Locking.h

#ifndef _LOCKING_h
#define _LOCKING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Physics.h"

#define MODE_COUNT 2
//#define MODE_DEBUG

extern runner modes[];
extern runner activeMode;

void setupModes();
void doModes();

#endif

