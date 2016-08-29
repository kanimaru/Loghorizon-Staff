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

class Hardware
{
public:
	void setup();

	void turnOffLEDs();
	void doAccel();
	void doLEDs();

	void simmulateAccel();

	PCA9685 chips[PCA_AMOUNT] = { 0x40, 0x41 };// , 0x42, 0x43, 0x44};
	LED* leds[LED_AMOUNT];

	// angle Values
	double angX;
	double angY;
	double angZ;

	// accerlated Values
	int x;
	int y;
	int z;
private:
	/*
	My min and max values for my chip.
	Min-x:243 y:261 z:268
	Max-x:421 y:420 z:422
	*/
#ifndef ACCEL_SIMMULATE
	int minAccel[3] = { 262,261,275 };
	int maxAccel[3] = { 403,403,413 };
#else
	const int minAccel[3] = { 0,0,0 };
	const int maxAccel[3] = { 255,255,255 };
#endif // !ACCEL_SIMMULATE

	void transform(int xRead, int yRead, int zRead);
	void selfCheck();
	void messureAccel(int xRead, int yRead, int zRead);


};

extern Hardware hardware;

#endif

