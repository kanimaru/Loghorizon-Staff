// 
// Helper to change through different modes.
// 

#include "Modes.h"

ModeHandler modeHandler = ModeHandler();

/*
 * Callback for changing modes.
 */
void ModeHandler::changeMode(int8_t direction)
{
	if (!modeHandler.modeX->isTriggerd) return;
	modeHandler.mode += direction;

	if (modeHandler.mode < 0) modeHandler.mode = MODE_COUNT - 1;
	else if (modeHandler.mode >= MODE_COUNT) modeHandler.mode = 0;

	modeHandler.lastLED->setRGB(0, 0, 0);
	hardware.leds[modeHandler.mode]->setRGB(0xFFF, 0xFFF, 0xFFF);
	modeHandler.lastLED = hardware.leds[modeHandler.mode];

#ifdef MODE_DEBUG
	Serial.print("Mode Changes: ");
	Serial.println(modes.mode);
#endif //  MODE_DEBUG
	modeHandler.activeMode = modeHandler.modes[modeHandler.mode];
}
void ModeHandler::wrap_changeMode(int8_t direction)
{
	modeHandler.changeMode(direction);
}

/*
 * What happens when setup is joined / leaved
 */
void ModeHandler::doSetup()
{
	// SETUP STATE CHANGE
	if (setupX->isTriggerd && setupZ->isTriggerd)
	{
		setupMode = !setupMode;
		if (setupMode)
		{
			trackY = trackAngle(&hardware.angY, 60, ModeHandler::wrap_changeMode);
			modeX = restrictAngle(&hardware.angZ, 0, 20);
#ifdef MODE_DEBUG
			Serial.println("Setup ON");
#endif // MODE_DEBUG
			hardware.turnOffLEDs();
			hardware.leds[mode]->setRGB(0xFFF, 0xFFF, 0xFFF);
			lastLED = hardware.leds[mode];
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

void ModeHandler::setupModes()
{
	setupX = restrictAngle(&hardware.angX, 70, 110);
	setupZ = restrictAngle(&hardware.angZ, 70, 110);
	setupImpulsY = restrictImpuls(&hardware._y);
	setupImpulsY->onTrigger = ModeHandler::wrap_doSetup;

#ifdef MODE_DEBUG
	leds[0]->setRGB(10, 0, 0);
#endif
}

void ModeHandler::wrap_doSetup()
{
	modeHandler.doSetup();
}

void ModeHandler::doModes()
{
	if (!setupMode)
		activeMode();

#ifdef MODE_DEBUG
	if (setupX->isTriggerd) leds[1]->setRGB(10, 0, 0); else leds[1]->setRGB(0, 0, 0);
	if (setupZ->isTriggerd) leds[2]->setRGB(10, 0, 0); else leds[2]->setRGB(0, 0, 0);
#endif // MODE_DEBUG
}
