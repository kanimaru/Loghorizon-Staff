// 
// 
// 

#include "Light.h"
#include "Physics.h"
#include "Hardware.h"
#include "Effect.h"
#include "Modes.h"

Light light;

void Light::init()
{
	lightY.init(&hardware._y, -2, 2);
	physics.add(&lightY);

	lightImpulsY.init(&hardware._y);
	lightImpulsY.onTrigger = this;
	physics.add(&lightImpulsY);
}

void Light::onTrigger()
{
	if (!lightY.isTriggerd) return;

	if(!entered) {
		entered = true;
		hardware.turnOffLEDs();
		hardware.chips[4].leds[2].setRGB(0xFFF, 0xFFF, 0xFFF);
		hardware.chips[4].leds[3].setRGB(0xFFF, 0xFFF, 0xFFF);
		hardware.chips[4].leds[4].setRGB(0xFFF, 0xFFF, 0xFFF);

		oldMode = modes.activeMode;
		modes.activeMode = nullptr;
	}
	else
	{
		entered = false;
		hardware.chips[4].leds[2].setRGB(0, 0, 0);
		hardware.chips[4].leds[3].setRGB(0, 0, 0);
		hardware.chips[4].leds[4].setRGB(0, 0, 0);
		modes.activeMode = oldMode;
	}
}
