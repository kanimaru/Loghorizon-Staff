#include "Fire.h"
#include "Hardware.h"
#include "Gravity.h"
#include "LED.h"
#include "Ball.h"
#include "Hypnotic.h"
#include "PCA9685.h"
#include "Sound.h"
#include "Light.h"
#include "Modes.h"
#include "Timer.h"
#include "Physics.h"

void setup() {
	modeHandler.modes[0] = doHypnotic;
	modeHandler.modes[1] = doGravity;
	modeHandler.modes[2] = doFire;
	modeHandler.activeMode = doHypnotic;

	Serial.begin(19200);
	hardware.setup();
	
	setupPhysics();
	modeHandler.setupModes();
	//setupLight();
	setupSound();

	hardware.chips[0].leds[0].initDef(0, -20, 10, 100);
	hardware.chips[0].leds[1].initDef(3, -10, 10, 70);
	hardware.chips[0].leds[2].initDef(6, 0, 10, 50);
	hardware.chips[0].leds[3].initDef(9, 10, 10, 20);
	hardware.chips[0].leds[4].initDef(12, 40, 10, 0);

	hardware.chips[1].leds[0].initDef(0, -20, 10, 100);
	hardware.chips[1].leds[1].initDef(3, -10, 10, 70);
	hardware.chips[1].leds[2].initDef(6, 0, 10, 50);
	hardware.chips[1].leds[3].initDef(9, 10, 10, 20);
	hardware.chips[1].leds[4].initDef(12, 20, 10, 10);
	

	hardware.chips[2].leds[0].initDef(0, -20, 10, 100);
	hardware.chips[2].leds[1].initDef(3, -10, 10, 70);
	hardware.chips[2].leds[2].initDef(6, 0, 10, 50);
	hardware.chips[2].leds[3].initDef(9, 10, 10, 20);
	hardware.chips[2].leds[4].initDef(12, 40, 10, 0);

	hardware.chips[3].leds[0].initDef(0, -20, 10, 100);
	hardware.chips[3].leds[1].initDef(3, -10, 10, 70);
	hardware.chips[3].leds[2].initDef(6, 0, 10, 50);
	hardware.chips[3].leds[3].initDef(9, 10, 10, 20);
	hardware.chips[3].leds[4].initDef(12, 20, 10, 10);
	
	//setupFire();


}




void loop() {
	hardware.doAccel();
	
	//handleTime();
	//doPhysics();
	//modeHandler.doModes();
	//doLight();
	doSound();
	
	hardware.doLEDs();
}
