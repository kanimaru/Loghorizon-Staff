// 
// 
// 

#include "LED.h"
#define R_FIRST 0b001
#define G_FIRST 0b010
#define B_FIRST 0b100

#define R_SECOND 0b0010000
#define G_SECOND 0b0100000
#define B_SECOND 0b1000000

void LED::initDef(uint8_t channel, int16_t _x, int16_t _y, int16_t _z)
{
	this->channel = channel;
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
}

void LED::setRGB(uint16_t r, uint16_t g, uint16_t b)
{
	uint16_t temp;
	r = constrain(r, 0, 0xFFF);
	g = constrain(g, 0, 0xFFF);
	b = constrain(b, 0, 0xFFF);

	if (this->r == r && this->g == g && this->b == b) return;
	update = true;
	this->r = r;
	this->g = g;
	this->b = b;
}
