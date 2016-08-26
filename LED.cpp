// 
// 
// 

#include "LED.h"


void LED::initDef(uint8_t channel, int16_t x, int16_t y, int16_t z)
{
	this->channel = channel;
	this->x = x;
	this->y = y;
	this->z = z;
}

void LED::setRGB(uint16_t b, uint16_t g, uint16_t r)
{
	r = constrain(r, 0, 0xFFF);
	g = constrain(g, 0, 0xFFF);
	b = constrain(b, 0, 0xFFF);
	if (this->r == r && this->g == g && this->b == b) return;
	update = true;
	this->r = r;
	this->g = g;
	this->b = b;
}
