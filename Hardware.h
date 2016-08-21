// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ACCEL_DEBUG
//#define ACCEL_MESSURE

#define PIN_ACCEL_X 0
#define PIN_ACCEL_Y 1
#define PIN_ACCEL_Z 2

// accerlated Values
extern int x;
extern int y;
extern int z;

// angle Values
extern double angX;
extern double angY;
extern double angZ;

extern int ACCEL_maxVal;
extern int ACCEL_minVal;

void readAccel();
void serialIn();

#endif

