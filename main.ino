#include "PCA9685.h"
#include "Sound.h"
#include "Light.h"
#include "Modes.h"
#include "Timer.h"
#include "Hardware.h"
#include "RGBHandler.h"
#include "AccelHandling.h"

void serialEvent() {
	//serialIn();
}

void test()
{
	RGB_set(LED_STATUS, 10, 0, 0);
}

#define MODULE_1 0x40
#define MODULE_2 0x41
#define MODULE_3 0x42
#define MODULE_4 0x43
#define MODULE_5 0x44

PCA9685[5]

PCA9685 whiteDrv(MODULE_1);
PCA9685 otherDrv(MODULE_2);

void setup() {
	Serial.begin(19200);
	pinMode(PIN_R1, OUTPUT);
	pinMode(PIN_G1, OUTPUT);
	pinMode(PIN_B1, OUTPUT);

	pinMode(PIN_R2, OUTPUT);
	pinMode(PIN_G2, OUTPUT);
	pinMode(PIN_B2, OUTPUT);

	//setupPhysics();
	//setupModes();
	//setupLight();
	//setupSound();

	whiteDrv.begin();
	whiteDrv.setFrequency(200);

	
	otherDrv.begin();
	otherDrv.setFrequency(200);
	otherDrv.setChannel(61, 0x0FF);

	//whiteDrv.setChannel(4, 0XFFF);
	//whiteDrv.setChannel(5, 0);
	//whiteDrv.setChannel(6, 0XFFF);
	
}


double sinX = 0.01;
double val = 0;

void loop() {
	
	for (int i = 0; i < 15; i++)
	{
		sinX += 0.01;
		val = sin(i*0.3 + sinX) * 0x0FF;
		if (val < 0)
		{
			val *= -1;
		}
		whiteDrv.setChannel(i, val);		
	}

	for (int i = 0; i < 15; i++)
	{
		sinX += 0.01;
		val = sin(i*0.3 + sinX) * 0x0FF;
		if (val < 0)
		{
			val *= -1;
		}
		otherDrv.setChannel(i, val);
	}

	//readAccel();
	//handleTime();
	//doPhysics();
	//doModes();
	//doLight();
	//doSound();
}
