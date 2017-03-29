// 
// 
// 

#include "LED.h"

void LED::setPosition(int16_t _x, int16_t _y, int16_t _z)
{
	this->_x = _x;
	this->_y = _y;
	this->_z = _z;
}

void LED::setRGB(led_t r, led_t g, led_t b)
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
