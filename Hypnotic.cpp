// 
// 4 Bytes RAM
// 642 Bytes Programm Memory
// 

#include "Hypnotic.h"
#include "Hardware.h"

double sinX = 0.01;
void doHypnotic()
{
	for (int i = 0; i < LED_AMOUNT; i++)
	{
		sinX += 0.01;
		leds[i]->r = abs(sin(sinX + 0.5 * i) * 0x0FF);
		leds[i]->g = abs(sin(sinX + 0.5 * i + 1) * 0x0FF);
		leds[i]->b = abs(sin(sinX + 0.5 * i + 2) * 0x0FF);
		leds[i]->update = true;
	}
}

