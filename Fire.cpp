// 
// Simmulates fire and depends on the position how hot it is.
// 

#include "Fire.h"
#include "Hardware.h"
#include "Timer.h"

const uint16_t min_intensity = 0x00F;
const uint16_t max_intensity = 0x06F;
int simDelay;

uint16_t temperature[LED_AMOUNT];
uint16_t multiplier[LED_AMOUNT];
int minZ = 3000, maxZ = -3000;

void setupFire()
{

	// pre calculate
	for (uint8_t i = 0; i < LED_AMOUNT; i++) {
		minZ = min(hardware.leds[i]->z, minZ);
		maxZ = max(hardware.leds[i]->z, maxZ);
	}

	int diffZ = maxZ - minZ;
	// real calculation
	for (uint8_t i = 0; i < LED_AMOUNT; i++)
	{
		multiplier[i] = (100 * hardware.leds[i]->z / maxZ);
	}
}

void doFire()
{
	simDelay += diff;
	if (simDelay > 100)
	{
		for (uint8_t i = 0; i < LED_AMOUNT; i++)
		{
			if (random(0, 100) > 60)
			{
				uint8_t intensity = map(multiplier[i], 0, maxZ, 0x00F, 0xFFF);
				intensity += random(-0x0FF, 0x0FF);

				hardware.leds[i]->setRGB(intensity, intensity / 10, 0);
			}
		}
		simDelay = 0;
	}
}