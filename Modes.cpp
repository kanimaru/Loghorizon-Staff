// 
// 
// 

#include "Modes.h"
#include "AccelHandling.h"
#include "RGBHandler.h"
#include "Hardware.h"

AngleDef* setupX;
AngleDef* setupZ;
ImpulsDef* setupImpulsY;
boolean setupMode;

AngleDef* modeX;
AngleDef* modeZ;
TrackAngleDef* trackY;
int mode = 0;

void changeMode(int direction)
{
	if (!modeX->isTriggerd) return;
	mode += direction;
	
	if (mode < 0)
	{
		mode = 5;
	}
	else if (mode > 5)
	{
		mode = 0;
	}
	Serial.print("Mode Changes: ");
	Serial.println(mode);
}

void doSetup()
{
	// SETUP STATE CHANGE
	if (setupX->isTriggerd && setupZ->isTriggerd)
	{
		setupMode = !setupMode;
		if (setupMode)
		{
			RGB_set(LED_STATUS, 0, 10, 0);
			trackY = trackAngle(&angY, 60, changeMode);
			modeX = restrictAngle(&angX, 300, 360);
			Serial.println("Setup ON");
		}
		else
		{
			RGB_set(LED_STATUS, 10, 0, 0);
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

	RGB_set(LED_STATUS, 10, 0, 0);
}

void doModes()
{
	// MODES
	//analogWrite(11, mode * 10);
}
