// 
// 
// 

#include "AccelMode.h"
#include "Hardware.h"

void doAccel()
{
	for (uint8_t i = 0; i < LED_AMOUNT; i++)
	{
		hardware.leds[i]->setRGB(hardware._x * 0x0F, hardware._y * 0x0F, hardware._z * 0x0F);
	}
}
