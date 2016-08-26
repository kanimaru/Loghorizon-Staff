// 
// 
// 

#include "Modes.h"
#include "Physics.h"
#include "Hardware.h"
#include "LED.h"

AngleDef* setupX;
AngleDef* setupZ;
ImpulsDef* setupImpulsY;
boolean setupMode;

AngleDef* modeX;
AngleDef* modeZ;
TrackAngleDef* trackY;

int mode = 0;
runner modes[MODE_COUNT];
runner activeMode;
LED* lastLED;
void changeMode(int direction)
{
	if (!modeX->isTriggerd) return;
	mode += direction;

	if (mode < 0)
	{
		mode = MODE_COUNT - 1;
	}
	else if (mode >= MODE_COUNT)
	{
		mode = 0;
	}

	lastLED->setRGB(0, 0, 0);
	leds[mode]->setRGB(0xFFF, 0xFFF, 0xFFF);
	lastLED = leds[mode];

	Serial.print("Mode Changes: ");
	Serial.println(mode);
	activeMode = modes[mode];
	
}

void doSetup()
{
	// SETUP STATE CHANGE
	if (setupX->isTriggerd && setupZ->isTriggerd)
	{
		setupMode = !setupMode;
		if (setupMode)
		{
#ifdef MODE_DEBUG
			leds[0]->setRGB(0, 10, 0);
#endif
			trackY = trackAngle(&angY, 60, changeMode);
			modeX = restrictAngle(&angZ, 0, 20);
			Serial.println("Setup ON");
			for (uint8_t i = 0; i < LED_AMOUNT; i++)
			{
				leds[i]->setRGB(0, 0, 0);
			}
			leds[mode]->setRGB(0xFFF, 0xFFF, 0xFFF);
			lastLED = leds[mode];
		}
		else
		{
#ifdef MODE_DEBUG
			leds[0]->setRGB(10, 0, 0);
#endif
			freeTrackAngleDef(trackY);
			freeAngleDef(modeX);
			Serial.println("Setup OFF");
		}
	}
}

void setupModes()
{
	setupX = restrictAngle(&angX, 70, 110);
	setupZ = restrictAngle(&angZ, 70, 110);
	setupImpulsY = restrictImpuls(&y);
	setupImpulsY->onTrigger = doSetup;

#ifdef MODE_DEBUG
	leds[0]->setRGB(10, 0, 0);
#endif
}

void doModes()
{
	if (!setupMode)
	{
		activeMode();
	}
	

#ifdef MODE_DEBUG
	if (setupX->isTriggerd) leds[1]->setRGB(10, 0, 0); else leds[1]->setRGB(0, 0, 0);
	if (setupZ->isTriggerd) leds[2]->setRGB(10, 0, 0); else leds[2]->setRGB(0, 0, 0);
#endif // MODE_DEBUG
}
