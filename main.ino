#include "ColorChanger.h"
#include "Effect.h"
#include "LightningBall.h"
#include "ADXL345.h"
#include <SPI.h>
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
#include "Physics.h"

void setup()
{
	Serial.begin(19200);

	hardware.init();
	physics.init();
	modes.init();
	light.init();

	Serial.print("Hardware");
	Serial.println(sizeof(hardware));

	Serial.print("Physics");
	Serial.println(sizeof(physics));

	Serial.print("Mode");
	Serial.println(sizeof(modes));
	//setupSound();

	// ^ y 
	// |  / z
	// | /
	// |/
	// +-----> x

	hardware.chips[0].leds[0].setPosition(29, 94, -6);
	hardware.chips[0].leds[1].setPosition(17, 70, 0);
	hardware.chips[0].leds[2].setPosition(37, 91, 2);
	hardware.chips[0].leds[3].setPosition(27, 72, 6);
	hardware.chips[0].leds[4].setPosition(28, 96, 6);
	hardware.chips[1].leds[0].setPosition(55, 32, -6);
	hardware.chips[1].leds[1].setPosition(35, 14, 6);
	hardware.chips[1].leds[2].setPosition(61, 31, -1);
	hardware.chips[1].leds[3].setPosition(59, 54, -6); // 
	hardware.chips[1].leds[4].setPosition(55, 31, 6);
	hardware.chips[2].leds[0].setPosition(48, 61, 0);
	hardware.chips[2].leds[1].setPosition(60, 68, 0);
	hardware.chips[2].leds[2].setPosition(29, 74, -6); //
	hardware.chips[2].leds[3].setPosition(56, 55, 6);
	hardware.chips[2].leds[4].setPosition(44, 81, -1);
	hardware.chips[3].leds[0].setPosition(43, 27, 1);
	hardware.chips[3].leds[1].setPosition(32, 13, -6);
	hardware.chips[3].leds[2].setPosition(37, 11, 1);
	hardware.chips[3].leds[3].setPosition(12, 4, 6);
	hardware.chips[3].leds[4].setPosition(12, 6, -6);
	hardware.chips[4].leds[0].setPosition(13, 76, 1);
	hardware.chips[4].leds[1].setPosition(19, 91, 1);
	hardware.chips[4].leds[2].setPosition(29, 100, 3);
	hardware.chips[4].leds[3].setPosition(24, 100, 0);
	hardware.chips[4].leds[4].setPosition(24, 100, 5);

	sound.boot();
}
/*
int incomingByte = 0;   // for incoming serial data
int packet[3];
int counter;
void serialEvent()
{
	if (Serial.available() > 0)
	{
		if (incomingByte == 0)
		{
			incomingByte = Serial.read();
			if (incomingByte == 255)
			{
				Sound.playTone(packet[0], packet[1])
				counter = 0;
			}
			packet[counter++] = incomingByte;

		
		}		
	}
}*/

void loop() {
#ifdef DEBUG_TIMING
	uint32_t d = millis();
#endif // DEBUG_TIMING

	hardware.doAccel();
#ifdef DEBUG_TIMING
	Serial.print("After 1: ");
	Serial.println(millis() - d);
	d = millis();
#endif // DEBUG_TIMING
	
	hardware.doTime();
	hardware.doCheckInactivity();
#ifdef DEBUG_TIMING
	Serial.print("After 2: ");
	Serial.println(millis() - d);
	d = millis();
#endif // DEBUG_TIMING

	physics.doPhysics();
#ifdef DEBUG_TIMING
	Serial.print("After 3: ");
	Serial.println(millis() - d);
	d = millis();
#endif // DEBUG_TIMING

	if (!hardware.inactive)
	{
		modes.doModes();
#ifdef DEBUG_TIMING
		Serial.print("After 4: ");
		Serial.println(millis() - d);
		d = millis();
#endif // DEBUG_TIMING

		hardware.doLEDs();
#ifdef DEBUG_TIMING
		Serial.print("After 5: ");
		Serial.println(millis() - d);
		d = millis();
#endif // DEBUG_TIMING

		sound.doSound();
#ifdef DEBUG_TIMING
		Serial.print("After 6: ");
		Serial.println(millis() - d);
		d = millis();
#endif // DEBUG_TIMING
	}
}
