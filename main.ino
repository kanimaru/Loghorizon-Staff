#include "Selector.h"
#include "Cube.h"
#include "Scan.h"
#include "PCA9685_LED.h"
#include "Fire.h"
#include "Hardware.h"
#include "LED.h"
#include "Ball.h"
#include "Hypnotic.h"
#include "PCA9685.h"
#include "Sound.h"
#include "Light.h"
#include "Modes.h"
#include "Timer.h"
#include "Physics.h"

void setup()
{
	delay(5000);

	modeHandler.modes[0] = doHypnotic;
	modeHandler.modes[1] = doFire;
	modeHandler.modes[2] = doScan;

	modeHandler.activeMode = doScan;

	Serial.begin(19200);
	hardware.setup();



	setupPhysics();
	modeHandler.setupModes();
	setupLight();
	//setupSound();

	// ^ y
	// |  / z
	// | /
	// |/
	// +-----> x

	hardware.chips[0].leds[0].initDef(0, 29, 94, -6);
	hardware.chips[0].leds[1].initDef(3, 17, 70, 0);
	hardware.chips[0].leds[2].initDef(6, 37, 91, 2);
	hardware.chips[0].leds[3].initDef(9, 27, 72, 6);
	hardware.chips[0].leds[4].initDef(12, 28, 96, 6);
	hardware.chips[1].leds[0].initDef(0, 55, 32, -6);
	hardware.chips[1].leds[1].initDef(3, 35, 14, 6);
	hardware.chips[1].leds[2].initDef(6, 61, 31, -1);
	hardware.chips[1].leds[3].initDef(9, 59, 54, -6);
	hardware.chips[1].leds[4].initDef(12, 55, 31, 6);
	hardware.chips[2].leds[0].initDef(0, 48, 61, 0);
	hardware.chips[2].leds[1].initDef(3, 60, 68, 0);
	hardware.chips[2].leds[2].initDef(6, 29, 74, -6);
	hardware.chips[2].leds[3].initDef(9, 56, 55, 6);
	hardware.chips[2].leds[4].initDef(12, 44, 81, -1);
	hardware.chips[3].leds[0].initDef(0, 43, 27, 1);
	hardware.chips[3].leds[1].initDef(3, 32, 13, -6);
	hardware.chips[3].leds[2].initDef(6, 37, 11, 1);
	hardware.chips[3].leds[3].initDef(9, 12, 4, 6);
	hardware.chips[3].leds[4].initDef(12, 12, 6, -6);
	hardware.chips[4].leds[0].initDef(0, 13, 76, 1);
	hardware.chips[4].leds[1].initDef(3, 19, 91, 1);
	hardware.chips[4].leds[2].initDef(6, 29, 100, 3);
	hardware.chips[4].leds[3].initDef(9, 24, 100, 0);
	hardware.chips[4].leds[4].initDef(12, 24, 100, 5);

	//setupFire();
}




void loop() {
	hardware.doAccel();
	
	handleTime();
	doPhysics();
	modeHandler.doModes();
	doLight();
	//doSound();
	
	hardware.doLEDs();
}
