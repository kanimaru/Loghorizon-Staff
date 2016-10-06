// Hardware.h
#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PCA9685_LED.h"
#include "LED.h"

#define ACCEL_DEBUG
//#define ACCEL_MESSURE

#define PCA_AMOUNT 5
#define PCA_FREQ 200
#define PCA_ALL 61 // = 250 (PCA * 4 + 6 logic)

#define LED_AMOUNT 25
#define SELF_CHECK_DUR 100

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

	PCA9685 sound = PCA9685(0x43);
	PCA9685_LED chips[PCA_AMOUNT] = { 0x40, 0x41, 0x42, 0x44, 0x60};
	LED* leds[LED_AMOUNT];

	// angle Values
	double angX;
	double angY;
	double angZ;

	// accerlated Values
	int8_t _x;
	int8_t _y;
	int8_t _z;
private:
	const uint8_t offsetX = 27;
	const uint8_t offsetY = 116;
	const uint8_t offsetZ = 27;
	/*
	My min and max values for my chip.
	Min-x:243 y:261 z:268
	Max-x:421 y:420 z:422
	*/
#ifndef ACCEL_SIMMULATE
	const uint8_t minAccel[3] = { 262,261,275 };
	const uint8_t maxAccel[3] = { 403,403,413 };
#else
	const uint8_t minAccel[3] = { 0,0,0 };
	const uint8_t maxAccel[3] = { 255,255,255 };
#endif // !ACCEL_SIMMULATE

	void transform(uint8_t xRead, uint8_t yRead, uint8_t zRead);
	void selfCheck();
	void messureAccel(uint8_t xRead, uint8_t yRead, uint8_t zRead);


};

extern Hardware hardware;

#endif

