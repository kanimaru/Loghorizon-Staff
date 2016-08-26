// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PCA9685.h"
#include "LED.h"

//#define ACCEL_DEBUG
//#define ACCEL_MESSURE

#define PCA_AMOUNT 2
#define PCA_FREQ 1000
#define PCA_ALL 61 // = 250 (PCA * 4 + 6 logic)

#define LED_AMOUNT 10
#define SELF_CHECK_DUR 500

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

extern PCA9685 chips[];
extern LED* leds[];

void doLEDs();
void setupHardware();
void readAccel();
void serialIn();

#endif

