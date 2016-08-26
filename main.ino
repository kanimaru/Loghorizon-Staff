#include "Gravity.h"
#include "LED.h"
#include "Ball.h"
#include "Hypnotic.h"
#include "PCA9685.h"
#include "Sound.h"
#include "Light.h"
#include "Modes.h"
#include "Timer.h"
#include "Hardware.h"
#include "Physics.h"

void serialEvent() {
	//serialIn();
}

void setup() {
	modes[0] = doHypnotic;
	modes[1] = doGravity;
	activeMode = doHypnotic;

	Serial.begin(19200);
	setupHardware();
	setupPhysics();
	setupModes();
	//setupLight();
	//setupSound();

	chips[0].leds[0].initDef(0, -20, 10, 0);
	chips[0].leds[1].initDef(3, -10, 10, 0);
	chips[0].leds[2].initDef(6, 0, 10, 0);
	chips[0].leds[3].initDef(9, 10, 10, 0);
	chips[0].leds[4].initDef(12, 40, 10, 0);

	chips[1].leds[0].initDef(0, -20, 10, 0);
	chips[1].leds[1].initDef(3, -10, 10, 0);
	chips[1].leds[2].initDef(6, 0, 10, 0);
	chips[1].leds[3].initDef(9, 10, 10, 0);
	chips[1].leds[4].initDef(12, 20, 10, 0);


}




void loop() {
	readAccel();
	handleTime();
	doPhysics();
	doModes();
	//doLight();
	//doSound();
	
	doLEDs();
}
