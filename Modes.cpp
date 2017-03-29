// 
// Helper to change through different modes.
// 

#include "Sound.h"
#include "Modes.h"
#include "Hardware.h"
#include "Physics.h"

Modes modes = Modes();
Effect_LightningBall lightningBall;
Effect_Fire fire;
Effect_Scan scan;
Effect_Hypnotic hypnotic;
Effect_ColorChanger red = Effect_ColorChanger(0xFFF, 0, 0);
Effect_ColorChanger green = Effect_ColorChanger(0, 0xfff, 0);
Effect_ColorChanger blue = Effect_ColorChanger(0, 0, 0xfff);
Effect_ColorChanger all = Effect_ColorChanger(0xFFF, 0xfff, 0xfff);

void Modes::init()
{
	effects[0] = &all;
	effects[1] = &fire;
	effects[2] = &scan;
	effects[3] = &hypnotic;
	effects[4] = &red;
	effects[5] = &green;
	effects[6] = &blue;
	

	activeMode = effects[3];

	modeLed[0] = &hardware.chips[0].leds[0];
	modeLed[1] = &hardware.chips[2].leds[2];
	modeLed[2] = &hardware.chips[1].leds[3];
	modeLed[3] = &hardware.chips[1].leds[0];
	modeLed[4] = &hardware.chips[3].leds[1];
	modeLed[5] = &hardware.chips[3].leds[4];
	modeLed[6] = &hardware.chips[3].leds[2];

	setupY.init(&hardware._y, -20, -8);
	physics.add(&setupY);

	setupImpulsY.init(&hardware._y);
	setupImpulsY.onTrigger = this;
	physics.add(&setupImpulsY);
}

void Modes::onTrack(int8_t direction)
{
	mode += direction;

	if (mode < 0) mode = EFFECT_COUNT - 1;
	else if (mode >= EFFECT_COUNT) mode = 0;

	lastLED = modeLed[mode];
	activeMode = effects[mode];
}

/*
 * What happens when setup is joined / leaved
 */
void Modes::onTrigger()
{
#ifdef MODE_DEBUG
	Serial.print("Setup Triggerd:");
	Serial.println(setupY.isTriggerd);
#endif // MODE_DEBUG

	// SETUP STATE CHANGE
	if (setupY.isTriggerd)
	{
		setupMode = !setupMode;
		if (setupMode)
		{
#ifdef MODE_DEBUG
			Serial.println("Setup ON");
#endif // MODE_DEBUG
			hardware.turnOffLEDs();
			lastLED = modeLed[mode];
		}
		else
		{
#ifdef MODE_DEBUG
			Serial.println("Setup OFF");
#endif
		}
	}
}

void Modes::animate(Ball* selector, uint16_t range, LED* target, int8_t direction)
{
	float time, mul, curveFactor;
	LED* led;
	uint16_t dist, baseBrightness, red, green;

	hardware.turnOffLEDs();
	for (int i = 0; i < selector->ledCount; i++)
	{
		led = selector->leds[i];

		dist = abs(selector->dist(led->_x, led->_y, led->_z));
		mul = (float)pow((float)dist / range, 2);
		curveFactor = millis() * 2;
		time = sin((curveFactor + direction * dist * 20.0f) / 314.0f);

		if (target != nullptr && led == target) time = (time + 1.0f) / 2.0f;

		time = constrain(time, 0.0f, 1.0f);
		baseBrightness = (int16_t)(0xFFF * time * mul);

		red = baseBrightness;
		green = (int16_t)(baseBrightness * (1.0f - mul)) / 4;

		led->setRGB(red, green, 0);
	}
}

void Modes::doModes()
{
	if (!setupMode && activeMode != nullptr)
		activeMode->doIt();
	else
	{
		ballSelector.setPosition(modeLed[mode]->_x, modeLed[mode]->_y, modeLed[mode]->_z);
		animate(&ballSelector, MODE_ANIMATE_RANGE, modeLed[mode], -1);
	}
		
#ifdef MODE_DEBUG
	if (setupY.isInRange) hardware.leds[1]->setRGB(0xFFF, 0, 0); else hardware.leds[1]->setRGB(0, 0, 0);
#endif // MODE_DEBUG
}

void Modes::singleTap()
{
	activeMode->onTap();
	if (setupMode)
	{
		onTrack(1);
		sound.tap();
	}
}

void Modes::doubleTap()
{
	activeMode->onDoubleTap();
	if (setupMode)
	{
		onTrack(-1);
		sound.doubleTap();
	}
}