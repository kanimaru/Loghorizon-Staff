// 
// 
// 

#include "ColorChanger.h"
#include "Hardware.h"
Effect_ColorChanger::Effect_ColorChanger(uint16_t r, uint16_t g, uint16_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}


void Effect_ColorChanger::doIt()
{
	for (int i = 0; i < LED_AMOUNT; i++)
	{
		if (enabled)
		{
			hardware.leds[i]->setRGB(0,0,0);
		} else {
			hardware.leds[i]->setRGB(r, g, b);
		}
	}
}

void Effect_ColorChanger::onTap()
{
	enabled = enabled == true ? false : true ;
}